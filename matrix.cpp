#include <iostream>
#include <vector>
using namespace std;

/*
3. Design a simple matrix class with templated types, and general dimensions M x N
   a. Provide operators to access the elements.
   b. Provide a multiplication operator so one may be able to carry out matrix multiplications 
   as C = A * B. The types of A and B should have independent templated types, 
   and the returned matrix C should have the correct type.
   c. Test the correctness with data generated with standard library's random number generators by 
   comparing it with boost or eigen library. Compare the performance with a large matrix, 
   say of 1000 x 1000.

      Try to explain why the performance might be good or bad. 
*/

template<typename T> 
class Matrix;
template <typename U,typename Z>
auto operator* (const Matrix<U>& A, const Matrix<Z>& B);

template <class T>
class Matrix {
  private:
    int M;
    int N;
    vector<vector<T>> valVector;
  public:
    Matrix(int M,int N);
    Matrix(const vector<vector<T>>& V);
    
    template <typename U,typename Z>
    friend  auto operator* (const Matrix<U>& A, const Matrix<Z>& B);
    T operator() (int i,int j);
    void printVector();
    pair<int,int> getSize();
};

template <class T> 
Matrix<T>:: Matrix(int M,int N)
{   
  this->M=M;
  this->N=N;
}
template <class T> 
Matrix<T>:: Matrix(const vector<vector<T>>& V)
{   
  if(V.size()==0)
    return;
  int s=V[0].size();
  for(auto each:V)
  {
    if(each.size()!=s)
      throw std::invalid_argument("Matrix size is not valid");
  }
  this->M=V.size();
  this->N=V[0].size();
  this->valVector=V;

}

template <typename T, typename Z>
auto operator* (const Matrix<T>& A, const Matrix<Z>& B)
{   
  if(A.N!=B.M)
    throw std::invalid_argument("Matrix Multiplication is Not Possible");
  Matrix<decltype(A.valVector[0][0] * B.valVector[0][0])> newVal(A.M,B.N);
  newVal.valVector.resize(A.M,vector<decltype(A.valVector[0][0] * B.valVector[0][0])>(B.N,0));
  for(int i=0;i<A.M;i++)
  {
    for(int j=0;j<B.N;j++)
    {
      for(int k=0; k<A.N; k++)
        newVal.valVector[i][j]+=A.valVector[i][k]*B.valVector[k][j];
    }
  }
  
  return newVal;
}

template <class T> 
void Matrix<T>::printVector()
{
  for(int i=0;i<valVector.size();i++)
  {
    for(int j=0;j<valVector[0].size();j++)
    {
        cout<<valVector[i][j]<<" ";
    }
    cout<<endl;
  }
}

template <class T>
T Matrix<T>::operator() (int i,int j)
{
    if(i< valVector.size() && j< valVector[0].size())
        return this->valVector[i][j];
    else
      throw std::invalid_argument("i & j not accessable");
}

template <class T>
pair<int,int> Matrix<T>::getSize()
{
    return {this->M,this->N};
}

int main()
{
  try
  {
    // Matrix<int> a({{1,2},{2,3}});
    // Matrix<int> b({{3,2},{2,2}});
    // Matrix<int> c = a * b;
    // c.printVector();
    // cout<<"Value of Operator overload : "<<a(0,1)<<endl;
    // cout<<"Get Size of Matrix : "<<c.getSize().first<<"   "<<c.getSize().second<<endl;
    // Matrix<double> d({{1.1,0.2},{0.0,1.2}});
    // Matrix<int> e({{0,2},{2,2}});
    // auto f = d * e;
    // f.printVector();
    vector<vector<int>> vec1(1000,vector<int>(1000,0));
    vector<vector<int>> vec2(1000,vector<int>(1000,0));
    srand(time(0));
    int min=0;
    int max=1000;
    for(int i=0;i<1000;i++)
    {
      for(int j=0;j<1000;j++)
      {
          vec1[i][j]= min + (rand() % (max - min + 1));
          vec2[i][j]= min + (rand() % (max - min + 1));
      }
    }
    Matrix<int> testMatrix1(vec1);
    Matrix<int> testMatrix2(vec2);
    Matrix<int> resultMatrix = testMatrix1 * testMatrix2;
    resultMatrix.printVector();
  }
  catch (std::invalid_argument& e)
  {
      cerr << e.what() << endl;
      return -1;
  }
  return 0;
}