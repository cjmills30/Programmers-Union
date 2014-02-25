#include "DBMS.h"

void execute(vector<string> & executeThis){
	for(int i=0; i<executeThis.size(); ++i){
		executeCommand(executeThis[i]);
	}
	executeThis.clear();
}

int main(){
	vector<string> commands;
	commands.push_back("CREATE TABLE Shop (name VARCHAR(20), product VARCHAR(20), rating INTEGER) PRIMARY KEY (name)");
	commands.push_back("CREATE TABLE Shopper (ID INTEGER, age INTEGER, shop VARCHAR(20)) PRIMARY KEY (ID)");
	commands.push_back("CREATE TABLE Product (ID INTEGER, name VARCHAR(20), located VARCHAR(20)) PRIMARY KEY (ID)"); 
	execute(commands);
	for(;;){
		int choice = 0;
		cout << "Welcome to the Shopping Mall DBMS!\n
				Select an option:\n
				\t1) Add to Table\n
				\t2) Show Table\n
				\t3) Reset Table\n
				\t4) Show Shops containing Products\n
				\t5) Show Shoppers who shop at a Shop\n
				\t6) Exit\n
				>"
		cin >> choice;
		switch(choice){
			case 1: cout << "Select a table:\n
							\t1) Shop\n
							\t2) Shopper\n
							\t3) Product\n
							>";
					cin >> choice;
					switch(choice){
						case 1: 
							string name;
							cout << "Name:\n";
							cin >> name;
							string product;
							cout << "Product:\n";
							cin >> product;
							int rating;
							cout << "Rating:\n";
							cin >> rating;
							commands.push_back("INSERT INTO Shop VALUES FROM (\"" + name + "\", \"" + product + "\", " + rating + ");");
							execute(commands);
							break;
						case 2:
							int ID;
							cout << "ID:\n";
							cin >> ID;
							int age;
							cout << "Age:\n";
							cin >> age;
							string shop;
							cout << "Shop:\n";
							cin >> shop;
							commands.push_back("INSERT INTO Shopper VALUES FROM (" + ID + ", " + age + ", \"" + shop + "\");");
							execute(commands);
							break;
						case 3:
							int ID;
							cout << "ID:\n";
							cin >> ID;
							string name;
							cout << "Name:\n";
							cin >> name;
							string located;
							cout << "Located at:\n";
							cin >> located;
							commands.push_back("INSERT INTO Product VALUES FROM (" + ID + ", \"" + name + "\", \"" + located + "\");");
							execute(commands);
							break;
						default:
							cout << "Bad table (E76)";
							break;
					}
					break;
			case 2: cout << "Select a table:\n
							\t1) Shop\n
							\t2) Shopper\n
							\t3) Product\n
							>";
					cin >> choice;
					switch(choice){
						case 1: 
							commands.push_back("SHOW Shop;");
							execute(commands);
							break;
						case 2:
							commands.push_back("SHOW Shopper;");
							execute(commands);
							break;
						case 3:
							commands.push_back("SHOW Product;");
							execute(commands);
							break;
						default:
							cout << "Bad table (E100)";
							break;
					}
					break;
					
			case 3: cout << "Select a table:\n
							\t1) Shop\n
							\t2) Shopper\n
							\t3) Product\n
							>";
					cin >> choice;
					switch(choice){
						case 1: 
							//delete table and create new one
							execute(commands);
							break;
						case 2:
							//delete table and create new one
							execute(commands);
							break;
						case 3:
							//delete table and create new one
							execute(commands);
							break;
						default:
							cout << "Bad table (E125)";
							break;
					}
					break;
			case 4: // command that creates a relation containing the combination
					// command that shows the new relation
					// command that deletes the table
					execute(commands);
					break;
			case 5: // command that creates a relation containing the combination
					// command that shows the new relation
					// command that deletes the table
					execute(commands);
					break;
			case 6: commands.push_back("EXIT;");
					execute(commands);
					break;
			default:cout << "Bad command. (E142)\n";
					break;
		}
		cout << "Command completed. Press enter to continue...\n";
		string s;
		getline(cin, s);
		cout << string(100, '\n');
	}
}