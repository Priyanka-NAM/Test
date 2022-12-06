#include <iostream>
#include <vector>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/operation.hpp>
#include "question3.hpp"

using namespace std;

int main()
{

    cout << "1st Test Case => " << endl;
    try {
        Matrix<int> a({{1,2},{2,3}});
        Matrix<int> b({{3,2},{2,2}});
        Matrix<int> c = a * b;
        c.printVector();
        cout<<"Value of Operator overload : "<<a(0,1)<<endl;
        cout<<"Get Size of Matrix : "<<c.getSize().first<<"   "<<c.getSize().second<<endl;
        Matrix<double> d({{1.1,0.2},{0.0,1.2}});
        Matrix<int> e({{0,2},{2,2}});
        auto f = d * e;
        f.printVector();
    } catch (std::invalid_argument& e) {
        cerr << e.what() << endl;
        return -1;
    }

    cout << "2nd  Test Case => " << endl;
    try {
        Matrix<int> testMatrix1(1000, 1000);
        Matrix<int> testMatrix2(1000, 1000);
        
        boost::numeric::ublas::matrix<int> boostMatrix1(1000, 1000);
        boost::numeric::ublas::matrix<int> boostMatrix2(1000, 1000);

        srand(time(0));
        int min=0;
        int max=1000;
        for(int i=0;i<1000;i++)
        {
        for(int j=0;j<1000;j++)
        {
            testMatrix1(i, j) = boostMatrix1(i, j) = min + (rand() % (max - min + 1));
            testMatrix2(i, j) = boostMatrix2(i, j) = min + (rand() % (max - min + 1));
        }
        }
        auto resultMatrix = testMatrix1 * testMatrix2;
        auto boostresultMatrix = prod(boostMatrix1, boostMatrix2);

        for(int i=0; i<1000; i++) {
            for(int j=0; j<1000; j++) {
                if(boostresultMatrix(i, j) != resultMatrix(i, j))
                    cout << "Matrix Multiplication Failed " << endl;
            }
        }
    }  catch (std::invalid_argument& e) {
      cerr << e.what() << endl;
      return -1;
    }
  return 0;
}