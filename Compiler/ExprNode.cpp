#include "Node.h"
#include "stdafx.h"

namespace MiniC
{
	namespace IR
	{
		namespace AST
		{
			/*
			*		AssignNode Class: represents an assignment of a pre-existing variable or field
			*		Contains:	name - string
			*					rhs  - expression
			*/

			AssignNode::AssignNode(AssignNode& an)
			{
				this->lhs = an.lhs;
				this->rhs = an.rhs;
			}

			AssignNode::AssignNode(ExprNode* lhs, std::wstring op, ExprNode* rhs)
			{
				this->lhs = lhs;
				if (op.compare(L"+=") == 0)
				{
					this->rhs = new BinaryNode(lhs, L"+", rhs);
				}
				else if (op.compare(L"-=") == 0)
				{
					this->rhs = new BinaryNode(lhs, L"-", rhs);
				}
				else if (op.compare(L">>=") == 0)
				{
					this->rhs = new BinaryNode(lhs, L">>", rhs);
				}
				else if (op.compare(L"<<=") == 0)
				{
					this->rhs = new BinaryNode(lhs, L"<<", rhs);
				}
				else if (op.compare(L"&=") == 0)
				{
					this->rhs = new BinaryNode(lhs, L"&", rhs);
				}
				else if (op.compare(L"|=") == 0)
				{
					this->rhs = new BinaryNode(lhs, L"|", rhs);
				}
				else if (op.compare(L"^=") == 0)
				{
					this->rhs = new BinaryNode(lhs, L"^", rhs);
				}
				else
				{
					this->rhs = rhs;
				}
			}

			AssignNode::~AssignNode()
			{
				if (this->lhs)
				{
					delete this->lhs;
				}
				this->lhs = NULL;
				if (this->rhs)
				{
					delete this->rhs;
				}
				this->rhs = NULL;
			}

