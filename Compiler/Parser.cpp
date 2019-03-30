

#include <wchar.h>
#include "Parser.h"
#include "Scanner.h"


namespace MiniC {


void Parser::SynErr(int n) {
	if (errDist >= minErrDist) errors->SynErr(la->line, la->col, n);
	errDist = 0;
}

void Parser::SemErr(const wchar_t* msg) {
	if (errDist >= minErrDist) errors->Error(t->line, t->col, msg);
	errDist = 0;
}

void Parser::Get() {
	for (;;) {
		t = la;
		la = scanner->Scan();
		if (la->kind <= maxT) { ++errDist; break; }

		if (dummyToken != t) {
			dummyToken->kind = t->kind;
			dummyToken->pos = t->pos;
			dummyToken->col = t->col;
			dummyToken->line = t->line;
			dummyToken->next = NULL;
			coco_string_delete(dummyToken->val);
			dummyToken->val = coco_string_create(t->val);
			t = dummyToken;
		}
		la = t;
	}
}

void Parser::Expect(int n) {
	if (la->kind==n) Get(); else { SynErr(n); }
}

void Parser::ExpectWeak(int n, int follow) {
	if (la->kind == n) Get();
	else {
		SynErr(n);
		while (!StartOf(follow)) Get();
	}
}

bool Parser::WeakSeparator(int n, int syFol, int repFol) {
	if (la->kind == n) {Get(); return true;}
	else if (StartOf(repFol)) {return false;}
	else {
		SynErr(n);
		while (!(StartOf(syFol) || StartOf(repFol) || StartOf(0))) {
			Get();
		}
		return StartOf(syFol);
	}
}

void Parser::ParserGrammar() {
		std::list<IR::AST::TranslationUnitNode*>* units = new std::list<IR::AST::TranslationUnitNode*>();
		IR::AST::TranslationUnitNode* tmp_unit; 
		
		while (StartOf(1)) {
			TranslationUnit(tmp_unit);
			units->push_back(tmp_unit); 
		}
		this->program = new IR::AST::ProgramNode(*units);
		
}

void Parser::TranslationUnit(IR::AST::TranslationUnitNode*& result) {
		IR::AST::TypeNode* returnType = NULL;
		std::wstring* name = new std::wstring();
		int numPointer = 0;
		int* pNumPointer = &numPointer;
		std::list<IR::AST::FormalNode*>* params = new std::list<IR::AST::FormalNode*>();
		bool isVariableLength = false;
		bool* pIsVariableLength = &isVariableLength;
		
		if (la->kind == 25) {
			StructSpecifiers(returnType);
			StructTranslationUnit(returnType, result);
		} else if (StartOf(2)) {
			PrimitiveSpecifiers(returnType);
			Pointer(pNumPointer);
			Expect(1);
			name = new std::wstring(t->val); returnType->SetNumPointers(numPointer); 
			TranslationUnitPrime(returnType, name, result);
		} else if (la->kind == 71) {
			Get();
			PrimitiveSpecifiers(returnType);
			Pointer(pNumPointer);
			Expect(1);
			name = new std::wstring(t->val); returnType->SetNumPointers(numPointer); 
			Expect(56);
			ParameterList(params, pIsVariableLength);
			Expect(57);
			FuncSignature(returnType, name, params, true, pIsVariableLength, result);
		} else SynErr(82);
}

void Parser::StructSpecifiers(IR::AST::TypeNode*& result) {
		std::wstring* tmp_spec = new std::wstring();
		std::list<std::wstring*> storagespecs = std::list<std::wstring*>();
		
		StructTypeSpecifier(tmp_spec);
		result = new IR::AST::StructTypeNode(*tmp_spec); 
}

void Parser::StructTranslationUnit(IR::AST::TypeNode* type, IR::AST::TranslationUnitNode*& result) {
		IR::AST::ExprNode* arrayindex = NULL;
		std::wstring* tmp_name = new std::wstring();
		std::wstring init_name = std::wstring();
		int numPointer = 0;
		int* pNumPointer = &numPointer;
		std::list<std::wstring> names = std::list<std::wstring>();
		std::list<IR::AST::TypeNode*> types = std::list<IR::AST::TypeNode*>();
		std::wstring* name = new std::wstring();
		
		if (la->kind == 58) {
			name = new std::wstring(type->GetName()); 
			Get();
			while (StartOf(2)) {
				PrimitiveSpecifiers(type);
				Declarator(tmp_name, pNumPointer, arrayindex);
				Expect(40);
				type->SetNumPointers(numPointer);
				type->SetArrayDim(arrayindex); 
				names.push_back(*tmp_name);
				types.push_back(type);
				
			}
			Expect(59);
			if (la->kind == 1) {
				Get();
				init_name = std::wstring(t->val); 
			}
			Expect(40);
			result = new IR::AST::StructDeclNode(*name, init_name, types, names); 
		} else if (la->kind == 1) {
			Get();
			name = new std::wstring(t->val); 
			StructTranslationUnitPrime(type, name, result);
		} else SynErr(83);
}

void Parser::PrimitiveSpecifiers(IR::AST::TypeNode*& result) {
		std::wstring* tmp_spec = new std::wstring();
		std::list<std::wstring*> storagespecs = std::list<std::wstring*>();
		
		PrimitiveTypeSpecifier(tmp_spec);
		result = new IR::AST::PrimitiveTypeNode(*tmp_spec); 
}

void Parser::Pointer(int*& numPointers) {
		*numPointers = 0; 
		while (la->kind == 28) {
			Get();
			(*numPointers)++; 
		}
}

void Parser::TranslationUnitPrime(IR::AST::TypeNode* type, std::wstring* name, IR::AST::TranslationUnitNode*& result) {
		std::list<IR::AST::FormalNode*>* params = new std::list<IR::AST::FormalNode*>();
		std::list<IR::AST::StmtNode*>* body = new std::list<IR::AST::StmtNode*>();
		IR::AST::ExprNode* expr;
		bool isVariableLength = false;
		bool* pIsVariableLength = &isVariableLength;
		
		if (la->kind == 56) {
			Get();
			ParameterList(params, pIsVariableLength);
			Expect(57);
			FuncSignature(type, name, params, false, pIsVariableLength, result);
		} else if (la->kind == 40 || la->kind == 45 || la->kind == 60) {
			if (la->kind == 60) {
				Get();
				Expr(expr);
				type->SetArrayDim(expr); type->SetNumPointers(type->GetNumPointers() + 1); 
				Expect(61);
			}
			GlobalDeclAssign(type, name, result);
		} else SynErr(84);
}

void Parser::ParameterList(LISTOFFORMALS*& params, bool*& isVariableLength) {
		IR::AST::FormalNode* tmp_formal = new IR::AST::FormalNode(); 
		if (StartOf(3)) {
			Formal(tmp_formal);
			params->push_back(tmp_formal); 
			while (la->kind == 44) {
				Get();
				if (la->kind == 42) {
					Get();
					*isVariableLength = true; return; 
				} else if (StartOf(3)) {
					Formal(tmp_formal);
					params->push_back(tmp_formal); 
				} else SynErr(85);
			}
		}
}

void Parser::FuncSignature(IR::AST::TypeNode*& returnType, std::wstring*& name, LISTOFFORMALS*& params, bool isInterruptHandler, bool*& isVariableLength, IR::AST::TranslationUnitNode*& result) {
		std::list<IR::AST::StmtNode*>* body = new std::list<IR::AST::StmtNode*>();
		
		if (la->kind == 58) {
			FuncDef(body);
			result = new IR::AST::FuncNode(*name, returnType, *params, isInterruptHandler, *isVariableLength, *body); 
		} else if (la->kind == 40) {
			Get();
			result = new IR::AST::FuncDeclNode(*name, returnType, *params, *isVariableLength); 
		} else SynErr(86);
}

void Parser::Declarator(std::wstring*& name, int*& numPointers, IR::AST::ExprNode*& arrayindex) {
		Pointer(numPointers);
		DirectDeclarator(name, arrayindex);
		if (arrayindex)
		{
			(*numPointers)++;
		}
		
}

void Parser::StructTranslationUnitPrime(IR::AST::TypeNode* type, std::wstring* name, IR::AST::TranslationUnitNode*& result) {
		std::list<IR::AST::FormalNode*>* params = new std::list<IR::AST::FormalNode*>();
		std::list<IR::AST::StmtNode*>* body = new std::list<IR::AST::StmtNode*>();
		IR::AST::ExprNode* expr;
		bool isVariableLength = false;
		bool* pIsVariableLength = &isVariableLength;
		
		if (la->kind == 45) {
			Get();
			GlobalStructAssignment(type, name, result);
			Expect(40);
		} else if (la->kind == 40) {
			Get();
			result = new IR::AST::GlobalDeclAssignNode(type, *name, NULL); 
		} else SynErr(87);
}

void Parser::GlobalStructAssignment(IR::AST::TypeNode* type, std::wstring* name, IR::AST::TranslationUnitNode*& result) {
		IR::AST::ExprNode* tmp_expr;
		IR::AST::ExprNode* expr;
		std::list<IR::AST::ExprNode*> inits = std::list<IR::AST::ExprNode*>();
		
		if (la->kind == 58) {
			Get();
			Expr(tmp_expr);
			inits.push_back(tmp_expr); 
			while (la->kind == 44) {
				Get();
				Expr(tmp_expr);
				inits.push_back(tmp_expr); 
			}
			Expect(59);
			result = new IR::AST::GlobalStructInitNode(type, *name, inits); 
		} else if (StartOf(4)) {
			Expr(expr);
			result = new IR::AST::GlobalDeclAssignNode(type, *name, expr); 
		} else SynErr(88);
}

void Parser::Expr(IR::AST::ExprNode*& result) {
		IR::AST::ExprNode* lhs = NULL;
		
		TernaryExpr(lhs);
		ExprPrime(lhs, result);
}

void Parser::GlobalDeclAssign(IR::AST::TypeNode* type, std::wstring* name, IR::AST::TranslationUnitNode*& result) {
		IR::AST::ExprNode* expr;
		
		if (la->kind == 45) {
			Get();
			Expr(expr);
			Expect(40);
			result = new IR::AST::GlobalDeclAssignNode(type, *name, expr); 
		} else if (la->kind == 40) {
			Get();
			result = new IR::AST::GlobalDeclAssignNode(type, *name, NULL); 
		} else SynErr(89);
}

void Parser::FuncDef(LISTOFSTMTS* result) {
		IR::AST::StmtNode* tmp_stmt = NULL;
		
		Expect(58);
		while (StartOf(5)) {
			Stmt(tmp_stmt);
			result->push_back(tmp_stmt); 
		}
		Expect(59);
}

void Parser::Specifiers(IR::AST::TypeNode*& result) {
		bool tmp_val = false;
		bool* struct_val = &tmp_val;
		std::wstring* tmp_spec = new std::wstring();
		
		TypeSpecifier(tmp_spec, struct_val);
		if (*struct_val) { result = new IR::AST::StructTypeNode(*tmp_spec);
		} else {result = new IR::AST::PrimitiveTypeNode(*tmp_spec);} 
}

void Parser::TypeSpecifier(std::wstring*& result, bool*& struct_val) {
		if (StartOf(2)) {
			PrimitiveTypeSpecifier(result);
			*struct_val = false; 
		} else if (la->kind == 25) {
			StructTypeSpecifier(result);
			*struct_val = true; 
		} else SynErr(90);
}

void Parser::PrimitiveTypeSpecifier(std::wstring*& result) {
		switch (la->kind) {
		case 18: {
			Get();
			result = new std::wstring(L"void"); 
			break;
		}
		case 19: {
			Get();
			result = new std::wstring(L"char"); 
			break;
		}
		case 20: {
			Get();
			result = new std::wstring(L"short"); 
			break;
		}
		case 21: {
			Get();
			result = new std::wstring(L"int"); 
			break;
		}
		case 22: {
			Get();
			result = new std::wstring(L"long"); 
			break;
		}
		case 23: {
			Get();
			result = new std::wstring(L"boolean"); 
			break;
		}
		default: SynErr(91); break;
		}
}

void Parser::StructTypeSpecifier(std::wstring*& result) {
		Expect(25);
		Expect(1);
		result = new std::wstring(t->val);
}

void Parser::InitDeclarator(std::wstring*& name, int*& numPointers, IR::AST::ExprNode*& arrayindex, IR::AST::ExprNode*& result) {
		Declarator(name, numPointers, arrayindex);
		InitDeclaratorPrime(result);
}

void Parser::InitDeclaratorPrime(IR::AST::ExprNode*& result) {
		if (la->kind == 45) {
			Get();
			Expr(result);
		} else if (la->kind == 40) {
			result = NULL; 
		} else SynErr(92);
}

void Parser::DirectDeclarator(std::wstring*& name, IR::AST::ExprNode*& arrayindex) {
		Expect(1);
		*name = std::wstring(t->val); 
		DirectDeclaratorPrime(arrayindex);
}

void Parser::DirectDeclaratorPrime(IR::AST::ExprNode*& arrayindex) {
		if (la->kind == 60) {
			Get();
			TernaryExpr(arrayindex);
			Expect(61);
		} else if (StartOf(6)) {
			arrayindex = NULL; 
		} else SynErr(93);
}

void Parser::TernaryExpr(IR::AST::ExprNode*& result) {
		IR::AST::ExprNode* cond = NULL;
		
		AndOrExpr(cond);
		TernaryExprPrime(cond, result);
}

void Parser::Formal(IR::AST::FormalNode*& result) {
		IR::AST::TypeNode* type;
		IR::AST::ExprNode* arrayindex = NULL;
		std::wstring* name = new std::wstring();
		int numPointers = 0;
		int* pnumPointers = &numPointers;
		
		Specifiers(type);
		Declarator(name, pnumPointers, arrayindex);
		type->SetNumPointers(numPointers);
		type->SetArrayDim(arrayindex);
		result = new IR::AST::FormalNode(*name, type); 
		
}

void Parser::Stmt(IR::AST::StmtNode*& result) {
		IR::AST::StmtNode* tmp_stmt = NULL; 
		std::list<IR::AST::StmtNode*>* body = new std::list<IR::AST::StmtNode*>();
		std::list<IR::AST::StmtNode*>* body2 = new std::list<IR::AST::StmtNode*>();
		IR::AST::ExprNode* tmp_expr = NULL;
		IR::AST::ExprNode* tmp_expr2 = NULL;
		IR::AST::StmtNode* tmp_stmt2 = NULL;
		
		switch (la->kind) {
		case 1: case 2: case 3: case 4: case 5: case 6: case 8: case 15: case 16: case 17: case 24: case 26: case 27: case 28: case 39: case 56: case 62: case 69: case 70: case 78: case 79: case 80: {
			Expr(tmp_expr);
			Expect(40);
			result = new IR::AST::ExpressionStmt(tmp_expr); 
			break;
		}
		case 18: case 19: case 20: case 21: case 22: case 23: case 25: {
			VarDecl(result);
			break;
		}
		case 58: {
			Get();
			while (StartOf(5)) {
				Stmt(tmp_stmt);
				body->push_back(tmp_stmt); 
			}
			Expect(59);
			result = new IR::AST::BlockNode(*body); 
			break;
		}
		case 10: {
			Get();
			Expect(56);
			Expr(tmp_expr);
			Expect(57);
			Stmt(tmp_stmt);
			result = new IR::AST::IfNode(tmp_expr, tmp_stmt); 
			if (la->kind == 11) {
				Get();
				Stmt(tmp_stmt2);
				result = new IR::AST::IfNode(tmp_expr, tmp_stmt, tmp_stmt2); 
			}
			break;
		}
		case 12: {
			Get();
			Expect(56);
			Expr(tmp_expr);
			Expect(57);
			Stmt(tmp_stmt);
			result = new IR::AST::WhileNode(tmp_expr,tmp_stmt); 
			break;
		}
		case 72: {
			Get();
			Expect(56);
			Expr(tmp_expr);
			body->push_back(new IR::AST::ExpressionStmt(tmp_expr)); 
			Expect(40);
			Expr(tmp_expr);
			Expect(40);
			Expr(tmp_expr2);
			Expect(57);
			Stmt(tmp_stmt);
			body2->push_back(tmp_stmt); body2->push_back(new IR::AST::ExpressionStmt(tmp_expr2)); body->push_back(new IR::AST::WhileNode(tmp_expr, new IR::AST::BlockNode(*body2))); result = new IR::AST::BlockNode(*body); 
			break;
		}
		case 14: {
			Get();
			Expr(tmp_expr);
			Expect(40);
			result = new IR::AST::ReturnNode(tmp_expr); 
			break;
		}
		case 73: {
			Get();
			Expect(40);
			break;
		}
		case 74: {
			Get();
			Expect(40);
			break;
		}
		case 13: {
			SwitchStmt(result);
			break;
		}
		default: SynErr(94); break;
		}
}

void Parser::VarDecl(IR::AST::StmtNode*& result) {
		IR::AST::TypeNode* type = NULL; 
		IR::AST::ExprNode* tmp_expr = NULL;
		IR::AST::ExprNode* arrayindex = NULL;
		std::wstring* name = new std::wstring();
		std::wstring* typeStr = new std::wstring();
		int numPointers = 0;
		int* pnumPointers = &numPointers;
		
		if (StartOf(2)) {
			PrimitiveTypeSpecifier(typeStr);
			InitDeclarator(name, pnumPointers, arrayindex, tmp_expr);
			type = new IR::AST::PrimitiveTypeNode(*typeStr, numPointers, arrayindex);
			result = new IR::AST::DeclAssignNode(type, *name, tmp_expr); 
			
			Expect(40);
		} else if (la->kind == 25) {
			StructTypeSpecifier(typeStr);
			Declarator(name, pnumPointers, arrayindex);
			VarDeclPrime(typeStr, name, numPointers, arrayindex, result);
		} else SynErr(95);
}

void Parser::SwitchStmt(IR::AST::StmtNode*& result) {
		IR::AST::ExprNode* testcase = NULL;
		std::list<IR::AST::ExprNode*> cases = std::list<IR::AST::ExprNode*>();
		std::list<IR::AST::StmtNode*> bodies = std::list<IR::AST::StmtNode*>();
		IR::AST::ExprNode* tmp_expr = NULL;
		IR::AST::StmtNode* tmp_stmt = NULL;
		IR::AST::StmtNode* defaultstmt = NULL;
		std::list<IR::AST::StmtNode*> blockbody = std::list<IR::AST::StmtNode*>();
		
		Expect(13);
		Expect(56);
		Expr(testcase);
		Expect(57);
		Expect(58);
		while (la->kind == 75) {
			Get();
			Expr(tmp_expr);
			Expect(41);
			while (StartOf(5)) {
				Stmt(tmp_stmt);
				blockbody.push_back(tmp_stmt); 
			}
			Expect(74);
			Expect(40);
			cases.push_back(tmp_expr); bodies.push_back(new IR::AST::BlockNode(blockbody)); blockbody.clear(); 
		}
		if (la->kind == 76) {
			Get();
			Expect(41);
			while (StartOf(5)) {
				Stmt(defaultstmt);
				blockbody.push_back(tmp_stmt); 
			}
			Expect(74);
			Expect(40);
		}
		Expect(59);
		result = new IR::AST::SwitchNode(testcase, cases, bodies, defaultstmt); 
}

void Parser::VarDeclPrime(std::wstring* typeStr, std::wstring* name, int numPointers, IR::AST::ExprNode*& arrayindex, IR::AST::StmtNode*& result) {
		IR::AST::TypeNode* type = new IR::AST::StructTypeNode(*typeStr, numPointers, arrayindex);
		
		if (la->kind == 45) {
			Get();
			VarAssignment(type, name, result);
			Expect(40);
		} else if (la->kind == 40) {
			Get();
			result = new IR::AST::StructInitNode(type, *name, std::list<IR::AST::ExprNode*>()); 
		} else SynErr(96);
}

void Parser::VarAssignment(IR::AST::TypeNode* type, std::wstring* name, IR::AST::StmtNode*& result) {
		IR::AST::ExprNode* tmp_expr;
		IR::AST::ExprNode* expr;
		std::list<IR::AST::ExprNode*> inits = std::list<IR::AST::ExprNode*>();
		
		if (la->kind == 58) {
			Get();
			Expr(tmp_expr);
			inits.push_back(tmp_expr); 
			while (la->kind == 44) {
				Get();
				Expr(tmp_expr);
				inits.push_back(tmp_expr); 
			}
			Expect(59);
			result = new IR::AST::StructInitNode(type, *name, inits); 
		} else if (StartOf(4)) {
			Expr(expr);
			result = new IR::AST::DeclAssignNode(type, *name, expr); 
		} else SynErr(97);
}

void Parser::ExprPrime(IR::AST::ExprNode* lhs, IR::AST::ExprNode*& result) {
		std::wstring* op = new std::wstring();
		IR::AST::ExprNode* rhs = NULL;
		
		if (StartOf(7)) {
			AssignmentOperator(op);
			Expr(rhs);
			result = new IR::AST::AssignNode(lhs, *op, rhs); 
		} else if (StartOf(8)) {
			result = lhs; 
		} else SynErr(98);
}

void Parser::AssignmentOperator(std::wstring*& result) {
		switch (la->kind) {
		case 45: {
			Get();
			result = new std::wstring(L"="); 
			break;
		}
		case 46: {
			Get();
			result = new std::wstring(L"+="); 
			break;
		}
		case 47: {
			Get();
			result = new std::wstring(L"-="); 
			break;
		}
		case 51: {
			Get();
			result = new std::wstring(L"<<="); 
			break;
		}
		case 52: {
			Get();
			result = new std::wstring(L">>="); 
			break;
		}
		case 53: {
			Get();
			result = new std::wstring(L"&="); 
			break;
		}
		case 54: {
			Get();
			result = new std::wstring(L"^="); 
			break;
		}
		case 55: {
			Get();
			result = new std::wstring(L"|="); 
			break;
		}
		default: SynErr(99); break;
		}
}

void Parser::AndOrExpr(IR::AST::ExprNode*& result) {
		IR::AST::ExprNode* tmp_expr = NULL;
		
		BinaryAndOrExpr(tmp_expr);
		AndOrExprPrime(tmp_expr, result);
}

void Parser::TernaryExprPrime(IR::AST::ExprNode* cond, IR::AST::ExprNode*& result) {
		IR::AST::ExprNode* thenexpr = NULL;
		IR::AST::ExprNode* elseexpr = NULL;
		
		if (la->kind == 77) {
			Get();
			AndOrExpr(thenexpr);
			Expect(41);
			TernaryExpr(elseexpr);
			result = new IR::AST::TernaryNode(cond, thenexpr, elseexpr); 
		} else if (StartOf(9)) {
			result = cond; 
		} else SynErr(100);
}

void Parser::BinaryAndOrExpr(IR::AST::ExprNode*& result) {
		IR::AST::ExprNode* tmp_expr = NULL;
		
		EqualExpr(tmp_expr);
		BinaryAndOrExprPrime(tmp_expr, result);
}

void Parser::AndOrExprPrime(IR::AST::ExprNode* lhs, IR::AST::ExprNode*& result) {
		std::wstring op = std::wstring(); 
		IR::AST::ExprNode* rhs = NULL;
		
		if (la->kind == 37 || la->kind == 38) {
			if (la->kind == 37) {
				Get();
				op = std::wstring(L"&&"); 
			} else {
				Get();
				op = std::wstring(L"||"); 
			}
			AndOrExpr(rhs);
			result = new IR::AST::BinaryNode(lhs, op, rhs); 
		} else if (StartOf(10)) {
			result = lhs; 
		} else SynErr(101);
}

void Parser::EqualExpr(IR::AST::ExprNode*& result) {
		IR::AST::ExprNode* tmp_expr = NULL;
		
		CompareExpr(tmp_expr);
		EqualExprPrime(tmp_expr, result);
}

void Parser::BinaryAndOrExprPrime(IR::AST::ExprNode* lhs, IR::AST::ExprNode*& result) {
		std::wstring op = std::wstring(); 
		IR::AST::ExprNode* rhs = NULL;
		
		if (la->kind == 62 || la->kind == 63 || la->kind == 64) {
			if (la->kind == 62) {
				Get();
				op = std::wstring(L"&"); 
			} else if (la->kind == 63) {
				Get();
				op = std::wstring(L"|"); 
			} else {
				Get();
				op = std::wstring(L"^"); 
			}
			BinaryAndOrExpr(rhs);
			result = new IR::AST::BinaryNode(lhs, op, rhs); 
		} else if (StartOf(11)) {
			result = lhs; 
		} else SynErr(102);
}

void Parser::CompareExpr(IR::AST::ExprNode*& result) {
		IR::AST::ExprNode* tmp_expr = NULL;
		
		ShiftExpr(tmp_expr);
		CompareExprPrime(tmp_expr, result);
}

void Parser::EqualExprPrime(IR::AST::ExprNode* lhs, IR::AST::ExprNode*& result) {
		std::wstring op = std::wstring(); 
		IR::AST::ExprNode* rhs = NULL;
		
		if (la->kind == 35 || la->kind == 36) {
			if (la->kind == 35) {
				Get();
				op = std::wstring(L"=="); 
			} else {
				Get();
				op = std::wstring(L"!="); 
			}
			EqualExpr(rhs);
			result = new IR::AST::BinaryNode(lhs, op, rhs); 
		} else if (StartOf(12)) {
			result = lhs; 
		} else SynErr(103);
}

void Parser::ShiftExpr(IR::AST::ExprNode*& result) {
		IR::AST::ExprNode* tmp_expr = NULL;
		
		AddSubExpr(tmp_expr);
		ShiftExprPrime(tmp_expr, result);
}

void Parser::CompareExprPrime(IR::AST::ExprNode* lhs, IR::AST::ExprNode*& result) {
		std::wstring op = std::wstring(); 
		IR::AST::ExprNode* rhs = NULL;
		
		if (StartOf(13)) {
			if (la->kind == 31) {
				Get();
				op = std::wstring(L"<"); 
			} else if (la->kind == 32) {
				Get();
				op = std::wstring(L"<="); 
			} else if (la->kind == 34) {
				Get();
				op = std::wstring(L">"); 
			} else {
				Get();
				op = std::wstring(L">="); 
			}
			CompareExpr(rhs);
			result = new IR::AST::BinaryNode(lhs, op, rhs); 
		} else if (StartOf(14)) {
			result = lhs; 
		} else SynErr(104);
}

void Parser::AddSubExpr(IR::AST::ExprNode*& result) {
		IR::AST::ExprNode* tmp_expr = NULL;
		
		CastExpr(tmp_expr);
		AddSubExprPrime(tmp_expr, result);
}

void Parser::ShiftExprPrime(IR::AST::ExprNode* lhs, IR::AST::ExprNode*& result) {
		std::wstring op = std::wstring(); 
		IR::AST::ExprNode* rhs = NULL;
		
		if (la->kind == 65 || la->kind == 66) {
			if (la->kind == 66) {
				Get();
				op = std::wstring(L">>"); 
			} else {
				Get();
				op = std::wstring(L"<<"); 
			}
			ShiftExpr(rhs);
			result = new IR::AST::BinaryNode(lhs, op, rhs); 
		} else if (StartOf(15)) {
			result = lhs; 
		} else SynErr(105);
}

void Parser::CastExpr(IR::AST::ExprNode*& result) {
		IR::AST::ExprNode* tmp_expr = NULL;
		std::wstring* type = new std::wstring();
		
		UnaryExpr(result);
}

void Parser::AddSubExprPrime(IR::AST::ExprNode* lhs, IR::AST::ExprNode*& result) {
		std::wstring op = std::wstring(); 
		IR::AST::ExprNode* rhs = NULL;
		
		if (la->kind == 26 || la->kind == 27) {
			if (la->kind == 26) {
				Get();
				op = std::wstring(L"+"); 
			} else {
				Get();
				op = std::wstring(L"-"); 
			}
			AddSubExpr(rhs);
			result = new IR::AST::BinaryNode(lhs, op, rhs); 
		} else if (StartOf(16)) {
			result = lhs; 
		} else SynErr(106);
}

void Parser::UnaryExpr(IR::AST::ExprNode*& result) {
		IR::AST::PrimitiveTypeNode* type = new IR::AST::PrimitiveTypeNode();
		IR::AST::ExprNode* tmp_expr = NULL;
		std::wstring* op = new std::wstring();
		bool tmp_val = false;
		bool* struct_val = &tmp_val;
		
		if (StartOf(17)) {
			PostfixExpr(result);
		} else if (la->kind == 69) {
			Get();
			UnaryExpr(tmp_expr);
		} else if (la->kind == 70) {
			Get();
			UnaryExpr(tmp_expr);
		} else if (StartOf(18)) {
			UnaryOperator(op);
			UnaryExpr(tmp_expr);
			result = new IR::AST::UnaryNode(*op, tmp_expr); 
		} else if (la->kind == 24) {
			Get();
			Expect(56);
			TypeSpecifier(op, struct_val);
			Expect(57);
			result = new IR::AST::SizeOfNode(*op); 
		} else SynErr(107);
}

void Parser::PostfixExpr(IR::AST::ExprNode*& result) {
		if (la->kind == 17) {
			Get();
			AsmExpr(result);
		} else if (StartOf(19)) {
			PrimaryExpr(result);
			while (StartOf(20)) {
				PostfixExprPrime(result);
			}
		} else SynErr(108);
}

void Parser::UnaryOperator(std::wstring*& op) {
		switch (la->kind) {
		case 27: {
			Get();
			op = new std::wstring(L"-"); 
			break;
		}
		case 62: {
			Get();
			op = new std::wstring(L"&"); 
			break;
		}
		case 28: {
			Get();
			op = new std::wstring(L"*"); 
			break;
		}
		case 26: {
			Get();
			op = new std::wstring(L"+"); 
			break;
		}
		case 78: {
			Get();
			op = new std::wstring(L"+"); 
			break;
		}
		case 39: {
			Get();
			op = new std::wstring(L"!"); 
			break;
		}
		default: SynErr(109); break;
		}
}

void Parser::AsmExpr(IR::AST::ExprNode*& result) {
		std::wstring code = std::wstring(); 
		std::list<std::wstring>* varkeys = new std::list<std::wstring>();
		std::list<std::wstring>* varvals = new std::list<std::wstring>();
		std::list<std::wstring>* outkeys = new std::list<std::wstring>();
		std::list<std::wstring>* outvals = new std::list<std::wstring>(); 
		std::wstring inputs = std::wstring();
		std::wstring outputs = std::wstring();
		
		Expect(56);
		Expect(8);
		code = t->val; 
		Expect(44);
		Expect(8);
		inputs = t->val; 
		Expect(44);
		Expect(8);
		outputs = t->val; 
		Expect(57);
		result = new IR::AST::AssemblyNode(code, inputs, outputs); 
		
}

void Parser::PrimaryExpr(IR::AST::ExprNode*& result) {
		if (la->kind == 1) {
			Get();
			result = new IR::AST::VarNode(t->val); 
		} else if (StartOf(21)) {
			Constant(result);
		} else if (la->kind == 8) {
			Get();
			result = new IR::AST::StringNode(new std::wstring(t->val)); 
		} else if (la->kind == 56) {
			Get();
			Expr(result);
			Expect(57);
		} else SynErr(110);
}

void Parser::PostfixExprPrime(IR::AST::ExprNode*& result) {
		std::list<IR::AST::ExprNode*>* args = new std::list<IR::AST::ExprNode*>();
		IR::AST::ExprNode* tmp_expr = NULL;
		
		switch (la->kind) {
		case 60: {
			Get();
			Expr(tmp_expr);
			Expect(61);
			result = new IR::AST::ArrayNode(result, tmp_expr); 
			break;
		}
		case 56: {
			Get();
			ArgList(args);
			Expect(57);
			result = new IR::AST::FuncCallNode(result, *args); 
			break;
		}
		case 43: {
			Get();
			Expect(1);
			result = new IR::AST::StructReferenceNode(result, false, t->val); 
			break;
		}
		case 68: {
			Get();
			Expect(1);
			result = new IR::AST::StructReferenceNode(result, true, t->val); 
			break;
		}
		case 69: {
			Get();
			break;
		}
		case 70: {
			Get();
			break;
		}
		default: SynErr(111); break;
		}
}

void Parser::ArgList(LISTOFEXPR* result) {
		IR::AST::ExprNode* tmp_expr = NULL;
		
		if (StartOf(4)) {
			Expr(tmp_expr);
			result->push_back(tmp_expr); 
			while (la->kind == 44) {
				Get();
				Expr(tmp_expr);
				result->push_back(tmp_expr); 
			}
		}
}

void Parser::Constant(IR::AST::ExprNode*& result) {
		switch (la->kind) {
		case 3: {
			Get();
			result = new IR::AST::IntNode(t->val); 
			break;
		}
		case 5: {
			Get();
			int intval; swscanf(t->val, L"%x", &intval); result = new IR::AST::IntNode(intval); 
			break;
		}
		case 6: {
			Get();
			int intval; swscanf(t->val, L"%X", &intval); result = new IR::AST::IntNode(intval); 
			break;
		}
		case 4: {
			Get();
			int intval; swscanf(t->val, L"%o", &intval); result = new IR::AST::IntNode(intval); 
			break;
		}
		case 2: {
			Get();
			result = new IR::AST::CharNode(new std::wstring(t->val)); 
			break;
		}
		case 79: {
			Get();
			result = new IR::AST::IntNode(L"0"); 
			break;
		}
		case 80: {
			Get();
			result = new IR::AST::IntNode(L"0"); 
			break;
		}
		case 15: {
			Get();
			result = new IR::AST::KeywordNode(t->val); 
			break;
		}
		case 16: {
			Get();
			result = new IR::AST::KeywordNode(t->val); 
			break;
		}
		default: SynErr(112); break;
		}
}



void Parser::Parse() {
	t = NULL;
	la = dummyToken = new Token();
	la->val = coco_string_create(L"Dummy Token");
	Get();
	ParserGrammar();
	Expect(0);
}

Parser::Parser(Scanner *scanner) {
	maxT = 81;

	dummyToken = NULL;
	t = la = NULL;
	minErrDist = 2;
	errDist = minErrDist;
	this->scanner = scanner;
	errors = new Errors();
}

bool Parser::StartOf(int s) {
	const bool T = true;
	const bool x = false;

	static bool set[22][83] = {
		{T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,T,T, T,T,T,T, x,T,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, x,x,x,x, x,x,x,x, x,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,T,T, T,T,T,T, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,T,T, T,T,T,T, x,T,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,T,T,T, T,T,T,x, T,x,x,x, x,x,x,T, T,T,x,x, x,x,x,x, T,x,T,T, T,x,x,x, x,x,x,x, x,x,x,T, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, T,x,x,x, x,x,T,x, x,x,x,x, x,T,T,x, x,x,x,x, x,x,T,T, T,x,x},
		{x,T,T,T, T,T,T,x, T,x,T,x, T,T,T,T, T,T,T,T, T,T,T,T, T,T,T,T, T,x,x,x, x,x,x,x, x,x,x,T, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, T,x,T,x, x,x,T,x, x,x,x,x, x,T,T,x, T,T,T,x, x,x,T,T, T,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, T,x,x,x, T,T,x,x, x,x,x,x, x,x,x,x, x,T,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,T,T,T, x,x,x,T, T,T,T,T, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, T,T,x,x, T,x,x,x, x,x,x,x, x,x,x,x, x,T,x,T, x,T,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, T,T,x,x, T,T,T,T, x,x,x,T, T,T,T,T, x,T,x,T, x,T,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, T,T,x,x, T,T,T,T, x,x,x,T, T,T,T,T, x,T,x,T, x,T,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,T,x,x, x,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,T,T,x, T,T,x,x, T,T,T,T, x,x,x,T, T,T,T,T, x,T,x,T, x,T,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,T,x,x, x,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,T,T,x, T,T,x,x, T,T,T,T, x,x,x,T, T,T,T,T, x,T,x,T, x,T,T,T, T,x,x,x, x,x,x,x, x,x,x,x, x,T,x,x, x,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, T,T,T,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, T,T,T,x, T,T,x,x, T,T,T,T, x,x,x,T, T,T,T,T, x,T,x,T, x,T,T,T, T,x,x,x, x,x,x,x, x,x,x,x, x,T,x,x, x,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, T,T,T,T, T,T,T,x, T,T,x,x, T,T,T,T, x,x,x,T, T,T,T,T, x,T,x,T, x,T,T,T, T,x,x,x, x,x,x,x, x,x,x,x, x,T,x,x, x,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, T,T,T,T, T,T,T,x, T,T,x,x, T,T,T,T, x,x,x,T, T,T,T,T, x,T,x,T, x,T,T,T, T,T,T,x, x,x,x,x, x,x,x,x, x,T,x,x, x,x,x},
		{x,T,T,T, T,T,T,x, T,x,x,x, x,x,x,T, T,T,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, T,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,T,T, T,x,x,x, x,x,x,x, x,x,x,T, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,T,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,T,x, x,x,x},
		{x,T,T,T, T,T,T,x, T,x,x,x, x,x,x,T, T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, T,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, x,x,x,x, x,x,x,x, x,x,x,x, T,x,x,x, T,x,x,x, x,x,x,x, T,T,T,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,x,T,T, T,T,T,x, x,x,x,x, x,x,x,T, T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, T,x,x}
	};



	return set[s][la->kind];
}

Parser::~Parser() {
	delete errors;
	delete dummyToken;
}

Errors::Errors() {
	count = 0;
}

void Errors::SynErr(int line, int col, int n) {
	wchar_t* s;
	switch (n) {
			case 0: s = coco_string_create(L"EOF expected"); break;
			case 1: s = coco_string_create(L"id expected"); break;
			case 2: s = coco_string_create(L"char expected"); break;
			case 3: s = coco_string_create(L"integer expected"); break;
			case 4: s = coco_string_create(L"octalinteger expected"); break;
			case 5: s = coco_string_create(L"lowerhexinteger expected"); break;
			case 6: s = coco_string_create(L"upperhexinteger expected"); break;
			case 7: s = coco_string_create(L"float expected"); break;
			case 8: s = coco_string_create(L"string expected"); break;
			case 9: s = coco_string_create(L"reg expected"); break;
			case 10: s = coco_string_create(L"\"if\" expected"); break;
			case 11: s = coco_string_create(L"\"else\" expected"); break;
			case 12: s = coco_string_create(L"\"while\" expected"); break;
			case 13: s = coco_string_create(L"\"switch\" expected"); break;
			case 14: s = coco_string_create(L"\"return\" expected"); break;
			case 15: s = coco_string_create(L"\"true\" expected"); break;
			case 16: s = coco_string_create(L"\"false\" expected"); break;
			case 17: s = coco_string_create(L"\"asm\" expected"); break;
			case 18: s = coco_string_create(L"\"void\" expected"); break;
			case 19: s = coco_string_create(L"\"char\" expected"); break;
			case 20: s = coco_string_create(L"\"short\" expected"); break;
			case 21: s = coco_string_create(L"\"int\" expected"); break;
			case 22: s = coco_string_create(L"\"long\" expected"); break;
			case 23: s = coco_string_create(L"\"bool\" expected"); break;
			case 24: s = coco_string_create(L"\"sizeof\" expected"); break;
			case 25: s = coco_string_create(L"\"struct\" expected"); break;
			case 26: s = coco_string_create(L"\"+\" expected"); break;
			case 27: s = coco_string_create(L"\"-\" expected"); break;
			case 28: s = coco_string_create(L"\"*\" expected"); break;
			case 29: s = coco_string_create(L"\"/\" expected"); break;
			case 30: s = coco_string_create(L"\"%\" expected"); break;
			case 31: s = coco_string_create(L"\"<\" expected"); break;
			case 32: s = coco_string_create(L"\"<=\" expected"); break;
			case 33: s = coco_string_create(L"\">=\" expected"); break;
			case 34: s = coco_string_create(L"\">\" expected"); break;
			case 35: s = coco_string_create(L"\"==\" expected"); break;
			case 36: s = coco_string_create(L"\"!=\" expected"); break;
			case 37: s = coco_string_create(L"\"&&\" expected"); break;
			case 38: s = coco_string_create(L"\"||\" expected"); break;
			case 39: s = coco_string_create(L"\"!\" expected"); break;
			case 40: s = coco_string_create(L"\";\" expected"); break;
			case 41: s = coco_string_create(L"\":\" expected"); break;
			case 42: s = coco_string_create(L"\"...\" expected"); break;
			case 43: s = coco_string_create(L"\".\" expected"); break;
			case 44: s = coco_string_create(L"\",\" expected"); break;
			case 45: s = coco_string_create(L"\"=\" expected"); break;
			case 46: s = coco_string_create(L"\"+=\" expected"); break;
			case 47: s = coco_string_create(L"\"-=\" expected"); break;
			case 48: s = coco_string_create(L"\"*=\" expected"); break;
			case 49: s = coco_string_create(L"\"/=\" expected"); break;
			case 50: s = coco_string_create(L"\"%=\" expected"); break;
			case 51: s = coco_string_create(L"\"<<=\" expected"); break;
			case 52: s = coco_string_create(L"\">>=\" expected"); break;
			case 53: s = coco_string_create(L"\"&=\" expected"); break;
			case 54: s = coco_string_create(L"\"^=\" expected"); break;
			case 55: s = coco_string_create(L"\"|=\" expected"); break;
			case 56: s = coco_string_create(L"\"(\" expected"); break;
			case 57: s = coco_string_create(L"\")\" expected"); break;
			case 58: s = coco_string_create(L"\"{\" expected"); break;
			case 59: s = coco_string_create(L"\"}\" expected"); break;
			case 60: s = coco_string_create(L"\"[\" expected"); break;
			case 61: s = coco_string_create(L"\"]\" expected"); break;
			case 62: s = coco_string_create(L"\"&\" expected"); break;
			case 63: s = coco_string_create(L"\"|\" expected"); break;
			case 64: s = coco_string_create(L"\"^\" expected"); break;
			case 65: s = coco_string_create(L"\"<<\" expected"); break;
			case 66: s = coco_string_create(L"\">>\" expected"); break;
			case 67: s = coco_string_create(L"\"$\" expected"); break;
			case 68: s = coco_string_create(L"\"->\" expected"); break;
			case 69: s = coco_string_create(L"\"++\" expected"); break;
			case 70: s = coco_string_create(L"\"--\" expected"); break;
			case 71: s = coco_string_create(L"\"interrupt\" expected"); break;
			case 72: s = coco_string_create(L"\"for\" expected"); break;
			case 73: s = coco_string_create(L"\"continue\" expected"); break;
			case 74: s = coco_string_create(L"\"break\" expected"); break;
			case 75: s = coco_string_create(L"\"case\" expected"); break;
			case 76: s = coco_string_create(L"\"default\" expected"); break;
			case 77: s = coco_string_create(L"\"?\" expected"); break;
			case 78: s = coco_string_create(L"\"~\" expected"); break;
			case 79: s = coco_string_create(L"\"null\" expected"); break;
			case 80: s = coco_string_create(L"\"NULL\" expected"); break;
			case 81: s = coco_string_create(L"??? expected"); break;
			case 82: s = coco_string_create(L"invalid TranslationUnit"); break;
			case 83: s = coco_string_create(L"invalid StructTranslationUnit"); break;
			case 84: s = coco_string_create(L"invalid TranslationUnitPrime"); break;
			case 85: s = coco_string_create(L"invalid ParameterList"); break;
			case 86: s = coco_string_create(L"invalid FuncSignature"); break;
			case 87: s = coco_string_create(L"invalid StructTranslationUnitPrime"); break;
			case 88: s = coco_string_create(L"invalid GlobalStructAssignment"); break;
			case 89: s = coco_string_create(L"invalid GlobalDeclAssign"); break;
			case 90: s = coco_string_create(L"invalid TypeSpecifier"); break;
			case 91: s = coco_string_create(L"invalid PrimitiveTypeSpecifier"); break;
			case 92: s = coco_string_create(L"invalid InitDeclaratorPrime"); break;
			case 93: s = coco_string_create(L"invalid DirectDeclaratorPrime"); break;
			case 94: s = coco_string_create(L"invalid Stmt"); break;
			case 95: s = coco_string_create(L"invalid VarDecl"); break;
			case 96: s = coco_string_create(L"invalid VarDeclPrime"); break;
			case 97: s = coco_string_create(L"invalid VarAssignment"); break;
			case 98: s = coco_string_create(L"invalid ExprPrime"); break;
			case 99: s = coco_string_create(L"invalid AssignmentOperator"); break;
			case 100: s = coco_string_create(L"invalid TernaryExprPrime"); break;
			case 101: s = coco_string_create(L"invalid AndOrExprPrime"); break;
			case 102: s = coco_string_create(L"invalid BinaryAndOrExprPrime"); break;
			case 103: s = coco_string_create(L"invalid EqualExprPrime"); break;
			case 104: s = coco_string_create(L"invalid CompareExprPrime"); break;
			case 105: s = coco_string_create(L"invalid ShiftExprPrime"); break;
			case 106: s = coco_string_create(L"invalid AddSubExprPrime"); break;
			case 107: s = coco_string_create(L"invalid UnaryExpr"); break;
			case 108: s = coco_string_create(L"invalid PostfixExpr"); break;
			case 109: s = coco_string_create(L"invalid UnaryOperator"); break;
			case 110: s = coco_string_create(L"invalid PrimaryExpr"); break;
			case 111: s = coco_string_create(L"invalid PostfixExprPrime"); break;
			case 112: s = coco_string_create(L"invalid Constant"); break;

		default:
		{
			wchar_t format[20];
			coco_swprintf(format, 20, L"error %d", n);
			s = coco_string_create(format);
		}
		break;
	}
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
	coco_string_delete(s);
	count++;
}

void Errors::Error(int line, int col, const wchar_t *s) {
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
	count++;
}

void Errors::Warning(int line, int col, const wchar_t *s) {
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
}

void Errors::Warning(const wchar_t *s) {
	wprintf(L"%ls\n", s);
}

void Errors::Exception(const wchar_t* s) {
	wprintf(L"%ls", s); 
	exit(1);
}

} // namespace

