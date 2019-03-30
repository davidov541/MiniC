#include "Node.h"
#include "stdafx.h"


namespace MiniC
{
	namespace IR
	{
		namespace AST
		{
			/*
			*		FormalNode Class: represents the formal parameters of a method
			*		Contains:	name - string
			*				type - PrimitiveTypeNode
			*/

			MiniC::IR::Epicness::FlowGraph::FlowGraph* FormalNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 3)
				{
					wprintf(L"%s%s\n", L"Converting FormalNode To Instruction Name: ", this->name);
				}
				Instruction::Instruction* inst = new MiniC::IR::Instruction::Instruction();
				inst->op = L"formal";
				inst->rd = this->name;
				fg->InsertInstruction(inst);
				fg->AddLocalVar(this->name, this->allocSize);
				return fg;
			}
			
			/*
			*		FuncNode Class: represents a function declaration and implementation
			*		Contains:	name		- string
			*				type		- PrimitiveTypeNode
			*				parameters	- list of formals
			*				body		- list of statements
			*/

			bool FuncNode::CheckUsage(std::list<std::wstring> functionUses)
			{
				if (this->isMain)
				{
					return true;
				}
				BOOST_FOREACH(std::wstring func, functionUses)
				{
					if (this->name.compare(func) == 0)
					{
						return true;
					}
				}
				return false;
			}

			std::list<std::wstring> FuncNode::GetFunctionUses()
			{
				std::list<std::wstring> funcs = std::list<std::wstring>();
				BOOST_FOREACH(StmtNode* stmt, this->body)
				{
					BOOST_FOREACH(std::wstring func, stmt->GetFunctionUses())
					{
						funcs.push_back(func);
					}
				}
				return funcs;
			}

