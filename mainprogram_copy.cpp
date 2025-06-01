#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#include "Freight.h"

Freight freight;
//Cargo cargo;

//function prototypes
void showMenu();
void dispInfo();
void addInfo();
void delInfo();
void editInfo();
void sortInfo();

void showMenu() {
    while (true) {
        int option;

        cout << "\n-------- Please select an option ---------\n";
        cout << "1. Display freight/cargo information.\n";
        cout << "2. Add freight/cargo information.\n";
        cout << "3. Delete freight/cargo information.\n";
        cout << "4. Edit freight/cargo information.\n";
        cout << "5. Sort freight/cargo information.\n";
        cout << "6. Generate flight schduele.\n";
        cout << "7. Exit program.\n";

        cin >> option;

        if (cin.fail()) {
            cout << "Invalid input. Please enter any number from 1 to 6.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (option) {
        case 1:
            dispInfo();
            break;
        case 2:
            addInfo();
            break;
        case 3:
            delInfo();
            break;
        case 4:
            break;
        case 5:
            sortInfo();
            break;
        case 6:
            break;
        case 7:
            cout << "Program is terminated.\n";
            exit(0);
        default:
            cout << "Invalid option, please type any number from 1 to 6.\n";
        }

    }
}

void dispInfo() {
    while (true) {
        int option;

        cout << "\n-------- Freight or Cargo? ---------\n";
        cout << "1. Freight\n";
        cout << "2. Cargo\n";
        cout << "3. Go back\n";

        cin >> option;

        if (cin.fail()) {
            cout << "Invalid input. Please enter any number from 1 to 3.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (option) {
        case 1:
            freight.dispFreightInfo();
            break;
        case 2:
            break;
            //cargo.dispCargoInfo();
        case 3:
            showMenu();
        default:
            cout << "Invalid option, please type any number from 1 to 3.\n";
        }
    }
}

void sortInfo() {
    while (true) {
        int option;

        cout << "\n-------- Freight or Cargo? ---------\n";
        cout << "1. Freight\n";
        cout << "2. Cargo\n";
        cout << "3. Go back\n";

        cin >> option;

        if (cin.fail()) {
            cout << "Invalid input. Please enter any number from 1 to 3.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (option) {
        case 1:
            freight.sortFreightInfo();
            break;
        case 2:
            break;
            //cargo.sortCargoInfo();
        case 3:
            showMenu();
        default:
            cout << "Invalid option, please type any number from 1 to 3.\n";
        }
    }
}

void addInfo() {
    while (true) {
        int option;

        cout << "\n-------- Freight or Cargo? ---------\n";
        cout << "1. Freight\n";
        cout << "2. Cargo\n";
        cout << "3. Go back\n";

        cin >> option;

        if (cin.fail()) {
            cout << "Invalid input. Please enter any number from 1 to 3.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (option) {
        case 1:
            freight.addFreightInfo();
            break;
        case 2:
            break;
            //cargo.sortCargoInfo();
        case 3:
            showMenu();
        default:
            cout << "Invalid option, please type any number from 1 to 3.\n";
        }
    }
}

void delInfo() {
    while (true) {
        int option;

        cout << "\n-------- Freight or Cargo? ---------\n";
        cout << "1. Freight\n";
        cout << "2. Cargo\n";
        cout << "3. Go back\n";

        cin >> option;

        if (cin.fail()) {
            cout << "Invalid input. Please enter any number from 1 to 3.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (option) {
        case 1:
            freight.delFreightInfo();
            break;
        case 2:
            break;
            //cargo.sortCargoInfo();
        case 3:
            showMenu();
        default:
            cout << "Invalid option, please type any number from 1 to 3.\n";
        }
    }
}

void editInfo() {

}

int main() {
    freight.openFile();
    //cargo.openFile();

    if (freight.getfreightInfo().size() > 0) {
        showMenu();
    }
    
    return 0;
}