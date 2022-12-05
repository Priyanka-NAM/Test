#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/*
    1. For an array of data pairs (x_i, y_i) the x and y values are stored in separate vectors, 
    write a function to sort the data based on x values only so that the user can use it as
    sort_xy(x,y); // arguments are vectors. Use standard library’ sort function.
    This is needed for plotting if the points are not sorted.
*/
bool comparatorAscending(pair<int,int>& a,pair<int,int>& b)
{
    //check if the first element is same, if it is same then it sorts based on second element.
    if(a.first==b.first)
        return a.second<b.second;
    // if first element is different then it sort based on first element in ascending order.
    return a.first<b.first;
}

void sort_xy( vector<int>& x,  vector<int>& y)
{
    
// Checking whether the size of the vectors is same or not
    if(x.size()!=y.size())
        return;
    vector<pair<int,int>> newV;

// Making  x & y vectors as vector of pairs
    for(int i=0;i<x.size();i++)
    {
        newV.push_back({x[i],y[i]});
    }

// Sorting elements in vectors W.R.T "x" values in ascending order.
    sort(newV.begin(),newV.end(),comparatorAscending);

// adding values back into x & y vectors.
    for(int i=0;i<newV.size();i++)
    {
        x[i]=newV[i].first;
        y[i]=newV[i].second;
    }

    return;
}

int main()
{
// 1st Test case
cout<< "1st Test case"<<endl;
    vector<int> x={1,2,3,4,5};
    vector<int> y={2,5,3,5,6};
    sort_xy(x,y);
    for(int i=0;i<x.size();i++)
    {
        cout<<x[i]<<" "<<y[i]<<endl;
    }
// 2nd Test case
cout<< "2nd Test case"<<endl;
    x={2,2,2,2,2};
    y={2,2,2,2,2};
    sort_xy(x,y);
   for(int i=0;i<x.size();i++)
    {
        cout<<x[i]<<" "<<y[i]<<endl;
    }
// 3rd Test case
cout<< "3rd Test case"<<endl;
    x={2,2,2,2,2};
    y={6,5,4,3,2};
    sort_xy(x,y);
    for(int i=0;i<x.size();i++)
    {
        cout<<x[i]<<" "<<y[i]<<endl;
    }
// 4th Test case
cout<< "4th Test case"<<endl;
    x={1,2,3};
    y={6,5,4,3,2};
    sort_xy(x,y);
 
    for(int i=0;i<x.size();i++)
    {
        cout<<x[i]<<" "<<y[i]<<endl;
    }
// 5th Test case
cout<< "5th Test case"<<endl;
    x={1,2,3,8,9,5,4,5,5,1,2,7,9,2,6,1,1,4,7,5,2,3,5,4,6};
    y={6,5,4,3,2,7,4,1,8,5,2,6,1,4,7,5,8,4,6,3,1,0,1,7,8};
    sort_xy(x,y);
    for(int i=0;i<x.size();i++)
    {
        cout<<x[i]<<" "<<y[i]<<endl;
    }
    cout<<"Priyanka"<<endl;
    return 0;
}