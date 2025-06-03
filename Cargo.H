#ifndef CARGO_H
#define CARGO_H

#include <vector>
#include <string>
using namespace std;

class Cargo {
private:
    vector<vector<string>> cargoinfo;

public:
    void openFile();

    vector<vector<string>> getCargoInfo();

    void dispCargoInfo();

    void sortCargoInfo();

    void addCargoInfo();

    void delCargoInfo();

    void editCargoInfo();
};

#endif // CARGO_H
