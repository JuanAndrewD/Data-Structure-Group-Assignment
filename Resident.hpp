#ifndef RESIDENT_HPP
#define RESIDENT_HPP

#include <string>

enum AgeGroup {
    GROUP_6_17 = 0, // Children & Teenagers
    GROUP_18_25 = 1, // University Students / Young Adults
    GROUP_26_45 = 2, // Working Adults (Early Career)
    GROUP_46_60 = 3, // Working Adults (Late Career)
    GROUP_61_100 = 4, // Senior Citizens / Retirees
    GROUP_UNKNOWN = 5
};

// Returns the Age Group label for each age group
inline std::string ageGroupLabel(AgeGroup g) {
    switch (g) {
        case GROUP_6_17: return "Children & Teens";
        case GROUP_18_25: return "Young Adults";
        case GROUP_26_45: return "Early Career";
        case GROUP_46_60: return "Late Career";
        case GROUP_61_100: return "Senior Citizens";
        case GROUP_UNKNOWN: return "Unknown";
        default: return "Unknown";
    }
}

// Returns only the numeric range string for display in tables
inline std::string ageGroupRange(AgeGroup g) {
    switch (g) {
        case GROUP_6_17: return "6-17";
        case GROUP_18_25: return "18-25";
        case GROUP_26_45: return "26-45";
        case GROUP_46_60: return "46-60";
        case GROUP_61_100: return "61-100";
        case GROUP_UNKNOWN: return "Unknown";
        default: return "Unknown";
    }
}

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

    // Constructor
    Node(std::string id, int a, std::string mode,
         double dist, double factor, int days)
        : residentID(id), age(a), modeOfTransport(mode),
          dailyDistance(dist), carbonEmissionFactor(factor),
          averageDayPerMonth(days), carbonEmission(0.0), next(nullptr)
    {
        // Assign age group using assignment-specified ranges
        if (a >= 6  && a <= 17) ageGroup = GROUP_6_17;
        else if (a >= 18 && a <= 25) ageGroup = GROUP_18_25;
        else if (a >= 26 && a <= 45) ageGroup = GROUP_26_45;
        else if (a >= 46 && a <= 60) ageGroup = GROUP_46_60;
        else if (a >= 61 && a <= 100) ageGroup = GROUP_61_100;
        else ageGroup = GROUP_UNKNOWN;
    }
};

#endif // RESIDENT_HPP
