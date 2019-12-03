// Kayla Luther
// CSCI 6170 - Dr. Gao
// Programming Assignment 3_2 - Sorted Index File
// December 12, 2019

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>   	// for clock_t, clock(), CLOCKS_PER_SEC
#include <vector>
#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

typedef struct _title{
  char tconst[12];
  char name[255];
  int year;

}Title;

// sort the vector pairs
bool compareElements(const pair<int, string> &a, const pair<int, string> &b)
{
  return (a.second < b.second);
}

bool compareNames(Title name1, Title name2)
{
  if(strcmp(name1.name, name2.name) < 0){
    return true;
  }
  return false;
}

int main() 
{ 
  // to store execution time of code
  double time_spent = 0.0;
  char str[255];
  
  ifstream is;
  vector<Title> searchinfo;

  // This block of code will open the file and determine the filesize by finding the beg and end
  is.open("out.dat", ios::binary);
  is.seekg(0, ios::end);
  size_t filesize=is.tellg();
  is.seekg(0, ios::beg);
  
  searchinfo.resize(filesize/sizeof(Title));

  // This line of code will do the reading of the file
  is.read((char *)searchinfo.data(), filesize); 

  // I created a pair for the index file, which will have the blockID and movie title name
  vector<pair<int, string>> indexVect; 

  // This will load the information such as the blockID and movie title name into the pair vector
  for(int i=0; i<searchinfo.size(); i++) {
      indexVect.push_back(make_pair(i,searchinfo[i].name));
  }

  //sort the vector
  sort(indexVect.begin(), indexVect.end(), compareElements); 

  // write to outfile the data for the index file.. the index number and the title name
  ofstream outfile("index.txt");   

  // Print the information to the index file
  for(int i=0; i<indexVect.size(); i++) 
    outfile << indexVect[i].first << " " << indexVect[i].second << endl;

  // Close out the ifstream and ofstream files so that you can open the index.txt file to do the searching
  outfile.close();
  is.close();

  // This block of code will open the file and determine the filesize by finding the beg and end
  ifstream indexFile;
  indexFile.open("index.txt", ios::in);
  indexFile.seekg(0, ios::end);
  size_t filesize1=indexFile.tellg();
  indexFile.seekg(0, ios::beg);

  cout << "Enter the Name of the Movie you would like to view information about (MUST BE THE COMPLETE TITLE NAME): " << endl;
  cin.getline(str, sizeof(str));

  int blockID;
  clock_t begin = clock();

  for(int i = 0; i <indexVect.size(); i++){
      if(indexVect[i].second == str){
	blockID = indexVect[i].first;
	cout << "\nBlock ID: " << blockID;
	cout << "\nTconst: " << searchinfo[blockID].tconst << "\nName: " << searchinfo[blockID].name << "\nYear: " << searchinfo[blockID].year <<endl;
    }
  }
  clock_t end = clock();

  // calculate elapsed time by finding difference (end - begin) and
  // dividing the difference by CLOCKS_PER_SEC to convert to seconds
  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
  
  cout << "\nExecution Time is " << time_spent << " seconds\n\n";

  indexFile.close();

  return 0;
}
