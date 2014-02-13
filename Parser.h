#include "std_lib_facilities_4.h"
#include <string>
#include <iostream>

vector<string> parseCommand(string IN_string);

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

vector<vector<string>> parseLines(string in_read){
	vector<vector<string>> returnThis;
	
	vector<string> returnResult;
	
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

	for(size_t i=0;i<returnResult.size(); ++i){
		vector<string> extractedInfo;
		if(returnResult[i].substring(0,6).compare("CREATE")){ // do this
			extractedInfo.push_back("CREATE");
		} else if(returnResult[i].substring(0,6).compare("INSERT"){ // do this
			extractedInfo.push_back("INSERT");
			//extractedIndo.push_back(returnResult[i
		} else if(returnResult[i].substring(0,4).compare("SHOW"){
			extractedInfo.push_back("SHOW");
			extractedInfo.push_back(returnResult[i].substring(5,returnResult[i].length()));
		} else if(returnResult[i].substring(0,5).compare("WRITE"){ // do this
			extractedInfo.push_back("WRITE");
		} else if(returnResult[i].substring(0,4).compare("OPEN"){ // do this
			extractedInfo.push_back("OPEN");
		} else if(returnResult[i].substring(0,6).compare("DELETE"){ // do this
			extractedInfo.push_back("DELETE");
		} else if(returnResult[i].find("<-") > 0){
			extractedInfo.push_back("<-");
			extractedInfo.push_back(returnResult[i].substring(0,returnResult[i].find("<-")-1);
			extractedInfo.push_back(returnResult[i].substring(returnResult[i].find("<-")+3,returnResult[i].length()));
		}
		returnThis.push_back(extractedInfo);
	}
	
	//Done!
	return returnThis;
}

vector<string> parseCommand(string IN_string){
	if(IN_string
	
