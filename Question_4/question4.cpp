/* 4. Optional: The subtraction of functions can have cancellation errors, 
write a function to evaluate exp(x) - exp(y) as exp(x, y) with the help of built in functions 
such as expm1 or sinh.*/

/*
    To avoid the cancellation error in subtraction, we are evaluating
    the expression exp(x)-exp(y) using built-in expm1 as follows:
        exp(x) - exp(y) = expm1(x-y) * exp(y)
*/


#include <iostream>
#include <cmath>
using namespace std;

void EvaluateExp(double x, double y)
{
    double  lhs=exp(x)-exp(y);
    double  rhs= expm1(x-y)*exp(y);
    cout<<"exp(x) - exp(y) = "<<lhs<<endl;
    cout<<"expm1(x-y)*exp(y) => "<<rhs<<endl;
}

int main()
{
    cout << "1st Test Case => " << endl;
    EvaluateExp(1.00000000001, 1.00000000002);

    cout << "2nd Test Case => " << endl;
    EvaluateExp(0, 0.000001);

    cout << "3rd Test Case => " << endl;
    EvaluateExp(0, 0);

    cout << "4th Test Case => " << endl;
    EvaluateExp(2, 3);

    return 0;
}

