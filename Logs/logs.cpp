#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char** argv) {

  if (argc != 2) {
    cout << "Incorrect number of arguments" << '\n';
    return EXIT_FAILURE;
  }

  // Shared variables
  ifstream infile (argv[1]);
  vector<string> logs;

  if (!infile.is_open()) {
    cout << "System could not open file!" << '\n';
    return EXIT_FAILURE;
  } else {

    // Input log lines


  }



  return EXIT_SUCCESS;
}
