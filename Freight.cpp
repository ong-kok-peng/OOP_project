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

void Freight::dispFreightInfo() {

}
