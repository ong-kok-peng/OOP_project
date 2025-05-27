#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    ifstream input_file;
    string freightFilename;
    string textline;


    while (!input_file.is_open()) {
        cout << "What is the file name for the Freight information?\nMake sure filename has no spaces. If theres a space put an underscore.\n";
        cout << "To cancel, type \"CANCEL\" to terminate.\n";
        cin >> freightFilename;
        input_file.open(freightFilename);

        if (input_file.is_open()) {
            cout << "File " << freightFilename << " opened successfully.\n\n";

            while (getline(input_file, textline)) {
                stringstream ss(textline);
                while (ss.good()) {
                    string substr;
                    getline(ss, substr, ',');
                    cout << substr << ",";
                }
                cout << "\n";
            }
        }
        else if (freightFilename.compare("CANCEL") == 0) {
            cout << "Freight information file open is cancelled.\n";
            break;
        }
        else {
            cout << "File " << freightFilename << " is not found.\n\n";
        }
    }
    
    if (input_file.is_open()) { input_file.close(); }
    return 0;
}