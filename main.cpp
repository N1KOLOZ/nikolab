#include "parser.h"
#include "token.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

int main() {
    istringstream is("x*x + 4.234 / 3.2342");
    double x = 2;

    shared_ptr<Node> expr;
    try {
        expr = Parse(is, x);
    } catch (...) {
        cerr << "Invalid mathematical expression" << endl;
    }

    cout << "Result: " << expr->Evaluate();

    return 0;
}