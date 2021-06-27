# pragma once

# include <stack>
# include "node.h"

class Expression {
	private:
		node* root;	// Raiz del árbol de términos

		void	parse(const string& s);
		string	to_string() const;		// Devuelve la cadena que representa la expresión
		
	public:
		Expression(const string& expr_mat) {
			this->parse(expr_mat);
		}

		// Devuelve el resultado de evaluar la expresión
		float eval(const SymbolTab& syms) const;
		// Redefinición del operador <<
		friend ostream& operator<<(ostream& os, const Expression& e);
};

ostream& operator<<(ostream& os,const Expression& e);
