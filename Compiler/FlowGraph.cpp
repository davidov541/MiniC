#include "FlowGraph.h"
#include "stdafx.h"

namespace MiniC {
	namespace IR {
		namespace Epicness {
			namespace FlowGraph {

				/*
				*	FUNCTION: FlowGraph
				*	DESCRIPTION: Default constructor for the FlowGraph class.
				*/
				FlowGraph::FlowGraph()
				{ 
					this->currBlock = 0;
					this->blocks = std::list<BasicBlock::BasicBlock*>();
					this->links = std::multimap<int, int>();
					this->blocks.push_back(new BasicBlock::BasicBlock());
					this->data = std::list<std::wstring>();
					this->globalBlock = new BasicBlock::BasicBlock();
					this->currDataLabel = 0;
					this->inGlobalScope = true;
					this->table = new IR::AST::SymbolTable();
				}

				/*
				*	FUNCTION: FlowGraph
				*	PARAMETER 1: FlowGraph& fn
				*	DESCRIPTION: Copy constructor for the FlowGraph class.
				*/
				FlowGraph::FlowGraph(FlowGraph& fn)
				{
					this->blocks = fn.blocks;
					this->links = fn.links;
					this->currBlock = fn.currBlock;
					this->funcNames = fn.funcNames;
					this->data = fn.data;
					this->currDataLabel = fn.currDataLabel;
					this->globalBlock = fn.globalBlock;
					this->inGlobalScope = fn.inGlobalScope;
					this->table = fn.table;
					this->structFieldPositions = fn.structFieldPositions;
				}
				
				/*
				*	FUNCTION: FlowGraph
				*	PARAMETER 1: Initializes FlowGraph with given SymbolTable.
				*	DESCRIPTION: Default constructor for the FlowGraph class.
				*/
				FlowGraph::FlowGraph(IR::AST::SymbolTable* table)
				{
					this->table = table;
					this->currBlock = 0;
					this->blocks = std::list<BasicBlock::BasicBlock*>();
					this->links = std::multimap<int, int>();
					this->blocks.push_back(new BasicBlock::BasicBlock());
					this->data = std::list<std::wstring>();
					this->globalBlock = new BasicBlock::BasicBlock();
					this->currDataLabel = 0;
					this->inGlobalScope = true;
				}

				/*
				*	FUNCTION: ~FlowGraph
				*	DESCRIPTION: Destructor for the FlowGraph class.
				*/
				FlowGraph::~FlowGraph()
				{
					BOOST_FOREACH(BasicBlock::BasicBlock* b, this->blocks)
					{
						if (b)
						{
							delete b;
						}
					}
					if (this->globalBlock)
					{
						delete this->globalBlock;
					}
				}

				

