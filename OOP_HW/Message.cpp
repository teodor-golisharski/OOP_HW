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

Message::Message(int senderID, int recipientID, const MyString& content)
{
	this->isDeleted = false;
	this->senderID = senderID;
	this->recipientID = recipientID;
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

int Message::getSenderID() const
{
	return this->senderID;
}

int Message::getRecipientID() const
{
	return this->recipientID;
}

bool Message::getIsDeleted() const
{
	return this->isDeleted;
}

void Message::deleteMessage()
{
	isDeleted = true;
}

void Message::overrideTimestamp(const MyString& newTimestamp)
{
	timestamp = newTimestamp;
}

