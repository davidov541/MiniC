#include "stdafx.h"
#include "Node.h"
#include "UnitTests.h"
#include "Compiler.h"

using namespace MiniC::IR::AST;
using namespace MiniC::IR::Epicness;
using namespace MiniC::IR::Instruction;

// Typechecking Tests
extern "C" __declspec(dllexport) bool Test_PrimitiveAssign_TypeCheck(TCHAR* errMsg)
{
	SymbolTable st = SymbolTable();
	st.EnterScope();
	int assertNum = 1;

	//Constructing:
	//int a;
	//a = 'a';
	//a = 5;
	//a = true; --ERROR!
	//bool b;
	//b = 'a'; --ERROR!
	//b = 5; --ERROR!
	//b = false;
	//char c;
	//c = 'a';
	//c = 5; --ERROR!
	//c = false; --ERROR!
	PrimitiveTypeNode* inttype = new PrimitiveTypeNode(L"int");
	DeclAssignNode* decl1 = new DeclAssignNode(inttype, L"a", NULL);
	st = decl1->FullTypeCheck(st);
	delete decl1;
	CENE(errMsg, assertNum);

	ExpressionStmt* stmt1 = new ExpressionStmt(new AssignNode(new VarNode(L"a"), L"=", new CharNode(L'a')));
	st = stmt1->FullTypeCheck(st);
	delete stmt1;
	CENE(errMsg, assertNum);

	ExpressionStmt* stmt2 = new ExpressionStmt(new AssignNode(new VarNode(L"a"), L"=", new IntNode(5)));
	st = stmt2->FullTypeCheck(st);
	delete stmt2;
	CENE(errMsg, assertNum);

	ExpressionStmt* stmt3 = new ExpressionStmt(new AssignNode(new VarNode(L"a"), L"=", new KeywordNode(L"true")));
	st = stmt3->FullTypeCheck(st);
	delete stmt3;
	CEHE(errMsg, assertNum);

	PrimitiveTypeNode* booltype = new PrimitiveTypeNode(L"boolean");
	DeclAssignNode* decl2 = new DeclAssignNode(booltype, L"b", NULL);
	st = decl2->FullTypeCheck(st);
	delete decl2;
	CENE(errMsg, assertNum);

	ExpressionStmt* stmt4 = new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new CharNode(L'a')));
	st = stmt4->FullTypeCheck(st);
	delete stmt4;
	CEHE(errMsg, assertNum);

	ExpressionStmt* stmt5 = new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(5)));
	st = stmt5->FullTypeCheck(st);
	delete stmt5;
	CEHE(errMsg, assertNum);

	ExpressionStmt* stmt6 = new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new KeywordNode(L"true")));
	st = stmt6->FullTypeCheck(st);
	delete stmt6;
	CENE(errMsg, assertNum);

	PrimitiveTypeNode* chartype = new PrimitiveTypeNode(L"char");
	DeclAssignNode* decl3 = new DeclAssignNode(chartype, L"c", NULL);
	st = decl3->FullTypeCheck(st);
	delete decl3;
	CENE(errMsg, assertNum);

	ExpressionStmt* stmt7 = new ExpressionStmt(new AssignNode(new VarNode(L"c"), L"=", new CharNode(L'a')));
	st = stmt7->FullTypeCheck(st);
	delete stmt7;
	CENE(errMsg, assertNum);

	ExpressionStmt* stmt8 = new ExpressionStmt(new AssignNode(new VarNode(L"c"), L"=", new IntNode(5)));
	st = stmt8->FullTypeCheck(st);
	delete stmt8;
	CEHE(errMsg, assertNum);

	ExpressionStmt* stmt9 = new ExpressionStmt(new AssignNode(new VarNode(L"c"), L"=", new KeywordNode(L"true")));
	st = stmt9->FullTypeCheck(st);
	delete stmt9;
	CEHE(errMsg, assertNum);

	return true;
}

extern "C" __declspec(dllexport) bool Test_ArrayOfInts_TypeCheck(TCHAR* errMsg)
{
	SymbolTable st = SymbolTable();
	st.EnterScope();
	int assertNum = 1;

	//Set up AST for testing.
	//Constructing:
	//int x[10];
	//x[0] = 5;
	//x[1] = 'a'; ---Error!
	PrimitiveTypeNode* type = new PrimitiveTypeNode(L"int", 1, new IntNode(L"10"));
	DeclAssignNode* decl = new DeclAssignNode(type, L"x", NULL);
	st = decl->FullTypeCheck(st);
	delete decl;
	CENE(errMsg, assertNum);

	ArrayNode* arr1 = new ArrayNode(new VarNode(L"x"), new IntNode(L"0"));
	AssignNode* assign1 = new AssignNode(arr1, L"=", new IntNode(L"5"));
	ExpressionStmt* stmt2 = new ExpressionStmt(assign1);
	st = stmt2->FullTypeCheck(st);
	delete stmt2;
	CENE(errMsg, assertNum);

	ArrayNode* arr2 = new ArrayNode(new VarNode(L"x"), new IntNode(L"1"));
	AssignNode* assign2 = new AssignNode(arr2, L"=", new CharNode(new std::wstring(L"a")));
	ExpressionStmt* stmt3 = new ExpressionStmt(assign2);
	st = stmt3->FullTypeCheck(st);
	delete stmt3;
	CENE(errMsg, assertNum);

	return true;
}

extern "C" __declspec(dllexport) bool Test_ArrayOfPointers_TypeCheck(TCHAR* errMsg)
{
	SymbolTable st = SymbolTable();
	st.EnterScope();
	int assertNum = 1;

	//Constructing:
	//int* y[10];
	//y[0] = 5; -- Error!
	//*y[1] = 10;
	//int i = 5;
	//y[2] = &i;
	PrimitiveTypeNode* type2 = new PrimitiveTypeNode(L"int", 2, new IntNode(L"10"));
	DeclAssignNode* decl2 = new DeclAssignNode(type2, L"y", NULL);
	st = decl2->FullTypeCheck(st);
	delete decl2;
	CENE(errMsg, assertNum);

	ArrayNode* arr3 = new ArrayNode(new VarNode(L"y"), new IntNode(L"0"));
	AssignNode* assign3 = new AssignNode(arr3, L"=", new IntNode(L"5"));
	ExpressionStmt* stmt4 = new ExpressionStmt(assign3);
	st = stmt4->FullTypeCheck(st);
	delete stmt4;
	CEHE(errMsg, assertNum);

	ArrayNode* arr4 = new ArrayNode(new VarNode(L"y"), new IntNode(L"1"));
	UnaryNode* unary = new UnaryNode(L"*", arr4);
	AssignNode* assign4 = new AssignNode(unary, L"=", new IntNode(L"10"));
	ExpressionStmt* stmt5 = new ExpressionStmt(assign4);
	st = stmt5->FullTypeCheck(st);
	delete stmt5;
	CENE(errMsg, assertNum);

	DeclAssignNode* decl3 = new DeclAssignNode(new PrimitiveTypeNode(L"int"), L"i", new IntNode(L"5"));
	st = decl3->FullTypeCheck(st);
	delete decl3;
	CENE(errMsg, assertNum);

	UnaryNode* unary2 = new UnaryNode(L"&", new VarNode(L"i"));
	ArrayNode* arr5 = new ArrayNode(new VarNode(L"y"), new IntNode(L"2"));
	AssignNode* assign5 = new AssignNode(arr5, L"=", unary2);
	ExpressionStmt* stmt6 = new ExpressionStmt(assign5);
	st = stmt6->FullTypeCheck(st);
	delete stmt6;
	CENE(errMsg, assertNum);

	return true;
}

extern "C" __declspec(dllexport) bool Test_ArrayOfChars_TypeCheck(TCHAR* errMsg)
{
	SymbolTable st = SymbolTable();
	st.EnterScope();
	int assertNum = 1;

	//Constructing:
	//char z[10];
	//z[0] = 5; --ERROR!
	//z[1] = 'a';
	PrimitiveTypeNode* type3 = new PrimitiveTypeNode(L"char", 1, new IntNode(L"10"));
	DeclAssignNode* decl4 = new DeclAssignNode(type3, L"z", NULL);
	st = decl4->FullTypeCheck(st);
	delete decl4;
	CENE(errMsg, assertNum);

	ArrayNode* arr6 = new ArrayNode(new VarNode(L"z"), new IntNode(L"0"));
	AssignNode* assign6 = new AssignNode(arr6, L"=", new IntNode(L"5"));
	ExpressionStmt* stmt7 = new ExpressionStmt(assign6);
	st = stmt7->FullTypeCheck(st);
	delete stmt7;
	CEHE(errMsg, assertNum);

	ArrayNode* arr7 = new ArrayNode(new VarNode(L"z"), new IntNode(L"1"));
	AssignNode* assign7 = new AssignNode(arr7, L"=", new CharNode(new std::wstring(L"'a'")));
	ExpressionStmt* stmt8 = new ExpressionStmt(assign7);
	st = stmt8->FullTypeCheck(st);
	delete stmt8;
	CENE(errMsg, assertNum);

	return true;
}

extern "C" __declspec(dllexport) bool Test_ArrayWithStrangeIndicies_TypeCheck(TCHAR* errMsg)
{
	SymbolTable st = SymbolTable();
	st.EnterScope();
	int assertNum = 1;

	//Constructing:
	//int x = 5;
	//char a = 'a';
	//char y[x];
	//int z[a]; --Error!
	//y[0] = 'a';
	
	DeclAssignNode* decl = new DeclAssignNode(new PrimitiveTypeNode(L"int"), L"x", new IntNode(L"5"));
	st = decl->FullTypeCheck(st);
	delete decl;
	CENE(errMsg, assertNum);

	DeclAssignNode* decl2 = new DeclAssignNode(new PrimitiveTypeNode(L"char"), L"a", new CharNode(new std::wstring(L"a")));
	st = decl2->FullTypeCheck(st);
	delete decl2;
	CENE(errMsg, assertNum);

	PrimitiveTypeNode* type = new PrimitiveTypeNode(L"char", 1, new VarNode(L"x"));
	DeclAssignNode* decl3 = new DeclAssignNode(type, L"y", NULL);
	st = decl3->FullTypeCheck(st);
	delete decl3;
	CENE(errMsg, assertNum);
	
	PrimitiveTypeNode* type2 = new PrimitiveTypeNode(L"int", 1, new VarNode(L"a"));
	DeclAssignNode* decl4 = new DeclAssignNode(type2, L"z", NULL);
	st = decl4->FullTypeCheck(st);
	delete decl4;
	CEHE(errMsg, assertNum);

	ArrayNode* arr = new ArrayNode(new VarNode(L"y"), new IntNode(L"0"));
	AssignNode* assign = new AssignNode(arr, L"=", new CharNode(new std::wstring(L"a")));
	ExpressionStmt* stmt = new ExpressionStmt(assign);
	st = stmt->FullTypeCheck(st);
	delete stmt;
	CENE(errMsg, assertNum);

	return true;
}

