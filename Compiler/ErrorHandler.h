#ifndef ERROR_LOGGER_H_
#define ERROR_LOGGER_H_

#include "stdafx.h"

namespace MiniC {
	class Error {

	protected:
		std::wstring message;
		std::wstring function;

	public:
		Error(std::wstring function, std::wstring message);
		virtual ~Error();
		std::wstring GetMessage();
		std::wstring GetLocation();
	};

	class ErrorHandler {

	protected:
		static ErrorHandler* instance;
		std::list<Error> ErrorList;
		std::wstring currFunc;
		bool FlagRaised;
		int debugCode;

	public:
		ErrorHandler(int debugCode);
		virtual ~ErrorHandler();
		static ErrorHandler* GetInstance();
		static ErrorHandler* GetInstance(int debugCode);
		static void ClearErrors();
		void RegisterError(std::wstring message);
		void EnterFunc(std::wstring function);
		bool IsEmpty();
		std::wstring PrintErrors();
		bool CheckFlag();
		void SetFlag();
		int GetDebugCode();
	};

}

#endif