				/*
				*	FUNCTION: Equals
				*	DESCRIPTION: Returns true if the FlowGraph has the same instructions in it as the argument
				*		the function is passed, along with the same basic block structure. 
				*		It will return false if this is not the case.
				*/
				bool FlowGraph::Equals(FlowGraph* b2)
				{
					/*
					std::multimap<int, int> links;*/
					if (!this->globalBlock->Equals(b2->globalBlock) || this->currDataLabel != b2->currDataLabel || this->inGlobalScope != b2->inGlobalScope || this->currBlock != b2->currBlock \
						|| this->blocks.size() != b2->blocks.size() || this->links.size() != b2->links.size())
					{
						return false;
					}
					std::list<BasicBlock::BasicBlock*>::iterator itr1;
					std::list<BasicBlock::BasicBlock*>::iterator itr2;
					for(itr1 = this->blocks.begin(), itr2 = b2->blocks.begin(); itr1 != this->blocks.end() && itr2 != b2->blocks.end(); itr1++, itr2++)
					{
						if (!(*itr1)->Equals((*itr2)))
						{
							return false;
						}
					}
					std::list<std::wstring>::iterator itr3;
					std::list<std::wstring>::iterator itr4;
					for(itr3 = this->funcNames.begin(), itr4 = b2->funcNames.begin(); itr3 != this->funcNames.end() && itr4 != this->funcNames.end(); itr3++, itr4++)
					{
						if (itr3->compare(*itr4) != 0)
						{
							return false;
						}
					}	
					for(itr3 = this->data.begin(), itr4 = b2->data.begin(); itr3 != this->data.end() && itr4 != b2->data.end(); itr3++, itr4++)
					{
						if (itr3->compare(*itr4) != 0)
						{
							return false;
						}
					}	
					if (this->globalVars.size() != b2->globalVars.size())
					{
						return false;
					}
					boost::unordered_map<std::wstring, int>::iterator itr9;
					for(itr9 = this->globalVars.begin(); itr9 != this->globalVars.end(); itr9++)
					{
						if (b2->globalVars.find(itr9->first) == b2->globalVars.end())
						{
							return false;
						}
					}	
					std::multimap<int, int>::iterator itr5;
					std::multimap<int, int>::iterator itr6;
					for(itr5 = this->links.begin(), itr6 = b2->links.begin(); itr5 != this->links.end() && itr6 != b2->links.end(); itr5++, itr6++)
					{
						if (itr5->first != itr6->first || itr5->second != itr6->second)
						{
							return false;
						}
					}
					boost::unordered_map<std::wstring, std::list<std::pair<std::wstring, int> > >::iterator itr7;
					if (this->structFieldPositions.size() != b2->structFieldPositions.size())
					{
						return false;
					}
					for(itr7 = this->structFieldPositions.begin(); itr7 != this->structFieldPositions.end(); itr7++)
					{
						if(b2->structFieldPositions.find(itr7->first) == b2->structFieldPositions.end())
						{
							return false;
						}
						std::list<std::pair<std::wstring, int> > b2val = b2->structFieldPositions[itr7->first];
						std::list<std::pair<std::wstring, int> >::iterator itr8, itr9;
						if (itr7->second.size() != b2val.size())
						{
							return false;
						}
						for(itr8 = itr7->second.begin(), itr9 = b2val.begin(); itr8 != itr7->second.end() && itr9 != b2val.end(); itr8++, itr9++)
						{
							if (itr8->first.compare(itr9->first) != 0 || itr8->second != itr9->second)
							{
								return false;
							}
						}
					}
					return true;
				}

				/*
				*	FUNCTION: ToString
				*	DESCRIPTION: Prints out a representation of each basic block
				*		in this FlowGraph, along with the links between them.
				*/
				std::wstring FlowGraph::ToString()
				{
					std::wstringstream returnable;
					returnable << L"Basic Blocks: \n";
					BOOST_FOREACH(BasicBlock::BasicBlock* bb, this->blocks) {
						returnable << L"Start BasicBlock: \n";
						returnable << bb->ToString();
						returnable << L"End BasicBlock\n";
					}

					returnable << L"Links: \n";
					std::multimap<int, int>::iterator it;
					for (it = this->links.begin(); it != this->links.end(); it++) {
						returnable <<(*it).first;
						returnable << L", ";
						returnable << (*it).second;
						returnable << L"\n";
					}
					std::wstring returnableChar = returnable.str();
					return returnableChar;
				}

				/*
				*	FUNCTION: GetBlocks
				*	DESCRIPTION: Getter for the blocks instance member.
				*/
				std::list<BasicBlock::BasicBlock*> FlowGraph::GetBlocks()
				{
					return this->blocks;
				}
					
				/*
				*	FUNCTION: RemoveLastBlock
				*	DESCRIPTION: Removes last block which was inserted into the FlowGraph.
				*	USAGE: Used by ProgramNode to remove extra block at the end of the code.
				*/
				void FlowGraph::RemoveLastBlock()
				{
					this->blocks.pop_back();
				}
					
				/*
				*	FUNCTION: GetGlobalBlock
				*	DESCRIPTION: Getter for the globalblock instance member.
				*/
				BasicBlock::BasicBlock* FlowGraph::GetGlobalBlock()
				{
					return this->globalBlock;
				}
					
				/*
				*	FUNCTION: GetCurrBlock
				*	DESCRIPTION: Getter for the currblock instance member.
				*/
				int FlowGraph::GetCurrBlock()
				{
					return this->currBlock;
				}
					