extern "C" __declspec(dllexport) bool Test_SwitchStatement_TypeCheck(TCHAR* errMsg)
{
	SymbolTable st = SymbolTable();
	st.EnterScope();
	int assertNum = 1;

	//Constructing:
	//int a = 5;
	//int b;
	//switch(a)
	//{
	//	case 0:
	//		b = 10;
	//		break;
	//	case 1:
	//		b = 100;
	//		break;
	//	case 2:
	//		b = 1000;
	//		break;
	//	default:
	//		b = 10000;
	//		break;
	//}
	
	DeclAssignNode* decl = new DeclAssignNode(new PrimitiveTypeNode(L"int"), L"a", new IntNode(L"5"));
	st = decl->FullTypeCheck(st);
	delete decl;

	DeclAssignNode* decl2 = new DeclAssignNode(new PrimitiveTypeNode(L"int"), L"b", NULL);
	st = decl2->FullTypeCheck(st);
	delete decl2;

	std::list<ExprNode*> cases = std::list<ExprNode*>();
	cases.push_back(new IntNode(0));
	cases.push_back(new IntNode(1));
	cases.push_back(new IntNode(2));
	std::list<StmtNode*> stmts = std::list<StmtNode*>();
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(10))));
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(100))));
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(1000))));
	SwitchNode* sn = new SwitchNode(new VarNode(L"a"), cases, stmts, new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(10000))));
	st = sn->FullTypeCheck(st);
	CENE(errMsg, assertNum);

	//Constructing:
	//int a = 5;
	//int b;
	//switch(true)
	//{
	//	case 0:
	//		b = 10;
	//		break;
	//	case 1:
	//		b = 100;
	//		break;
	//	case 'c':
	//		b = 1000;
	//		break;
	//	default:
	//		b = 10000;
	//		break;
	//}

	cases = std::list<ExprNode*>();
	cases.push_back(new IntNode(0));
	cases.push_back(new IntNode(1));
	cases.push_back(new CharNode(L'c'));
	stmts = std::list<StmtNode*>();
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(10))));
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(100))));
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(1000))));
	sn = new SwitchNode(new KeywordNode(L"true"), cases, stmts, new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(10000))));
	st = sn->FullTypeCheck(st);
	CEHE(errMsg, assertNum);

	//Constructing:
	//int a = 5;
	//int b;
	//switch(a)
	//{
	//	case 0:
	//		b = 10;
	//		break;
	//	case 1:
	//		b = 100;
	//		break;
	//	case 2:
	//		b = 1000;
	//		break;
	//}

	cases = std::list<ExprNode*>();
	cases.push_back(new IntNode(0));
	cases.push_back(new IntNode(1));
	cases.push_back(new IntNode(2));
	stmts = std::list<StmtNode*>();
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(10))));
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(100))));
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(1000))));
	sn = new SwitchNode(new VarNode(L"a"), cases, stmts, NULL);
	st = sn->FullTypeCheck(st);
	CENE(errMsg, assertNum);

	//Constructing:
	//int a = 5;
	//int b;
	//switch(true)
	//{
	//	case 0:
	//		b = 10;
	//		break;
	//	case 1:
	//		b = 100;
	//		break;
	//	case 'c':
	//		b = 1000;
	//		break;
	//}

	cases = std::list<ExprNode*>();
	cases.push_back(new IntNode(0));
	cases.push_back(new IntNode(1));
	cases.push_back(new CharNode(L'c'));
	stmts = std::list<StmtNode*>();
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(10))));
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(100))));
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(1000))));
	sn = new SwitchNode(new KeywordNode(L"true"), cases, stmts, NULL);
	st = sn->FullTypeCheck(st);
	CEHE(errMsg, assertNum);

	return true;
}

extern "C" __declspec(dllexport) bool Test_ValidType_TypeCheck(TCHAR* errMsg)
{
	SymbolTable* st = new SymbolTable();
	st->EnterScope();
	int assertNum = 1;

	//Constructing:
	//foo a; --ERROR!
	//sizeof(foo); --ERROR!
	DeclAssignNode* dan = new DeclAssignNode(new PrimitiveTypeNode(L"foo"), L"a", NULL);
	*st = dan->FullTypeCheck(*st);
	CEHE(errMsg, assertNum);

	SizeOfNode* ton = new SizeOfNode(L"foo");
	ton->TypeOf(st);
	CEHE(errMsg, assertNum);

	return true;
}

extern "C" __declspec(dllexport) bool Test_StructDecl_TypeCheck(TCHAR* errMsg)
{
	SymbolTable* st = new SymbolTable();
	st->EnterScope();
	int assertNum = 1;
	
	//Constructing:
	//struct a {
	//	int x;
	//	void* y;
	//	char z;
	//};
	//struct x {
	//	int a;
	//	a b;	--ERROR!
	//	char c;
	//};
	//struct z {
	//	foo a;	--ERROR!
	//	int b;
	//	char c;
	//};
	//struct y {
	//	struct y a;	--ERROR!
	//	int b;
	//	char c;
	//};
	//struct b {
	//	int a;
	//	struct a b;
	//	char c;
	//};

	//Test #1
	std::list<std::wstring> names1 = std::list<std::wstring>();
	std::list<TypeNode*> types1 = std::list<TypeNode*>();
	names1.push_back(L"x");
	types1.push_back(new PrimitiveTypeNode(L"int"));
	names1.push_back(L"y");
	types1.push_back(new PrimitiveTypeNode(L"void", 1));
	names1.push_back(L"z");
	types1.push_back(new PrimitiveTypeNode(L"char"));
	StructDeclNode* struct1 = new StructDeclNode(L"a", L"", types1, names1);
	*st = struct1->FullTypeCheck(*st);
	delete struct1;
	CENE(errMsg, assertNum);

	//Test #2
	std::list<std::wstring> names2 = std::list<std::wstring>();
	std::list<TypeNode*> types2 = std::list<TypeNode*>();
	names2.push_back(L"a");
	types2.push_back(new PrimitiveTypeNode(L"int"));
	names2.push_back(L"b");
	types2.push_back(new PrimitiveTypeNode(L"a"));
	names2.push_back(L"c");
	types2.push_back(new PrimitiveTypeNode(L"char"));
	StructDeclNode* struct2 = new StructDeclNode(L"x", L"", types2, names2);
	*st = struct2->FullTypeCheck(*st);
	delete struct2;
	CEHE(errMsg, assertNum);

	//Test #3
	std::list<std::wstring> names3 = std::list<std::wstring>();
	std::list<TypeNode*> types3 = std::list<TypeNode*>();
	names3.push_back(L"a");
	types3.push_back(new PrimitiveTypeNode(L"foo"));
	names3.push_back(L"b");
	types3.push_back(new PrimitiveTypeNode(L"int"));
	names3.push_back(L"c");
	types3.push_back(new PrimitiveTypeNode(L"char"));
	StructDeclNode* struct3 = new StructDeclNode(L"z", L"", types3, names3);
	*st = struct3->FullTypeCheck(*st);
	delete struct3;
	CEHE(errMsg, assertNum);

	//Test #4
	std::list<std::wstring> names4 = std::list<std::wstring>();
	std::list<TypeNode*> types4 = std::list<TypeNode*>();
	names4.push_back(L"a");
	types4.push_back(new StructTypeNode(L"y"));
	names4.push_back(L"b");
	types4.push_back(new PrimitiveTypeNode(L"int"));
	names4.push_back(L"c");
	types4.push_back(new PrimitiveTypeNode(L"char"));
	StructDeclNode* struct4 = new StructDeclNode(L"y", L"", types4, names4);
	*st = struct4->FullTypeCheck(*st);
	delete struct4;
	CEHE(errMsg, assertNum);

	//Test #5
	std::list<std::wstring> names5 = std::list<std::wstring>();
	std::list<TypeNode*> types5 = std::list<TypeNode*>();
	names5.push_back(L"a");
	types5.push_back(new PrimitiveTypeNode(L"int"));
	names5.push_back(L"b");
	types5.push_back(new StructTypeNode(L"a"));
	names5.push_back(L"c");
	types5.push_back(new PrimitiveTypeNode(L"char"));
	StructDeclNode* struct5 = new StructDeclNode(L"b", L"", types5, names5);
	*st = struct5->FullTypeCheck(*st);
	delete struct5;
	CENE(errMsg, assertNum);

	return true;
}

extern "C" __declspec(dllexport) bool Test_StructInit_TypeCheck(TCHAR* errMsg)
{
	SymbolTable* st = new SymbolTable();
	st->EnterScope();
	int assertNum = 1;

	//Constructing:
	//struct foo {
	//	int a;
	//	int b;
	//};
	//struct foo f = {1, 2};
	//struct foo g = {f, 2}; -- ERROR!
	//struct foo h = {1}; --ERROR!
	//struct foo i = {1, 2, 3}; --ERROR!
	//struct foo j;
	std::list<std::wstring> names1 = std::list<std::wstring>();
	std::list<TypeNode*> types1 = std::list<TypeNode*>();
	names1.push_back(L"a");
	types1.push_back(new PrimitiveTypeNode(L"int"));
	names1.push_back(L"b");
	types1.push_back(new PrimitiveTypeNode(L"int"));
	StructDeclNode* struct1 = new StructDeclNode(L"foo", L"", types1, names1);
	*st = struct1->FullTypeCheck(*st);
	delete struct1;
	CENE(errMsg, assertNum);

	std::list<ExprNode*> inits1 = std::list<ExprNode*>();
	inits1.push_back(new IntNode(1));
	inits1.push_back(new IntNode(2));
	StructInitNode* init1 = new StructInitNode(new StructTypeNode(L"foo"), L"f", inits1);
	*st = init1->FullTypeCheck(*st);
	delete init1;
	CENE(errMsg, assertNum);
	
	std::list<ExprNode*> inits2 = std::list<ExprNode*>();
	inits2.push_back(new VarNode(L"f"));
	inits2.push_back(new IntNode(2));
	StructInitNode* init2 = new StructInitNode(new StructTypeNode(L"foo"), L"g", inits2);
	*st = init2->FullTypeCheck(*st);
	delete init2;
	CEHE(errMsg, assertNum);
	
	std::list<ExprNode*> inits3 = std::list<ExprNode*>();
	inits3.push_back(new IntNode(1));
	StructInitNode* init3 = new StructInitNode(new StructTypeNode(L"foo"), L"h", inits3);
	*st = init3->FullTypeCheck(*st);
	delete init3;
	CEHE(errMsg, assertNum);
	
	std::list<ExprNode*> inits4 = std::list<ExprNode*>();
	inits4.push_back(new IntNode(1));
	inits4.push_back(new IntNode(2));
	inits4.push_back(new IntNode(3));
	StructInitNode* init4 = new StructInitNode(new StructTypeNode(L"foo"), L"i", inits4);
	*st = init4->FullTypeCheck(*st);
	delete init4;
	CEHE(errMsg, assertNum);
	
	StructInitNode* init5 = new StructInitNode(new StructTypeNode(L"foo"), L"j", std::list<ExprNode*>());
	*st = init5->FullTypeCheck(*st);
	delete init5;
	CENE(errMsg, assertNum);
	
	return true;
}

extern "C" __declspec(dllexport) bool Test_StructDeclInit_TypeCheck(TCHAR* errMsg)
{
	SymbolTable* st = new SymbolTable();
	st->EnterScope();
	int assertNum = 1;

	//Constructing:
	//struct foo {
	//	int a;
	//	int b;
	//} f;
	std::list<std::wstring> names1 = std::list<std::wstring>();
	std::list<TypeNode*> types1 = std::list<TypeNode*>();
	names1.push_back(L"a");
	types1.push_back(new PrimitiveTypeNode(L"int"));
	names1.push_back(L"b");
	types1.push_back(new PrimitiveTypeNode(L"int"));
	StructDeclNode* struct1 = new StructDeclNode(L"foo", L"f", types1, names1);
	*st = struct1->FullTypeCheck(*st);
	delete struct1;
	CENE(errMsg, assertNum);

	return true;
}

