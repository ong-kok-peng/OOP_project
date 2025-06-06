#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#include "Schedule.h"

//declare constants for mode name macros
const string Schedule::FREIGHT_MODE = "freight";
const string Schedule::CARGO_MODE = "cargo";

Schedule::Schedule() {
    //default constructor
    dataMode = "";
}

void Schedule::gotoDataMode(int theChoice) {
    if (theChoice == 1) {
        dataMode = FREIGHT_MODE;
    }
    else if (theChoice == 2) {
        dataMode = CARGO_MODE;
    }
    showDataMenu();
}

void Schedule::showDataMenu() {
	if (!dataMode.empty()) {
        while (true) {
            int option;

            cout << "\n-----------------------------------------------------";
            cout << "\n------- Menu for " << dataMode << ": Please select an option ---------\n";
            cout << "1. Open/re-open " << dataMode << " information file\n";
            cout << "2. Display " << dataMode << " information.\n";
            cout << "3. Sort " << dataMode << " information.\n";
            cout << "4. Add " << dataMode << " information.\n";
            cout << "5. Delete " << dataMode << " information.\n";
            cout << "6. Edit " << dataMode << " Information.\n";
            cout << "7. Go back.\n";
            cout << "Option: ";

            cin >> option;

            if (cin.fail()) {
                cout << "\nInvalid input. Please enter any number from 1 to 7.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            switch (option) {
            case 1:
                openFile();
                break;
            case 2:
                dispInfo();
                break;
            case 3:
                sortInfo();
                break;
            case 4:
                addInfo();
                break;
            case 5:
                delInfo();
                break;
            case 6:
                editInfo();
                break;
            case 7:
                return;
                break;
            default:
                cout << "\nInvalid option, please type any number from 1 to 6.\n";
            }

        }
	}
}

void Schedule::openFile() {
    if (!dataMode.empty()) {
        if (dataMode.compare(FREIGHT_MODE) == 0) {
            Freight::openFile();
        }
        else if (dataMode.compare(CARGO_MODE) == 0) {
            Cargo::openFile();
        }
    }
}

void Schedule::dispInfo() {
    if (!dataMode.empty()) {
        if (dataMode.compare(FREIGHT_MODE) == 0) {
            Freight::dispInfo();
        }
        else if (dataMode.compare(CARGO_MODE) == 0) {
            Cargo::dispInfo();
        }
    }
}

void Schedule::sortInfo() {
    if (!dataMode.empty()) {
        if (dataMode.compare(FREIGHT_MODE) == 0) {
            Freight::sortInfo();
        }
        else if (dataMode.compare(CARGO_MODE) == 0) {
            Cargo::sortInfo();
        }
    }
}

void Schedule::addInfo() {
    if (!dataMode.empty()) {
        if (dataMode.compare(FREIGHT_MODE) == 0) {
            Freight::addInfo();
        }
        else if (dataMode.compare(CARGO_MODE) == 0) {
            Cargo::addInfo();
        }
    }
}

void Schedule::delInfo() {
    if (!dataMode.empty()) {
        if (dataMode.compare(FREIGHT_MODE) == 0) {
            Freight::delInfo();
        }
        else if (dataMode.compare(CARGO_MODE) == 0) {
            Cargo::delInfo();
        }
    }
}

void Schedule::editInfo() {
    if (!dataMode.empty()) {
        if (dataMode.compare(FREIGHT_MODE) == 0) {
            Freight::editInfo();
        }
        else if (dataMode.compare(CARGO_MODE) == 0) {
            Cargo::editInfo();
        }
    }
}