				/*
				*	FUNCTION: SetCurrBlock
				*	DESCRIPTION: Setter for the currblock instance member.
				*/
				void FlowGraph::SetCurrBlock(int currBlock)
				{
					this->currBlock = currBlock;
				}

				/*
				*	FUNCTION: InsertInstruction
				*	PARAMETER 1: Instruction::Instruction* inst - Instruction to be added to FlowGraph
				*	DESCRIPTION: Adds FlowGraph to last BasicBlock that was added to the FlowGraph
				*/
				void FlowGraph::InsertInstruction(Instruction::Instruction* inst)
				{
					if (!this->inGlobalScope)
					{
						this->blocks.back()->InsertInstruction(inst);
					}
					else
					{
						this->globalBlock->InsertInstruction(inst);
					}
				}

				/*
				*	FUNCTION: ResetLastRd
				*	PARAMETER 1: Wstring rd - New value for the destination variable
				*	DESCRIPTION: Sets the destination variable of the last instruction in the last BasicBlock
				*		to rd.
				*/
				void FlowGraph::ResetLastRd(std::wstring rd)
				{
					if (!this->inGlobalScope)
					{
						this->blocks.back()->ResetLastRd(rd);
					}
					else
					{
						this->globalBlock->ResetLastRd(rd);
					}
				}	

				void FlowGraph::EnterFunction()
				{
					this->inGlobalScope = false;
					this->localVariables.push_back(boost::unordered_map<std::wstring, int>());
				}

				void FlowGraph::ExitFunction()
				{
					this->inGlobalScope = true;
				}

				/*
				*	FUNCTION: InsertNewBasicBlock
				*	PARAMETER 1: bool connect - Boolean value determining if new block is connected
				*	DESCRIPTION: Creates a new BasicBlock, and adding it to the end of the list.
				*		If connect is true, the new BasicBlock is connected to the original last BasicBlock
				*		in the list.
				*/
				void FlowGraph::InsertNewBasicBlock(bool connect) {
					if (this->blocks.back()->GetInstructions().size() > 0)
					{
						if (connect) 
						{
							this->links.insert(std::pair<int, int>(this->currBlock, this->currBlock + 1));
						}
						this->currBlock++;
						this->blocks.push_back(new BasicBlock::BasicBlock());
					}
				}

				/*
				*	FUNCTION: InsertFuncName
				*	PARAMETER 1: wstring funcname - Name of the function which is being evaluated.
				*	DESCRIPTION: Indicates that the last basic block which was inserted was in fact a
				*		function block, and sets it as such. Also stores the name in funcNmaes.
				*/
				void FlowGraph::InsertFuncName(std::wstring funcName)
				{
					this->funcNames.push_back(funcName);
					this->blocks.back()->SetFunction();
					if (ErrorHandler::GetInstance()->GetDebugCode() == 3)
					{
						wprintf(L"%s%s\n", L"FuncName = ", funcName);
					}
				}

				/*
				*	FUNCTION: InsertLink
				*	PARAMETER 1: int source - The basic block number which connects to target.
				*	PARAMETER 2: int target - The basic block which is being connected to.
				*	DESCRIPTION: Connects the two basic blocks indicated using an entry
				*		in the links table.
				*/
				void FlowGraph::InsertLink(int source, int target)
				{
					this->links.insert(std::pair<int, int>(source, target));
				}

				/*
				*	FUNCTION: AddGlobalVar
				*	PARAMETER 1: std::wstring var - Name of global variable being registered.
				*	DESCRIPTION: Adds global variable to list. This list is used to allocate
				*		memory for variables in the assembly code.
				*/
				void FlowGraph::AddGlobalVar(std::wstring var, int size)
				{
					this->globalVars[var] = size;
				}

				/*
				*	FUNCTION: AddLocalVar
				*	PARAMETER 1: std::wstring var - Name of global variable being registered.
				*	PARAMETER 2: int size - Size which should be allocated for the variable.
				*	DESCRIPTION: Adds local variable to list. This list is used to allocate
				*		memory for variables in the assembly code.
				*/
				void FlowGraph::AddLocalVar(std::wstring var, int size)
				{
					this->localVariables.back()[var] = size;
				}
				