			std::wstring AssignNode::To_String()
			{
				std::wstringstream returnable;
				returnable << L"Assign Node: LHS = ";
				returnable << this->lhs->To_String();
				returnable << L"\n";
				returnable << L"RHS = ";
				returnable << this->rhs->To_String();
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool AssignNode::Equals(Node* n)
			{
				AssignNode* an;
				try
				{
					an = dynamic_cast<AssignNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				return (this->lhs->Equals(an->lhs) && this->rhs->Equals(an->rhs));
			}

			/*
			*		BinaryNode Class: represents a binary expression
			*		Contains:	operation	- string
			*				lhs			- expression
			*				rhs			- expression
			*/

			BinaryNode::BinaryNode(BinaryNode& bn) {
				this->operation = bn.operation;
				this->lhs = bn.lhs;
				this->rhs = bn.rhs;
			}

			BinaryNode::BinaryNode(ExprNode* lhs, std::wstring operation, ExprNode* rhs) {
				this->operation = operation;
				this->lhs = lhs;
				this->rhs = rhs;
			}

			BinaryNode::~BinaryNode() {
				this->operation = L"";
				if (this->lhs) {
					delete this->lhs;
				}
				this->lhs = NULL;
				if (this->rhs) {
					delete this->rhs;
				}
				this->rhs = NULL;
			}

			std::wstring BinaryNode::To_String() {
				std::wstringstream returnable;
				returnable << L"Enter Binary Node\nLHS:\n";
				returnable << this->lhs->To_String();
				returnable << L"Operation:\n";
				returnable << this->operation << std::endl;
				returnable << L"RHS:\n";
				returnable << this->rhs->To_String();
				returnable << L"Leave Binary Node\n";
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool BinaryNode::Equals(Node* n)
			{
				BinaryNode* bn;
				try
				{
					bn = dynamic_cast<BinaryNode*>(n);	
				}
				catch(...)
				{
					return false;
				}
				return (bn && this->lhs->Equals(bn->lhs) && this->rhs->Equals(bn->rhs) && (this->operation.compare(bn->operation) == 0));
			}

			/*
			*		KeywordNode Class: represents a keyword expression
			*		Contains:	word - string
			*/

			KeywordNode::KeywordNode(KeywordNode& kn) {
				this->word = kn.word;
			}

			KeywordNode::KeywordNode(std::wstring word) {
				this->word = word;
			}

			KeywordNode::~KeywordNode() {
				this->word = L"";
			}

			std::wstring KeywordNode::To_String() {
				std::wstringstream returnable;
				returnable << L"KeywordNode with value ";
				returnable << this->word;
				returnable << L".\n";
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool KeywordNode::Equals(Node* n)
			{
				KeywordNode* kn;
				try
				{
					kn = dynamic_cast<KeywordNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				return (kn && this->word.compare(kn->word) == 0);
			}

			std::wstring KeywordNode::GetWord()
			{
				return this->word;
			}

			/*
			*		VarNode Class: represents a variable expression
			*		Contains:	name - string
			*/

			VarNode::VarNode(VarNode& vn) {
				this->name = vn.name;
			}

			VarNode::VarNode(std::wstring name) {
				this->name = name;
			}

			VarNode::~VarNode() {
				this->name = L"";
			}

			std::wstring VarNode::To_String() {
				std::wstringstream returnable;
				returnable << L"VarNode with name ";
				returnable << this->name;
				returnable << L".\n";
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool VarNode::Equals(Node* n)
			{
				VarNode* vn;
				try
				{
					vn = dynamic_cast<VarNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				return (vn && this->name.compare(vn->name) == 0);
			}

			/*
			*		IntNode Class: represents a constant integer
			*		Contains:	val - int
			*/

			IntNode::IntNode(IntNode& in)
			{
				this->val = in.val;
			}

			IntNode::IntNode(std::wstring val)
			{
				this->val = _wtoi(val.c_str());
			}

			IntNode::IntNode(int val)
			{
				this->val = val;
			}

			IntNode::~IntNode() {
			}

			std::wstring IntNode::To_String()
			{
				std::wstringstream returnable;
				returnable << L"Int Node with value ";
				returnable << this->val;
				returnable << L".\n";
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool IntNode::Equals(Node* n)
			{
				IntNode* in;
				try
				{
					in = dynamic_cast<IntNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				return in && this->val == in->val;
			}

			int IntNode::GetValue()
			{
				return this->val;
			}

			/*
			*		FuncCallNode Class: represents a method call
			*		contains:	funcname	- string
			*				params		- list of expressions
			*/

			FuncCallNode::FuncCallNode(FuncCallNode& mcn)
			{
				this->funcname = mcn.funcname;
				this->params = mcn.params;
			}

			FuncCallNode::FuncCallNode(std::wstring funcname, std::list<ExprNode*> params)
			{
				this->funcname = funcname;
				this->params = params;
			}

			FuncCallNode::FuncCallNode(ExprNode* func, std::list<ExprNode*> params)
			{
				this->funcname = ((VarNode*) func)->name;
				this->params = params;
			}

			FuncCallNode::~FuncCallNode()
			{
				this->funcname = L"";
				BOOST_FOREACH(ExprNode* param, this->params) {
					if (param) {
						delete param;
					}
					param = NULL;
				}
				this->params.clear();      
			}

			std::wstring FuncCallNode::To_String()
			{
				std::wstringstream returnable;
				returnable << L"Enter MethodCallNode";
				returnable << L"\nFunction Name: ";
				returnable << this->funcname;
				returnable << L"\nParams: ";
				BOOST_FOREACH(ExprNode* param, this->params) {
					returnable << param->To_String() << L"\n";
				}
				returnable << L"Leave MethodCallNode";
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool FuncCallNode::Equals(Node* n)
			{
				FuncCallNode* fcn;
				try
				{
					fcn = dynamic_cast<FuncCallNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				if (!fcn)
				{
					return false;
				}
				if (this->funcname.compare(fcn->funcname) != 0)
				{
					return false;
				}
				else if (this->returnType.compare(fcn->returnType) != 0)
				{
					return false;
				}
				else
				{
					std::list<ExprNode*> formalcopy = std::list<ExprNode*>();
					BOOST_FOREACH(ExprNode* e, this->params)
					{
						formalcopy.push_back(e);
					}
					int size = formalcopy.size();
					BOOST_FOREACH(ExprNode* e, fcn->params)
					{
						formalcopy.remove(e);
						if (size - 1 != formalcopy.size())
						{
							return false;
						}
						size--;
					}
					return size == 0;
				}
			}

			/*
			*		UnaryNode Class: represents a unary expression
			*		contains:	operation	- string
			*					rhs			- expression
			*					
			*/

			UnaryNode::UnaryNode(UnaryNode& un) {
				this->operation = un.operation;
				this->rhs = un.rhs;
			}

			UnaryNode::UnaryNode(std::wstring operation, ExprNode* rhs) {
				this->operation = operation;
				this->rhs = rhs;
			}

			UnaryNode::~UnaryNode() {
				this->operation = L"";
				if (this->rhs) {
					delete this->rhs;
				}
				this->rhs = NULL;
			}

			std::wstring UnaryNode::To_String() {
				std::wstringstream returnable;
				returnable <<  L"Enter Unary Node\nOperation: ";
				returnable << this->operation;
				returnable << L"\nRHS: ";
				returnable << this->rhs->To_String();
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool UnaryNode::Equals(Node* n)
			{
				UnaryNode* un;
				try
				{
					un = dynamic_cast<UnaryNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				if (!un)
				{
					return false;
				}
				if (this->operation.compare(un->operation) != 0)
				{
					return false;
				}
				else
				{
					return this->rhs->Equals(un->rhs);
				}
			}


			TernaryNode::TernaryNode(TernaryNode& tn)
			{
				this->cond = tn.cond;
				this->thenstmt = tn.thenstmt;
				this->elsestmt = tn.elsestmt;
			}

			TernaryNode::TernaryNode(ExprNode* cond, ExprNode* thenstmt, ExprNode* elsestmt)
			{
				this->cond = cond;
				this->thenstmt = thenstmt;
				this->elsestmt = elsestmt;
			}

			TernaryNode::~TernaryNode()
			{
				if (this->cond)
				{
					delete this->cond;
				}
				this->cond = NULL;
				if (this->thenstmt)
				{
					delete this->thenstmt;
				}
				this->thenstmt = NULL;
				if (this->elsestmt)
				{
					delete this->elsestmt;
				}
				this->elsestmt = NULL;
			}

			std::wstring TernaryNode::To_String()
			{
				std::wstringstream returnable;
				returnable <<  L"Enter Ternary Node\nCondition: ";
				returnable << this->cond->To_String();
				returnable << L"\nThen Stmt: ";
				returnable << this->thenstmt->To_String();
				returnable << L"\nElse Stmt: ";
				returnable << this->elsestmt->To_String();
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool TernaryNode::Equals(Node* n)
			{
				TernaryNode* tn;
				try
				{
					tn = dynamic_cast<TernaryNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				if (!tn)
				{
					return false;
				}
				if (!this->cond->Equals(tn->cond))
				{
					return false;
				}
				else if (!this->thenstmt->Equals(tn->thenstmt))
				{
					return false;
				}
				else if (!this->elsestmt->Equals(tn->elsestmt))
				{
					return false;
				}
				else
				{
					return true;
				}
			}


			/*
			*		StringNode Class: represents a string
			*					
			*/

			StringNode::StringNode(StringNode& sn)
			{
				this->value = sn.value;
			}

			StringNode::StringNode(std::wstring* value)
			{
				this->value = new std::wstring(value->substr(1, value->length() - 2));
			}

			StringNode::~StringNode()
			{
				this->value = new std::wstring(L"");
			}

			std::wstring StringNode::To_String()
			{
				std::wstringstream returnable;
				returnable <<  L"Enter String Node\nValue: ";
				returnable << this->value;
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool StringNode::Equals(Node* n)
			{
				StringNode* sn;
				try
				{
					sn = dynamic_cast<StringNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				return sn && sn->value->compare(*this->value) == 0;
			}

			/*
			*		CharNode Class: represents a string
			*					
			*/

			CharNode::CharNode(CharNode& sn)
			{
				this->value = sn.value;
			}

			CharNode::CharNode(std::wstring* value)
			{
				if ((*value)[1] == L'\\')
				{
					switch((*value)[2])
					{
					case L'0':
						this->value = L'\0';
						break;
					case L'n':
					case L'N':
						this->value = L'\n';
						break;
					case L't':
					case L'T':
						this->value = L'\t';
						break;
					case L'r':
					case L'R':
						this->value = L'\r';
						break;
					case L'"':
						this->value = L'\"';
						break;
					case L'\'':
						this->value = L'\'';
						break;
					case L'\\':
						this->value = L'\\';
						break;
					default:
						this->value = L'\0';
						break;
					}
				}
				else
				{
					this->value = (*value)[1];
				}
			}

			CharNode::CharNode(TCHAR val)
			{
				this->value = val;
			}

			CharNode::~CharNode()
			{
				this->value = 0;
			}

			std::wstring CharNode::To_String()
			{
				std::wstringstream returnable;
				returnable <<  L"Enter Char Node\nValue: ";
				returnable << this->value;
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool CharNode::Equals(Node* n)
			{
				CharNode* cn;
				try
				{
					cn = dynamic_cast<CharNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				return cn && this->value == cn->value;
			}

			int CharNode::GetConstValue()
			{
				return (int) this->value;
			}

			/*
			*		ArrayNode Class: represents indexing into an array
			*					
			*/

			ArrayNode::ArrayNode(ArrayNode& an)
			{
				this->lhs = an.lhs;
				this->inner = an.inner;
			}

			ArrayNode::ArrayNode(ExprNode* lhs, ExprNode* inner)
			{
				this->lhs = lhs;
				this->inner = inner;
			}

			ArrayNode::~ArrayNode()
			{
				if (this->lhs)
				{
					delete this->lhs;
				}
				this->lhs = NULL;
				if (this->inner)
				{
					delete this->inner;
				}
				this->inner = NULL;
			}

			std::wstring ArrayNode::To_String()
			{
				std::wstringstream returnable;
				returnable <<  L"Enter Array Node\nLHS: ";
				returnable << this->lhs->To_String();
				returnable << L"\nInner:\n";
				returnable << this->inner->To_String();
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool ArrayNode::Equals(Node* n)
			{
				ArrayNode* an;
				try
				{
					an = dynamic_cast<ArrayNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				return (an && this->inner->Equals(an->inner) && this->lhs->Equals(an->lhs));
			}

			AssemblyNode::AssemblyNode(std::wstring code, std::wstring inputs, std::wstring outputs)
			{
				TCHAR* tmpCode = (TCHAR*) calloc(sizeof(TCHAR), code.size() + 1);
				swscanf_s(code.c_str(), L"\"%[^\n\"]s\"", tmpCode, code.size() + 1);
				this->code = std::wstring(tmpCode);
				TCHAR* var = (TCHAR*) calloc(sizeof(TCHAR), inputs.size() + outputs.size());
				TCHAR* val = (TCHAR*) calloc(sizeof(TCHAR), inputs.size() + outputs.size());
				this->invars = boost::unordered_map<std::wstring, std::wstring>();
				TCHAR* inputsChar = (TCHAR*) calloc(sizeof(TCHAR), inputs.size() + 1);
				wcscpy_s(inputsChar, inputs.size() + 1, inputs.c_str());
				TCHAR* context;
				TCHAR* pair = wcstok_s(inputsChar + 1, L", ", &context);
				if (pair != NULL && wcslen(pair) > 0)
				{
					do
					{
						TCHAR* var = (TCHAR*) calloc(sizeof(TCHAR), inputs.size() + outputs.size());
						TCHAR* val = (TCHAR*) calloc(sizeof(TCHAR), inputs.size() + outputs.size());
						swscanf_s(pair, L"%[^ \n:\"] : %[^ \n:\"]", var, inputs.size() + outputs.size(), val, inputs.size() + outputs.size());
						if (wcscmp(var, L"") != 0 && wcscmp(val, L"") != 0)
						{
							std::wstring vars = std::wstring();
							vars.append(var);
							std::wstring vals = std::wstring();
							vals.append(val);
							this->invars[vars] = vals;
						}
					} while((pair = wcstok_s(NULL, L", ", &context)) != NULL);
				}
				this->outvars = boost::unordered_map<std::wstring, std::wstring>();
				TCHAR* outputsChar = (TCHAR*) calloc(sizeof(TCHAR), outputs.size() + 1);
				wcscpy_s(outputsChar, outputs.size() + 1, outputs.c_str());
				context = NULL;
				pair = wcstok_s(outputsChar + 1, L", ", &context);
				if (pair != NULL && wcslen(pair) > 0)
				{
					do
					{
						TCHAR* var = (TCHAR*) calloc(sizeof(TCHAR), inputs.size() + outputs.size());
						TCHAR* val = (TCHAR*) calloc(sizeof(TCHAR), inputs.size() + outputs.size());
						swscanf_s(pair, L"%[^ \n:\"] : %[^ \n:\"]", var, inputs.size() + outputs.size(), val, inputs.size() + outputs.size());
						if (wcscmp(var, L"") != 0 && wcscmp(val, L"") != 0)
						{
							std::wstring vars = std::wstring();
							vars.append(var);
							std::wstring vals = std::wstring();
							vals.append(val);
							this->outvars[vars] = vals;
						}
					} while((pair = wcstok_s(NULL, L", ", &context)) != NULL);
				}
				free(inputsChar);
				free(outputsChar);
				free(var);
				free(val);
				free(tmpCode);
			}

			AssemblyNode::~AssemblyNode()
			{
				this->code = L"";
			}

			std::wstring AssemblyNode::To_String()
			{
				std::wstringstream returnable;
				returnable << L"Enter Assembly Node\nCode:";
				returnable << this->code;
				returnable << L"Input Variables:\n";

				boost::unordered_map<std::wstring, std::wstring>::iterator it;
				for(it = this->invars.begin(); it != this->invars.end(); it++) {
					returnable << L"\t" << it->first << L", " << it->second << L"\n";
				}

				returnable << L"Output Variables:\n";
				for(it = this->outvars.begin(); it != this->outvars.end(); it++) {
					returnable << L"\t" << it->first << L", " << it->second << L"\n";
				}

				returnable << L"Leave Assembly Node\n";
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool AssemblyNode::Equals(Node* n)
			{
				AssemblyNode* an;
				try
				{
					an = dynamic_cast<AssemblyNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				if (!an)
				{
					return false;
				}
				if (this->code.compare(an->code) != 0)
				{
					return false;
				}
				else if (this->invars.size() != an->invars.size())
				{
					return false;
				}
				else if (this->outvars.size() != an->outvars.size())
				{
					return false;
				}
				else
				{

					boost::unordered_map<std::wstring, std::wstring>::iterator it;
					for(it = this->invars.begin(); it != this->invars.end(); it++)
					{
						if (an->invars[it->first].compare(it->second) != 0)
						{
							return false;
						}
					}

					for(it = this->outvars.begin(); it != this->outvars.end(); it++)
					{
						if (an->invars[it->first].compare(it->second) != 0)
						{
							return false;
						}
					}
					return true;
				}
			}

			SizeOfNode::SizeOfNode(std::wstring type)
			{
				this->strType = type;
				this->size = std::wstring(L"");
			}

			SizeOfNode::~SizeOfNode()
			{

			}

			std::wstring SizeOfNode::To_String()
			{
				std::wstringstream returnable;
				returnable << L"Enter Size Of Node\nType:\n";
				returnable << this->type->To_String();
				std::wstring returnableChar = returnable.str();
				return returnableChar;
			}

			bool SizeOfNode::Equals(Node* n)
			{
				SizeOfNode* son;
				try
				{
					son = dynamic_cast<SizeOfNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				return (son && this->type->Equals(son->type));
			}

			int SizeOfNode::GetConstValue()
			{
				return wtoi(this->size.c_str());
			}

			/*
			*	StructReferenceNode: Represents a reference through . or -> to a field in a struct.
			*/
			StructReferenceNode::StructReferenceNode(ExprNode* lhs, bool isArrow, std::wstring field)
			{
				if (isArrow)
				{
					this->lhs = new UnaryNode(L"*", lhs);
				}
				else
				{
					this->lhs = lhs;
				}
				this->fieldName = field;
			}

			
			StructReferenceNode::StructReferenceNode(StructReferenceNode* srn)
			{
				this->lhs = srn->lhs;
				this->fieldName = srn->fieldName;
			}
			
			StructReferenceNode::~StructReferenceNode()
			{
				if (this->lhs)
				{
					delete this->lhs;
				}
			}
			
			std::wstring StructReferenceNode::To_String()
			{
				std::wstringstream returnable;
				returnable << L"Enter Struct Reference Node\nLHS:\n";
				returnable << this->lhs->To_String();
				returnable << L"Field:\n";
				returnable << this->fieldName;
				returnable << L"\n";
				return returnable.str();
			}
			
			bool StructReferenceNode::Equals(Node* n)
			{
				StructReferenceNode* srn;
				try
				{
					srn = dynamic_cast<StructReferenceNode*>(n);
				}
				catch(...)
				{
					return false;
				}
				if (!srn)
				{
					return false;
				}
				return (this->fieldName.compare(srn->fieldName) == 0) && (this->lhs->Equals(srn->lhs));
			}
		}
	}
}