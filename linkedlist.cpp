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

void LinkedList::sortByAge(int algorithm) {
    std::chrono::duration<double> time;
    if (algorithm == 0) {
        bubbleSortByAge(time);
        std::cout << "Bubble Sorted by Age in " << time.count() << " seconds." << std::endl;
    } else {
        mergeSortByAge(time);
        std::cout << "Merge Sorted by Age in " << time.count() << " seconds." << std::endl;
    }
}

void LinkedList::sortByDistance(int algorithm) {
    std::chrono::duration<double> time;
    if (algorithm == 0) {
        bubbleSortByDistance(time);
        std::cout << "Bubble Sorted by Distance in " << time.count() << " seconds." << std::endl;
    } else {
        mergeSortByDistance(time);
        std::cout << "Merge Sorted by Distance in " << time.count() << " seconds." << std::endl;
    }
}

void LinkedList::mergeSortByAge(std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    head = mergeSort(head, 0);
    auto end = std::chrono::high_resolution_clock::now();
    time = end - start;
}

void LinkedList::mergeSortByDistance(std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    head = mergeSort(head, 1);
    auto end = std::chrono::high_resolution_clock::now();
    time = end - start;
}

void LinkedList::mergeSortByEmission(std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    head = mergeSort(head, 2);
    auto end = std::chrono::high_resolution_clock::now();
    time = end - start;
}

void LinkedList::sortByEmission(int algorithm) {
    std::chrono::duration<double> time;
    if (algorithm == 0) {
        bubbleSortByEmission(time);
        std::cout << "Bubble Sorted by Emission in " << time.count() << " seconds." << std::endl;
    } else {
        mergeSortByEmission(time);
        std::cout << "Merge Sorted by Emission in " << time.count() << " seconds." << std::endl;
    }
}

Node* LinkedList::mergeSort(Node* head, int sortType) {
    if (!head || !head->next) return head;

    Node* slow = head;
    Node* fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* mid = slow->next;
    slow->next = nullptr;

    Node* left = mergeSort(head, sortType);
    Node* right = mergeSort(mid, sortType);

    return merge(left, right, sortType);
}

Node* LinkedList::merge(Node* left, Node* right, int sortType) {
    if (!left) return right;
    if (!right) return left;

    bool condition;
    if (sortType == 0) condition = left->age <= right->age;
    else if (sortType == 1) condition = left->dailyDistance <= right->dailyDistance;
    else condition = left->carbonEmission <= right->carbonEmission;

    if (condition) {
        left->next = merge(left->next, right, sortType);
        return left;
    } else {
        right->next = merge(left, right->next, sortType);
        return right;
    }
}


