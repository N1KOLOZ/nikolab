#include "node.h"


ValueNode::ValueNode(char digit) :
        _value(digit - '0')
{

}

double ValueNode::Evaluate() const {
    return _value;
}

VariableNode::VariableNode(const double &x) :
        _x(x)
{

}

double VariableNode::Evaluate() const {
    return _x;
}

OperationNode::OperationNode(
        Operation op, shared_ptr<Node> lhs, shared_ptr<Node> rhs) :
        _op(op),
        _lhs(lhs),
        _rhs(rhs)
{

}

double OperationNode::Evaluate() const {
    if (_op == Operation::Add) {
        return  _lhs->Evaluate() + _rhs->Evaluate();
    } else if (_op == Operation::Subtract) {
        return  _lhs->Evaluate() - _rhs->Evaluate();
    } else if (_op == Operation::Multiply) {
        return  _lhs->Evaluate() * _rhs->Evaluate();
    }
}
