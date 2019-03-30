#include "stdafx.h"
#include "Instruction.h"
#include "ErrorHandler.h"

#ifndef _BASIC_BLOCK__H_
#define _BASIC_BLOCK__H_

namespace MiniC {
  namespace IR {
    namespace Epicness {
      namespace BasicBlock {
	
		#define PRINTWORDNUM() { code << L"// Words: "; code << (*numWord)++; code << L"\n"; }

		class BasicBlock {
	  
		protected:

			/*
			*	ATTRIBUTE: funcDecl
			*	DESCRIPTION: Boolean which describes whether this BasicBlock has a
			*		function declaration in it. This is used by the FlowGraph 
			*		GenerateCode function in order to treat correctly.
			*/
			bool funcDecl; 

			/*	ATTRIBUTE: body
			*	DESCRIPTION: Contains list of instructions which the BasicBlock contains.
			*/
			std::list<MiniC::IR::Instruction::Instruction*> body;
		public:			
			/*
			*	FUNCTION: BasicBlock
			*	DESCRIPTION: Default constructor for BasicBlock
			*/
			BasicBlock();
		  
			/*
			*	FUNCTION: BasicBlock
			*	PARAMETER 1: BasicBlock& bn - BasicBlock object to copy
			*	DESCRIPTION: Copy constructor for BasicBlock
			*/
			BasicBlock(BasicBlock& bn);
			
			/*
			*	FUNCTION: ~BasicBlock
			*	DESCRIPTION: Destructor for BasicBlock
			*/
			~BasicBlock();
		  
			/*
			*	FUNCTION: BasicBlock
			*	PARAMETER 1: std::list<Instruction::Instruction*> insts - List of instructions 
			*		which are contained in the BasicBlock object
			*	DESCRIPTION: Default constructor for BasicBlock
			*/
			BasicBlock(std::list<MiniC::IR::Instruction::Instruction*> insts);
	  
			/*
			*	FUNCTION: GetInstructions
			*	DESCRIPTION: Getter function for body private member.
			*/
			std::list<Instruction::Instruction*> GetInstructions();

			/*
			*	FUNCTION: RemoveInstruction
			*	PARAMETER 1: Instruction::Instruction* i - Instruction to be removed from
			*				the body.
			*	DESCRIPTION: Removes given instruction from body member.
			*/
			void RemoveInstruction(Instruction::Instruction* i);
			
			/*
			*	FUNCTION: SetInstructions
			*	PARAMETER 1: std::list<Instruction::Instruction*> insts - New body to replace itself with.
			*	DESCRIPTION: Replaces the current basic block body with insts.
			*/
			void SetInstructions(std::list<Instruction::Instruction*> insts);

			/*
			*	FUNCTION: ToString
			*	DESCRIPTION: Returns WString containing description of BasicBlock, including a list of
			*		all of the instructions which the BasicBlock contains.
			*/
			std::wstring ToString();

			/*
			*	FUNCTION: Equals
			*	DESCRIPTION: Returns true if the BasicBlock has the same instructions in it as the argument
			*		the function is passed. It will return false if this is not the case.
			*/
			bool Equals(BasicBlock* b2);

			/*
			*	FUNCTION: InsertInstruction
			*	PARAMETER 1: Instruction::Instruction* inst - Instruction to be added to basic block.
			*	DESCRIPTION: Inserts instruction inst into the list of instructions in the BasicBlock object.
			*/
			void InsertInstruction(Instruction::Instruction* inst);

			/*
			*	FUNCTION: ResetLastRd
			*	PARAMETER 1: WString representing the variable to which the last instruction's 
			*		destination should be assigned to.
			*	DESCRIPTION: Reassigns the destination location for the last instruction in the 
			*		BasicBlock to str. This is used when the BasicBlock is being created, helping
			*		deal with destination registers during assignments and operations.
			*/
			void ResetLastRd(std::wstring str);
			
			/*
			*	FUNCTION: SetFunction
			*	DESCRIPTION: Declares that this BasicBlock contains a function declaration.
			*/
			void SetFunction();

			/*
			*	FUNCTION: GetFunction
			*	DESCRIPTION: Returns whether this is a function declaration or not.
			*/
			bool GetFunction();

			/*
			*	FUNCTION: GetVariables
			*	PARAMETER 1: List of WStrings which the BasicBlock's variables should be appended to.
			*	DESCRIPTION: Appends any variables which are used or assigned to in GetVariables to
			*		the list currVariables. The list is then ensured that it is unique, and temporary
			*		variables are removed.
			*/
			std::list<std::wstring> GetVariables(std::list<std::wstring> currVariables);

			/*
			*	FUNCTION: GenerateCode
			*	PARAMETER 1: Mapping of variable to location in stack relative to stack pointer value. 
			*	PARAMETER 2: Amount of room to allocate on the stack for the BasicBlock.
			*	PARAMETER 3: Label which should be present at the beginning of the code.
			*	PARAMETER 4: Label to which the BasicBlock should jump at the end. May be NULL, if a jr is present.
			*	DESCRIPTION: Appends any variables which are used or assigned to in GetVariables to
			*		the list currVariables. The list is then ensured that it is unique, and temporary
			*		variables are removed.
			*/
			std::wstring GenerateCode(boost::unordered_map<std::wstring, int> mem, boost::unordered_map<std::wstring, int> globalMem, int globalAllocSize, int allocSize, std::wstring startLabel, std::wstring endLabel, BasicBlock* globalAllocBlock, int* latestLabel, int* numWord);

		};
	
      }
    }
  }
}

#endif
