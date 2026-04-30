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
        }
        else if (choice == 6) {
            if (csvLoaded) {
                std::cout << "\nChoose search algorithm: (0: Linear Search (Unsorted), 1: Early-Exit Search (Sorted), 2: Binary Search (Sorted)):" << std::endl;
                int algo;
                std::cin >> algo;

                if (algo == 1 || algo == 2) {
                    std::cout << "(Auto-sorting data to prepare for search...)\n";
                    std::chrono::duration<double> sortTime;
                    list.mergeSortByAge(sortTime);
                }

                std::cout << "\nEnter age group (0: 6-17, 1: 18-25, 2: 26-35, 3: 36-50, 4: 51+): ";
                int group;
                std::cin >> group;

                std::string groupName = (
                    group == 0 ? "6-17" :
                    group == 1 ? "18-25" :
                    group == 2 ? "26-35" :
                    group == 3 ? "36-50" :
                    group == 4 ? "51+" :
                    "Unknown"
                    );
                std::cout << "\nAge Group Search Result" << std::endl;
                list.searchAge(algo, static_cast<AgeGroup>(group));
            }
            else {
                std::cout << "Please load CSV files first." << std::endl;
            }
        }
        else if (choice == 7) {
            if (csvLoaded) {
                std::cout << "\nChoose search algorithm: (0: Linear Search (Unsorted), 1: Early-Exit Search (Sorted), 2: Binary Search (Sorted)):" << std::endl;
                int algo;
                std::cin >> algo;

                if (algo == 1 || algo == 2) {
                    std::cout << "(Auto-sorting data to prepare for search...)\n";
                    std::chrono::duration<double> sortTime;
                    list.bubbleSortByMode(sortTime);
                }
                std::cout << "\nEnter exact transport mode (e.g. Car, Bicycle, Bus): ";
                std::string mode;
                std::cin >> mode;

                std::cout << "\nTransport Mode Search Result" << std::endl;
                list.searchMode(algo, mode);
            }
            else {
                std::cout << "Please load CSV files first." << std::endl;
            }
        }
        else if (choice == 8) {
            if (csvLoaded) {
                std::cout << "\nChoose search algorithm: (0: Linear Search (Unsorted), 1: Early-Exit Search (Sorted), 2: Binary Search (Sorted)): " << std::endl;
                int algo;
                std::cin >> algo;

                if (algo == 1 || algo == 2) {
                    std::cout << "(Auto-sorting data to prepare for search...)\n";
                    std::chrono::duration<double> sortTime;
                    list.mergeSortByDistance(sortTime);
                }
                std::cout << "\nEnter distance threshold (e.g. > 15km): ";
                double threshold;
                std::cin >> threshold;

                std::cout << "\nDistance Search Result" << std::endl;
                list.searchDistance(algo, threshold);
            }
            else {
                std::cout << "Please load CSV files first." << std::endl;
            }
        }
        else if (choice == 9) {
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