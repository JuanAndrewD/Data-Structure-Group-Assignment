#include "LinkedList.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <chrono>

Node::Node(std::string id, int a, std::string mode, double dist, double factor, int days)
    : residentID(id), age(a), modeOfTransport(mode), dailyDistance(dist),
      carbonEmissionFactor(factor), averageDayPerMonth(days), carbonEmission(0.0), next(nullptr) {
    if (age >= 6 && age <= 17) ageGroup = GROUP_6_17;
    else if (age >= 18 && age <= 25) ageGroup = GROUP_18_25;
    else if (age >= 26 && age <= 35) ageGroup = GROUP_26_35;
    else if (age >= 36 && age <= 50) ageGroup = GROUP_36_50;
    else ageGroup = GROUP_51_PLUS;
}

LinkedList::LinkedList() : head(nullptr), size(0) {}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void LinkedList::insert(std::string id, int age, std::string mode, double dist, double factor, int days) {
    Node* newNode = new Node(id, age, mode, dist, factor, days);
    newNode->next = head;
    head = newNode;
    size++;
}

void LinkedList::display() {
    Node* current = head;
    while (current) {
        std::cout << "ID: " << current->residentID << ", Age: " << current->age << ", Mode: " << current->modeOfTransport
                  << ", Distance: " << current->dailyDistance << ", Emission: " << current->carbonEmission << std::endl;
        current = current->next;
    }
}

void LinkedList::readCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line); // skip header
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, mode, ageStr, distStr, factorStr, daysStr;
        int age, days;
        double dist, factor;
        std::getline(ss, id, ',');
        std::getline(ss, ageStr, ',');
        age = std::stoi(ageStr);
        std::getline(ss, mode, ',');
        std::getline(ss, distStr, ',');
        dist = std::stod(distStr);
        std::getline(ss, factorStr, ',');
        factor = std::stod(factorStr);
        std::getline(ss, daysStr, ',');
        days = std::stoi(daysStr);
        insert(id, age, mode, dist, factor, days);
    }
    file.close();
}

void LinkedList::calculateEmissions() {
    Node* current = head;
    while (current) {
        current->carbonEmission = current->dailyDistance * current->carbonEmissionFactor * current->averageDayPerMonth;
        current = current->next;
    }
}

void LinkedList::displayAnalytics() {
    double totalEmission[5] = {0};
    int count[5] = {0};
    Node* current = head;
    while (current) {
        int group = current->ageGroup;
        totalEmission[group] += current->carbonEmission;
        count[group]++;
        current = current->next;
    }
    std::cout << std::setw(15) << "Age Group" << std::setw(20) << "Total Emission" << std::setw(20) << "Average Emission" << std::setw(15) << "Count" << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    std::string groups[5] = {"6-17", "18-25", "26-35", "36-50", "51+"};
    for (int i = 0; i < 5; i++) {
        double avg = count[i] > 0 ? totalEmission[i] / count[i] : 0;
        std::cout << std::setw(15) << groups[i] << std::setw(20) << totalEmission[i] << std::setw(20) << avg << std::setw(15) << count[i] << std::endl;
    }
}

void LinkedList::bubbleSortByAge(std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    if (!head) return;
    bool swapped;
    do {
        swapped = false;
        Node* current = head;
        while (current->next) {
            if (current->age > current->next->age) {
                std::swap(current->residentID, current->next->residentID);
                std::swap(current->age, current->next->age);
                std::swap(current->modeOfTransport, current->next->modeOfTransport);
                std::swap(current->dailyDistance, current->next->dailyDistance);
                std::swap(current->carbonEmissionFactor, current->next->carbonEmissionFactor);
                std::swap(current->averageDayPerMonth, current->next->averageDayPerMonth);
                std::swap(current->carbonEmission, current->next->carbonEmission);
                std::swap(current->ageGroup, current->next->ageGroup);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
    auto end = std::chrono::high_resolution_clock::now();
    time = end - start;
}

void LinkedList::bubbleSortByDistance(std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    if (!head) return;
    bool swapped;
    do {
        swapped = false;
        Node* current = head;
        while (current->next) {
            if (current->dailyDistance > current->next->dailyDistance) {
                std::swap(current->residentID, current->next->residentID);
                std::swap(current->age, current->next->age);
                std::swap(current->modeOfTransport, current->next->modeOfTransport);
                std::swap(current->dailyDistance, current->next->dailyDistance);
                std::swap(current->carbonEmissionFactor, current->next->carbonEmissionFactor);
                std::swap(current->averageDayPerMonth, current->next->averageDayPerMonth);
                std::swap(current->carbonEmission, current->next->carbonEmission);
                std::swap(current->ageGroup, current->next->ageGroup);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
    auto end = std::chrono::high_resolution_clock::now();
    time = end - start;
}

void LinkedList::bubbleSortByEmission(std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    if (!head) return;
    bool swapped;
    do {
        swapped = false;
        Node* current = head;
        while (current->next) {
            if (current->carbonEmission > current->next->carbonEmission) {
                std::swap(current->residentID, current->next->residentID);
                std::swap(current->age, current->next->age);
                std::swap(current->modeOfTransport, current->next->modeOfTransport);
                std::swap(current->dailyDistance, current->next->dailyDistance);
                std::swap(current->carbonEmissionFactor, current->next->carbonEmissionFactor);
                std::swap(current->averageDayPerMonth, current->next->averageDayPerMonth);
                std::swap(current->carbonEmission, current->next->carbonEmission);
                std::swap(current->ageGroup, current->next->ageGroup);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
    auto end = std::chrono::high_resolution_clock::now();
    time = end - start;
}

void LinkedList::sortByAge() {
    std::chrono::duration<double> time;
    bubbleSortByAge(time);
    std::cout << "Sorted by Age in " << time.count() << " seconds." << std::endl;
}

void LinkedList::sortByDistance() {
    std::chrono::duration<double> time;
    bubbleSortByDistance(time);
    std::cout << "Sorted by Distance in " << time.count() << " seconds." << std::endl;
}

void LinkedList::sortByEmission() {
    std::chrono::duration<double> time;
    bubbleSortByEmission(time);
    std::cout << "Sorted by Emission in " << time.count() << " seconds." << std::endl;
}

Node* LinkedList::searchByAgeGroup(AgeGroup group, std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    Node* current = head;
    while (current) {
        if (current->ageGroup == group) {
            auto end = std::chrono::high_resolution_clock::now();
            time = end - start;
            return current;
        }
        current = current->next;
    }
    auto end = std::chrono::high_resolution_clock::now();
    time = end - start;
    return nullptr;
}

Node* LinkedList::searchByMode(const std::string& mode, std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    Node* current = head;
    while (current) {
        if (current->modeOfTransport == mode) {
            auto end = std::chrono::high_resolution_clock::now();
            time = end - start;
            return current;
        }
        current = current->next;
    }
    auto end = std::chrono::high_resolution_clock::now();
    time = end - start;
    return nullptr;
}

Node* LinkedList::searchByDistanceThreshold(double threshold, std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    Node* current = head;
    while (current) {
        if (current->dailyDistance > threshold) {
            auto end = std::chrono::high_resolution_clock::now();
            time = end - start;
            return current;
        }
        current = current->next;
    }
    auto end = std::chrono::high_resolution_clock::now();
    time = end - start;
    return nullptr;
}