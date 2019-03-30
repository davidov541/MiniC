#include "BasicBlock.h"
#include "stdafx.h"

namespace MiniC {
	namespace IR {
		namespace Epicness {
			namespace BasicBlock {

				/*
				*	FUNCTION: BasicBlock
				*	PARAMETER 1: BasicBlock& bn - BasicBlock object to copy
				*	DESCRIPTION: Copy constructor for BasicBlock
				*/
				BasicBlock::BasicBlock(BasicBlock& bn) {
					this->body = bn.body;
					this->funcDecl = bn.funcDecl;
				}

				/*
				*	FUNCTION: BasicBlock
				*	DESCRIPTION: Default constructor for BasicBlock
				*/
				BasicBlock::BasicBlock() {
					this->funcDecl = false;
					this->funcDecl = 0;
				}

				/*
				*	FUNCTION: BasicBlock
				*	PARAMETER 1: std::list<Instruction::Instruction*> insts - List of instructions 
				*		which are contained in the BasicBlock object
				*	DESCRIPTION: Default constructor for BasicBlock
				*/
				BasicBlock::BasicBlock(std::list<Instruction::Instruction*> insts) {
					this->body = insts;
					this->funcDecl = 0;
					this->funcDecl = false;
				}
			
				/*
				*	FUNCTION: ~BasicBlock
				*	DESCRIPTION: Destructor for BasicBlock
				*/
				BasicBlock::~BasicBlock()
				{
					BOOST_FOREACH(MiniC::IR::Instruction::Instruction* i, this->body)
					{
						if (i)
						{
							delete i;
						}
					}
				}

				/*
				*	FUNCTION: GetInstructions
				*	DESCRIPTION: Getter function for body private member.
				*/
				std::list<Instruction::Instruction*> BasicBlock::GetInstructions()
				{
					return this->body;
				}

				/*
				*	FUNCTION: RemoveInstruction
				*	PARAMETER 1: Instruction::Instruction* i - Instruction to be removed from
				*				the body.
				*	DESCRIPTION: Removes given instruction from body member.
				*/
				void BasicBlock::RemoveInstruction(Instruction::Instruction* i)
				{
					this->body.remove(i);
				}

				/*
				*	FUNCTION: SetInstructions
				*	PARAMETER 1: std::list<Instruction::Instruction*> insts - New body to replace itself with.
				*	DESCRIPTION: Replaces the current basic block body with insts.
				*/
				void BasicBlock::SetInstructions(std::list<Instruction::Instruction*> insts)
				{
					this->body = insts;
				}

				/*
				*	FUNCTION: ToString
				*	DESCRIPTION: Returns WString containing description of BasicBlock, including a list of
				*		all of the instructions which the BasicBlock contains.
				*/
				std::wstring BasicBlock::ToString() {
					std::wstringstream returnable;
					BOOST_FOREACH(MiniC::IR::Instruction::Instruction* i, this->body) {
						returnable << i->ToString();
						returnable << L"\n";
					}
					std::wstring returnableChar = returnable.str();
					return returnableChar;
				}

				/*
				*	FUNCTION: Equals
				*	DESCRIPTION: Returns true if the BasicBlock has the same instructions in it as the argument
				*		the function is passed. It will return false if this is not the case.
				*/
				bool BasicBlock::Equals(BasicBlock* b2)
				{
					if (this->body.size() != b2->body.size())
					{
						return false;
					}
					std::list<Instruction::Instruction*>::iterator itr, itr2;
					for(itr = this->body.begin(), itr2 = b2->body.begin(); itr != this->body.end() && itr2 != b2->body.end(); itr++, itr2++)
					{
						if ((*itr)->ToString().compare((*itr2)->ToString()) != 0)
						{
							return false;
						}
					}
					return true;
				}

				/*
				*	FUNCTION: InsertInstruction
				*	PARAMETER 1: Instruction::Instruction* inst - Instruction to be added to basic block.
				*	DESCRIPTION: Inserts instruction inst into the list of instructions in the BasicBlock object.
				*/
				void BasicBlock::InsertInstruction(Instruction::Instruction* inst) {
					this->body.push_back(inst);
				}

				/*
				*	FUNCTION: SetFunction
				*	DESCRIPTION: Declares that this BasicBlock contains a function declaration.
				*/
				void BasicBlock::SetFunction() {
					this->funcDecl = 1;
				}

				/*
				*	FUNCTION: GetFunction
				*	DESCRIPTION: Returns whether this is a function declaration or not.
				*/
				bool BasicBlock::GetFunction() {
					return this->funcDecl;
				}

