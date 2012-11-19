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
#include <sstream>
#include <iomanip>

#include <Poco/DateTime.h>
#include <Poco/DateTimeParser.h>

#include <MQ/Message.h>

namespace MQ
{
  
MQMD Message::_initialMD = {MQMD_DEFAULT};

Message::Message(int size) 
  : _buffer(size)
  , _md(_initialMD)
  , _dataLength(0L)
{
}


BufferPtr Message::getCorrelationId() const
{
  return new Buffer(_md.CorrelId, MQ_CORREL_ID_LENGTH);
}


void Message::setCorrelationId(const Buffer& buffer)
{
	std::memset(_md.CorrelId, 0, MQ_CORREL_ID_LENGTH);
	std::memcpy(_md.CorrelId, 
				buffer.begin(), 
				buffer.size() > MQ_CORREL_ID_LENGTH ? MQ_CORREL_ID_LENGTH : buffer.size());
}

BufferPtr Message::getMessageId() const
{
  return new Buffer(_md.MsgId, MQ_MSG_ID_LENGTH);
}

bool Message::isEmptyMessageId() const
{
  for(int i = 0; i < MQ_MSG_ID_LENGTH; i++)
  {
    if ( _md.MsgId[i] != 0 )
    {
      return false;
    }
  }
  return true;
}

void Message::setMessageId(const Buffer& buffer)
{
	std::memset(_md.MsgId, 0, MQ_MSG_ID_LENGTH);
	std::memcpy(_md.MsgId, 
				buffer.begin(), 
				buffer.size() > MQ_MSG_ID_LENGTH ? MQ_MSG_ID_LENGTH : buffer.size());
}

Poco::DateTime Message::getPutDate() const
{
  Poco::DateTime dateTime;

  std::string dateValue(_md.PutDate, MQ_PUT_DATE_LENGTH);
  std::string timeValue(_md.PutTime, MQ_PUT_TIME_LENGTH);
  dateValue += timeValue;
 
  int timeZone;
  Poco::DateTimeParser::parse("%Y%n%e%H%M%S", dateValue, dateTime, timeZone);
  return dateTime;
}

std::string Message::getUser() const
{
  std::string user(_md.UserIdentifier, MQ_USER_ID_LENGTH);
  user.erase(user.find_last_not_of(" \n\r\t")+1); // trim
  return user;
}

std::string Message::getPutApplication() const
{
  std::string app(_md.PutApplName, MQ_PUT_APPL_NAME_LENGTH);
  app.erase(app.find_last_not_of(" \n\r\t")+1); // trim
  return app;
}

std::string Message::getReplyToQueue() const
{
  std::string q(_md.ReplyToQ, MQ_Q_NAME_LENGTH);
  q.erase(q.find_last_not_of(" \n\r\t")+1); // trim
  return q;
}

}
