#include "LinkedList.hpp"
#include <iostream>
#include <string>

void displayMenu() {
    std::cout << "\n=== Data Structure Group Assignment Menu ===" << std::endl;
    std::cout << "1. Read CSV files" << std::endl;
    std::cout << "2. Display Analytics" << std::endl;
    std::cout << "3. Sort by Age" << std::endl;
    std::cout << "4. Sort by Distance" << std::endl;
    std::cout << "5. Sort by Emission" << std::endl;
    std::cout << "6. Search by Age Group" << std::endl;
    std::cout << "7. Search by Mode of Transport" << std::endl;
    std::cout << "8. Search by Distance Threshold" << std::endl;
    std::cout << "9. Display List" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    LinkedList list;
    bool csvLoaded = false;

    while (true) {
        displayMenu();
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            if (!csvLoaded) {
                list.readCSV("dataset1-cityA.csv");
                list.readCSV("dataset2-cityB.csv");
                list.readCSV("dataset3-cityC.csv");
                list.calculateEmissions();
                csvLoaded = true;
                std::cout << "CSV files loaded and emissions calculated." << std::endl;
            } else {
                std::cout << "CSV files already loaded." << std::endl;
            }
        } else if (choice == 2) {
            if (csvLoaded) {
                list.displayAnalytics();
            } else {
                std::cout << "Please load CSV files first." << std::endl;
            }
        } else if (choice == 3) {
            if (csvLoaded) {
                std::cout << "Choose algorithm (0: Bubble Sort, 1: Merge Sort): ";
                int algo;
                std::cin >> algo;
                list.sortByAge(algo);
            } else {
                std::cout << "Please load CSV files first." << std::endl;
            }
        } else if (choice == 4) {
            if (csvLoaded) {
                std::cout << "Choose algorithm (0: Bubble Sort, 1: Merge Sort): ";
                int algo;
                std::cin >> algo;
                list.sortByDistance(algo);
            } else {
                std::cout << "Please load CSV files first." << std::endl;
            }
        } else if (choice == 5) {
            if (csvLoaded) {
                std::cout << "Choose algorithm (0: Bubble Sort, 1: Merge Sort): ";
                int algo;
                std::cin >> algo;
                list.sortByEmission(algo);
            } else {
                std::cout << "Please load CSV files first." << std::endl;
            }
        } else if (choice == 6) {
            if (csvLoaded) {
                std::cout << "Enter age group (0: 6-17, 1: 18-25, 2: 26-35, 3: 36-50, 4: 51+): ";
                int group;
                std::cin >> group;
                std::chrono::duration<double> time;
                Node* found = list.searchByAgeGroup(static_cast<AgeGroup>(group), time);
                if (found) {
                    std::cout << "Found: ID " << found->residentID << " in " << time.count() << " seconds." << std::endl;
                } else {
                    std::cout << "Not found in " << time.count() << " seconds." << std::endl;
                }
            } else {
                std::cout << "Please load CSV files first." << std::endl;
            }
        } else if (choice == 7) {
            if (csvLoaded) {
                std::cout << "Enter mode of transport: ";
                std::string mode;
                std::cin >> mode;
                std::chrono::duration<double> time;
                Node* found = list.searchByMode(mode, time);
                if (found) {
                    std::cout << "Found: ID " << found->residentID << " in " << time.count() << " seconds." << std::endl;
                } else {
                    std::cout << "Not found in " << time.count() << " seconds." << std::endl;
                }
            } else {
                std::cout << "Please load CSV files first." << std::endl;
            }
        } else if (choice == 8) {
            if (csvLoaded) {
                std::cout << "Enter distance threshold: ";
                double threshold;
                std::cin >> threshold;
                std::chrono::duration<double> time;
                Node* found = list.searchByDistanceThreshold(threshold, time);
                if (found) {
                    std::cout << "Found: ID " << found->residentID << " in " << time.count() << " seconds." << std::endl;
                } else {
                    std::cout << "Not found in " << time.count() << " seconds." << std::endl;
                }
            } else {
                std::cout << "Please load CSV files first." << std::endl;
            }
        } else if (choice == 9) {
            if (csvLoaded) {
                list.display();
            } else {
                std::cout << "Please load CSV files first." << std::endl;
            }
        } else if (choice == 0) {
            break;
        } else {
            std::cout << "Invalid choice. Try again." << std::endl;
        }
    }

    return 0;
}