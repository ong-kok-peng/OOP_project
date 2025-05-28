#ifndef FREIGHT_H
#define FREIGHT_H

class Freight {
private:
	string filename;
	ifstream inputfile;
	string textline;
	vector<vector<string>> freightinfo;
public:
	void openFile();
	vector<vector<string>> getfreightInfo();
	void dispFreightInfo();
	//void addFreightInfo();
	//void delFreightInfo();
	//void editFreightInfo();
};

#endif // !FREIGHT_H
