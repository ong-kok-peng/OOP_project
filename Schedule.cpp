#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <unordered_map>
using namespace std;

#include "Schedule.h"

//declare constants for mode name macros
const string Schedule::FREIGHT_MODE = "freight";
const string Schedule::CARGO_MODE = "cargo";

Schedule::Schedule() {
    //default constructor, initialize variables
    dataMode = "";
    isScheduleGenerated = false;
    pairedFlights, unpairedCargo, unpairedFreight = {};
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
                clearTerminal();
                openFile();
                break;
            case 2:
                clearTerminal();
                dispInfo();
                break;
            case 3:
                clearTerminal();
                sortInfo();
                break;
            case 4:
                clearTerminal();
                addInfo();
                break;
            case 5:
                clearTerminal();
                delInfo();
                break;
            case 6:
                clearTerminal();
                editInfo();
                break;
            case 7:
                clearTerminal();
                return;
                break;
            default:
                cout << "\nInvalid option, please type any number from 1 to 6.\n";
            }

        }
	}
}

void Schedule::clearTerminal() {
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
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

void Schedule::generateSchedule() {
    cout << "\n--------------- Generate flight schedule ---------------\n";
    if (Freight::getInfo().empty() || Cargo::getInfo().empty()) {
        cout << "\nCargo or/and freight information is/are not loaded. Please open both information files first.\n";
        return;
    }

    //check if user already generated a schedule previously
    if (!isScheduleGenerated) {
        cout << "\nThere are " << Freight::getInfo().size() << " freight record(s) and " <<
            Cargo::getInfo().size() << " cargo record(s).\n";
        cout << "Confirm to generate flight schedule? (Y/N): ";
    }
    else {
        cout << "\nFlight schedule is previously already generated. Confirm to re-generate again? (Y/N): ";
    }

    char confirm;
    cin >> confirm;

    //check if user confirms to generate schedule. the code will return so long as confirm !=Y or y.
    if (cin.fail()) {
        cout << "\nInvalid input. Please enter 'Y' / 'y' / 'N' / 'n'.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if (confirm == 'N' || confirm == 'n') { return; }
    else if (confirm != 'Y' && confirm != 'y') {
        cout << "\nInvalid option, Please enter 'Y' / 'y' / 'N' / 'n'.\n";
        return;
    }

    //user picks Y or y; proceed to generate
    
    //firstly, erase all the matched and unmatched flight arrays 
    //and convert both freightinfo and cargoinfo vectors to unordered_list
    pairedFlights.clear(); unpairedFreight.clear(); unpairedCargo.clear();
    unordered_map<string, deque<string>> tmpFreightInfo, tmpCargoInfo;

    //each list elmement has key "(destination),(time)", and value {ID}
    for (const auto& row : Freight::getInfo()) tmpFreightInfo[row[1] + "," + row[2]].push_back(row[0]);
    for (const auto& row : Cargo::getInfo())   tmpCargoInfo[row[1] + "," + row[2]].push_back(row[0]);

    // match the freightIDs to the cargoIDs (values) based on the same time and destination (keys)
    // take the firstmost freight and cargo IDs to store in pairedFlights and remove from the maps
    // whatever IDs thats left in the maps are unpaired.

    cout << "\nGenerating flight schedule...\n\n";

    for (auto& [locationAndTime, freightIDs] : tmpFreightInfo) {
        //separate location and time values
        stringstream ss(locationAndTime);
        string location, time;
        getline(ss, location, ',');
        getline(ss, time, ',');

        auto iterator = tmpCargoInfo.find(locationAndTime);
        if (iterator == tmpCargoInfo.end()) {
            cout << "INFO: No matching cargo for freight heading to " << location << " at " << time << ".\n";
            continue;
        }
        auto& cargoIDs = iterator->second;

        int matchedFreightCount = 0;
        while (!freightIDs.empty() && !cargoIDs.empty()) {
            pairedFlights.push_back({freightIDs.front()+" <--> "+cargoIDs.front(), location, time});
            freightIDs.pop_front();
            cargoIDs.pop_front();
            matchedFreightCount++;
        }
        cout << "INFO: " << matchedFreightCount << " matching cargo for freight heading to " << location << " at " << time << ".\n";
    }

    //add the remaining unpaired freight 
    for (auto& [locationAndTime, freightIDs] : tmpFreightInfo) {
        //separate location and time values
        stringstream ss(locationAndTime);
        string location, time;
        getline(ss, location, ',');
        getline(ss, time, ',');

        while (!freightIDs.empty()) {
            unpairedFreight.push_back({freightIDs.front(), location, time});
            freightIDs.pop_front();
        }
    }

    //add the remaining unpaired cargo
    for (auto& [locationAndTime, cargoIDs] : tmpCargoInfo) {
        //separate location and time values
        stringstream ss(locationAndTime);
        string location, time;
        getline(ss, location, ',');
        getline(ss, time, ',');

        while (!cargoIDs.empty()) {
            unpairedCargo.push_back({ cargoIDs.front(), location, time });
            cargoIDs.pop_front();
        }
    }

    //wohooooo!! the end! 
    isScheduleGenerated = true;
    cout << "\nFlight schedule genrerated!\n";
    cout << "******** Statistics *********\n\n";
    cout << "No. of paired freight: " << (Freight::getInfo().size() - unpairedFreight.size()) << "\n";
    cout << "No. of unpaired freight: " << unpairedFreight.size() << "\n\n";
    cout << "No. of paired cargo: " << (Cargo::getInfo().size() - unpairedCargo.size()) << "\n";
    cout << "No. of unpaired cargo: " << unpairedCargo.size() << "\n\n";
}

void Schedule::dispSchedule() {
    cout << "\n--------------- Display flight schedule ---------------\n";
    if (!isScheduleGenerated) {
        cout << "\nFlight schedule is not generated yet.\n";
        return;
    }

    cout << "\n******* Paired flights schedule ********\n";
    cout << "Row\tIDs\t\tDestination\tTime\n";
    for (int row = 0; row < pairedFlights.size(); row++) {
        cout << (row + 1) << "\t";
        for (int col = 0; col < pairedFlights[row].size(); col++) {
            //for destination string, print 2 tabs if too short
            if (col == 1 && pairedFlights[row][col].length() <= 7) {
                cout << pairedFlights[row][col] << "\t\t";
            }
            else {
                cout << pairedFlights[row][col] << "\t";
            }
        }
        cout << "\n";
    }

    cout << "\n******* Unpaired freight ********\n";
    cout << "Row\tID\tDestination\tTime\n";
    for (int row = 0; row < unpairedFreight.size(); row++) {
        cout << (row + 1) << "\t";
        for (int col = 0; col < unpairedFreight[row].size(); col++) {
            //for destination string, print 2 tabs if too short
            if (col == 1 && unpairedFreight[row][col].length() <= 7) {
                cout << unpairedFreight[row][col] << "\t\t";
            }
            else {
                cout << unpairedFreight[row][col] << "\t";
            }
        }
        cout << "\n";
    }

    cout << "\n******* Unpaired cargo ********\n";
    cout << "Row\tID\tDestination\tTime\n";
    for (int row = 0; row < unpairedCargo.size(); row++) {
        cout << (row + 1) << "\t";
        for (int col = 0; col < unpairedCargo[row].size(); col++) {
            //for destination string, print 2 tabs if too short
            if (col == 1 && unpairedCargo[row][col].length() <= 7) {
                cout << unpairedCargo[row][col] << "\t\t";
            }
            else {
                cout << unpairedCargo[row][col] << "\t";
            }
        }
        cout << "\n";
    }
}

void Schedule::saveSchedule() {
    cout << "\n------------ Save flight schedule to file ------------\n";
    if (!isScheduleGenerated) {
        cout << "\nFlight schedule is not generated yet.\n";
        return;
    }

    string rawfolder, rawfilename;
    filesystem::path outputfilepath;
    ofstream outputfile;
    string textline;

    cout << "Input folder path to save the flight schedule:\n";
    cout << "To go back, type \"CANCEL\".\n\n-> ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover newline
    getline(cin, rawfolder);

    if (rawfolder.compare("CANCEL") == 0) {
        cout << "\nSave to file is cancelled.\n";
        return;
    }

    outputfilepath = filesystem::path(rawfolder).lexically_normal();
    outputfilepath.make_preferred();

    //validate folder path
    try {
        if (filesystem::create_directory(outputfilepath)) {
            cout << "Folder " << outputfilepath << " doesn't exist, has be created.\n";
        }
    }
    catch (const exception& e) {
        cout << "\nInvalid folder path. Folder path must be absolute.\n";
        return;
    }

    cout << "\nInput file name of the flight schedule file. Hit enter first before input.\n";
    cout << "To go back, type \"CANCEL\".\n\n-> ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover newline
    getline(cin, rawfilename);

    if (rawfilename.empty()) {
        cout << "\nEmpty input. Please try again.\n";
        return;
    }
    else if (rawfilename.compare("CANCEL") == 0) {
        cout << "\nFile open is cancelled.\n";
        return;
    }

    //concatenate file name to folder path and open the file!
    outputfilepath = outputfilepath / (rawfilename + ".txt");

    outputfile.open(outputfilepath); //overwrites the file if file exists

    if (outputfile.is_open()) {
        cout << "\n" << outputfilepath << " is opened successfully.\n\n";

        //write the paired flights to file
        outputfile << "\n******* Paired flights schedule ********\n";
        outputfile << "Row\tIDs\t\tDestination\tTime\n";
        for (int row = 0; row < pairedFlights.size(); row++) {
            outputfile << (row + 1) << "\t";
            for (int col = 0; col < pairedFlights[row].size(); col++) {
                //for destination string, print 2 tabs if too short
                if (col == 1 && pairedFlights[row][col].length() <= 7) {
                    outputfile << pairedFlights[row][col] << "\t\t";
                }
                else {
                    outputfile << pairedFlights[row][col] << "\t";
                }
            }
            outputfile << "\n";
        }

        //write the unpaired freight to file
        outputfile << "\n******* Unpaired freight ********\n";
        outputfile << "Row\tID\tDestination\tTime\n";
        for (int row = 0; row < unpairedFreight.size(); row++) {
            outputfile << (row + 1) << "\t";
            for (int col = 0; col < unpairedFreight[row].size(); col++) {
                //for destination string, print 2 tabs if too short
                if (col == 1 && unpairedFreight[row][col].length() <= 7) {
                    outputfile << unpairedFreight[row][col] << "\t\t";
                }
                else {
                    outputfile << unpairedFreight[row][col] << "\t";
                }
            }
            outputfile << "\n";
        }

        //write the unpaired cargo to file
        outputfile << "\n******* Unpaired cargo ********\n";
        outputfile << "Row\tID\tDestination\tTime\n";
        for (int row = 0; row < unpairedCargo.size(); row++) {
            outputfile << (row + 1) << "\t";
            for (int col = 0; col < unpairedCargo[row].size(); col++) {
                //for destination string, print 2 tabs if too short
                if (col == 1 && unpairedCargo[row][col].length() <= 7) {
                    outputfile << unpairedCargo[row][col] << "\t\t";
                }
                else {
                    outputfile << unpairedCargo[row][col] << "\t";
                }
            }
            outputfile << "\n";
        }
    }

    if (outputfile.is_open()) { 
        cout << "\nFlight schedule file is saved to " << outputfilepath << ".\n";
        outputfile.close(); 
    }
}