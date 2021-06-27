# pragma once

# include <iostream>
# include <sstream>      // ostringstream
# include <assert.h>     // assert(false)
# include "symboltab.h"  // map: SymbolTab

enum Operacion {
    SUM = '+',
    SUB = '-',
    MUL = '*',
    DIV = '/'
};

// ===== Node ==============================
class node {
    public:
        node();
        virtual ~node() = default;

        virtual float eval(const SymbolTab& syms) const = 0;
        virtual string to_string() const = 0;
};

// ----- Node_Var --------------------------
class node_var : public node {
    private:
        string var;
    public:
        node_var(const string& _var);

        float eval(const SymbolTab& syms) const override;
        string to_string() const override;
};

// ----- Node_Dato -------------------------
class node_dato : public node {
    private:
        float dato;
    public:
        node_dato(const float& _dato);
        
        float eval(const SymbolTab& syms) const override;
        string to_string() const override;
};

// ===== Node_Operator =====================
class node_operator : public node {
    private:
        char operador;
        node *node1, *node2;
    public:
        node_operator(const char& _operador, node* _node1, node* _node2);
        ~node_operator();

        float eval(const SymbolTab& syms) const override;
        string to_string() const override;
};

// ----- Operator '+' ----------------------
class node_add : public node_operator {
    public:
        node_add(node* _node1, node* _node2);
};

// ----- Operator '-' ----------------------
class node_sub : public node_operator {
    public:
        node_sub(node* _node1, node* _node2);
};

// ----- Operator '*' ----------------------
class node_mul : public node_operator {
    public:
        node_mul(node* _node1, node* _node2);
};

// ----- Operator '/' ----------------------
class node_div : public node_operator {
    public:
        node_div(node* _node1, node* _node2);
};