extern "C" __declspec(dllexport) bool Test_StructReference_TypeCheck(TCHAR* errMsg)
{
	SymbolTable* st = new SymbolTable();
	st->EnterScope();
	int assertNum = 1;

	//Constructing:
	//struct foo {
	//	int a;
	//	int b;
	//} f;
	//f.a = 5;
	//f.a = f;	--ERROR!
	//f.c = 5;	--ERROR!
	//5.a = 10; --ERROR!
	std::list<std::wstring> names1 = std::list<std::wstring>();
	std::list<TypeNode*> types1 = std::list<TypeNode*>();
	names1.push_back(L"a");
	types1.push_back(new PrimitiveTypeNode(L"int"));
	names1.push_back(L"b");
	types1.push_back(new PrimitiveTypeNode(L"int"));
	StructDeclNode* struct1 = new StructDeclNode(L"foo", L"f", types1, names1);
	*st = struct1->FullTypeCheck(*st);
	delete struct1;
	CENE(errMsg, assertNum);

	StructReferenceNode* ref1 = new StructReferenceNode(new VarNode(L"f"), false, L"a");
	ExpressionStmt* stmt1 = new ExpressionStmt(new AssignNode(ref1, L"=", new IntNode(5)));
	*st = stmt1->FullTypeCheck(*st);
	delete stmt1;
	CENE(errMsg, assertNum);
	
	StructReferenceNode* ref2 = new StructReferenceNode(new VarNode(L"f"), false, L"a");
	ExpressionStmt* stmt2 = new ExpressionStmt(new AssignNode(ref2, L"=", new VarNode(L"f")));
	*st = stmt2->FullTypeCheck(*st);
	delete stmt2;
	CEHE(errMsg, assertNum);
	
	StructReferenceNode* ref3 = new StructReferenceNode(new VarNode(L"f"), false, L"c");
	ExpressionStmt* stmt3 = new ExpressionStmt(new AssignNode(ref3, L"=", new IntNode(5)));
	*st = stmt3->FullTypeCheck(*st);
	delete stmt3;
	CEHE(errMsg, assertNum);
	
	StructReferenceNode* ref4 = new StructReferenceNode(new IntNode(5), false, L"a");
	ExpressionStmt* stmt4 = new ExpressionStmt(new AssignNode(ref4, L"=", new IntNode(5)));
	*st = stmt4->FullTypeCheck(*st);
	delete stmt4;
	CEHE(errMsg, assertNum);
	
	return true;
}

extern "C" __declspec(dllexport) bool Test_StructArrowReference_TypeCheck(TCHAR* errMsg)
{
	//Not sure if getting a pointer to a struct is even possible at this point.
	return true;
}

//Flowgraph Generation Tests
extern "C" __declspec(dllexport) bool Test_ArrayOfInts_FGGen(TCHAR* errMsg)
{
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	fg->EnterFunction();
	MiniC::IR::AST::SymbolTable* st = new MiniC::IR::AST::SymbolTable();
	st->EnterScope();
	BasicBlock::BasicBlock* bb_test = new BasicBlock::BasicBlock();
	BasicBlock::BasicBlock* bb;
	int assertNum = 1;

	//Constructing:
	//int x[10];
	//x[0] = 5;
	bb_test->InsertInstruction(new Instruction(L"loadi", L"*tmp", L"10", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"<<i", L"*tmp", L"*tmp", L"1", L""));
	bb_test->InsertInstruction(new Instruction(L"pusharr", L"*tmp", L"*tmp", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"store", L"x", L"*tmp", L"0", L""));
	PrimitiveTypeNode* type = new PrimitiveTypeNode(L"int", 1, new IntNode(L"10"));
	DeclAssignNode* decl = new DeclAssignNode(type, L"x", NULL);
	*st = decl->FullTypeCheck(*st);
	fg = decl->GetFlowGraph(fg);
	bb = fg->GetBlocks().back();
	delete decl;
	CPEQ(bb, bb_test, errMsg, assertNum);

	bb_test->InsertInstruction(new Instruction(L"loadi", L"*tmp", L"5", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"push", L"", L"*tmp", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"load", L"*tmp", L"x", L"0", L""));
	bb_test->InsertInstruction(new Instruction(L"push", L"", L"*tmp", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"loadi", L"*tmp2", L"0", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"pop", L"*tmp", L"", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"<<i", L"*tmp2", L"*tmp2", L"1", L""));
	bb_test->InsertInstruction(new Instruction(L"+", L"*tmp2", L"*tmp", L"*tmp2", L""));
	bb_test->InsertInstruction(new Instruction(L"pop", L"*tmp", L"", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"storeadd", L"*tmp", L"*tmp2", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"move", L"*tmp", L"*tmp", L"", L""));
	ArrayNode* arr1 = new ArrayNode(new VarNode(L"x"), new IntNode(L"0"));
	AssignNode* assign1 = new AssignNode(arr1, L"=", new IntNode(L"5"));
	ExpressionStmt* stmt2 = new ExpressionStmt(assign1);
	*st = stmt2->FullTypeCheck(*st);
	fg = stmt2->GetFlowGraph(fg);
	bb = fg->GetBlocks().back();
	delete stmt2;
	CPEQ(bb, bb_test, errMsg, assertNum);

	delete fg;
	delete bb_test;

	return true;
}

extern "C" __declspec(dllexport) bool Test_ArrayOfPointers_FGGen(TCHAR* errMsg)
{
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	fg->EnterFunction();
	MiniC::IR::AST::SymbolTable* st = new MiniC::IR::AST::SymbolTable();
	st->EnterScope();
	BasicBlock::BasicBlock* bb_test = new BasicBlock::BasicBlock();
	BasicBlock::BasicBlock* bb;
	int assertNum = 1;

	//Constructing:
	//int* y[10];
	//*y[1] = 10;
	//int i = 5;
	//y[2] = &i;
	bb_test->InsertInstruction(new Instruction(L"loadi", L"*tmp", L"10", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"<<i", L"*tmp", L"*tmp", L"1", L""));
	bb_test->InsertInstruction(new Instruction(L"pusharr", L"*tmp", L"*tmp", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"store", L"y", L"*tmp", L"0", L""));
	PrimitiveTypeNode* type2 = new PrimitiveTypeNode(L"int", 2, new IntNode(L"10"));
	DeclAssignNode* decl2 = new DeclAssignNode(type2, L"y", NULL);
	*st = decl2->FullTypeCheck(*st);
	fg = decl2->GetFlowGraph(fg);
	bb = fg->GetBlocks().back();
	delete decl2;
	CPEQ(bb, bb_test, errMsg, assertNum);


	bb_test->InsertInstruction(new Instruction(L"loadi", L"*tmp", L"10", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"push", L"", L"*tmp", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"load", L"*tmp", L"y", L"0", L""));
	bb_test->InsertInstruction(new Instruction(L"push", L"", L"*tmp", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"loadi", L"*tmp2", L"1", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"pop", L"*tmp", L"", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"<<i", L"*tmp2", L"*tmp2", L"1", L""));
	bb_test->InsertInstruction(new Instruction(L"+", L"*tmp", L"*tmp", L"*tmp2", L""));
	bb_test->InsertInstruction(new Instruction(L"u*", L"*tmp2", L"*tmp", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"pop", L"*tmp", L"", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"storeadd", L"*tmp", L"*tmp2", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"move", L"*tmp", L"*tmp", L"", L""));
	ArrayNode* arr4 = new ArrayNode(new VarNode(L"y"), new IntNode(L"1"));
	UnaryNode* unary = new UnaryNode(L"*", arr4);
	AssignNode* assign4 = new AssignNode(unary, L"=", new IntNode(L"10"));
	ExpressionStmt* stmt5 = new ExpressionStmt(assign4);
	*st = stmt5->FullTypeCheck(*st);
	fg = stmt5->GetFlowGraph(fg);
	bb = fg->GetBlocks().back();
	delete stmt5;
	CPEQ(bb, bb_test, errMsg, assertNum);

	bb_test->InsertInstruction(new Instruction(L"loadi", L"*tmp", L"5", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"store", L"i", L"*tmp", L"0", L""));
	DeclAssignNode* decl3 = new DeclAssignNode(new PrimitiveTypeNode(L"int"), L"i", new IntNode(L"5"));
	*st = decl3->FullTypeCheck(*st);
	fg = decl3->GetFlowGraph(fg);
	bb = fg->GetBlocks().back();
	delete decl3;
	CPEQ(bb, bb_test, errMsg, assertNum);

	bb_test->InsertInstruction(new Instruction(L"u&", L"*tmp", L"i", L"0", L""));
	bb_test->InsertInstruction(new Instruction(L"push", L"", L"*tmp", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"load", L"*tmp", L"y", L"0", L""));
	bb_test->InsertInstruction(new Instruction(L"push", L"", L"*tmp", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"loadi", L"*tmp2", L"2", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"pop", L"*tmp", L"", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"<<i", L"*tmp2", L"*tmp2", L"1", L""));
	bb_test->InsertInstruction(new Instruction(L"+", L"*tmp2", L"*tmp", L"*tmp2", L""));
	bb_test->InsertInstruction(new Instruction(L"pop", L"*tmp", L"", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"storeadd", L"*tmp", L"*tmp2", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"move", L"*tmp", L"*tmp", L"", L""));
	UnaryNode* unary2 = new UnaryNode(L"&", new VarNode(L"i"));
	ArrayNode* arr5 = new ArrayNode(new VarNode(L"y"), new IntNode(L"2"));
	AssignNode* assign5 = new AssignNode(arr5, L"=", unary2);
	ExpressionStmt* stmt6 = new ExpressionStmt(assign5);
	*st = stmt6->FullTypeCheck(*st);
	fg = stmt6->GetFlowGraph(fg);
	bb = fg->GetBlocks().back();
	delete stmt6;
	CPEQ(bb, bb_test, errMsg, assertNum);

	
	delete fg;
	delete bb_test;
	return true;
}

extern "C" __declspec(dllexport) bool Test_ArrayOfChars_FGGen(TCHAR* errMsg)
{
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	fg->EnterFunction();
	MiniC::IR::AST::SymbolTable* st = new MiniC::IR::AST::SymbolTable();
	st->EnterScope();
	BasicBlock::BasicBlock* bb_test = new BasicBlock::BasicBlock();
	BasicBlock::BasicBlock* bb;
	int assertNum = 1;

	//Constructing:
	//char z[10];
	//z[1] = 'a';
	bb_test->InsertInstruction(new Instruction(L"loadi", L"*tmp", L"10", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"<<i", L"*tmp", L"*tmp", L"1", L""));
	bb_test->InsertInstruction(new Instruction(L"pusharr", L"*tmp", L"*tmp", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"store", L"z", L"*tmp", L"0", L""));
	PrimitiveTypeNode* type3 = new PrimitiveTypeNode(L"char", 1, new IntNode(L"10"));
	DeclAssignNode* decl4 = new DeclAssignNode(type3, L"z", NULL);
	*st = decl4->FullTypeCheck(*st);
	fg = decl4->GetFlowGraph(fg);
	bb = fg->GetBlocks().back();
	delete decl4;
	CPEQ(bb, bb_test, errMsg, assertNum);
	
	bb_test->InsertInstruction(new Instruction(L"loadi", L"*tmp", L"97", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"push", L"", L"*tmp", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"load", L"*tmp", L"z", L"0", L""));
	bb_test->InsertInstruction(new Instruction(L"push", L"", L"*tmp", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"loadi", L"*tmp2", L"1", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"pop", L"*tmp", L"", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"<<i", L"*tmp2", L"*tmp2", L"1", L""));
	bb_test->InsertInstruction(new Instruction(L"+", L"*tmp2", L"*tmp", L"*tmp2", L""));
	bb_test->InsertInstruction(new Instruction(L"pop", L"*tmp", L"", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"storeadd", L"*tmp", L"*tmp2", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"move", L"*tmp", L"*tmp", L"", L""));
	ArrayNode* arr7 = new ArrayNode(new VarNode(L"z"), new IntNode(L"1"));
	AssignNode* assign7 = new AssignNode(arr7, L"=", new CharNode(new std::wstring(L"'a'")));
	ExpressionStmt* stmt7 = new ExpressionStmt(assign7);
	*st = stmt7->FullTypeCheck(*st);
	fg = stmt7->GetFlowGraph(fg);
	bb = fg->GetBlocks().back();
	delete stmt7;
	CPEQ(bb, bb_test, errMsg, assertNum);
	
	delete fg;
	delete bb_test;
	return true;
}

