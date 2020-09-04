#pragma once

#include <cstdint>
#include <memory>
#include <map>

using namespace std;

struct Node {
    virtual double Evaluate() const = 0;
};

struct EmptyNode : public Node {
    double Evaluate() const override;
};

struct ValueNode : public Node {
    explicit ValueNode(double value);

    double Evaluate() const override;

private:
    const double _value;
};

struct VariableNode : public Node {
    explicit VariableNode(const double& x);

    double Evaluate() const override;

private:
    const double& _x;
};

enum class Op {
    Add,
    Subtract,
    Multiply,
    Divide,
    Exponentiate,
};

class OperationNode : public Node {
public:
    static unsigned GetPrecedence(Op op);

    explicit OperationNode(Op op);

    OperationNode(
            Op op, shared_ptr<Node> lhs, shared_ptr<Node> rhs);

    void set_lhs(shared_ptr<Node> lhs);
    void set_rhs(shared_ptr<Node> rhs);

    double Evaluate() const override;

    const unsigned precedence;

private:
    Op _op;
    shared_ptr<const Node> _lhs, _rhs;
};