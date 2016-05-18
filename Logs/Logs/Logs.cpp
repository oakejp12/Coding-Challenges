#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

enum string_value
{
	OS,
	BROWSER,
	IP,
	DATE_TIME,
	REFERRER,
	FILEREQ
};

string_value hashit(string const& request)
{
	if (request == "OS" || request == "OS") return OS;
	if (request == "BROWSER" || request == "browser") return BROWSER;
	if (request == "IP" || request == "ip") return IP;
	if (request == "DATE_TIME" || request == "date_time") return DATE_TIME;
	if (request == "REFERRER" || request == "referrer") return REFERRER;
	if (request == "FILEREQ" || request == "filereq") return FILEREQ;
}

void publish(vector<string> const& logs, regex const& regx)
{
	// Regex matching object on string literals
	std::smatch m;

	// Output results to file
	ofstream output;
	output.open("Results.txt");

	try {
		for (size_t i = 0; i < logs.size(); ++i) {
			string test = logs[i];
			while (regex_search(test, m, regx))
			{
				for (const auto& x : m)
				{
					output << x << " ";
					break;
				}
				output << endl;
				test = m.suffix().str();
			}
		}
	} catch (regex_error& err) {
		// Syntax error in the regular expression
		output << err.what() << '\n';
	}

	output.close();
}

int main(int argc, char** argv) {
	
	if (argc != 2) {
		cout << "Incorrect number of arguments" << '\n';
		return EXIT_FAILURE;
	}

	// Shared variables
	ifstream infile(argv[1]);
	vector<string> logs;

	// Read log file and push logs to vector of strings
	if (!infile.is_open()) {
		cout << "System could not open file!" << '\n';
		return EXIT_FAILURE;
	}
	else {
		// Input log lines
		string temp;
		while (getline(infile, temp)) {
			logs.push_back(temp);
		}
	}

	// Close the file
	infile.close();

	// Get input from the user
	cout << "Enter search term: OS, BROWSER, IP, DATE_TIME, REFERRER, FILEREQ" << '\n';
	string choice;
	cin >> choice;

	cout << "Writing to Results.txt" << '\n';

	// Develop regex patterns for searching the log file
	// OS, Browser, IP, Date and Time, File Requested, Referrer
	switch (hashit(choice))
	{
	case OS: {
		const regex SYS(R"(\([a-zA-Z]+(?:.*)\))");
		publish(logs, SYS);
		break;
	}
	case BROWSER: {
		const regex BROWS(R"([^\"]\w+\/[0-9].[0-9](?:\s))");
		publish(logs, BROWS);
		break;
	}
	case IP: {
		const regex IP(R"(^(?:[0-9]{1,3}\.){3}[0-9]{1,3})");
		publish(logs, IP);
		break;
	}
	case DATE_TIME: {
		const regex DATE(R"(\[[0-9]{2}\/[a-zA-Z]{3,}\/[0-9]{4}(?:\:[0-9]{2}){3}\s\+[0-9]{4}\])");
		publish(logs, DATE);
		break;
	}
	case REFERRER: {
		const regex REF(R"((?:\")[a-z]{4,5}\:\/\/(?:.+?).[a-z]+(?:\"))");
		publish(logs, REF);
		break;
	}
	case FILEREQ: {
		const regex FREQ(R"((?:\s\/)[a-zA-Z0-9]+\.[a-z]+)");
		publish(logs, FREQ);
		break;
	}
	default:
		cout << "Entered in wrong command!" << '\n';
		return EXIT_FAILURE;
	}
	

	return EXIT_SUCCESS;
}
