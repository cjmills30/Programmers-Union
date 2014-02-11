Table Select(string newName, string condition, string tabName);
Table Project(string newName, vector<string> columnNames, string tabName);
Table Rename(string newName, vector<string> columnNames, string tabName);
Table Union(string newName, string tabName1, string tabName2);
Table Difference(string newName, string tabName1, string tabName2);
Table Product (string newName, string tabName1, string tabName2);
Table Join(string newName, string tabName1, string tabName2);