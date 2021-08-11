
#ifndef EVALUATOR_H
#define EVALUATOR_H


#include <string>
using std::string;

double Evaluate(const string& postfix, bool& error);
bool IsOperator(char mathOp);
float EvaluateStack(char op, float a, float b);
#endif