				/*
				*	FUNCTION: InsertData
				*	PARAMETER 1: std::wstring data - Data which wil be referenced, and should be stored in assembly file.
				*	DESCRIPTION: Inserts data into list which will be stored in the assembly file. This function should return
				*		the number of the label at which the data will be stored.
				*/
				int FlowGraph::InsertData(std::wstring data)
				{
					this->data.push_back(data);
					return this->currDataLabel++;
				}
				
				/*
				*	FUNCTION:	AddStruct
				*	PARAMETER 1: std::wstring structname - Name of struct which is being added
				*/
				void FlowGraph::AddStruct(std::wstring structname)
				{
					this->structFieldPositions[structname] = std::list<std::pair<std::wstring, int> >();
				}

				/*
				*	FUNCTION AddStructField
				*	PARAMETER 1: std::wstring structname - Name of struct which the field being added belongs to.
				*	PARAMETER 2: std::wstring fieldname - Name of struct field which is being added.
				*	PARAMETER 3: int fieldpos - Offset from the struct start where this field should be.
				*/
				void FlowGraph::AddStructField(std::wstring structname, std::wstring fieldname, int fieldpos)
				{
					std::pair<std::wstring, int> p = std::pair<std::wstring, int>(fieldname, fieldpos);
					this->structFieldPositions[structname].push_back(p);
				}

				/*
				*	FUNCTION: GetStructFieldPos
				*	PARAMETER 1: std::wstring structname - Name of struct which is being queried.
				*	PARAMETER 2: std::wstring fieldname - Name of field which is being queried.
				*	DESCRIPTION: Returns the position of the given field inside of the given struct relative to the
				*		beginning of the struct.
				*/
				int FlowGraph::GetStructFieldPos(std::wstring structname, std::wstring fieldname)
				{
					std::list<std::pair<std::wstring, int> > fields = this->structFieldPositions[structname];
					std::list<std::pair<std::wstring, int> >::iterator itr;
					for(itr = fields.begin(); itr != fields.end(); itr++)
					{
						if (itr->first.compare(fieldname) == 0)
						{
							return itr->second;
						}
					}
					return -1;
				}

				/*
				*	FUNCTION: RemoveUselessMoves
				*	DESCRIPTION: Removes IR operations which moves values from one register to the same register.
				*				These are the results from assignments which are not used as values for other
				*				statements, and can be safely removed easily.
				*/
				void FlowGraph::RemoveUselessMoves(BasicBlock::BasicBlock* bb)
				{
					std::list<Instruction::Instruction*> removeableInstructions = std::list<Instruction::Instruction*>();
					BOOST_FOREACH(Instruction::Instruction* i, bb->GetInstructions())
					{
						if (i->op.compare(L"move") == 0 && i->rd.compare(i->rt) == 0)
						{
							removeableInstructions.push_back(i);
						}
					}
					BOOST_FOREACH(Instruction::Instruction* i, removeableInstructions)
					{
						bb->RemoveInstruction(i);
					}
				}

