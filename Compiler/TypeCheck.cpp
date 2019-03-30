#include "Node.h"
#include "stdafx.h"

//TODOs:
//Check all possible locations of return statements so all paths will return.
//Check for unreachable code (because of return statements).
//Keep track of line numbers inside of the Node for reporting purposes.
//Test all possible type errors.


namespace MiniC
{
	namespace IR
	{
		namespace AST
		{
			void PrimitiveTypeNode::VerifyValidType(SymbolTable env)
			{
				if (!env.IsPrimitiveTypeValid(this->name))
				{
					std::wstringstream ss;
					ss << L"Invalid type " << this->name << L".";
					ErrorHandler::GetInstance()->RegisterError(ss.str());
				}
			}

			int PrimitiveTypeNode::GetTypeSize(SymbolTable env)
			{
				return 2;
			}

			void StructTypeNode::VerifyValidType(SymbolTable env)
			{
				if (!env.CheckStructExists(this->name))
				{
					std::wstringstream ss;
					ss << L"Invalid type " << this->name << L".";
					ErrorHandler::GetInstance()->RegisterError(ss.str());
				}
			}

			int StructTypeNode::GetTypeSize(SymbolTable env)
			{
				std::list<std::wstring> names = env.GetStructFieldNames(this->name);
				int count = 0;
				BOOST_FOREACH(std::wstring name, names)
				{
					std::wstring strType = env.GetStructFieldType(this->name, name);
					TypeNode* type = TypeNode::GetTypeNode(strType, env);
					count += type->GetTypeSize(env);
					delete type;
				}
				return count;
			}

			SymbolTable FormalNode::FullTypeCheck(SymbolTable env)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 2)
				{
					wprintf(L"%s%s%s%s.\n", L"Typechecking FormalNode Name: ", this->name.c_str(), L" Type: ", this->type->To_String().c_str());
				}

				this->type->VerifyValidType(env);
				this->allocSize = this->type->GetTypeSize(env);
				//Void types cannot be declared, are only implicit (like 0 or NULL)
				if (this->type->Equals(new PrimitiveTypeNode(L"void"))) 
				{
					ErrorHandler::GetInstance()->RegisterError(L"Void is not a valid variable type.");
				} 
				else 
				{
					env.AddVariable(this->name, this->type->To_String());
				}
				return env;
			}

			SymbolTable FuncNode::Register(SymbolTable env)
			{
				if (env.CheckFuncImplementation(this->name))
				{
					ErrorHandler::GetInstance()->RegisterError(L"Multiple definitions found for function.");
					return env;
				}
				std::list<std::wstring> paramNames;
				std::list<std::wstring> paramTypes;
				BOOST_FOREACH(FormalNode* formal, this->parameters)
				{
					paramNames.push_back(formal->name);
					paramTypes.push_back(formal->type->To_String());
				}
				env.AddFunction(this->name, this->type->To_String(), paramNames, paramTypes, this->isVariableLength);
				return env;
			}

