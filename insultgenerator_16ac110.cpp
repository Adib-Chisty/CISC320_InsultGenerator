#include "insultgenerator_16ac110.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <exception>
#include <algorithm>
#include <random>
#include <time.h>
#include <set>
#include <unordered_set>

using namespace std;

void InsultGenerator::initialize() {
	string word1, word2, word3;
	ifstream src("InsultsSource.txt");
	if (src.fail()) {
		throw FileException();
	}
	else {
		while (!src.eof()) {
			getline(src, word1, '\t');
			col1.push_back(word1);
			getline(src, word2, '\t');
			col2.push_back(word2);
			getline(src, word3, '\n');
			col3.push_back(word3);
		}
	}
	src.close();
}

string InsultGenerator::talkToMe() { //TODO: add phrase compatibility
	srand(time(NULL));
	string single_insult = "Thou " + col1.at(rand() % col1.size()) + " " + col2.at(rand() % col2.size()) + " " + col3.at(rand() % col3.size()) + "!";
	return single_insult;
}

bool exists(vector<string> vecToTest, string input) {
	for (int i = 0; i < vecToTest.size(); i++) {
		if (input == vecToTest.at(i)) {
			return true;
		}
	}
	return false;
}


vector<string> setToVec(unordered_set<string> uset) {
	vector<string> v;
	copy(uset.begin(), uset.end(), std::back_inserter(v));  
	sort(v.begin(), v.end());
	return v;
}

vector<string> setToVec(set<string> set) {
	vector<string> v(set.begin(),set.end());
	return v;
}

vector<string> InsultGenerator::generate(unsigned int n) {
	if (n < 1 || n > 10000) {
		throw NumInsultsOutOfBounds();
	}
	set<string> set_of_insults; //it seems an ordered set with no sorting at the end works better than unordered sets with sorting
	string tmp;
	srand(time(NULL));
	int i = 1;
	while (set_of_insults.size() < n) {
		tmp = "Thou " + col1.at(rand() % col1.size()) + " " + col2.at(rand() % col2.size()) + " " + col3.at(rand() % col3.size()) + "!";
		set_of_insults.emplace(tmp);
	}
	vector<string>vector_of_insults = setToVec(set_of_insults);
	return vector_of_insults;
}


void InsultGenerator::generateAndSave(string fName, unsigned int n) {
	vector<string> insults = generate(n);
	ofstream outputFile(fName);
	for (int idx = 0; idx < insults.size(); idx++) {
		outputFile << insults.at(idx) << endl;
	}
	outputFile.close();
}

string NumInsultsOutOfBounds::what() {
	return "Invalid number of insults requested! (Valid range:1-10,000)";
}

string FileException::what() {
	return "An error occured while finding or trying to open the input file!";
}