				/*
				*	FUNCTION: ReplaceIfs
				*	DESCRIPTION: Replaces any comparison followed by an if with the correct branching
				*				statement for that comparison. Since comparisons branch already, this
				*				removes an entire branching sequence from the compiled code.
				*/
				void FlowGraph::ReplaceIfs(BasicBlock::BasicBlock* bb)
				{
					std::list<Instruction::Instruction*> newBlockBody = std::list<Instruction::Instruction*>();
					Instruction::Instruction* lastInst = new Instruction::Instruction();
					BOOST_FOREACH(Instruction::Instruction* i, bb->GetInstructions())
					{
						if(lastInst->op.compare(L">") == 0 && i->op.compare(L"if") == 0 && lastInst->rd.compare(i->rd) == 0)
						{
							//Replace with blte
							newBlockBody.push_back(new Instruction::Instruction(L"blte", L"", lastInst->rt, lastInst->rs, lastInst->label));
							lastInst = new Instruction::Instruction();
						}
						else if(lastInst->op.compare(L">=") == 0 && i->op.compare(L"if") == 0 && lastInst->rd.compare(i->rd) == 0) 
						{
							//Replace with blt
							newBlockBody.push_back(new Instruction::Instruction(L"blt", L"", lastInst->rt, lastInst->rs, lastInst->label));
							lastInst = new Instruction::Instruction();
						}
						else if(lastInst->op.compare(L"<") == 0 && i->op.compare(L"if") == 0 && lastInst->rd.compare(i->rd) == 0)
						{
							//Replace with bgte
							newBlockBody.push_back(new Instruction::Instruction(L"bgte", L"", lastInst->rt, lastInst->rs, lastInst->label));
							lastInst = new Instruction::Instruction();
						}
						else if(lastInst->op.compare(L"<=") == 0 && i->op.compare(L"if") == 0 && lastInst->rd.compare(i->rd) == 0) 
						{
							//Replace with bgt
							newBlockBody.push_back(new Instruction::Instruction(L"bgt", L"", lastInst->rt, lastInst->rs, lastInst->label));
							lastInst = new Instruction::Instruction();
						}
						else if(lastInst->op.compare(L"==") == 0 && i->op.compare(L"if") == 0 && lastInst->rd.compare(i->rd) == 0)
						{
							//Replace with bne
							newBlockBody.push_back(new Instruction::Instruction(L"bne", L"", lastInst->rt, lastInst->rs, lastInst->label));
							lastInst = new Instruction::Instruction();
						}
						else if(lastInst->op.compare(L"!=") == 0 && i->op.compare(L"if") == 0 && lastInst->rd.compare(i->rd) == 0) 
						{
							//Replace with beq
							newBlockBody.push_back(new Instruction::Instruction(L"beq", L"", lastInst->rt, lastInst->rs, lastInst->label));
							lastInst = new Instruction::Instruction();
						}
						else if (lastInst->op.compare(L"") != 0)
						{
							newBlockBody.push_back(lastInst);
							lastInst = i;
						}
						else
						{
							lastInst = i;
						}
					}
					if (lastInst->op.compare(L"") != 0)
					{
						newBlockBody.push_back(lastInst);
					}
					bb->SetInstructions(newBlockBody);
				}
				
				
				/*
				*	FUNCTION: ReplaceUselessStackOps
				*	DESCRIPTION: Replaces any pops and pushes of registers which are not used between the two operations. 
				*				Since if the registers are not used, the pushes and pops are not needed to verify correct
				*				usage of the system.
				*	NOTE:		Assumes all register uses will be explicitly defined (aka *tmp and *tmp2). If we start using
				*				registers like rr or *tmp3, we have issues.
				*/
				void FlowGraph::ReplaceUselessStackOps(BasicBlock::BasicBlock* bb)
				{
					std::list<Instruction::Instruction*> newBlockBody = std::list<Instruction::Instruction*>();
					BOOST_FOREACH(Instruction::Instruction* inst, bb->GetInstructions())
					{
						if (inst->op.compare(L"push") == 0)
						{
							bool found = false;
							BOOST_FOREACH(Instruction::Instruction* inst2, bb->GetInstructions())
							{
								if (inst == inst2)
								{
									found = true;
								}
								else if (found)
								{
									if (inst2->op.compare(L"pop") == 0 && inst2->rd.compare(inst->rt) == 0)
									{
										found = false;
										inst->op = L"";
										inst2->op = L"";
									}
									else if (inst2->rd.compare(inst->rt) == 0 || inst2->rt.compare(inst->rt) == 0 || inst2->rs.compare(inst->rt) == 0)
									{
										break;
									}
								}
							}
							if (inst->op.compare(L"") != 0)
							{
								newBlockBody.push_back(inst);
							}
						}
						else if (inst->op.compare(L"") != 0)
						{
							newBlockBody.push_back(inst);
						}
					}
					bb->SetInstructions(newBlockBody);
				}

				/*
				*	FUNCTION: Optimize
				*	DESCRIPTION: Goes through each individual IR instruction in the flowgraph, optimizing the code
				*				as necessary. Each individual optimization is in a separate function, and is documented
				*				there.
				*/
				void FlowGraph::Optimize()
				{
					this->RemoveUselessMoves(this->globalBlock);
					this->ReplaceIfs(this->globalBlock);
					this->ReplaceUselessStackOps(this->globalBlock);
					BOOST_FOREACH(BasicBlock::BasicBlock* bb, this->blocks)
					{
						this->RemoveUselessMoves(bb);
						this->ReplaceIfs(bb);
						this->ReplaceUselessStackOps(bb);
					}
				}

