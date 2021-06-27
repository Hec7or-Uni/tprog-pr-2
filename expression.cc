# include "expression.h"

using namespace std;

void Expression::parse(const string& s) {
	istringstream ss(s);
	string tok;

	// Pila de términos (resultados de operaciones)
	stack<node*> stk;

	// Nodo para apilar el resultado de una operación
	node* rama;

	// Nodos para guardar datos tipo "dato" | "variable"
	node* node1;
	node* node2;

	while (ss >> tok) {
		if (tok == "+" ||  tok == "-" || tok == "*" || tok == "/") {
			node2 = stk.top();
			stk.pop();
			node1 = stk.top();
			stk.pop();

			if 		(tok == "+")	rama = new node_add(node1, node2);
			else if (tok == "-")	rama = new node_sub(node1, node2);
			else if (tok == "*")	rama = new node_mul(node1, node2);
			else if (tok == "/")	rama = new node_div(node1, node2);
		} else {
			if (isalpha(tok[0])) {
				rama = new node_var(tok);
			} else {
				float dato = stof(tok);
				rama = new node_dato(dato);
			}
		}

		stk.push(rama);
	}

	root = stk.top();	// cima de la pila
}

float Expression::eval(const SymbolTab& syms) const {
	return root->eval(syms);
}

string Expression::to_string() const {
	return root->to_string();
}

ostream& operator<<(ostream& os,const Expression& e) {
    os << e.to_string();
    return os;
}