extern "C" __declspec(dllexport) bool Test_ArrayWithStrangeIndicies_FGGen(TCHAR* errMsg)
{
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	fg->EnterFunction();
	MiniC::IR::AST::SymbolTable* st = new MiniC::IR::AST::SymbolTable();
	st->EnterScope();
	BasicBlock::BasicBlock* bb_test = new BasicBlock::BasicBlock();
	BasicBlock::BasicBlock* bb;
	int assertNum = 1;

	//Constructing:
	//int x = 5;
	//char y[x];
	//y[0] = 'a';
	
	bb_test->InsertInstruction(new Instruction(L"loadi", L"*tmp", L"5", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"store", L"x", L"*tmp", L"0", L""));
	DeclAssignNode* decl = new DeclAssignNode(new PrimitiveTypeNode(L"int"), L"x", new IntNode(L"5"));
	*st = decl->FullTypeCheck(*st);
	fg = decl->GetFlowGraph(fg);
	bb = fg->GetBlocks().back();
	delete decl;
	CPEQ(bb, bb_test, errMsg, assertNum);

	bb_test->InsertInstruction(new Instruction(L"load", L"*tmp", L"x", L"0", L""));
	bb_test->InsertInstruction(new Instruction(L"<<i", L"*tmp", L"*tmp", L"1", L""));
	bb_test->InsertInstruction(new Instruction(L"pusharr", L"*tmp", L"*tmp", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"store", L"y", L"*tmp", L"0", L""));
	PrimitiveTypeNode* type = new PrimitiveTypeNode(L"char", 1, new VarNode(L"x"));
	DeclAssignNode* decl2 = new DeclAssignNode(type, L"y", NULL);
	*st = decl2->FullTypeCheck(*st);
	fg = decl2->GetFlowGraph(fg);
	bb = fg->GetBlocks().back();
	delete decl2;
	CPEQ(bb, bb_test, errMsg, assertNum);
	
	
	bb_test->InsertInstruction(new Instruction(L"loadi", L"*tmp", L"97", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"push", L"", L"*tmp", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"load", L"*tmp", L"y", L"0", L""));
	bb_test->InsertInstruction(new Instruction(L"push", L"", L"*tmp", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"loadi", L"*tmp2", L"0", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"pop", L"*tmp", L"", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"<<i", L"*tmp2", L"*tmp2", L"1", L""));
	bb_test->InsertInstruction(new Instruction(L"+", L"*tmp2", L"*tmp", L"*tmp2", L""));
	bb_test->InsertInstruction(new Instruction(L"pop", L"*tmp", L"", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"storeadd", L"*tmp", L"*tmp2", L"", L""));
	bb_test->InsertInstruction(new Instruction(L"move", L"*tmp", L"*tmp", L"", L""));
	ArrayNode* arr = new ArrayNode(new VarNode(L"y"), new IntNode(L"0"));
	AssignNode* assign = new AssignNode(arr, L"=", new CharNode(new std::wstring(L"'a'")));
	ExpressionStmt* stmt = new ExpressionStmt(assign);
	*st = stmt->FullTypeCheck(*st);
	fg = stmt->GetFlowGraph(fg);
	bb = fg->GetBlocks().back();
	delete stmt;
	CPEQ(bb, bb_test, errMsg, assertNum);
	
	delete fg;
	delete bb_test;
	return true;
}

extern "C" __declspec(dllexport) bool Test_SwitchStatementWithDefault_FGGen(TCHAR* errMsg)
{
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg_test = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	fg->EnterFunction();
	MiniC::IR::AST::SymbolTable* st = new MiniC::IR::AST::SymbolTable();
	st->EnterScope();
	fg_test->EnterFunction();
	int assertNum = 1;

	//Constructing:
	//int a = 5;
	//int b;
	//switch(a)
	//{
	//	case 0:
	//		b = 10;
	//		break;
	//	case 1:
	//		b = 100;
	//		break;
	//	case 2:
	//		b = 1000;
	//		break;
	//	default:
	//		b = 10000;
	//		break;
	//}
	
	DeclAssignNode* decl = new DeclAssignNode(new PrimitiveTypeNode(L"int"), L"a", new IntNode(L"5"));
	*st = decl->FullTypeCheck(*st);
	fg = decl->GetFlowGraph(fg);
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"5", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"a", L"*tmp", L"0", L""));
	CPEQ(fg, fg_test, errMsg, assertNum);
	delete decl;

	DeclAssignNode* decl2 = new DeclAssignNode(new PrimitiveTypeNode(L"int"), L"b", NULL);
	*st = decl2->FullTypeCheck(*st);
	fg = decl2->GetFlowGraph(fg);
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"0", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"b", L"*tmp", L"0", L""));
	CPEQ(fg, fg_test, errMsg, assertNum);
	delete decl2;

	std::list<ExprNode*> cases = std::list<ExprNode*>();
	cases.push_back(new IntNode(0));
	cases.push_back(new IntNode(1));
	cases.push_back(new IntNode(2));
	std::list<StmtNode*> stmts = std::list<StmtNode*>();
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(10))));
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(100))));
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(1000))));
	SwitchNode* sn = new SwitchNode(new VarNode(L"a"), cases, stmts, new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(10000))));
	*st = sn->FullTypeCheck(*st);
	fg = sn->GetFlowGraph(fg);

	//Case 0 Branch
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"load", L"*tmp", L"a", L"0", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp2", L"0", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"beq", L"", L"*tmp", L"*tmp2", L""));
	fg_test->InsertNewBasicBlock(true);

	//Case 1 Branch
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp2", L"1", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"beq", L"", L"*tmp", L"*tmp2", L""));
	fg_test->InsertNewBasicBlock(true);

	//Case 2 Branch
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp2", L"2", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"beq", L"", L"*tmp", L"*tmp2", L""));
	fg_test->InsertNewBasicBlock(true);
	
	//Default
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"10000", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"b", L"*tmp", L"0", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"move", L"*tmp", L"*tmp", L"", L""));
	fg_test->InsertNewBasicBlock(false);
	
	//Case 0
	fg_test->InsertLink(0, 4);
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"10", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"b", L"*tmp", L"0", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"move", L"*tmp", L"*tmp", L"", L""));
	fg_test->InsertNewBasicBlock(false);
	
	//Case 1
	fg_test->InsertLink(1, 5);
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"100", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"b", L"*tmp", L"0", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"move", L"*tmp", L"*tmp", L"", L""));
	fg_test->InsertNewBasicBlock(false);
	
	//Case 2
	fg_test->InsertLink(2, 6);
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"1000", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"b", L"*tmp", L"0", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"move", L"*tmp", L"*tmp", L"", L""));
	fg_test->InsertNewBasicBlock(false);
	
	fg_test->InsertLink(3, 7);
	fg_test->InsertLink(4, 7);
	fg_test->InsertLink(5, 7);
	fg_test->InsertLink(6, 7);

	CPEQ(fg, fg_test, errMsg, assertNum);

	delete fg;
	return true;
}

extern "C" __declspec(dllexport) bool Test_SwitchStatement_FGGen(TCHAR* errMsg)
{
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg_test = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	fg->EnterFunction();
	MiniC::IR::AST::SymbolTable* st = new MiniC::IR::AST::SymbolTable();
	st->EnterScope();
	fg_test->EnterFunction();
	int assertNum = 1;

	//Constructing:
	//int a = 5;
	//int b;
	//switch(a)
	//{
	//	case 0:
	//		b = 10;
	//		break;
	//	case 1:
	//		b = 100;
	//		break;
	//	case 2:
	//		b = 1000;
	//		break;
	//}
	
	DeclAssignNode* decl = new DeclAssignNode(new PrimitiveTypeNode(L"int"), L"a", new IntNode(L"5"));
	*st = decl->FullTypeCheck(*st);
	fg = decl->GetFlowGraph(fg);
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"5", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"a", L"*tmp", L"0", L""));
	CPEQ(fg, fg_test, errMsg, assertNum);
	delete decl;

	DeclAssignNode* decl2 = new DeclAssignNode(new PrimitiveTypeNode(L"int"), L"b", NULL);
	*st = decl2->FullTypeCheck(*st);
	fg = decl2->GetFlowGraph(fg);
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"0", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"b", L"*tmp", L"0", L""));
	CPEQ(fg, fg_test, errMsg, assertNum);
	delete decl2;

	std::list<ExprNode*> cases = std::list<ExprNode*>();
	cases.push_back(new IntNode(0));
	cases.push_back(new IntNode(1));
	cases.push_back(new IntNode(2));
	std::list<StmtNode*> stmts = std::list<StmtNode*>();
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(10))));
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(100))));
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(1000))));
	SwitchNode* sn = new SwitchNode(new VarNode(L"a"), cases, stmts, NULL);
	*st = sn->FullTypeCheck(*st);
	fg = sn->GetFlowGraph(fg);

	//Case 0 Branch
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"load", L"*tmp", L"a", L"0", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp2", L"0", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"beq", L"", L"*tmp", L"*tmp2", L""));
	fg_test->InsertNewBasicBlock(true);

	//Case 1 Branch
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp2", L"1", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"beq", L"", L"*tmp", L"*tmp2", L""));
	fg_test->InsertNewBasicBlock(true);

	//Case 2 Branch
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp2", L"2", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"beq", L"", L"*tmp", L"*tmp2", L""));
	fg_test->InsertNewBasicBlock(true);
	
	//Default
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"jump", L"", L"", L"", L""));
	fg_test->InsertNewBasicBlock(false);
	
	//Case 0
	fg_test->InsertLink(0, 4);
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"10", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"b", L"*tmp", L"0", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"move", L"*tmp", L"*tmp", L"", L""));
	fg_test->InsertNewBasicBlock(false);
	
	//Case 1
	fg_test->InsertLink(1, 5);
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"100", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"b", L"*tmp", L"0", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"move", L"*tmp", L"*tmp", L"", L""));
	fg_test->InsertNewBasicBlock(false);
	
	//Case 2
	fg_test->InsertLink(2, 6);
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"1000", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"b", L"*tmp", L"0", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"move", L"*tmp", L"*tmp", L"", L""));
	fg_test->InsertNewBasicBlock(false);
	
	fg_test->InsertLink(3, 7);
	fg_test->InsertLink(4, 7);
	fg_test->InsertLink(5, 7);
	fg_test->InsertLink(6, 7);

	CPEQ(fg, fg_test, errMsg, assertNum);

	delete fg;
	return true;
}