				/*
				*	FUNCTION: GenerateCode
				*	DESCRIPTION: Manages the creation of code from all of the basic blocks
				*		contained in the current FlowGraph. Space in the stack is allocated
				*		for each function, and locations are kept track of, and are then
				*		passed into the GenerateCode for the BasicBlock class.
				*/
				std::wstring FlowGraph::GenerateCode() {
					if(ErrorHandler::GetInstance()->GetDebugCode() == 4)
					{
						wprintf(L"Entering Generate Code.\n");
					}
					// Get list of variables for each function.
					std::list<boost::unordered_map<std::wstring, int> > funcVariables = this->localVariables;

					// Generate Code
					int blockNum = 0;
					std::wstringstream ss;
					int latestLabel = (int) this->blocks.size();

					boost::unordered_map<std::wstring, int> variableMemLoc;
					boost::unordered_map<std::wstring, int> globalMemLoc;
					int globalAllocNum = 0;
					int numWord = 0;
					boost::unordered_map<std::wstring, int>::iterator itr;
					for(itr = this->globalVars.begin(); itr != this->globalVars.end(); itr++)
					{
						globalAllocNum += itr->second;
						globalMemLoc[itr->first] = globalAllocNum;
					}
					int allocNum = 0;
					BOOST_FOREACH(BasicBlock::BasicBlock* bb, this->blocks) {
						if (bb->GetFunction())
						{
							//Create Register and Memory Assignments for function.
							allocNum = 2*NUMSREGS + 5; // Save room for $fp, # of parameters, and $ra.
							variableMemLoc.clear();
							boost::unordered_map<std::wstring, int>::iterator itr2;
							for(itr2 = funcVariables.front().begin(); itr2 != funcVariables.front().end(); itr2++)
							{
								if (variableMemLoc.count(itr2->first) == 0)
								{
									allocNum += itr2->second;
									variableMemLoc[itr2->first] = allocNum;
								}
							}
							funcVariables.pop_front();
							if(ErrorHandler::GetInstance()->GetDebugCode() == 4)
							{
								std::cout << "Initialized VariableMemLoc to: \n";
								boost::unordered_map<std::wstring, int>::iterator iterate;
								for(iterate = variableMemLoc.begin(); iterate != variableMemLoc.end(); iterate++)
								{
									wprintf(L"%s -> %d\n", (*iterate).first.c_str(), (*iterate).second);
								}
							}
						}

						int target = this->GetTarget(blockNum);
						std::wstring targetLabel = L"";
						if (target != -1)
						{
							std::wstringstream sstarget;
							sstarget << L"L";
							sstarget << target;
							targetLabel = sstarget.str();
						}

						if (bb->GetFunction())
						{
							if (ErrorHandler::GetInstance()->GetDebugCode() == 4)
							{
								wprintf(L"target = \n%d\nfuncNames.size() = \n%d\n", target, funcNames.size());
							}
							ss << bb->GenerateCode(variableMemLoc, globalMemLoc, allocNum - 1, globalAllocNum, funcNames.front(), targetLabel, this->globalBlock, &latestLabel, &numWord);
							funcNames.pop_front();
						} 
						else
						{
							std::wstringstream ssstart;
							ssstart << L"L";
							ssstart << blockNum;
							std::wstring startLabel = ssstart.str();
							std::wstring tmp = bb->GenerateCode(variableMemLoc, globalMemLoc, allocNum - 1, globalAllocNum, startLabel, targetLabel, this->globalBlock, &latestLabel, &numWord);
							ss << tmp;
							int tmp_int = ss.str().size();
						}
 						blockNum++;
					}
					
					if (this->currDataLabel > 0)
					{
						ss << L".data\n";
					}
					for(int i = 0; i < this->currDataLabel; i++)
					{
						ss << L"D" << i << L":\n";
						for(int j = 0; j < (int) this->data.front().size() + 1; j++)
						{
							char c = (this->data.front().c_str())[j];
							if (c == 0)
							{
								ss << L"\\0\n";
							}
							else
							{
								ss << (this->data.front().c_str())[j] << L"\n";
							}
						}
						this->data.pop_front();

					}
					if(ErrorHandler::GetInstance()->GetDebugCode() == 4)
					{
						std::cout << "Exiting Generate Code.\n";
					}
					std::wstring returnable = ss.str();
					return returnable;
				}

