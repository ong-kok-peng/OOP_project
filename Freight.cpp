#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#include "Freight.h"

void Freight::openFile() {
    while (!inputfile.is_open()) {
        cout << "What is the file name for the Freight information?\nMake sure filename has no spaces. If theres a space put an underscore.\n";
        cout << "To cancel, type \"EXIT\" to terminate the program.\n";
        cin >> filename;
        inputfile.open(filename);

        if (inputfile.is_open()) {
            cout << "File " << filename << " opened successfully.\n\n";
            
            freightinfo = {};
            int a = 0;
            while (getline(inputfile, textline)) {
                stringstream ss(textline);
                freightinfo.push_back({});
                while (ss.good()) {
                    string substr;
                    getline(ss, substr, ',');
                    freightinfo[a].push_back(substr);
                }
                a++;
            }
        }
        else if (filename.compare("EXIT") == 0) {
            cout << "Program is terminated.\n";
            exit(0);
        }
        else {
            cout << "File " << filename << " is not found.\n\n";
        }
    }

    if (inputfile.is_open()) { inputfile.close(); }
}

vector<vector<string>> Freight::getfreightInfo() {
    return freightinfo;
}

void Freight::dispFreightInfo() {
    cout << "\n------------ Freight Information ------------\n\n";
    cout << "Row\tID\tDestination\tTime\n";
    for (int row = 0; row < freightinfo.size(); row++) {
        cout << (row + 1) << "\t";
        for (int col = 0; col < freightinfo[row].size(); col++) {
            //for destination string, print 2 tabs if too short
            if (col == 1 && freightinfo[row][col].length() <= 6) {
                cout << freightinfo[row][col] << "\t\t";
            }
            else {
                cout << freightinfo[row][col] << "\t";
            }
        }
        cout << "\n";
    }
}