extern "C" __declspec(dllexport) bool Test_StructInit_FGGen(TCHAR* errMsg)
{
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg_test = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	fg->EnterFunction();
	MiniC::IR::AST::SymbolTable* st = new MiniC::IR::AST::SymbolTable();
	st->EnterScope();
	fg_test->EnterFunction();
	int assertNum = 1;

	//Constructing:
	//struct foo {
	//	int a;
	//	int b;
	//};
	//struct foo f = {1, 2};
	//struct foo j;
	std::list<std::wstring> names1 = std::list<std::wstring>();
	std::list<TypeNode*> types1 = std::list<TypeNode*>();
	names1.push_back(L"a");
	types1.push_back(new PrimitiveTypeNode(L"int"));
	names1.push_back(L"b");
	types1.push_back(new PrimitiveTypeNode(L"int"));
	StructDeclNode* struct1 = new StructDeclNode(L"foo", L"", types1, names1);
	*st = struct1->FullTypeCheck(*st);
	fg = struct1->GetFlowGraph(fg);
	fg_test->AddStruct(L"foo");
	fg_test->AddStructField(L"foo", L"a", 0);
	fg_test->AddStructField(L"foo", L"b", 1);
	delete struct1;
	CPEQ(fg, fg_test, errMsg, assertNum);

	std::list<ExprNode*> inits1 = std::list<ExprNode*>();
	inits1.push_back(new IntNode(1));
	inits1.push_back(new IntNode(2));
	StructInitNode* init1 = new StructInitNode(new StructTypeNode(L"foo"), L"f", inits1);
	*st = init1->FullTypeCheck(*st);
	fg = init1->GetFlowGraph(fg);
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"1", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"f", L"*tmp", L"0", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"2", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"f", L"*tmp", L"1", L""));
	delete init1;
	CENE(errMsg, assertNum);
	
	StructInitNode* init2 = new StructInitNode(new StructTypeNode(L"foo"), L"j", std::list<ExprNode*>());
	*st = init2->FullTypeCheck(*st);
	fg = init2->GetFlowGraph(fg);
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"0", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"j", L"*tmp", L"0", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"0", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"j", L"*tmp", L"1", L""));
	delete init2;
	CENE(errMsg, assertNum);
	
	return true;
}

extern "C" __declspec(dllexport) bool Test_StructDeclInit_FGGen(TCHAR* errMsg)
{
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg_test = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	MiniC::IR::AST::SymbolTable* st = new MiniC::IR::AST::SymbolTable();
	st->EnterScope();
	int assertNum = 1;

	//Constructing:
	//struct foo {
	//	int a;
	//	int b;
	//} f;
	std::list<std::wstring> names1 = std::list<std::wstring>();
	std::list<TypeNode*> types1 = std::list<TypeNode*>();
	names1.push_back(L"a");
	types1.push_back(new PrimitiveTypeNode(L"int"));
	names1.push_back(L"b");
	types1.push_back(new PrimitiveTypeNode(L"int"));
	StructDeclNode* struct1 = new StructDeclNode(L"foo", L"f", types1, names1);
	*st = struct1->FullTypeCheck(*st);
	fg = struct1->GetFlowGraph(fg);
	fg_test->AddStruct(L"foo");
	fg_test->AddStructField(L"foo", L"a", 0);
	fg_test->AddStructField(L"foo", L"b", 1);
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"0", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"f", L"*tmp", L"0", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"0", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"f", L"*tmp", L"1", L""));
	fg_test->AddGlobalVar(L"f", 2);
	delete struct1;
	CPEQ(fg, fg_test, errMsg, assertNum);

	delete fg;
	delete fg_test;
	delete st;
	return true;
}

extern "C" __declspec(dllexport) bool Test_StructReference_FGGen(TCHAR* errMsg)
{
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg_test = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	MiniC::IR::AST::SymbolTable* st = new MiniC::IR::AST::SymbolTable();
	st->EnterScope();
	int assertNum = 1;

	//Constructing:
	//struct foo {
	//	int a;
	//	int b;
	//} f;
	//f.a = 5;
	//f.b = 10;
	std::list<std::wstring> names1 = std::list<std::wstring>();
	std::list<TypeNode*> types1 = std::list<TypeNode*>();
	names1.push_back(L"a");
	types1.push_back(new PrimitiveTypeNode(L"int"));
	names1.push_back(L"b");
	types1.push_back(new PrimitiveTypeNode(L"int"));
	StructDeclNode* struct1 = new StructDeclNode(L"foo", L"f", types1, names1);
	*st = struct1->FullTypeCheck(*st);
	fg = struct1->GetFlowGraph(fg);
	fg_test->AddStruct(L"foo");
	fg_test->AddStructField(L"foo", L"a", 0);
	fg_test->AddStructField(L"foo", L"b", 1);
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"0", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"f", L"*tmp", L"0", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"0", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"f", L"*tmp", L"1", L""));
	fg_test->AddGlobalVar(L"f", 2);
	delete struct1;
	CPEQ(fg, fg_test, errMsg, assertNum);
	
	fg->EnterFunction();
	fg_test->EnterFunction();
	StructReferenceNode* ref1 = new StructReferenceNode(new VarNode(L"f"), false, L"a");
	ExpressionStmt* stmt1 = new ExpressionStmt(new AssignNode(ref1, L"=", new IntNode(5)));
	*st = stmt1->FullTypeCheck(*st);
	fg = stmt1->GetFlowGraph(fg);
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"5", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"f", L"*tmp", L"0", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"move", L"*tmp", L"*tmp", L"", L""));
	delete stmt1;
	CPEQ(fg, fg_test, errMsg, assertNum);

	StructReferenceNode* ref2 = new StructReferenceNode(new VarNode(L"f"), false, L"b");
	ExpressionStmt* stmt2 = new ExpressionStmt(new AssignNode(ref2, L"=", new IntNode(10)));
	*st = stmt2->FullTypeCheck(*st);
	fg = stmt2->GetFlowGraph(fg);
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"10", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"f", L"*tmp", L"1", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"move", L"*tmp", L"*tmp", L"", L""));
	delete stmt2;
	CPEQ(fg, fg_test, errMsg, assertNum);

	return true;
}

extern "C" __declspec(dllexport) bool Test_StructArrowReference_FGGen(TCHAR* errMsg)
{
	//Not sure if getting a pointer to a struct is even possible at this point.
	return true;
}

//SymbolTable Tests
extern "C" __declspec(dllexport) bool Test_StructSymbolTableFunctions(TCHAR* errMsg)
{
	SymbolTable* st = new SymbolTable();
	int assertNum = 1;

	//Constructing:
	//struct a {
	//	int x;
	//	void* y;
	//	char z;
	//}
	//struct x {
	//	int a;
	//	struct a b;
	//	char c;
	//}
	std::list<std::wstring> names1 = std::list<std::wstring>();
	names1.push_back(L"x");
	names1.push_back(L"y");
	names1.push_back(L"z");
	std::list<std::wstring> types1 = std::list<std::wstring>();
	types1.push_back(L"int");
	types1.push_back(L"void*");
	types1.push_back(L"char");
	st->AddStruct(L"a", names1, types1);
	std::list<std::wstring> names2 = std::list<std::wstring>();
	names2.push_back(L"a");
	names2.push_back(L"b");
	names2.push_back(L"c");
	std::list<std::wstring> types2 = std::list<std::wstring>();
	types2.push_back(L"int");
	types2.push_back(L"int");
	types2.push_back(L"char");
	st->AddStruct(L"x", names2, types2);

	CSCP(st->GetStructFieldType(L"a", L"x"), L"int", errMsg, assertNum);
	CSCP(st->GetStructFieldType(L"a", L"y"), L"void*", errMsg, assertNum);
	CSCP(st->GetStructFieldType(L"a", L"b"), L"ERROR", errMsg, assertNum);
	CEHE(errMsg, assertNum);
	CSCP(st->GetStructFieldType(L"x", L"a"), L"int", errMsg, assertNum);
	CSCP(st->GetStructFieldType(L"x", L"c"), L"char", errMsg, assertNum);
	CSCP(st->GetStructFieldType(L"x", L"y"), L"ERROR", errMsg, assertNum);
	CEHE(errMsg, assertNum);	
	st->GetStructFieldNames(L"aaa");
	CEHE(errMsg, assertNum);
	return true;
}

