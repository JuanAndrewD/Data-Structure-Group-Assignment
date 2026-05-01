#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <string>

struct ArrayResident {
    std::string residentID;
    int age;
    std::string transportMode;
    float dailyDistance;
    float carbonFactor;
    int daysPerMonth;
    float totalCarbon;
};

class ResidentArray {
private:
    static const int MAX_SIZE = 2000;
    ArrayResident arr[MAX_SIZE];
    int size;

    // Merge Sort Algorithm
    void mergeAge(int left, int mid, int right);
    void mergeSortAge(int left, int right);

    void mergeDistance(int left, int mid, int right);
    void mergeSortDistance(int left, int right);

    void mergeEmission(int left, int mid, int right);
    void mergeSortEmission(int left, int right);

public:
    // Constructor & Destructor
    ResidentArray();
    ~ResidentArray();

    // Manage Data
    void readCSV(const std::string& filename);
    void readAllCities();
    void clearData();
    void printAll();

    // Sorting Algorithms
    void sortByID();
    void sortByAgeBubble();
    void sortByAgeMerge();
    void sortByDistanceBubble();
    void sortByDistanceMerge();
    void sortByEmissionBubble();
    void sortByEmissionMerge();
    void sortByModeBubble();

    // Searching Algorithms
    int linearSearch(const std::string& targetID);
    int binarySearch(const std::string& targetID);
    void searchAgeRange(int minAge, int maxAge);
    void searchAgeEarlyExit(int minAge, int maxAge);
    void searchAgeBinary(int minAge, int maxAge);
    void searchTransport(const std::string& mode);
    void searchTransportEarlyExit(const std::string& mode);
    void searchTransportBinary(const std::string& mode);
    void searchDistance(float threshold);
    void searchDistanceEarlyExit(float threshold);
    void searchDistanceBinary(float threshold);

    // Analytics & Performance
    void displayAnalytics();
    void displayMemoryUsage();
    void runExperiment(std::string command, std::string target = "", int algo = 0);
};

#endif