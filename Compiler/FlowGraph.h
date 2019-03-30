#include "stdafx.h"
#include "SymbolTable.h"
#include "BasicBlock.h"
#include "ErrorHandler.h"

#ifndef _FLOW_GRAPH__H_
#define _FLOW_GRAPH__H_

namespace MiniC {
	namespace IR {
		namespace Epicness {
			namespace FlowGraph {

				class FlowGraph {
				protected:

					std::list<std::wstring> funcNames;
					std::multimap<int, int> links;

					std::list<std::wstring> data;
					int currDataLabel;
					BasicBlock::BasicBlock* globalBlock;

					boost::unordered_map<std::wstring, int> globalVars;
					bool inGlobalScope;

					std::list<boost::unordered_map<std::wstring, int> > localVariables;

					std::list<BasicBlock::BasicBlock*> blocks;

					IR::AST::SymbolTable* table;

					int currBlock;

					boost::unordered_map<std::wstring, std::list<std::pair<std::wstring, int> > > structFieldPositions;

					/*
					*	FUNCTION: IsConnectedTo
					*	PARAMETER 1: int blockNum - The basic block number which is under question.
					*	DESCRIPTION: Looking through all recorded links, this function determines if
					*		the requested basic block is connected to by any other basic block. 
					*		If not, it is assumed that this block is a function block, although
					*		a corrupted FlowGraph could give this result.
					*/
					bool IsConnectedTo(int blockNum);

					/*
					*	FUNCTION: GetTarget
					*	PARAMETER 1: int blockNum - The basic block number which is under question.
					*	DESCRIPTION: Looking through all recorded links, this function determines the
					*		basic block which the requested block is connected to, but not next to.
					*		Such connections are present in branches and jumps. If no such link is found,
					*		the function returns -1.
					*/
					int GetTarget(int blockNum);

					/*
					*	FUNCTION: GetFuncVariables
					*	DESCRIPTION: Looking through all of the basic blocks, it determines which ones
					*		are function declarations (using IsConnectedTo), and then calls GetVariables
					*		on each basic block to get its variables. These variables are separated into
					*		lists based on which function they belong to (a function will have consecutive
					*		basic blocks), and this list of lists of function names is returned.
					*/  
					std::list<std::list<std::wstring> > GetFuncVariables();

					/*
					*	FUNCTION: RemoveUselessMoves
					*	DESCRIPTION: Removes IR operations which moves values from one register to the same register.
					*				These are the results from assignments which are not used as values for other
					*				statements, and can be safely removed easily.
					*/
					void RemoveUselessMoves(BasicBlock::BasicBlock* bb);

					/*
					*	FUNCTION: ReplaceIfs
					*	DESCRIPTION: Replaces any comparison followed by an if with the correct branching
					*				statement for that comparison. Since comparisons branch already, this
					*				removes an entire branching sequence from the compiled code.
					*/
					void ReplaceIfs(BasicBlock::BasicBlock* bb);
					
					/*
					*	FUNCTION: ReplaceUselessStackOps
					*	DESCRIPTION: Replaces any pops and pushes of registers which are not used between the two operations. 
					*				Since if the registers are not used, the pushes and pops are not needed to verify correct
					*				usage of the system.
					*/
					void ReplaceUselessStackOps(BasicBlock::BasicBlock* bb);

				public:

					/*
					*	FUNCTION: FlowGraph
					*	DESCRIPTION: Default constructor for the FlowGraph class.
					*/
					FlowGraph();

					/*
					*	FUNCTION: FlowGraph
					*	PARAMETER 1: FlowGraph& fn
					*	DESCRIPTION: Copy constructor for the FlowGraph class.
					*/
					FlowGraph(FlowGraph& fg);

					/*
					*	FUNCTION: FlowGraph
					*	PARAMETER 1: Initializes FlowGraph with given SymbolTable.
					*	DESCRIPTION: Default constructor for the FlowGraph class.
					*/
					FlowGraph(IR::AST::SymbolTable* table);
					
					/*
					*	FUNCTION: ~FlowGraph
					*	DESCRIPTION: Destructor for the FlowGraph class.
					*/
					~FlowGraph();

					/*
					*	FUNCTION: Equals
					*	DESCRIPTION: Returns true if the FlowGraph has the same instructions in it as the argument
					*		the function is passed, along with the same basic block structure. 
					*		It will return false if this is not the case.
					*/
					bool Equals(FlowGraph* b2);
					
					/*
					*	FUNCTION: GetBlocks
					*	DESCRIPTION: Getter for the blocks instance member.
					*/
					std::list<BasicBlock::BasicBlock*> GetBlocks();

					/*
					*	FUNCTION: RemoveLastBlock
					*	DESCRIPTION: Removes last block which was inserted into the FlowGraph.
					*	USAGE: Used by ProgramNode to remove extra block at the end of the code.
					*/
					void RemoveLastBlock();
					
					/*
					*	FUNCTION: GetGlobalBlock
					*	DESCRIPTION: Getter for the globalblock instance member.
					*/
					BasicBlock::BasicBlock* GetGlobalBlock();
					
					/*
					*	FUNCTION: GetCurrBlock
					*	DESCRIPTION: Getter for the currblock instance member.
					*/
					int GetCurrBlock();
					
