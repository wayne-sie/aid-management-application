//Wayne Sie 139951180
#pragma once
#include <iostream>

#ifndef AMA_ERRORSTATE_H
#define AMA_ERRORSTATE_H

namespace ama
{
	class ErrorState
	{
		char* messageInfo;


	public:
		explicit ErrorState(const char* errorMessage = nullptr);
		ErrorState(const ErrorState& other) = delete;
		ErrorState& operator=(const ErrorState& other) = delete;
		~ErrorState();
		operator bool() const;
		ErrorState& operator=(const char* pText);
		void message(const char* pText);
		const char* message() const;

	};

	std::ostream& operator<<(std::ostream& rs, const ErrorState& es);
}
#endif
//Wayne Sie 139951180
#pragma once
#include <iostream>

#ifndef AMA_ERRORSTATE_H
#define AMA_ERRORSTATE_H

namespace ama
{
	class ErrorState
	{
		char* messageInfo;


	public:
		explicit ErrorState(const char* errorMessage = nullptr);
		ErrorState(const ErrorState& other) = delete;
		ErrorState& operator=(const ErrorState& other) = delete;
		~ErrorState();
		operator bool() const;
		ErrorState& operator=(const char* pText);
		void message(const char* pText);
		const char* message() const;

	};

	std::ostream& operator<<(std::ostream& rs, const ErrorState& es);
}
#endif
