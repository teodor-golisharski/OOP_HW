// Teodor Golisharski 6MI0600367
#include "Utilities.h"
#include "ApplicationConstants.h"

bool validateName(const MyString& input)
{
	if (!validateString(input)) return false;
    return input != "" && input.length() >= GeneralConstants::NAME_MIN_LENGTH;
}

bool validateString(const MyString& input)
{
	if (input.length() == 0)
	{
		return false;
	}
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == GeneralConstants::DELIMETER)
		{
			return false;
		}
	}
	return true;
}