					/*
					*	FUNCTION: SetCurrBlock
					*	DESCRIPTION: Setter for the currblock instance member.
					*/
					void SetCurrBlock(int currBlock);

					/*
					*	FUNCTION: InsertInstruction
					*	PARAMETER 1: Instruction::Instruction* inst - Instruction to be added to FlowGraph
					*	DESCRIPTION: Adds FlowGraph to last BasicBlock that was added to the FlowGraph
					*/
					void InsertInstruction(Instruction::Instruction* inst);

					/*
					*	FUNCTION: ResetLastRd
					*	PARAMETER 1: Wstring rd - New value for the destination variable
					*	DESCRIPTION: Sets the destination variable of the last instruction in the last BasicBlock
					*		to rd.
					*/
					void ResetLastRd(std::wstring rd);
					
					/*
					*	FUNCTION: EnterFunction
					*	DESCRIPTION: Sets inGlobalScope to false.
					*/
					void EnterFunction();
					
					/*
					*	FUNCTION: ExitFunction
					*	DESCRIPTION: Sets inGlobalScope to true.
					*/
					void ExitFunction();

					/*
					*	FUNCTION: InsertFuncName
					*	PARAMETER 1: wstring funcname - Name of the function which is being evaluated.
					*	DESCRIPTION: Indicates that the last basic block which was inserted was in fact a
					*		function block, and sets it as such. Also stores the name in funcNmaes.
					*/
					void InsertFuncName(std::wstring funcName);

					/*
					*	FUNCTION: InsertNewBasicBlock
					*	PARAMETER 1: bool connect - Boolean value determining if new block is connected
					*	DESCRIPTION: Creates a new BasicBlock, and adding it to the end of the list.
					*		If connect is true, the new BasicBlock is connected to the original last BasicBlock
					*		in the list.
					*/
					void InsertNewBasicBlock(bool connect);

					/*
					*	FUNCTION: InsertLink
					*	PARAMETER 1: int source - The basic block number which connects to target.
					*	PARAMETER 2: int target - The basic block which is being connected to.
					*	DESCRIPTION: Connects the two basic blocks indicated using an entry
					*		in the links table.
					*/
					void InsertLink(int source, int target);
					
					/*
					*	FUNCTION: InsertData
					*	PARAMETER 1: std::wstring data - Data which wil be referenced, and should be stored in assembly file.
					*	DESCRIPTION: Inserts data into list which will be stored in the assembly file. This function should return
					*		the number of the label at which the data will be stored.
					*/
					int InsertData(std::wstring data);

					/*
					*	FUNCTION: AddGlobalVar
					*	PARAMETER 1: std::wstring var - Name of global variable being registered.
					*	PARAMETER 2: int size - Size which should be allocated for the variable.
					*	DESCRIPTION: Adds global variable to list. This list is used to allocate
					*		memory for variables in the assembly code.
					*/
					void AddGlobalVar(std::wstring var, int size);

					/*
					*	FUNCTION: AddLocalVar
					*	PARAMETER 1: std::wstring var - Name of global variable being registered.
					*	PARAMETER 2: int size - Size which should be allocated for the variable.
					*	DESCRIPTION: Adds local variable to list. This list is used to allocate
					*		memory for variables in the assembly code.
					*/
					void AddLocalVar(std::wstring var, int size);

					/*
					*	FUNCTION:	AddStruct
					*	PARAMETER 1: std::wstring structname - Name of struct which is being added
					*	DESCRIPTION: Adds a struct with an empty list of pairs to the mapping of struct arrangements.
					*/
					void AddStruct(std::wstring structname);

					/*
					*	FUNCTION: AddStructField
					*	PARAMETER 1: std::wstring structname - Name of struct which the field being added belongs to.
					*	PARAMETER 2: std::wstring fieldname - Name of struct field which is being added.
					*	PARAMETER 3: int fieldpos - Offset from the struct start where this field should be.
					*	DESCRIPTION: Adds the position of the given field in the given struct physical representation.
					*/
					void AddStructField(std::wstring structname, std::wstring fieldname, int fieldpos);

					/*
					*	FUNCTION: GetStructFieldPos
					*	PARAMETER 1: std::wstring structname - Name of struct which is being queried.
					*	PARAMETER 2: std::wstring fieldname - Name of field which is being queried.
					*	DESCRIPTION: Returns the position of the given field inside of the given struct relative to the
					*		beginning of the struct.
					*/
					int GetStructFieldPos(std::wstring structname, std::wstring fieldname);

					/*
					*	FUNCTION: ToString
					*	DESCRIPTION: Prints out a representation of each basic block
					*		in this FlowGraph, along with the links between them.
					*/
					std::wstring ToString();

					/*
					*	FUNCTION: Optimize
					*	DESCRIPTION: Goes through each individual IR instruction in the flowgraph, optimizing the code
					*				as necessary. Each individual optimization is in a separate function, and is documented
					*				there.
					*/
					void Optimize();

					/*
					*	FUNCTION: GenerateCode
					*	DESCRIPTION: Manages the creation of code from all of the basic blocks
					*		contained in the current FlowGraph. Space in the stack is allocated
					*		for each function, and locations are kept track of, and are then
					*		passed into the GenerateCode for the BasicBlock class.
					*/
					std::wstring GenerateCode();

				};

			}
		}
	}
}

#endif