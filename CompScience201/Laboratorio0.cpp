// Ashley Ogamaba
// Program 1 -- Numbers
// Prompts user for 4 numbers, prints max, min, average, ascending, descending

#include <iostream>
#include <cstdlib>
using namespace std;

int main() {


   


    int num1, num2, num3, num4;
    cout << "Please input four numbers: ";
    cin >> num1 >> num2 >> num3 >> num4;

    int* array = (int*)malloc(4 * sizeof(int));
    if (array == NULL) {
        cout << "Failure to allocate memory" << endl;
        return 1;
    }

    array[0] = num1;
    array[1] = num2;
    array[2] = num3;
    array[3] = num4;

    int min = array[0], max = array[0], sum = 0;
    for (int i = 0; i < 4; i++) {
        if (array[i] < min) min = array[i];
        if (array[i] > max) max = array[i];
        sum += array[i];
    }

    int average = sum / 4;

    // Bubble sort
    int temp;
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3 - j; i++) {
            if (array[i] > array[i + 1]) {
                temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
    }

    cout << "The largest number is " << max << "." << endl;
    cout << "The smallest number is " << min << "." << endl;
    cout << "The average is " << average << "." << endl;

    cout << "Numbers in increasing order: ";
    for (int i = 0; i < 4; i++) {
        cout << array[i];
        if (i < 3) cout << ", ";
    }
    cout << "." << endl;

    cout << "Numbers in decreasing order: ";
    for (int i = 3; i >= 0; i--) {
        cout << array[i];
        if (i > 0) cout << ", ";
    }
    cout << "." << endl;


    

    free(array);
    return 0;
}
