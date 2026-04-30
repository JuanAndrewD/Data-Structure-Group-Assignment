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
    void sortByAge(int algorithm); // 0: bubble, 1: merge
    void sortByDistance(int algorithm);
    void sortByEmission(int algorithm);
    void bubbleSortByAge(std::chrono::duration<double>& time);
    void bubbleSortByDistance(std::chrono::duration<double>& time);
    void bubbleSortByEmission(std::chrono::duration<double>& time);
    void mergeSortByAge(std::chrono::duration<double>& time);
    void mergeSortByDistance(std::chrono::duration<double>& time);
    void mergeSortByEmission(std::chrono::duration<double>& time);
    Node* merge(Node* left, Node* right, int sortType);
    Node* mergeSort(Node* head, int sortType);
    Node* getMiddle(Node* start, Node* last); //Tortoise and Hare helper
    void bubbleSortByMode();
    void linearSearchByAge(AgeGroup group, std::chrono::duration<double>& time);
    void earlyExitSearchByAge(AgeGroup group, std::chrono::duration<double>& time);
    void binarySearchByAge(AgeGroup group, std::chrono::duration<double>& time);
    void searchAge(int algorithm, AgeGroup group);
    void linearSearchByMode(const std::string& mode, std::chrono::duration<double>& time);
    void earlyExitSearchByMode(const std::string& mode, std::chrono::duration<double>& time);
    void binarySearchByMode(const std::string& mode, std::chrono::duration<double>& time);
    void searchMode(int algorithm, const std::string& mode);
    void linearSearchByDistance(double threshold, std::chrono::duration<double>& time);
    void earlyExitSearchByDistance(double threshold, std::chrono::duration<double>& time);
    void binarySearchByDistance(double threshold, std::chrono::duration<double>& time);
    void searchDistance(int algorithm, double threshold);
};

#endif // LINKEDLIST_HPP