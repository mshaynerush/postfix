#include "evaluator.h"
#include <iostream>
#include <stack>
#include <queue>
#include <math.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <ctype.h>
using std::stack;
using std::cout;

double Evaluate(const string& postfix, bool& error) {
    stack<float> park;
    float a = 0;
    float b = 0;
    float c = 0;
    float d = 0.0;
    double res;
    string num = "";
    char op;
    error = false;
    for (auto i: postfix) {
        if (i == ' ') {//if current item is a space either go to next i or if the number has digits, push to stack
            if(num.size() > 0){ //when the codes reaches a space, push number to stack and advance iterator
                d = stof(num); // convert string to a float when inserting into the stack
                park.push(d);
                num.clear(); // reset number to null;
            }
            i++;
        }
        if (isdigit(i)) {//if this item is a digit, append the string with current char
            num += i;
        }
        if(i == '.'){//if this is a dot, this is a decimal number. add the next concurrent numbers to the string
            num += '.';
        }

        if(isalpha(i)){// anything other than a space, operator or number will make an error
            error = true;
            return - 1.0;
        }
        if (IsOperator(i)) { //check to see if this is an operator and if so, pull two numbers from the stack and evaluate based on the current operator
            if (park.size() < 2) {
                error = true;
                return -1.0;
            }
            op = i; //set operator
            a = park.top();
            park.pop();
            b = park.top();
            park.pop();
            c = EvaluateStack(op, a, b); // send operator, and both numbers to Evaluate
            park.push(c);
        }
    }
    res = park.top(); // get result as the last item placed into stack and empty stack
    park.pop();
    return res;
}

bool IsOperator(char mathOp){
    if(mathOp == '+' || mathOp == '-' || mathOp == '*' || mathOp == '/' || mathOp == '^'){ // will return true if this char passed is any of these operators
        return true;
    } else {
        return false;
    }
}

float EvaluateStack(char op, float a, float b){ //based on operator type, do operation with care to order of operations for division, subtraction and powers.
    float c = 0;
    if(op == '+'){
        c = a + b;
    } else if (op == '-') {
        c = b - a;
    } else if(op == '/'){
        c = b / a;
    } else if (op =='*'){
        c = a * b;
    } else if (op =='^'){
        c = pow(b, a);
    }
    return c;
}