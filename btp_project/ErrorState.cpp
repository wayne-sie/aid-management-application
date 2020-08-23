//Wayne Sie 139951180
#include <iostream>
#include "ErrorState.h"
#include <cstring>

using namespace std;
using namespace ama;

namespace ama
{
	ErrorState::ErrorState(const char* errorMessage)
	{
		//delete[] messageInfo;
		if (errorMessage == nullptr || strcmp(errorMessage, "") == 0)
		{
			messageInfo = nullptr;
		}
		else
		{
			int size = strlen(errorMessage);
			this->messageInfo = new char[size + 1];
			strcpy(messageInfo, errorMessage);
			messageInfo[size] = '\0';
		}
	}

	ErrorState::~ErrorState()
	{
		delete[] messageInfo;
		messageInfo = nullptr;
	}

	ErrorState::operator bool() const
	{
		return this->messageInfo != nullptr;
	}

	ErrorState& ErrorState::operator=(const char* pText)
	{
		delete[] messageInfo;
		if (pText != nullptr && pText[0] != '\0')
		{

			int size = strlen(pText);
			this->messageInfo = new char[size + 1];
			strcpy(messageInfo, pText);
			messageInfo[size] = '\0';
		}
		else
		{
			this->messageInfo = nullptr;
		}
		return *this;
	}

	void ErrorState::message(const char* pText)
	{
		*this = pText;
	}

	const char* ErrorState::message() const
	{
		if (*this == false)
		{
			return nullptr;
		}
		else
		{
			return this->messageInfo;
		}
	}

	ostream& operator<<(ostream & rs, const ErrorState & es)
	{
		if (es)
		{
			rs << es.message();
		}
		return rs;
	}

}