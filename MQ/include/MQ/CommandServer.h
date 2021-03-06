/*
 * Copyright 2010 MQWeb - Franky Braem
 *
 * Licensed under the EUPL, Version 1.1 or – as soon they
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

#ifndef _MQ_CommandServer_h
#define _MQ_CommandServer_h

#include <cmqc.h>
#include <vector>

#include "MQ/Queue.h"
#include "MQ/PCF.h"

#include "Poco/SharedPtr.h"

namespace MQ {

class QueueManager;

class CommandServer
	/// Class for sending PCF commands to a queuemanager
{
public:
	std::string commandQName() const;
		/// Returns the name of the command queue.

	PCF::Ptr createCommand(MQLONG command) const;
		/// Returns a shared pointer to a PCF object for the given command.

	void sendCommand(PCF::Ptr& command, PCF::Vector& response);
		/// Sends the command to the queuemanager. The response is returned
		/// as a vector of PCF objects. Can throw a MQException.

	std::string replyQName() const;
		/// Returns the name of the reply queue.

private:
	CommandServer(QueueManager& qmgr, const std::string& modelQueue);
		/// Constructor.

	CommandServer(const CommandServer& copy);
	CommandServer& operator = (const  CommandServer& copy);

	QueueManager& _qmgr;

	Queue _commandQ;

	Queue _replyQ;

	friend class QueueManager;
};

inline std::string CommandServer::commandQName() const
{
	return _commandQ.name();
}

inline std::string CommandServer::replyQName() const
{
	return _replyQ.name();
}

} // namespace MQ

#endif //  _MQ_CommandServer_h