				/*
				*	FUNCTION: ResetLastRd
				*	PARAMETER 1: WString representing the variable to which the last instruction's 
				*		destination should be assigned to.
				*	DESCRIPTION: Reassigns the destination location for the last instruction in the 
				*		BasicBlock to str. This is used when the BasicBlock is being created, helping
				*		deal with destination registers during assignments and operations.
				*/
				void BasicBlock::ResetLastRd(std::wstring str) {
					this->body.back()->rd = str;
				}

				/*
				*	FUNCTION: GetVariables
				*	PARAMETER 1: List of WStrings which the BasicBlock's variables should be appended to.
				*	DESCRIPTION: Appends any variables which are used or assigned to in GetVariables to
				*		the list currVariables. The list is then ensured that it is unique, and temporary
				*		variables are removed.
				*/
				std::list<std::wstring> BasicBlock::GetVariables(std::list<std::wstring> currVariables)
				{
					if(ErrorHandler::GetInstance()->GetDebugCode() == 4)
					{
						wprintf(L"Entering GetVariables.\n");
					}
					BOOST_FOREACH(MiniC::IR::Instruction::Instruction* i, this->body)
					{
						if (i->op.compare(L"formal") == 0 || i->op.compare(L"loadi") == 0 || i->op.compare(L"param") == 0 || i->op.compare(L"print") == 0 || i->op.compare(L"rp") == 0 || i->op.compare(L"if") == 0 || i->op.compare(L"funccall") == 0)
						{		
							currVariables.push_back(i->rd);
						} 
						else if (i->op.compare(L"load") == 0 || i->op.compare(L"store") == 0)
						{ 
							currVariables.push_back(i->rd);
							currVariables.push_back(i->rt);
						}
						else if (i->op.compare(L"jr") == 0)
						{
							currVariables.push_back(i->rs);
						}
						else if(i->op.compare(L"==") == 0 || i->op.compare(L"!=") == 0 || i->op.compare(L"<") == 0 || i->op.compare(L"<=") == 0 || i->op.compare(L">") == 0 || i->op.compare(L">=") == 0)
						{
							currVariables.push_back(i->rd);
							currVariables.push_back(i->rt);
							currVariables.push_back(i->rs);
						}
						else if(i->op.compare(L"+") == 0 || i->op.compare(L"-") == 0)
						{
							currVariables.push_back(i->rs);
							currVariables.push_back(i->rt);
						}
						else if (i->op.compare(L"u-") == 0 || i->op.compare(L"u~") == 0)
						{
							currVariables.push_back(i->rd);
							currVariables.push_back(i->rs);
						}
					}
					if(ErrorHandler::GetInstance()->GetDebugCode() == 4)
					{
						wprintf(L"Exiting GetVariables.\n");
					}
					currVariables.unique();
					currVariables.remove(L"");
					currVariables.remove(L"*tmp");
					currVariables.remove(L"*tmp2");
					currVariables.remove(L"tmp3");
					currVariables.remove(L"rr");
					return currVariables;
				}

