
#include <iostream>
#include <vector>
using namespace std;
/*
2.  Write a templated class/struct to hold polynomial coefficients which can be float, double,
     or complex numbers, with the following properties:

    a. User can access the elements of the coefficients based on index.

    b. Provide a functor to evaluate the polynomial as p(x), 
    where the argument x should be templated (independent of the coefficients) since it can be float, double or complex types.

    You should try two approaches and one of which must be based on the Horner algorithm, and explain why it is preferred.

      Since the evaluation does not alter the coefficients, the functor should observe constant correctness.
*/

//Class for Polynomial
template <class T>
class Polynomial 
{
    unsigned size;
    vector<T> coefficients;
    public:
        Polynomial(){}
        Polynomial(unsigned size);
        Polynomial(const Polynomial& poly);
        Polynomial(vector<T>& coefficient);
        unsigned getSize();
        T operator[] (unsigned index);
};

// Constructor takes vector of coefficients
template <class T>
Polynomial<T>::Polynomial(vector<T> &coefficients) : 
    size(coefficients.size()), coefficients(coefficients) {}

// Constructor takes size as argument 
template <class T>
Polynomial<T>::Polynomial(unsigned size): size(size) {
    coefficients.resize(size);
}

//Operator [] overloading to access the elements of the coefficients based on index.
template <class T>
T Polynomial<T>::operator[] (unsigned index) {
    if(index>=this->size)
        throw std::invalid_argument("Index out of range");
    return this->coefficients[index];
}

//Copy Constructor
template <class T>
Polynomial<T>::Polynomial(const Polynomial& poly) {
    this->size=poly.size;
    this->coefficients=poly.coefficients;
}

// Returns the total number of coefficients.
template <class T>
unsigned Polynomial<T>::getSize() {
            return size;
}


// Functor without Horner algorithm
template <class T>
class EvalPolynomialNonHorner
{
    int x;
    Polynomial<T> polyfun;
    public:
        EvalPolynomialNonHorner();
        EvalPolynomialNonHorner(Polynomial<T>& poly)
        {
             this->polyfun=poly;
        }
        
        //To Evaluate the polynomial as p(x)
        template <class U>
        auto operator() (U x)
        {
            if(polyfun.getSize()==0)
                throw std::invalid_argument("polyfun size is 0"); 
            decltype(polyfun[0]*x) result = polyfun[0];
            for(int i=1;i<polyfun.getSize();i++)
            {
                U tmp=x;
                for(int j=1;j<i;j++)
                    tmp=tmp*x;
                result=result+polyfun[i]*tmp;
            }
            return result;
        }

};


// Functor with Horner algorithm
template <class T>
class EvalPolynomialHorner
{
    Polynomial<T> polyfun;
    public:
        EvalPolynomialHorner();
        EvalPolynomialHorner(Polynomial<T>& poly)
        {
             this->polyfun=poly;
        }
        //To Evaluate the polynomial as p(x)
        template <class U>
        auto operator() (U x)
        {
            if(polyfun.getSize()==0)
                throw std::invalid_argument("polyfun size is 0"); 
            decltype(polyfun[0]*x) result = polyfun[polyfun.getSize()-1];
            for(int i=polyfun.getSize()-2;i>=0;i--)
            {
                result = result*x + polyfun[i];
            }
            return result;
        }

};

