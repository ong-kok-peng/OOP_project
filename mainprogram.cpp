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

void showMenu() {
    while (true) {
        int option;

        cout << "\n-----------------------------------------------------";
        cout << "\n------- Freight & Cargo Scheduler -------------------\n";
        cout << "1. Work with Freight data.\n";
        cout << "2. Work with Cargo data.\n";
        cout << "3. Generate flight schedule.\n";
        cout << "4. Display generated flight schedule.\n";
        cout << "5. Save generated flight schedule to file.\n";
        cout << "6. Exit program.\n";
        cout << "Option: ";
        cin >> option;

        if (cin.fail()) {
            cout << "\nInvalid input. Please enter any number from 1 to 6.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (option) {
        case 1:
        case 2:
            schedule.clearTerminal();
            schedule.gotoDataMode(option);
            break;
        case 3:
            schedule.clearTerminal();
            schedule.generateSchedule();
            break;
        case 4:
            schedule.clearTerminal();
            schedule.dispSchedule();
            break;
        case 5:
            schedule.clearTerminal();
            schedule.saveSchedule();
            break;
        case 6:
            cout << "\nProgram is terminated. Goodbye!\n";
            exit(0);
        default:
            cout << "\nInvalid option, please type any number from 1 to 6.\n";
            continue;
        }
    }
}

int main() {
    showMenu();
    return 0;
}
