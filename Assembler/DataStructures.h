#include "Constants.h"

#ifndef __BITEPICNESS_ASSEMBLER_DATASTRUCTS
#define __BITEPICNESS_ASSEMBLER_DATASTRUCTS

namespace BitEpicness
{
	namespace Assembler
	{
		enum OpType
		{
			R = 0,
			I = 1,
			J = 2,
			M = 3,
			L = 4,
			SYSI = 5,
			SYSN = 6,
			SYSR = 7,
			SYSRR = 8
		};

		typedef struct
		{
			TCHAR** errorMessages;
			int numErrors;
		} ErrorHandler;
	}
}

#endif