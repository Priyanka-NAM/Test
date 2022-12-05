
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
    int siz;
    vector<T> coeffi;
    public:
        Polynomial(){}
        Polynomial(int siz);
        Polynomial(const Polynomial& poly);
        Polynomial(vector<T>& coefficient);
        int getSize()
        {
            return siz;
        }
        T operator[] (int index);
};

// Constructor takes vector of coefficients 
template <class T>
Polynomial<T>::Polynomial(vector<T>& coefficient)
{
    this->coeffi=coefficient;
    this->siz=coefficient.size();
}

// Constructor takes size as argument 
template <class T>
Polynomial<T>::Polynomial(int siz)
{
    this->siz=siz;
    coeffi.resize(siz);
}

//Operator [] overloading to access the elements of the coefficients based on index.
template <class T>
T Polynomial<T>::operator[] (int index)
{
    if(index>=this->siz)
        throw std::invalid_argument("Index out of range");
    return this->coeffi[index];
}

//Copy Constructor
template <class T>
Polynomial<T>::Polynomial(const Polynomial& poly)
{
    this->siz=poly.siz;
    this->coeffi=poly.coeffi;
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
            auto result=polyfun[0];
            for(int i=1;i<polyfun.getSize();i++)
            {
                U tmp=1;
                for(int j=0;j<i;j++)
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
            auto result=polyfun[polyfun.getSize()-1];
            for(int i=polyfun.getSize()-2;i>=0;i--)
            {
                result = result*x + polyfun[i];
            }
            return result;
        }

};

template <class T>
class ComplexNumber
{
public:
    ComplexNumber();
    ComplexNumber(T real , T imaginary);
    template<typename U>
    ComplexNumber<T> operator *(const U other) const
    {
        ComplexNumber<T> temp;
        temp.realnumber = realnumber * other;
        temp.imaginarynumber = imaginarynumber * other;
        return temp;
    }
    
    ComplexNumber<T> operator +(const ComplexNumber<T>& other) 
    {
        ComplexNumber<T> temp;
        temp.realnumber = realnumber + other.realnumber;
        temp.imaginarynumber = imaginarynumber + other.imaginarynumber;
        return temp;
    }
    void printComplexNumber()
    {
        cout<<realnumber;
        cout<<"+";
        cout<<imaginarynumber;
        cout<<"i";
    }
private:
    T realnumber;
    T imaginarynumber;
};

template<class T>
ComplexNumber<T>::ComplexNumber()
{
    realnumber = 0.0;
    imaginarynumber = 0.0;
}

template<class T>
ComplexNumber<T>::ComplexNumber(const T real,const T imaginary)
{
    realnumber = real;
    imaginarynumber = imaginary;
}

int main()
{
    vector<int> v={1,2,5};
    Polynomial<int> polobj(v);
    EvalPolynomialNonHorner<int> obj1(polobj);
    EvalPolynomialHorner<int> obj2(polobj);
    cout<<obj1(2)<<endl;
    cout<<obj2(2)<<endl;
    cout<<"Complied Successfully"<<endl;
    ComplexNumber<int> cn1(1,2);
    ComplexNumber<int> cn2(1,2);
    vector<ComplexNumber<int>> vec={cn1,cn2};
    Polynomial<ComplexNumber<int>> polobjvec(vec);
    EvalPolynomialHorner<ComplexNumber<int>> newobj1(polobjvec);
    auto result=newobj1(2.2);
    result.printComplexNumber();
    cout<<"Ended Successfully"<<endl;
    return 0;
}