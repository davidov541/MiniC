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
				
			std::list<std::wstring> ExpressionStmt::GetFunctionUses()
			{
				return this->expr->GetFunctionUses();
			}

			void ExpressionStmt::Optimize(SymbolTable env)
			{
				int val = 0;
				if (this->expr->IsConstant(&val))
				{
					this->expr = new IntNode(val);
				}
			}
				
			bool ExpressionStmt::IsEmpty()
			{
				return false;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* ExpressionStmt::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg)
			{
				return this->expr->GetFlowGraph(fg, 0);
			}

			
			/*
			*		DeclAssignNode Class: represents a declaration & assignment node
			*		Contains:	type - Type
			*					name - string
			*					rhs  - expression
			*/
			
			std::list<std::wstring> DeclAssignNode::GetFunctionUses()
			{
				if (this->rhs)
				{
					return this->rhs->GetFunctionUses();
				}
				else
				{
					return std::list<std::wstring>();
				}
			}

			void DeclAssignNode::Optimize(SymbolTable env)
			{
				int val = 0;
				if (this->rhs->IsConstant(&val))
				{
					this->rhs = new IntNode(val);
				}
			}
				
			bool DeclAssignNode::IsEmpty()
			{
				return false;
			}
			
			MiniC::IR::Epicness::FlowGraph::FlowGraph* DeclAssignNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 3)
				{
					wprintf(L"%s%s\n", "Converting AssignNode To Instruction Name: ", this->name);
				}
				if (this->defaultVal && this->type->GetArrayDim())
				{
					fg = ((ExprNode*) this->type->GetArrayDim())->GetFlowGraph(fg, 0);
					fg->ResetLastRd(L"*tmp");
					fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"<<i", L"*tmp", L"*tmp", L"1", L""));
					fg->InsertInstruction(new Instruction::Instruction(L"pusharr", L"*tmp", L"*tmp", L"", L""));
				}
				else
				{
					fg = this->rhs->GetFlowGraph(fg, 0);
					fg->ResetLastRd(L"*tmp");
				}
				fg->AddLocalVar(this->name, this->allocSize);
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", this->name, L"*tmp", L"0", L""));
				return fg;
			}

			/*
			*		StructInitNode Class: represents a declaration & assignment node
			*		Contains:	type - Type
			*					name - string
			*					inits - list<string>
			*					defaultVal - bool
			*/			
			std::list<std::wstring> StructInitNode::GetFunctionUses()
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
			
			void StructInitNode::Optimize(SymbolTable env)
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
				
			bool StructInitNode::IsEmpty()
			{
				return false;
			}
			
			MiniC::IR::Epicness::FlowGraph::FlowGraph* StructInitNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg)
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
				fg->AddLocalVar(this->name, currPos);
				return fg;
			}	
			
			
			/*
			*		BlockNode Class: represents a block 
			*		Contains:	body - list of statements
			*/
			
			std::list<std::wstring> BlockNode::GetFunctionUses()
			{
				std::list<std::wstring> returnable = std::list<std::wstring>();
				BOOST_FOREACH(StmtNode* stmt, this->body)
				{
					BOOST_FOREACH(std::wstring func, stmt->GetFunctionUses())
					{
						returnable.push_back(func);
					}
				}
				returnable.unique();
				return returnable;
			}

			void BlockNode::Optimize(SymbolTable env)
			{
				BOOST_FOREACH(StmtNode* stmt, this->body)
				{
					stmt->Optimize(env);
				}
			}
				
			bool BlockNode::IsEmpty()
			{
				return this->body.size() == 0;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* BlockNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 3)
				{
					wprintf(L"Converting BlockNode To Instruction\n");
				}
				BOOST_FOREACH(StmtNode* stmt, this->body)
				{
					fg = stmt->GetFlowGraph(fg);
				}
				return fg;
			}

			
			/*
			*		ReturnNode Class: represents a return from a function
			*		Contains:	rhs - expression
			*/
			
			std::list<std::wstring> ReturnNode::GetFunctionUses()
			{
				return this->rhs->GetFunctionUses();
			}

			void ReturnNode::Optimize(SymbolTable env)
			{
				int val = 0;
				if (this->rhs->IsConstant(&val))
				{
					this->rhs = new IntNode(val);
				}
			}
				
			bool ReturnNode::IsEmpty()
			{
				return false;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* ReturnNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 3)
				{
					wprintf(L"Converting ReturnNode To Instruction\n");
				}
				fg = this->rhs->GetFlowGraph(fg, 0);
				fg->ResetLastRd(L"*tmp");
				MiniC::IR::Instruction::Instruction* inst = new MiniC::IR::Instruction::Instruction();
				inst->op = L"jr";
				inst->rs = L"*tmp";
				fg->InsertInstruction(inst);
				return fg;
			}

			
			/*
			*		IfNode Class: represents an if-then-else branching structure
			*		Contains:	testcase - expression
			*					thenstmt - statement
			*					elsestmt - statement
			*/
			
			std::list<std::wstring> IfNode::GetFunctionUses()
			{
				std::list<std::wstring> returnable = std::list<std::wstring>();
				BOOST_FOREACH(std::wstring function, this->testcase->GetFunctionUses())
				{
					returnable.push_back(function);
				}
				BOOST_FOREACH(std::wstring function, this->thenstmt->GetFunctionUses())
				{
					returnable.push_back(function);
				}
				if (this->elsestmt)
				{
					BOOST_FOREACH(std::wstring function, this->elsestmt->GetFunctionUses())
					{
						returnable.push_back(function);
					}
				}
				return returnable;
			}

			void IfNode::Optimize(SymbolTable env)
			{
				int val = 0;
				if (this->testcase->IsConstant(&val))
				{
					this->testcase = new IntNode(val);
				}
				this->thenstmt->Optimize(env);
				if (this->elsestmt)
				{
					this->elsestmt->Optimize(env);
				}
			}
				
			bool IfNode::IsEmpty()
			{
				return false;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* IfNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 3)
				{
					std::cout << "Converting IfNode To Instruction Name: \n";
				}
				if (this->testcase->Equals(new KeywordNode(L"true")) || this->testcase->Equals(new IntNode(L"1")))
				{
					fg = this->thenstmt->GetFlowGraph(fg);
				}
				else if (this->testcase->Equals(new KeywordNode(L"false")) || this->testcase->Equals(new IntNode(L"0")))
				{
					if (this->elsestmt)
					{
						fg = this->elsestmt->GetFlowGraph(fg);
					}
				}
				else
				{
					fg = this->testcase->GetFlowGraph(fg, 0);
					fg->ResetLastRd(L"*tmp");
					MiniC::IR::Instruction::Instruction* inst = new MiniC::IR::Instruction::Instruction();
					inst->op = L"if";
					inst->rd = L"*tmp";
					fg->InsertInstruction(inst);
					int caseNum = fg->GetCurrBlock();
					fg->InsertNewBasicBlock(true);
					fg = this->thenstmt->GetFlowGraph(fg);
					int thenNum = fg->GetCurrBlock();
					if (this->thenstmt->IsEmpty())
					{
						fg->InsertInstruction(new Instruction::Instruction(L"nop", L"", L"", L"", L""));
					}
					if (this->elsestmt) 
					{
						// Creates Else BasicBlock, and connects it
						fg->InsertNewBasicBlock(false);
						fg->InsertLink(caseNum,  fg->GetCurrBlock());
						fg = this->elsestmt->GetFlowGraph(fg);
						if (this->elsestmt->IsEmpty())
						{
							fg->InsertInstruction(new Instruction::Instruction(L"nop", L"", L"", L"", L""));
						}

						// Creates next basicblock and connects the then and else blocks to it.
						fg->InsertNewBasicBlock(true);
						fg->InsertLink(thenNum, fg->GetCurrBlock());
					} 
					else 
					{
						// Creates next basic block and connects the case and then blocks to it.
						fg->InsertNewBasicBlock(true);
						fg->InsertLink(caseNum, fg->GetCurrBlock());
					}
				}
				return fg;
			}


			/*
			*		SwitchNode Class: represents an switch branching structure
			*		Contains:	testcase - expression
			*					cases - list of expressions
			*					thenstmts - list of statements
			*					defaultCase - statement
			*/
			
			std::list<std::wstring> SwitchNode::GetFunctionUses()
			{
				std::list<std::wstring> returnable = std::list<std::wstring>();
				BOOST_FOREACH(std::wstring function, this->testcase->GetFunctionUses())
				{
					returnable.push_back(function);
				}
				BOOST_FOREACH(StmtNode* stmt, this->thenstmts)
				{
					BOOST_FOREACH(std::wstring function, stmt->GetFunctionUses())
					{
						returnable.push_back(function);
					}
				}
				BOOST_FOREACH(ExprNode* expr, this->cases)
				{
					BOOST_FOREACH(std::wstring function, expr->GetFunctionUses())
					{
						returnable.push_back(function);
					}
				}
				if (this->defaultCase)
				{
					BOOST_FOREACH(std::wstring function, this->defaultCase->GetFunctionUses())
					{
						returnable.push_back(function);
					}
				}
				return returnable;
			}

			void SwitchNode::Optimize(SymbolTable env)
			{
				int val = 0;
				if (this->testcase->IsConstant(&val))
				{
					this->testcase = new IntNode(val);
				}
				std::list<ExprNode*> replacementList = std::list<ExprNode*>();
				BOOST_FOREACH(ExprNode* expr, this->cases)
				{
					if (expr->IsConstant(&val))
					{
						replacementList.push_back(new IntNode(val));
					}
					else
					{
						replacementList.push_back(expr);
					}
				}
				BOOST_FOREACH(StmtNode* stmt, this->thenstmts)
				{
					stmt->Optimize(env);
				}
				if (this->defaultCase)
				{
					this->defaultCase->Optimize(env);
				}
			}
				
			bool SwitchNode::IsEmpty()
			{
				return false;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* SwitchNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 3)
				{
					std::cout << "Converting IfNode To Instruction Name: \n";
				}
				std::list<ExprNode*>::iterator itr1;
				std::list<StmtNode*>::iterator itr2;
				for(itr1 = this->cases.begin(), itr2 = this->thenstmts.begin(); itr1 != this->cases.end() && itr2 != this->thenstmts.end(); itr1++, itr2++)
				{
					if (this->testcase->Equals((*itr1)))
					{
						fg = (*itr2)->GetFlowGraph(fg);
						return fg;
					}
				}
				int val = 0;
				if (this->testcase->IsConstant(&val))
				{
					if (this->defaultCase)
					{
						fg = this->defaultCase->GetFlowGraph(fg);
						return fg;
					}
					else
					{
						for(itr1 = this->cases.begin(), itr2 = this->thenstmts.begin(); itr1 != this->cases.end() && itr2 != this->thenstmts.end(); itr1++, itr2++)
						{
							if (this->testcase->Equals((*itr1)))
							{
								fg = (*itr2)->GetFlowGraph(fg);
								return fg;
							}
						}
						return fg;
					}
				}
				fg = this->testcase->GetFlowGraph(fg, 0);
				fg->ResetLastRd(L"*tmp");
				std::list<int> branchBlocks = std::list<int>();
				for(itr1 = this->cases.begin(); itr1 != this->cases.end();)
				{
					branchBlocks.push_back(fg->GetCurrBlock());
					MiniC::IR::Instruction::Instruction* inst2 = new MiniC::IR::Instruction::Instruction();
					inst2->op = L"push";
					inst2->rt = L"*tmp";
					fg->InsertInstruction(inst2);
					fg = (*itr1)->GetFlowGraph(fg, 0);
					fg->ResetLastRd(L"*tmp2");
					MiniC::IR::Instruction::Instruction* inst3 = new MiniC::IR::Instruction::Instruction();
					inst3->op = L"pop";
					inst3->rd = L"*tmp";
					fg->InsertInstruction(inst3);
					MiniC::IR::Instruction::Instruction* inst = new MiniC::IR::Instruction::Instruction();
					inst->op = L"beq";
					inst->rt = L"*tmp";
					inst->rs = L"*tmp2";
					fg->InsertInstruction(inst);
					itr1++;
					fg->InsertNewBasicBlock(true);
				}
				std::list<int> caseBlocks = std::list<int>();
				caseBlocks.push_back(fg->GetCurrBlock());
				if (this->defaultCase)
				{
					fg = this->defaultCase->GetFlowGraph(fg);
					fg->InsertNewBasicBlock(false);
				}
				else
				{
					fg->InsertInstruction(new Instruction::Instruction(L"jump", L"", L"", L"", L""));
					fg->InsertNewBasicBlock(false);
				}
				for(itr2 = this->thenstmts.begin(); itr2 != this->thenstmts.end(); itr2++)
				{
					fg->InsertLink(branchBlocks.front(), fg->GetCurrBlock());
					branchBlocks.pop_front();
					caseBlocks.push_back(fg->GetCurrBlock());
					fg = (*itr2)->GetFlowGraph(fg);
					if ((*itr2)->IsEmpty())
					{
						fg->InsertInstruction(new Instruction::Instruction(L"nop", L"", L"", L"", L""));	
					}
					fg->InsertNewBasicBlock(false);
				}
				while(caseBlocks.size() > 0)
				{
					fg->InsertLink(caseBlocks.front(), fg->GetCurrBlock());
					caseBlocks.pop_front();
				}
				return fg;
			}
			
			/*
			*		WhileNode Class: represents a while looping structure
			*		Contains:	testcase - expression
			*					body	 - statement
			*/
			
			std::list<std::wstring> WhileNode::GetFunctionUses()
			{
				std::list<std::wstring> returnable = std::list<std::wstring>();
				BOOST_FOREACH(std::wstring function, this->testcase->GetFunctionUses())
				{
					returnable.push_back(function);
				}
				BOOST_FOREACH(std::wstring function, this->body->GetFunctionUses())
				{
					returnable.push_back(function);
				}
				return returnable;
			}

			void WhileNode::Optimize(SymbolTable env)
			{
				int val = 0;
				if (this->testcase->IsConstant(&val))
				{
					this->testcase = new IntNode(val);
				}
				else
				{
					this->body->Optimize(env);
				}
			}
				
			bool WhileNode::IsEmpty()
			{
				return false;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* WhileNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg) {
				if(ErrorHandler::GetInstance()->GetDebugCode() == 3)
				{
					std::cout << "Converting WhileNode To Instruction\n";
				}
				if (!this->testcase->Equals(new KeywordNode(L"false")) && !this->testcase->Equals(new IntNode(L"0")))
				{
					fg->InsertNewBasicBlock(true);
					if (!this->testcase->Equals(new KeywordNode(L"true")) && !this->testcase->Equals(new IntNode(1)))
					{
						int testNum = fg->GetCurrBlock();
						fg = this->testcase->GetFlowGraph(fg, 0);
						fg->ResetLastRd(L"*tmp");
						MiniC::IR::Instruction::Instruction* inst = new MiniC::IR::Instruction::Instruction();
						inst->op = L"if";
						inst->rd = L"*tmp";
						fg->InsertInstruction(inst);
						fg->InsertNewBasicBlock(true);
						fg = this->body->GetFlowGraph(fg);
						fg->InsertLink(fg->GetCurrBlock(), testNum);
						MiniC::IR::Instruction::Instruction* inst2 = new MiniC::IR::Instruction::Instruction();
						inst2->op = L"jump";
						fg->InsertInstruction(inst2);
						fg->InsertNewBasicBlock(false);
						fg->InsertLink(testNum, fg->GetCurrBlock());
					}
					else
					{
						if (!this->body->IsEmpty())
						{
							int startBlock = fg->GetCurrBlock();
							fg = this->body->GetFlowGraph(fg);
							fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"jump", L"", L"", L"", L""));
							fg->InsertLink(fg->GetCurrBlock(), startBlock);
							fg->InsertNewBasicBlock(false);
						}
					}
				}
				return fg;
			}
		}
	}
}