			void FuncNode::Optimize(SymbolTable env)
			{
				BOOST_FOREACH(StmtNode* stmt, this->body)
				{
					stmt->Optimize(env);
				}
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* FuncNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 3)
				{
					wprintf(L"%s%s\n", L"Converting FuncNode To Instruction Name: ", this->name);
				}
				fg->EnterFunction();
				Instruction::Instruction* inst = new Instruction::Instruction();
				if (this->isInterruptHandler)
				{
					inst->op = L"nop";
				}
				else
				{
					inst->op = L"funcdecl";
				}
				inst->label = this->name;
				inst->label.append(this->type->To_String());
				TCHAR* buf = (TCHAR*) calloc(sizeof(TCHAR), 3);
				swprintf(buf, L"%d", this->parameters.size());
				inst->rd = std::wstring(buf);
				fg->InsertInstruction(inst);
				fg->InsertFuncName(inst->label);
				if (!this->isMain)
				{
					BOOST_FOREACH(FormalNode* formal, this->parameters) 
					{
						fg = formal->GetFlowGraph(fg);
					}
				}
				BOOST_FOREACH(StmtNode* stmt, this->body)
				{
					fg = stmt->GetFlowGraph(fg);
				}
				if (this->isVoid && !this->isInterruptHandler)
				{
					Instruction::Instruction* inst2 = new Instruction::Instruction();
					inst2->op = L"funcend";
					fg->InsertInstruction(inst2);
				}
				fg->InsertNewBasicBlock(false);
				fg->ExitFunction();
				return fg;
			}


			/*
			*		FuncDeclNode Class: represents a function declaration
			*		Contains:	name		- string
			*				type		- PrimitiveTypeNode
			*				parameters	- list of formals
			*/
			
			std::list<std::wstring> FuncDeclNode::GetFunctionUses()
			{
				return std::list<std::wstring>();
			}

			bool FuncDeclNode::CheckUsage(std::list<std::wstring> functionUses)
			{
				return true;
			}

			void FuncDeclNode::Optimize(SymbolTable env)
			{
				return;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* FuncDeclNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg)
			{
				return fg;
			}


			/*
			*		GlobalDeclAssignNode Class: represents a declaration & assignment node at the global scope
			*		Contains:	type - Type
			*					name - string
			*					rhs  - expression
			*/
			
			std::list<std::wstring> GlobalDeclAssignNode::GetFunctionUses()
			{
				return std::list<std::wstring>();
			}

			bool GlobalDeclAssignNode::CheckUsage(std::list<std::wstring> functionUses)
			{
				return true;
			}

			void GlobalDeclAssignNode::Optimize(SymbolTable env)
			{
				int val = 0;
				if (this->rhs->IsConstant(&val))
				{
					this->rhs = new IntNode(val);
				}
			}
			
			MiniC::IR::Epicness::FlowGraph::FlowGraph* GlobalDeclAssignNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg)
			{
				fg->AddGlobalVar(this->name, this->allocSize);
				if (this->rhs)
				{
					fg = this->rhs->GetFlowGraph(fg, 0);
				}
				fg->ResetLastRd(L"*tmp");
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", this->name, L"*tmp", L"0", L""));
				return fg;
			}

			/*
			*		GlobalStructInitNode Class: represents a declaration & assignment node
			*		Contains:	type - Type
			*					name - string
			*					inits - list<string>
			*					defaultVal - bool
			*/
			std::list<std::wstring> GlobalStructInitNode::GetFunctionUses()
			{
				std::list<std::wstring> funcs;
				BOOST_FOREACH(ExprNode* init, this->inits)
				{
					BOOST_FOREACH(std::wstring func, init->GetFunctionUses())
					{
						funcs.push_back(func);
					}
				}
				return funcs;
			}

			bool GlobalStructInitNode::CheckUsage(std::list<std::wstring> functionUses)
			{
				return true;
			}
			
			void GlobalStructInitNode::Optimize(SymbolTable env)
			{
				std::list<ExprNode*> newInits = std::list<ExprNode*>();
				int value = 0;
				BOOST_FOREACH(ExprNode* init, this->inits)
				{
					if (init->IsConstant(&value))
					{
						newInits.push_back(new IntNode(value));
					}
					else
					{
						newInits.push_back(init);
					}
				}
				this->inits = newInits;
			}
			
			MiniC::IR::Epicness::FlowGraph::FlowGraph* GlobalStructInitNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg)
			{
				//Assumes only 1 word-sized primitives in struct.
				int currPos = 0;
				BOOST_FOREACH(ExprNode* init, this->inits)
				{
					init->GetFlowGraph(fg, 0);
					fg->ResetLastRd(L"*tmp");
					std::wstringstream wss;
					wss << currPos++;
					fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", this->name, L"*tmp", wss.str(), L""));
				}
				fg->AddGlobalVar(this->name, currPos);
				return fg;
			}	

			/*
			*		StructDeclNode Class: represents the declaration of a struct
			*/
			std::list<std::wstring> StructDeclNode::GetFunctionUses()
			{
				return std::list<std::wstring>();
			}

			bool StructDeclNode::CheckUsage(std::list<std::wstring> functionUses)
			{
				return true;
			}

			void StructDeclNode::Optimize(SymbolTable env)
			{
				
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* StructDeclNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg)
			{
				fg->AddStruct(this->struct_name);
				std::list<TypeNode*>::iterator itr;
				std::list<std::wstring>::iterator itr2;
				int currPos = 0;
				for(itr2 = this->names.begin(), itr = this->types.begin(); itr2 != this->names.end() && itr != this->types.end(); itr++, itr2++)
				{
					fg->AddStructField(this->struct_name, (*itr2), currPos);
					//Assumes no structs within structs (not supported in other places as well anyways).
					currPos += 1;
				}
				if (this->init_name.compare(L"") != 0)
				{
					BOOST_FOREACH(std::wstring field, this->names)
					{
						fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"0", L"", L""));
						std::wstringstream wss;
						wss << fg->GetStructFieldPos(this->struct_name, field);
						fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", this->init_name, L"*tmp", wss.str(), L""));
					}			
					fg->AddGlobalVar(this->init_name, currPos);
				}
				return fg;
			}
			
			/*
			*		ProgramNode Class: represents a program in the minijava AST
			*		Contains:	mainFunc	- main function declaration
			*			        otherFuncs	- all other class declarations
			*/

			void ProgramNode::Optimize(SymbolTable env)
			{
				BOOST_FOREACH(TranslationUnitNode* unit, this->funcs)
				{
					unit->Optimize(env);
				}
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* ProgramNode::GetFlowGraph()
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 3)
				{
					wprintf(L"Converting ProgramNode To FlowGraph\n");
				}
				MiniC::IR::Epicness::FlowGraph::FlowGraph* fg = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
				//Makes sure interrupt is first function, and main is second.
				//Declarations should be run through FlowGraph ASAP as well.
				BOOST_FOREACH(TranslationUnitNode* unit, this->funcs)
				{
					if(ErrorHandler::GetInstance()->GetDebugCode() == 3)
					{
						wprintf(L"Converting FunctionNode...\n");
					}
					if (unit->isInterruptHandler || unit->isDecl)
					{
						fg = unit->GetFlowGraph(fg);
					}
				}
				BOOST_FOREACH(TranslationUnitNode* unit, this->funcs)
				{
					if(ErrorHandler::GetInstance()->GetDebugCode() == 3)
					{
						wprintf(L"Converting FunctionNode...\n");
					}
					if (unit->isMain)
					{
						fg = unit->GetFlowGraph(fg);
					}
				}
				BOOST_FOREACH(TranslationUnitNode* unit, this->funcs)
				{
					if(ErrorHandler::GetInstance()->GetDebugCode() == 3)
					{
						wprintf(L"Converting FunctionNode...\n");
					}
					if (!unit->isMain && !unit->isDecl && !unit->isInterruptHandler)
					{
						fg = unit->GetFlowGraph(fg);
					}
				}
				fg->RemoveLastBlock();
				return fg;
			}
		}
	}
}