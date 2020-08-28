#pragma once

#include <cstdint>
#include <memory>

using namespace std;

struct Node {
    virtual double Evaluate() const = 0;
};

struct ValueNode : public Node {
    ValueNode(char digit);

    double Evaluate() const override;

private:
    const int64_t _value;
};

struct VariableNode : public Node {
    VariableNode(const double &x);

    double Evaluate() const override;

private:
    const double &_x;
};

enum class Operation {
    Add,
    Subtract,
    Multiply,
};

class OperationNode : public Node {
public:
    OperationNode(
            Operation op, shared_ptr<Node> lhs, shared_ptr<Node> rhs);

    double Evaluate() const override;

private:
    Operation _op;
    shared_ptr<const Node> _lhs, _rhs;

};