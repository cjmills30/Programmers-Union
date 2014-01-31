#include "std_lib_facilities_4.h"
#include <string>
#include <iterator>

template <typename T>
ostream& operator<< (ostream& out, vector<T> in_vector){
	//This FINALLY lets you just plain send a vector to cout.
	//TODO: figure out what those warnings that flash on the compiler are/mean
	out << "{";
	for(size_t i=0; i < in_vector.size(); ++i){ // Changed i's type from int to size_t to solve signed/unsigned mismatch
		out << in_vector[i];
		if(i != in_vector.size()-1){
			out << ", ";
		}
	}
	out << "}";
	return out;
}

// add the Command class here

vector<string> parseLines(string in_read){
	vector<string> returnResult; //HACK: set as string until command class complete
	
	// This section strips all \n characters from in_read.
	size_t SPosition_StripNewline = 0;
	string strResultAfterStripNewline = "";
	string strDelimiter_Newline = "\n";
	while((SPosition_StripNewline = in_read.find(strDelimiter_Newline)) != -1) { // -1 = no match (formerly std::string::npos)
		strResultAfterStripNewline += in_read.substr(0,SPosition_StripNewline);
		in_read.erase(0,SPosition_StripNewline + strDelimiter_Newline.length());
	}

	// This section turns each full command (xxxxx xxx;yy yyyy yy;) into its own string and puts into a vector<string>.
	size_t SPosition = 0;
	string strToken = "";
	string strDelimiter = ";";
	while((SPosition = strResultAfterStripNewline.find(strDelimiter)) != -1) { // -1 = no match (formerly std::string::npos)
		strToken = strResultAfterStripNewline.substr(0,SPosition);
		returnResult.push_back(strToken);
		strResultAfterStripNewline.erase(0,SPosition + strDelimiter.length());
	}

	// This section parses the vector<string> passed from above into a vector<Command>


	//Done!
	return returnResult; // HACK: return vector<string> until command class complete
}

int main(){
	/* My goal is to parse:
		CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);

		INSERT INTO animals VALUES FROM ("Joe", "cat", 4);
		INSERT INTO animals VALUES FROM ("Spot", "dog", 10);
		INSERT INTO animals VALUES FROM ("Snoopy", "dog", 3);
		INSERT INTO animals VALUES FROM ("Tweety", "bird", 1);
		INSERT INTO animals VALUES FROM ("Joe", "bird", 2);

		SHOW animals;

		dogs <- select (kind == "dog") animals;
		old_dogs <- select (age > 10) dogs;

		cats_or_dogs <- dogs + (select (kind == "cat") animals);

		CREATE TABLE species (kind VARCHAR(10)) PRIMARY KEY (kind);

		INSERT INTO species VALUES FROM RELATION project (kind) animals;

		a <- rename (aname, akind) (project (name, kind) animals);
		common_names <- project (name) (select (aname == name && akind != kind) (a * animals));
		answer <- common_names;

		SHOW answer;

		WRITE animals;
		CLOSE animals;

		EXIT;
	Then we can change it to our liking and customize it for our code.
	*/
	string goalToParse = "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);\n\nINSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);\nINSERT INTO animals VALUES FROM (\"Spot\", \"dog\", 10);\nINSERT INTO animals VALUES FROM (\"Snoopy\", \"dog\", 3);\nINSERT INTO animals VALUES FROM (\"Tweety\", \"bird\", 1);\nINSERT INTO animals VALUES FROM (\"Joe\", \"bird\", 2);\n\nSHOW animals;\n\ndogs <- select (kind == \"dog\") animals;\nold_dogs <- select (age > 10) dogs;\n\ncats_or_dogs <- dogs + (select (kind == \"cat\") animals);\n\nCREATE TABLE species (kind VARCHAR(10)) PRIMARY KEY (kind);\n\nINSERT INTO species VALUES FROM RELATION project (kind) animals;\n\na <- rename (aname, akind) (project (name, kind) animals);\ncommon_names <- project (name) (select (aname == name && akind != kind) (a * animals));\nanswer <- common_names;\n\nSHOW answer;\n\nWRITE animals;\nCLOSE animals;\n\nEXIT;";
	vector<string> trythis = parseLines(goalToParse);
	cout << trythis;
	cin.get();
}
