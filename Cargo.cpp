#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits> 
#include <iomanip>


using namespace std;

#include "cargo.h"

void Cargo::openFile() {
    string filename;
    ifstream inputfile;
    string textline;

    while (!inputfile.is_open()) {
        cout << "What is the file name for the Cargo information? (no spaces; use underscores if needed)\n";
        cout << "To cancel, type \"EXIT\".\n-> ";
        cin >> filename;
        if (filename == "EXIT") {
            cout << "Program is terminated. Goodbye!\n";
            exit(0);
        }

        inputfile.open(filename);
        if (inputfile.is_open()) {
            cout << "File \"" << filename << "\" opened successfully.\n\n";
            cargoinfo.clear();

            int row = 0;
            while (getline(inputfile, textline)) {
                stringstream ss(textline);
                cargoinfo.push_back({});
                while (ss.good()) {
                    string cell;
                    getline(ss, cell, ',');
                    cell.erase(0, cell.find_first_not_of(" \t\r\n"));
                    cell.erase(cell.find_last_not_of(" \t\r\n") + 1);
                    cargoinfo[row].push_back(cell);
                }
                ++row;
            }
        }
        else {
            cout << "Could not open \"" << filename << "\". Please try again.\n\n";
        }
    }

    if (inputfile.is_open()) {
        inputfile.close();
    }
}

vector<vector<string>> Cargo::getCargoInfo() {
    return cargoinfo;
}

void Cargo::dispCargoInfo() {
    cout << "\n--------- Cargo Information ---------\n\n";

    cout << "Row\tID\tDestination\tTime\n";
    for (int row = 0; row < cargoinfo.size(); row++) {
        cout << (row + 1) << "\t";
        for (int col = 0; col < cargoinfo[row].size(); col++) {
            //for destination string, print 2 tabs if too short
            if (col == 1 && cargoinfo[row][col].length() <= 7) {
                cout << cargoinfo[row][col] << "\t\t";
            }
            else {
                cout << cargoinfo[row][col] << "\t";
            }
        }
        cout << "\n";
    }
}


void Cargo::sortCargoInfo() {
    if (cargoinfo.empty()) {
        cout << "No cargo data to sort.\n";
        return;
    }

    sort(cargoinfo.begin(), cargoinfo.end(),
         [](const vector<string>& A, const vector<string>& B) {
             return A[0] < B[0];
         });

    cout << "Cargo records have been sorted by CargoID.\n";
}

void Cargo::addCargoInfo() {
    string cargoID, destination, time;
    string textline;

    while (true) {
        cout << "\nEnter the cargo ID, destination and time, separated with a comma in between.\n-> ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover newline
        getline(cin, textline);

        if (textline.empty()) {
            cout << "Empty input. Hit enter to re-input.\n";
        }
        else { break; }
    }

    stringstream ss(textline);
    int paramcount = 0;

    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        substr.erase(0, substr.find_first_not_of(" \t\r\n"));
        substr.erase(substr.find_last_not_of(" \t\r\n") + 1);

        if (paramcount == 0) { cargoID = substr; }
        else if (paramcount == 1) { destination = substr; }
        else if (paramcount == 2) { time = substr; }
        paramcount++;
    }

    if (paramcount == 3) {
        //check if cargo already exist
        for (auto& row : cargoinfo) {
            if (row.size() > 0 && row[0] == cargoID) {
                cout << "A cargo with ID \"" << cargoID << "\" already exists.\n";
                return;
            }
        }

        //validate time
        try {
            int timestamp = stoi(time);
            if (timestamp < 0 || timestamp > 2359) {
                cout << "Invalid time value. Must be between 0000 and 2359.\n";
                return;
            }
        }
        catch (const invalid_argument& e) {
            cout << "Invalid time value. Must be numeric.\n";
            return;
        }

        // Add the new row to freightinfo
        cargoinfo.push_back({ cargoID, destination, time });

        // Display updated freight info
        cout << "New freight record added!\n\n";
        dispCargoInfo();
    }
    else {
        cout << "One or more parameters is missing.\n";
        return;
    }
}

void Cargo::delCargoInfo() {
    string id;
    cout << "\nEnter the CargoID to delete: ";
    cin >> id;

    int indexToDelete = -1;
    for (int i = 0; i < (int)cargoinfo.size(); ++i) {
        if (cargoinfo[i][0] == id) {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete == -1) {
        cout << "Cargo ID " << id << " not found! Please enter an existing cargo ID.\n";
        return;
    }

    // Show info to confirm deletion
    cout << "The following record will be deleted:\n\n";
    cout << "ID\tDestination\tTime\n";
    for (int col = 0; col < 3; col++) {
        if (col == 1 && cargoinfo[indexToDelete][col].length() <= 7) {
            cout << cargoinfo[indexToDelete][col] << "\t\t";
        }
        else {
            cout << cargoinfo[indexToDelete][col] << "\t";
        }
    }

    while (true) {
        cout << "\nAre you sure you want to delete this Cargo record? (Y/N): ";
        char confirm;
        cin >> confirm;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (confirm == 'Y' || confirm == 'y') {
            cargoinfo.erase(cargoinfo.begin() + indexToDelete);
            cout << "Cargo record deleted.\n";
            return;
        }
        else if (confirm == 'N' || confirm == 'n') {
            cout << "Deletion canceled.\n";
            return;
        }
        else {
            cout << "Please enter 'Y' or 'N'.\n";
        }
    }
}

void Cargo::editCargoInfo() {
    string id;
    cout << "\nEnter the CargoID to edit: ";
    cin >> id;

    int indexToEdit = -1;
    for (int i = 0; i < (int)cargoinfo.size(); ++i) {
        if (cargoinfo[i][0] == id) {
            indexToEdit = i;
            break;
        }
    }

    if (indexToEdit == -1) {
        cout << "Cargo ID " << id << " not found! Please enter an existing cargo ID.\n";
        return;
    }

    cout << "Record found:\n";
    cout << "ID\tDestination\tTime\n";
    for (int col = 0; col < 3; col++) {
        if (col == 1 && cargoinfo[indexToEdit][col].length() <= 7) {
            cout << cargoinfo[indexToEdit][col] << "\t\t";
        }
        else {
            cout << cargoinfo[indexToEdit][col] << "\t";
        }
    }
    cout << "\n";

    while (true) {
        int fieldChoice;
        cout << "\nWhich field do you want to edit?\n";
        cout << "1. ID\n";
        cout << "2. Destination\n";
        cout << "3. Time\n";
        cout << "4. Cancel edit\n";
        cout << "-> ";
        cin >> fieldChoice;

        if (cin.fail() || fieldChoice < 1 || fieldChoice > 4) {
            cout << "Invalid option selected.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (fieldChoice == 4) {
            cout << "Edit cancelled.\n";
            break;
        }

        string newValue;
        while (true) {
            cout << "Enter new value: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover newline
            getline(cin, newValue);

            if (newValue.empty()) {
                cout << "Empty input. Hit enter to re-input.\n";
            }
            else { break; }
        }

        //Validate time
        if (fieldChoice == 3) {
            try {
                int timestamp = stoi(newValue);
                if (timestamp < 0 || timestamp > 2359) {
                    cout << "Invalid time value. Must be between 0000 and 2359.\n";
                    continue;
                }
            }
            catch (const invalid_argument& e) {
                cout << "Invalid time value. Must be numeric.\n";
                continue;
            }
        }

        cargoinfo[indexToEdit][fieldChoice - 1] = newValue;
        cout << "Record updated successfully!\n\n";
        dispCargoInfo();
        continue;
    }

    
}
