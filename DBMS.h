#include "std_lib_facilities_4.h"
#include <string>
#include <iostream>

class Column{
public:
	Column(string IN_name, string IN_type){
		name = IN_name;
		type = IN_type;
	}
	//this is part of table.addrow; don't use if you don't evenly distribute
	void addCell(string IN_string){
		data.push_back(IN_string);
	}
	void setName(string newName) {
		name = newName;
	}
	const string getName() {
		return name;
	}
	const string getType() {
		return type;
	}
	const size_t getSize() {
		return data.size();
	}
	//treat a column as an array; able to use [] when accessing a column variable
	string& operator[] (int i) {
		return data[i];
	}
	//goes through a column and deletes a cell (element)
	void deleteCell(int i)
	{
		vector<string>::iterator itt;
		for (itt = data.begin(); itt != data.end(); itt++)
		{
			if ((*itt) == data[i])
			{
				data.erase(itt);
			}
		}
	}
private:
	string name;
	string type;
	vector<string> data;
};

class Table{
public:
	// constructor
	Table(string IN_name, vector<string> IN_columnNames, vector<string> IN_columnTypes, vector<string> IN_primaryKeys){
		name = IN_name;
		for (size_t i = 0; i<IN_columnNames.size(); i++){
			columns.push_back(Column(IN_columnNames[i], IN_columnTypes[i]));
		}
		for (size_t i = 0; i<IN_primaryKeys.size(); i++)	{
			primaryKeys.push_back(IN_primaryKeys[i]);
		}
	}
	// constructor 
	Table(string IN_name, vector<Column> IN_columns, vector<string> IN_primaryKeys){
		name = IN_name;
		columns = IN_columns;
		for (size_t i = 0; i<IN_primaryKeys.size(); i++){
			primaryKeys.push_back(IN_primaryKeys[i]);
		}
	}
	// another constructor
	Table() {
		name = "";
	}

	const string getName() {
		return name;
	}
	void setName(string newName) {
		name = newName;
	}
	//use this instead of column.addcell
	int addRow(vector<string> IN_row){
		if (columns.size() == IN_row.size()){
			for (size_t i = 0; i<columns.size(); i++){
				columns[i].addCell(IN_row[i]);
			}
			return 0;
		}
		else {
			return -1;
		}
	}
	//used for outputting table
	friend ostream& operator<< (ostream &out, Table &IN_table){
		string returnOutput = "";

		returnOutput += IN_table.getName();
		returnOutput += "\n";

		for (size_t i = 0; i<IN_table.columns[0].getSize(); ++i){
			for (size_t j = 0; j<IN_table.columns.size(); ++j){
				returnOutput += IN_table.columns[j][i];
				returnOutput += "\t";
			}
			returnOutput += "\n";
		}
		return out << returnOutput;
	}
	//delete function
	void deleteFrom(string comparison){
		for (size_t i = 0; i<columns[0].getSize(); ++i)  // goes through first column of table
		{
			if (columns[0][i] == comparison)  // finds index of the data that matches comparison
			{
				for (size_t j = 0; j<columns.size(); j++)  // goes through columns of table
				{
					columns[j].deleteCell(i);  // deletes ith cell in each column
				}
			}
		}
	}
	// returns a vector of columns based on a list of their names
	vector<Column> getColumns(vector<string> columnNames) {
		vector<Column> subset;
		for (size_t i = 0; i<columnNames.size(); ++i) { // goes through the column names
			for (size_t j = 0; j<columns.size(); ++j) {  // goes through columns of table
				if (columnNames[i] == columns[j].getName()) {
					subset.push_back(columns[j]);		// add the column to the subset if name is in the list
				}
			}
		}
		return subset;
	}
	// returns a vector of all of the columns in the table
	vector<Column> getColumns() {
		return columns;
	}
	/*
	int Update(vector<string> IN_columnNames, vector<string> values, vector<int> rows_to_update) {

	for(size_t k = 0; k<IN_columnNames.size(); ++k) {	// goes through the list of columns to update
	for(size_t i = 0; i<columns.size(); ++i) {  // goes through the columns of table
	if(columns[i].getName() == IN_columnNames[k]) {  // find the column needed to update
	for(size_t j = 0; j<columns[i].getSize(); j++) { // goes through rows of the
	if(columns[i][j] == condition_val) {	// find the rows with the condition value
	rows_to_update.push_back(j);		// add the row index to rows_to_update
	}
	}
	}
	}
	//now we know which rows to update
	for(size_t i = 0; i<columns.getSize(); ++i) {  // goes through the columns of table
	//if(columns[i].getName() == IN_columnNames
	}
	}
	*/
private:
	string name;
	vector<Column> columns;
	vector<string> primaryKeys;
};

Table Select(string newName, string condition, string tabName,vector<Table> database);
Table Project(string newName, vector<string> columnNames, string tabName,vector<Table> database);
Table Rename(string newName, vector<string> columnNames, string tabName,vector<Table> database);
Table Union(string newName, string tabName1, string tabName2,vector<Table> database);
Table Difference(string newName, string tabName1, string tabName2,vector<Table> database);
Table Product (string newName, string tabName1, string tabName2,vector<Table> database);
Table Join(string newName, string tabName1, string tabName2,vector<Table> database);

void Show(string tabname, vector<Table> database);


