#ifndef FREIGHT_H
#define FREIGHT_H

class Freight {
private:
	vector<vector<string>> info;
public:
	Freight();
	vector<vector<string>> getInfo();

	virtual void openFile();
	virtual void dispInfo();
	virtual void sortInfo();
	virtual void addInfo();
	virtual void delInfo();
	virtual void editInfo();
};

#endif // !FREIGHT_H
