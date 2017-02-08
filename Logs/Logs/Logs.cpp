#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

enum string_value
{
	OS,
	BROWSER,
	IP,
	DATE_TIME,
	REFERRER,
	FILEREQ
};

string_value hashit(std::string const& request)
{
	if (request == "OS" || request == "os") return OS;
	if (request == "BROWSER" || request == "browser") return BROWSER;
	if (request == "IP" || request == "ip") return IP;
	if (request == "DATE_TIME" || request == "date_time") return DATE_TIME;
	if (request == "REFERRER" || request == "referrer") return REFERRER;
	if (request == "FILEREQ" || request == "filereq") return FILEREQ;
}

void publish(std::vector<std::string> const& logs, std::regex const& regx)
{
	// Regex matching object on string literals
	std::smatch matchingObj;

	// Output results to file
	std::ofstream output;
	output.open("Results.txt");

	try {
		// TODO: Any way to destruct this away from three loops
		for (auto test : logs) {
			while (std::regex_search(test, matchingObj, regx)) {
				for (const auto& elem : matchingObj) {
					output << elem << " ";
					break;
				}
				output << '\n';
				test = matchingObj.suffix().str();
			}
		}

	} catch (std::regex_error& err) {
		// Error in the regular expression
		output << err.what() << '\n';
	}

	output.close();
}

int main(int argc, char** argv) {
	
	if (argc != 2) {
		std::cout << "Incorrect number of arguments" << '\n';
		return EXIT_FAILURE;
	}

	// Shared variables
	std::ifstream infile(argv[1]);
	std::vector<std::string> logs;

	// Read log file and push logs to vector of strings
	if (!infile.is_open()) {
		std::cout << "System could not open file!\n";
		return EXIT_FAILURE;
	} else {
		// Input log lines
		std::string temp;
		while (getline(infile, temp)) {
			logs.push_back(temp);
		}
	}

	// Close the file
	infile.close();

	// Get input from the user
	std::cout << "Enter search term: OS, BROWSER, IP, DATE_TIME, REFERRER, FILEREQ\n";
	std::string choice;
	std::cin >> choice;

	std::cout << "Writing to Results.txt\n";

	// Develop regex patterns for searching the log file
	// OS, Browser, IP, Date and Time, File Requested, Referrer
	switch (hashit(choice)) {
	case OS: {
		const std::regex SYS(R"(\([a-zA-Z]+(?:.*)\))");
		publish(logs, SYS);
		break;
	}
	case BROWSER: {
		const std::regex BROWS(R"([^\"]\w+\/[0-9].[0-9](?:\s))");
		publish(logs, BROWS);
		break;
	}
	case IP: {
		const std::regex IP(R"(^(?:[0-9]{1,3}\.){3}[0-9]{1,3})");
		publish(logs, IP);
		break;
	}
	case DATE_TIME: {
		const std::regex DATE(R"(\[[0-9]{2}\/[a-zA-Z]{3,}\/[0-9]{4}(?:\:[0-9]{2}){3}\s\+[0-9]{4}\])");
		publish(logs, DATE);
		break;
	}
	case REFERRER: {
		const std::regex REF(R"((?:\")[a-z]{4,5}\:\/\/(?:.+?).[a-z]+(?:\"))");
		publish(logs, REF);
		break;
	}
	case FILEREQ: {
		const std::regex FREQ(R"((?:\s\/)[a-zA-Z0-9]+\.[a-z]+)");
		publish(logs, FREQ);
		break;
	}
	default:
		std::cout << "Entered in wrong command!" << '\n';
		return EXIT_FAILURE;
	}

	return 0;
}
