#include "LinkedList.hpp"
#include <iostream>
#include <chrono>

int main() {
    LinkedList list;

    // Read CSV files
    list.readCSV("dataset1-cityA.csv");
    list.readCSV("dataset2-cityB.csv");
    list.readCSV("dataset3-cityC.csv");

    // Calculate emissions
    list.calculateEmissions();

    // Display analytics
    std::cout << "Analytics:" << std::endl;
    list.displayAnalytics();

    // Sort by age
    std::cout << "\nSorting by Age..." << std::endl;
    list.sortByAge();

    // Search examples
    std::chrono::duration<double> time;
    Node* found = list.searchByAgeGroup(GROUP_18_25, time);
    if (found) {
        std::cout << "Found in age group 18-25: ID " << found->residentID << " in " << time.count() << " seconds." << std::endl;
    }

    found = list.searchByMode("Car", time);
    if (found) {
        std::cout << "Found mode Car: ID " << found->residentID << " in " << time.count() << " seconds." << std::endl;
    }

    found = list.searchByDistanceThreshold(15.0, time);
    if (found) {
        std::cout << "Found distance > 15: ID " << found->residentID << " in " << time.count() << " seconds." << std::endl;
    }

    // Sort by distance
    std::cout << "\nSorting by Distance..." << std::endl;
    list.sortByDistance();

    // Sort by emission
    std::cout << "\nSorting by Emission..." << std::endl;
    list.sortByEmission();

    return 0;
}