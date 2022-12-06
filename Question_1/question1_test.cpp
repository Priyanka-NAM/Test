#include <iostream>
#include <vector>
#include "question1.hpp"

using namespace std;

void testcaseCheck(vector<int> expectedX, vector<int> expectedY,
                   vector<int> actualX, vector<int> actualY) {
    if (expectedX != actualX || expectedY != actualY) {
        cout << "Failed" << endl;
    }
    else {
        cout << "Passed" << endl;
    }
}

int main() {
    // 1st Test case
    cout<< "1st Test case => ";
    vector<int> x={1,2,3,4,5};
    vector<int> y={2,5,3,5,6};
    sort_xy(x,y);
    vector<int> expected_x = {1,2,3,4,5};
    vector<int> expected_y = {2,5,3,5,6};
    testcaseCheck(expected_x, expected_y, x, y);

    // 2nd Test case
    cout<< "2nd Test case => ";
    x={2,2,2,2,2};
    y={2,2,2,2,2};
    sort_xy(x,y);
    expected_x = {2,2,2,2,2};
    expected_y = {2,2,2,2,2};
    testcaseCheck(expected_x, expected_y, x, y);

    // 3rd Test case
    cout<< "3rd Test case => ";
    x={2,2,2,2,2};
    y={6,5,4,3,2};
    sort_xy(x,y);
    expected_x = {2,2,2,2,2};
    expected_y = {2,3,4,5,6};
    testcaseCheck(expected_x, expected_y, x, y);

    // 4th Test case
    cout<< "4th Test case => ";
    x={3,2,1};
    y={6,5,4,3,2};
    try {
        sort_xy(x,y);
    }  catch (std::invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    } 

    // 5th Test case
    cout<< "5th Test case => ";
    x={1,2,3,8,9,5,4,5,5,1,2,7,9,2,6,1,1,4,7,5,2,3,5,4,6};
    y={6,5,4,3,2,7,4,1,8,5,2,6,1,4,7,5,8,4,6,3,1,0,1,7,8};
    sort_xy(x,y);
    expected_x = {1,1,1,1,2,2,2,2,3,3,4,4,4,5,5,5,5,5,6,6,7,7,8,9,9};
    expected_y = {5,5,6,8,1,2,4,5,0,4,4,4,7,1,1,3,7,8,7,8,6,6,3,1,2};
    testcaseCheck(expected_x, expected_y, x, y);
    return 0;
}