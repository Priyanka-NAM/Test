#include <iostream>
#include <chrono>
#include <vector>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/operation.hpp>
#include "question3.hpp"

/*
    1.For multiplying two 1000 x 1000 matrices, 
       => My implemmentation of matrix multiplication takes ~35 seconds
       => Boost Library implementation also takes similar time of ~35 seconds.
    2. My implementations time complexity is O(n^3) which is same as the Boost internal implementation.
    3. For cache optimization, we can make the second operand as column major which can improve
       performance in both implementation (ijk => ikj in my implementation and prod(A, col_major_B) in Boost)
    4. Also when we used optimization (-O2) flag in the compilation, the runtimes of both reduced to ~8 seconds. 
    5. Another overhead in Boost library would be becasue of the heavy use of matrix expressions and type checking.
    6. We can use Strassen algorithm for matrix multiplication in our implementation which will reduce
       time complexity from O(n^3) and similarly using block_prod from Boost library will give an better performance.
*/

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
        for(int i=0;i<1000;i++) {
            for(int j=0;j<1000;j++) {
                testMatrix1(i, j) = boostMatrix1(i, j) = min + (rand() % (max - min + 1));
                testMatrix2(i, j) = boostMatrix2(i, j) = min + (rand() % (max - min + 1));
            }
        }
        auto selfImplementationTimeStart = std::chrono::high_resolution_clock::now();
        auto resultMatrix = testMatrix1 * testMatrix2;
        auto selfImplementationTimeStop = std::chrono::high_resolution_clock::now();
        cout << "Time taken by own implementation of  Matrix multiplication: "
        << duration_cast<microseconds>(selfImplementationTimeStop - selfImplementationTimeStart).count() 
        << " microseconds" << endl;

        auto boostImplementationTimeStart = std::chrono::high_resolution_clock::now();
        auto boostresultMatrix = prod(boostMatrix1, boostMatrix2);
        auto boostImplementationTimeStop = std::chrono::high_resolution_clock::now();
        cout << "Time taken by Boost Library implementation of  Matrix multiplication: "
        << duration_cast<microseconds>(boostImplementationTimeStop - boostImplementationTimeStart).count() 
        << " microseconds" << endl;

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