				/*
				*	FUNCTION: GenerateCode
				*	PARAMETER 1: Mapping of variable to actual register names. Currently, these only contain temporary registers.
				*	PARAMETER 2: Mapping of variable to location in stack relative to stack pointer value. 
				*	PARAMETER 3: Amount of room to allocate on the stack for the BasicBlock.
				*	PARAMETER 4: Code which modifies the stack appropriately at the beginning of a function.
				*	PARAMETER 5: Label which should be present at the beginning of the code.
				*	PARAMETER 6: Label to which the BasicBlock should jump at the end. May be NULL, if a jr is present.
				*	DESCRIPTION: Appends any variables which are used or assigned to in GetVariables to
				*		the list currVariables. The list is then ensured that it is unique, and temporary
				*		variables are removed.
				*/
				std::wstring BasicBlock::GenerateCode(boost::unordered_map<std::wstring, int> mem, boost::unordered_map<std::wstring, int> globalMem, int allocSize, int globalAllocSize, std::wstring startLabel, std::wstring endLabel, BasicBlock* globalAllocBlock, int* latestLabel, int* numWord) {
					if(ErrorHandler::GetInstance()->GetDebugCode() == 4)
					{
						wprintf(L"Entering BasicBlock::GenerateCode.\n");
					}
					std::wstringstream code;
					bool first = true;
					int currParam = 0;
					int currFormal = 0;
					bool foundBranch = false;
					
					boost::unordered_map<std::wstring, std::wstring> reg;
					reg[L"*tmp"] = L"$k0";
					reg[L"*tmp2"] = L"$k1";
					reg[L"*tmp3"] = L"$k2";
					reg[L"rr"] = L"$rr";
					reg[L"*v"] = L"$v";

					BOOST_FOREACH(Instruction::Instruction* i, this->body) 
					{
						if (ErrorHandler::GetInstance()->GetDebugCode() == 4)
						{
							wprintf(L"%s %s\n", L"Evaluating Instruction", i->ToString());
						}
						int tmp_int = code.str().size();
						code << L"//";
						code << i->ToString();
						code << L"\n";
						if (first) 
						{
							code << startLabel;
							code << L":";
							first = false;
						}
						if (i->op.compare(L"funcdecl") == 0) 
						{
							if (startLabel.compare(L"mainint") == 0)
							{
								PRINTWORDNUM();
								code << L"addi $sp, ";
								code << globalAllocSize;
								code << L"\n";
								PRINTWORDNUM();
								code << L"move $gp, $rr\n";
								PRINTWORDNUM();
								code << L"move $sp, $rr\n";
								code << globalAllocBlock->GenerateCode(mem, globalMem, allocSize, globalAllocSize, L"global", endLabel, new BasicBlock(), latestLabel, numWord);
							}
							/* Stack Structure:
							*
							*		$fp, $sp ->	|		|
							*					|		|
							*			 		|  $ra	|
							*			 		|  $ra	|
							*					|old $fp|
							*					|old $fp|
							*					|#Formal|
							*					|  $s0	|
							*					|  $s0  |
							*					|  $s1	|
							*					|  $s1	|
							*					|  $s2	|
							*					|  $s2	|
							*		old $sp ->	|  $s3	|
							*					|  $s3	|
							*					|  ...  |
							*		old $fp ->	|		|
							*
							*/
							PRINTWORDNUM();
							code << L"addi $sp, ";
							code << allocSize + 1;
							code << L"\n";
							PRINTWORDNUM();
							code << L"move $sp, $rr\n";
							PRINTWORDNUM();
							code << L"addi $0, -2\n";
							PRINTWORDNUM();
							code << L"sdw $ra, $sp, $rr\n";
							PRINTWORDNUM();
							code << L"addi $rr, -2\n";
							PRINTWORDNUM();
							code << L"sdw $fp, $sp, $rr\n";
							PRINTWORDNUM();
							code << L"move $fp, $sp\n";
							PRINTWORDNUM();
							code << L"addi $rr, -1\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"ldi " << reg[L"*tmp3"] << L", " << i->rd << L"\n";
							PRINTWORDNUM();
							code << L"swn " << reg[L"*tmp3"] << L", $fp, $rr\n";
							for(int j = 0; j < NUMSREGS; j++) 
							{
								PRINTWORDNUM();
								code << L"addi $rr, -2\n";
								PRINTWORDNUM();
								code << L"sdw $s";
								code << j;
								code << L", $fp, $rr\n";
							}
						} 
						else if (i->op.compare(L"funcend") == 0)
						{
							PRINTWORDNUM();
							code << L"addi $0, -2\n";
							PRINTWORDNUM();
							code << L"ldw $ra, $fp, $rr\n";
							PRINTWORDNUM();
							code << L"addi $rr, -5\n";
							for(int j = 0; j < NUMSREGS; j++) 
							{
								if (j != 0)
								{
									PRINTWORDNUM();
									code << L"addi $rr, -2\n";
								}
								PRINTWORDNUM();
								code << L"ldw $s";
								code << j;
								code << L", $fp, $rr\n";
							}
							PRINTWORDNUM();
							code << L"addi $fp, -";
							code << allocSize + 1;
							code << L"\n";
							PRINTWORDNUM();
							code << L"move $sp, $rr\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"ldi $k0, -4\n";
							PRINTWORDNUM();
							code << L"ldw $fp, $fp, $k0\n";
							PRINTWORDNUM();
							code << L"jr $ra\n";
							foundBranch = true;
						}
						else if (i->op.compare(L"formal") == 0) 
						{
							if (currFormal == 0)
							{
								PRINTWORDNUM();
								code << L"ldw ";
								code << reg[L"*tmp3"];
								code << L", $a, $0\n";
								currFormal++;
							}
							else
							{
								PRINTWORDNUM();
								PRINTWORDNUM();
								code << L"ldi ";
								code << reg[L"*tmp3"];
								code << L", ";
								code << 2*(currFormal++);
								code << L"\n";
								PRINTWORDNUM();
								code << L"ldw ";
								code << reg[L"*tmp3"];
								code << L", $a, ";
								code << reg[L"*tmp3"];
								code << L"\n";
							}
							PRINTWORDNUM();
							code << L"addi $0, -";
							code << mem[i->rd];
							code << L"\n";
							PRINTWORDNUM();
							code << L"sdw ";
							code << reg[L"*tmp3"];
							code << L", $fp, $rr\n";
						} 
						else if (i->op.compare(L"load") == 0) 
						{
							if (mem.count(i->rt) > 0)
							{
								PRINTWORDNUM();
								PRINTWORDNUM();
								code << L"ldi ";
								code << reg[L"*tmp3"];
								code << L", -";
								code << mem[i->rt] - 2*wtoi(i->rs.c_str());
								code << L"\n";
								PRINTWORDNUM();
								code << L"ldw ";
								code << reg[i->rd];
								code << L", $fp, ";
								code << reg[L"*tmp3"];
								code << L"\n";
							}
							else
							{
								PRINTWORDNUM();
								code << L"addi $gp, -";
								code << globalMem[i->rt] - 2*wtoi(i->rs.c_str());
								code << L"\n";
								PRINTWORDNUM();
								code << L"ldw ";
								code << reg[i->rd];
								code << L", $0, $rr\n";
							}
						} 
						else if (i->op.compare(L"store") == 0)
						{
							if (mem.count(i->rd) > 0)
							{
								PRINTWORDNUM();
								PRINTWORDNUM();
								code << L"ldi ";
								code << reg[L"*tmp3"];
								code << L", -";
								code << mem[i->rd] - 2*wtoi(i->rs.c_str());
								code << L"\n";
								PRINTWORDNUM();
								code << L"sdw ";
								code << reg[i->rt];
								code << L", $fp, ";
								code << reg[L"*tmp3"];
								code << L"\n";
							}
							else
							{
								PRINTWORDNUM();
								code << L"addi $gp, -";
								code << globalMem[i->rd] - 2*wtoi(i->rs.c_str());
								code << L"\n";
								PRINTWORDNUM();
								code << L"sdw ";
								code << reg[i->rt];
								code << L", $0, $rr\n";
							}
						} 
						else if (i->op.compare(L"loadi") == 0)
						{
							int val = wtoi(i->rt.c_str());
							if (val <= pow((long double) 2, 15) + 1 && val >= -1 * pow((long double) 2, 15))
							{
								PRINTWORDNUM();
								PRINTWORDNUM();
								code << L"ldi ";
								code << reg[i->rd];
								code << L", ";
								code << i->rt;
								code << L"\n";
							}
							else
							{
								int LSB = val & 0x0000FFFF;
								int MSB = val >> 16;
								PRINTWORDNUM();
								PRINTWORDNUM();
								code << L"ldl $at, ";
								code << LSB;
								code << L"\n";
								PRINTWORDNUM();
								PRINTWORDNUM();
								code << L"ldl ";
								code << reg[i->rd];
								code << L", ";
								code << MSB;
								code << L"\n";
								PRINTWORDNUM();
								code << L"slli ";
								code << reg[i->rd];
								code << L", 16\n";
								PRINTWORDNUM();
								code << L"add $at, $rr\n";
								PRINTWORDNUM();
								code << L"move ";
								code << reg[i->rd];
								code << L", $rr\n";
							}
						} 
						else if (i->op.compare(L"param") == 0) 
						{
							if (currParam == 0)
							{
								PRINTWORDNUM();
								code << L"sdw ";
								code << reg[i->rd];
								code << L", $sp, $0\n";
								currParam++;
							}
							else
							{
								PRINTWORDNUM();
								PRINTWORDNUM();
								code << L"ldi ";
								code << reg[L"*tmp3"];
								code << L", ";
								code << 2*(currParam++);
								code << L"\n";
								PRINTWORDNUM();
								code << L"sdw ";
								code << reg[i->rd];
								code << L", $sp, ";
								code << reg[L"*tmp3"];
								code << L"\n";
							}
						} 
						else if (i->op.compare(L"print") == 0) 
						{
							PRINTWORDNUM();
							code << L"wp ";
							code << reg[i->rd];
							code << L", 0\n";
						} 
						else if (i->op.compare(L"rp") == 0) 
						{
							PRINTWORDNUM();
							code << L"rp ";
							code << reg[i->rd];
							code << L"\n";
						} 
						else if (i->op.compare(L"funccall") == 0) 
						{
							PRINTWORDNUM();
							code << L"addi $sp, ";
							code << currParam*2;
							code << L"\n";
							PRINTWORDNUM();
							code << L"move $a, $sp\n";
							PRINTWORDNUM();
							code << L"move $sp, $rr\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << L", ";
							code << i->rt;
							code << L"\n";
							PRINTWORDNUM();
							code << L"jalr ";
							code << reg[L"*tmp3"];
							code << L"\n";
							if (i->rd.compare(L"") != 0)
							{
								PRINTWORDNUM();
								code << L"move ";
								code << reg[i->rd];
								code << L", $v\n";
							}
							PRINTWORDNUM();
							code << L"addi $sp, -";
							code << 2*currParam;
							code << L"\n";
							PRINTWORDNUM();
							code << L"move $sp, $rr\n";
							currParam = 0;
						} 
						else if (i->op.compare(L"jr") == 0) 
						{
							PRINTWORDNUM();
							code << L"move $v, ";
							code << reg[i->rs];
							code << L"\n";
							PRINTWORDNUM();
							code << L"addi $0, -2\n";
							PRINTWORDNUM();
							code << L"ldw $ra, $fp, $rr\n";
							PRINTWORDNUM();
							code << L"addi $rr, -3\n";
							for(int j = 0; j < NUMSREGS; j++) 
							{
								PRINTWORDNUM();
								code << L"addi $rr, -2\n";
								PRINTWORDNUM();
								code << L"ldw $s";
								code << j;
								code << L", $fp, $rr\n";
							}
							PRINTWORDNUM();
							code << L"addi $fp, -";
							code << allocSize + 1;
							code << L"\n";
							PRINTWORDNUM();
							code << L"move $sp, $rr\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"ldi $k0, -4\n";
							PRINTWORDNUM();
							code << L"ldw $fp, $fp, $k0\n";
							PRINTWORDNUM();
							code << L"jr $ra\n";
							foundBranch = true;
						} 
						else if(i->op.compare(L"nop") == 0) 
						{
							PRINTWORDNUM();
							code << L"nop\n";
						} 
						else if(i->op.compare(L"==") == 0) 
						{
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << ", L";
							code << (*latestLabel)++;
							code << L"\n";
							PRINTWORDNUM();
							code << L"beq ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L", ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"ldi ";
							code << reg[i->rd];
							code << L", 0\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << L", L";
							code << (*latestLabel);
							code << L"\n";
							PRINTWORDNUM();
							code << L"jr ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"L";
							code << (*latestLabel) - 1;
							code << L":ldi ";
							code << reg[i->rd];
							code << L", 1\n";
							code << L"L";
							code << (*latestLabel)++;
							code << L":\n";
						} 
						else if (i->op.compare(L"!=") == 0) 
						{
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << ", L";
							code << (*latestLabel)++;
							code << L"\n";
							PRINTWORDNUM();
							code << L"bne ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L", ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"ldi ";
							code << reg[i->rd];
							code << L", 0\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << L", L";
							code << (*latestLabel);
							code << L"\n";
							PRINTWORDNUM();
							code << L"jr ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"L";
							code << (*latestLabel) - 1;
							code << L":ldi ";
							code << reg[i->rd];
							code << L", 1\n";
							code << L"L";
							code << (*latestLabel)++;
							code << L":\n";
						} 
						else if (i->op.compare(L"if") == 0) 
						{
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << L", ";
							code << endLabel;
							code << L"\n";
							PRINTWORDNUM();
							code << L"beq ";
							code << reg[i->rd];
							code << L", $0, ";
							code << reg[L"*tmp3"];
							code << L"\n";
							foundBranch = true;
						} 
						else if (i->op.compare(L"ifnot") == 0) 
						{
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << L", ";
							code << endLabel;
							code << L"\n";
							PRINTWORDNUM();
							code << L"bne ";
							code << reg[i->rd];
							code << L", $0, ";
							code << reg[L"*tmp3"];
							code << L"\n";
							foundBranch = true;
						} 
						else if (i->op.compare(L"beq") == 0) 
						{
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << L", ";
							code << endLabel;
							code << L"\n";
							PRINTWORDNUM();
							code << L"beq ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L", ";
							code << reg[L"*tmp3"];
							code << L"\n";
							foundBranch = true;
						} 
						else if (i->op.compare(L"bne") == 0) 
						{
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << L", ";
							code << endLabel;
							code << L"\n";
							PRINTWORDNUM();
							code << L"bne ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L", ";
							code << reg[L"*tmp3"];
							code << L"\n";
							foundBranch = true;
						} 
						else if (i->op.compare(L"bgt") == 0) 
						{
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << L", ";
							code << endLabel;
							code << L"\n";
							PRINTWORDNUM();
							code << L"bgt ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L", ";
							code << reg[L"*tmp3"];
							code << L"\n";
							foundBranch = true;
						} 
						else if (i->op.compare(L"bgte") == 0) 
						{
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << L", ";
							code << endLabel;
							code << L"\n";
							PRINTWORDNUM();
							code << L"bgt ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L", ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							code << L"beq ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L", ";
							code << reg[L"*tmp3"];
							code << L"\n";
							foundBranch = true;
						} 
						else if (i->op.compare(L"blt") == 0) 
						{
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << L", ";
							code << endLabel;
							code << L"\n";
							PRINTWORDNUM();
							code << L"blt ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L", ";
							code << reg[L"*tmp3"];
							code << L"\n";
							foundBranch = true;
						} 
						else if (i->op.compare(L"blte") == 0) 
						{
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << L", ";
							code << endLabel;
							code << L"\n";
							PRINTWORDNUM();
							code << L"blt ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L", ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							code << L"beq ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L", ";
							code << reg[L"*tmp3"];
							code << L"\n";
							foundBranch = true;
						} 
						else if (i->op.compare(L"+") == 0) 
						{
							PRINTWORDNUM();
							code << L"add ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L"\n";
							PRINTWORDNUM();
							code << L"move ";
							code << reg[i->rd];
							code << L", ";
							code << reg[L"rr"];
							code << L"\n";
						} 
						else if (i->op.compare(L"-") == 0) 
						{
							PRINTWORDNUM();
							code << L"sub ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L"\n";
							PRINTWORDNUM();
							code << L"move ";
							code << reg[i->rd];
							code << L", ";
							code << reg[L"rr"];
							code << L"\n";
						} 
						else if (i->op.compare(L"&") == 0) 
						{
							PRINTWORDNUM();
							code << L"and ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L"\n";
							PRINTWORDNUM();
							code << L"move ";
							code << reg[i->rd];
							code << L", ";
							code << reg[L"rr"];
							code << L"\n";
						} 
						else if (i->op.compare(L"|") == 0) 
						{
							PRINTWORDNUM();
							code << L"or ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L"\n";
							PRINTWORDNUM();
							code << L"move ";
							code << reg[i->rd];
							code << L", ";
							code << reg[L"rr"];
							code << L"\n";
						} 
						else if (i->op.compare(L"&&") == 0)
						{
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << L", L";
							code << (*latestLabel)++;
							code << L"\n";
							PRINTWORDNUM();
							code << L"beq $0, ";
							code << reg[i->rt];
							code << L", ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							code << L"beq $0, ";
							code << reg[i->rs];
							code << L", ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"ldi ";
							code << reg[i->rd];
							code << L", 1\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << L", L";
							code << (*latestLabel)++;
							code << L"\n";
							PRINTWORDNUM();
							code << L"jr ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							code << L"L";
							code << (*latestLabel) - 2;
							code << L": move ";
							code << reg[i->rd];
							code << L", $0\n";
							PRINTWORDNUM();
							code << L"L";
							code << (*latestLabel) - 1;
							code << L": nop\n";
						}
						else if (i->op.compare(L"||") == 0)
						{
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << L", L";
							code << (*latestLabel)++;
							code << L"\n";
							PRINTWORDNUM();
							code << L"bne $0, ";
							code << reg[i->rt];
							code << L", ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							code << L"bne $0, ";
							code << reg[i->rs];
							code << L", ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							code << L"move ";
							code << reg[i->rd];
							code << L", $0\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << L", L";
							code << (*latestLabel)++;
							code << L"\n";
							PRINTWORDNUM();
							code << L"jr ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"L";
							code << (*latestLabel) - 2;
							code << L": ldi ";
							code << reg[i->rd];
							code << L", 1\n";
							PRINTWORDNUM();
							code << L"L";
							code << (*latestLabel) - 1;
							code << L": nop\n";
						}
						else if (i->op.compare(L"<<") == 0)
						{
							PRINTWORDNUM();
							code << L"sll ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L"\n";
							PRINTWORDNUM();
							code << L"move ";
							code << reg[i->rd];
							code << L", $rr\n";
						}
						else if (i->op.compare(L"<<i") == 0)
						{
							PRINTWORDNUM();
							code << L"slli ";
							code << reg[i->rt];
							code << L", ";
							code << i->rs;
							code << L"\n";
							PRINTWORDNUM();
							code << L"move ";
							code << reg[i->rd];
							code << L", $rr\n";
						}
						else if (i->op.compare(L">>") == 0)
						{
							PRINTWORDNUM();
							code << L"neg ";
							code << reg[L"*tmp3"];
							code << L", ";
							code << reg[i->rs];
							code << L"\n";
							PRINTWORDNUM();
							code << L"sll ";
							code << reg[i->rt];
							code << L", ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							code << L"move ";
							code << reg[i->rd];
							code << L", $rr\n";
						}
						else if (i->op.compare(L">>i") == 0)
						{
							PRINTWORDNUM();
							code << L"slli ";
							code << reg[i->rt];
							code << L", ";
							code << wtoi(i->rs.c_str())*(-1);
							code << L"\n";
							PRINTWORDNUM();
							code << L"move ";
							code << reg[i->rd];
							code << L", $rr\n";
						}
						else if (i->op.compare(L"u-") == 0) 
						{
							PRINTWORDNUM();
							code << L"neg ";
							code << reg[i->rd];
							code << L", ";
							code << reg[i->rt];
							code << L"\n";
						} 
						else if (i->op.compare(L"u~") == 0) 
						{
							PRINTWORDNUM();
							code << L"not ";
							code << reg[i->rd];
							code << L", ";
							code << reg[i->rt];
							code << L"\n";
						} 
						else if (i->op.compare(L"jump") == 0) 
						{
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << L", ";
							code << endLabel;
							code << L"\n";
							PRINTWORDNUM();
							code << L"jr ";
							code << reg[L"*tmp3"];
							code << L"\n";
							foundBranch = true;
						} 
						else if (i->op.compare(L">") == 0) 
						{
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << ", L";
							code << (*latestLabel)++;
							code << L"\n";
							PRINTWORDNUM();
							code << L"bgt ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L", ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"ldi ";
							code << reg[i->rd];
							code << L", 0\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << L", L";
							code << (*latestLabel);
							code << L"\n";
							PRINTWORDNUM();
							code << L"jr ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"L";
							code << (*latestLabel) - 1;
							code << L":ldi ";
							code << reg[i->rd];
							code << L", 1\n";
							code << L"L";
							code << (*latestLabel)++;
							code << L":\n";
						} 
						else if (i->op.compare(L">=") == 0) 
						{
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << ", L";
							code << (*latestLabel)++;
							code << L"\n";
							PRINTWORDNUM();
							code << L"bgt ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L", ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							code << L"beq ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L", ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"ldi ";
							code << reg[i->rd];
							code << L", 0\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << L", L";
							code << (*latestLabel);
							code << L"\n";
							PRINTWORDNUM();
							code << L"jr ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"L";
							code << (*latestLabel) - 1;
							code << L":ldi ";
							code << reg[i->rd];
							code << L", 1\n";
							code << L"L";
							code << (*latestLabel)++;
							code << L":\n";
						} 
						else if (i->op.compare(L"<") == 0) 
						{
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << ", L";
							code << (*latestLabel)++;
							code << L"\n";
							PRINTWORDNUM();
							code << L"blt ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L", ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"ldi ";
							code << reg[i->rd];
							code << L", 0\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << L", L";
							code << (*latestLabel);
							code << L"\n";
							PRINTWORDNUM();
							code << L"jr ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"L";
							code << (*latestLabel) - 1;
							code << L":ldi ";
							code << reg[i->rd];
							code << L", 1\n";
							code << L"L";
							code << (*latestLabel)++;
							code << L":\n";
						} 
						else if (i->op.compare(L"<=") == 0) 
						{
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << ", L";
							code << (*latestLabel)++;
							code << L"\n";
							PRINTWORDNUM();
							code << L"blt ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L", ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							code << L"beq ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L", ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"ldi ";
							code << reg[i->rd];
							code << L", 0\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[L"*tmp3"];
							code << L", L";
							code << (*latestLabel);
							code << L"\n";
							PRINTWORDNUM();
							code << L"jr ";
							code << reg[L"*tmp3"];
							code << L"\n";
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"L";
							code << (*latestLabel) - 1;
							code << L":ldi ";
							code << reg[i->rd];
							code << L", 1\n";
							code << L"L";
							code << (*latestLabel)++;
							code << L":\n";
						} 
						else if (i->op.compare(L"move") == 0)
						{
							PRINTWORDNUM();
							code << L"move ";
							code << reg[i->rd];
							code << L", ";
							code << reg[i->rt];
							code << L"\n";
						}
						else if (i->op.compare(L"assembly") == 0)
						{
							boost::unordered_map<std::wstring, std::wstring>::iterator it;
							for(it = i->inputVars.begin(); it != i->inputVars.end(); it++) 
							{
								if (mem.count(it->first) > 0)
								{
									PRINTWORDNUM();
									PRINTWORDNUM();
									code << L"ldi ";
									code << reg[L"*tmp3"];
									code << L", -";
									code << mem[it->first];
									code << L"\n";
									PRINTWORDNUM();
									code << L"ldw ";
									code << it->second;
									code << L", $fp, ";
									code << reg[L"*tmp3"];
									code << L"\n";
								}
								else
								{
									PRINTWORDNUM();
									code << L"addi $gp, -";
									code << globalMem[it->first];
									code << L"\n";
									PRINTWORDNUM();
									code << L"ldw ";
									code << it->second;
									code << L", $0, $rr\n";
								}
							}
							TCHAR* line = (TCHAR*) calloc(sizeof(TCHAR), i->rd.size() + 1);
							TCHAR* codeChar = (TCHAR*) calloc(sizeof(TCHAR), i->rd.size() + 1);
							wcscpy_s(codeChar, i->rd.size() + 1, i->rd.c_str());
							line = wcstok(codeChar, L";");
							do
							{
								PRINTWORDNUM();
								code << line << L"\n";
							} while((line = wcstok(NULL, L";")) != NULL);
							for(it = i->outputVars.begin(); it != i->outputVars.end(); it++) 
							{
								if (mem.count(it->first) > 0)
								{
									PRINTWORDNUM();
									PRINTWORDNUM();
									code << L"ldi ";
									code << reg[L"*tmp3"];
									code << L", -";
									code << mem[it->first];
									code << L"\n";
									PRINTWORDNUM();
									code << L"sdw ";
									code << it->second;
									code << L", $fp, ";
									code << reg[L"*tmp3"];
									code << L"\n";
								}
								else
								{
									PRINTWORDNUM();
									code << L"addi $gp, -";
									code << globalMem[it->first];
									code << L"\n";
									PRINTWORDNUM();
									code << L"sdw ";
									code << it->second;
									code << L", $0, $rr\n";
								}
							}
						}
						else if (i->op.compare(L"u&") == 0)
						{
							PRINTWORDNUM();
							code << L"addi $sp, -";
							code << mem[i->rt];
							code << L"\n";
							PRINTWORDNUM();
							code << L"move ";
							code << reg[i->rd];
							code << L", $rr\n";
						}
						else if (i->op.compare(L"u*") == 0)
						{
							PRINTWORDNUM();
							code << L"ldw ";
							code << reg[i->rd];
							code << L", $0, ";
							code << reg[i->rt];
							code << L"\n";
						}
						else if (i->op.compare(L"storeadd") == 0)
						{
							PRINTWORDNUM();
							code << L"sdw ";
							code << reg[i->rd];
							code << L", $0, ";
							code << reg[i->rt];
							code << L"\n";
						}
						else if (i->op.compare(L"push") == 0)
						{
							PRINTWORDNUM();
							code << L"addi $sp, 2\n";
							PRINTWORDNUM();
							code << L"sdw ";
							code << reg[i->rt];
							code << L", $sp, $0\n";
							PRINTWORDNUM();
							code << L"move $sp, $rr\n";
						}
						else if (i->op.compare(L"pop") == 0)
						{
							PRINTWORDNUM();
							code << L"addi $sp, -2\n";
							PRINTWORDNUM();
							code << L"move $sp, $rr\n";
							PRINTWORDNUM();
							code << L"ldw ";
							code << reg[i->rd];
							code << L", $sp, $0\n";
						}
						else if (i->op.compare(L"pusharr") == 0)
						{
							PRINTWORDNUM();
							code << L"add $sp, ";
							code << reg[i->rt];
							code << L"\n";
							PRINTWORDNUM();
							code << L"move ";
							code << reg[i->rd];
							code << L", $sp\n";
							PRINTWORDNUM();
							code << L"move $sp, $rr\n";
						}
						else if (i->op.compare(L"+i") == 0)
						{
							PRINTWORDNUM();
							code << L"addi ";
							code << reg[i->rt];
							code << L", ";
							code << reg[i->rs];
							code << L"\n";
							PRINTWORDNUM();
							code << L"move ";
							code << reg[i->rd];
							code << L", ";
							code << reg[L"rr"];
							code << L"\n";
						}
						else if (i->op.compare(L"la") == 0)
						{
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							PRINTWORDNUM();
							code << L"la ";
							code << reg[i->rd];
							code << L", ";
							code << i->rt;
							code << L"\n";
						}
						else 
						{
							code << L"//Did not match any instructions with op ";
							code << i->op;
							code << L".\n";
						}
					}
					int tmp_int = code.str().size();
					if (!foundBranch && endLabel.length() > 0)
					{
						PRINTWORDNUM();
						PRINTWORDNUM();
						PRINTWORDNUM();
						PRINTWORDNUM();
						PRINTWORDNUM();
						PRINTWORDNUM();
						PRINTWORDNUM();
						code << L"la ";
						code << reg[L"*tmp3"];
						code << L", ";
						code << endLabel;
						code << L"\n";
						PRINTWORDNUM();
						code << L"jr ";
						code << reg[L"*tmp3"];
						code << L"\n";
					}
					if(ErrorHandler::GetInstance()->GetDebugCode() == 4)
					{
						wprintf(L"Exiting BasicBlock::GenerateCode.\n");
					}
					std::wstring returnableChar = code.str();
					return returnableChar;
				}
			}	  	    
		}
	}
}
