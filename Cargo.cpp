#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#include "cargo.h"

Cargo::Cargo() {
    //default constructor, initialize variables
    info = {};
}

void Cargo::openFile() {
    string rawpath;
    ifstream inputfile;
    string textline;

    cout << "\n------------ Open Cargo Information ------------\n\n";
    cout << "Input file path to the cargo information file:\n";
    cout << "To go back, type \"CANCEL\".\n\n-> ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover newline
    getline(cin, rawpath);

    if (rawpath.compare("CANCEL") == 0) {
        cout << "\nFile open is cancelled.\n";
        return;
    }

    filesystem::path filepath = filesystem::path(rawpath).lexically_normal();
    filepath.make_preferred();

    //validate file path
    if (!filepath.is_absolute()) {
        cout << "\nInvalid file path. File path must be absolute.\n";
        return;
    }
    if (!filesystem::exists(filepath)) {
        cout << "\n" << filepath << " does not exist.\n";
        return;
    }
    string fileExtension = filepath.extension().string();
    if (fileExtension.compare(".txt") != 0 && fileExtension.compare(".csv") != 0) {
        cout << "\n" << filepath << " must be a .txt or .csv file.\n";
        return;
    }

    inputfile.open(filepath);

    if (inputfile.is_open()) {
        cout << "\n" << filepath << " opened successfully.\n\n";

        info.clear(); //erase all the information
        int a = 0;
        while (getline(inputfile, textline)) {
            stringstream ss(textline);
            info.push_back({});
            while (ss.good()) {
                string substr;
                getline(ss, substr, ',');
                substr.erase(0, substr.find_first_not_of(" \t\r\n"));
                substr.erase(substr.find_last_not_of(" \t\r\n") + 1);
                info[a].push_back(substr);
            }
            a++;
        }
    }
    else {
        cout << filepath << " is not found.\n\n";
    }

    if (inputfile.is_open()) { inputfile.close(); }
}

vector<vector<string>> Cargo::getInfo() {
    return info;
}

void Cargo::dispInfo() {
    cout << "\n------------ Display Cargo Information ------------\n\n";
    if (info.empty()) {
        cout << "Cargo information is not loaded. Open the Cargo information file first.\n";
        return;
    }

    cout << "Row\tID\tDestination\tTime\n";
    for (int row = 0; row < info.size(); row++) {
        cout << (row + 1) << "\t";
        for (int col = 0; col < info[row].size(); col++) {
            //for destination string, print 2 tabs if too short
            if (col == 1 && info[row][col].length() <= 7) {
                cout << info[row][col] << "\t\t";
            }
            else {
                cout << info[row][col] << "\t";
            }
        }
        cout << "\n";
    }
}


void Cargo::sortInfo() {
    cout << "\n------------ Sort Cargo Information ------------\n\n";
    if (info.empty()) {
        cout << "Cargo information is not loaded. Open the Cargo information file first.\n";
        return;
    }

    sort(info.begin(), info.end(),
         [](const vector<string>& A, const vector<string>& B) {
             return A[0] < B[0];
         });

    cout << "Cargo records have been sorted by CargoID.\n";
}

void Cargo::addInfo() {
    cout << "\n------------ Add Cargo Information ------------\n\n";
    if (info.empty()) {
        cout << "Cargo information is not loaded. Open the Cargo information file first.\n";
        return;
    }

    string cargoID, destination, time;
    string textline;

    while (true) {
        cout << "\nEnter the cargo ID, destination and time, separated with a comma in between.\n";
        cout << "To go back, type \"CANCEL\".\n\n-> ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover newline
        getline(cin, textline);

        if (textline.compare("CANCEL") == 0) {
            cout << "\nAdd cargo is cancelled.\n";
            return;
        }

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
        for (auto& row : info) {
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

        // Add the new row to Cargoinfo
        info.push_back({ cargoID, destination, time });

        // Display updated Cargo info
        cout << "New Cargo record added!\n\n";
        dispInfo();
    }
    else {
        cout << "Invalid input, or one or more parameters is missing.\n";
        return;
    }
}

void Cargo::delInfo() {
    cout << "\n------------ Delete Cargo Information ------------\n\n";
    if (info.empty()) {
        cout << "Cargo information is not loaded. Open the Cargo information file first.\n";
        return;
    }

    string id;
    cout << "\nEnter the Cargo ID to delete: ";
    cin >> id;

    int indexToDelete = -1;
    for (int i = 0; i < (int)info.size(); ++i) {
        if (info[i][0] == id) {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete == -1) {
        cout << "\nCargo ID " << id << " not found! Please enter an existing cargo ID.\n";
        return;
    }

    // Show info to confirm deletion
    cout << "The following record will be deleted:\n\n";
    cout << "ID\tDestination\tTime\n";
    for (int col = 0; col < 3; col++) {
        if (col == 1 && info[indexToDelete][col].length() <= 7) {
            cout << info[indexToDelete][col] << "\t\t";
        }
        else {
            cout << info[indexToDelete][col] << "\t";
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
            info.erase(info.begin() + indexToDelete);
            cout << "\nCargo record deleted.\n";
            return;
        }
        else if (confirm == 'N' || confirm == 'n') {
            cout << "\nDeletion canceled.\n";
            return;
        }
        else {
            cout << "\nInvalid option, Please enter 'Y' / 'y' / 'N' / 'n'.\n";
        }
    }
}

void Cargo::editInfo() {
    cout << "\n------------ Edit Cargo Information ------------\n\n";
    if (info.empty()) {
        cout << "Cargo information is not loaded. Open the Cargo information file first.\n";
        return;
    }

    string id;
    cout << "\nEnter the Cargo ID to edit: ";
    cin >> id;

    int indexToEdit = -1;
    for (int i = 0; i < (int)info.size(); ++i) {
        if (info[i][0] == id) {
            indexToEdit = i;
            break;
        }
    }

    if (indexToEdit == -1) {
        cout << "\nCargo ID " << id << " not found! Please enter an existing cargo ID.\n";
        return;
    }

    cout << "\nRecord found:\n";
    cout << "ID\tDestination\tTime\n";
    for (int col = 0; col < 3; col++) {
        if (col == 1 && info[indexToEdit][col].length() <= 7) {
            cout << info[indexToEdit][col] << "\t\t";
        }
        else {
            cout << info[indexToEdit][col] << "\t";
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
            cout << "\nInvalid option selected.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (fieldChoice == 4) {
            cout << "\nEdit cancelled.\n";
            break;
        }

        string newValue;
        while (true) {
            cout << "\nEnter new value: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover newline
            getline(cin, newValue);

            if (newValue.empty()) {
                cout << "\nEmpty input. Hit enter to re-input.\n";
            }
            else { break; }
        }

        //Validate time
        if (fieldChoice == 3) {
            try {
                int timestamp = stoi(newValue);
                if (timestamp < 0 || timestamp > 2359) {
                    cout << "\nInvalid time value. Must be between 0000 and 2359.\n";
                    continue;
                }
            }
            catch (const invalid_argument& e) {
                cout << "\nInvalid time value. Must be numeric.\n";
                continue;
            }
        }

        info[indexToEdit][fieldChoice - 1] = newValue;
        cout << "\nRecord updated successfully!\n\n";
        dispInfo();
        continue;
    }

    
}
