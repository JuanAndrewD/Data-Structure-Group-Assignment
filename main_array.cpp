#include "Array.hpp"
#include <iostream>
#include <string>
using namespace std;


void displayMenu() {
    cout << "\n=== Array Module Menu ===" << endl;
    cout << "1. Read CSV files" << endl;
    cout << "2. Display Analytics" << endl;
    cout << "3. Sort by Age" << endl;
    cout << "4. Sort by Distance" << endl;
    cout << "5. Sort by Emission" << endl;
    cout << "6. Search by Age Group" << endl;
    cout << "7. Search by Mode of Transport" << endl;
    cout << "8. Search by Distance Threshold" << endl;
    cout << "9. Search by Resident ID" << endl;
    cout << "10. Display List" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    ResidentArray arrayList;
    bool csvLoaded = false;

    while (true) {
        displayMenu();
        int choice; cin >> choice;

        if (choice == 1) {
            arrayList.clearData();
            cout << "\n--- Select Cities to Load ---" << endl;
            cout << "1. City A only" << endl;
            cout << "2. City B only" << endl;
            cout << "3. City C only" << endl;
            cout << "4. All Cities (A, B, and C)" << endl;
            cout << "Enter sub-choice: ";
            int sub; cin >> sub;
            if (sub == 1) arrayList.readCSV("dataset1-cityA.csv");
            else if (sub == 2) arrayList.readCSV("dataset2-cityB.csv");
            else if (sub == 3) arrayList.readCSV("dataset3-cityC.csv");
            else if (sub == 4) arrayList.readAllCities();
            csvLoaded = true;
        }
        else if (choice == 2) {
            if (csvLoaded) arrayList.displayAnalytics();
            else cout << "Please load CSV first." << endl;
        }
        else if (choice == 3) {
            if (csvLoaded) {
                cout << "Choose algorithm (0: Bubble, 1: Merge): ";
                int algo; cin >> algo;
                if (algo == 0) arrayList.runExperiment("bubble_age");
                else if (algo == 1) arrayList.runExperiment("merge_age");
                else cout << "[Error] Invalid algorithm! Please enter 0 or 1." << endl;
            }
            else cout << "Please load CSV first." << endl;
        }
        else if (choice == 4) {
            if (csvLoaded) {
                cout << "Choose algorithm (0: Bubble, 1: Merge): ";
                int algo; cin >> algo;
                if (algo == 0) arrayList.runExperiment("bubble_distance");
                else if (algo == 1) arrayList.runExperiment("merge_distance");
                else cout << "[Error] Invalid algorithm! Please enter 0 or 1." << endl;
            }
            else cout << "Please load CSV first." << endl;
        }
        else if (choice == 5) {
            if (csvLoaded) {
                cout << "Choose algorithm (0: Bubble, 1: Merge): ";
                int algo; cin >> algo;
                if (algo == 0) arrayList.runExperiment("bubble_emission");
                else if (algo == 1) arrayList.runExperiment("merge_emission");
                else cout << "[Error] Invalid algorithm! Please enter 0 or 1." << endl;
            }
            else cout << "Please load CSV first." << endl;
        }
        else if (choice == 6) {
            if (csvLoaded) {
                cout << "\nChoose search algorithm: (0: Linear (Unsorted), 1: Early-Exit (Sorted), 2: Binary (Sorted)):" << endl;
                int algo; cin >> algo;
                if (algo < 0 || algo > 2) cout << "[Error] Invalid number! Please enter 0, 1, or 2." << endl;
                else {
                    if (algo == 1 || algo == 2) {
                        cout << "(Notice: Auto-sorting data to prepare for search...)" << endl;
                    }
                    cout << "\nEnter group (0: 6-17, 1: 18-25, 2: 26-45, 3: 46-60, 4: 61-100): ";
                    string group; cin >> group;
                    arrayList.runExperiment("search_age", group, algo);
                }
            }
            else cout << "Please load CSV first." << endl;
        }
        else if (choice == 7) {
            if (csvLoaded) {
                cout << "\nChoose search algorithm: (0: Linear (Unsorted), 1: Early-Exit (Sorted), 2: Binary (Sorted)):" << endl;
                int algo; cin >> algo;
                if (algo < 0 || algo > 2) cout << "[Error] Invalid number! Please enter 0, 1, or 2." << endl;
                else {
                    if (algo == 1 || algo == 2) {
                        cout << "(Notice: Auto-sorting data to prepare for search...)" << endl;
                    }
                    cout << "Available modes: Car, Bus, Bicycle, Walking, Carpool, School Bus" << endl;
                    cout << "Enter mode: ";
                    string mode; cin >> mode;
                    arrayList.runExperiment("search_transport", mode, algo);
                }
            }
            else cout << "Please load CSV first." << endl;
        }
        else if (choice == 8) {
            if (csvLoaded) {
                cout << "\nChoose search algorithm: (0: Linear (Unsorted), 1: Early-Exit (Sorted), 2: Binary (Sorted)):" << endl;
                int algo; cin >> algo;
                if (algo < 0 || algo > 2) cout << "[Error] Invalid number! Please enter 0, 1, or 2." << endl;
                else {
                    if (algo == 1 || algo == 2) {
                        cout << "(Notice: Auto-sorting data to prepare for search...)" << endl;
                    }
                    cout << "Enter daily distance threshold (in km, e.g., 15): ";
                    string distance; cin >> distance;
                    arrayList.runExperiment("search_distance", distance, algo);
                }
            }
            else cout << "Please load CSV first." << endl;
        }
        else if (choice == 9) {
            if (csvLoaded) {
                string id;
                cout << "Enter Resident ID: ";
                cin >> id;
                cout << "Method (1: Linear, 2: Binary): ";
                int method; cin >> method;
                if (method == 1) arrayList.runExperiment("linear_id", id);
                else if (method == 2) arrayList.runExperiment("binary_id", id);
                else cout << "[Error] Invalid algorithm! Please enter 0 or 1." << endl;
            }
            else cout << "Please load CSV first." << endl;
        }
        else if (choice == 10) {
            if (csvLoaded) arrayList.printAll();
            else cout << "Please load CSV first." << endl;
        }
        else if (choice == 0) break;
    }
        
    return 0;
    
}