#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

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
                    substr.erase(0, substr.find_first_not_of(" \t\r\n"));
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

void Freight::addFreightInfo() {
    string id, destination, time;

    cout << "\nEnter freight ID\n-> ";
    cin >> id;
    cout << "Enter Destination\n-> ";
    cin.ignore(); // to flush newline left in input buffer
    getline(cin, destination);
    cout << "Enter Time\n-> ";
    cin >> time;

    // Add the new row to freightinfo
    freightinfo.push_back({ id, destination, time });

    // Display updated freight info
    cout << "\n------------ Freight Information ------------\n\n";
    cout << "Row\tID\tDestination\tTime\n";
    for (int row = 0; row < freightinfo.size(); row++) {
        cout << (row + 1) << "\t";
        for (int col = 0; col < freightinfo[row].size(); col++) {
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

void Freight::delFreightInfo() {
    string id;
    while (true) {
        cout << "\nEnter freight ID\n-> ";
        cin >> id;

        // Search for the freight ID
        int indexToDelete = -1;
        for (int i = 0; i < freightinfo.size(); i++) {
            if (freightinfo[i][0] == id) {
                indexToDelete = i;
                break;
            }
        }

        if (indexToDelete == -1) {
            cout << "Freight info not found! Please enter an existing freight ID\n";
            break;
        }

        // Show info to confirm deletion
        cout << "Are you sure you want to delete the following freight info? (Y/N)\n";
        cout << "ID\tDestination\tTime\n";
        cout << freightinfo[indexToDelete][0] << "\t"
            << freightinfo[indexToDelete][1] << "\t\t"
            << freightinfo[indexToDelete][2] << "\n-> ";

        string confirm;
        cin >> confirm;
        if (confirm == "Y" || confirm == "y") {
            freightinfo.erase(freightinfo.begin() + indexToDelete);
            cout << "Freight info deleted successfully!\n";

            // Display updated freight info
            cout << "\n------------ Freight Information ------------\n\n";
            cout << "Row\tID\tDestination\tTime\n";
            for (int row = 0; row < freightinfo.size(); row++) {
                cout << (row + 1) << "\t";
                for (int col = 0; col < freightinfo[row].size(); col++) {
                    if (col == 1 && freightinfo[row][col].length() <= 6) {
                        cout << freightinfo[row][col] << "\t\t";
                    }
                    else {
                        cout << freightinfo[row][col] << "\t";
                    }
                }
                cout << "\n";
            }

            break;
        }
        else {
            cout << "Deletion cancelled\n";
            break;
        }
    }
}

void Freight::sortFreightInfo() {
    //validate freightinfo all timestamps are valid before sorting them by ascending timestamp 
    bool validationOk = true;

    for (int row = 0; row < freightinfo.size(); row++) {
        try {
            int timestamp = stoi(freightinfo[row][2]);
            if (timestamp < 0 || timestamp > 2359) {
                cout << "Sorting failed because freight information contains an invalid time stamp at row " << (row + 1) << ".\n";
                validationOk = false; break;
            }
        }
        catch (const invalid_argument& e) {
            cout << "Sorting failed because freight information contains an invalid time stamp at row " << (row + 1) << ".\n";
            validationOk = false; break;
        }
    }

    if (validationOk) {
        sort(freightinfo.begin(), freightinfo.end(), [](const vector<string>& a, const vector<string>& b) {
            return stoi(a[2]) < stoi(b[2]);
            });
        cout << "Freight information sorted in ascending order!\n";
    }
}
