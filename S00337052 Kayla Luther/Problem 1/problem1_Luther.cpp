// Kayla Luther
// CSCI 6170 - Dr. Gao
// Programming Assignment 3_1 - Keyword search - non sorted 
// December 12, 2019

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>   	// for clock_t, clock(), CLOCKS_PER_SEC
#include <vector>
#include <fstream>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef struct _title{
  char tconst[12];
  char name[255];
  int year;

}Title;

int main() 
{ 
    // to store execution time of code
    double time_spent = 0.0;
    char str[255];
  
    ifstream is;
    vector<Title> titles;

    // This block of code will open the file and determine the filesize by finding the beg and end
    is.open("out.dat", ios::binary);
    is.seekg(0, ios::end);
    size_t filesize=is.tellg();
    is.seekg(0, ios::beg);
  
    titles.resize(filesize/sizeof(Title));
    
    // This line of code will do the reading of the file
    is.read((char *)titles.data(), filesize);

    cout << "Enter the Name of the Movie you would like to view information about (MUST BE THE COMPLETE TITLE NAME): " << endl;
    cin.getline(str, sizeof(str));
    
    clock_t begin = clock();

    for(int i = 0; i < titles.size(); i++){
      if(strstr(titles[i].name,str) != NULL){
        cout << "\nTconst: " << titles[i].tconst << "\nName: " << titles[i].name << "\nYear: " << titles[i].year <<endl;
      }
    }
    clock_t end = clock();
    printf("\n");

    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
  
    cout << "Execution Time is " << time_spent << " seconds\n\n";
    
    is.close();
    return 0;
} 