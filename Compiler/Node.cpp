#include "Node.h"
#include "stdafx.h"

namespace MiniC {
	namespace IR {
		namespace AST {

			////////////////////////////////////
			//	      Interfaces              //
			////////////////////////////////////

			/*
			*		Node Class: Provides an abstract interface for all AST nodes
			*/

			Node::Node() {}
			Node::Node(Node&) {}
			Node::~Node() {}

			/*
			*		TranslationUnitNode Class: Provides an abstract interface for all AST statement nodes
			*/

			TranslationUnitNode::TranslationUnitNode(TranslationUnitNode&) {}
			TranslationUnitNode::~TranslationUnitNode() {}

			/*
			*		StmtNode Class: Provides an abstract interface for all AST statement nodes
			*/

			StmtNode::StmtNode() {}
			StmtNode::StmtNode(StmtNode&) {}
			StmtNode::~StmtNode() {}

			/*
			*		ExprNode Class: Provides an abstract interface for all AST expression nodes
			*/

			ExprNode::ExprNode(){}
			ExprNode::ExprNode(ExprNode&){}
			ExprNode::~ExprNode(){}
			std::wstring ExprNode::ErrorReport()
			{
				return this->_error;
			}

			

			/*
			*		TypeNode Class: abstract class representing a type
			*		Contains:	name - string
			*/
			TypeNode::TypeNode() {}
			TypeNode::TypeNode(TypeNode&) {}
			TypeNode::~TypeNode() {}

			TypeNode* TypeNode::GetTypeNode(std::wstring name, SymbolTable env)
			{
				WCHAR* strippedname = (WCHAR*) calloc(sizeof(WCHAR), name.size() + 1);
				wcscpy_s(strippedname, name.size() + 1, name.c_str());
				int i = 0;
				int numPointers = 0;
				const WCHAR* namechar = name.c_str();
				while(namechar[i] != '\0')
				{
					if (namechar[i] == '*')
					{
						numPointers++;
						strippedname[i] = '\0';
					}
					i++;
				}
				strippedname[i] = '\0';
				if (env.IsPrimitiveTypeValid(name))
				{
					PrimitiveTypeNode* ptm = new PrimitiveTypeNode(strippedname, numPointers, NULL);
					return ptm;
				}
				else
				{
					StructTypeNode* stn = new StructTypeNode(strippedname, numPointers, NULL);
					return stn;
				}
			}

			/*
			*		PrimitiveTypeNode Class: represents the formal parameters of a method
			*		Contains:	name - string
			*/
			PrimitiveTypeNode::PrimitiveTypeNode(PrimitiveTypeNode& tn) 
			{
				this->name = tn.name;
				this->numPointers = tn.GetNumPointers();
				this->arrayDim = tn.arrayDim;
			}

			PrimitiveTypeNode::PrimitiveTypeNode(std::wstring name) 
			{
				WCHAR* strippedname = (WCHAR*) calloc(sizeof(WCHAR), name.size() + 1);
				wcscpy_s(strippedname, name.size() + 1, name.c_str());
				int i = 0;
				int numPointers = 0;
				const WCHAR* namechar = name.c_str();
				while(namechar[i] != '\0')
				{
					if (namechar[i] == '*')
					{
						numPointers++;
						strippedname[i] = '\0';
					}
					i++;
				}
				strippedname[i] = '\0';
				this->name = strippedname;
				this->numPointers = numPointers;
				this->arrayDim = NULL;
			}

			PrimitiveTypeNode::PrimitiveTypeNode(std::wstring name, int numpointers)
			{
				this->name = name;
				this->numPointers = numpointers;
				this->arrayDim = NULL;
			}

			PrimitiveTypeNode::PrimitiveTypeNode(std::wstring name, int numpointers, Node* arrayDim)
			{
				this->name = name;
				this->numPointers = numpointers;
				this->arrayDim = arrayDim;
			}

			PrimitiveTypeNode::~PrimitiveTypeNode()
			{
				this->name = L"";
				if (this->arrayDim)
				{
					delete this->arrayDim;
				}
				this->arrayDim = NULL;
			}

			std::wstring PrimitiveTypeNode::GetName()
			{
				return this->name;
			}

