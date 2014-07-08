/*
 * Copyright 2010 MQWeb - Franky Braem
 *
 * Licensed under the EUPL, Version 1.1 or - as soon they
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
#ifndef _MQWeb_ChannelMapper_H
#define _MQWeb_ChannelMapper_H

#include "MQ/Web/MQMapper.h"

namespace MQ {
namespace Web {

class ChannelMapper : public MQMapper
	/// Maps channel object to/from Websphere MQ
{
public:

	ChannelMapper(CommandServer& commandServer);
		/// Constructor

	virtual ~ChannelMapper();
		/// Destructor

	void change(const Poco::JSON::Object::Ptr&obj);
		/// Implements the change channel command. Not implemented yet.

	void create(const Poco::JSON::Object::Ptr& obj, bool replace = false);
		/// Implements the create channel command. Not implemented yet.

	void copy(const Poco::JSON::Object::Ptr& obj, bool replace = false);
		/// Implements the copy channel command. Not implemented yet.

	Poco::JSON::Array::Ptr inquire(const Poco::JSON::Object::Ptr& filter);
		/// Implements the inquire channel command.

private:

	ChannelMapper(const ChannelMapper&);

};

}} // Namespace MQ::Web

#endif // _MQWeb_ChannelMapper_H
