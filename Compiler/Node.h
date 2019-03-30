#ifndef NODE_H_
#define NODE_H_

#include "stdafx.h"
#include "SymbolTable.h"
#include "ErrorHandler.h"
#include "Instruction.h"
#include "FlowGraph.h"

namespace MiniC {
	namespace IR {
		namespace AST {

			////////////////////////////////////
			//	      Interfaces              //
			////////////////////////////////////

			/*
			*		Node Class: Provides an abstract interface for all AST nodes
			*/

			class Node {
			protected:
				Node();
				Node(Node&);
			public:
				~Node();

				virtual std::wstring To_String()=0;
				virtual bool Equals(Node* n)=0;
			};


			/*
			*		StmtNode Class: Provides an abstract interface for all AST statement nodes
			*/

			class StmtNode : public Node {
			protected:
				StmtNode();
				StmtNode(StmtNode&); 
			public:
				virtual MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg) = 0;
				virtual SymbolTable FullTypeCheck(SymbolTable env)= 0;
				virtual std::list<std::wstring> GetFunctionUses() = 0;
				virtual bool IsEmpty() = 0;
				virtual void Optimize(SymbolTable env)=0;
				~StmtNode();
			};

			/*
			*		TypeNode Class: abstract class representing a type
			*		Contains:	name - string
			*/

			class TypeNode : public Node {
			protected:
				TypeNode(TypeNode&);
				TypeNode();
				std::wstring name;
				int numPointers;
				Node* arrayDim;
			public:
				~TypeNode();
				virtual std::wstring GetName()=0;
				virtual int GetNumPointers()=0;
				virtual Node* GetArrayDim()=0;
				virtual void SetNumPointers(int numPointers)=0;
				virtual void SetArrayDim(Node* arrayDim)=0;
				virtual std::wstring To_String()=0;
				virtual bool Equals(Node* n)=0;
				virtual int Compare(TypeNode* check)=0;
				virtual bool CheckArrayDim(SymbolTable env)=0;
				virtual void VerifyValidType(SymbolTable env)=0;
				virtual int GetTypeSize(SymbolTable env)=0;
				virtual Node* GetDefaultValue(SymbolTable env)=0;
				static TypeNode* GetTypeNode(std::wstring str, SymbolTable env);
			};

			/*
			*		PrimitiveTypeNode Class: represents a primitive type
			*		Contains:	name - string
			*/

			class PrimitiveTypeNode : public TypeNode {
			protected:
				PrimitiveTypeNode(PrimitiveTypeNode&);
				std::wstring name;
				int numPointers;
				Node* arrayDim;
			public:
				PrimitiveTypeNode() {}
				PrimitiveTypeNode(std::wstring name);
				PrimitiveTypeNode(std::wstring name, int numpointers);
				PrimitiveTypeNode(std::wstring name, int numpointers, Node* arrayDim);
				~PrimitiveTypeNode();
				std::wstring GetName();
				int GetNumPointers();
				void SetNumPointers(int numPointers);
				void SetArrayDim(Node* arrayDim);
				Node* GetArrayDim();
				std::wstring To_String();
				bool Equals(Node* n);
				int Compare(TypeNode* check);
				bool CheckArrayDim(SymbolTable env);
				void VerifyValidType(SymbolTable env);
				Node* GetDefaultValue(SymbolTable env);
				int GetTypeSize(SymbolTable env);
			};
			
			/*
			*		StructTypeNode Class: represents a struct type
			*		Contains:	name - string
			*/

