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
            cout << "Program terminated by user.\n";
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

    // Column headers
    cout << left
         << setw(6) << "Row"
         << setw(10) << "CargoID"
         << setw(12) << "FreightID"
         << setw(15) << "Description"
         << setw(10) << "Weight"
         << endl;

    for (size_t r = 0; r < cargoinfo.size(); ++r) {
        cout << left
             << setw(6) << (r + 1)
             << setw(10) << cargoinfo[r][0]     // CargoID
             << setw(12) << cargoinfo[r][1]     // FreightID
             << setw(15) << cargoinfo[r][2]     // Description
             << setw(10) << cargoinfo[r][3]     // Weight
             << endl;
    }

    cout << endl;
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
    string cargoID, freightID, description, weight;

    cout << "\nEnter new CargoID: ";
    cin >> cargoID;

    for (auto& row : cargoinfo) {
        if (row.size() > 0 && row[0] == cargoID) {
            cout << "A cargo with ID \"" << cargoID << "\" already exists. Aborting.\n";
            return;
        }
    }

    cout << "Enter associated FreightID: ";
    cin >> freightID;
    cout << "Enter Description: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, description);

    cout << "Enter Weight (e.g., in kg): ";
    cin >> weight;
    cargoinfo.push_back({ cargoID, freightID, description, weight });
    cout << "New cargo record added successfully.\n";
}

void Cargo::delCargoInfo() {
    if (cargoinfo.empty()) {
        cout << "No cargo data to delete.\n";
        return;
    }

    string key;
    cout << "\nEnter the CargoID to delete: ";
    cin >> key;

    int indexToDelete = -1;
    for (int i = 0; i < (int)cargoinfo.size(); ++i) {
        if (cargoinfo[i][0] == key) {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete == -1) {
        cout << "CargoID \"" << key << "\" not found. Aborting deletion.\n";
        return;
    }
    cout << "\nThe following Cargo record will be deleted:\n";
    cout << "CargoID\tFreightID\tDescription\tWeight\n";
    for (size_t c = 0; c < cargoinfo[indexToDelete].size(); ++c) {
        cout << cargoinfo[indexToDelete][c] << "\t";
    }
    cout << "\n";

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
    if (cargoinfo.empty()) {
        cout << "No cargo data to edit.\n";
        return;
    }

    string key;
    cout << "\nEnter the CargoID to edit: ";
    cin >> key;

    int indexToEdit = -1;
    for (int i = 0; i < (int)cargoinfo.size(); ++i) {
        if (cargoinfo[i][0] == key) {
            indexToEdit = i;
            break;
        }
    }

    if (indexToEdit == -1) {
        cout << "CargoID \"" << key << "\" not found. Aborting edit.\n";
        return;
    }

    cout << "\nCurrent record:\n";
    cout << "1) CargoID:   " << cargoinfo[indexToEdit][0] << "\n";
    cout << "2) FreightID: " << cargoinfo[indexToEdit][1] << "\n";
    cout << "3) Description: " << cargoinfo[indexToEdit][2] << "\n";
    cout << "4) Weight:     " << cargoinfo[indexToEdit][3] << "\n";

    cout << "\nEnter the number of the field you want to edit (1–4), or 0 to cancel: ";
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice) {
        case 0:
            cout << "Edit canceled.\n";
            return;
        case 1: {
            string newVal;
            cout << "Enter new CargoID: ";
            getline(cin, newVal);
            cargoinfo[indexToEdit][0] = newVal;
            cout << "CargoID updated.\n";
            break;
        }
        case 2: {
            string newVal;
            cout << "Enter new FreightID: ";
            getline(cin, newVal);
            cargoinfo[indexToEdit][1] = newVal;
            cout << "FreightID updated.\n";
            break;
        }
        case 3: {
            string newVal;
            cout << "Enter new Description: ";
            getline(cin, newVal);
            cargoinfo[indexToEdit][2] = newVal;
            cout << "Description updated.\n";
            break;
        }
        case 4: {
            string newVal;
            cout << "Enter new Weight: ";
            getline(cin, newVal);
            cargoinfo[indexToEdit][3] = newVal;
            cout << "Weight updated.\n";
            break;
        }
        default:
            cout << "Invalid option. No changes made.\n";
    }
}
