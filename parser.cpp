//***
// TODO 1) Add parser for parentheses
//      2) Add parser for sin
//***

#include "parser.h"
#include "token.h"

#include <string> //stod
#include <stack>
#include <queue>
#include <map>
#include <stdexcept>

// for debug
#include <iostream>

using namespace std;

Op GetOp(const string& value) {
    if (value == "+") {
        return Op::Add;
    } else if (value == "-") {
        return Op::Subtract;
    } else if (value == "*") {
        return Op::Multiply;
    } else if (value == "/") {
        return Op::Divide;
    } else if (value == "^") {
        return Op::Exponentiate;
    }
}

// Converts infix notation to reverse Polish notation
// by means of shunting-yard algorithm
template <typename It>
shared_ptr<Node> ParseExpression(It& current, It end, const double& x) {
    if (current == end) {
        return shared_ptr<EmptyNode>();
    }

    stack<shared_ptr<Node>> values;
    stack<shared_ptr<OperationNode>> ops;

    auto PopOps = [&values, &ops](unsigned precedence) {
        while(!ops.empty() && precedence <= ops.top()->precedence) {

            if (values.size() < 2 || ops.empty()) {
                throw logic_error("Invalid expression");
            }

            auto value_rhs = values.top();
            values.pop();
            auto value_lhs = values.top();
            values.pop();
            auto top_op_node = ops.top();
            ops.pop();

            top_op_node->set_lhs(value_lhs);
            top_op_node->set_rhs(value_rhs);

            values.push(top_op_node);
        }

    };

    while (current != end) {
        if (current->type == TokenType::VALUE) {
            values.push(make_shared<ValueNode>(stod(current->value)));
        }

        if (current->type == TokenType::VARIABLE) {
            values.push(make_shared<VariableNode>(x));
        }

        if (current->type == TokenType::OP) {
            auto new_op_node = make_shared<OperationNode>(GetOp(current->value));
            PopOps(new_op_node->precedence);

            ops.push(new_op_node);
        }
        ++current;
    }

    PopOps(0);

    if (values.size() != 1 || ops.size() != 0) {
        throw logic_error("Invalid expression");
    }

    return values.top();
}

shared_ptr<Node> Parse(istream &is, const double& x) {
    auto tokens = Tokenize(is);

    auto current = tokens.begin();
    auto top_node = ParseExpression(current, tokens.end(), x);

    return top_node;
}