			class StructTypeNode : public TypeNode {
			protected:
				StructTypeNode(StructTypeNode&);
				std::wstring name;
				int numPointers;
				Node* arrayDim;
			public:
				StructTypeNode() {}
				StructTypeNode(std::wstring name);
				StructTypeNode(std::wstring name, int numpointers);
				StructTypeNode(std::wstring name, int numpointers, Node* arrayDim);
				~StructTypeNode();
				std::wstring GetName();
				int GetNumPointers();
				void SetNumPointers(int numPointers);
				void SetArrayDim(Node* arrayDim);
				Node* GetArrayDim();
				std::wstring To_String();
				bool Equals(Node* n);
				int Compare(TypeNode* check);
				bool CheckArrayDim(SymbolTable env);
				void VerifyValidType(SymbolTable env);
				Node* GetDefaultValue(SymbolTable env);
				int GetTypeSize(SymbolTable env);
			};


			/*
			*		ExprNode Class: Provides an abstract interface for all AST expression nodes
			*/

			class ExprNode: public Node {
			protected:
				ExprNode();
				ExprNode(ExprNode&);
				std::wstring _error;
			public:
				~ExprNode();
				virtual TypeNode* TypeOf(SymbolTable* env) = 0;
				std::wstring ErrorReport();
				virtual bool IsConstant(int* val)=0;
				virtual std::list<std::wstring> GetFunctionUses() = 0;
				virtual MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset) = 0;
				virtual MiniC::IR::Epicness::FlowGraph::FlowGraph* StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset) = 0;
				virtual MiniC::IR::Epicness::FlowGraph::FlowGraph* GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset) = 0;
			};

			/*
			*		FormalNode Class: represents the formal parameters of a method
			*		Contains:	name - string
			*				type - TypeNode
			*/

			class FormalNode : public Node {
			protected:
				FormalNode(FormalNode&);
				int allocSize;
			public:
				std::wstring name;
				TypeNode* type;
				FormalNode() {}
				FormalNode(std::wstring name, TypeNode* type);
				~FormalNode();
				std::wstring To_String();
				bool Equals(Node* n);
				SymbolTable FullTypeCheck(SymbolTable env);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg);
			};


			/*
			*		FuncNode Class: represents the set of classes which can be found in a global scope.
			*		Contains:	isMain - boolean
			*/
			class TranslationUnitNode : public Node
			{
			protected:
				TranslationUnitNode(TranslationUnitNode&);
				TranslationUnitNode() {}
			public:
				bool isMain;
				bool isDecl;
				bool isInterruptHandler;
				~TranslationUnitNode();
				virtual std::wstring To_String()=0;
				virtual SymbolTable Register(SymbolTable env)=0;
				virtual SymbolTable FullTypeCheck(SymbolTable env)=0;
				virtual std::list<std::wstring> GetFunctionUses() = 0;
				virtual bool CheckUsage(std::list<std::wstring> usedFunctions)=0;
				virtual void Optimize(SymbolTable env)=0;
				virtual MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg)=0;
			};


			/*
			*		FuncNode Class: represents a function declaration and implementation
			*		Contains:	name		- string
			*				type		- TypeNode
			*				parameters	- list of formals
			*				body		- list of statements
			*/

			class FuncNode : public TranslationUnitNode {
			protected:
				FuncNode(FuncNode&);
				std::wstring name;
				TypeNode* type;
				std::list<FormalNode*> parameters;
				std::list<StmtNode*> body;
				bool isVoid;
				bool isVariableLength;
			public:
				FuncNode() {}
				~FuncNode();
				FuncNode(std::wstring name, TypeNode* type, std::list<FormalNode*> parameters, bool isInterruptHandler, bool isVariableLength, std::list<StmtNode*> body);
				std::wstring To_String();
				bool Equals(Node* n);
				SymbolTable Register(SymbolTable env);
				SymbolTable FullTypeCheck(SymbolTable env);
				bool CheckUsage(std::list<std::wstring> usedFunctions);
				std::list<std::wstring> GetFunctionUses();
				void Optimize(SymbolTable env);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg);
			};


			/*
			*		FuncDeclNode Class: represents a function declaration
			*		Contains:	name		- string
			*				type		- TypeNode
			*				parameters	- list of formals
			*/

			class FuncDeclNode : public TranslationUnitNode {
			protected:
				FuncDeclNode(FuncDeclNode&);
				std::wstring name;
				TypeNode* type;
				std::list<FormalNode*> parameters;
				bool isVariableLength;
			public:
				FuncDeclNode() {}
				~FuncDeclNode();
				FuncDeclNode(std::wstring name, TypeNode* type, std::list<FormalNode*> parameters, bool isVariableLength);
				std::wstring To_String();
				bool Equals(Node* n);
				SymbolTable Register(SymbolTable env);
				SymbolTable FullTypeCheck(SymbolTable env);
				bool CheckUsage(std::list<std::wstring> usedFunctions);
				std::list<std::wstring> GetFunctionUses();
				void Optimize(SymbolTable env);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg);
			};

			/*
			*		GlobalDeclAssignNode Class: represents a declaration & assignment node at the global scope
			*		Contains:	type - Type
			*					name - string
			*					rhs  - expression
			*/

			class GlobalDeclAssignNode : public TranslationUnitNode
			{
			protected:
				GlobalDeclAssignNode(GlobalDeclAssignNode&);
				bool defaultVal;
				int allocSize;
			public:
				std::wstring name;
				ExprNode* rhs;
				TypeNode* type;
				GlobalDeclAssignNode() {}
				GlobalDeclAssignNode(TypeNode* type, std::wstring name, ExprNode* rhs);
				~GlobalDeclAssignNode();
				std::wstring To_String();
				bool Equals(Node* n);
				SymbolTable Register(SymbolTable env);
				SymbolTable FullTypeCheck(SymbolTable env);
				bool CheckUsage(std::list<std::wstring> usedFunctions);
				std::list<std::wstring> GetFunctionUses();
				void Optimize(SymbolTable env);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg);
			};	

			/*
			*		GlobalStructInitNode Class: represents a declaration & assignment node
			*		Contains:	type - Type
			*					name - string
			*					inits - list<string>
			*					defaultVal - bool
			*/

			class GlobalStructInitNode : public TranslationUnitNode
			{
			protected:
				GlobalStructInitNode(GlobalStructInitNode&);
				bool defaultVal;
				std::list<ExprNode*> inits;
				std::wstring name;
				TypeNode* type;
			public:
				GlobalStructInitNode() {}
				GlobalStructInitNode(TypeNode* type, std::wstring name, std::list<ExprNode*> inits);
				~GlobalStructInitNode();
				std::wstring To_String();
				bool Equals(Node* n);
				SymbolTable Register(SymbolTable env);
				SymbolTable FullTypeCheck(SymbolTable env);
				bool CheckUsage(std::list<std::wstring> usedFunctions);
				std::list<std::wstring> GetFunctionUses();
				void Optimize(SymbolTable env);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg);
			};	

			/*
			*		StructDeclNode Class: represents the declaration of a struct
			*/

			class StructDeclNode : public TranslationUnitNode
			{
			protected:
				StructDeclNode(StructDeclNode&);
				std::list<TypeNode*> types;
				std::list<std::wstring> names;
				std::wstring struct_name;
				std::wstring init_name;
			public:
				StructDeclNode() {}
				StructDeclNode(std::wstring name, std::wstring init_name, std::list<TypeNode*> types, std::list<std::wstring> varnames);
				~StructDeclNode();
				std::wstring To_String();
				bool Equals(Node* n);
				SymbolTable Register(SymbolTable env);
				SymbolTable FullTypeCheck(SymbolTable env);
				bool CheckUsage(std::list<std::wstring> usedFunctions);
				std::list<std::wstring> GetFunctionUses();
				void Optimize(SymbolTable env);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg);
			};	



			/*
			*		ProgramNode Class: represents a program in the minijava AST
			*		Contains:	mainFunc	- main function declaration
			*			        otherFuncs	- all other class declarations
			*/

			class ProgramNode: public Node {
			protected:
				std::list<TranslationUnitNode*> funcs;
			public:
				ProgramNode(ProgramNode&);

				ProgramNode() {}
				ProgramNode(std::list<TranslationUnitNode*> others);
				~ProgramNode();
				std::wstring To_String();
				bool Equals(Node* n);
				SymbolTable FullTypeCheck(SymbolTable env);
				SymbolTable GetFunctions(SymbolTable env, bool isOS);
				void Optimize(SymbolTable env);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph();
			};





			//////////////////////////////////////
			//	       Statement Classes     	//
			//	     * Execution Statements	//
			//////////////////////////////////////



			/*
			*		ExpressionStmt Class: represents an expression acting as a statement.
			*		Contains:	expr - Expression
			*/

			class ExpressionStmt : public StmtNode {
			protected:
				ExpressionStmt(ExpressionStmt&);

			public:
				ExprNode* expr;
				ExpressionStmt() {}
				ExpressionStmt(ExprNode* expr);
				~ExpressionStmt();
				std::wstring To_String();
				bool Equals(Node* n);
				SymbolTable FullTypeCheck(SymbolTable env);
				std::list<std::wstring> GetFunctionUses();
				void Optimize(SymbolTable env);
				bool IsEmpty();
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg);
			};

			/*
			*		DeclAssignNode Class: represents a declaration & assignment node
			*		Contains:	type - Type
			*					name - string
			*					rhs  - expression
			*/

			class DeclAssignNode : public StmtNode {
			protected:
				DeclAssignNode(DeclAssignNode&);
				bool defaultVal;
				int allocSize;
			public:
				std::wstring name;
				ExprNode* rhs;
				TypeNode* type;
				DeclAssignNode() {}
				DeclAssignNode(TypeNode* type, std::wstring name, ExprNode* rhs);
				~DeclAssignNode();
				std::wstring To_String();
				bool Equals(Node* n);
				SymbolTable FullTypeCheck(SymbolTable env);
				std::list<std::wstring> GetFunctionUses();
				void Optimize(SymbolTable env);
				bool IsEmpty();
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg);
			};	

			/*
			*		StructInitNode Class: represents a declaration & assignment node
			*		Contains:	type - Type
			*					name - string
			*					inits - list<string>
			*					defaultVal - bool
			*/

			class StructInitNode : public StmtNode {
			protected:
				StructInitNode(StructInitNode&);
				bool defaultVal;
				std::list<ExprNode*> inits;
				std::wstring name;
				TypeNode* type;
			public:
				StructInitNode() {}
				StructInitNode(TypeNode* type, std::wstring name, std::list<ExprNode*> inits);
				~StructInitNode();
				std::wstring To_String();
				bool Equals(Node* n);
				SymbolTable FullTypeCheck(SymbolTable env);
				std::list<std::wstring> GetFunctionUses();
				void Optimize(SymbolTable env);
				bool IsEmpty();
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg);
			};		

			/*
			*		BlockNode Class: represents a block 
			*		Contains:	body - list of statements
			*/

			class BlockNode : public StmtNode {
			protected:
				BlockNode(BlockNode&);
				std::list<StmtNode*> body;
			public:
				BlockNode() {}
				BlockNode(std::list<StmtNode*> body);
				~BlockNode();
				std::wstring To_String();
				bool Equals(Node* n);
				SymbolTable FullTypeCheck(SymbolTable env);
				std::list<std::wstring> GetFunctionUses();
				void Optimize(SymbolTable env);
				bool IsEmpty();
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg);
			};

			/*
			*		ReturnNode Class: represents a return from a function
			*		Contains:	rhs - expression
			*/

			class ReturnNode : public StmtNode {
			protected:
				ReturnNode(ReturnNode&);
			public:
				ExprNode* rhs;
				ReturnNode() {}
				ReturnNode(ExprNode* rhs);
				~ReturnNode();
				std::wstring To_String();
				bool Equals(Node* n);
				SymbolTable FullTypeCheck(SymbolTable env);
				std::list<std::wstring> GetFunctionUses();
				void Optimize(SymbolTable env);
				bool IsEmpty();
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg);
			};

			/*
			*		IfNode Class: represents an if-then-else branching structure
			*		Contains:	testcase - expression
			*					thenstmt - statement
			*					elsestmt - statement
			*/

			class IfNode : public StmtNode {
			protected:
				IfNode(IfNode&);
				ExprNode* testcase;
				StmtNode* thenstmt;
				StmtNode* elsestmt;
			public:
				IfNode() {}
				IfNode(ExprNode* testcase, StmtNode* thenstmt, StmtNode* elsestmt);
				IfNode(ExprNode* testcase, StmtNode* thenstmt);
				~IfNode();
				std::wstring To_String();
				bool Equals(Node* n);
				SymbolTable FullTypeCheck(SymbolTable env);
				std::list<std::wstring> GetFunctionUses();
				void Optimize(SymbolTable env);
				bool IsEmpty();
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg);
			};

			/*
			*		SwitchNode Class: represents an switch branching structure
			*		Contains:	testcase - expression
			*					cases - list of expressions
			*					thenstmts - list of statements
			*					defaultCase - statement
			*/

			class SwitchNode : public StmtNode {
			protected:
				SwitchNode(SwitchNode&);
				ExprNode* testcase;
				std::list<ExprNode*> cases;
				std::list<StmtNode*> thenstmts;
				StmtNode* defaultCase;
			public:
				SwitchNode() {}
				SwitchNode(ExprNode* test, std::list<ExprNode*> cases, std::list<StmtNode*> thenstmts, StmtNode* defaultCase);
				~SwitchNode();
				std::wstring To_String();
				bool Equals(Node* n);
				SymbolTable FullTypeCheck(SymbolTable env);
				std::list<std::wstring> GetFunctionUses();
				void Optimize(SymbolTable env);
				bool IsEmpty();
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg);
			};

			/*
			*		WhileNode Class: represents a while looping structure
			*		Contains:	testcase - expression
			*					body	 - statement
			*/

			class WhileNode : public StmtNode {
			protected:
				WhileNode(WhileNode&);
				ExprNode* testcase;
				StmtNode* body;
			public:
				WhileNode() {}
				WhileNode(ExprNode* testcase, StmtNode* body);
				~WhileNode();
				std::wstring To_String();
				bool Equals(Node* n);
				SymbolTable FullTypeCheck(SymbolTable env);
				std::list<std::wstring> GetFunctionUses();
				void Optimize(SymbolTable env);
				bool IsEmpty();
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg);
			};

			//////////////////////////////////////
			//	Expression Classes        //
			//////////////////////////////////////


			/*
			*		AssignNode Class: represents an assignment of a pre-existing variable or field
			*		Contains:	name - string
			*					rhs  - expression
			*/

			class AssignNode : public ExprNode 
			{
			protected:
				AssignNode(AssignNode&);
				ExprNode* lhs;
				ExprNode* rhs;
			public:
				AssignNode() {}
				AssignNode(ExprNode* lhs, std::wstring op, ExprNode* rhs);
				~AssignNode();
				std::wstring To_String();
				bool Equals(Node* n);
				TypeNode* TypeOf(SymbolTable* env);
				std::list<std::wstring> GetFunctionUses();
				bool IsConstant(int* val);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset);
			};

			/*
			*		BinaryNode Class: represents a binary expression
			*		Contains:	operation	- string
			*				lhs			- expression
			*				rhs			- expression
			*/

			class BinaryNode : public ExprNode {
			protected:
				BinaryNode(BinaryNode&);
				ExprNode* lhs;
				ExprNode* rhs;
				std::wstring operation;
			public:
				BinaryNode() {}
				BinaryNode(ExprNode* lhs, std::wstring operation, ExprNode* rhs);
				~BinaryNode();
				std::wstring To_String();
				bool Equals(Node* n);
				TypeNode* TypeOf(SymbolTable* env);
				std::list<std::wstring> GetFunctionUses();
				bool IsConstant(int* val);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset);
			};

			/*
			*		KeywordNode Class: represents a keyword expression
			*		Contains:	word - string
			*/

			class KeywordNode : public ExprNode {
			protected:
				KeywordNode(KeywordNode&);
				std::wstring word;
			public:
				KeywordNode() {}
				KeywordNode(std::wstring word);
				~KeywordNode();
				TypeNode* TypeOf(SymbolTable* env);
				std::wstring To_String();
				bool Equals(Node* n);
				int GetConstValue();
				std::wstring GetWord();
				std::list<std::wstring> GetFunctionUses();
				bool IsConstant(int* val);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset);
			};

			/*
			*		VarNode Class: represents a variable expression
			*		Contains:	name - wstring
			*                          type - wstring
			*/

			class VarNode : public ExprNode {
			protected:
				VarNode(VarNode&);
			public:
				std::wstring name;
				VarNode() {}
				VarNode(std::wstring name);
				~VarNode();
				TypeNode* TypeOf(SymbolTable* env);
				std::wstring To_String();
				bool Equals(Node* n);
				std::list<std::wstring> GetFunctionUses();
				bool IsConstant(int* val);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset);
			};

			/*
			*		IntNode Class: represents a constant integer
			*		Contains:	val - int
			*/

			class IntNode : public ExprNode {
			protected:
				IntNode(IntNode&);
				int val;
			public:
				IntNode() {}
				IntNode(std::wstring val);
				IntNode(int val);
				~IntNode();
				std::wstring To_String();
				bool Equals(Node* n);
				TypeNode* TypeOf(SymbolTable* env);
				std::list<std::wstring> GetFunctionUses();
				bool IsConstant(int* val);
				int GetValue();
				int GetConstValue();
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset);
			};

			/*
			*		FuncCallNode Class: represents a method call
			*		contains:	funcname	- string
			*				params		- list of expressions
			*/

			class FuncCallNode : public ExprNode {
			protected:
				FuncCallNode(FuncCallNode&);
				std::list<ExprNode*> params;
				std::wstring returnType;
			public:
				std::wstring funcname;
				FuncCallNode() {}
				FuncCallNode(std::wstring funcname, std::list<ExprNode*> params);
				FuncCallNode(ExprNode* funcname, std::list<ExprNode*> params);
				~FuncCallNode();
				TypeNode* TypeOf(SymbolTable* env);
				std::wstring To_String();
				bool Equals(Node* n);
				std::list<std::wstring> GetFunctionUses();
				bool IsConstant(int* val);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset);
			};

			/*
			*		UnaryNode Class: represents a unary expression
			*		contains:	operation	- string
			*					rhs			- expression
			*					
			*/

			class UnaryNode : public ExprNode {
			protected:
				UnaryNode(UnaryNode&);
				ExprNode* rhs;
				std::wstring operation;
			public:
				UnaryNode() {}
				UnaryNode(std::wstring operation, ExprNode* rhs);
				~UnaryNode();
				TypeNode* TypeOf(SymbolTable* env);
				std::wstring To_String();
				bool Equals(Node* n);
				std::list<std::wstring> GetFunctionUses();
				bool IsConstant(int* val);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset);
			};

			/*
			*		TernaryNode Class: represents a ternary expression
			*					
			*/

			class TernaryNode : public ExprNode {
			protected:
				TernaryNode(TernaryNode&);
				ExprNode* cond;
				ExprNode* thenstmt;
				ExprNode* elsestmt;
			public:
				TernaryNode() {}
				TernaryNode(ExprNode* cond, ExprNode* thenstmt, ExprNode* elsestmt);
				~TernaryNode();
				TypeNode* TypeOf(SymbolTable* env);
				std::wstring To_String();
				bool Equals(Node* n);
				std::list<std::wstring> GetFunctionUses();
				bool IsConstant(int* val);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset);
			};

			/*
			*		StringNode Class: represents a string
			*					
			*/

			class StringNode : public ExprNode {
			protected:
				StringNode(StringNode&);
				std::wstring* value;
			public:
				StringNode() {}
				StringNode(std::wstring* value);
				~StringNode();
				TypeNode* TypeOf(SymbolTable* env);
				std::wstring To_String();
				bool Equals(Node* n);
				std::list<std::wstring> GetFunctionUses();
				bool IsConstant(int* val);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset);
			};

			/*
			*		CharNode Class: represents a character
			*					
			*/

			class CharNode : public ExprNode {
			protected:
				CharNode(CharNode&);
				TCHAR value;
			public:
				CharNode() {}
				CharNode(std::wstring* value);
				CharNode(TCHAR val);
				~CharNode();
				TypeNode* TypeOf(SymbolTable* env);
				std::wstring To_String();
				bool Equals(Node* n);
				int GetConstValue();
				std::list<std::wstring> GetFunctionUses();
				bool IsConstant(int* val);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset);
			};

			/*
			*		ArrayNode Class: represents indexing into an array
			*					
			*/

			class ArrayNode : public ExprNode {
			protected:
				ArrayNode(ArrayNode&);
				ExprNode* lhs;
				ExprNode* inner;
			public:
				ArrayNode() {}
				ArrayNode(ExprNode* lhs, ExprNode* inner);
				~ArrayNode();
				TypeNode* TypeOf(SymbolTable* env);
				std::wstring To_String();
				bool Equals(Node* n);
				std::list<std::wstring> GetFunctionUses();
				bool IsConstant(int* val);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset);
			};

			/*
			*		AssemblyNode Class: Represents a "function" call inserting some custom assembly into the generated code.
			*					
			*/

			class AssemblyNode : public ExprNode {
			protected:
				std::wstring code;
				boost::unordered_map<std::wstring, std::wstring> invars;
				boost::unordered_map<std::wstring, std::wstring> outvars;
			public:
				AssemblyNode() {}
				AssemblyNode(std::wstring code, std::wstring inputs, std::wstring outputs);
				~AssemblyNode();
				std::wstring To_String();
				bool Equals(Node* n);
				TypeNode* TypeOf(SymbolTable* env);
				std::list<std::wstring> GetFunctionUses();
				bool IsConstant(int* val);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset);
			};

			/*
			*		SizeOfNode Class: Represents a "function" call to find out the size of a type.
			*					
			*/

			class SizeOfNode : public ExprNode {
			protected:
				TypeNode* type;
				std::wstring size;
				std::wstring strType;
			public:
				SizeOfNode() {}
				SizeOfNode(std::wstring type);
				~SizeOfNode();
				std::wstring To_String();
				bool Equals(Node* n);
				int GetConstValue();
				TypeNode* TypeOf(SymbolTable* env);
				std::list<std::wstring> GetFunctionUses();
				bool IsConstant(int* val);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset);
			};

			/*
			*	StructReferenceNode: Represents a reference through . or -> to a field in a struct.
			*/
			class StructReferenceNode : public ExprNode {
			protected:
				ExprNode* lhs;
				std::wstring fieldName;
				TypeNode* lhsType;
			public:
				StructReferenceNode() {}
				StructReferenceNode(StructReferenceNode* srn);
				StructReferenceNode(ExprNode* lhs, bool isArrow, std::wstring field);
				~StructReferenceNode();
				std::wstring To_String();
				bool Equals(Node* n);
				int GetConstValue();
				TypeNode* TypeOf(SymbolTable* env);
				std::list<std::wstring> GetFunctionUses();
				bool IsConstant(int* val);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetFlowGraph(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* StoreValue(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, int offset);
				MiniC::IR::Epicness::FlowGraph::FlowGraph* GetAddress(MiniC::IR::Epicness::FlowGraph::FlowGraph* fg, std::wstring storage, int offset);
			};
		}
	}
}

#endif
