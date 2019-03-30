#include "Node.h"
#include "stdafx.h"


namespace MiniC
{
	namespace IR
	{
		namespace AST
		{			
			/*
			*		AssignNode Class: represents an assignment of a pre-existing variable or field
			*		Contains:	name - string
			*					rhs  - expression
			*/
			
			std::list<std::wstring> AssignNode::GetFunctionUses()
			{
				return this->rhs->GetFunctionUses();
			}

			bool AssignNode::IsConstant(int* val)
			{
				if (this->rhs->IsConstant(val))
				{
					this->rhs = new IntNode(*val);
				}
				return false;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* AssignNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 3)
				{
					wprintf(L"%s%s\n", L"Converting AssignNode To Instruction");
				}
				fg = this->rhs->GetFlowGraph(fg, offset);
				fg->ResetLastRd(L"*tmp");
				fg->InsertInstruction(new Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
				fg = this->lhs->StoreValue(fg, 0);
				fg->InsertInstruction(new Instruction::Instruction(L"move", L"*tmp", L"*tmp", L"", L""));
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* AssignNode::StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* AssignNode::GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset)
			{
				return fg;
			}

			
			/*
			*		BinaryNode Class: represents a binary expression
			*		Contains:	operation	- string
			*				lhs			- expression
			*				rhs			- expression
			*/
			
			std::list<std::wstring> BinaryNode::GetFunctionUses()
			{
				std::list<std::wstring> returnable = std::list<std::wstring>();
				BOOST_FOREACH(std::wstring function, this->lhs->GetFunctionUses())
				{
					returnable.push_back(function);
				}
				BOOST_FOREACH(std::wstring function, this->rhs->GetFunctionUses())
				{
					returnable.push_back(function);
				}
				return returnable;
			}

