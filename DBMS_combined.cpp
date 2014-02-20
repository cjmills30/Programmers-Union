//
// IMPORTANT: TO COMPILE:
//	g++ -std=c++11 -static-libstdc++ DBMS_combined.cpp
// ERRORS CORRELATE, BUT DO NOT NECESSARILY CORRESPOND TO LINE NUMBERS
//	Don't waste your time updating the error numbers unless it is absolutely crucial to what you are doing.

#include "std_lib_facilities_4.h"
#include <string>
#include <iostream>

using namespace std;

template <typename T>
ostream& operator<< (ostream& out, vector<T> in_vector){
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
	
	/* int Update(vector<string> IN_columnNames, vector<string> values, vector<int> rows_to_update) {

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
	}*/
	
private:
	string name;
	vector<Column> columns;
	vector<string> primaryKeys;
};

vector<Table> database;

Table Select(string newName, string condition, string tabName, vector<Table> database) {

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
Table Project(string newName, vector<string> columnNames, string tabName, vector<Table> database) {
	
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
Table Rename(string newName, vector<string> columnNames, string tabName, vector<Table> database) {
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

// UNION /********WORKING-ACTUALLY ADDS NEW ROWS***********/
Table Union(string newName, string tabName1, string tabName2, vector<Table> database) {
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
	/*if(tab1.size() != tab2.size()) {
		compatible = false;
	} else {
		for(size_t i = 0; i<tab1.size(); i++) {
			if(tab1[i].getType() != tab2[i].getType()) {
				compatible = false;
			}
		}
	}*/
			
	// execute the union of tab1 and tab2 (duplicates are allowed)
	/*if(compatible) {
		onion = Table(newName, tab1, primaryKeys);	// creates a new table with the first tables columns
		for(size_t i = 0; i<tab2[0].getSize(); i++) {	// iterates down the column
			vector<string> row;
			for(size_t j = 0; i<tab2.size(); j++) {	// iterates through the row
				row.push_back(tab2[j][i]);
			}
			onion.addRow(row);
		}
	}*/

	vector<string> colName;
	vector<string> colType;
	colName.push_back("col Name");
	colType.push_back("Type T");

	Table onion = Table(newName, colName, colType, primaryKeys);
	for(size_t i = 0; i<tab1[0].getSize(); i++) { //iterate down first column of table 1
		vector<string> newRow;
		vector<string> tmp1;  //IMPORTANT!!! tmp1, tmp2, and tmp3 created
		  vector<string> tmp2;//so that row vector doesn't get pushed into, requiring more columns
		vector<string> newColumns;
		vector<string> colNames;
		for(size_t j = 0; j<tab1.size(); j++){    //iterate across row using number of columns 3 col = 3 rows
			for(size_t k = 0; k < tab2[0].getSize(); k++) { // iterate down first column of table 2
				for(size_t ii = 0; ii<tab2.size(); ii++){ // iterate through rows of column
					if(newRow.size() == 0) {	         //Checks to make sure has values in vector
						if(tab1[j][0] == tab2[ii][0]) {
							newRow.push_back(tab1[j][0]);
							onion.addRow(newRow);
						}
						else //Adds both table values since both don't have same value
							
						  
							newRow.push_back(tab1[j][0]);
							tmp1.push_back(tab1[j][0]);
							onion.addRow(tmp1);
							tmp2.push_back(tab2[ii][0]);
							newRow.push_back(tab2[ii][0]);
							onion.addRow(tmp2);
					}	
					else if(newRow.size() != 0) {          //If values in vector then can check for copies
							int t1flag = 0;
							int t2flag = 0;
						for(int iii = 0; iii < newRow.size(); iii++){ //flags to check both tables
							if(newRow[iii] == tab1[j][0]){
								t1flag = 1;
							}
							if(newRow[iii] == tab2[ii][0]){
								t2flag = 1;
							}
						}
						if(t1flag != 1){               //If not flagged then value doesn't exist yet
							vector<string> tmp3;
							tmp3.push_back(tab1[j][0]);
							newRow.push_back(tab1[j][0]);
							onion.addRow(tmp3);
						}
						if(t2flag != 1){
							vector<string> tmp3;
							tmp3.push_back(tab2[ii][0]);
							newRow.push_back(tab2[ii][0]);
							onion.addRow(tmp3);
						}
					}
				}
			}
		}

	}
	return onion;	// returns the union if compatible and and empty table otherwise
}

// DIFFERENCE /****WORKING****/
Table Difference(string newName, string tabName1, string tabName2, vector<Table> database) {
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
	/***********************************************************************/
	//           SEE TESTING CODE BELOW-THIS CODE DIDN'T WORK PROPERLY     //
	/***********************************************************************/
	
	// execute the difference of tab1 and tab2 (tab1 - tab2)
	/*bool addrow;
	for(size_t i = 0; i<tab1[0].getSize(); i++) {	// iterates down the first column of tab1
		addrow = true;
		vector<string> row1;
		vector<string> finalRow;
		for(size_t j = 0; j<tab1.size(); j++) {	// iterates across each row of tab1
			row1.push_back(tab1[j][i]);
			//cout << row1[j];
		}
		for(size_t i = 0; i<tab1[0].getSize(); i++) {	// iterates down the first column of tab2
			vector<string> row2;
			for(size_t j = 0; j<tab2.size(); j++) {	// iterates across each row of tab2
				row2.push_back(tab2[j][i]);
				//cout << row2[j];
			}
			if(row1==row2) {		// compare row1 with row2
				finalRow.push_back("");		// if row1 equals row2, row1 will not be in the difference table
			}
		}
		if(addrow) {
			difference.addRow(finalRow);
		}	
	}*/

	///////////////////////////////////////////////////////
	//                TESTING DIFFERENT CODE             //
	///////////////////////////////////////////////////////
	/*************** Proper Output ***********************/
	vector<string> testrow;
	for (size_t i = 0; i < tab1[0].getSize(); i++){
		for (size_t j = 0; j < tab2.size(); j++){
			if (tab1[j][i] != tab2[j][i]){
				testrow.push_back(tab1[j][i]);
			} else {
				testrow.push_back("");                     //Currently inputs blanks for when values are same
			}
		}
	}
	difference.addRow(testrow);
	return difference;	// returns the union if compatible and and empty table otherwise
}

//Product    /*****KIND OF WORKING****/
Table Product (string newName, string tabName1, string tabName2, vector<Table> database){
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

	Table product;

	for(size_t i = 0; i<tab1[0].getSize(); i++) { //iterate down first column of table 1
		vector<string> newRow;
		vector<string> newColumns;
		vector<string> colNames;
		for(size_t j = 0; j<tab1.size(); j++){    //iterate across row using number of columns 3 col = 3 rows
			for(size_t k = 0; k < tab2[0].getSize(); k++) { // iterate down first column of table 2
				for(size_t ii = 0; ii<tab2.size(); ii++){ // iterate through rows of column
					newColumns.push_back("type T");       /***pushes back a new column for every row**/
					colNames.push_back("name");           /***in order for addRow function to work***/
					newRow.push_back(tab1[j][0]);        //push value of current row of tab1 with every row of current tab2.
					cout << tab1[j][0] << "\n\r";
					newColumns.push_back("type T");     /******************************************/
					colNames.push_back("name");         //      set second brackets to 0 so       //
					newRow.push_back(tab2[ii][0]);      //      that doesn't go outside of range  //
					cout << tab2[ii][0]<< "\n\r";       /******************************************/
				}
			}
		}
		product = Table(newName, colNames, newColumns, primaryKeys);
		product.addRow(newRow);
	}
	return product; // returns product
}

//Join /*****WORKING*****/
Table Join(string newName, string tabName1, string tabName2, vector<Table> database) {
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
	
	
	/*******************************************************/
	//           MEMORY ISSUES                             //
	/*******************************************************/
	// execute the joining of tab1 and tab2 
	/*bool addrow;
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
	}*/
	/****************************************************/
	// CURRENT WORKING CODE SIMILAR TO DIFFERENCE       //
	// FUNCTION BUT IT MAKES SURE THEY HAVE SAME        //
	// ELEMENTS.                                        //
	/****************************************************/
	Table join;
	for(size_t i = 0; i<tab1[0].getSize(); i++) { //iterate down first column of table 1
		vector<string> newRow;
		vector<string> newColumns;
		vector<string> colNames;
		for(size_t j = 0; j<tab1.size(); j++){    //iterate across row using number of columns 3 col = 3 rows
			for(size_t k = 0; k < tab2[0].getSize(); k++) { // iterate down first column of table 2
				for(size_t ii = 0; ii<tab2.size(); ii++){ // iterate through rows of column
					if(tab1[j][0] == tab2[ii][0])
					{
						newColumns.push_back("type T");       /***pushes back a new column for every row**/
						colNames.push_back("name");           /***in order for addRow function to work***/
						newRow.push_back(tab1[j][0]);        //push value of current row of tab1 with every row of current tab2.
						cout << tab1[j][0] << "\n\r";
						newColumns.push_back("type T");     /******************************************/
						colNames.push_back("name");         //      set second brackets to 0 so       //
						newRow.push_back(tab2[ii][0]);      //      that doesn't go outside of range  //
						cout << tab2[ii][0]<< "\n\r";       /******************************************/
					}
				}
			}
		}
		join = Table(newName, colNames, newColumns, primaryKeys);
		join.addRow(newRow);
	}
		
		
	return join;	// returns the union if compatible and and empty table otherwise
}

void Show(string name, vector<Table> database){
	for (size_t i = 0; i<database.size(); ++i){ //typical "find the table"
		if (database[i].getName().compare(name) == 0){
			cout << database[i];
		}
	}
}

void writeTable(Table IN_table) {}

void openTable(Table IN_table) {}

void createRelationTable(string IN_name, string IN_commands) {}

void insertFromRelation(string IN_name, string IN_relation) {}

void deleteData(string IN_name, string IN_relation) {}

void parser(string IN_string){
	IN_string += "      ";
	if(IN_string.substr(0,6).compare("CREATE") == 0){ // do this
		string name;
		vector<string> colNames;
		vector<string> colTypes;
		vector<string> primaryKeys;
		size_t locTABLE = 0;
		locTABLE = IN_string.find("TABLE");
		if(locTABLE != string::npos){
			if(IN_string.find(' ',locTABLE+6) == string::npos){
				cout << "Argument list of bad form. (E448)\n";
				return;
			}
			name = IN_string.substr(locTABLE+6,IN_string.find(' ',locTABLE+6)-(locTABLE+6));
			//cout << "Name: \"" << name << "\"\n";
		} else{
			cout << "Please specify a name. (E454)\n";
			return;
		}
		size_t locColParenthesis = 0;
		size_t locColName = 0;
		size_t locColType = 0;
		if(IN_string.find("(",locTABLE) == string::npos){
			cout << "Argument list of bad form. (E461)\n";
			return;
		}
		locColParenthesis = IN_string.find("(",locTABLE) + 1;
		for(;;){
			//cout << "In for loop - ";
			locColName = IN_string.find(' ',locColParenthesis);
			colNames.push_back(IN_string.substr(locColParenthesis,locColName-locColParenthesis));
			if(IN_string.find(',',locColName) == string::npos && IN_string.find(')',locColName) == string::npos){
				cout << "Argument list of bad form. (E470)\n";
				//cout << locColName << " - " << 
				return;
			} else if(IN_string.find(',',locColName) < IN_string.rfind(')',locColName)){
				//cout << locColParenthesis << " (->) ";
				locColType = IN_string.find(',',locColName);
				colTypes.push_back(IN_string.substr(locColName+1,locColType-(locColName+1)));
				locColParenthesis = locColType+2;
				//cout << locColName << " - " << locColType << " (->) " << locColParenthesis << endl;
			} else{
				//cout << locColParenthesis << " (->) ";
				locColType = IN_string.find(')',locColName);
				colTypes.push_back(IN_string.substr(locColName+1,locColType-(locColName+1)));
				//cout << locColName << " - " << locColType << " (->) x" << endl;
				break;
			}
		}
		//cout << colNames << endl << colTypes << endl;
		size_t locPRIMARYKEY = 0;
		if(IN_string.find("PRIMARY KEY") == string::npos){
			cout << "Please specify a primary key. (E490)\n";
			return;
		}
		locPRIMARYKEY = IN_string.find("PRIMARY KEY")+13;
		size_t locNextPRIMARYKEY = 0;
		for(;;){
			if(IN_string.find(',',locPRIMARYKEY) == string::npos && IN_string.find(')',locPRIMARYKEY) == string::npos){
				cout << "Argument list of bad form. (E497)\n";
				return;
			}
			if(IN_string.find(',',locPRIMARYKEY) < IN_string.find(')',locPRIMARYKEY)){
				locNextPRIMARYKEY = IN_string.find(',',locPRIMARYKEY);
				string tempPRIMARYKEY = IN_string.substr(locPRIMARYKEY,locNextPRIMARYKEY-locPRIMARYKEY);
				bool foundPRIMARYKEY = false;
				for(int i=0; i<colNames.size(); ++i){
					if(colNames[i].compare(tempPRIMARYKEY) == 0){
						primaryKeys.push_back(tempPRIMARYKEY);
						foundPRIMARYKEY = true;
						break;
					}
				}
				if(!foundPRIMARYKEY){
					cout << "Primary Key Mismatch (E512)\n";
					return;
				}
				locNextPRIMARYKEY += 2;
			} else {
				locNextPRIMARYKEY = IN_string.find(')',locPRIMARYKEY);
				primaryKeys.push_back(IN_string.substr(locPRIMARYKEY,locNextPRIMARYKEY-locPRIMARYKEY));
				break;
			}
		}
		//cout << primaryKeys << endl;
		database.push_back(Table(name,colNames,colTypes,primaryKeys));
		return;
		
	} else if(IN_string.substr(0,6).compare("INSERT") == 0){ // do this
		if(IN_string.find("INTO") == string::npos){
			cout << "Specify a table to insert values into (E527)\n";
			return;
		}
		size_t locINTO = IN_string.find("INTO")+5;
		if(IN_string.find(' ',locINTO) == string::npos){
			cout << "Argument list of bad form. (E532)\n";
			return;
		}
		string targetTable = IN_string.substr(locINTO,IN_string.find(' ',locINTO)-locINTO);
		bool targetFound = false;
		int targetLocation = -1;
		for(int i=0; i<database.size(); ++i){
			if(database[i].getName().compare(targetTable) == 0){
				targetLocation = i;
				targetFound = true;
				break;
			}
		}
		if(!targetFound) {
			cout << "Table not found. (E546)\n";
			return;
		}
		if(IN_string.find("VALUES FROM ") == string::npos){
			cout << "Specify values to insert. (E550)\n";
			return;
		}
		size_t locVALUESFROM = IN_string.find("VALUES FROM ")+12;
		if(IN_string.substr(locVALUESFROM,8).compare("RELATION") == 0){
			insertFromRelation(targetTable,IN_string.substr(locVALUESFROM+9,IN_string.rfind(';')-(locVALUESFROM+9)));
			return;
		} else {
			locVALUESFROM++;
			vector<string> getValues;
			while(IN_string.find(',',locVALUESFROM) != string::npos){
				getValues.push_back(IN_string.substr(locVALUESFROM,IN_string.find(',',locVALUESFROM)-locVALUESFROM));
				locVALUESFROM = IN_string.find(',',locVALUESFROM)+2;
			}
			getValues.push_back(IN_string.substr(locVALUESFROM,IN_string.find(')',locVALUESFROM)-locVALUESFROM));
			if(database[targetLocation].addRow(getValues) == -1){
				cout << "Column/Data Mismatch (E566)\n";
				return;
			}
			return;
		}
	} else if(IN_string.substr(0,4).compare("SHOW") == 0){
		string inTable = IN_string.substr(5,IN_string.rfind(";"));
		for(int i=0; i<database.size(); ++i){
			if(database[i].getName().compare(inTable) == 0) {
				//cout << database[i] << endl;
				return;
			}
		}
		cout << "No such table exists (E579)\n";
		return;
	} else if(IN_string.substr(0,5).compare("WRITE") == 0){ // do this
		string inTable = IN_string.substr(6,IN_string.rfind(";"));
		for(int i=0; i<database.size(); ++i){
			if(database[i].getName().compare(inTable) == 0) {
				writeTable(database[i]);
				return;
			}
		}
		cout << "No such table exists (E589)\n";
		return;
	} else if(IN_string.substr(0,4).compare("OPEN") == 0){ // do this
		string inTable = IN_string.substr(5,IN_string.rfind(";"));
		for(int i=0; i<database.size(); ++i){
			if(database[i].getName().compare(inTable) == 0) {
				openTable(database[i]);
				return;
			}
		}
		cout << "No such table exists (E599)\n";
		return;
	} else if(IN_string.substr(0,6).compare("DELETE") == 0){ // do this
		if(IN_string.find("FROM") == string::npos){
			cout << "Specify a table (E603)\n";
			return;
		}
		size_t locFROM = IN_string.find("FROM")+5;
		if(IN_string.find(' ',locFROM) == string::npos){
			cout << "Argument list of bad form. (E608)\n";
			return;
		}
		string targetTable = IN_string.substr(locFROM,IN_string.find(' ',locFROM)-locFROM);
		bool targetFound = false;
		int targetLocation = -1;
		for(int i=0; i<database.size(); ++i){
			if(database[i].getName().compare(targetTable) == 0){
				targetLocation = i;
				targetFound = true;
				break;
			}
		}
		if(!targetFound) {
			cout << "Table not found. (E622)\n";
			return;
		}
		if(IN_string.find("WHERE") == string::npos){
			cout << "Specify a relation (E626)\n";
			return;
		}
		size_t locWHERE = IN_string.find("WHERE")+6;
		string getCondition = IN_string.substr(locWHERE,IN_string.rfind(';')-locWHERE);
		deleteData(targetTable, getCondition);
		return;
		
	} else if(IN_string.find("<-") > 1){
		size_t locArrow = IN_string.find("<-");
		string tempName = IN_string.substr(0,locArrow-1);
		string tempCommand = IN_string.substr(locArrow+3,IN_string.length());
		createRelationTable(tempName,tempCommand);
	} else {
		cout << "Invalid command. (E640)\n";
		return;
	}
	cout << "Invalid command. (E643)\n";
}


int main(){
	printf("WELCOME TO THE DBMS!\n");
	for(;;){
		printf(">");
		string commandIN;
		getline(cin,commandIN);
		parser(commandIN);
	}
}