/*Bubblesort instead of mergesort used for pre-sorting data for early-exit. This is for comparing performance purpose or control variable since we know mergesort is more efficient. Used for the search by transport mode.*/
void LinkedList::bubbleSortByMode(std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    if (!head) return;
    bool swapped;
    do {
        swapped = false;
        Node* current = head;
        while (current->next) {
            if (current->modeOfTransport > current->next->modeOfTransport) {
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


//Tortoise and Hare helper to find middle node between start and last (used for binary searches)
Node* LinkedList::getMiddle(Node* start, Node* last) {
    if (start == nullptr) return nullptr;
    if (start == last) return start;

    Node* slow = start;
    Node* fast = start->next;

    while (fast != last) {
        fast = fast->next;
        slow = slow->next;
        if (fast != last) {
            fast = fast->next;
        }
    }
    return slow;
}


/*Linear search functions for unsorted data */
void LinkedList::linearSearchByAge(AgeGroup group, std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    bool found = false;
    Node* current = head;

    std::cout << std::string(30, '=') << std::endl;

    while (current) {
        if (current->ageGroup == group) {
            std::cout << current->residentID << ", Age: " << current->age << ", Distance: " << current->dailyDistance << std::endl;
            found = true;
        }
        current = current->next;
    }
    std::cout << std::string(30, '=') << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    time = end - start;

    if (!found) std::cout << "No residents found." << std::endl;
    std::cout << "Search completed in " << time.count() << " seconds." << std::endl;
}


/*Linear search with early exit for sorted data (uses pre-sorted from mergesort) */
void LinkedList::earlyExitSearchByAge(AgeGroup group, std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    bool found = false;
    Node* current = head;

    while (current) {
        if (current->ageGroup > group) {
            std::cout << "Passed target age group. Stopping search." << std::endl;
            break;
        }
        if (current->ageGroup == group) {
            std::cout << current->residentID << ", Age: " << current->age << ", Dist: " << current->dailyDistance << "km" << std::endl;
            found = true;
        }
        current = current->next;
    }
    std::cout << std::string(30, '=') << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    time = end - start;

    if (!found) std::cout << "No residents found." << std::endl;
    time = end - start;
}


/*Binary search*/
//Binary search on linked list(does not work efficiently but for experimental purposes)
void LinkedList::binarySearchByAge(AgeGroup group, std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    bool found = false;
    Node* startNode = head;
    Node* lastNode = nullptr;

    while (true) {
        Node* mid = getMiddle(startNode, lastNode);
        if (mid == nullptr) break;

        if (mid->ageGroup == group) {
            std::cout << mid->residentID << ", Age: " << mid->age << ", Dist: " << mid->dailyDistance << "km" << std::endl;
            std::cout << "First match found! (Binary Search stops here)" << std::endl;
            found = true;
            break;
        }
        else if (startNode == lastNode) break;
        else if (mid->ageGroup < group) startNode = mid->next;
        else lastNode = mid;
    }
    std::cout << std::string(30, '=') << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    time = end - start;

    if (!found) std::cout << "No residents found." << std::endl;
    time = end - start;
}



void LinkedList::searchAge(int algorithm, AgeGroup group) {
    std::chrono::duration<double> time;

    if (algorithm == 0) {
        linearSearchByAge(group, time);
    }
    else if (algorithm == 1) {
        earlyExitSearchByAge(group, time);
    }
    else if (algorithm == 2) {
        binarySearchByAge(group, time);
    }
    else {
        std::cout << "Invalid algorithm choice!" << std::endl;
    }
}


/*Linear search functions for unsorted data */
void LinkedList::linearSearchByMode(const std::string& mode, std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    bool found = false;
    Node* current = head;

    std::cout << std::string(30, '=') << std::endl;

    while (current) {
        if (current->modeOfTransport == mode) {
            std::cout << current->residentID << ", Mode: " << current->modeOfTransport << ", Dist: " << current->dailyDistance << "km" << std::endl;
            found = true;
        }
        current = current->next;
    }
    std::cout << std::string(30, '=') << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    time = end - start;

    if (!found) std::cout << "No residents found." << std::endl;
    std::cout << "Search completed in " << time.count() << " seconds." << std::endl;
}


/*Linear search with early exit for sorted data (uses pre-sorted from mergesort) */
void LinkedList::earlyExitSearchByMode(const std::string& mode, std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    bool found = false;
    Node* current = head;

    std::cout << std::string(30, '=') << std::endl;

    while (current) {
        if (current->modeOfTransport > mode) {
            std::cout << "Passed target transport mode. Stopping search." << std::endl;
            break;
        }
        if (current->modeOfTransport == mode) {
            std::cout << current->residentID << ", Mode: " << current->modeOfTransport << ", Dist: " << current->dailyDistance << "km" << std::endl;
            found = true;
        }
        current = current->next;
    }

    std::cout << std::string(30, '=') << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    time = end - start;

    if (!found) std::cout << "No residents found." << std::endl;
    std::cout << "Search completed in " << time.count() << " seconds." << std::endl;
}

/*Binary search*/
//Binary search on linked list(does not work efficiently but for experimental purposes)
void LinkedList::binarySearchByMode(const std::string& mode, std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    bool found = false;
    Node* startNode = head;
    Node* lastNode = nullptr;

    std::cout << std::string(30, '=') << std::endl;

    while (true) {
        Node* mid = getMiddle(startNode, lastNode);
        if (mid == nullptr) break;

        if (mid->modeOfTransport == mode) {
            std::cout << mid->residentID << ", Mode: " << mid->modeOfTransport << ", Dist: " << mid->dailyDistance << "km" << std::endl;
            std::cout << "First match found! (Binary Search stops here)" << std::endl;
            found = true;
            break;
        }
        else if (startNode == lastNode) break;
        else if (mid->modeOfTransport < mode) startNode = mid->next;
        else lastNode = mid;
    }

    std::cout << std::string(30, '=') << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    time = end - start;

    if (!found) std::cout << "No residents found." << std::endl;
    std::cout << "Search completed in " << time.count() << " seconds." << std::endl;
}


void LinkedList::searchMode(int algorithm, const std::string& mode) {
    std::chrono::duration<double> time;
    if (algorithm == 0) {
        linearSearchByMode(mode, time);
    }
    else if (algorithm == 1) {
        earlyExitSearchByMode(mode, time);
    }
    else if (algorithm == 2) {
        binarySearchByMode(mode, time);
    }
    else {
        std::cout << "Invalid algorithm choice!" << std::endl;
    }
}


/*Linear search functions for unsorted data */
void LinkedList::linearSearchByDistance(double threshold, std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    bool found = false;
    Node* current = head;

    std::cout << std::string(30, '=') << std::endl;

    while (current) {
        if (current->dailyDistance == threshold) {
            std::cout << current->residentID << ", Dist: " << current->dailyDistance << "km, Mode: " << current->modeOfTransport << std::endl;
            found = true;
        }
        current = current->next;
    }
    std::cout << std::string(30, '=') << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    time = end - start;

    if (!found) std::cout << "No residents found." << std::endl;
    std::cout << "Search completed in " << time.count() << " seconds." << std::endl;
}


/*Linear search with early exit for sorted data (uses pre-sorted from mergesort) */
void LinkedList::earlyExitSearchByDistance(double threshold, std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    bool found = false;
    Node* current = head;

    std::cout << std::string(30, '=') << std::endl;

    while (current) {
        if (current->dailyDistance > threshold) {
            std::cout << "Passed target distance. Stopping search." << std::endl;
            break;
        }
        if (current->dailyDistance == threshold) {
            std::cout << current->residentID << ", Dist: " << current->dailyDistance << "km, Mode: " << current->modeOfTransport << std::endl;
            found = true;
        }
        current = current->next;
    }
    std::cout << std::string(30, '=') << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    time = end - start;

    if (!found) std::cout << "No residents found." << std::endl;
    std::cout << "Search completed in " << time.count() << " seconds." << std::endl;
}


/*Binary search*/
//Binary search on linked list(does not work efficiently but for experimental purposes)
void LinkedList::binarySearchByDistance(double threshold, std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    bool found = false;
    Node* startNode = head;
    Node* lastNode = nullptr;

    std::cout << std::string(30, '=') << std::endl;

    while (true) {
        Node* mid = getMiddle(startNode, lastNode);
        if (mid == nullptr) break;

        if (mid->dailyDistance == threshold) {
            std::cout << mid->residentID << ", Dist: " << mid->dailyDistance << "km, Mode: " << mid->modeOfTransport << std::endl;
            std::cout << "First match found! (Binary Search stops here)" << std::endl;
            found = true;
            break;
        }
        else if (startNode == lastNode) break;
        else if (mid->dailyDistance < threshold) startNode = mid->next;
        else lastNode = mid;
    }
    std::cout << std::string(30, '=') << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    time = end - start;

    if (!found) std::cout << "No residents found." << std::endl;
    std::cout << "Search completed in " << time.count() << " seconds." << std::endl;
}


void LinkedList::searchDistance(int algorithm, double threshold) {
    std::chrono::duration<double> time;
    if (algorithm == 0) {
        linearSearchByDistance(threshold, time);
    }
    else if (algorithm == 1) {
        earlyExitSearchByDistance(threshold, time);
    }
    else if (algorithm == 2) {
        binarySearchByDistance(threshold, time);
    }
    else {
        std::cout << "Invalid algorithm choice!" << std::endl;
    }
}