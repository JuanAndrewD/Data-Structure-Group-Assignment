#ifndef RESIDENT_HPP
#define RESIDENT_HPP

#include <string>

enum AgeGroup {
    GROUP_6_17,
    GROUP_18_25,
    GROUP_26_35,
    GROUP_36_50,
    GROUP_51_PLUS
};

struct Node {
    std::string residentID;
    int age;
    std::string modeOfTransport;
    double dailyDistance;
    double carbonEmissionFactor;
    int averageDayPerMonth;
    double carbonEmission;
    AgeGroup ageGroup;
    Node* next;

    Node(std::string id, int a, std::string mode, double dist, double factor, int days);
};

#endif // RESIDENT_HPP