			int PrimitiveTypeNode::GetNumPointers()
			{
				return this->numPointers;
			}

			void PrimitiveTypeNode::SetNumPointers(int numPointers)
			{
				this->numPointers = numPointers;
			}
			
			void PrimitiveTypeNode::SetArrayDim(Node* arrayDim)
			{
				this->arrayDim = arrayDim;
			}
			
			Node* PrimitiveTypeNode::GetArrayDim()
			{
				return this->arrayDim;
			}

			std::wstring PrimitiveTypeNode::To_String()
			{
				std::wstringstream ss;
				ss << this->name;
				for(int i = 0; i < this->numPointers; i++)
				{
					ss << L"*";
				}
				return ss.str();
			}
			
			//Checks that this is compatible with Type check.
			int PrimitiveTypeNode::Compare(TypeNode* check)
			{
				//Void can be used with any other type.
				if (check->Equals(new PrimitiveTypeNode(L"void")))// || this->Equals(new PrimitiveTypeNode(L"void")))
				{
					return 0;
				}
				//Void* can be used with any pointer type
				else if (this->Equals(new PrimitiveTypeNode(L"void", 1)) && check->GetNumPointers() > 0)
				{
					return 0;
				}
				else if (check->Equals(new PrimitiveTypeNode(L"void", 1)) && this->numPointers > 0)
				{
					return 0;
				}
				//int can be used with any non-pointer type
				else if (this->Equals(new PrimitiveTypeNode(L"int")) && SymbolTable::IsPrimitiveTypeValid(check->To_String()) && !check->Equals(new PrimitiveTypeNode(L"boolean")))
				{
					return 0;
				}
				/*else if (check->Equals(new PrimitiveTypeNode(L"int")) && SymbolTable::IsPrimitiveTypeValid(this->To_String()))
				{
					return 0;
				}*/
				else
				{
					return this->To_String().compare(check->To_String());
				}
			}

			bool PrimitiveTypeNode::CheckArrayDim(SymbolTable env)
			{
				if (this->arrayDim)
				{
					TypeNode* arrayDimType = ((ExprNode*) this->arrayDim)->TypeOf(&env);
					return (arrayDimType->Compare(new PrimitiveTypeNode(L"int")) == 0);
				}
				return true;
			}

