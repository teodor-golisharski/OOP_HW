// Teodor Golisharski 6MI0600367
#include "Message.h"
#include "Utilities.h"
#pragma warning (disable : 4996)

Message::Message() : isDeleted(false), senderId(-1), recipientId(-1), content(""), timestamp("")
{
}

MyString Message::getCurrentTime()
{
	time_t now = time(0);
	tm* localTime = localtime(&now);

	char buffer[20];
	strftime(buffer, sizeof(buffer), "%H:%M %d.%m.%Y", localTime);

	return MyString(buffer);
}

Message::Message(int senderID, int recipientID, const MyString& content)
{
	this->isDeleted = false;
	this->senderId = senderID;
	this->recipientId = recipientID;
	if (!validateString(content))
	{
		throw std::invalid_argument(InformativeMessages::CONTENT_RULES);

	}
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
	return this->senderId;
}

int Message::getRecipientID() const
{
	return this->recipientId;
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

