//This program creates a max heap either through a keyboard or through a file input
//Author: Mark Daniloff
//3/4/2020
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace std;

//Function declarations
void manualinput();
void fileinput();
void parse(char* input, int* token, int* heaparr, int num, int count, int total, int exp, int j);
void heapify(int* arr, int n, int i);
void buildHeap(int* arr, int n);
void printHeap(int* arr, int* outputarr, int n, int o, int h);
void displayVisual(int* arr, int n);

int main() {
  //Initialize variables
  bool running = true;
  char input1[10];
  char input2[10];
  //Ask user for input
  cout << "Enter H to create a max heap, or Q to quit" << endl;
  cin.get(input1, 10);
  cin.ignore();
  //Heap
  if (strcmp(input1, "H")==0) {
    //Ask user for input
    cout << "Enter 1 to input manually, or 2 to input through a file" << endl;
    cin.get(input2, 10);
    cin.ignore();
    //Manual
    if (strcmp(input2, "1")==0) {
      manualinput();
    }
    //File
    else if (strcmp(input2, "2")==0) {
      fileinput();
    }
    //Quit
    else if (strcmp(input1, "Q")==0) {
      running = false;
    }
  }
}

//Get input from keyboard
void manualinput() {
  char input[100];
  int token[100];
  int ftoken[100];
  cout << "Enter a series of numbers separated by spaces" << endl;
  cin.get(input, 100);
  cin.ignore();
  int count = 0;
  int total = 0;
  int num = 0;
  int exp = 0;
  int j = 0;
  //Parse the input
  parse(input, token, ftoken, num, count, total, exp, j);
}

//Get input from file
void fileinput() {
  //Initialize variables
  char input[100];
  int token[100];
  int ftoken[100];
  int count = 0;
  int total = 0;
  int num = 0;
  int exp = 0;
  int j = 1;
  //Ask user for filename
  char filename[100];
  cout << "Enter the name of the file " << endl;
  cin.get(filename, 100);
  cin.ignore();
  //This code is from Stefan Ene, period 3, who in turn got it from Omar Nassar. This code reads in a file
  streampos size;
  //in opens the file, binary makes sure new line characters aren't translated,
  //and ate means that the output position starts at the end of the file
  ifstream file(filename, ios::in | ios::binary | ios::ate);
  //If the file exists
  if (file.is_open()) {
    //Get input position
    size = file.tellg();
    //Seek to 0 characters from the beginning of the file
    file.seekg(0, ios::beg);
    //Read the file and assign to input
    file.read(input, size);
    //Close the file
    file.close();
    //Parse the input
    parse(input, token, ftoken, num, count, total, exp, j);    
  }
  //If the file can't be opened
  else {
    cout << "The file can't be opened" << endl;
  }  
}

//Parse the input into an int array
void parse(char* input, int* token, int* heaparr, int num, int count, int total, int exp, int j) {
  int o = 0;
  int h = 1;
  int outputarr[100];
  //Set the  arrays to all zeros
  for (int i = 0; i < 100; i++) {
    heaparr[i] = 0;
    outputarr[i] = 0;
    token[i] = 0;
  }
  for (int i = 0; i < 100; i++) {
    //Null character
    if (input[i] == '\0') {
      i = 100;
    }
    //Single digit number
    else if (isdigit(input[i]) && !isdigit(input[i+1]) && input[i] != '\0') {
      token[i] = (int)input[i] - 48;
    }
    //Multiple digit number
    else if (isdigit(input[i]) && isdigit(input[i+1])) {
      //While input[i] isn't a space
      while (isdigit(input[i])) {
	count++;
	i++;
      }
      //If input[i] is a space
      if (!isdigit(input[i])) {
	for (int j = count; j > 0; j--) {
	  num = input[i-j] - 48;
	  exp = pow(10, j-1);
	  total += num * exp;
	}
      }
      token[i] = total;
      total = count = 0;
    }
  }
   heaparr[0] = 0;
   //Place parsed values into another array with no zeros
   for (int i = 0; i < 100; i++) {
       if (token[i] != 0) {
	 heaparr[j] = token[i];
	 j++;
	 count++;
       }
   }
   //Construct the max heap
   buildHeap(heaparr, count);
   //Display heap
   displayVisual(heaparr, count);
   printHeap(heaparr, outputarr, count, o, h);
}
//Max heap functions are partially from GeeksforGeeks
//www.geeksforgeeks.com/building-heap-from-array/
//Function to convert array into heap
void heapify(int* arr, int n, int i) {
  //Initialize largest as root
  int largest = i;
  //Left = 2*1+1
  int l = 2*i +1;
  //Right = 2*i+2
  int r = 2*i +2;
  //If the left child is larger than i
  if (l < n && arr[l] > arr[largest]) {
    largest = l;
  }
  //If the right child is larger than the largest so far
  if (r < n && arr[r] > arr[largest]) {
    largest = r;
  }
  //If the largest is not i
  if (largest != i) {
    swap(arr[i], arr[largest]);
    //Recursively heapify the subtree
    heapify(arr, n, largest);
  }
}

//Function to build max heap
void buildHeap(int* arr, int n) {
  int startIdx = (n/2)-1;
  for (int i = startIdx; i >= 0; i--) {
    heapify(arr, n, i);
  }
}

//Function to print the max heap
//Help from Nicholas Fong, period 1, for help with this
void printHeap(int* arr, int* outputarr, int n, int o, int h) {
  while (arr[0] != '\0') {
    int r = 1;
    while (arr[r+1] != 0) {
      r++;
    }
    //Swap first and last items
    int temp = arr[0];
    arr[0] = arr[r];
    arr[r] = 0;
    outputarr[o] = temp;
    o++;
    h = 0;
    //Sort the array
    while (arr[h] != 0 && (arr[h] < arr[(h*2)+1] || arr[h] < arr[(h*2)+2])) {
      //If left child is larger than the right child
      if (arr[(h*2)+1] > arr[(h*2)+2]) {
	//Swap
	int swap1 = arr[h];
	arr[h] = arr[(h*2)+1];
	arr[(h*2)+1] = swap1;
	h = (h*2)+1;
      }
      //If right child is larger than the left child
      else if (arr[(h*2)+2] > arr[(h*2)+1]) {
	//Swap
	int swap2 = arr[h];
	arr[h] = arr[(h*2)+2];
	arr[(h*2)+2] = swap2;
	h = (h*2)+2;
      }
    }
  }
  //Print out the heap and remove numbers
  cout <<"\n" <<  "Heap: " << endl;
  for (int i = 0; i < n; i++) {
    if (outputarr[i] != 0) {
      cout << outputarr[i] << " ";
      outputarr[i] = '\0';
    }
  }
}

//Function to visually display the max heap
void displayVisual(int* arr, int n) {
  for (int i = 0; i <= (n/2)-1; i++) {
    if (arr[i] != 0) {
      cout << " " << arr[i] << endl;
      cout << " /\\" << endl;
    }
    //If left child exists
    if (arr[(i*2)+1] != 0) {
      cout << arr[(i*2)+1] << " ";
    }
    //if right child exists
    if (arr[(i*2)+2] != 0) {
      cout <<  arr[(i*2)+2] << "\n";
    }
  }
}