			//Checks that PrimitiveTypeNode instances are exactly the same.
			bool PrimitiveTypeNode::Equals(Node* n)
			{
				PrimitiveTypeNode* tn;
				try
				{
					tn = dynamic_cast<PrimitiveTypeNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				if (tn)
				{
					if (tn->arrayDim && this->arrayDim)
					{
						return this->arrayDim->Equals(tn->arrayDim) && this->name.compare(tn->name) == 0 && this->numPointers == tn->GetNumPointers();
					}
					else if (!tn->arrayDim && !this->arrayDim)
					{
						return this->name.compare(tn->name) == 0 && this->numPointers == tn->GetNumPointers();
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}

			Node* PrimitiveTypeNode::GetDefaultValue(SymbolTable env)
			{
				if (this->name.compare(L"char") == 0 && this->numPointers == 0)
				{
					return new IntNode('\0');
				}
				else if (this->name.compare(L"boolean") == 0 && this->numPointers == 0)
				{
					return new KeywordNode(L"false");
				}
				else
				{
					return new IntNode(0);
				}
			}
			
			/*
			*		StructTypeNode Class: represents a struct type
			*		Contains:	name - string
			*/
			StructTypeNode::StructTypeNode(StructTypeNode& tn) 
			{
				this->name = tn.name;
				this->numPointers = tn.GetNumPointers();
				this->arrayDim = tn.arrayDim;
			}

			StructTypeNode::StructTypeNode(std::wstring name) 
			{
				WCHAR* strippedname = (WCHAR*) calloc(sizeof(WCHAR), name.size() + 1);
				wcscpy_s(strippedname, name.size() + 1, name.c_str());
				int i = 0;
				int numPointers = 0;
				const WCHAR* namechar = name.c_str();
				while(namechar[i] != '\0')
				{
					if (namechar[i] == '*')
					{
						numPointers++;
						strippedname[i] = '\0';
					}
					i++;
				}
				strippedname[i] = '\0';
				this->name = strippedname;
				this->numPointers = numPointers;
				this->arrayDim = NULL;
			}

			StructTypeNode::StructTypeNode(std::wstring name, int numpointers)
			{
				this->name = name;
				this->numPointers = numpointers;
				this->arrayDim = NULL;
			}

			StructTypeNode::StructTypeNode(std::wstring name, int numpointers, Node* arrayDim)
			{
				this->name = name;
				this->numPointers = numpointers;
				this->arrayDim = arrayDim;
			}

			StructTypeNode::~StructTypeNode()
			{
				this->name = L"";
				if (this->arrayDim)
				{
					delete this->arrayDim;
				}
				this->arrayDim = NULL;
			}

			std::wstring StructTypeNode::GetName()
			{
				return this->name;
			}

			int StructTypeNode::GetNumPointers()
			{
				return this->numPointers;
			}

			void StructTypeNode::SetNumPointers(int numPointers)
			{
				this->numPointers = numPointers;
			}
			
			void StructTypeNode::SetArrayDim(Node* arrayDim)
			{
				this->arrayDim = arrayDim;
			}
			
			Node* StructTypeNode::GetArrayDim()
			{
				return this->arrayDim;
			}

			std::wstring StructTypeNode::To_String()
			{
				std::wstringstream ss;
				ss << this->name;
				for(int i = 0; i < this->numPointers; i++)
				{
					ss << L"*";
				}
				return ss.str();
			}
			
			//Checks that this is compatible with Type check.
			int StructTypeNode::Compare(TypeNode* check)
			{
				//Void can be used with any other type.
				if (check->Equals(new PrimitiveTypeNode(L"void")) || this->Equals(new PrimitiveTypeNode(L"void")))
				{
					return 0;
				}
				//Void* can be used with any pointer type
				else if (this->Equals(new PrimitiveTypeNode(L"void", 1)) && check->GetNumPointers() > 0)
				{
					return 0;
				}
				else if (check->Equals(new PrimitiveTypeNode(L"void", 1)) && this->numPointers > 0)
				{
					return 0;
				}
				//int can be used with any non-pointer type
				else if (this->Equals(new PrimitiveTypeNode(L"int")) && check->GetNumPointers() == 0)
				{
					return 0;
				}
				else if (check->Equals(new PrimitiveTypeNode(L"int")) && this->numPointers == 0)
				{
					return 0;
				}
				else
				{
					return this->To_String().compare(check->To_String());
				}
			}

			bool StructTypeNode::CheckArrayDim(SymbolTable env)
			{
				if (this->arrayDim)
				{
					TypeNode* arrayDimType = ((ExprNode*) this->arrayDim)->TypeOf(&env);
					return (arrayDimType->Compare(new PrimitiveTypeNode(L"int")) == 0);
				}
				return true;
			}

			//Checks that PrimitiveTypeNode instances are exactly the same.
			bool StructTypeNode::Equals(Node* n)
			{
				StructTypeNode* tn;
				try
				{
					tn = dynamic_cast<StructTypeNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				if (tn)
				{
					if (tn->arrayDim && this->arrayDim)
					{
						return this->arrayDim->Equals(tn->arrayDim) && this->name.compare(tn->name) == 0 && this->numPointers == tn->GetNumPointers();
					}
					else if (!tn->arrayDim && !this->arrayDim)
					{
						return this->name.compare(tn->name) == 0 && this->numPointers == tn->GetNumPointers();
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}

			Node* StructTypeNode::GetDefaultValue(SymbolTable env)
			{
				return NULL;
			}

			/*
			*		FormalNode Class: represents the formal parameters of a method
			*		Contains:	name - string
			*				type - string
			*/

			FormalNode::FormalNode(FormalNode& fn) {
				this->name = fn.name;
				this->type = fn.type;
				this->allocSize = fn.allocSize;
			}

			FormalNode::FormalNode(std::wstring name, TypeNode* type) {
				this->name = name;
				this->type = type;
			}

			FormalNode::~FormalNode() {
				this->name = L"";
				if (this->type) {
					delete this->type;
				}
				this->type = NULL;
			}

			std::wstring FormalNode::To_String() {
				std::wstringstream returnable;
				returnable << L"Visiting Formal Node for ";
				returnable << this->name;
				returnable << L" of type ";
				returnable << this->type->To_String();
				returnable << L"\n";
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool FormalNode::Equals(Node* n)
			{
				FormalNode* f;
				try
				{
					f = dynamic_cast<FormalNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				if (!f)
				{
					return false;
				}
				if (this->name.compare(f->name) != 0)
				{
					return false;
				}
				else if (!this->type->Equals(f->type))
				{
					return false;
				}
				else
				{
					return true;
				}
			}

			/*
			*		FuncNode Class: represents a function declaration and implementation
			*		Contains:	name		- string
			*				type		- string
			*				parameters	- list of formals
			*				body		- list of statements
			*				return_expr - expression
			*/

			FuncNode::FuncNode(FuncNode& fn)
			{
				this->name = fn.name;
				this->type = fn.type;
				this->parameters = fn.parameters;
				this->body = fn.body;
				this->isMain = fn.isMain;
				this->isVoid = fn.isVoid;
				this->isDecl = false;
				this->isInterruptHandler = fn.isInterruptHandler;
			}

			FuncNode::~FuncNode()
			{
				this->name = L"";
				if (this->type) {
					delete this->type;
				}
				this->type = NULL;
				BOOST_FOREACH(FormalNode* param, this->parameters) {
					if (param) {
						delete param;
					}
					param = NULL;
				}
				this->parameters.clear();
				BOOST_FOREACH(StmtNode* stmt, this->body) {
					if (stmt) {
						delete stmt;
					}
					stmt = NULL;
				}
				this->body.clear();
			}

			FuncNode::FuncNode(std::wstring name, TypeNode* type, std::list<FormalNode*> parameters, bool isInterruptHandler, bool isVariableLength, std::list<StmtNode*> body)
			{
				this->name = name;
				this->type = type;
				this->parameters = parameters;
				this->body = body;
				this->isMain = false;
				this->isVoid = false;
				this->isDecl = false;
				this->isInterruptHandler = isInterruptHandler;
				this->isVariableLength = isVariableLength;
				if (this->name.compare(L"main") == 0 && this->type->Equals(new PrimitiveTypeNode(L"int"))) 
				{
					this->isMain = true;
				}
				if (this->type->Equals(new PrimitiveTypeNode(L"void"))) 
				{
					this->isVoid = true;
				}
			}

			std::wstring FuncNode::To_String()
			{
				std::wstringstream returnable;
				returnable << L"Entering Function Node for ";
				returnable << this->name;
				returnable << L" with return type ";
				returnable << this->type->To_String();
				returnable << L"\nParameters: \n";
				std::list<FormalNode*>::iterator it;
				for(it = this->parameters.begin(); it != this->parameters.end(); it++)
				{
					returnable << (**it).To_String();
				}
				returnable << L"Body: \n";
				std::list<StmtNode*>::iterator it2;
				for(it2 = this->body.begin(); it2 != this->body.end(); it2++)
				{
					returnable << (**it2).To_String();
				}
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool FuncNode::Equals(Node* n)
			{
				FuncNode* fn;
				try
				{
					fn = dynamic_cast<FuncNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				if (!fn)
				{
					return false;
				}
				if (this->name.compare(fn->name) != 0)
				{
					return false;
				}
				else if (!this->type->Equals(fn->type))
				{
					return false;
				}
				else if (this->isMain != fn->isMain)
				{
					return false;
				}
				else if (this->isVoid != fn->isVoid)
				{
					return false;
				}
				else
				{
					std::list<FormalNode*> paramcopy = std::list<FormalNode*>();
					BOOST_FOREACH(FormalNode* f, this->parameters)
					{
						paramcopy.push_back(f);
					}
					int size = fn->parameters.size();
					BOOST_FOREACH(FormalNode* f, fn->parameters)
					{
						paramcopy.remove(f);
						if (size - 1 != paramcopy.size())
						{
							return false;
						}
						size--;
					}
					if (paramcopy.size() != 0)
					{
						return false;
					}
					else
					{
						std::list<StmtNode*> bodycopy = std::list<StmtNode*>();
						BOOST_FOREACH(StmtNode* s, this->body)
						{
							bodycopy.push_back(s);
						}
						int size = fn->body.size();
						BOOST_FOREACH(StmtNode* s, fn->body)
						{
							bodycopy.remove(s);
							if (size - 1 != bodycopy.size())
							{
								return false;
							}
							size--;
						}
						return (bodycopy.size() == 0);
					}
				}
			}


			/*
			*		FuncDeclNode Class: represents a function declaration
			*		Contains:	name		- string
			*				type		- TypeNode
			*				parameters	- list of formals
			*/

			FuncDeclNode::FuncDeclNode(FuncDeclNode& fn)
			{
				this->isDecl = false;
				this->name = fn.name;
				this->parameters = fn.parameters;
				this->type = fn.type;
				this->isMain = false;
				this->isInterruptHandler = false;
			}

			FuncDeclNode::FuncDeclNode(std::wstring name, TypeNode* type, std::list<FormalNode*> parameters, bool isVariableLength)
			{
				this->isDecl = false;
				this->name = name;
				this->type = type;
				this->parameters = parameters;
				this->isMain = false;
				this->isVariableLength = isVariableLength;
				this->isInterruptHandler = false;
			}

			FuncDeclNode::~FuncDeclNode()
			{
				this->name = L"";
				if (this->type)
				{
					delete this->type;
				}
				this->type = NULL;
				BOOST_FOREACH(FormalNode* param, this->parameters)
				{
					if (param)
					{
						delete param;
					}
					param = NULL;
				}
				this->parameters.clear();
			}

			std::wstring FuncDeclNode::To_String()
			{
				std::wstringstream returnable;
				returnable << L"Entering Function Declaration Node for ";
				returnable << this->name;
				returnable << L" with return type ";
				returnable << this->type->To_String();
				returnable << L"\nParameters: \n";
				std::list<FormalNode*>::iterator it;
				for(it = this->parameters.begin(); it != this->parameters.end(); it++)
				{
					returnable << (**it).To_String();
				}
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool FuncDeclNode::Equals(Node* n)
			{
				FuncDeclNode* fdn;
				try
				{
					fdn = dynamic_cast<FuncDeclNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				if (!fdn)
				{
					return false;
				}
				if (this->name.compare(fdn->name) != 0)
				{
					return false;
				}
				else if (!this->type->Equals(fdn->type))
				{
					return false;
				}
				else if (this->isMain != fdn->isMain)
				{
					return false;
				}
				else
				{
					std::list<FormalNode*> paramcopy = std::list<FormalNode*>();
					BOOST_FOREACH(FormalNode* f, this->parameters)
					{
						paramcopy.push_back(f);
					}
					int size = fdn->parameters.size();
					BOOST_FOREACH(FormalNode* f, fdn->parameters)
					{
						paramcopy.remove(f);
						if (size - 1 != paramcopy.size())
						{
							return false;
						}
						size--;
					}
					return (paramcopy.size() == 0);
				}
			}

			/*
			*		GlobalDeclAssignNode Class: represents a declaration & assignment node at the global scope
			*		Contains:	type - Type
			*					name - string
			*					rhs  - expression
			*/

			GlobalDeclAssignNode::GlobalDeclAssignNode(GlobalDeclAssignNode& dan)
			{
				this->type = dan.type;
				this->name = dan.name;
				this->rhs = dan.rhs;
				this->isMain = false;
				this->defaultVal = dan.defaultVal;
				this->isDecl = true;
				this->isInterruptHandler = false;
			}

			GlobalDeclAssignNode::GlobalDeclAssignNode(TypeNode* type, std::wstring name, ExprNode* rhs)
			{
				this->isDecl = true;
				this->name = name;
				this->type = type;
				if (!rhs)
				{
					this->defaultVal = true;
				}
				else
				{
					this->rhs = rhs;
					this->defaultVal = false;
				}
				this->isMain = false;
				this->isInterruptHandler = false;
			}

			GlobalDeclAssignNode::~GlobalDeclAssignNode()
			{
				if (this->type)
				{
					delete this->type;
				}
				this->type = NULL;
				this->name = L"";
				if (this->rhs)
				{
					delete this->rhs;
				}
				this->rhs = NULL;
			}

			std::wstring GlobalDeclAssignNode::To_String()
			{
				std::wstringstream returnable;
				returnable << L"GlobalDeclAssignNode: Name = ";
				returnable << this->name;
				returnable << L" Type = ";
				returnable << this->type->To_String();
				returnable << L".\n";
				returnable << this->rhs->To_String();
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool GlobalDeclAssignNode::Equals(Node* n)
			{
				GlobalDeclAssignNode* dan;
				try
				{
					dan= dynamic_cast<GlobalDeclAssignNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				if (!dan)
				{
					return false;
				}
				if (this->defaultVal != dan->defaultVal)
				{
					return false;
				}
				else if (this->name.compare(dan->name) != 0)
				{
					return false;
				}
				else if (!this->type->Equals(dan->type))
				{
					return false;
				}
				else if (this->rhs == NULL && dan->rhs == NULL)
				{
					return true;
				}
				else
				{
					return this->rhs->Equals(dan->rhs);
				}
			}
			

			/*
			*		StructInitNode Class: represents a declaration & assignment node
			*		Contains:	type - Type
			*					name - string
			*/
			GlobalStructInitNode::GlobalStructInitNode(GlobalStructInitNode& sdan)
			{
				this->isDecl = true;
				this->defaultVal = sdan.defaultVal;
				this->inits = sdan.inits;
				this->name = sdan.name;
				this->type = sdan.type;
				this->isInterruptHandler = false;
			}

			GlobalStructInitNode::GlobalStructInitNode(TypeNode* type, std::wstring name, std::list<ExprNode*> inits)
			{
				this->isDecl = true;
				this->type = type;
				this->name = name;
				if (inits.size() == 0)
				{
					this->defaultVal = true;
				}
				else
				{
					this->inits = inits;
					this->defaultVal = false;
				}
				this->isInterruptHandler = false;
			}
			
			GlobalStructInitNode::~GlobalStructInitNode()
			{
				BOOST_FOREACH(ExprNode* init, this->inits)
				{
					if (init)
					{
						delete init;
					}
					init = NULL;
				}
			}

			std::wstring GlobalStructInitNode::To_String()
			{
				std::wstringstream returnable;
				returnable << L"StructInitNode: Name = ";
				returnable << this->name;
				returnable << L" Type = ";
				returnable << this->type->To_String();
				returnable << L".\n";
				returnable << L"Inits: ";
				BOOST_FOREACH(ExprNode* init, inits)
				{
					returnable << init->To_String();
					returnable << L"\n";
				}
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}
			
			bool GlobalStructInitNode::Equals(Node* n)
			{
				GlobalStructInitNode* sdan;
				try
				{
					sdan = dynamic_cast<GlobalStructInitNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				if (!sdan)
				{
					return false;
				}
				if (this->name.compare(sdan->name) != 0)
				{
					return false;
				}
				if ((!this->defaultVal && sdan->defaultVal) || (this->defaultVal && !sdan->defaultVal))
				{
					return false;
				}
				if (!(this->type->Equals(sdan->type)))
				{
					return false;
				}
				std::list<ExprNode*>::iterator itr, itr2;
				for(itr = this->inits.begin(), itr2 = sdan->inits.begin(); itr != this->inits.end() && itr2 != sdan->inits.begin(); itr++, itr2++)
				{
					if (!((*itr)->Equals((*itr2))))
					{
						return false;
					}
				}
				return (itr == this->inits.end() && itr2 == sdan->inits.end());
			}

			/*
			*		StructDeclNode Class: represents the declaration of a struct
			*/
			StructDeclNode::StructDeclNode(StructDeclNode& sdn)
			{
				this->isDecl = true;
				this->names = sdn.names;
				this->isMain = false;
				this->types = sdn.types;
				this->struct_name = sdn.struct_name;
				this->init_name = sdn.init_name;
				this->isInterruptHandler = false;
			}

			StructDeclNode::StructDeclNode(std::wstring name, std::wstring init_name, std::list<TypeNode*> types, std::list<std::wstring> varnames)
			{
				this->isDecl = true;
				this->names = varnames;
				this->isMain = false;
				this->types = types;
				this->struct_name = name;
				this->init_name = init_name;
				this->isInterruptHandler = false;
			}
			
			StructDeclNode::~StructDeclNode()
			{
				BOOST_FOREACH(TypeNode* type, this->types)
				{
					if (type)
					{
						delete type;
					}
				}
				this->types.clear();
			}

			std::wstring StructDeclNode::To_String()
			{
				std::wstringstream returnable;
				returnable << L"StructDeclNode: Name = ";
				returnable << this->struct_name;
				if (this->init_name.compare(L"") != 0)
				{
					returnable << L"\nInitialized Name = ";
					returnable << this->init_name;
				}
				returnable << L" Fields: ";
				std::list<std::wstring>::iterator itr;
				std::list<TypeNode*>::iterator itr2;
				for(itr = this->names.begin(), itr2 = this->types.begin(); itr != this->names.end() && itr2 != this->types.end(); itr++, itr2++)
				{
					returnable << (*itr) << L" -- " << (*itr2)->To_String() << L"\n";
				}
				std::wstring returnableChar = returnable.str();
				return returnableChar;

			}
			
			bool StructDeclNode::Equals(Node* n)
			{
				StructDeclNode* sdn;
				try
				{
					sdn = dynamic_cast<StructDeclNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				if (!sdn)
				{
					return false;
				}
				if (sdn->struct_name.compare(this->struct_name) != 0 || sdn->init_name.compare(this->init_name) != 0)
				{
					return false;
				}
				std::list<TypeNode*> typescopy = std::list<TypeNode*>();
				BOOST_FOREACH(TypeNode* type, this->types)
				{
					typescopy.push_back(type);
				}
				int size = sdn->types.size();
				BOOST_FOREACH(TypeNode* s, sdn->types)
				{
					typescopy.remove(s);
					if (size - 1 != typescopy.size())
					{
						return false;
					}
					size--;
				}
				if (size != 0)
				{
					return false;
				}
				std::list<std::wstring> namescopy = std::list<std::wstring>();
				BOOST_FOREACH(std::wstring name, this->names)
				{
					namescopy.push_back(name);
				}
				size = sdn->names.size();
				BOOST_FOREACH(std::wstring s, sdn->names)
				{
					namescopy.remove(s);
					if (size - 1 != namescopy.size())
					{
						return false;
					}
					size--;
				}
				return (size == 0);
			}

			/*
			*		ProgramNode Class: represents a program in the minijava AST
			*		Contains:	mainFunc	- main function declaration
			*			        otherClasses	- all other class declarations
			*/

			ProgramNode::ProgramNode(ProgramNode& pn)
			{
				this->funcs = pn.funcs;
			}

			ProgramNode::ProgramNode(std::list<TranslationUnitNode*> others)
			{
				this->funcs = others;
			}

			ProgramNode::~ProgramNode()
			{
				//delete otherfuncs
				BOOST_FOREACH( TranslationUnitNode* unit, this->funcs)
				{
					if(unit)
					{
						delete unit;
					}
					unit=NULL;
				}
				this->funcs.clear();      
			}

			std::wstring ProgramNode::To_String()
			{
				std::wstringstream returnable;
				returnable << L"Entering Program Node\n";
				BOOST_FOREACH(TranslationUnitNode* unit, this->funcs)
				{
					returnable << L"Unit: \n";
					returnable << unit->To_String();
				}
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool ProgramNode::Equals(Node* n)
			{
				ProgramNode* pn;
				try
				{
					pn = dynamic_cast<ProgramNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				if (!pn)
				{
					return false;
				}
				std::list<TranslationUnitNode*> funcscopy = std::list<TranslationUnitNode*>();
				BOOST_FOREACH(TranslationUnitNode* unit, this->funcs)
				{
					funcscopy.push_back(unit);
				}
				int size = pn->funcs.size();
				BOOST_FOREACH(TranslationUnitNode* unit, pn->funcs)
				{
					funcscopy.remove(unit);
					if (size - 1 != funcscopy.size())
					{
						return false;
					}
					size--;
				}
				return (size == 0);
			}


			//////////////////////////////////////
			//	       Statement Classes     	//
			//	     * Execution Statements	//
			//////////////////////////////////////
		}
	}
}
