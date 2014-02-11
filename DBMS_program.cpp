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
		for(itt = data.begin(); itt != data.end(); itt++)
		{
			if((*itt) ==  data[i])
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
		for(size_t i=0;i<IN_columnNames.size();i++){
			columns.push_back(Column(IN_columnNames[i],IN_columnTypes[i]));
		}
		for(size_t i=0;i<IN_primaryKeys.size();i++)	{
			primaryKeys.push_back(IN_primaryKeys[i]);
		}
	}
	// constructor 
	Table(string IN_name, vector<Column> IN_columns, vector<string> IN_primaryKeys){
		name = IN_name;
		columns = IN_columns;
		for(size_t i=0;i<IN_primaryKeys.size();i++){
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
		
		for(size_t i = 0; i<IN_table.columns[0].getSize(); ++i){	
			for(size_t j = 0; j<IN_table.columns.size(); ++j){		
				returnOutput += IN_table.columns[j][i];		
				returnOutput += "\t";
			}
			returnOutput += "\n";
		}
		return out << returnOutput;
	}
	//delete function
	void deleteFrom(string comparison){
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
	// returns a vector of columns based on a list of their names
	vector<Column> getColumns(vector<string> columnNames) {
		vector<Column> subset;
		for(size_t i = 0; i<columnNames.size(); ++i) { // goes through the column names
			for(size_t j = 0; j<columns.size(); ++j) {  // goes through columns of table
				if( columnNames[i] == columns[j].getName() ) {
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

vector<Table> database;

int main(){
	//Parser goes here.
	int type = 0;
	//"type" will emulate parser for time being.
	printf("WELCOME TO THE DBMS!\n");
		
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
		
	} else if(type == 4) {
		// UPDATE relation-name SET (column-name = literal) WHERE condition 
		vector<string> colNames;
		string name = "test table";
		string column_name = "Col1";
		string literal = "12";
		//string condition_col = "Col1"
		//string condition_val = "42";
	
		//actual work
		for(size_t i = 0; i<database.size(); i++){ //typical "find the table"
			if(database[i].getName().compare(name) == 0){
				//database[i].Update(...);
			}
		}
	}	
}

// Selection
Table Select(string newName, string condition, string tabName) {

	Table selection;
	for(size_t i = 0; i<database.size(); i++){ //typical "find the table"
			if(database[i].getName().compare(tabName) == 0){
				selection = database[i];
			}
	}
	// delete from selection rows that do not meet the condition
	selection.deleteFrom(condition);
	selection.setName(newName);
	return selection;
}

// Projection
Table Project(string newName, vector<string> columnNames, string tabName) {
	
	vector<Column> subset;
	vector<string> primaryKeys;
	primaryKeys.push_back("key:projection");
	
	for(size_t i = 0; i<database.size(); i++){ //typical "find the table"
			if(database[i].getName().compare(tabName) == 0){
				subset = database[i].getColumns(columnNames);
			}
	}
	
	return Table(newName, subset, primaryKeys);

}

// Renaming (renames the columns)
Table Rename(string newName, vector<string> columnNames, string tabName) {
	vector<Column> subset;
	vector<string> primaryKeys;
	primaryKeys.push_back("key:rename");
	
	for(size_t i = 0; i<database.size(); i++){ //typical "find the table"
			if(database[i].getName().compare(tabName) == 0){
				subset = database[i].getColumns(columnNames);
			}
	}
	if(columnNames.size() == subset.size()) {	// make sure the column counts are matching
		for(size_t i = 0; i<subset.size(); i++){ 
			subset[i].setName(columnNames[i]);	// change the column names
		}
	}
	return Table(newName, subset, primaryKeys);	// returns the table with change column names if the input is correct
}

// UNION
Table Union(string newName, string tabName1, string tabName2) {
	vector<Column> tab1, tab2;
	bool compatible = true;
	vector<string> primaryKeys;
	primaryKeys.push_back("key:union");
	
	
	for(size_t i = 0; i<database.size(); i++){ //typical "find the table"
			if(database[i].getName().compare(tabName1) == 0){
				tab1 = database[i].getColumns();
			} else if(database[i].getName().compare(tabName2) == 0) {
				tab2 = database[i].getColumns();
			}		
	}
	
	// check for union compatibility
	if(tab1.size() != tab2.size()) {
		compatible = false;
	} else {
		for(size_t i = 0; i<tab1.size(); i++) {
			if(tab1[i].getType() != tab2[i].getType()) {
				compatible = false;
			}
		}
	}
	Table onion;			
	// execute the union of tab1 and tab2 (duplicates are allowed)
	if(compatible) {
		onion = Table(newName, tab1, primaryKeys);	// creates a new table with the first tables columns
		for(size_t i = 0; i<tab2[0].getSize(); i++) {	// iterates down the column
			vector<string> row;
			for(size_t j = 0; i<tab2.size(); j++) {	// iterates through the row
				row.push_back(tab2[j][i]);
			}
			onion.addRow(row);
		}
	}
	return onion;	// returns the union if compatible and and empty table otherwise
}

// DIFFERENCE
Table Difference(string newName, string tabName1, string tabName2) {
	vector<Column> tab1, tab2;
	bool compatible = true;
	vector<string> columnNames;
	vector<string> columnTypes;
	vector<string> primaryKeys;
	primaryKeys.push_back("key:difference");
	
	
	for(size_t i = 0; i<database.size(); i++){ //typical "find the table"
			if(database[i].getName().compare(tabName1) == 0){
				tab1 = database[i].getColumns();
			} else if(database[i].getName().compare(tabName2) == 0) {
				tab2 = database[i].getColumns();
			}		
	}
	
	// check for union compatibility
	if(tab1.size() != tab2.size()) {
		compatible = false;
	} else {
		for(size_t i = 0; i<tab1.size(); i++) {
			if(tab1[i].getType() != tab2[i].getType()) {
				compatible = false;
			}
			else {
				columnTypes.push_back(tab1[i].getType());
				columnNames.push_back(tab1[i].getName());
			}
		}
	}
	
	Table difference = Table(newName, columnNames, columnTypes, primaryKeys);// creates a new table with the column names/types of table 1
	// execute the difference of tab1 and tab2 (tab1 - tab2)
	bool addrow;
	for(size_t i = 0; i<tab1[0].getSize(); i++) {	// iterates down the first column of tab1
		addrow = true;
		vector<string> row1;
		for(size_t j = 0; i<tab1.size(); j++) {	// iterates across each row of tab1
			row1.push_back(tab1[j][i]);
		}
		for(size_t i = 0; i<tab1[0].getSize(); i++) {	// iterates down the first column of tab2
			vector<string> row2;
			for(size_t j = 0; i<tab2.size(); j++) {	// iterates across each row of tab2
				row2.push_back(tab2[j][i]);
			}
			if(row1==row2) {		// compare row1 with row2
				addrow = false;		// if row1 equals row2, row1 will not be in the difference table
			}
		}
		if(addrow) {
			difference.addRow(row1);
		}	
	}
	return difference;	// returns the union if compatible and and empty table otherwise

}

//Product
Table Product (string newName, string tabName1, string tabName2){
	vector<Column> tab1, tab2;
	vector<string> columnNames;
	vector<string> columnTypes;
	vector<string> primaryKeys;
	primaryKeys.push_back("key:product");

	for(size_t i = 0; i<database.size(); i++){ //typical "find the table"
			if(database[i].getName().compare(tabName1) == 0){
				tab1 = database[i].getColumns();
			} else if(database[i].getName().compare(tabName2) == 0) {
				tab2 = database[i].getColumns();
			}		
	}

	Table product = Table(newName, columnNames, columnTypes, primaryKeys);

	for(size_t i = 0; i<tab1[0].getSize(); i++) { //iterate down first column of table 1
		vector<string> newRow;
		for(size_t j = 0; i<tab1.size(); j++){    //iterate across row
			for(size_t k = 0; k < tab2[0].getSize(); k++) { // iterate down first column of table 2
				for(size_t ii = 0; k<tab2.size(); ii++){ // iterate through rows of column
					newRow.push_back(tab1[j][i]);        //push value of current row of tab1 with every row of current tab2.
					newRow.push_back(tab2[ii][k]);
				}
			}
		}

		product.addRow(newRow);

	}

	return product; // returns product
	
}

//Join
Table Join(string newName, string tabName1, string tabName2) {
	vector<Column> tab1, tab2;
	bool compatible = true;
	vector<string> columnNames;
	vector<string> columnTypes;
	vector<string> primaryKeys;
	primaryKeys.push_back("key:difference");
	
	
	for(size_t i = 0; i<database.size(); i++){ //typical "find the table"
			if(database[i].getName().compare(tabName1) == 0){
				tab1 = database[i].getColumns();
			} else if(database[i].getName().compare(tabName2) == 0) {
				tab2 = database[i].getColumns();
			}		
	}
	
	Table join = Table(newName, columnNames, columnTypes, primaryKeys);// creates a new table with the column names/types of table 1
	// execute the joining of tab1 and tab2 
	bool addrow;
	for(size_t i = 0; i<tab1[0].getSize(); i++) {	// iterates down the first column of tab1
		addrow = false;
		vector<string> row1;
		for(size_t j = 0; i<tab1.size(); j++) {	// iterates across each row of tab1
			row1.push_back(tab1[j][i]);
		}
		for(size_t i = 0; i<tab1[0].getSize(); i++) {	// iterates down the first column of tab2
			vector<string> row2;
			for(size_t j = 0; i<tab2.size(); j++) {	// iterates across each row of tab2
				row2.push_back(tab2[j][i]);			// pushes into row2 to compare later
				row1.push_back(tab2[j][i]);         // appends row2 onto row1 in case they are same
			}
			if(row1==row2) {		// compare row1 with row2
				addrow = true;		// if row1 equals row2, then the appended row1 is added to join table
			}
		}
		if(addrow) {
			join.addRow(row1);
		}	
	}
	return join;	// returns the union if compatible and and empty table otherwise

}