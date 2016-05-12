/*
* Johan Oakes
* Compile: g++ -g -Wall commseq.cpp -o commseq -std=c++0x
* Run: ./commseq <filename>
*/


#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// Void function to implement looking back at table to find longest common subsequence
void commSeq(const vector< vector<int> >& lcs_matrix, const string x_seq, const string y_seq, size_t i, size_t j, vector<char>& result) {
  result.clear();

  // If length of strings are zero -> no lcs
  if (i == 0 || j == 0)
    return;
  else if (x_seq[i] == y_seq[j]) {
    commSeq(lcs_matrix, x_seq, y_seq, i-1, j-1, result);
    result.push_back(x_seq[i]);
    return;
  } else {
    (lcs_matrix[i][j-1] > lcs_matrix[i-1][j]) ? commSeq(lcs_matrix, x_seq, y_seq, i, j-1, result) : commSeq(lcs_matrix, x_seq, y_seq, i-1, j, result);
  }
}


int main(int argc, char* argv[]) {

  if (argc != 2) {
    cout << "Incorrect number of arguments";
  }

  // Global variables
  ifstream infile (argv[1]);
  string sequence;

  if (!infile.is_open()) {
    cout << "System could not open file!" << '\n';
    exit(4);
  } else {
    // Input sequence line
    infile >> sequence;
  }

  // Find the delimeter position and split the strings
  // Insert the zero char in front of string
  string delimiter = ";";
  string x_seq = (sequence.substr(0, sequence.find(delimiter))).insert(0, "0");
  string y_seq = (sequence.substr(sequence.find(delimiter) + 1)).insert(0, "0");

  // Values to speed up looping and make code readable
  size_t x_size = x_seq.size();
  size_t y_size = y_seq.size();

  // Make a 2D vector of ints to compute the lcs
  vector< vector<int> > lcs_matrix(x_size, vector<int>(y_size));

  // Initialize first row and column with zero
  for (size_t i = 0; i != x_size; i++) {
    lcs_matrix[i][0] = 0;
  }
  vector<int> row(y_size, 0);
  lcs_matrix.push_back(row);

  // Populate rows withs LCS values
  for (size_t m = 1; m != x_size; m++) {
    for (size_t n = 1; n != y_size; n++) {
      if (x_seq[m] == y_seq[n]) {
        lcs_matrix[m][n] = lcs_matrix[m-1][n-1] + 1;
      } else {
        lcs_matrix[m][n] = max(lcs_matrix[m-1][n], lcs_matrix[m][n-1]);
      }
    }
  }


  // Read through the matrix to find the common subsequence
  vector<char> result;
  commSeq(lcs_matrix, x_seq, y_seq, x_size, y_size, result);

  // Print out
  for (const auto& x : result)
    cout << x;

  return 0;
}
