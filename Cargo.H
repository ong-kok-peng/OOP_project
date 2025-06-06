#ifndef CARGO_H
#define CARGO_H

class Cargo {
private:
    vector<vector<string>> info;

public:
    Cargo();
    vector<vector<string>> getInfo();

	virtual void openFile();
	virtual void dispInfo();
	virtual void sortInfo();
	virtual void addInfo();
	virtual void delInfo();
	virtual void editInfo();
};

#endif // CARGO_H
