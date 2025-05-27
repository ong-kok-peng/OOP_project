#ifndef FREIGHT_H
#define FREIGHT_H

class Freight {
private:
	string filename;
	ifstream inputfile;
	string textline;
public:
	vector<vector<string>> freightinfo;
	void openFile();
	void dispFreightInfo();
};

#endif // !FREIGHT_H