//Optimization Tests
extern "C" __declspec(dllexport) bool Test_OptimizeUselessMoves(TCHAR* errMsg)
{
	int assertNum = 0;

	std::list<Instruction*> full_insts = std::list<Instruction*>();
	full_insts.push_back(new Instruction(L"move", L"$s0", L"$s1", L"", L""));
	full_insts.push_back(new Instruction(L"move", L"$s0", L"$s0", L"", L""));
	full_insts.push_back(new Instruction(L"move", L"$s1", L"$s0", L"", L""));
	full_insts.push_back(new Instruction(L"move", L"$s0", L"$s1", L"abcd", L""));
	full_insts.push_back(new Instruction(L"move", L"$s0", L"$s0", L"abcd", L""));
	full_insts.push_back(new Instruction(L"move", L"$s1", L"$s0", L"abcd", L""));
	full_insts.push_back(new Instruction(L"move", L"$s0", L"$s1", L"", L"efgh"));
	full_insts.push_back(new Instruction(L"move", L"$s0", L"$s0", L"", L"efgh"));
	full_insts.push_back(new Instruction(L"move", L"$s1", L"$s0", L"", L"efgh"));
	full_insts.push_back(new Instruction(L"move", L"$s0", L"$s1", L"abcd", L"efgh"));
	full_insts.push_back(new Instruction(L"move", L"$s0", L"$s0", L"abcd", L"efgh"));
	full_insts.push_back(new Instruction(L"move", L"$s1", L"$s0", L"abcd", L"efgh"));
	full_insts.push_back(new Instruction(L"addi", L"$s0", L"$s1", L"", L""));
	full_insts.push_back(new Instruction(L"addi", L"$s0", L"$s0", L"", L""));
	full_insts.push_back(new Instruction(L"addi", L"$s1", L"$s0", L"", L""));
	full_insts.push_back(new Instruction(L"addi", L"$s0", L"$s1", L"abcd", L""));
	full_insts.push_back(new Instruction(L"addi", L"$s0", L"$s0", L"abcd", L""));
	full_insts.push_back(new Instruction(L"addi", L"$s1", L"$s0", L"abcd", L""));
	full_insts.push_back(new Instruction(L"addi", L"$s0", L"$s1", L"", L"efgh"));
	full_insts.push_back(new Instruction(L"addi", L"$s0", L"$s0", L"", L"efgh"));
	full_insts.push_back(new Instruction(L"addi", L"$s1", L"$s0", L"", L"efgh"));
	full_insts.push_back(new Instruction(L"addi", L"$s0", L"$s1", L"abcd", L"efgh"));
	full_insts.push_back(new Instruction(L"addi", L"$s0", L"$s0", L"abcd", L"efgh"));
	full_insts.push_back(new Instruction(L"addi", L"$s1", L"$s0", L"abcd", L"efgh"));
	
	FlowGraph::FlowGraph* fg = new FlowGraph::FlowGraph();

	//Checks that multiple blocks are optimized.
	for(int i = 0; i < 2; i++)
	{
		fg->EnterFunction();
		fg->InsertNewBasicBlock(false);
		BOOST_FOREACH(Instruction* i, full_insts)
		{
			fg->InsertInstruction(i);
		}

		fg->ExitFunction();
	}

	// Check Global
	BOOST_FOREACH(Instruction* i, full_insts)
	{
		fg->InsertInstruction(i);
	}

	fg->Optimize();
	
	std::list<Instruction*> opt_insts = std::list<Instruction*>();
	opt_insts.push_back(new Instruction(L"move", L"$s0", L"$s1", L"", L""));
	opt_insts.push_back(new Instruction(L"move", L"$s1", L"$s0", L"", L""));
	opt_insts.push_back(new Instruction(L"move", L"$s0", L"$s1", L"abcd", L""));
	opt_insts.push_back(new Instruction(L"move", L"$s1", L"$s0", L"abcd", L""));
	opt_insts.push_back(new Instruction(L"move", L"$s0", L"$s1", L"", L"efgh"));
	opt_insts.push_back(new Instruction(L"move", L"$s1", L"$s0", L"", L"efgh"));
	opt_insts.push_back(new Instruction(L"move", L"$s0", L"$s1", L"abcd", L"efgh"));
	opt_insts.push_back(new Instruction(L"move", L"$s1", L"$s0", L"abcd", L"efgh"));
	opt_insts.push_back(new Instruction(L"addi", L"$s0", L"$s1", L"", L""));
	opt_insts.push_back(new Instruction(L"addi", L"$s0", L"$s0", L"", L""));
	opt_insts.push_back(new Instruction(L"addi", L"$s1", L"$s0", L"", L""));
	opt_insts.push_back(new Instruction(L"addi", L"$s0", L"$s1", L"abcd", L""));
	opt_insts.push_back(new Instruction(L"addi", L"$s0", L"$s0", L"abcd", L""));
	opt_insts.push_back(new Instruction(L"addi", L"$s1", L"$s0", L"abcd", L""));
	opt_insts.push_back(new Instruction(L"addi", L"$s0", L"$s1", L"", L"efgh"));
	opt_insts.push_back(new Instruction(L"addi", L"$s0", L"$s0", L"", L"efgh"));
	opt_insts.push_back(new Instruction(L"addi", L"$s1", L"$s0", L"", L"efgh"));
	opt_insts.push_back(new Instruction(L"addi", L"$s0", L"$s1", L"abcd", L"efgh"));
	opt_insts.push_back(new Instruction(L"addi", L"$s0", L"$s0", L"abcd", L"efgh"));
	opt_insts.push_back(new Instruction(L"addi", L"$s1", L"$s0", L"abcd", L"efgh"));
	BasicBlock::BasicBlock* opt_block = new BasicBlock::BasicBlock(opt_insts);

	std::list<BasicBlock::BasicBlock*> blocks = fg->GetBlocks();
	CPNN(blocks.front(), errMsg, assertNum);
	CPEQ(opt_block, blocks.front(), errMsg, assertNum);
	CPEQ(opt_block, blocks.back(), errMsg, assertNum);
	CPEQ(opt_block, fg->GetGlobalBlock(), errMsg, assertNum);

	return true;
}

extern "C" __declspec(dllexport) bool Test_OptimizeBranches(TCHAR* errMsg)
{
	int assertNum = 0;

	std::list<Instruction*> full_insts = std::list<Instruction*>();
	full_insts.push_back(new Instruction(L"move", L"$s0", L"$s1", L"", L""));
	full_insts.push_back(new Instruction(L">", L"*tmp", L"x", L"y", L""));
	full_insts.push_back(new Instruction(L"if", L"*tmp", L"", L"", L""));
	full_insts.push_back(new Instruction(L">", L"*tmp", L"x", L"y", L""));
	full_insts.push_back(new Instruction(L"push", L"", L"*tmp", L"", L""));
	full_insts.push_back(new Instruction(L">=", L"*tmp", L"x", L"y", L""));
	full_insts.push_back(new Instruction(L"if", L"*tmp", L"", L"", L""));
	full_insts.push_back(new Instruction(L">=", L"*tmp", L"x", L"y", L""));
	full_insts.push_back(new Instruction(L"push", L"", L"*tmp", L"", L""));
	full_insts.push_back(new Instruction(L"<", L"*tmp", L"x", L"y", L""));
	full_insts.push_back(new Instruction(L"if", L"*tmp", L"", L"", L""));
	full_insts.push_back(new Instruction(L"<", L"*tmp", L"x", L"y", L""));
	full_insts.push_back(new Instruction(L"push", L"", L"*tmp", L"", L""));
	full_insts.push_back(new Instruction(L"<=", L"*tmp", L"x", L"y", L""));
	full_insts.push_back(new Instruction(L"if", L"*tmp", L"", L"", L""));
	full_insts.push_back(new Instruction(L"<=", L"*tmp", L"x", L"y", L""));
	full_insts.push_back(new Instruction(L"push", L"", L"*tmp", L"", L""));
	full_insts.push_back(new Instruction(L"==", L"*tmp", L"x", L"y", L""));
	full_insts.push_back(new Instruction(L"if", L"*tmp", L"", L"", L""));
	full_insts.push_back(new Instruction(L"==", L"*tmp", L"x", L"y", L""));
	full_insts.push_back(new Instruction(L"push", L"", L"*tmp", L"", L""));
	full_insts.push_back(new Instruction(L"!=", L"*tmp", L"x", L"y", L""));
	full_insts.push_back(new Instruction(L"if", L"*tmp", L"", L"", L""));
	full_insts.push_back(new Instruction(L"!=", L"*tmp", L"x", L"y", L""));
	full_insts.push_back(new Instruction(L"push", L"", L"*tmp", L"", L""));
	full_insts.push_back(new Instruction(L"addi", L"$s1", L"$s0", L"", L""));
	full_insts.push_back(new Instruction(L"!=", L"*tmp", L"x", L"y", L""));
	full_insts.push_back(new Instruction(L"if", L"*tmp", L"", L"", L""));
	
	FlowGraph::FlowGraph* fg = new FlowGraph::FlowGraph();

	//Checks that multiple blocks are optimized.
	for(int i = 0; i < 2; i++)
	{
		fg->EnterFunction();
		fg->InsertNewBasicBlock(false);
		BOOST_FOREACH(Instruction* i, full_insts)
		{
			fg->InsertInstruction(i);
		}

		fg->ExitFunction();
	}

	// Check Global
	BOOST_FOREACH(Instruction* i, full_insts)
	{
		fg->InsertInstruction(i);
	}

	fg->Optimize();
	
	std::list<Instruction*> opt_insts = std::list<Instruction*>();
	opt_insts.push_back(new Instruction(L"move", L"$s0", L"$s1", L"", L""));
	opt_insts.push_back(new Instruction(L"blte", L"", L"x", L"y", L""));
	opt_insts.push_back(new Instruction(L">", L"*tmp", L"x", L"y", L""));
	opt_insts.push_back(new Instruction(L"push", L"", L"*tmp", L"", L""));
	opt_insts.push_back(new Instruction(L"blt", L"", L"x", L"y", L""));
	opt_insts.push_back(new Instruction(L">=", L"*tmp", L"x", L"y", L""));
	opt_insts.push_back(new Instruction(L"push", L"", L"*tmp", L"", L""));
	opt_insts.push_back(new Instruction(L"bgte", L"", L"x", L"y", L""));
	opt_insts.push_back(new Instruction(L"<", L"*tmp", L"x", L"y", L""));
	opt_insts.push_back(new Instruction(L"push", L"", L"*tmp", L"", L""));
	opt_insts.push_back(new Instruction(L"bgt", L"", L"x", L"y", L""));
	opt_insts.push_back(new Instruction(L"<=", L"*tmp", L"x", L"y", L""));
	opt_insts.push_back(new Instruction(L"push", L"", L"*tmp", L"", L""));
	opt_insts.push_back(new Instruction(L"bne", L"", L"x", L"y", L""));
	opt_insts.push_back(new Instruction(L"==", L"*tmp", L"x", L"y", L""));
	opt_insts.push_back(new Instruction(L"push", L"", L"*tmp", L"", L""));
	opt_insts.push_back(new Instruction(L"beq", L"", L"x", L"y", L""));
	opt_insts.push_back(new Instruction(L"!=", L"*tmp", L"x", L"y", L""));
	opt_insts.push_back(new Instruction(L"push", L"", L"*tmp", L"", L""));
	opt_insts.push_back(new Instruction(L"addi", L"$s1", L"$s0", L"", L""));
	opt_insts.push_back(new Instruction(L"beq", L"", L"x", L"y", L""));
	BasicBlock::BasicBlock* opt_block = new BasicBlock::BasicBlock(opt_insts);

	std::list<BasicBlock::BasicBlock*> blocks = fg->GetBlocks();
	CPNN(blocks.front(), errMsg, assertNum);
	CPEQ(opt_block, blocks.front(), errMsg, assertNum);
	CPEQ(opt_block, blocks.back(), errMsg, assertNum);
	CPEQ(opt_block, fg->GetGlobalBlock(), errMsg, assertNum);

	return true;
}

extern "C" __declspec(dllexport) bool Test_OptimizeConstantAddExpressions(TCHAR* errMsg)
{
	SymbolTable st = SymbolTable();
	int assertNum = 1;

	//Set up AST for testing.
	//Constructing:
	//int a = 5 + 3;
	//int b = 5 + a;
	//int c = b + a;
	//int d = a + 5;
	PrimitiveTypeNode* test_type = new PrimitiveTypeNode(L"int");
	IntNode* inteight = new IntNode(L"8");
	DeclAssignNode* test_decl = new DeclAssignNode(test_type, L"a", inteight);
	PrimitiveTypeNode* type = new PrimitiveTypeNode(L"int");
	IntNode* intfive = new IntNode(L"5");
	IntNode* intthree = new IntNode(L"3");
	BinaryNode* bn = new BinaryNode(intfive, L"+", intthree);
	DeclAssignNode* decl = new DeclAssignNode(type, L"a", bn);
	decl->Optimize(st);
	CPEQ(decl, test_decl, errMsg, assertNum);
	delete decl;
	delete test_decl;

	test_type = new PrimitiveTypeNode(L"int");
	IntNode* test_intfive = new IntNode(L"5");
	VarNode* test_vara = new VarNode(L"a");
	BinaryNode* test_bin = new BinaryNode(test_intfive, L"+", test_vara);
	test_decl = new DeclAssignNode(test_type, L"b", test_bin);
	type = new PrimitiveTypeNode(L"int");
	intfive = new IntNode(L"5");
	VarNode* vara = new VarNode(L"a");
	bn = new BinaryNode(intfive, L"+", vara);
	decl = new DeclAssignNode(type, L"b", bn);
	decl->Optimize(st);
	CPEQ(decl, test_decl, errMsg, assertNum);
	delete decl;
	delete test_decl;

	test_type = new PrimitiveTypeNode(L"int");
	VarNode* test_varb = new VarNode(L"b");
	test_vara = new VarNode(L"a");
	test_bin = new BinaryNode(test_varb, L"+", test_vara);
	test_decl = new DeclAssignNode(test_type, L"c", test_bin);
	type = new PrimitiveTypeNode(L"int");
	vara = new VarNode(L"a");
	VarNode* varb = new VarNode(L"b");
	bn = new BinaryNode(varb, L"+", vara);
	decl = new DeclAssignNode(type, L"c", bn);
	decl->Optimize(st);
	CPEQ(decl, test_decl, errMsg, assertNum);
	delete decl;
	delete test_decl;

	test_type = new PrimitiveTypeNode(L"int");
	test_intfive = new IntNode(L"5");
	test_vara = new VarNode(L"a");
	test_bin = new BinaryNode(test_vara, L"+", test_intfive);
	test_decl = new DeclAssignNode(test_type, L"d", test_bin);
	type = new PrimitiveTypeNode(L"int");
	intfive = new IntNode(L"5");
	vara = new VarNode(L"a");
	bn = new BinaryNode(vara, L"+", intfive);
	decl = new DeclAssignNode(type, L"d", bn);
	decl->Optimize(st);
	CPEQ(decl, test_decl, errMsg, assertNum);
	delete decl;
	delete test_decl;

	return true;
}

