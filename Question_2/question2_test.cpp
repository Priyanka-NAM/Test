#include <iostream>
#include "question2.hpp"
using namespace std;

// Complex Number Implementation for Testing
template <class T>
class ComplexNumber
{
public:
    ComplexNumber(): realnumber(0), imaginarynumber(0) {};
    ComplexNumber(T real, T imaginary) : realnumber(real), imaginarynumber(imaginary){};
    // Constructor takes vector of coefficients
    template <class U>
    ComplexNumber(const ComplexNumber<U> &complexnumber)
    {
        this->realnumber = complexnumber.real();
        this->imaginarynumber = complexnumber.imaginary();
    }

    T real() const {
        return realnumber;
    }
    T imaginary() const {
        return imaginarynumber;
    }
    template <typename U>
    auto operator*(const U other) const
    {
        ComplexNumber<decltype(realnumber * other)> temp(realnumber * other,
                                                         imaginarynumber * other);
        return temp;
    }

    template<typename U>
    auto operator *(const ComplexNumber<U>& other) const
    {
        ComplexNumber<decltype(realnumber * other.real())> temp;
        temp.realnumber = realnumber * other.real() -
                          imaginarynumber * other.imaginary();
        temp.imaginarynumber = realnumber * other.imaginary() +
                               imaginarynumber * other.real();
        return temp;
    }

    template<typename U>
    auto operator +(const ComplexNumber<U>& other) 
    {
        ComplexNumber<decltype(realnumber + other.real())> temp(realnumber + other.real(),
                                                                    imaginarynumber + other.imaginary());
        return temp;
    }

    template<typename U>
    bool operator ==(const ComplexNumber<U>& other) 
    {
        return realnumber == other.real() && imaginarynumber == other.imaginary();
    }

    void printComplexNumber() {
        cout<<realnumber << "+" << imaginarynumber << "i" << endl;
    }
private:
    T realnumber;
    T imaginarynumber;
};

int main()
{
    cout<<"1st Test Case => " << endl;
    vector<int> v={1,2,5};
    Polynomial<int> polobj(v);
    EvalPolynomialNonHorner<int> obj1(polobj);
    EvalPolynomialHorner<int> obj2(polobj);
    cout<<"Horner Polynomial Evaluation (int x): " << obj1(2)<<endl;
    cout<<"Naive Polynomial Evaluation (int x): " << obj2(2)<<endl;
    
    if(obj1(2) == obj2(2)) {
        cout << " Passed " << endl;
    } else {
        cout << "Failed " << endl;
    }
    
    cout<<"2nd Test Case => " << endl;
    ComplexNumber<int> cn1(1,2);
    ComplexNumber<int> cn2(1,2);
    vector<ComplexNumber<int>> vec={cn1,cn2};
    Polynomial<ComplexNumber<int>> polobjvec(vec);
    EvalPolynomialHorner<ComplexNumber<int>> newobj1(polobjvec);
    EvalPolynomialNonHorner<ComplexNumber<int>> newobj2(polobjvec);
    cout<<"Horner Polynomial Evaluation (float x): ";
    newobj1(2.2).printComplexNumber();
    cout<<"Naive Polynomial Evaluation (float x): ";
    newobj2(2.2).printComplexNumber();
    if (newobj1(2.2) == newobj2(2.2)) {
        cout << " Passed " << endl;
    } else {
        cout << "Failed " << endl;
    }

    cout<<"3rd Test Case => " << endl;
    EvalPolynomialHorner<ComplexNumber<int>> newcompobj1(polobjvec);
    EvalPolynomialNonHorner<ComplexNumber<int>> newcompobj2(polobjvec);
    cout<<"Horner Polynomial Evaluation (ComplexNumber x): ";
    newcompobj1(cn1).printComplexNumber();
    cout<<"Naive Polynomial Evaluation (ComplexNumber x): ";
    newcompobj2(cn1).printComplexNumber();
    if (newcompobj1(cn1) == newcompobj2(cn1)) {
        cout << " Passed " << endl;
    } else {
        cout << "Failed " << endl;
    }

    return 0;
}