/* Naming Convention:
	All four letters
	First - Indicates what type of test
		*C == Check
	Second - Indicates input types or what is being checked
		*E = ErrorHandler
		*P = Pointer
		*S = String or WString
	Third + Fourth - Indicates the procedure doing the checking
		*NE = No Exceptions
		*HE = Has Exceptions
		*NN = Not Null
		*IN = Is Null
		*EQ = Equals
		*CP = compare
*/

#define CEHE(errMsg, numAssert) if (MiniC::ErrorHandler::GetInstance()->IsEmpty()) {swprintf_s(errMsg, MAX_ERROR_LEN, L"ERROR in Assertion #%d: %s", numAssert, L"ERROR - Error should have happened for this test, but none was found!\n"); return false;} else { MiniC::ErrorHandler::GetInstance()->ClearErrors(); numAssert++; }
#define CENE(errMsg, numAssert) if (!MiniC::ErrorHandler::GetInstance()->IsEmpty()) { swprintf_s(errMsg, MAX_ERROR_LEN, L"ERROR in Assertion #%d: %s", numAssert, MiniC::ErrorHandler::GetInstance()->PrintErrors().c_str()); MiniC::ErrorHandler::GetInstance()->ClearErrors(); return false;} else { numAssert++; }
#define CPNN(obj, errMsg, numAssert) if (!obj) { swprintf_s(errMsg, MAX_ERROR_LEN, L"ERROR in Assertion #%d: %s", numAssert, L"ERROR - Object is null when it shouldn't be!\n"); return false; } else { numAssert++; }
#define CPEQ(p1, p2, errMsg, numAssert) if (!(p1->Equals(p2))) {swprintf_s(errMsg, MAX_ERROR_LEN, L"ERROR in Assertion #%d: %s", numAssert, L"ERROR - Objects were not equal!\n"); return false; } else { numAssert++; }
#define CSCP(s1, s2, errMsg, numAssert) if (s1.compare(s2) != 0) {swprintf_s(errMsg, MAX_ERROR_LEN, L"ERROR in Assertion #%d: %s", numAssert, L"ERROR - Strings were not equal!\n"); return false; } else { numAssert++; }

//Array Type-Check Tests
extern "C" __declspec(dllexport) bool Test_ArrayOfInts_TypeCheck(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_ArrayOfPointers_TypeCheck(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_ArrayOfChars_TypeCheck(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_ArrayWithStrangeIndicies_TypeCheck(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_StructDecl_TypeCheck(TCHAR* errMsg);

//Array Flowgraph Generation Tests
extern "C" __declspec(dllexport) bool Test_ArrayOfInts_FGGen(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_ArrayOfPointers_FGGen(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_ArrayOfChars_FGGen(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_ArrayWithStrangeIndicies_FGGen(TCHAR* errMsg);

//Optimization Tests
extern "C" __declspec(dllexport) bool Test_OptimizeUselessMoves(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_OptimizeBranches(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_OptimizeConstantAddExpressions(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_OptimizeConstantBoolExpressions(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_OptimizeConstantShiftExpressions(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_OptimizeConstantUnaryExpressions(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_OptimizeStackOperations(TCHAR* errMsg);

//Integration Tests
extern "C" __declspec(dllexport) void Test_CompileCode(TCHAR* fileName, int fileLength, TCHAR* translatedAsm);

//Switch Statement Tests
extern "C" __declspec(dllexport) bool Test_SwitchStatement_TypeCheck(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_SwitchStatementWithDefault_FGGen(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_SwitchStatement_FGGen(TCHAR* errMsg);

//Struct Tests
extern "C" __declspec(dllexport) bool Test_StructSymbolTableFunctions(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_StructInit_TypeCheck(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_StructDeclInit_TypeCheck(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_StructInit_FGGen(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_StructDeclInit_FGGen(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_StructReference_TypeCheck(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_StructReference_FGGen(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_StructArrowReference_TypeCheck(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_StructArrowReference_FGGen(TCHAR* errMsg);

//Misc. Type-Check Tests
extern "C" __declspec(dllexport) bool Test_ValidType_TypeCheck(TCHAR* errMsg);
extern "C" __declspec(dllexport) bool Test_PrimitiveAssign_TypeCheck(TCHAR* errMsg);