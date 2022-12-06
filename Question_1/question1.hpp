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
bool comparatorAscending(const pair<int, int> &a, const pair<int, int> &b) {
    // check if the first element is same, if it is same then it sorts 
    // based on second element.
    if (a.first == b.first)
        return a.second < b.second;
    // if first element is different then it sort based on first element
    // in ascending order.
    return a.first < b.first;
}

void sort_xy( vector<int>& x,  vector<int>& y) {
    
// Checking whether the size of the vectors is same or not.
// If the sizes are different throw an error.
    if(x.size()!=y.size()) {
        throw std::invalid_argument("Vector sizes are different");
    }
    vector<pair<int,int>> newV;

// Making  x & y vectors as vector of pairs
    for(int i=0;i<x.size();i++) {
        newV.push_back({x[i],y[i]});
    }

// Sorting elements in vectors W.R.T "x" values in ascending order.
    sort(newV.begin(),newV.end(),comparatorAscending);

// adding values back into x & y vectors.
    for(int i=0;i<newV.size();i++) {
        x[i]=newV[i].first;
        y[i]=newV[i].second;
    }

    return;
}