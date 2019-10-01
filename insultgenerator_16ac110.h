#pragma once
#include <vector>
#include <string>
using namespace std;

class InsultGenerator {
public:
	void initialize();
	string talkToMe();
	vector<string> generate(unsigned int n);
	void generateAndSave(string fName, unsigned int n);
private:
	vector<string> col1;
	vector<string> col2;
	vector<string> col3;
};

class NumInsultsOutOfBounds {
public:
	string what();
};

class FileException {
public:
	string what();
};