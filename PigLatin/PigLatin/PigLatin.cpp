/*
* Johan Oakes
* Pig Latin Solution - EA Challenges
*
* Example Input : "HeLLo World! I can't wait to explore your VAST forests. The-End!"
* Example Output : "ElLOhay Orldway! I antca'y aitway otay exploreway ouryay ASTVay orestfay. Hetay-Endway!"
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;


int main(int argc, char** argv) {

	string inputline; // Holds the input

	// Read the line
	cout << "What's the input string" << '\n';
	getline(cin, inputline);

	// Use streams to operate word by word
	stringstream ss(inputline);
	string word;
	while (ss >> word) {
		// Operate on the word
	}
	
	



	cin.get(); // Used to make VS2015 wait

	return 0;
}