			bool BinaryNode::IsConstant(int* val)
			{
				int lh;
				int rh;
				if (this->lhs->IsConstant(&lh) && this->rhs->IsConstant(&rh))
				{
					if (this->operation.compare(L"+") == 0)
					{
						*val = lh + rh;
						return true;
					}
					else if (this->operation.compare(L"-") == 0)
					{
						*val = lh - rh;
						return true;
					}
					else if (this->operation.compare(L"<<") == 0)
					{
						*val = lh << rh;
						return true;
					}
					else if (this->operation.compare(L">>") == 0)
					{
						*val = lh >> rh;
						return true;
					}
					else if (this->operation.compare(L"<") == 0)
					{
						*val = lh < rh;
						return true;
					}
					else if (this->operation.compare(L"<=") == 0)
					{
						*val = lh <= rh;
						return true;
					}
					else if (this->operation.compare(L">") == 0)
					{
						*val = lh > rh;
						return true;
					}
					else if (this->operation.compare(L">=") == 0)
					{
						*val = lh >= rh;
						return true;
					}
					else if (this->operation.compare(L"==") == 0)
					{
						*val = lh == rh;
						return true;
					}
					else if (this->operation.compare(L"!=") == 0)
					{
						*val = lh != rh;
						return true;
					}
					else if (this->operation.compare(L"&") == 0)
					{
						*val = lh & rh;
						return true;
					}
					else if (this->operation.compare(L"|") == 0)
					{
						*val = lh | rh;
						return true;
					}
					else if (this->operation.compare(L"&&") == 0)
					{
						*val = lh && rh;
						return true;
					}
					else if (this->operation.compare(L"||") == 0)
					{
						*val = lh || rh;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (this->lhs->IsConstant(&lh))
				{
					delete this->lhs;
					this->lhs = new IntNode(lh);
					return false;
				}
				else if (this->rhs->IsConstant(&rh))
				{
					delete this->rhs;
					this->rhs = new IntNode(rh);
					return false;
				}
				else
				{
					return false;
				}
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* BinaryNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset) {
				if(ErrorHandler::GetInstance()->GetDebugCode() == 3) {
					wprintf(L"Converting BinaryNode To Instruction Operation: %s\n", this->operation);
				}
				fg = this->lhs->GetFlowGraph(fg, 0);
				fg->ResetLastRd(L"*tmp");
				Instruction::Instruction* inst3 = new Instruction::Instruction();
				inst3->op = L"push";
				inst3->rt = L"*tmp";
				fg->InsertInstruction(inst3);
				fg = this->rhs->GetFlowGraph(fg, 0);
				fg->ResetLastRd(L"*tmp2");
				Instruction::Instruction* inst4 = new Instruction::Instruction();
				inst4->op = L"pop";
				inst4->rd = L"*tmp";
				fg->InsertInstruction(inst4);
				MiniC::IR::Instruction::Instruction* inst = new MiniC::IR::Instruction::Instruction();
				inst->op = this->operation;
				inst->rt = L"*tmp";
				inst->rs = L"*tmp2";
				fg->InsertInstruction(inst);
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* BinaryNode::StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				fg = this->lhs->GetFlowGraph(fg, 0);
				fg->ResetLastRd(L"*tmp");
				Instruction::Instruction* inst3 = new Instruction::Instruction();
				inst3->op = L"push";
				inst3->rt = L"*tmp";
				fg->InsertInstruction(inst3);
				fg = this->rhs->GetFlowGraph(fg, 0);
				fg->ResetLastRd(L"*tmp2");
				Instruction::Instruction* inst4 = new Instruction::Instruction();
				inst4->op = L"pop";
				inst4->rd = L"*tmp";
				fg->InsertInstruction(inst4);
				MiniC::IR::Instruction::Instruction* inst = new MiniC::IR::Instruction::Instruction();
				inst->op = this->operation;
				inst->rd = L"*tmp";
				inst->rt = L"*tmp";
				inst->rs = L"*tmp2";
				fg->InsertInstruction(inst);
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp2", L"", L"", L""));
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"storeadd", L"*tmp", L"*tmp2", L"", L""));
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* BinaryNode::GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 3)
				{
					wprintf(L"Converting BinaryNode To InstructionOperation: %s\n", this->operation);
				}
				fg = this->lhs->GetAddress(fg, L"*tmp", 0);
				MiniC::IR::Instruction::Instruction* inst3 = new MiniC::IR::Instruction::Instruction();
				inst3->op = L"push";
				inst3->rt = L"*tmp";
				fg->InsertInstruction(inst3);
				fg = this->rhs->GetAddress(fg, L"*tmp2", 0);
				MiniC::IR::Instruction::Instruction* inst4 = new MiniC::IR::Instruction::Instruction();
				inst4->op = L"pop";
				inst4->rd = L"*tmp";
				fg->InsertInstruction(inst4);
				MiniC::IR::Instruction::Instruction* inst = new MiniC::IR::Instruction::Instruction();
				inst->op = this->operation;
				inst->rt = L"*tmp";
				inst->rs = L"*tmp2";
				inst->rd = storage;
				fg->InsertInstruction(inst);
				return fg;
			}

			
			/*
			*		KeywordNode Class: represents a keyword expression
			*		Contains:	word - string
			*/
			
			std::list<std::wstring> KeywordNode::GetFunctionUses()
			{
				std::list<std::wstring> returnable = std::list<std::wstring>();
				return returnable;
			}

			bool KeywordNode::IsConstant(int* val)
			{
				if (this->word.compare(L"true") == 0)
				{
					*val = 1;
					return true;
				}
				else if (this->word.compare(L"false") == 0)
				{
					*val = 0;
					return true;
				}
				else
				{
					return false;
				}
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* KeywordNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset) {
				if(ErrorHandler::GetInstance()->GetDebugCode() == 3) {
					wprintf(L"%s%s\n", L"Converting KeywordNode To Instruction Keyword: ", this->word);
				}
				MiniC::IR::Instruction::Instruction* inst = new MiniC::IR::Instruction::Instruction();
				if (this->word.compare(L"null") == 0)
				{
					inst->op = L"null";
				} 
				else if (this->word.compare(L"true") == 0)
				{
					inst->op = L"loadi";
					inst->rt = L"1";
				} 
				else if (this->word.compare(L"false") == 0)
				{
					inst->op = L"loadi";
					inst->rt = L"0";
				}
				fg->InsertInstruction(inst);
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* KeywordNode::StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* KeywordNode::GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset)
			{
				return fg;
			}

			
			/*
			*		VarNode Class: represents a variable expression
			*		Contains:	name - wstring
			*                          type - wstring
			*/
			
