#include "LinkedList.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>

void displayMenu() {
    std::cout << "\n";
    std::cout << "============================================================\n";
    std::cout << "                      Linked List Module                    \n";
    std::cout << "============================================================\n";
    std::cout << "  1.  Load datasets (City A, B, C)\n";
    std::cout << "  2.  Show analytics (age groups & transport modes)\n";
    std::cout << "  3.  Sort by Age\n";
    std::cout << "  4.  Sort by Daily Distance\n";
    std::cout << "  5.  Sort by Carbon Emission\n";
    std::cout << "  6.  Search by Age Group\n";
    std::cout << "  7.  Search by Transport Mode\n";
    std::cout << "  8.  Search by Distance (> X km)\n";
    std::cout << "  9.  Show all residents\n";
    std::cout << " 10.  Performance comparison (Bubble Sort vs Merge Sort)\n";
    std::cout << " 11.  Insights & Recommendations\n";
    std::cout << "  0.  Exit\n";
    std::cout << "============================================================\n";
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
                std::cout << "\nAll datasets loaded and carbon emissions calculated.\n";
            } else {
                std::cout << "\nDatasets are already loaded.\n";
            }
        }

        else if (choice == 2) {
            if (!csvLoaded) { std::cout << "Please load CSV files first (Option 1).\n"; continue; }
            list.displayAnalytics();
        }
        
        else if (choice == 3) {
            if (!csvLoaded) { std::cout << "Please load CSV files first (Option 1).\n"; continue; }
            std::cout << "Choose sort algorithm:\n"
                      << "0 = Bubble Sort\n"
                      << "1 = Merge Sort\n"
                      << "Enter choice: ";
            int algo; std::cin >> algo;
            list.sortByAge(algo);
        }
        
        else if (choice == 4) {
            if (!csvLoaded) { std::cout << "Please load CSV files first (Option 1).\n"; continue; }
            std::cout << "Choose sort algorithm:\n"
                      << "0 = Bubble Sort\n"
                      << "1 = Merge Sort\n"
                      << "Enter choice: ";
            int algo; std::cin >> algo;
            list.sortByDistance(algo);
        }
        
        else if (choice == 5) {
            if (!csvLoaded) { std::cout << "Please load CSV files first (Option 1).\n"; continue; }
            std::cout << "Choose sort algorithm:\n"
                      << "0 = Bubble Sort\n"
                      << "1 = Merge Sort\n"
                      << "Enter choice: ";
            int algo; std::cin >> algo;
            list.sortByEmission(algo);
        }
        
        else if (choice == 6) {
            if (!csvLoaded) { std::cout << "Please load CSV files first (Option 1).\n"; continue; }

            std::cout << "\nChoose search method:\n"
                      << "0 = Linear Search (works on unsorted data)\n"
                      << "1 = Early-Exit (requires sorted by age)\n"
                      << "2 = Binary Search (requires sorted by age)\n"
                      << "3 = Linear Search (first match only and unsorted)\n"
                      << "Enter choice: ";
            int algo; std::cin >> algo;

            if (algo == 1 || algo == 2) {
                std::cout << "  Sorting by Age first (Merge Sort)...\n";
                std::chrono::duration<double> sortTime;
                list.mergeSortByAge(sortTime);
                std::cout << "  Sort done in " << std::fixed << std::setprecision(8)
                          << sortTime.count() << " s\n";
            }

            std::cout << "\nEnter age group:\n"
                      << "0 = 6-17 (Children & Teenagers)\n"
                      << "1 = 18-25 (University Students / Young Adults)\n"
                      << "2 = 26-45 (Working Adults, Early Career)\n"
                      << "3 = 46-60 (Working Adults, Late Career)\n"
                      << "4 = 61+ (Senior Citizens / Retirees)\n"
                      << "Enter choice: ";
            int group; std::cin >> group;
            if (group < 0 || group > 4) {
                std::cout << "  Invalid group selection.\n"; continue;
            }
            list.searchAge(algo, static_cast<AgeGroup>(group));
        }
        
        else if (choice == 7) {
            if (!csvLoaded) { std::cout << "  Please load CSV files first (Option 1).\n"; continue; }

            std::cout << "\nChoose search method:\n"
                      << "0 = Linear Search (works on unsorted data)\n"
                      << "1 = Early-Exit (requires sorted by mode)\n"
                      << "2 = Binary Search (requires sorted by mode)\n"
                      << "3 = Linear Search (first match only and unsorted)\n"
                      << "Enter choice: ";
            int algo; std::cin >> algo;

            if (algo == 1 || algo == 2) {
                std::cout << "Sorting by Mode first (Bubble Sort)...\n";
                std::chrono::duration<double> sortTime;
                list.bubbleSortByMode(sortTime);
                std::cout << "Sorted in " << std::fixed << std::setprecision(8)
                          << sortTime.count() << " s\n";
            }

            std::cout << "\n  Enter exact transport mode\n"
                      << "  (e.g., Car  Bus  Bicycle  Walking  School Bus  Carpool):\n"
                      << "Enter mode: ";
            std::cin.ignore();
            std::string mode;
            std::getline(std::cin, mode);

            list.searchMode(algo, mode);
        }
        
        else if (choice == 8) {
            if (!csvLoaded) { std::cout << "  Please load CSV files first (Option 1).\n"; continue; }

            std::cout << "\nChoose search method:\n"
                      << "0 = Linear Search (works on unsorted data)\n"
                      << "1 = Early-Exit (requires sorted by distance)\n"
                      << "2 = Binary Search (requires sorted by distance)\n"
                      << "3 = Linear Search (first match only and unsorted)\n"
                      << "Enter choice: ";
            int algo; std::cin >> algo;

            if (algo == 1 || algo == 2) {
                std::cout << "Sorting by Distance first (Merge Sort)...\n";
                std::chrono::duration<double> sortTime;
                list.mergeSortByDistance(sortTime);
                std::cout << "Sorted in " << std::fixed << std::setprecision(8)
                          << sortTime.count() << " s\n";
            }

            std::cout << "\nFind all residents with Daily Distance > X km.\n"
                      << "Enter X (e.g., 15): ";
            double threshold; std::cin >> threshold;

            list.searchDistance(algo, threshold);
        }
        
        else if (choice == 9) {
            if (!csvLoaded) { std::cout << "Please load CSV files first (Option 1).\n"; continue; }
            list.display();
        }
        
        else if (choice == 10) {
            if (!csvLoaded) { std::cout << "Please load CSV files first (Option 1).\n"; continue; }
            list.displayPerformanceSummary();
        }
        
        else if (choice == 11) {
            if (!csvLoaded) { std::cout << "Please load CSV files first (Option 1).\n"; continue; }
            list.displayInsights();
        }
        
        else if (choice == 0) {
            std::cout << "Exiting program. Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid choice. Please enter 0-11.\n";
        }
    }

    return 0;
}