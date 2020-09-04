#include "node.h"

#include <cmath>

double EmptyNode::Evaluate() const {
    return 0;
}

ValueNode::ValueNode(double value) :
        _value(value)
{

}

double ValueNode::Evaluate() const {
    return _value;
}

VariableNode::VariableNode(const double& x) :
        _x(x)
{

}

double VariableNode::Evaluate() const {
    return _x;
}

unsigned OperationNode::GetPrecedence(Op op) {
    map<Op, unsigned> op_to_precedence = { {Op::Add,          2},
                                           {Op::Subtract,     2},
                                           {Op::Multiply,     3},
                                           {Op::Divide,       3},
                                           {Op::Exponentiate, 4},
    };

    return op_to_precedence[op];
}

OperationNode::OperationNode(Op op) :
        precedence(GetPrecedence(op)),
        _op(op)
{

}

OperationNode::OperationNode(
        Op op, shared_ptr<Node> lhs, shared_ptr<Node> rhs) :
        precedence(GetPrecedence(op)),
        _op(op),
        _lhs(lhs),
        _rhs(rhs)
{

}

void OperationNode::set_lhs(shared_ptr<Node> lhs) {
    _lhs = lhs;
}

void OperationNode::set_rhs(shared_ptr<Node> rhs) {
    _rhs = rhs;
}

double OperationNode::Evaluate() const {
    if (_op == Op::Add) {
        return  _lhs->Evaluate() + _rhs->Evaluate();
    } else if (_op == Op::Subtract) {
        return  _lhs->Evaluate() - _rhs->Evaluate();
    } else if (_op == Op::Multiply) {
        return  _lhs->Evaluate() * _rhs->Evaluate();
    } else if (_op == Op::Divide) {
        return _lhs->Evaluate() / _rhs->Evaluate();
    } else if (_op == Op::Exponentiate) {
        return pow(_lhs->Evaluate(), _rhs->Evaluate());
    }
}