				/*
				*	FUNCTION: IsConnectedTo
				*	PARAMETER 1: int blockNum - The basic block number which is under question.
				*	DESCRIPTION: Looking through all recorded links, this function determines if
				*		the requested basic block is connected to by any other basic block. 
				*		If not, it is assumed that this block is a function block, although
				*		a corrupted FlowGraph could give this result.
				*/
				bool FlowGraph::IsConnectedTo(int blockNum) {
					if(ErrorHandler::GetInstance()->GetDebugCode() == 4) {
						std::cout << "Entering IsConnectedTo.\n";
					}
					std::multimap<int, int>::iterator it;
					for(it = this->links.begin(); it != this->links.end(); it++) {
						if ((*it).second == blockNum) {
							if(ErrorHandler::GetInstance()->GetDebugCode() == 4) {
								std::cout << "Exiting IsConnectedTo.\n";
							}
							return true;
						}
					}
					if(ErrorHandler::GetInstance()->GetDebugCode() == 4) {
						std::cout << "Exiting IsConnectedTo.\n";
					}
					return false;
				}

				/*
				*	FUNCTION: GetTarget
				*	PARAMETER 1: int blockNum - The basic block number which is under question.
				*	DESCRIPTION: Looking through all recorded links, this function determines the
				*		basic block which the requested block is connected to, but not next to.
				*		Such connections are present in branches and jumps. If no such link is found,
				*		the function returns -1.
				*/
				int FlowGraph::GetTarget(int blockNum) {
					if(ErrorHandler::GetInstance()->GetDebugCode() == 4) {
						std::cout << "Entering GetTarget with blockNum = " << blockNum  << " " << this->links.size() << ".\n";
					}
					int target = -1;
					std::multimap<int, int>::iterator it;

					std::pair<std::multimap<int, int>::iterator, std::multimap<int, int>::iterator> ret = this->links.equal_range(blockNum);
					for(it = ret.first; it != ret.second; ++it) {
						if ((*it).second - (*it).first != 1) {
							target = (*it).second;
							break;
						}
					}
					if(ErrorHandler::GetInstance()->GetDebugCode() == 4) {
						std::cout << "Exiting GetTarget.\n";
					}
					return target;	  
				}

				/*
				*	FUNCTION: GetFuncVariables
				*	DESCRIPTION: Looking through all of the basic blocks, it determines which ones
				*		are function declarations (using IsConnectedTo), and then calls GetVariables
				*		on each basic block to get its variables. These variables are separated into
				*		lists based on which function they belong to (a function will have consecutive
				*		basic blocks), and this list of lists of function names is returned.
				*/                   
				std::list<std::list<std::wstring> > FlowGraph::GetFuncVariables()
				{
					std::list<std::list<std::wstring> > funcVariables = std::list<std::list<std::wstring> >();
					int blockNum = 0;
					BOOST_FOREACH(BasicBlock::BasicBlock* bb, this->blocks)
					{
						if (!IsConnectedTo(blockNum))
						{
							funcVariables.push_back(std::list<std::wstring>());
						}
						std::list<std::wstring> returned = bb->GetVariables(funcVariables.back());
						if(ErrorHandler::GetInstance()->GetDebugCode() == 4)
						{
							std::cout << "Variables: \n";
							BOOST_FOREACH(std::wstring var, returned)
							{
								wprintf(L"%s\n", var.c_str());
							}
						}
						funcVariables.pop_back();
						returned.unique();
						boost::unordered_map<std::wstring, int>::iterator itr;
						for(itr = this->globalVars.begin(); itr != this->globalVars.end(); itr++)
						{
							returned.remove(itr->first);
						}
						funcVariables.push_back(returned);
						blockNum++;
					}
					return funcVariables;
				}

			}
		}
	}

}