extern "C" __declspec(dllexport) bool Test_OptimizeConstantBoolExpressions(TCHAR* errMsg)
{
	SymbolTable st = SymbolTable();
	int assertNum = 1;

	//Set up AST for testing.
	//Constructing:
	//bool a = 5 > 3;
	//bool b = 5 > a;
	//bool c = b > a;
	//bool d = 3 > 5;
	//bool e = true;
	//bool f = !(3 > 5);
	PrimitiveTypeNode* test_type = new PrimitiveTypeNode(L"bool");
	IntNode* truebool = new IntNode(L"1");
	DeclAssignNode* test_decl = new DeclAssignNode(test_type, L"a", truebool);
	PrimitiveTypeNode* type = new PrimitiveTypeNode(L"bool");
	IntNode* intfive = new IntNode(L"5");
	IntNode* intthree = new IntNode(L"3");
	BinaryNode* bn = new BinaryNode(intfive, L">", intthree);
	DeclAssignNode* decl = new DeclAssignNode(type, L"a", bn);
	decl->Optimize(st);
	CPEQ(decl, test_decl, errMsg, assertNum);
	delete decl;
	delete test_decl;

	test_type = new PrimitiveTypeNode(L"bool");
	IntNode* test_intfive = new IntNode(L"5");
	VarNode* test_vara = new VarNode(L"a");
	BinaryNode* test_bin = new BinaryNode(test_intfive, L">", test_vara);
	test_decl = new DeclAssignNode(test_type, L"b", test_bin);
	type = new PrimitiveTypeNode(L"bool");
	intfive = new IntNode(L"5");
	VarNode* vara = new VarNode(L"a");
	bn = new BinaryNode(intfive, L">", vara);
	decl = new DeclAssignNode(type, L"b", bn);
	decl->Optimize(st);
	CPEQ(decl, test_decl, errMsg, assertNum);
	delete decl;
	delete test_decl;

	test_type = new PrimitiveTypeNode(L"bool");
	VarNode* test_varb = new VarNode(L"b");
	test_vara = new VarNode(L"a");
	test_bin = new BinaryNode(test_varb, L">", test_vara);
	test_decl = new DeclAssignNode(test_type, L"c", test_bin);
	type = new PrimitiveTypeNode(L"bool");
	vara = new VarNode(L"a");
	VarNode* varb = new VarNode(L"b");
	bn = new BinaryNode(varb, L">", vara);
	decl = new DeclAssignNode(type, L"c", bn);
	decl->Optimize(st);
	CPEQ(decl, test_decl, errMsg, assertNum);
	delete decl;
	delete test_decl;

	test_type = new PrimitiveTypeNode(L"bool");
	IntNode* falseint = new IntNode(L"0");	
	test_decl = new DeclAssignNode(test_type, L"d", falseint);
	type = new PrimitiveTypeNode(L"bool");
	intfive = new IntNode(L"5");
	intthree = new IntNode(L"3");
	bn = new BinaryNode(intthree, L">", intfive);
	decl = new DeclAssignNode(type, L"d", bn);
	decl->Optimize(st);
	CPEQ(decl, test_decl, errMsg, assertNum);
	delete decl;
	delete test_decl;

	test_type = new PrimitiveTypeNode(L"bool");
	IntNode* test_falsebool = new IntNode(L"1");	
	test_decl = new DeclAssignNode(test_type, L"e", test_falsebool);
	type = new PrimitiveTypeNode(L"bool");
	KeywordNode* falsebool = new KeywordNode(L"true");	
	decl = new DeclAssignNode(type, L"e", falsebool);
	decl->Optimize(st);
	CPEQ(decl, test_decl, errMsg, assertNum);
	delete decl;
	delete test_decl;

	test_type = new PrimitiveTypeNode(L"bool");
	falseint = new IntNode(L"1");	
	test_decl = new DeclAssignNode(test_type, L"f", falseint);
	type = new PrimitiveTypeNode(L"bool");
	intfive = new IntNode(L"5");
	intthree = new IntNode(L"3");
	bn = new BinaryNode(intthree, L">", intfive);
	UnaryNode* un = new UnaryNode(L"!", bn);
	decl = new DeclAssignNode(type, L"f", un);
	decl->Optimize(st);
	CPEQ(decl, test_decl, errMsg, assertNum);
	delete decl;
	delete test_decl;

	return true;
}

extern "C" __declspec(dllexport) bool Test_OptimizeConstantShiftExpressions(TCHAR* errMsg)
{
	SymbolTable st = SymbolTable();
	int assertNum = 1;

	//Set up AST for testing.
	//Constructing:
	//int a = 5 << 3;
	//int b = 5 << a;
	//int c = b << a;
	//int d = a << 5;
	PrimitiveTypeNode* test_type = new PrimitiveTypeNode(L"int");
	IntNode* inteight = new IntNode(L"40");
	DeclAssignNode* test_decl = new DeclAssignNode(test_type, L"a", inteight);
	PrimitiveTypeNode* type = new PrimitiveTypeNode(L"int");
	IntNode* intfive = new IntNode(L"5");
	IntNode* intthree = new IntNode(L"3");
	BinaryNode* bn = new BinaryNode(intfive, L"<<", intthree);
	DeclAssignNode* decl = new DeclAssignNode(type, L"a", bn);
	decl->Optimize(st);
	CPEQ(decl, test_decl, errMsg, assertNum);
	delete decl;
	delete test_decl;

	test_type = new PrimitiveTypeNode(L"int");
	IntNode* test_intfive = new IntNode(L"5");
	VarNode* test_vara = new VarNode(L"a");
	BinaryNode* test_bin = new BinaryNode(test_intfive, L"<<", test_vara);
	test_decl = new DeclAssignNode(test_type, L"b", test_bin);
	type = new PrimitiveTypeNode(L"int");
	intfive = new IntNode(L"5");
	VarNode* vara = new VarNode(L"a");
	bn = new BinaryNode(intfive, L"<<", vara);
	decl = new DeclAssignNode(type, L"b", bn);
	decl->Optimize(st);
	CPEQ(decl, test_decl, errMsg, assertNum);
	delete decl;
	delete test_decl;

	test_type = new PrimitiveTypeNode(L"int");
	VarNode* test_varb = new VarNode(L"b");
	test_vara = new VarNode(L"a");
	test_bin = new BinaryNode(test_varb, L"<<", test_vara);
	test_decl = new DeclAssignNode(test_type, L"c", test_bin);
	type = new PrimitiveTypeNode(L"int");
	vara = new VarNode(L"a");
	VarNode* varb = new VarNode(L"b");
	bn = new BinaryNode(varb, L"<<", vara);
	decl = new DeclAssignNode(type, L"c", bn);
	decl->Optimize(st);
	CPEQ(decl, test_decl, errMsg, assertNum);
	delete decl;
	delete test_decl;

	test_type = new PrimitiveTypeNode(L"int");
	test_intfive = new IntNode(L"5");
	test_vara = new VarNode(L"a");
	test_bin = new BinaryNode(test_vara, L"<<", test_intfive);
	test_decl = new DeclAssignNode(test_type, L"d", test_bin);
	type = new PrimitiveTypeNode(L"int");
	intfive = new IntNode(L"5");
	vara = new VarNode(L"a");
	bn = new BinaryNode(vara, L"<<", intfive);
	decl = new DeclAssignNode(type, L"d", bn);
	decl->Optimize(st);
	CPEQ(decl, test_decl, errMsg, assertNum);
	delete decl;
	delete test_decl;

	return true;
}

extern "C" __declspec(dllexport) bool Test_OptimizeConstantUnaryExpressions(TCHAR* errMsg)
{
	SymbolTable st = SymbolTable();
	int assertNum = 1;

	//Set up AST for testing.
	//Constructing:
	//int a = -5;
	//int b = -(5 + 3);
	//int c = -(a + b);
	//int d = +(5 + 3);
	//int e = ~(5 + 3);
	PrimitiveTypeNode* test_type = new PrimitiveTypeNode(L"int");
	IntNode* inteight = new IntNode(L"-5");
	DeclAssignNode* test_decl = new DeclAssignNode(test_type, L"a", inteight);
	PrimitiveTypeNode* type = new PrimitiveTypeNode(L"int");
	IntNode* intfive = new IntNode(L"5");
	UnaryNode* un = new UnaryNode(L"-", intfive);
	DeclAssignNode* decl = new DeclAssignNode(type, L"a", un);
	decl->Optimize(st);
	CPEQ(decl, test_decl, errMsg, assertNum);
	delete decl;
	delete test_decl;

	test_type = new PrimitiveTypeNode(L"int");
	IntNode* test_intnegeight = new IntNode(L"-8");
	test_decl = new DeclAssignNode(test_type, L"b", test_intnegeight);
	type = new PrimitiveTypeNode(L"int");
	intfive = new IntNode(L"5");
	IntNode* intthree = new IntNode(L"3");
	BinaryNode* bn = new BinaryNode(intfive, L"+", intthree);
	un = new UnaryNode(L"-", bn);
	decl = new DeclAssignNode(type, L"b", un);
	decl->Optimize(st);
	CPEQ(decl, test_decl, errMsg, assertNum);
	delete decl;
	delete test_decl;

	test_type = new PrimitiveTypeNode(L"int");
	VarNode* test_varb = new VarNode(L"b");
	VarNode* test_vara = new VarNode(L"a");
	BinaryNode* test_bin = new BinaryNode(test_varb, L"+", test_vara);
	UnaryNode* test_un = new UnaryNode(L"-", test_bin);
	test_decl = new DeclAssignNode(test_type, L"c", test_un);
	type = new PrimitiveTypeNode(L"int");
	VarNode* vara = new VarNode(L"a");
	VarNode* varb = new VarNode(L"b");
	bn = new BinaryNode(varb, L"+", vara);
	un = new UnaryNode(L"-", bn);
	decl = new DeclAssignNode(type, L"c", un);
	decl->Optimize(st);
	CPEQ(decl, test_decl, errMsg, assertNum);
	delete decl;
	delete test_decl;

	test_type = new PrimitiveTypeNode(L"int");
	IntNode* test_inteight = new IntNode(L"8");
	test_decl = new DeclAssignNode(test_type, L"d", test_inteight);
	type = new PrimitiveTypeNode(L"int");
	intfive = new IntNode(L"5");
	intthree = new IntNode(L"3");
	bn = new BinaryNode(intfive, L"+", intthree);
	un = new UnaryNode(L"+", bn);
	decl = new DeclAssignNode(type, L"d", un);
	decl->Optimize(st);
	CPEQ(decl, test_decl, errMsg, assertNum);
	delete decl;
	delete test_decl;
	
	test_type = new PrimitiveTypeNode(L"int");
	test_inteight = new IntNode(L"-9");
	test_decl = new DeclAssignNode(test_type, L"e", test_inteight);
	type = new PrimitiveTypeNode(L"int");
	intfive = new IntNode(L"5");
	intthree = new IntNode(L"3");
	bn = new BinaryNode(intfive, L"+", intthree);
	un = new UnaryNode(L"~", bn);
	decl = new DeclAssignNode(type, L"e", un);
	decl->Optimize(st);
	CPEQ(decl, test_decl, errMsg, assertNum);
	delete decl;
	delete test_decl;
	return true;
}

