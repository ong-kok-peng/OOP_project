#ifndef FREIGHT_H
#define FREIGHT_H

class Freight {
private:
	vector<vector<string>> freightinfo;
public:
	void openFile();
	vector<vector<string>> getfreightInfo();
	void dispFreightInfo();
	void sortFreightInfo();
	void addFreightInfo();
	void delFreightInfo();
	void editFreightInfo();
};

#endif // !FREIGHT_H
