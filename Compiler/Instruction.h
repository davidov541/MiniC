#ifndef INSTR_H_
#define INSTR_H_

#include "stdafx.h"

namespace MiniC {
	namespace IR {
		namespace Instruction {

			class Instruction {
			public:
				std::wstring op;
				std::wstring rd;
				std::wstring rt;
				std::wstring rs;
				std::wstring label;
				boost::unordered_map<std::wstring, std::wstring> inputVars;
				boost::unordered_map<std::wstring, std::wstring> outputVars;

				Instruction() {
					this->op = L"";
					this->rd = L"";
					this->rt = L"";
					this->rs = L"";
					this->label = L"";
				}
				Instruction(Instruction* id);
				Instruction(std::wstring op, std::wstring rd, std::wstring rt, std::wstring rs, std::wstring label);
				std::wstring ToString();
			};
		}
	}
}
#endif
