#include "std_lib_facilities_4.h"
#include <string>

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
	const size_t getSize() {
		return data.size();
	}
	//treat a column as an array; able to use [] when accessing a column variable
	string& operator[] (int i) {
		return data[i];
	}
	//goes through a column and deletes an element
	void deleteCell(int i){
		vector<string>::iterator itt = data.begin();
		for(; itt < data.end(); itt++)
		{
			if(itt == i)
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
	Table(string IN_name, vector<string> IN_columnNames, vector<string> IN_columnTypes, vector<string> IN_primaryKeys){
		name = IN_name;
		for(size_t i=0;i<IN_columnNames.size();i++){
			columns.push_back(Column(IN_columnNames[i],IN_columnTypes[i]));
		}
		for(size_t i=0;i<IN_primaryKeys.size();i++){
			primaryKeys.push_back(IN_primaryKeys[i]);
		}
	}
	const string getName() {
		return name;
	}
	//use this instead of column.addcell
	int addRow(vector<string> IN_row){
		if(columns.size() == IN_row.size()){
			for(size_t i = 0; i<columns.size(); i++){
				columns[i].addCell(IN_row[i]);
			}
			return 0;
		} else {
			return -1;
		}
	}
	//used for outputting table
	friend ostream& operator<< (ostream &out, Table &IN_table){
		string returnOutput = "";
		for(size_t i = 0; i<columns[0].getSize(); ++i){
			for(size_t j = 0; j<columns.size(); ++j){
				returnOutput += columns[j][i];
				returnOutput += "\t";
			}
			returnOutput += "\n";
		}
		return out << returnOutput;
	}
	//delete function
	void deleteFrom(string tabname, string comparison){
		for(size_t i = 0; i<columns[0].getSize(); ++i)  // goes through first column of table
		{
			if(columns[0][i] == comparison)  // finds index of the data that matches comparison
			{
				for(size_t j = 0; j<columns.size(); j++)  // goes through columns of table
				{
					columns[j].deleteCell(i);  // deletes ith cell in each column
				}
			}
		}	
	}
private:
	string name;
	vector<Column> columns;
	vector<string> primaryKeys;
};

vector<Table> database;

int main(){
	//Parser goes here.
	int type = 0;
	//"type" will emulate parser for time being.

	if(type == 0){
		//CREATE TABLE tabname (name VARCHAR(20), years INTEGER) PRIMARY KEY (name)
		string name = "test table";
		vector<string> colNames;
		colNames.push_back("Col1");
		colNames.push_back("Col2");
		colNames.push_back("Col3");
		vector<string> colTypes;
		colTypes.push_back("int");
		colTypes.push_back("char(40)");
		colTypes.push_back("int");
		vector<string> primaryKeys;
		primaryKeys.push_back("Col1");
		//actual work
		database.push_back(Table(name,colNames,colTypes,primaryKeys));
	} else if(type == 1){
		//DROP TABLE tabname
		string name = "test table";
		//actual work
		for(size_t i = 0; i<database.size(); i++){ //typical "find the table"
			if(database[i].getName().compare(name) == 0){
				database.erase(database.begin()+i);
				break;
			}
		}
	} else if(type == 2){
		//INSERT INTO relation-name VALUES FROM (T, T, T)
		string name = "test table";
		vector<string> row;
		row.push_back("42");
		row.push_back("Col2Cell");
		row.push_back("84");
		//actual work
		for(size_t i = 0; i<database.size(); i++){ //typical "find the table"
			if(database[i].getName().compare(name) == 0){
				if(database[i].addRow(row) == -1){
					cout << "Tried to add bad row";
				}
			}
		}
	} else if(type == 3){
		//SHOW tabname
		string name = "test table";
		//actual work
		for(size_t i = 0; i<database.size(); ++i){ //typical "find the table"
			if(database[i].getName().compare(name) == 0){
				cout << database[i];
			}
		}
	}

	
}