extern "C" __declspec(dllexport) bool Test_OptimizeConstantSwitchStatements(TCHAR* errMsg)
{
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg_test = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	fg->EnterFunction();
	MiniC::IR::AST::SymbolTable* st = new MiniC::IR::AST::SymbolTable();
	st->EnterScope();
	fg_test->EnterFunction();
	int assertNum = 1;

	//Constructing:
	//int b;
	//switch(0)
	//{
	//	case 0:
	//		b = 10;
	//		break;
	//	case 1:
	//		b = 100;
	//		break;
	//	case 2:
	//		b = 1000;
	//		break;
	//	default:
	//		b = 10000;
	//		break;
	//}

	DeclAssignNode* decl2 = new DeclAssignNode(new PrimitiveTypeNode(L"int"), L"b", NULL);
	*st = decl2->FullTypeCheck(*st);
	fg = decl2->GetFlowGraph(fg);
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"0", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"b", L"*tmp", L"0", L""));
	CPEQ(fg, fg_test, errMsg, assertNum);
	delete decl2;

	std::list<ExprNode*> cases = std::list<ExprNode*>();
	cases.push_back(new IntNode(0));
	cases.push_back(new IntNode(1));
	cases.push_back(new IntNode(2));
	std::list<StmtNode*> stmts = std::list<StmtNode*>();
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(10))));
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(100))));
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(1000))));
	SwitchNode* sn = new SwitchNode(new IntNode(0), cases, stmts, new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(10000))));
	*st = sn->FullTypeCheck(*st);
	fg = sn->GetFlowGraph(fg);
	
	//Case 0
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"10", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"b", L"*tmp", L"0", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"move", L"*tmp", L"*tmp", L"", L""));

	CPEQ(fg, fg_test, errMsg, assertNum);

	delete fg;
	return true;
}

extern "C" __declspec(dllexport) bool Test_OptimizeVariableSwitchStatements(TCHAR* errMsg)
{
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg_test = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	fg->EnterFunction();
	MiniC::IR::AST::SymbolTable* st = new MiniC::IR::AST::SymbolTable();
	st->EnterScope();
	fg_test->EnterFunction();
	int assertNum = 1;

	//Constructing:
	//int a = 5;
	//int b;
	//switch(a)
	//{
	//	case 0:
	//		b = 10;
	//		break;
	//	case a:
	//		b = 100;
	//		break;
	//	case 2:
	//		b = 1000;
	//		break;
	//	default:
	//		b = 10000;
	//		break;
	//}
	
	DeclAssignNode* decl = new DeclAssignNode(new PrimitiveTypeNode(L"int"), L"a", new IntNode(L"5"));
	*st = decl->FullTypeCheck(*st);
	fg = decl->GetFlowGraph(fg);
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"5", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"a", L"*tmp", L"0", L""));
	CPEQ(fg, fg_test, errMsg, assertNum);
	delete decl;

	DeclAssignNode* decl2 = new DeclAssignNode(new PrimitiveTypeNode(L"int"), L"b", NULL);
	*st = decl2->FullTypeCheck(*st);
	fg = decl2->GetFlowGraph(fg);
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"0", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"b", L"*tmp", L"0", L""));
	CPEQ(fg, fg_test, errMsg, assertNum);
	delete decl2;

	std::list<ExprNode*> cases = std::list<ExprNode*>();
	cases.push_back(new IntNode(0));
	cases.push_back(new VarNode(L"a"));
	cases.push_back(new IntNode(2));
	std::list<StmtNode*> stmts = std::list<StmtNode*>();
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(10))));
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(100))));
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(1000))));
	SwitchNode* sn = new SwitchNode(new VarNode(L"a"), cases, stmts, new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(10000))));
	*st = sn->FullTypeCheck(*st);
	fg = sn->GetFlowGraph(fg);
	
	//Case 1
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"100", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"b", L"*tmp", L"0", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"move", L"*tmp", L"*tmp", L"", L""));

	CPEQ(fg, fg_test, errMsg, assertNum);

	delete fg;
	return true;
}

extern "C" __declspec(dllexport) bool Test_OptimizeConstantDefaultSwitchStatements(TCHAR* errMsg)
{
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg_test = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	fg->EnterFunction();
	MiniC::IR::AST::SymbolTable* st = new MiniC::IR::AST::SymbolTable();
	st->EnterScope();
	fg_test->EnterFunction();
	int assertNum = 1;

	//Constructing:
	//int b;
	//switch(3)
	//{
	//	case 0:
	//		b = 10;
	//		break;
	//	case 1:
	//		b = 100;
	//		break;
	//	case 2:
	//		b = 1000;
	//		break;
	//	default:
	//		b = 10000;
	//		break;
	//}

	DeclAssignNode* decl2 = new DeclAssignNode(new PrimitiveTypeNode(L"int"), L"b", NULL);
	*st = decl2->FullTypeCheck(*st);
	fg = decl2->GetFlowGraph(fg);
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"0", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"b", L"*tmp", L"0", L""));
	CPEQ(fg, fg_test, errMsg, assertNum);
	delete decl2;

	std::list<ExprNode*> cases = std::list<ExprNode*>();
	cases.push_back(new IntNode(0));
	cases.push_back(new IntNode(1));
	cases.push_back(new IntNode(2));
	std::list<StmtNode*> stmts = std::list<StmtNode*>();
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(10))));
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(100))));
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(1000))));
	SwitchNode* sn = new SwitchNode(new IntNode(3), cases, stmts, new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(10000))));
	*st = sn->FullTypeCheck(*st);
	fg = sn->GetFlowGraph(fg);
	
	//Default Case
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"10000", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"push", L"", L"*tmp", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"pop", L"*tmp", L"", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"b", L"*tmp", L"0", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"move", L"*tmp", L"*tmp", L"", L""));

	CPEQ(fg, fg_test, errMsg, assertNum);

	delete fg;
	return true;
}

extern "C" __declspec(dllexport) bool Test_OptimizeStackOperations(TCHAR* errMsg)
{
	int assertNum = 0;

	std::list<Instruction*> full_insts = std::list<Instruction*>();
	full_insts.push_back(new Instruction(L"push", L"", L"*tmp", L"", L""));
	full_insts.push_back(new Instruction(L"pop", L"*tmp", L"", L"", L""));
	full_insts.push_back(new Instruction(L"push", L"", L"*tmp2", L"", L""));
	full_insts.push_back(new Instruction(L"addi", L"*tmp", L"tmp", L"5", L""));
	full_insts.push_back(new Instruction(L"u-", L"*tmp", L"tmp", L"", L""));
	full_insts.push_back(new Instruction(L"pop", L"*tmp2", L"", L"", L""));
	full_insts.push_back(new Instruction(L"add", L"*tmp2", L"*tmp", L"*tmp2", L""));
	full_insts.push_back(new Instruction(L"push", L"", L"*tmp", L"", L""));
	full_insts.push_back(new Instruction(L"addi", L"*tmp", L"*tmp", L"5", L""));
	full_insts.push_back(new Instruction(L"u-", L"*tmp", L"*tmp", L"", L""));
	full_insts.push_back(new Instruction(L"pop", L"*tmp", L"", L"", L""));
	
	FlowGraph::FlowGraph* fg = new FlowGraph::FlowGraph();
	fg->EnterFunction();
	BOOST_FOREACH(Instruction* i, full_insts)
	{
		fg->InsertInstruction(i);
	}
	fg->ExitFunction();
	
	fg->Optimize();
	
	std::list<Instruction*> opt_insts = std::list<Instruction*>();
	opt_insts.push_back(new Instruction(L"addi", L"*tmp", L"tmp", L"5", L""));
	opt_insts.push_back(new Instruction(L"u-", L"*tmp", L"tmp", L"", L""));
	opt_insts.push_back(new Instruction(L"add", L"*tmp2", L"*tmp", L"*tmp2", L""));
	opt_insts.push_back(new Instruction(L"push", L"", L"*tmp", L"", L""));
	opt_insts.push_back(new Instruction(L"addi", L"*tmp", L"*tmp", L"5", L""));
	opt_insts.push_back(new Instruction(L"u-", L"*tmp", L"*tmp", L"", L""));
	opt_insts.push_back(new Instruction(L"pop", L"*tmp", L"", L"", L""));
	BasicBlock::BasicBlock* opt_block = new BasicBlock::BasicBlock(opt_insts);

	std::list<BasicBlock::BasicBlock*> blocks = fg->GetBlocks();
	CPNN(blocks.front(), errMsg, assertNum);
	CPEQ(opt_block, blocks.front(), errMsg, assertNum);

	return true;
}

extern "C" __declspec(dllexport) bool Test_OptimizeConstantNoDefaultSwitchStatements(TCHAR* errMsg)
{
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg_test = new MiniC::IR::Epicness::FlowGraph::FlowGraph();
	fg->EnterFunction();
	MiniC::IR::AST::SymbolTable* st = new MiniC::IR::AST::SymbolTable();
	st->EnterScope();
	fg_test->EnterFunction();
	int assertNum = 1;

	//Constructing:
	//int b;
	//switch(3)
	//{
	//	case 0:
	//		b = 10;
	//		break;
	//	case 1:
	//		b = 100;
	//		break;
	//	case 2:
	//		b = 1000;
	//		break;
	//}

	DeclAssignNode* decl2 = new DeclAssignNode(new PrimitiveTypeNode(L"int"), L"b", NULL);
	*st = decl2->FullTypeCheck(*st);
	fg = decl2->GetFlowGraph(fg);
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"loadi", L"*tmp", L"0", L"", L""));
	fg_test->InsertInstruction(new MiniC::IR::Instruction::Instruction(L"store", L"b", L"*tmp", L"0", L""));
	CPEQ(fg, fg_test, errMsg, assertNum);
	delete decl2;

	std::list<ExprNode*> cases = std::list<ExprNode*>();
	cases.push_back(new IntNode(0));
	cases.push_back(new IntNode(1));
	cases.push_back(new IntNode(2));
	std::list<StmtNode*> stmts = std::list<StmtNode*>();
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(10))));
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(100))));
	stmts.push_back(new ExpressionStmt(new AssignNode(new VarNode(L"b"), L"=", new IntNode(1000))));
	SwitchNode* sn = new SwitchNode(new IntNode(3), cases, stmts, NULL);
	*st = sn->FullTypeCheck(*st);
	fg = sn->GetFlowGraph(fg);
	
	CPEQ(fg, fg_test, errMsg, assertNum);

	delete fg;
	return true;
}

//Integration Tests
extern "C" __declspec(dllexport) void Test_CompileCode(TCHAR* fileName, int fileLength, TCHAR* translatedAsm)
{
	std::wstring* byteCode = new std::wstring();
	Compile(fileName, true, 1, byteCode);

	wcscpy_s(translatedAsm, fileLength, byteCode->c_str());
}