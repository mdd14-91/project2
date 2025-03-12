#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// Function prototypes
// 

//reverse array function
 //Function description-function takes array and # of elements in array then dynamically creates a new array of same size.
 // copies elements in reverse order from original array and returns a pointer to the new array. If invalid data is there
 //then it terminates the program with appropriate error message.
 //Inputs=constant integer array and size=number of elements in array
 //Outputs=pointer to the new array that was made in reverse order
 //Preconditions=size>0
 //Post condition=Returns pointer to the new array that is the reverse order of the original 
int* ReverseArray(int const arr[], int size);


//Void Print function 
//description-iterates through a for loop based on # of elements in array printing out each element based on array size
//inputs= integer constant array or a fixed array only made of integers
//inputs cont= also integer size of array or the number of elements in the array
//output=print array to screen
//preconditions= size>0
//post conditions= prints out array to screen
void print(int const arr[], int size);

//Main Function
//Program generates initial array then reverses it and displays both the original and reverse to the screen
//with appropriate labeling and punctuation. The original is displayed above the reversed array. deallocates memory
//before terminating after successfully running the reverse array function. Or terminates with error message if 
//the array size or output is incorrect.
int main()
{
    // Initialize size for # of elements and array
    int originalArray[] = { 0,2, 4, 6, 8, 20, 1, 3, 5, 7, 9, 30 };
    int size = sizeof(originalArray) / sizeof(originalArray[0]); // Takes number of elements in array

    // Print the original array
    cout << "Original array: " << endl;
    print(originalArray, size);

    // Reverse the original array order and returns pointer to new array
    int* reversedArray = ReverseArray(originalArray, size);

    // Print output of reversed array
    cout << "Reversed Array: " << endl;
    print(reversedArray, size);

    // Deallocate memory for reversed array 
    free(reversedArray);

    return 0;
}

// Function definitions


int* ReverseArray(int const arr[], int size) {
    // Allocate memory for new array
    int* RevArray = (int*)malloc(size * sizeof(int)); // Stores output as integer pointer 

    if (RevArray == 0) {
        cout << "Memory allocation failed" << endl; // Send message and exit program if memory allocation failed
        exit(1);
    }
    if (size <= 1) {
        cout << "You need more than 1 element to reverse it" << endl; //terminates if you only have 1 element or less
        exit(1);
    }

    // Copy elements in reverse order
    for (int i = 0; i < size; i++) {
        RevArray[i] = arr[size - 1 - i];
    }

    return RevArray;
} // Reverse array function returned

void print(int const arr[], int size) {
    // Print function
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl; // Create new line after list is printed
}
