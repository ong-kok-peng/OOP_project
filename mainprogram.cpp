#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#include "Schedule.h"

Schedule schedule;

//function prototypes
void showMenu();
void clearTerminal();

void showMenu() {
    while (true) {
        int option;

        cout << "\n-----------------------------------------------------";
        cout << "\n------- Freight & Cargo Scheduler -------------------\n";
        cout << "1. Work with Freight data.\n";
        cout << "2. Work with Cargo data.\n";
        cout << "3. Generate flight schedule.\n";
        cout << "4. View generated flight schedule.\n";
        cout << "5. Save generated flight schedule to file.\n";
        cout << "6. Clear terminal screen.\n";
        cout << "7. Exit program.\n";
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
        case 2:
            schedule.gotoDataMode(option);
            break;
        case 6:
            clearTerminal();
            break;
        case 7:
            cout << "\nProgram is terminated. Goodbye!\n";
            exit(0);
        default:
            cout << "\nInvalid option, please type any number from 1 to 7.\n";
            continue;
        }
    }
}

void clearTerminal() {
    #ifdef _WIN32
        system("cls");
    #elif __linux__
        system("clear");
    #endif
        showMenu();
}

int main() {
    showMenu();
    return 0;
}
