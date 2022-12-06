/* 4. Optional: The subtraction of functions can have cancellation errors, 
write a function to evaluate exp(x) - exp(y) as exp(x, y) with the help of built in functions 
such as expm1 or sinh.*/

/*
    exp(x)-exp(y)=expm1(x-y).exp(y)
*/


#include <iostream>
#include <cmath>
using namespace std;

void cancellationError()
{
    double  x;
    double  y;
    cout<<"enter x value"<<endl;
    cin>>x;
    cout<<"enter y value"<<endl;
    cin>>y;
    double  lhs=exp(x)-exp(y);
    double  rhs= expm1(x-y)*exp(y);
    cout<<"lhs => "<<lhs<<endl;
    cout<<"rhs => "<<rhs<<endl;
}

int main()
{
    cancellationError();
    return 0;
}

