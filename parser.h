#pragma once

#include "node.h"

#include <memory>
#include <istream>

using namespace std;

shared_ptr<Node> Parse(istream& is, const double& x);