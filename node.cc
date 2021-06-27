# include "node.h"

using namespace std;

// ===== Node ==============================
node::node()
{}

// ----- Node_Var --------------------------
node_var::node_var(const string& _var) 
    : var(_var)
{}

float node_var::eval(const SymbolTab& syms) const {
    try {
        if (syms.count(var) == 1) {
            auto map = syms.find(var);
            return map->second;
        } else {
            throw (syms);
        }
    } catch(const SymbolTab& ex) {
        cout << "ERROR!!! \'" + var + "\' no esta definida\n";
        exit(0);
    }
}

string node_var::to_string() const {
    return var;
}

// ----- Node_Dato -------------------------
node_dato::node_dato(const float& _dato) 
    : dato(_dato)
{}

float node_dato::eval(const SymbolTab& syms) const {
    return dato;
}

string node_dato::to_string() const {
    ostringstream buffer;
    buffer << dato;
    return buffer.str();
}

// ===== Node_Operator =====================
node_operator::node_operator(const char& _operador, node* _node1, node* _node2)
    : operador(_operador), node1(_node1), node2(_node2)
{}

node_operator::~node_operator() {
    delete node1;
    delete node2;
}

float node_operator::eval(const SymbolTab& syms) const {
    switch (operador) {
        case SUM:   return node1->eval(syms) + node2->eval(syms);
        case SUB:   return node1->eval(syms) - node2->eval(syms);
        case MUL:   return node1->eval(syms) * node2->eval(syms);
        case DIV:   return node1->eval(syms) / node2->eval(syms);
    }
    assert(false);
}

string node_operator::to_string() const {
    return (operador == SUM || operador == SUB) ? '(' + node1->to_string() + operador + node2->to_string() + ')' : node1->to_string() + operador + node2->to_string();
}

// ----- Operator '+' ----------------------
node_add::node_add(node* _node1, node* _node2)
    : node_operator(SUM, _node1, _node2)
{}

// ----- Operator '-' ----------------------
node_sub::node_sub(node* _node1, node* _node2)
    : node_operator(SUB, _node1, _node2)
{}

// ----- Operator '*' ----------------------
node_mul::node_mul(node* _node1, node* _node2)
    : node_operator(MUL, _node1, _node2)
{}

// ----- Operator '/' ----------------------
node_div::node_div(node* _node1, node* _node2)
    : node_operator(DIV, _node1, _node2)
{}