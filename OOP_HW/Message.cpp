#include "Message.h"
#pragma warning (disable : 4996)

MyString Message::getCurrentTime()
{
	time_t now = time(0);
	tm* localTime = localtime(&now);

	char buffer[20];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);

	return MyString(buffer);
}

Message::Message(int senderID, MyString content)
{
	this->senderID = senderID;
	this->content = content;
	this->timestamp = getCurrentTime();
}

const MyString& Message::getContent() const
{
	return this->content;
}
const MyString& Message::getTimeStamp() const
{
	return this->timestamp;
}