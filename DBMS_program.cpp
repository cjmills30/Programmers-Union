#include "std_lib_facilities_4.h"
#include <string>
#include <iostream>
#include "DBMS.h"

vector<Table> database;

int main(){
	//Parser goes here.
	int type = 0;
	//"type" will emulate parser for time being.
	printf("WELCOME TO THE DBMS!\n");

	/***********************************************************************/
	//Tables for testing
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
		vector<string> row1;
		row1.push_back("1");
		row1.push_back("2");
		row1.push_back("3");
		//actual work
		database.push_back(Table(name,colNames,colTypes,primaryKeys));
		database[0].addRow(row1);

		string name2 = "test table 2";
		vector<string> colNames2;
		colNames2.push_back("Col12");
		colNames2.push_back("Col22");
		colNames2.push_back("Col32");
		vector<string> colTypes2;
		colTypes2.push_back("int");
		colTypes2.push_back("char(40)");
		colTypes2.push_back("int");
		vector<string> primaryKeys2;
		primaryKeys2.push_back("Col12");
		vector<string> row2;
		row2.push_back("4");
		row2.push_back("5");
		row2.push_back("6");
		//actual work
		database.push_back(Table(name2,colNames2,colTypes2,primaryKeys2));
		database[1].addRow(row2);

		string name3 = "test table 3";
		vector<string> colNames3;
		colNames3.push_back("Col1");
		colNames3.push_back("Col2");
		colNames3.push_back("Col3");
		vector<string> colTypes3;
		colTypes3.push_back("int");
		colTypes3.push_back("char(40)");
		colTypes3.push_back("int");
		vector<string> primaryKeys3;
		primaryKeys3.push_back("Col3");
		vector<string> row3;
		row3.push_back("6");
		row3.push_back("2");
		row3.push_back("4");
		//actual work
		database.push_back(Table(name3, colNames3, colTypes3, primaryKeys3));
		database[2].addRow(row3);

		cout<<database.size()<<" tables automatically created\n";

		//cout<<"0: Creates another table called test table\n\r";
		//cout<<"1: Will drop or remove test table\n\r";
		//cout<<"2: Will add a new row everytime with random numbers to every table called test table\n\r";
		cout<<"3: Will display current test table\n\r";
		cout<<"9: testing DIFFERENCE FUNCTION of tab vs. tab 3\n\r";
	
	while(1){
		int rnd1 = rand() %100 + 1;
		int rnd2 = rand() %100 + 1;

		printf("Type a number for options\n\r");
		cin>>type;
	/*if(type == 0){
		//CREATE TABLE tabname (name VARCHAR(20), years INTEGER) PRIMARY KEY (name)
		string name = "test table"; //table being created
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
		cout<<database.size()<<" tables now live\n\r";
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
		cout<<"test table removed!\n\r";
	} else if(type == 2){
		//INSERT INTO relation-name VALUES FROM (T, T, T)
		string rndint1, rndint2;
		rndint1 = to_string(rnd1);
		rndint2 = to_string(rnd2);
		string name = "test table";
		vector<string> row;
		row.push_back(rndint1);
		row.push_back("Col2Cell");
		row.push_back(rndint2);
		//actual work
		for(size_t i = 0; i<database.size(); i++){ //typical "find the table"
			if(database[i].getName().compare(name) == 0){
				if(database[i].addRow(row) == -1){
					cout << "Tried to add bad row";
				}
			}
		}
	}*/
	if (type == 3){
		//SHOW tabname
		string name = "test table";
		for (int i = 0; i < database.size(); i++){
			Show(database[i].getName(), database);
	}
		
	} /*else if(type == 4) {
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
	} else if(type == 5) { 
		string name = "selection table";
		string condition = "Col2Cell";
		string tabName = "test table 2";

		//Select(name, condition, tabName);

		
	}*/ else if(type == 9){ //exit
		string diffTab = "Difference Table";
		string tab1, tab2;
		tab1 = "test table";
		tab2 = "test table 3";
		cout << Difference(diffTab, tab1, tab2, database);
	}
	
	}
}

