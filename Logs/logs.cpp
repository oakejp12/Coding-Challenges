#include <iostream>
#include <fstream>
#include <string>
#include <regex>
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

  // Read log file and push logs to vector of strings
  if (!infile.is_open()) {
    cout << "System could not open file!" << '\n';
    return EXIT_FAILURE;
  } else {

    // Input log lines
    string x;
    while(infile >> x) {
      logs.push_back(x);
    }
  }

  // Develop regex patterns for searching the log file
  // OS, Browser, IP, Date and Time, File Requested, Referrer

  regex integer("(\\+|-)?[[:digit:]]+");
  regex browser("((\")[a-zA-Z]+\\/[0-9]+\\.[0-9]+)");
  regex IP ("^((([0-9]){1,3})\\.){3}[0-9]{1,3}");
  regex DATE_TIME("(?:\\[[0-9]{2}\\/[a-zA-Z]{3,}\\/[0-9]{4}(\\:[0-9]{2}){3} \\+[0-9]{4}\\])");
  regex REFERRER("(?:\"([a-z]{4,5}:\\/\\/)(.+?).[a-z]+\")");
  regex FILE ("(?:(\\/)[a-zA-Z0-9]+\\.[a-z]+)");


  string log_ex = "127.0.0.1 - - [19/Jun/2012:09:16:22 +0100] \"GET /GO.gif HTTP/1.1\" 499 0 \"http://domain.com/htm_data/7/1206/758536.html\" \"Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; Trident/4.0; .NET CLR 1.1.4322; .NET CLR 2.0.50727; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729; SE 2.X MetaSr 1.0)\"";







  return EXIT_SUCCESS;
}
