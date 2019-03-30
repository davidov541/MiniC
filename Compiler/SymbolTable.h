#ifndef ST_H_
#define ST_H_

#include "stdafx.h"
#include "ErrorHandler.h"

namespace MiniC
{
  namespace IR
  {
    namespace AST
	{
      class SymbolTable
	  {
      private:
		//Set to true when return node is found, and reset to false once we leave the scope. Checked when leaving function to make sure an overall return statement is found.
		bool returnStmtFound;
	
		std::wstring currFunc;
	
		//Maps local variables to their types.
		std::stack<boost::unordered_map<std::wstring, std::wstring> > variableLookup;
	
		//Maps function name to a list of parameter types.
		boost::unordered_map<std::wstring, std::list<std::wstring> > functionSignatureTypes;

		//Maps function name to a list of parameter names.
		boost::unordered_map<std::wstring, std::list<std::wstring> > functionSignatureNames;
	
		// Tracks which functions have been implemented, versus functions that have only been declared.
		boost::unordered_map<std::wstring, std::wstring> implementedFuncs;

		// Tracks which functions have been called, allowing us to prune out useless functions.
		std::list<std::wstring> calledFuncs;

		//Tracks which funcs are allowed to have any number of variables after the defined number.
		std::list<std::wstring> variableLengthFuncs;

		//Maps struct name to list of types which it contains.
		boost::unordered_map<std::wstring, std::list<std::wstring> > structSignatureTypes;

		//Maps struct name to list of names of fields it contains.
		boost::unordered_map<std::wstring, std::list<std::wstring> > structSignatureFields;

      public:
		//CONSTRUCTORS:
		SymbolTable();
		SymbolTable(SymbolTable& rhs);
		
		bool Equals(SymbolTable* other);

		//FUNCTIONS:
		void SymbolTable::AddFunction(std::wstring name, std::wstring type, std::list<std::wstring> paramNames, std::list<std::wstring> paramTypes, bool isVariableLength);
		void AddFunctionDecl(std::wstring name, std::list<std::wstring> paramNames, std::list<std::wstring> paramTypes, bool isVariableLength);
		bool CheckFuncImplementation(std::wstring name);
		void AddFunctionUse(std::wstring name);
		bool CheckFunctionUse(std::wstring name);
		bool CheckVariableLengthFunction(std::wstring name);
		//NOTE: GetCurrFunc is responsible for telling ErrorHandler::GetInstance() that we are in a new function.
		std::wstring GetCurrFunc();
		void SetCurrFunc(std::wstring name);
		std::wstring GetReturnType(std::wstring name);
		std::list<std::wstring> GetParamTypes(std::wstring name);
		void FoundReturn();
		bool WasReturnFound();
	
		//VARIABLES:
		void AddVariable(std::wstring name, std::wstring type);
		std::wstring GetVarType(std::wstring name);
	
		//SCOPES:
		void EnterScope();
		void ExitScope();

		//STRUCTS:
		void AddStruct(std::wstring name, std::list<std::wstring> fieldNames, std::list<std::wstring> fieldTypes);
		std::wstring GetStructFieldType(std::wstring structName, std::wstring fieldName);
		std::list<std::wstring> GetStructFieldNames(std::wstring structName);
		bool CheckStructExists(std::wstring name);
		static bool IsPrimitiveTypeValid(std::wstring name);
      };
    }
  }
}
#endif