			SymbolTable FuncNode::FullTypeCheck(SymbolTable env)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 2)
				{
					wprintf(L"%s %s %s %s.\n", L"Typechecking FuncNode Name:", this->name.c_str(), L"Type:", this->type->To_String().c_str());
				}
				env.EnterScope();
				ErrorHandler::GetInstance()->EnterFunc(this->name);
				env.SetCurrFunc(this->name);
				this->type->VerifyValidType(env);
				BOOST_FOREACH(FormalNode* formal, this->parameters) 
				{
					env = formal->FullTypeCheck(env);
				}
				BOOST_FOREACH(StmtNode* stmt, this->body) 
				{
					env = stmt->FullTypeCheck(env);
				}
				if (!this->type->Equals(new PrimitiveTypeNode(L"void")) && !env.WasReturnFound()) 
				{
					ErrorHandler::GetInstance()->RegisterError(L"No return statement found for function.");
				}
				env.ExitScope();
				return env;
			}


			/*
			*		FuncDeclNode Class: represents a function declaration
			*		Contains:	name		- string
			*				type		- PrimitiveTypeNode
			*				parameters	- list of formals
			*/
			
			SymbolTable FuncDeclNode::Register(SymbolTable env)
			{
				std::list<std::wstring> paramNames;
				std::list<std::wstring> paramTypes;
				BOOST_FOREACH(FormalNode* formal, this->parameters)
				{
					paramNames.push_back(formal->name);
					paramTypes.push_back(formal->type->To_String());
				}
				env.AddFunctionDecl(this->name, paramNames, paramTypes, this->isVariableLength);
				return env;
			}
			
			SymbolTable FuncDeclNode::FullTypeCheck(SymbolTable env)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 2)
				{
					wprintf(L"%s %s %s %s.\n", L"Typechecking FuncDeclNode Name:", this->name.c_str(), L"Type:", this->type->To_String().c_str());
				}
				env.EnterScope();
				ErrorHandler::GetInstance()->EnterFunc(this->name);
				env.SetCurrFunc(this->name);
				this->type->VerifyValidType(env);
				BOOST_FOREACH(FormalNode* formal, this->parameters) 
				{
					env = formal->FullTypeCheck(env);
				}
				env.ExitScope();
				return env;
			}


			/*
			*		GlobalDeclAssignNode Class: represents a declaration & assignment node at the global scope
			*		Contains:	type - Type
			*					name - string
			*					rhs  - expression
			*/

			SymbolTable GlobalDeclAssignNode::Register(SymbolTable env)
			{
				return env;
			}

			SymbolTable GlobalDeclAssignNode::FullTypeCheck(SymbolTable env) 
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 2)
				{
					wprintf(L"%s%s%s%s.\n", L"Typechecking DeclAssignNode Name: ", this->name.c_str(), L" Type: ", this->type->To_String().c_str());
				}
				if (this->defaultVal)
				{
					this->rhs = (ExprNode*) this->type->GetDefaultValue(env);
				}
				TypeNode* rhsType = this->rhs->TypeOf(&env);
				this->type->VerifyValidType(env);
				if (!(this->type->CheckArrayDim(env)))
				{
					ErrorHandler::GetInstance()->RegisterError(L"Array dimensions for array declaration is not of type integer.");
				}
				else if (this->type->Equals(new PrimitiveTypeNode(L"void"))) 
				{
					ErrorHandler::GetInstance()->RegisterError(L"Cannot instantiate variable of type void.");
				} 
				else if (this->type->Compare(rhsType) == 0)
				{
					this->allocSize = this->type->GetTypeSize(env);
					env.AddVariable(this->name, this->type->To_String());
				} 
				else
				{
					wprintf(L"%s%s%s%s\n", "LHSType = ", this->type->To_String(), " RHSType = ", rhsType->To_String());
					ErrorHandler::GetInstance()->RegisterError(L"Type of right hand side does not match declared type of variable.");
				}
				return env;
			}

			SymbolTable GlobalStructInitNode::Register(SymbolTable env)
			{
				return env;
			}

			SymbolTable GlobalStructInitNode::FullTypeCheck(SymbolTable env)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 2)
				{
					wprintf(L"%s%s%s%s.\n", L"Typechecking DeclAssignNode Name: ", this->name.c_str(), L" Type: ", this->type->To_String().c_str());
				}
				this->type->VerifyValidType(env);
				if (!(this->type->CheckArrayDim(env)))
				{
					ErrorHandler::GetInstance()->RegisterError(L"Array dimensions for array declaration is not of type integer.");
				}
				else if (this->type->Equals(new PrimitiveTypeNode(L"void"))) 
				{
					ErrorHandler::GetInstance()->RegisterError(L"Cannot instantiate variable of type void.");
				}
				else if (this->defaultVal)
				{
					std::list<std::wstring> fields = env.GetStructFieldNames(this->type->GetName());
					std::list<ExprNode*>::iterator itr = this->inits.begin();
					BOOST_FOREACH(std::wstring field, fields)
					{
						std::wstring type = env.GetStructFieldType(this->type->GetName(), field);
						TypeNode* fieldType = TypeNode::GetTypeNode(type, env);
						this->inits.push_back((ExprNode*) fieldType->GetDefaultValue(env));
					}
				}
				else
				{
					std::list<std::wstring> fields = env.GetStructFieldNames(this->type->GetName());
					std::list<ExprNode*>::iterator itr = this->inits.begin();
					BOOST_FOREACH(std::wstring field, fields)
					{
						std::wstring type = env.GetStructFieldType(this->type->GetName(), field);
						TypeNode* initType = (*itr)->TypeOf(&env);
						if (TypeNode::GetTypeNode(type, env)->Compare(initType) != 0)
						{
							std::wstringstream wss;
							wss << L"Incorrect value in initializer for struct. Expected Type was ";
							wss << this->type->To_String();
							wss << L", while actual type was " << initType->To_String();
							ErrorHandler::GetInstance()->RegisterError(wss.str());
						}
					}
				}
				return env;
			}

			/*
			*		StructDeclNode Class: represents the declaration of a struct
			*/
			SymbolTable StructDeclNode::Register(SymbolTable env)
			{
				return env;
			}

			SymbolTable StructDeclNode::FullTypeCheck(SymbolTable env)
			{
				std::list<std::wstring> strTypes = std::list<std::wstring>();
				BOOST_FOREACH(TypeNode* type, this->types)
				{
					strTypes.push_back(type->To_String());
				}
				env.AddStruct(this->struct_name, this->names, strTypes);
				BOOST_FOREACH(TypeNode* type, this->types)
				{
					type->VerifyValidType(env);
					if (type->Equals(TypeNode::GetTypeNode(this->struct_name, env)))
					{
						std::wstringstream errMsg = std::wstringstream();
						errMsg << L"Struct " << this->struct_name << L" has a field of its' own type, which is not allowed.";
						ErrorHandler::GetInstance()->RegisterError(errMsg.str());
					}
				}
				if (this->init_name.compare(L"") != 0)
				{
					env.AddVariable(this->init_name, this->struct_name);
				}
				return env;
			}

			SymbolTable ProgramNode::GetFunctions(SymbolTable env, bool isOS)
			{
				std::list<TranslationUnitNode*> removeable;
				std::list<std::wstring> foundFuncs;
				do
				{
					removeable = std::list<TranslationUnitNode*>();
					foundFuncs = std::list<std::wstring>();
					BOOST_FOREACH(TranslationUnitNode* unit, this->funcs)
					{
						BOOST_FOREACH(std::wstring func, unit->GetFunctionUses())
						{
							foundFuncs.push_back(func);
						}
					}
					BOOST_FOREACH(TranslationUnitNode* unit, this->funcs)
					{
						if (!unit->CheckUsage(foundFuncs) && !unit->isInterruptHandler)
						{
							removeable.push_back(unit);
						}
					}
					BOOST_FOREACH(TranslationUnitNode* unit, removeable)
					{
						this->funcs.remove(unit);
					}
				} while (removeable.size() > 0);
				bool foundIH = false;
				BOOST_FOREACH(TranslationUnitNode* unit, this->funcs) 
				{
					if (!isOS && unit->isInterruptHandler)
					{
						std::wstringstream wss;
						wss << L"ERROR - Interrupt Handler routines are not allowed in non-boot loadable programs!";
						ErrorHandler::GetInstance()->RegisterError(wss.str());
					}
					else if (unit->isInterruptHandler && foundIH)
					{
						std::wstringstream wss;
						wss << L"ERROR - Only one interrupt handler routine is allowed per boot-loadable program!";
						ErrorHandler::GetInstance()->RegisterError(wss.str());
					}
					else if (unit->isInterruptHandler)
					{
						foundIH = true;
					}
					env = unit->Register(env);
				}
				return env;
			}      

			SymbolTable ProgramNode::FullTypeCheck(SymbolTable env) 
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 2)
				{
					wprintf(L"Typechecking ProgramNode \n");
				}
				bool hasMain = false;
				env.EnterScope();
				BOOST_FOREACH(TranslationUnitNode* unit, this->funcs)
				{
					if (unit->isMain && !hasMain) 
					{
						hasMain = true;
					} 
					else if (hasMain && unit->isMain)
					{
						ErrorHandler::GetInstance()->RegisterError(L"More than one possible main function detected. Only one main function is allowed per program.");
					}
					env = unit->FullTypeCheck(env);
				}
				env.ExitScope();
				if (!hasMain) 
				{
					ErrorHandler::GetInstance()->EnterFunc(L"Program");
					ErrorHandler::GetInstance()->RegisterError(L"No Main Function Found. Please include a main function for execution to start.");
				}
				return env;
			}

			SymbolTable ExpressionStmt::FullTypeCheck(SymbolTable env)
			{
				this->expr->TypeOf(&env);
				return env;
			}

			SymbolTable DeclAssignNode::FullTypeCheck(SymbolTable env) 
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 2)
				{
					wprintf(L"%s%s%s%s.\n", L"Typechecking DeclAssignNode Name: ", this->name.c_str(), L" Type: ", this->type->To_String().c_str());
				}
				if (this->defaultVal)
				{
					this->rhs = (ExprNode*) this->type->GetDefaultValue(env);
				}
				TypeNode* rhsType = this->rhs->TypeOf(&env);
				this->type->VerifyValidType(env);
				if (!(this->type->CheckArrayDim(env)))
				{
					ErrorHandler::GetInstance()->RegisterError(L"Array dimensions for array declaration is not of type integer.");
				}
				else if (this->type->Equals(new PrimitiveTypeNode(L"void"))) 
				{
					ErrorHandler::GetInstance()->RegisterError(L"Cannot instantiate variable of type void.");
				} 
				else if (this->type->Compare(rhsType) == 0)
				{
					env.AddVariable(this->name, this->type->To_String());
					this->allocSize = this->type->GetTypeSize(env);
				} 
				else
				{
					std::wstringstream wss;
					wss << L"Incorrect type on right hand side of initialization. Expected Type was ";
					wss << this->type->To_String();
					wss << L", while actual type was " << rhsType->To_String();
					ErrorHandler::GetInstance()->RegisterError(wss.str());
				}
				return env;
			}

			SymbolTable StructInitNode::FullTypeCheck(SymbolTable env)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 2)
				{
					wprintf(L"%s%s%s%s.\n", L"Typechecking DeclAssignNode Name: ", this->name.c_str(), L" Type: ", this->type->To_String().c_str());
				}
				this->type->VerifyValidType(env);
				if (!(this->type->CheckArrayDim(env)))
				{
					ErrorHandler::GetInstance()->RegisterError(L"Array dimensions for array declaration is not of type integer.");
				}
				else if (this->type->Equals(new PrimitiveTypeNode(L"void"))) 
				{
					ErrorHandler::GetInstance()->RegisterError(L"Cannot instantiate variable of type void.");
				} 
				else if (this->defaultVal)
				{
					std::list<std::wstring> fields = env.GetStructFieldNames(this->type->GetName());
					std::list<ExprNode*>::iterator itr = this->inits.begin();
					BOOST_FOREACH(std::wstring field, fields)
					{
						std::wstring type = env.GetStructFieldType(this->type->GetName(), field);
						TypeNode* fieldType = TypeNode::GetTypeNode(type, env);
						this->inits.push_back((ExprNode*) fieldType->GetDefaultValue(env));
					}
					env.AddVariable(this->name, this->type->To_String());
				}
				else
				{
					std::list<std::wstring> fields = env.GetStructFieldNames(this->type->GetName());
					std::list<ExprNode*>::iterator itr = this->inits.begin();
					if(fields.size() != this->inits.size())
					{
						std::wstringstream wss;
						wss << L"Incorrect number of arguments for initialization for struct " << this->name;
						ErrorHandler::GetInstance()->RegisterError(wss.str());
					}
					BOOST_FOREACH(std::wstring field, fields)
					{
						std::wstring type = env.GetStructFieldType(this->type->GetName(), field);
						TypeNode* initType = (*itr)->TypeOf(&env);
						if (TypeNode::GetTypeNode(type, env)->Compare(initType) != 0)
						{
							std::wstringstream wss;
							wss << L"Incorrect value in initializer parameter for struct. Expected Type was ";
							wss << this->type->To_String();
							wss << L", while actual type was " << initType->To_String();
							ErrorHandler::GetInstance()->RegisterError(wss.str());
						}
					}
					env.AddVariable(this->name, this->type->To_String());
				}
				return env;
			}

			SymbolTable BlockNode::FullTypeCheck(SymbolTable env)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 2)
				{
					wprintf(L"Typechecking BlockNode\n");
				}
				env.EnterScope();
				BOOST_FOREACH(StmtNode* stmt, this->body)
				{
					env = stmt->FullTypeCheck(env);
				}
				env.ExitScope();
				return env;
			}

			SymbolTable ReturnNode::FullTypeCheck(SymbolTable env)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 2)
				{
					wprintf(L"Typechecking ReturnNode\n");
				}
				std::wstring currFunc = env.GetCurrFunc();
				std::wstring currReturnType = env.GetReturnType(currFunc);
				TypeNode* rhsType = this->rhs->TypeOf(&env);
				if (currReturnType.compare(L"void") == 0)
				{
					ErrorHandler::GetInstance()->RegisterError(L"Void functions are not allowed to return anything!");
				}
				else if (TypeNode::GetTypeNode(currReturnType, env)->Compare(rhsType) != 0)
				{
					ErrorHandler::GetInstance()->RegisterError(L"Return statement type does not match return type of function.");
				}
				env.FoundReturn();
				return env;
			}

			SymbolTable IfNode::FullTypeCheck(SymbolTable env)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 2)
				{
					wprintf(L"Typechecking IfNode\n");
				}
				TypeNode* condType = this->testcase->TypeOf(&env);
				PrimitiveTypeNode* boolType = new PrimitiveTypeNode(L"boolean");
				if (boolType->Compare(condType) != 0) 
				{
					ErrorHandler::GetInstance()->RegisterError(L"Test case for if statement must return a boolean or integer value.");
				}
				env.EnterScope();
				env = this->thenstmt->FullTypeCheck(env);
				env.ExitScope();
				if (this->elsestmt)
				{
					env.EnterScope();
					env = this->elsestmt->FullTypeCheck(env);
					env.ExitScope();
				}
				return env;
			}

			SymbolTable SwitchNode::FullTypeCheck(SymbolTable env)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 2)
				{
					wprintf(L"Typechecking SwitchNode\n");
				}
				TypeNode* caseType = this->testcase->TypeOf(&env);
				int caseNum = 1;
				BOOST_FOREACH(ExprNode* expr, this->cases)
				{
					if (caseType->Compare(expr->TypeOf(&env)) != 0)
					{
						std::wstringstream err;
						err << L"Type of case #";
						err << caseNum;
						err << L" does not match the case statement.";
						ErrorHandler::GetInstance()->RegisterError(err.str());
					}
				}
				BOOST_FOREACH(StmtNode* stmt, this->thenstmts)
				{
					env = stmt->FullTypeCheck(env);
				}
				if (this->defaultCase)
				{
					env = this->defaultCase->FullTypeCheck(env);
				}
				return env;
			}

			SymbolTable WhileNode::FullTypeCheck(SymbolTable env) {
				if(ErrorHandler::GetInstance()->GetDebugCode() == 2)
				{
					wprintf(L"Typechecking WhileNode\n");
				}
				TypeNode* condType = this->testcase->TypeOf(&env);
				PrimitiveTypeNode* boolType = new PrimitiveTypeNode(L"boolean");
				if (boolType->Compare(condType) != 0) 
				{
					ErrorHandler::GetInstance()->RegisterError(L"Test case for if statement must return a boolean value.");
				}
				env.EnterScope();
				env = this->body->FullTypeCheck(env);
				env.ExitScope();
				return env;     
			}
			
			TypeNode* AssignNode::TypeOf(SymbolTable* env)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 2)
				{
					wprintf(L"Typechecking AssignNode\n");
				}
				TypeNode* rhsType = rhs->TypeOf(env);
				TypeNode* lhsType = lhs->TypeOf(env);
				if (lhsType->Compare(rhsType) != 0)
				{
					std::wstringstream wss;
					wss << L"Type of right hand side of " << rhsType->To_String();
					wss << L" does not match declared type of " << lhsType->To_String() << L".";
					ErrorHandler::GetInstance()->RegisterError(wss.str());
				}
				return lhsType;      
			}

			TypeNode* BinaryNode::TypeOf(SymbolTable* env)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode()==2)
				{
					wprintf(L"Typechecking BinaryNode Operation: %s \n", this->operation.c_str());
				}
				TypeNode* returnType;
				TypeNode* lhsType = this->lhs->TypeOf(env);
				TypeNode* rhsType = this->rhs->TypeOf(env);
				if (this->operation.compare(L"+") == 0 || this->operation.compare(L"-") == 0)
				{
					// Addition and subtraction is allowed for pointers, ints and chars.
					std::wstring lhstypestr = lhsType->To_String();
					std::wstring rhstypestr = rhsType->To_String();
					/* Allow addition and subtraction for all types to all other types? (Only difference from above is booleans)
					if (lhstypestr[lhstypestr.size() - 1] != '*' && lhsType->Compare(std::wstring(L"int")) != 0) 
					{
						ErrorHandler::GetInstance()->RegisterError(L"Left hand side of binary operation is not a valid type.");
					}
					if (rhstypestr[rhstypestr.size() - 1] != '*' && rhsType->Compare(std::wstring(L"int")) != 0) 
					{
						ErrorHandler::GetInstance()->RegisterError(L"Right hand side of binary operation is not a valid type.");
					}*/
					
					if (lhsType->Equals(new PrimitiveTypeNode(L"int")) && rhsType->Equals(new PrimitiveTypeNode(L"int")))
					{
						returnType = new PrimitiveTypeNode(L"int");
					}
					else if (lhstypestr[lhstypestr.size() - 1] == '*' && rhstypestr[rhstypestr.size() - 1] == '*') 
					{
						if (!lhsType->Equals(rhsType))
						{
							std::wstringstream wss;
							wss << L"ERROR - Pointer types must match in order to apply arithmetic operations to it!";
							ErrorHandler::GetInstance()->RegisterError(wss.str());
						}
						returnType = new PrimitiveTypeNode(L"int");
					}
					else if (lhstypestr[lhstypestr.size() - 1] == '*')
					{
						returnType = lhsType;
					}
					else if (rhstypestr[rhstypestr.size() - 1] == '*')
					{
						returnType = rhsType;
					}
					else if (lhsType->Equals(new PrimitiveTypeNode(L"char")) || rhsType->Equals(new PrimitiveTypeNode(L"char")))
					{
						returnType = new PrimitiveTypeNode(L"char");
					}
					else if (lhsType->Equals(rhsType))
					{
						returnType = rhsType;
					}
					else
					{
						returnType = new PrimitiveTypeNode(L"int");
					}
				}
				else if (this->operation.compare(L"&") == 0 || this->operation.compare(L"|") == 0 || this->operation.compare(L"<<") == 0 || this->operation.compare(L">>") == 0) 
				{
					//Advanced arithmetic manipulation only allowed for non-pointer types.
					PrimitiveTypeNode* intType = new PrimitiveTypeNode(L"int");
					if (intType->Compare(lhsType) != 0)
					{
						ErrorHandler::GetInstance()->RegisterError(L"Left hand side of binary operation is a pointer, which is invalid for this operation.");
					}
					if (intType->Compare(rhsType) != 0)
					{
						ErrorHandler::GetInstance()->RegisterError(L"Right hand side of binary operation is a pointer, which is invalid for this operation.");
					}
					returnType = new PrimitiveTypeNode(L"int");
				}
				else if (this->operation.compare(L"==") == 0 || this->operation.compare(L"!=") == 0 || this->operation.compare(L">") == 0 || this->operation.compare(L">=") == 0 || this->operation.compare(L"<") == 0 || this->operation.compare(L"<=") == 0)
				{
					// No Type Checks since any two things can be equal to each other, as long as they are compared correctly.
					returnType = new PrimitiveTypeNode(L"boolean");
				}
				else if (this->operation.compare(L"&&") == 0 || this->operation.compare(L"||") == 0)
				{
					PrimitiveTypeNode* boolType = new PrimitiveTypeNode(L"boolean");
					if (boolType->Compare(lhsType) != 0)
					{
						ErrorHandler::GetInstance()->RegisterError(L"Left hand side of binary operation is not a boolean, which is invalid for this operation.");
					}
					if (boolType->Compare(rhsType) != 0)
					{
						ErrorHandler::GetInstance()->RegisterError(L"Right hand side of binary operation is not a boolean, which is invalid for this operation.");
					}
					returnType = new PrimitiveTypeNode(L"boolean");
				}
				return returnType;
			}

			TypeNode* KeywordNode::TypeOf(SymbolTable* env)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode()==2)
				{
					wprintf(L"Typechecking KeywordNode Word: %s \n", this->word.c_str());
				}
				if (this->word.compare(L"true") == 0 || this->word.compare(L"false") == 0) 
				{
					return new PrimitiveTypeNode(L"boolean");
				}
				ErrorHandler::GetInstance()->RegisterError(L"Unregistered keyword has been found.");
				return new PrimitiveTypeNode(L"");
			}

			TypeNode* VarNode::TypeOf(SymbolTable* env)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode()==2)
				{
					wprintf(L"Typechecking VarNode Name: %s \n", this->name.c_str());
				}
				std::wstring type = env->GetVarType(this->name);
				return new PrimitiveTypeNode(type);
			}

			TypeNode* IntNode::TypeOf(SymbolTable* env)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode()==2)
				{
					wprintf(L"Typechecking IntNode Value: %d\n", this->val);
				}
				//Check for 0, since apparently 0 can be assigned to any type...
				if (this->val == 0)
				{
					return new PrimitiveTypeNode(L"void");
				}
				return new PrimitiveTypeNode(L"int");
			}

			TypeNode* FuncCallNode::TypeOf(SymbolTable* env)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode()==2)
				{
					wprintf(L"Typechecking FuncCallNode FuncName: %s \n", this->funcname.c_str());
				}
				this->returnType = env->GetReturnType(this->funcname);
				std::list<std::wstring> params = env->GetParamTypes(this->funcname);
				env->AddFunctionUse(this->funcname);
				std::list<std::wstring>::iterator it1;
				std::list<ExprNode*>::iterator it2;
				int i = 1;
				for(it1 = params.begin(), it2 = this->params.begin(); it1 != params.end() && it2 != this->params.end(); it1++, it2++)
				{
					TypeNode* paramtype = (*it2)->TypeOf(env);
					if (paramtype->Compare(TypeNode::GetTypeNode(*it1, *env)) != 0)
					{
						std::wstringstream wss;
						wss << L"Improper parameter #";
						wss << i;
						wss << L" of call to ";
						wss << this->funcname;
						wss << L". Parameter should be of type ";
						wss << (*it1);
						wss << L" but input is of type ";
						wss << paramtype->To_String();
						wss << L".";
						ErrorHandler::GetInstance()->RegisterError(wss.str());
					}
					i++;
				}
				if (!(it1 == params.end() && it2 == this->params.end()) && !env->CheckVariableLengthFunction(this->funcname))
				{
					std::wstringstream wss;
					wss << L"Incorrect number of parameters passed to the function " << this->funcname << L".";
					ErrorHandler::GetInstance()->RegisterError(wss.str());
				}
				return new PrimitiveTypeNode(this->returnType);
			}

			TypeNode* UnaryNode::TypeOf(SymbolTable* env)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode()==2)
				{
					wprintf(L"Typechecking UnaryNode Operation: %s \n", this->operation.c_str());
				}
				PrimitiveTypeNode* returnType;
				if (this->operation.compare(L"-") == 0 || this->operation.compare(L"~") == 0 || this->operation.compare(L"+") == 0)
				{
					TypeNode* rhsType = this->rhs->TypeOf(env);
					PrimitiveTypeNode* intNode = new PrimitiveTypeNode(L"int");
					if (intNode->Compare(rhsType) != 0) 
					{
						ErrorHandler::GetInstance()->RegisterError(L"Right hand side of unary operation is a pointer, which cannot have these unary arithmetic operations applied to it.");
					}
					returnType = new PrimitiveTypeNode(L"int");
				} 
				else if (this->operation.compare(L"!") == 0)
				{
					TypeNode* rhsType = this->rhs->TypeOf(env);
					PrimitiveTypeNode* boolNode = new PrimitiveTypeNode(L"boolean");
					if (boolNode->Compare(rhsType) != 0 && rhsType->GetNumPointers() == 0) 
					{
						ErrorHandler::GetInstance()->RegisterError(L"Right hand side of unary operation is not a boolean or pointer type, which cannot have the ! operator applied to it.");
					}
					returnType = new PrimitiveTypeNode(L"boolean");
				}
				else if (this->operation.compare(L"&") == 0)
				{
					TypeNode* rhsType = this->rhs->TypeOf(env);
					returnType = new PrimitiveTypeNode(rhsType->GetName(), rhsType->GetNumPointers() + 1);
				}
				else if (this->operation.compare(L"*") == 0)
				{
					TypeNode* rhsType = this->rhs->TypeOf(env);
					if (rhsType->GetNumPointers() == 0) 
					{
						ErrorHandler::GetInstance()->RegisterError(L"Right hand side of unary operation is not a pointer, and cannot have the * operator applied to it.");
					}
					returnType = new PrimitiveTypeNode(rhsType->GetName(), rhsType->GetNumPointers() - 1);
				}
				return returnType;      
			}

			TypeNode* TernaryNode::TypeOf(SymbolTable* env)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode()==2)
				{
					wprintf(L"Typechecking TernaryNode\n");
				}
				TypeNode* condType = this->cond->TypeOf(env);
				PrimitiveTypeNode* boolNode = new PrimitiveTypeNode(L"boolean");
				if (boolNode->Compare(condType) != 0) 
				{
					ErrorHandler::GetInstance()->RegisterError(L"Condition Statement of Ternary Operator must return a boolean!");
				}
				TypeNode* thenType = this->thenstmt->TypeOf(env);
				TypeNode* elseType = this->elsestmt->TypeOf(env);
				if (thenType->Compare(elseType) != 0 && elseType->Compare(thenType) != 0)
				{
					ErrorHandler::GetInstance()->RegisterError(L"Return types of ternary cases are not compatible.");
				}
				return thenType;
			}

			TypeNode* StringNode::TypeOf(SymbolTable* env)
			{
				return new PrimitiveTypeNode(L"char", 1);
			}

			TypeNode* CharNode::TypeOf(SymbolTable* env)
			{
				return new PrimitiveTypeNode(L"char");
			}

			TypeNode* ArrayNode::TypeOf(SymbolTable* env)
			{
				TypeNode* lhsType = this->lhs->TypeOf(env);
				TypeNode* innerType = this->inner->TypeOf(env);
				PrimitiveTypeNode* intType = new PrimitiveTypeNode(L"int");
				if (intType->Compare(innerType) != 0)
				{
					ErrorHandler::GetInstance()->RegisterError(L"Array indexes must be an integer.");
				}
				if (lhsType->GetNumPointers() == 0)
				{
					ErrorHandler::GetInstance()->RegisterError(L"Cannot index into a variable of non-pointer type.");
				}
				return new PrimitiveTypeNode(lhsType->GetName(), lhsType->GetNumPointers() - 1);
			}
			
			TypeNode* AssemblyNode::TypeOf(SymbolTable* env)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 2) 
				{
					wprintf(L"Typechecking AssemblyNode Code:\n");
				}
				boost::unordered_map<std::wstring, std::wstring>::iterator it;
				for(it = this->invars.begin(); it != this->invars.end(); it++)
				{
					if (wcscmp(env->GetVarType(it->first).c_str(), L"ERROR") == 0)
					{
						ErrorHandler::GetInstance()->RegisterError(L"Invalid in variable entry for assembly code.");
					}
				}
				for(it = this->outvars.begin(); it != this->outvars.end(); it++)
				{
					if (wcscmp(env->GetVarType(it->first).c_str(), L"ERROR") == 0)
					{
						ErrorHandler::GetInstance()->RegisterError(L"Invalid out variable entry for assembly code.");
					}
				}
				return new PrimitiveTypeNode(L"void");
			}
			
			TypeNode* SizeOfNode::TypeOf(SymbolTable* env)
			{
				this->type = TypeNode::GetTypeNode(this->strType, *env);
				this->type->VerifyValidType(*env);
				std::wstringstream ss;
				ss << this->type->GetTypeSize(*env);
				this->size = ss.str();
				return new PrimitiveTypeNode(L"int");
			}
			
			TypeNode* StructReferenceNode::TypeOf(SymbolTable* env)
			{
				this->lhsType = this->lhs->TypeOf(env);
				if (lhsType->GetNumPointers() > 0)
				{
					std::wstringstream wss;
					wss << L"Type left of . must be of non-pointer type for field " << this->fieldName;
					ErrorHandler::GetInstance()->RegisterError(wss.str());
				}
				else if (env->IsPrimitiveTypeValid(lhsType->To_String()))
				{
					std::wstringstream wss;
					wss << L"Type left of . must be of some struct type for field " << this->fieldName;
					ErrorHandler::GetInstance()->RegisterError(wss.str());
				}
				return TypeNode::GetTypeNode(env->GetStructFieldType(lhsType->To_String(), this->fieldName), *env);
			}
		}
	}
}
