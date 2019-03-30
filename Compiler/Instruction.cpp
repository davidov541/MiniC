#include "stdafx.h"
#include "Instruction.h"

namespace MiniC {
	namespace IR {
		namespace Instruction {
			Instruction::Instruction(Instruction* inst)
			{
				this->label = inst->label;
				this->op = inst->op;
				this->rd = inst->rd;
				this->rs = inst->rs;
				this->rt = inst->rt;
			}
			
			Instruction::Instruction(std::wstring op, std::wstring rd, std::wstring rt, std::wstring rs, std::wstring label)
			{
				this->op = op;
				this->rd = rd;
				this->rs = rs;
				this->rt = rt;
				this->label = label;
			}

			std::wstring Instruction::ToString()
			{
				std::wstringstream result;
				result << this->label;
				result << L": ";
				result << this->op;
				result << L" ";
				result << this->rd;
				result << L", ";
				result << this->rs;
				result << L", ";
				result << this->rt;
				std::wstring resultChar = result.str();
				return resultChar;
			}
		}
	}
}