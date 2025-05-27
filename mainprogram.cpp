#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#include "Freight.h"

Freight freight;

//function prototypes
void showMenu();
void dispInfo();
void addInfo();
void delInfo();
void editInfo();

void showMenu() {
    while (true) {
        int option;

        cout << "\n-------- Please select an option ---------\n";
        cout << "1. Display freight/cargo information.\n";
        cout << "2. Add freight/cargo information.\n";
        cout << "3. Delete freight/cargo information.\n";
        cout << "4. Edit freight/cargo information.\n";
        cout << "5. Generate flight schduele.\n";
        cout << "6. Exit program.\n";

        cin >> option;

        switch (option) {
        case 1:
            dispInfo();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 6:
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

        switch (option) {
        case 1:
            freight.dispFreightInfo();
            break;
        case 2:
            break;
        case 3:
            showMenu();
        default:
            cout << "Invalid option, please type any number from 1 to 3.\n";
        }
    }
}

void addInfo() {

}

void delInfo() {

}

void editInfo() {

}

int main() {
    freight.openFile();

    if (freight.freightinfo.size() > 0) {
        showMenu();
    }
    
    return 0;
}