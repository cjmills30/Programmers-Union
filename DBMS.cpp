#include "std_lib_facilities_4.h"
#include <string>
#include <iostream>
#include "DBMS.h"

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

void Show(string name, vector<Table> database)
{
	for (size_t i = 0; i<database.size(); ++i){ //typical "find the table"
		if (database[i].getName().compare(name) == 0){
			cout << database[i];
		}
	}
}
