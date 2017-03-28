/*
 * Copyright 2010 MQWeb - Franky Braem
 *
 * Licensed under the EUPL, Version 1.1 or  as soon they
 * will be approved by the European Commission - subsequent
 * versions of the EUPL (the "Licence");
 * You may not use this work except in compliance with the
 * Licence.
 * You may obtain a copy of the Licence at:
 *
 * http://joinup.ec.europa.eu/software/page/eupl
 *
 * Unless required by applicable law or agreed to in
 * writing, software distributed under the Licence is
 * distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied.
 * See the Licence for the specific language governing
 * permissions and limitations under the Licence.
 */
#include "Poco/Util/Application.h"

#include "MQ/MQSubsystem.h"

#include "MQ/Web/QueueManagerPoolCache.h"
#include "MQ/Web/QueueManagerDefaultConfig.h"

namespace MQ {
namespace Web {

QueueManagerPoolCache* QueueManagerPoolCache::_instance = NULL;

QueueManagerPoolCache::QueueManagerPoolCache()
{
	setup();
}

QueueManagerPoolCache::~QueueManagerPoolCache()
{
	_instance = NULL;
}

void QueueManagerPoolCache::setup()
{
	poco_assert(_instance == NULL);
	_instance = this;
}

QueueManagerPool::Ptr QueueManagerPoolCache::getQueueManagerPool(const std::string& qmgrName)
{
	QueueManagerPool::Ptr pool = _cache.get(qmgrName);
	if ( pool.isNull() )
	{
		Poco::Mutex::ScopedLock lock(_mutex);
		pool = _cache.get(qmgrName); // Check it again ...
		if ( pool.isNull() )
		{
			pool = createPool(qmgrName);
		}
	}

	return pool;
}

void QueueManagerPoolCache::clear()
{
	_cache.clear();
}

QueueManagerPool::Ptr QueueManagerPoolCache::createPool(const std::string& qmgrName)
{
	QueueManagerPool::Ptr pool;

	MQSubsystem& mqSystem = Poco::Util::Application::instance().getSubsystem<MQSubsystem>();
	Poco::Util::LayeredConfiguration& config = Poco::Util::Application::instance().config();

	Poco::SharedPtr<QueueManagerFactory> factory;

	if ( mqSystem.client() )
	{
		QueueManagerDefaultConfig qmgrConfig(qmgrName, config);
		factory = new QueueManagerFactory(qmgrName, qmgrConfig.read());
	}
	else
	{
		factory = new QueueManagerFactory(qmgrName);
	}

	std::size_t capacity;
	std::size_t peakCapacity;
	int idle;

	std::string qmgrConfig = "mq.web.qmgr." + qmgrName;
	std::string qmgrPoolCapacity = qmgrConfig + ".pool.capacity";
	if ( !config.has(qmgrPoolCapacity) )
	{
		qmgrPoolCapacity = "mq.web.pool.capacity";
	}
	capacity = config.getInt(qmgrPoolCapacity, 10);

	std::string qmgrPoolPeakCapacity = qmgrConfig + ".pool.peakcapacity";
	if ( !config.has(qmgrPoolPeakCapacity) )
	{
		qmgrPoolPeakCapacity = "mq.web.pool.peakcapacity";
	}
	peakCapacity = config.getInt(qmgrPoolPeakCapacity, 20);

	std::string qmgrPoolIdle = qmgrConfig + ".pool.idle";
	if ( !config.has(qmgrPoolIdle) )
	{
		qmgrPoolIdle = "mq.web.pool.idle";
	}
	idle = config.getInt(qmgrPoolIdle, 60);

	pool = new QueueManagerPool(factory, capacity, peakCapacity, idle);

	_cache.add(qmgrName, pool);
	return pool;
}

} } // Namespace MQ
