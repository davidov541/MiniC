#include "SymbolTable.h"
#include "stdafx.h"

namespace MiniC
{
	namespace IR
	{
		namespace AST
		{
			SymbolTable::SymbolTable()
			{
				this->variableLookup = std::stack<boost::unordered_map<std::wstring, std::wstring> >();
				this->functionSignatureTypes = boost::unordered_map<std::wstring, std::list<std::wstring> >();
				this->functionSignatureNames = boost::unordered_map<std::wstring, std::list<std::wstring> >();
				this->implementedFuncs = boost::unordered_map<std::wstring, std::wstring>();
				this->variableLengthFuncs = std::list<std::wstring>();
				this->calledFuncs = std::list<std::wstring>();
				this->structSignatureFields = boost::unordered_map<std::wstring, std::list<std::wstring> >();
				this->structSignatureTypes = boost::unordered_map<std::wstring, std::list<std::wstring> >();
			}

			SymbolTable::SymbolTable(SymbolTable& rhs)
			{
				this->variableLookup = rhs.variableLookup;
				// this->functionSignatureNames = rhs.functionSignatureNames;
				// this->functionSignatureTypes = rhs.functionSignatureTypes;
				this->returnStmtFound = rhs.returnStmtFound;
				this->currFunc = rhs.currFunc;
				// this->implementedFuncs = rhs.implementedFuncs;
				this->calledFuncs = rhs.calledFuncs;
				this->variableLengthFuncs = rhs.variableLengthFuncs;
				// this->structSignatureFields = rhs.structSignatureFields;
				// this->structSignatureTypes = rhs.structSignatureTypes;
			}

			void SymbolTable::AddFunction(std::wstring name, std::wstring type, std::list<std::wstring> paramNames, std::list<std::wstring> paramTypes, bool isVariableLength)
			{
				this->functionSignatureNames[name] = paramNames;
				this->functionSignatureTypes[name] = paramTypes;
				this->implementedFuncs[name] = type;
				if (isVariableLength)
				{
					this->variableLengthFuncs.push_back(name);
				}
			}

			void SymbolTable::AddFunctionDecl(std::wstring name, std::list<std::wstring> paramNames, std::list<std::wstring> paramTypes, bool isVariableLength)
			{
				this->functionSignatureNames[name] = paramNames;
				this->functionSignatureTypes[name] = paramTypes;
				if (isVariableLength)
				{
					this->variableLengthFuncs.push_back(name);
				}
			}

			bool SymbolTable::CheckFuncImplementation(std::wstring name)
			{
				return (this->implementedFuncs.find(name) != this->implementedFuncs.end());
			}
		
			void SymbolTable::AddFunctionUse(std::wstring name)
			{
				this->calledFuncs.push_back(name);
			}

			bool SymbolTable::CheckFunctionUse(std::wstring name)
			{
				BOOST_FOREACH(std::wstring currFunc, this->calledFuncs)
				{
					if (currFunc.compare(name) == 0)
					{
						return true;
					}
				}
				return false;
			}

			
			bool SymbolTable::CheckVariableLengthFunction(std::wstring name)
			{
				BOOST_FOREACH(std::wstring currFunc, this->variableLengthFuncs)
				{
					if (currFunc.compare(name) == 0)
					{
						return true;
					}
				}
				return false;
			}

			std::wstring SymbolTable::GetCurrFunc()
			{
				return this->currFunc;
			}

			void SymbolTable::SetCurrFunc(std::wstring name)
			{
				this->currFunc = name;
			}

			std::wstring SymbolTable::GetReturnType(std::wstring name)
			{
				//TODO: This is a bit of a hack, since it will break if I add structs, but it works for now.
				std::wstring intName = L"int";
				std::wstring boolName = L"boolean";
				std::wstring voidName = L"void";
				if (this->implementedFuncs.count(name) > 0)
				{
					return this->implementedFuncs[name];
				}
				else
				{
					ErrorHandler::GetInstance()->RegisterError(L"Return type for function is not recognized.");
					return L"ERROR";
				}
			}

			std::list<std::wstring> SymbolTable::GetParamTypes(std::wstring name)
			{
				std::list<std::wstring> returnable;
				if (this->functionSignatureNames.find(name) == this->functionSignatureNames.end() || this->functionSignatureTypes.find(name) == this->functionSignatureTypes.end())
				{
					TCHAR* error = (TCHAR*) calloc(sizeof(TCHAR), ERROR_LENGTH_MAX);
					swprintf_s(error, MAX_ERROR_LEN, FUNCTION_SIGNATURE_NOT_FOUND, name.c_str());
					MiniC::ErrorHandler::GetInstance()->RegisterError(error);
					return returnable;								
				}
				std::list<std::wstring> types = this->functionSignatureTypes.at(name);
				std::list<std::wstring> names = this->functionSignatureNames.at(name);
				std::list<std::wstring>::iterator it;
				std::list<std::wstring>::iterator it2;
				for(it = types.begin(), it2 = names.begin(); it != types.end() && it2 != names.end(); it++, it2++)
				{
					returnable.push_back((*it));
				}
				return returnable;
			}

