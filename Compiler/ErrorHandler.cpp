#include "ErrorHandler.h"
#include "stdafx.h"

namespace MiniC {

	ErrorHandler* ErrorHandler::instance = NULL;

	ErrorHandler::ErrorHandler(int debugCode) 
	{
		this->debugCode = debugCode;
	}

	ErrorHandler::~ErrorHandler() {  }

	bool ErrorHandler::CheckFlag()
	{
		bool flag = this->FlagRaised;
		this->FlagRaised = false;
		return flag;
	}

	void ErrorHandler::SetFlag()
	{
		this->FlagRaised = true;
	}

	ErrorHandler* ErrorHandler::GetInstance()
	{
		return GetInstance(0);
	}

	ErrorHandler* ErrorHandler::GetInstance(int debugCode)
	{
		if (instance == NULL)
		{
			instance = new ErrorHandler(debugCode);
		}
		return instance;
	}

	void ErrorHandler::ClearErrors()
	{
		instance = NULL;
	}

	void ErrorHandler::RegisterError(std::wstring message)
	{
		this->ErrorList.push_back(Error(this->currFunc, message));
	}

	bool ErrorHandler::IsEmpty()
	{
		return this->ErrorList.size() == 0;
	}

	std::wstring ErrorHandler::PrintErrors()
	{
		int errorCount = 0;
		std::wstringstream errorMsgs;
		BOOST_FOREACH(Error e, this->ErrorList) {
			errorMsgs << L"Error ";
			errorMsgs << ++errorCount;
			errorMsgs << L" in ";
			errorMsgs << e.GetLocation();
			errorMsgs << L": ";
			errorMsgs << e.GetMessage();
			errorMsgs << std::endl;
		}
		return errorMsgs.str();
	}

	void ErrorHandler::EnterFunc(std::wstring function)
	{
		this->currFunc = function;
	}

	int ErrorHandler::GetDebugCode()
	{
		return this->debugCode;
	}

	Error::Error(std::wstring function, std::wstring message)
	{
		this->function = function;
		this->message = message;
	}

	Error::~Error() {   }

	std::wstring Error::GetMessage()
	{
		return this->message;
	}

	std::wstring Error::GetLocation()
	{
		return this->function;
	}
}