			std::list<std::wstring> VarNode::GetFunctionUses()
			{
				std::list<std::wstring> returnable = std::list<std::wstring>();
				return returnable;
			}

			bool VarNode::IsConstant(int* val)
			{
				return false;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* VarNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset) {
				if(ErrorHandler::GetInstance()->GetDebugCode() == 3) {
					wprintf(L"%s%s\n", L"Converting VarNode To Instruction Name: ", this->name);
				}
				MiniC::IR::Instruction::Instruction* inst = new MiniC::IR::Instruction::Instruction();
				inst->op = L"load";
				inst->rt = this->name;
				std::wstringstream wss;
				wss << offset;
				inst->rs = wss.str();
				fg->InsertInstruction(inst);
				return fg;
			}
			
			MiniC::IR::Epicness::FlowGraph::FlowGraph* VarNode::StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				fg->InsertInstruction(new Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
				std::wstringstream wss;
				wss << offset;
				fg->InsertInstruction(new Instruction::Instruction(L"store", this->name, L"*tmp", wss.str(), L""));
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* VarNode::GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset)
			{
				std::wstringstream wss;
				wss << offset;
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"u&", storage, this->name, wss.str(), L""));
				return fg;
			}

			
			/*
			*		IntNode Class: represents a constant integer
			*		Contains:	val - int
			*/
			
			std::list<std::wstring> IntNode::GetFunctionUses()
			{
				std::list<std::wstring> returnable = std::list<std::wstring>();
				return returnable;
			}

			bool IntNode::IsConstant(int* val)
			{
				*val = this->val;
				return true;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* IntNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset) {
				if(ErrorHandler::GetInstance()->GetDebugCode() == 3)
				{
					printf("Converting IntNode To Instruction Value: %d\n", this->val);
				}
				MiniC::IR::Instruction::Instruction* inst = new MiniC::IR::Instruction::Instruction();
				inst->op = L"loadi";
				TCHAR* value = (TCHAR*) calloc(sizeof(TCHAR), NUM_LENGTH_MAX);
				swprintf_s(value, NUM_LENGTH_MAX, L"%d", this->val);
				inst->rt = value;
				fg->InsertInstruction(inst);
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* IntNode::StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* IntNode::GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 3)
				{
					printf("Converting IntNode To Instruction Value: %d\n", this->val);
				}
				MiniC::IR::Instruction::Instruction* inst = new MiniC::IR::Instruction::Instruction();
				inst->op = L"loadi";
				TCHAR* value = (TCHAR*) calloc(sizeof(TCHAR), NUM_LENGTH_MAX);
				swprintf_s(value, NUM_LENGTH_MAX, L"%d", this->val);
				inst->rt = value;
				fg->InsertInstruction(inst);
				return fg;
			}

			
			/*
			*		FuncCallNode Class: represents a method call
			*		contains:	funcname	- string
			*				params		- list of expressions
			*/
			
			std::list<std::wstring> FuncCallNode::GetFunctionUses()
			{
				std::list<std::wstring> returnable = std::list<std::wstring>();
				returnable.push_back(this->funcname);
				return returnable;
			}

			bool FuncCallNode::IsConstant(int* val)
			{
				std::list<ExprNode*> newParams = std::list<ExprNode*>();
				int value = 0;
				BOOST_FOREACH(ExprNode* param, this->params)
				{
					if (param->IsConstant(&value))
					{
						newParams.push_back(new IntNode(value));
					}
					else
					{
						newParams.push_back(param);
					}
				}
				this->params = newParams;
				return false;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* FuncCallNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 3) {
					wprintf(L"%s%s\n", L"Converting FuncCallNode To Instruction FuncName: ", this->funcname);
				}
				int numParams = 0;
				BOOST_FOREACH(ExprNode* param, this->params) {
					fg = param->GetFlowGraph(fg, 0);
					fg->ResetLastRd(L"*tmp");
					MiniC::IR::Instruction::Instruction* inst = new MiniC::IR::Instruction::Instruction();
					inst->op = L"param";
					inst->rd = L"*tmp";
					fg->InsertInstruction(inst);
					numParams++;
				}
				MiniC::IR::Instruction::Instruction* inst = new MiniC::IR::Instruction::Instruction;
				inst->op = L"funccall";
				inst->rt = this->funcname;
				inst->rt.append(this->returnType);
				inst->rs = numParams + 0x30;
				fg->InsertInstruction(inst);
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* FuncCallNode::StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* FuncCallNode::GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset)
			{
				return fg;
			}

			
			/*
			*		UnaryNode Class: represents a unary expression
			*		contains:	operation	- string
			*					rhs			- expression
			*					
			*/
			
			std::list<std::wstring> UnaryNode::GetFunctionUses()
			{
				return this->rhs->GetFunctionUses();
			}

			bool UnaryNode::IsConstant(int* val)
			{
				if (this->operation.compare(L"-") == 0)
				{
					if (!this->rhs->IsConstant(val))
					{
						return false;
					}
					*val = -*val;
					return true;
				}
				else if (this->operation.compare(L"+") == 0)
				{
					if (!this->rhs->IsConstant(val))
					{
						return false;
					}
					return true;
				}
				else if (this->operation.compare(L"~") == 0)
				{
					if (!this->rhs->IsConstant(val))
					{
						return false;
					}
					*val = ~*val;
					return true;
				}
				else if (this->operation.compare(L"!") == 0)
				{
					if (!this->rhs->IsConstant(val))
					{
						return false;
					}
					*val = !*val;
					return true;
				}
				else
				{
					return false;
				}
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* UnaryNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 3)
				{
					wprintf(L"%s%s\n", L"Converting UnaryNode To Instruction Operation: ", this->operation);
				}
				if (this->operation.compare(L"&") == 0)
				{
					fg = this->rhs->GetAddress(fg, L"*tmp", offset);
				}
				else
				{
					fg = this->rhs->GetFlowGraph(fg, offset);
					fg->ResetLastRd(L"*tmp");
					MiniC::IR::Instruction::Instruction* inst = new MiniC::IR::Instruction::Instruction();
					if (this->operation.compare(L"!") == 0)
					{
						inst->op = L"u~";
					}
					else
					{
						inst->op = L"u" + this->operation;
					}
					inst->rt = L"*tmp";
					fg->InsertInstruction(inst);
				}
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* UnaryNode::StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				if (this->operation.compare(L"*") == 0)
				{
					fg = this->rhs->GetFlowGraph(fg, offset);
					fg->ResetLastRd(L"*tmp2");
					fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
					fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"storeadd", L"*tmp", L"*tmp2", L"", L""));
				}
				else if (this->operation.compare(L"&") == 0)
				{
					fg = this->rhs->GetAddress(fg, L"*tmp2", offset);
					fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
					fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"storeadd", L"*tmp", L"*tmp2", L"", L""));
				}
				else
				{
					return fg;
				}
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* UnaryNode::GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset)
			{
				return fg;
			}

			
			/*
			*		TernaryNode Class: represents a ternary expression
			*					
			*/
			
			std::list<std::wstring> TernaryNode::GetFunctionUses()
			{
				std::list<std::wstring> returnable = std::list<std::wstring>();
				BOOST_FOREACH(std::wstring func, this->cond->GetFunctionUses())
				{
					returnable.push_back(func);
				}
				BOOST_FOREACH(std::wstring func, this->thenstmt->GetFunctionUses())
				{
					returnable.push_back(func);
				}
				BOOST_FOREACH(std::wstring func, this->elsestmt->GetFunctionUses())
				{
					returnable.push_back(func);
				}
				return returnable;
			}

			bool TernaryNode::IsConstant(int* val)
			{
				int condi = 0;
				if (this->cond->IsConstant(&condi))
				{
					this->cond = new IntNode(condi);
				}
				return false;
			}
			
			MiniC::IR::Epicness::FlowGraph::FlowGraph* TernaryNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 3)
				{
					std::cout << "Converting TernaryNode To Instruction\n";
				}
				if (this->cond->Equals(new KeywordNode(L"true")) || this->cond->Equals(new IntNode(1)))
				{
					fg = this->thenstmt->GetFlowGraph(fg, offset);
				}
				else if (this->cond->Equals(new KeywordNode(L"false")) || this->cond->Equals(new IntNode(0)))
				{
					fg = this->elsestmt->GetFlowGraph(fg, offset);
				}
				else
				{
					fg = this->cond->GetFlowGraph(fg, offset);
					fg->ResetLastRd(L"*tmp");
					MiniC::IR::Instruction::Instruction* inst = new MiniC::IR::Instruction::Instruction();
					inst->op = L"if";
					inst->rd = L"*tmp";
					fg->InsertInstruction(inst);
					int caseNum = fg->GetCurrBlock();
					fg->InsertNewBasicBlock(true);
					fg = this->thenstmt->GetFlowGraph(fg, offset);
					fg->ResetLastRd(L"*tmp");
					int thenNum = fg->GetCurrBlock();

					// Creates Else BasicBlock, and connects it
					fg->InsertNewBasicBlock(false);
					fg->InsertLink(caseNum, fg->GetCurrBlock());
					fg = this->elsestmt->GetFlowGraph(fg, offset);
					fg->ResetLastRd(L"*tmp");

					// Creates next basicblock and connects the then and else blocks to it.
					fg->InsertNewBasicBlock(true);
					fg->InsertLink(thenNum, fg->GetCurrBlock());
					fg->InsertInstruction(new Instruction::Instruction(L"move", L"*tmp", L"*tmp", L"", L""));
				}
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* TernaryNode::StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* TernaryNode::GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset)
			{
				return fg;
			}

			
			/*
			*		StringNode Class: represents a string
			*					
			*/
			
			std::list<std::wstring> StringNode::GetFunctionUses()
			{
				std::list<std::wstring> returnable = std::list<std::wstring>();
				return returnable;
			}

			bool StringNode::IsConstant(int* val)
			{
				return false;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* StringNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				int labelNum = fg->InsertData(*(this->value));
				MiniC::IR::Instruction::Instruction* inst = new MiniC::IR::Instruction::Instruction();
				inst->op = L"la";
				TCHAR* label = (TCHAR*) calloc(sizeof(TCHAR), LABEL_LENGTH_MAX);
				swprintf_s(label, LABEL_LENGTH_MAX, L"D%d", labelNum);
				inst->rt = label;
				fg->InsertInstruction(inst);
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* StringNode::StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* StringNode::GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset)
			{
				return fg;
			}

			
			/*
			*		CharNode Class: represents a character
			*					
			*/

			std::list<std::wstring> CharNode::GetFunctionUses()
			{
				std::list<std::wstring> returnable = std::list<std::wstring>();
				return returnable;
			}

			bool CharNode::IsConstant(int* val)
			{
				*val = (int) this->value;
				return true;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* CharNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 3)
				{
					printf("Converting CharNode To Instruction Value: %s\n", this->value);
				}
				MiniC::IR::Instruction::Instruction* inst = new MiniC::IR::Instruction::Instruction();
				inst->op = L"loadi";
				TCHAR* value = (TCHAR*) calloc(sizeof(TCHAR), NUM_LENGTH_MAX);
				swprintf_s(value, NUM_LENGTH_MAX, L"%d", this->value);
				inst->rt = value;
				fg->InsertInstruction(inst);
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* CharNode::StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* CharNode::GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset)
			{
				return fg;
			}
				

			/*
			*		ArrayNode Class: represents indexing into an array
			*					
			*/
			
			std::list<std::wstring> ArrayNode::GetFunctionUses()
			{
				std::list<std::wstring> returnable = std::list<std::wstring>();
				BOOST_FOREACH(std::wstring func, this->inner->GetFunctionUses())
				{
					returnable.push_back(func);
				}
				BOOST_FOREACH(std::wstring func, this->lhs->GetFunctionUses())
				{
					returnable.push_back(func);
				}
				return returnable;
			}

			bool ArrayNode::IsConstant(int* val)
			{
				int value = 0;
				if (this->inner->IsConstant(&value))
				{
					delete inner;
					this->inner = new IntNode(value);
				}
				return false;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* ArrayNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				if(ErrorHandler::GetInstance()->GetDebugCode() == 3)
				{
					printf("Converting ArrayNode To Instruction\n");
				}
				fg = this->lhs->GetFlowGraph(fg, offset);
				fg->ResetLastRd(L"*tmp");
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
				fg = this->inner->GetFlowGraph(fg, 0);
				fg->ResetLastRd(L"*tmp2");
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"<<i", L"*tmp2", L"*tmp2", L"1", L""));
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"+", L"*tmp", L"*tmp", L"*tmp2", L""));
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"u*", L"", L"*tmp", L"", L""));
				return fg;
			}
			
			MiniC::IR::Epicness::FlowGraph::FlowGraph* ArrayNode::StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				fg = this->lhs->GetFlowGraph(fg, offset);
				fg->ResetLastRd(L"*tmp");
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
				fg = this->inner->GetFlowGraph(fg, 0);
				fg->ResetLastRd(L"*tmp2");
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"<<i", L"*tmp2", L"*tmp2", L"1", L""));
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"+", L"*tmp2", L"*tmp", L"*tmp2", L""));
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"storeadd", L"*tmp", L"*tmp2", L"", L""));
				return fg;
			}
			
			MiniC::IR::Epicness::FlowGraph::FlowGraph* ArrayNode::GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset)
			{
				fg = this->lhs->GetFlowGraph(fg, offset);
				fg->ResetLastRd(L"*tmp");
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
				fg = this->inner->GetFlowGraph(fg, 0);
				fg->ResetLastRd(L"*tmp2");
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"<<i", L"*tmp2", L"*tmp2", L"1", L""));
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"+", storage, L"*tmp", L"*tmp2", L""));
				return fg;
			}
				

			/*
			*		AssemblyNode Class: represents raw assembly code written in C
			*					
			*/
			
			std::list<std::wstring> AssemblyNode::GetFunctionUses()
			{
				std::list<std::wstring> returnable = std::list<std::wstring>();
				return returnable;
			}

			 bool AssemblyNode::IsConstant(int* val)
			{
				return false;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* AssemblyNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				Instruction::Instruction* i = new Instruction::Instruction();
				i->op = L"assembly";
				i->rd = this->code;
				i->inputVars = this->invars;
				i->outputVars = this->outvars;
				fg->InsertInstruction(i);
				if (this->code.find(L"$v") != std::wstring::npos)
				{
					fg->InsertInstruction(new Instruction::Instruction(L"move", L"*tmp", L"*v", L"", L""));
				}
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* AssemblyNode::StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* AssemblyNode::GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset)
			{
				return fg;
			}
				

			/*
			*		SizeOfNode Class: represents call to sizeof "macro"
			*					
			*/
			
			std::list<std::wstring> SizeOfNode::GetFunctionUses()
			{
				std::list<std::wstring> returnable = std::list<std::wstring>();
				return returnable;
			}

			bool SizeOfNode::IsConstant(int* val)
			{
				*val = 1;
				return true;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* SizeOfNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				fg->InsertInstruction(new Instruction::Instruction(L"loadi", L"", this->size, L"", L""));
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* SizeOfNode::StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				return fg;
			}

			MiniC::IR::Epicness::FlowGraph::FlowGraph* SizeOfNode::GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset)
			{
				return fg;
			}
			
			/*
			*	StructReferenceNode: Represents a reference through . or -> to a field in a struct.
			*/
			int StructReferenceNode::GetConstValue()
			{
				return -1;
			}

			std::list<std::wstring> StructReferenceNode::GetFunctionUses()
			{
				return this->lhs->GetFunctionUses();
			}
			
			bool StructReferenceNode::IsConstant(int* val)
			{
				return false;
			}
			
			MiniC::IR::Epicness::FlowGraph::FlowGraph* StructReferenceNode::GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				fg = this->lhs->GetFlowGraph(fg, fg->GetStructFieldPos(this->lhsType->To_String(), this->fieldName) + offset);
				return fg;
			}
			
			MiniC::IR::Epicness::FlowGraph::FlowGraph* StructReferenceNode::StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset)
			{
				fg = this->lhs->StoreValue(fg, fg->GetStructFieldPos(this->lhsType->To_String(), this->fieldName) + offset);
				return fg;
			}
			
			MiniC::IR::Epicness::FlowGraph::FlowGraph* StructReferenceNode::GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset)
			{
				fg = this->lhs->GetFlowGraph(fg, 0);
				fg->ResetLastRd(L"*tmp");
				std::wstringstream wss;
				wss << fg->GetStructFieldPos(this->lhsType->To_String(), this->fieldName);
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"u&", L"*tmp", L"*tmp", L"", L""));
				fg->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"+i", L"", L"*tmp", wss.str(), L""));
				return fg;
			}
		}
	}
}