			void SymbolTable::FoundReturn()
			{
				this->returnStmtFound = true;
			}

			bool SymbolTable::WasReturnFound()
			{
				return this->returnStmtFound;
			}

			//VARIABLES:
			void SymbolTable::AddVariable(std::wstring name, std::wstring type)
			{
				boost::unordered_map<std::wstring, std::wstring>* scopeMap = &(this->variableLookup.top());
				if (scopeMap->count(name) > 0) {
					ErrorHandler::GetInstance()->RegisterError(L"Variable with this name is already registered for this scope.");
				} else {
					(*scopeMap)[name] = type;
					this->variableLookup.push(*scopeMap);
				}
				this->variableLookup.pop();
			}

			std::wstring SymbolTable::GetVarType(std::wstring name)
			{
				std::stack<boost::unordered_map<std::wstring, std::wstring> > tmpStack;
				while(this->variableLookup.size() > 0) {
					tmpStack.push(this->variableLookup.top());
					this->variableLookup.pop();
					boost::unordered_map<std::wstring, std::wstring>* scopeMap = &(tmpStack.top());
					if (scopeMap->count(name) > 0) {
						std::wstring type = (*scopeMap)[name];
						while(!tmpStack.empty()) {
							this->variableLookup.push(tmpStack.top());
							tmpStack.pop();
						}
						return type;
					}
				}
				while(!tmpStack.empty()) {
					this->variableLookup.push(tmpStack.top());
					tmpStack.pop();
				}
				std::wstring err = std::wstring();
				err.append(L"Variable ");
				err.append(name);
				err.append(L" does not exist in this context. Please ensure it has been properly declared and initialized.");
				ErrorHandler::GetInstance()->RegisterError(err.c_str());
				return L"ERROR";
			}      

			//SCOPES:
			void SymbolTable::EnterScope()
			{
				this->variableLookup.push(boost::unordered_map<std::wstring, std::wstring>());
			}

			void SymbolTable::ExitScope()
			{
				this->variableLookup.pop();
				this->returnStmtFound = false;
			}

			//STRUCTS:
			void SymbolTable::AddStruct(std::wstring name, std::list<std::wstring> fieldNames, std::list<std::wstring> fieldTypes)
			{
				if (this->structSignatureFields.count(name) > 0)
				{
					ErrorHandler::GetInstance()->RegisterError(L"A struct with the same name has already been declared.");
				}
				this->structSignatureFields[name] = fieldNames;
				this->structSignatureTypes[name] = fieldTypes;
			}

			std::wstring SymbolTable::GetStructFieldType(std::wstring structName, std::wstring fieldName)
			{
				if (this->structSignatureTypes.count(structName) == 0)
				{
					std::wstring errMsg = std::wstring();
					errMsg.append(L"Struct ");
					errMsg.append(structName);
					errMsg.append(L" has not been declared before this use.");
					ErrorHandler::GetInstance()->RegisterError(errMsg);
				}
				std::list<std::wstring> types = this->structSignatureTypes[structName];
				std::list<std::wstring> names = this->structSignatureFields[structName];
				std::list<std::wstring>::iterator itr1;
				std::list<std::wstring>::iterator itr2;
				for(itr1 = names.begin(), itr2 = types.begin(); itr1 != names.end() && itr2 != types.end(); itr1++, itr2++)
				{
					if (itr1->compare(fieldName) == 0)
					{
						return *itr2;
					}
				}
				std::wstring errMsg = std::wstring();
				errMsg.append(L"Struct ");
				errMsg.append(structName);
				errMsg.append(L" has no field named ");
				errMsg.append(fieldName);
				errMsg.append(L".");
				ErrorHandler::GetInstance()->RegisterError(errMsg);
				return L"ERROR";
			}
			
			std::list<std::wstring> SymbolTable::GetStructFieldNames(std::wstring structName)
			{
				if (this->structSignatureTypes.count(structName) == 0)
				{
					std::wstring errMsg = std::wstring();
					errMsg.append(L"Struct ");
					errMsg.append(structName);
					errMsg.append(L" has not been declared before this use.");
					ErrorHandler::GetInstance()->RegisterError(errMsg);
				}
				return this->structSignatureFields[structName];
			}

			bool SymbolTable::IsPrimitiveTypeValid(std::wstring name)
			{
				std::list<std::wstring> primitiveTypes = std::list<std::wstring>();
				primitiveTypes.push_back(L"int");
				primitiveTypes.push_back(L"long");
				primitiveTypes.push_back(L"void");
				primitiveTypes.push_back(L"char");
				primitiveTypes.push_back(L"short");
				primitiveTypes.push_back(L"boolean");
				BOOST_FOREACH(std::wstring type, primitiveTypes)
				{
					if (name.compare(type) == 0)
					{
						return true;
					}
				}
				return false;
			}
			
			
			bool SymbolTable::CheckStructExists(std::wstring name)
			{
				int fieldCount = this->structSignatureFields.count(name);
				int typeCount = this->structSignatureTypes.count(name);
				return this->structSignatureFields.count(name) > 0 && this->structSignatureTypes.count(name) > 0;
			}
		}
	}
}
