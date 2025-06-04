#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#include "Freight.h"

void Freight::openFile() {
    string filename;
    ifstream inputfile;
    string textline;

    while (!inputfile.is_open()) {
        cout << "What is the file name for the Freight information?\nMake sure filename has no spaces. If theres a space put an underscore.\n";
        cout << "To cancel, type \"EXIT\" to terminate the program.\n\n-> ";
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
                    substr.erase(substr.find_last_not_of(" \t\r\n") + 1);
                    freightinfo[a].push_back(substr);
                }
                a++;
            }
        }
        else if (filename.compare("EXIT") == 0) {
            cout << "Program is terminated. Goodbye!\n";
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
            if (col == 1 && freightinfo[row][col].length() <= 7) {
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
    string freightID, destination, time;
    string textline;

    while (true) {
        cout << "\nEnter the freight ID, destination and time, separated with a comma in between.\n-> ";
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

        if (paramcount == 0) { freightID = substr; }
        else if (paramcount == 1) { destination = substr; }
        else if (paramcount == 2) { time = substr; }
        paramcount++;
    }

    if (paramcount == 3) {
        //check if freight already exist
        for (auto& row : freightinfo) {
            if (row.size() > 0 && row[0] == freightID) {
                cout << "A freight with ID \"" << freightID << "\" already exists.\n";
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
        freightinfo.push_back({ freightID, destination, time });

        // Display updated freight info
        cout << "New freight record added!\n\n";
        dispFreightInfo();
    }
    else {
        cout << "One or more parameters is missing.\n";
        return;
    }
}

void Freight::delFreightInfo() {
    string id;

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
        return;
    }

    // Show info to confirm deletion
    cout << "The following record will be deleted:\n\n";
    cout << "ID\tDestination\tTime\n";
    for (int col = 0; col < 3; col++) {
        if (col == 1 && freightinfo[indexToDelete][col].length() <= 7) {
            cout << freightinfo[indexToDelete][col] << "\t\t";
        }
        else {
            cout << freightinfo[indexToDelete][col] << "\t";
        }
    }

    while (true) {
        cout << "\nAre you sure you want to delete the following freight record? (Y/N)\n";
        cout << "-> ";

        char confirm;
        cin >> confirm;

        if (cin.fail()) {
            cout << "Invalid input. Please enter 'Y' / 'y' / 'N' / 'n'.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (confirm == 'Y' || confirm == 'y') {
            freightinfo.erase(freightinfo.begin() + indexToDelete);
            cout << "Freight info deleted successfully!\n\n";

            // Display updated freight info
            dispFreightInfo();
            break;
        }
        else if (confirm == 'N' || confirm == 'n') {
            cout << "Deletion cancelled.\n";
            break;
        }
        else {
            cout << "Invalid option, Please enter 'Y' / 'y' / 'N' / 'n'.\n";
            continue;
        }
    }
    
}

void Freight::editFreightInfo() {
    string id;
    cout << "\nEnter freight ID to edit:\n-> ";
    cin >> id;

    int indexToEdit = -1;
    for (int i = 0; i < freightinfo.size(); i++) {
        if (freightinfo[i][0] == id) {
            indexToEdit = i;
            break;
        }
    }

    if (indexToEdit == -1) {
        cout << "Freight ID " << id << " not found! Please enter an existing freight ID.\n";
        return;
    }

    cout << "Record found:\n";
    cout << "ID\tDestination\tTime\n";
    for (int col = 0; col < 3; col++) {
        if (col == 1 && freightinfo[indexToEdit][col].length() <= 7) {
            cout << freightinfo[indexToEdit][col] << "\t\t";
        }
        else {
            cout << freightinfo[indexToEdit][col] << "\t";
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

        freightinfo[indexToEdit][fieldChoice - 1] = newValue;
        cout << "Record updated successfully!\n\n";
        dispFreightInfo();
        continue;
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
        cout << "Freight information sorted in ascending time order!\n";
    }
}
