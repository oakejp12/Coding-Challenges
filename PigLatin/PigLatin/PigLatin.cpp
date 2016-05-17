/*
* Johan Oakes
* Pig Latin Solution - EA Challenges
*
* Example Input : "HeLLo World! I can't wait to explore your VAST forests. The-End!"
* Example Output : "ElLOhay Orldway! I antca'y aitway otay exploreway ouryay ASTVay orestfay. Hetay-Endway!"
*/

#include <iostream>
#include <string>
#include <sstream>
#include <ctype.h>

using namespace std;


string PigLatin(string const& word) {
	string plword = word;
	const string vowel = "aeiouAEIOU";
	const string way = "way";

	// If string is empty -> return
	// Or if string is one character
	if (word.empty() || word.length() == 1) {
		return word;
	}
	else if (word.find(way) != string::npos) {
		// Words the end in way are not modified
		return word;
	}
	else if (word.find('-') != string::npos) {
		size_t hyphen = word.find('-');
		return plword = PigLatin(word.substr(0, hyphen)) + '-' + PigLatin(word.substr(hyphen + 1));
	}

	char first = word.front();
	size_t found = vowel.find(first);
	if (found != string::npos) {
		// Word starts with a vowel
		plword += "way";
	}
	else {
		// Word starts with a consonant
		char plfirst = plword.front();

		// Check for words the preserve capitals throughout
		if (!isupper(word.back())) {
			plfirst = tolower(plfirst);
		}

		// Move first letter to the back
		plword.push_back(plfirst); 
		plword.erase(0, 1);
		plword += "ay";
	}

	// Check for punctuation
	for (size_t i = 0; i != word.size(); i++) {
		if (ispunct(word[i])) {
			size_t loc = word.size() - i;
			char temp = word[i];
			
			// Erase based on whether word starts with a vowel or not
			if (found != string::npos) plword.erase(i, 1);
			else plword.erase(i - 1, 1);

			plword.insert(plword.size() - loc + 1, 1, temp);
			break;
		}
	}

	// Maintain captilization
	if (isupper(first)) {
		plword.front() = toupper(plword.front());
	}

	return plword;
}

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
		cout << PigLatin(word) << " ";
	}
	
	//cin.get(); // Used to make VS2015 wait

	return 0;
}