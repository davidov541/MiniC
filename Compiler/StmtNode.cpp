#include "Node.h"
#include "stdafx.h"

namespace MiniC
{
	namespace IR
	{
		namespace AST
		{
			/*
			*		ExpressionStmt Class: represents an expression acting as a statement.
			*		Contains:	expr - Expression
			*/

			ExpressionStmt::ExpressionStmt(ExpressionStmt& es)
			{
				this->expr = es.expr;
			}

			ExpressionStmt::ExpressionStmt(ExprNode* expr)
			{
				this->expr = expr;
			}

			ExpressionStmt::~ExpressionStmt()
			{
				if (this->expr)
				{
					delete this->expr;
				}
				this->expr = NULL;
			}

			std::wstring ExpressionStmt::To_String()
			{
				std::wstringstream returnable;
				returnable << L"ExpressionStmt: Expression = ";
				returnable << this->expr->To_String();
				returnable << L".\n";
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool ExpressionStmt::Equals(Node* n)
			{
				ExpressionStmt* es;
				try
				{
					es = dynamic_cast<ExpressionStmt*>(n);
				}
				catch(...)
				{
					return false;
				}
				return (es && es->expr->Equals(this->expr));
			}

			/*
			*		DeclAssignNode Class: represents a declaration & assignment node
			*		Contains:	type - string
			*					name - string
			*					rhs  - expression
			*/

			DeclAssignNode::DeclAssignNode(DeclAssignNode& dan)
			{
				this->type = dan.type;
				this->name = dan.name;
				this->rhs = dan.rhs;
				this->defaultVal = dan.defaultVal;
				this->allocSize = dan.allocSize;
			}

			DeclAssignNode::DeclAssignNode(TypeNode* type, std::wstring name, ExprNode* rhs)
			{
				this->name = name;
				this->type = type;
				this->allocSize = 0;
				if (!rhs)
				{
					this->defaultVal = true;
				}
				else
				{
					this->defaultVal = false;
				}
				this->rhs = rhs;
			}

			DeclAssignNode::~DeclAssignNode()
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

			std::wstring DeclAssignNode::To_String()
			{
				std::wstringstream returnable;
				returnable << L"DeclAssignNode: Name = ";
				returnable << this->name;
				returnable << L" Type = ";
				returnable << this->type->To_String();
				returnable << L".\n";
				returnable << this->rhs->To_String();
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool DeclAssignNode::Equals(Node* n)
			{
				DeclAssignNode* dan;
				try
				{
					dan = dynamic_cast<DeclAssignNode*>(n);
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
				else if (this->allocSize != dan->allocSize)
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

			StructInitNode::StructInitNode(StructInitNode& sdan)
			{
				this->defaultVal = sdan.defaultVal;
				this->inits = sdan.inits;
				this->name = sdan.name;
				this->type = sdan.type;
			}

			StructInitNode::StructInitNode(TypeNode* type, std::wstring name, std::list<ExprNode*> inits)
			{
				this->type = type;
				this->name = name;
				if (inits.size() == 0)
				{
					this->defaultVal = true;
				}
				else
				{
					this->defaultVal = false;
				}
				this->inits = inits;
			}
			
			StructInitNode::~StructInitNode()
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

			std::wstring StructInitNode::To_String()
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
			
			bool StructInitNode::Equals(Node* n)
			{
				StructInitNode* sdan;
				try
				{
					sdan = dynamic_cast<StructInitNode*>(n);
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
			*		BlockNode Class: represents a block 
			*		Contains:	body - list of statements
			*/

			BlockNode::BlockNode(BlockNode& bn)
			{
				this->body = bn.body;
			}

			BlockNode::BlockNode(std::list<StmtNode*> body)
			{
				this->body = body;
			}

			BlockNode::~BlockNode()
			{
				BOOST_FOREACH(StmtNode* s, this->body)
				{
					if(s)
					{
						delete s;
					}
					s=NULL;
				}
				this->body.clear();
			}

			std::wstring BlockNode::To_String()
			{
				std::wstringstream returnable;
				returnable << L"Enter Block Node\n";
				BOOST_FOREACH(StmtNode* s, this->body)
				{
					returnable << s->To_String();
				}
				returnable << L"Exit Block Node\n";
				std::wstring returnableChar = returnable.str();
				return returnableChar;      
			}

			bool BlockNode::Equals(Node* n)
			{
				BlockNode* bn;
				try
				{
					bn = dynamic_cast<BlockNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				if (!bn)
				{
					return false;
				}
				std::list<StmtNode*> bodycopy = std::list<StmtNode*>();
				BOOST_FOREACH(StmtNode* s, this->body)
				{
					bodycopy.push_back(s);
				}
				int size = bn->body.size();
				BOOST_FOREACH(StmtNode* s, bn->body)
				{
					bodycopy.remove(s);
					if (size - 1 != bodycopy.size())
					{
						return false;
					}
					size--;
				}
				return (size == 0);
			}

			/*
			*		ReturnNode Class: represents a return from a function
			*		Contains:	rhs - expression
			*/

			ReturnNode::ReturnNode(ReturnNode& rn)
			{
				this->rhs = rn.rhs;
			}

			ReturnNode::ReturnNode(ExprNode* rhs)
			{
				this->rhs = rhs;
			}

			ReturnNode::~ReturnNode() 
			{
				if (this->rhs) 
				{
					delete this->rhs;
				}
				this->rhs = NULL;
			}

			std::wstring ReturnNode::To_String()
			{
				std::wstringstream returnable;
				returnable << L"Enter Return Node\nRHS: ";
				returnable << this->rhs->To_String();
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool ReturnNode::Equals(Node* n)
			{
				ReturnNode* rn;
				try
				{
					rn = dynamic_cast<ReturnNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				return rn && this->rhs->Equals(rn->rhs);
			}

			/*
			*		IfNode Class: represents an if-then-else branching structure
			*		Contains:	testcase - expression
			*					thenstmt - statement
			*					elsestmt - statement
			*/

			IfNode::IfNode(IfNode& ino)
			{
				this->testcase = ino.testcase;
				this->thenstmt = ino.thenstmt;
				this->elsestmt = ino.elsestmt;
			}

			IfNode::IfNode(ExprNode* testcase, StmtNode* thenstmt, StmtNode* elsestmt)
			{
				this->testcase = testcase;
				this->thenstmt = thenstmt;
				this->elsestmt = elsestmt;
			}

			IfNode::IfNode(ExprNode* testcase, StmtNode* thenstmt)
			{
				this->testcase = testcase;
				this->thenstmt = thenstmt;
				this->elsestmt = NULL;
			}

			IfNode::~IfNode()
			{
				if (this->testcase)
				{
					delete this->testcase;
				}
				this->testcase = NULL;
				if (this->thenstmt)
				{
					delete this->thenstmt;
				}
				this->thenstmt = NULL;
				if (this->elsestmt)
				{
					delete this->elsestmt;
				}
				this->elsestmt = NULL;
			}

			std::wstring IfNode::To_String()
			{
				std::wstringstream returnable;
				returnable << L"Enter If Node\n";
				returnable << L"Test Case: \n";
				returnable << this->testcase->To_String();
				returnable << L"Then Case: \n";
				returnable << this->thenstmt->To_String();
				if (this->elsestmt)
				{
					returnable << L"Else Case: \n";
					returnable << this->elsestmt->To_String();
				}
				returnable << L"Leave If Node\n";
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool IfNode::Equals(Node* n)
			{
				IfNode* in;
				try
				{
					in = dynamic_cast<IfNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				if (!this->testcase->Equals(in))
				{
					return false;
				}
				else if (!this->thenstmt->Equals(in))
				{
					return false;
				}
				else if (this->elsestmt == NULL && in->elsestmt == NULL)
				{
					return true;
				}
				else
				{
					return this->elsestmt->Equals(in);
				}
			}

			/*
			*		SwitchNode Class: represents an switch branching structure
			*		Contains:	testcase - expression
			*					cases - list of expressions
			*					thenstmts - list of statements
			*					defaultCase - statement
			*/

			SwitchNode::SwitchNode(SwitchNode& sn)
			{
				this->cases = sn.cases;
				this->defaultCase = sn.defaultCase;
				this->testcase = sn.testcase;
				this->thenstmts = sn.thenstmts;
			}

			SwitchNode::SwitchNode(ExprNode* test, std::list<ExprNode*> cases, std::list<StmtNode*> thenstmts, StmtNode* defaultCase)
			{
				this->testcase = test;
				this->cases = cases;
				this->thenstmts = thenstmts;
				this->defaultCase = defaultCase;
			}

			SwitchNode::~SwitchNode()
			{
				if (this->testcase)
				{
					delete this->testcase;
				}
				this->testcase = NULL;
				BOOST_FOREACH(ExprNode* exp, this->cases)
				{
					if (exp)
					{
						delete exp;
					}
					exp = NULL;
				}
				BOOST_FOREACH(StmtNode* exp, this->thenstmts)
				{
					if (exp)
					{
						delete exp;
					}
					exp = NULL;
				}
				if (this->defaultCase)
				{
					delete this->defaultCase;
				}
				this->defaultCase = NULL;
			}

			std::wstring SwitchNode::To_String()
			{
				std::wstringstream returnable;
				returnable << L"Enter Switch Node\n";
				returnable << L"Test Case: \n";
				returnable << this->testcase->To_String();
				int numCases = 1;
				std::list<ExprNode*>::iterator itr1;
				std::list<StmtNode*>::iterator itr2;
				for(itr1 = this->cases.begin(), itr2 = this->thenstmts.begin(); itr1 != this->cases.end() && itr2 != this->thenstmts.end(); itr1++, itr2++)
				{
					returnable << L"Case #" << numCases++ << ":\n";
					returnable << (*itr1)->To_String();
					returnable << L"\n";
					returnable << (*itr2)->To_String();
					returnable << L"\n";
				}
				if (this->defaultCase)
				{
					returnable << L"Default Case: \n";
					returnable << this->defaultCase->To_String();
				}
				returnable << L"Leave Switch Node\n";
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool SwitchNode::Equals(Node* n)
			{
				SwitchNode* sn;
				try
				{
					sn = dynamic_cast<SwitchNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				if (!this->testcase->Equals(sn))
				{
					return false;
				}
				else 
				{
					std::list<ExprNode*>::iterator itr1;
					std::list<ExprNode*>::iterator itr2;
					for(itr1 = this->cases.begin(), itr2 = sn->cases.begin(); itr1 != this->cases.end() && itr2 != sn->cases.end(); itr1++, itr2++)
					{
						if (!(*itr1)->Equals((*itr2)))
						{
							return false;
						}
					}
					std::list<StmtNode*>::iterator itr3;
					std::list<StmtNode*>::iterator itr4;
					for(itr3 = this->thenstmts.begin(), itr4 = sn->thenstmts.begin(); itr3 != this->thenstmts.end() && itr4 != sn->thenstmts.end(); itr3++, itr4++)
					{
						if (!(*itr3)->Equals((*itr4)))
						{
							return false;
						}
					}
					if (this->defaultCase == NULL && sn->defaultCase == NULL)
					{
						return true;
					}
					else if (this->defaultCase == NULL || sn->defaultCase == NULL)
					{
						return false;
					}
					else
					{
						return this->defaultCase->Equals(sn->defaultCase);
					}
				}
			}

			/*
			*		WhileNode Class: represents a while looping structure
			*		Contains:	testcase - expression
			*					body	 - statement
			*/

			WhileNode::WhileNode(WhileNode& wn)
			{
				this->testcase = wn.testcase;
				this->body = wn.body;
			}

			WhileNode::WhileNode(ExprNode* testcase, StmtNode* body) {
				this->testcase = testcase;
				this->body = body;
			}

			WhileNode::~WhileNode() {
				if (this->testcase)
				{
					delete this->testcase;
				}
				this->testcase = NULL;
				if (this->body)
				{
					delete this->body;
				}
				this->body = NULL;
			}

			std::wstring WhileNode::To_String() {
				std::wstringstream returnable;
				returnable << L"Enter While Node\nTest Case:";
				returnable << this->testcase->To_String();
				returnable << L"Body:\n";
				returnable << this->body->To_String();
				returnable << L"Leave While Node\n";
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool WhileNode::Equals(Node* n)
			{
				WhileNode* wn;
				try
				{
					wn = dynamic_cast<WhileNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				if (!this->testcase->Equals(wn->testcase))
				{
					return false;
				}
				else
				{
					return this->body->Equals(wn->body);
				}
			}
		}
	}
}