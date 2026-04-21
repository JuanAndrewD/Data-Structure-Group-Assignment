#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "Resident.hpp"
#include <string>
#include <chrono>

class LinkedList {
private:
    Node* head;
    int size;

public:
    LinkedList();
    ~LinkedList();
    void insert(std::string id, int age, std::string mode, double dist, double factor, int days);
    void display();
    void readCSV(const std::string& filename);
    void calculateEmissions();
    void categorizeAgeGroups();
    void displayAnalytics();
    void sortByAge();
    void sortByDistance();
    void sortByEmission();
    Node* searchByAgeGroup(AgeGroup group, std::chrono::duration<double>& time);
    Node* searchByMode(const std::string& mode, std::chrono::duration<double>& time);
    Node* searchByDistanceThreshold(double threshold, std::chrono::duration<double>& time);
    void bubbleSortByAge(std::chrono::duration<double>& time);
    void bubbleSortByDistance(std::chrono::duration<double>& time);
    void bubbleSortByEmission(std::chrono::duration<double>& time);
};

#endif // LINKEDLIST_HPP