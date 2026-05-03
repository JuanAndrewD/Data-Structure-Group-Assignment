#include "LinkedList.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <map>
#include <string>
#include <functional>

static void printSeparator(int width = 80) {
    std::cout << std::string(width, '-') << std::endl;
}
static void printDoubleSeparator(int width = 80) {
    std::cout << std::string(width, '=') << std::endl;
}

void LinkedList::reverseList() {
    Node* prev = nullptr;
    Node* curr = head;
    while (curr) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

static void swapNodeData(Node* a, Node* b) {
    std::swap(a->residentID, b->residentID);
    std::swap(a->age, b->age);
    std::swap(a->modeOfTransport, b->modeOfTransport);
    std::swap(a->dailyDistance, b->dailyDistance);
    std::swap(a->carbonEmissionFactor, b->carbonEmissionFactor);
    std::swap(a->averageDayPerMonth, b->averageDayPerMonth);
    std::swap(a->carbonEmission, b->carbonEmission);
    std::swap(a->ageGroup, b->ageGroup);
}

LinkedList::LinkedList() : head(nullptr), size(0) {}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current) {
        Node* nxt = current->next;
        delete current;
        current = nxt;
    }
}

// Add new node at the front
void LinkedList::insert(std::string id, int age, std::string mode, double dist, double factor, int days) {
    Node* newNode = new Node(id, age, mode, dist, factor, days);
    newNode->next = head;
    head = newNode;
    size++;
}

// Load one CSV file, show header + first 5 rows as head preview smtg smtg, i'll change this comment later
void LinkedList::readCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "ERROR: Cannot open file: " << filename << std::endl;
        return;
    }

    // Determine city label from filename
    std::string label;
    if (filename.find("cityA") != std::string::npos)
        label = "City A - Metropolitan City";
    else if (filename.find("cityB") != std::string::npos)
        label = "City B - University Town";
    else if (filename.find("cityC") != std::string::npos)
        label = "City C - Suburban/Rural Area";
    else
        label = filename;

    printDoubleSeparator(90);
    std::cout << "  Loading Dataset: " << label << "  (" << filename << ")" << std::endl;
    printDoubleSeparator(90);

    std::cout << std::left
              << std::setw(10) << "ID"
              << std::setw(6)  << "Age"
              << std::setw(14) << "Transport"
              << std::setw(12) << "Dist(km)"
              << std::setw(16) << "EmFactor(kg/km)"
              << std::setw(10) << "Days/Mo"
              << std::endl;
    printSeparator(90);

    std::string line;
    std::getline(file, line); // skip CSV header line

    int rowCount = 0;
    int previewRows = 5;

    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string id, mode, ageStr, distStr, factorStr, daysStr;
        int age, days;
        double dist, factor;

        std::getline(ss, id, ',');
        std::getline(ss, ageStr, ',');
        std::getline(ss, mode, ',');
        std::getline(ss, distStr, ',');
        std::getline(ss, factorStr, ',');
        std::getline(ss, daysStr, ',');

        // Trim whitespace
        auto trim = [](std::string& s) {
            size_t start = s.find_first_not_of(" \t\r\n");
            size_t end = s.find_last_not_of(" \t\r\n");
            s = (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
        };
        trim(id); trim(ageStr); trim(mode);
        trim(distStr); trim(factorStr); trim(daysStr);

        try {
            age    = std::stoi(ageStr);
            dist   = std::stod(distStr);
            factor = std::stod(factorStr);
            days   = std::stoi(daysStr);
        } catch (...) {
            std::cerr << "WARN: Skipping malformed row: " << line << std::endl;
            continue;
        }

        insert(id, age, mode, dist, factor, days);
        rowCount++;

        // Print first 5 rows as preview
        if (rowCount <= previewRows) {
            std::cout << std::left
                      << std::setw(10) << id
                      << std::setw(6)  << age
                      << std::setw(14) << mode
                      << std::setw(12) << dist
                      << std::setw(16) << factor
                      << std::setw(10) << days
                      << std::endl;
        }
        if (rowCount == previewRows) {
            std::cout << "  ... (showing first " << previewRows
                      << " rows only)" << std::endl;
        }
    }

    printSeparator(90);
    std::cout << "  Total records loaded from " << filename
              << ": " << rowCount << std::endl;
    printDoubleSeparator(90);
    std::cout << std::endl;

    file.close();
}

// Carbon emission = dailyDistance * carbonEmissionFactor * averageDayPerMonth
void LinkedList::calculateEmissions() {
    Node* current = head;
    while (current) {
        current->carbonEmission =
            current->dailyDistance *
            current->carbonEmissionFactor *
            current->averageDayPerMonth;
        current = current->next;
    }
}

// Assign age group based on age ranges from assignment spec
void LinkedList::categorizeAgeGroups() {
    Node* current = head;
    while (current) {
        int a = current->age;
        if (a >= 6  && a <= 17) current->ageGroup = GROUP_6_17;
        else if (a >= 18 && a <= 25) current->ageGroup = GROUP_18_25;
        else if (a >= 26 && a <= 45) current->ageGroup = GROUP_26_45;
        else if (a >= 46 && a <= 60) current->ageGroup = GROUP_46_60;
        else if (a >= 61 && a <= 100) current->ageGroup = GROUP_61_100;
        else current->ageGroup = GROUP_UNKNOWN;
        current = current->next;
    }
}

// Print all records in a table
void LinkedList::display() {
    printDoubleSeparator(95);
    std::cout << "  FULL RESIDENT LIST  (Total: " << size << " records)" << std::endl;
    printDoubleSeparator(95);

    std::cout << std::left
              << std::setw(10) << "ID"
              << std::setw(6) << "Age"
              << std::setw(14) << "AgeGroup"
              << std::setw(14) << "Transport"
              << std::setw(10) << "Dist(km)"
              << std::setw(16) << "EmFactor"
              << std::setw(10) << "Days/Mo"
              << std::setw(14) << "Emission(kg)"
              << std::endl;
    printSeparator(95);

    Node* current = head;
    int   row     = 0;
    while (current) {
        std::cout << std::left
                  << std::setw(10) << current->residentID
                  << std::setw(6)  << current->age
                  << std::setw(14) << ageGroupRange(current->ageGroup)
                  << std::setw(14) << current->modeOfTransport
                  << std::setw(10) << std::fixed << std::setprecision(1)
                                   << current->dailyDistance
                  << std::setw(16) << std::fixed << std::setprecision(3)
                                   << current->carbonEmissionFactor
                  << std::setw(10) << current->averageDayPerMonth
                  << std::setw(14) << std::fixed << std::setprecision(2)
                                   << current->carbonEmission
                  << std::endl;
        current = current->next;
        row++;
    }
    printSeparator(95);
    std::cout << "  Total records: " << row << std::endl;
    printDoubleSeparator(95);
}

void LinkedList::displayAnalytics() {
    const int NUM_GROUPS = 5;

    double totalEmission[NUM_GROUPS] = {0};
    int count[NUM_GROUPS] = {0};
    std::map<std::string, int> modeCount[NUM_GROUPS];
    std::map<std::string, double> modeEmission[NUM_GROUPS];

    Node* current = head;
    while (current) {
        int g = static_cast<int>(current->ageGroup);
        totalEmission[g] += current->carbonEmission;
        count[g]++;
        modeCount[g][current->modeOfTransport]++;
        modeEmission[g][current->modeOfTransport] += current->carbonEmission;
        current = current->next;
    }

    // Per-age-group breakdown (matches PDF sample format)
    for (int i = 0; i < NUM_GROUPS; i++) {
        if (count[i] == 0) continue;

        // Average Emission = Total Emission in Age Group / Number of Residents in Age Group
        double avg = totalEmission[i] / count[i];

        std::cout << "\nAge Group: " << ageGroupRange(static_cast<AgeGroup>(i))
                  << " (" << ageGroupLabel(static_cast<AgeGroup>(i)) << ")\n";
        printSeparator(65);
        std::cout << std::left
                  << std::setw(16) << "Mode of Transport"
                  << std::setw(8)  << "Count"
                  << std::setw(24) << "Total Emission (kg CO2)"
                  << std::setw(20) << "Average per Resident"
                  << "\n";
        printSeparator(65);

        for (auto& kv : modeEmission[i]) {
            const std::string& mode = kv.first;
            double modeTotal = kv.second;
            int    mc        = modeCount[i][mode];
            // Average per resident for this mode within the age group
            double modeAvg   = (mc > 0) ? modeTotal / mc : 0.0;
            std::cout << std::left
                      << std::setw(16) << mode
                      << std::setw(8)  << mc
                      << std::setw(24) << std::fixed << std::setprecision(2) << modeTotal
                      << std::setw(20) << std::fixed << std::setprecision(2) << modeAvg
                      << "\n";
        }
        printSeparator(65);
        std::cout << "Total Emission for Age Group: "
                  << std::fixed << std::setprecision(2) << totalEmission[i] << " kg CO2\n";
        std::cout << "Average Emission per Resident: "
                  << std::fixed << std::setprecision(2) << avg << " kg CO2\n";
    }

    // Summary table across all age groups
    double grandTotal = 0;
    printDoubleSeparator(85);
    std::cout << "  SUMMARY : ALL AGE GROUPS\n";
    printDoubleSeparator(85);
    std::cout << std::left
              << std::setw(26) << "Age Group"
              << std::setw(10) << "Count"
              << std::setw(22) << "Total Emission (kg CO2)"
              << std::setw(22) << "Avg per Resident"
              << std::setw(20) << "Top Transport Mode"
              << "\n";
    printSeparator(85);

    for (int i = 0; i < NUM_GROUPS; i++) {
        double avg = (count[i] > 0) ? totalEmission[i] / count[i] : 0.0;
        grandTotal += totalEmission[i];

        std::string topMode = "N/A";
        int topCount = 0;
        for (auto& kv : modeCount[i]) {
            if (kv.second > topCount) { topCount = kv.second; topMode = kv.first; }
        }

        std::cout << std::left
                  << std::setw(26) << ageGroupLabel(static_cast<AgeGroup>(i))
                  << std::setw(10) << count[i]
                  << std::setw(22) << std::fixed << std::setprecision(2) << totalEmission[i]
                  << std::setw(22) << std::fixed << std::setprecision(2) << avg
                  << std::setw(20) << topMode
                  << "\n";
    }
    printSeparator(85);
    std::cout << std::left
              << std::setw(36) << "GRAND TOTAL"
              << std::setw(22) << std::fixed << std::setprecision(2) << grandTotal
              << "\n";
    printDoubleSeparator(85);

    // Emissions by transport mode (all cities combined)
    std::map<std::string, int>    allModeCount;
    std::map<std::string, double> allModeEmission;
    current = head;
    while (current) {
        allModeCount[current->modeOfTransport]++;
        allModeEmission[current->modeOfTransport] += current->carbonEmission;
        current = current->next;
    }

    printDoubleSeparator(75);
    std::cout << "  CARBON EMISSION BY TRANSPORT MODE (All Cities)\n";
    printDoubleSeparator(75);
    std::cout << std::left
              << std::setw(16) << "Transport Mode"
              << std::setw(10) << "Count"
              << std::setw(24) << "Total Emission (kg CO2)"
              << std::setw(20) << "Avg per Resident"
              << "\n";
    printSeparator(75);
    for (auto& kv : allModeEmission) {
        int    mc   = allModeCount[kv.first];
        double mAvg = (mc > 0) ? kv.second / mc : 0.0;
        std::cout << std::left
                  << std::setw(16) << kv.first
                  << std::setw(10) << mc
                  << std::setw(24) << std::fixed << std::setprecision(2) << kv.second
                  << std::setw(20) << std::fixed << std::setprecision(2) << mAvg
                  << "\n";
    }
    printSeparator(75);
    std::cout << std::left
              << std::setw(26) << "TOTAL"
              << std::setw(24) << std::fixed << std::setprecision(2) << grandTotal
              << "\n";
    printDoubleSeparator(75);
}

void LinkedList::displayPerformanceSummary() {
    const int SORT_RUNS = 5;

    printDoubleSeparator(95);
    std::cout << "SORTING ALGORITHM PERFORMANCE ANALYSIS: Bubble Sort vs Merge Sort\n";
    printDoubleSeparator(95);
    std::cout << std::left
              << std::setw(20) << "Sort By"
              << std::setw(25) << "Bubble Sort (s)"
              << std::setw(25) << "Merge Sort (s)"
              << std::setw(20) << "Faster"
              << "\n";
    printSeparator(95);

    // Timing helper: time a lambda for SORT_RUNS iterations, return avg seconds
    auto benchSort = [&](
        void (LinkedList::*bubbleFn)(std::chrono::duration<double>&),
        void (LinkedList::*mergeFn) (std::chrono::duration<double>&),
        double& bAvg, double& mAvg)
    {
        double bTotal = 0.0, mTotal = 0.0;
        for (int i = 0; i < SORT_RUNS; i++) {
            std::chrono::duration<double> t;
            reverseList();
            (this->*bubbleFn)(t);
            bTotal += t.count();
            reverseList();
            (this->*mergeFn)(t);
            mTotal += t.count();
        }
        bAvg = bTotal / SORT_RUNS;
        mAvg = mTotal / SORT_RUNS;
    };

    double bAvg, mAvg;

    benchSort(&LinkedList::bubbleSortByAge, &LinkedList::mergeSortByAge, bAvg, mAvg);
    std::cout << std::left << std::setw(18) << "Age"
              << std::setw(26) << std::fixed << std::setprecision(10) << bAvg
              << std::setw(26) << std::fixed << std::setprecision(10) << mAvg
              << (mAvg < bAvg ? "Merge Sort" : "Bubble Sort") << "\n";

    reverseList();
    benchSort(&LinkedList::bubbleSortByDistance, &LinkedList::mergeSortByDistance, bAvg, mAvg);
    std::cout << std::left << std::setw(18) << "Daily Distance"
              << std::setw(26) << std::fixed << std::setprecision(10) << bAvg
              << std::setw(26) << std::fixed << std::setprecision(10) << mAvg
              << (mAvg < bAvg ? "Merge Sort" : "Bubble Sort") << "\n";

    reverseList();
    benchSort(&LinkedList::bubbleSortByEmission, &LinkedList::mergeSortByEmission, bAvg, mAvg);
    std::cout << std::left << std::setw(18) << "Carbon Emission"
              << std::setw(26) << std::fixed << std::setprecision(10) << bAvg
              << std::setw(26) << std::fixed << std::setprecision(10) << mAvg
              << (mAvg < bAvg ? "Merge Sort" : "Bubble Sort") << "\n";

    printDoubleSeparator(95);

    const int SEARCH_RUNS = 1000;

    // Timing helper: time a lambda for SEARCH_RUNS iterations, return avg seconds
    auto timeIt = [&](std::function<void()> fn) -> double {
        auto t0 = std::chrono::high_resolution_clock::now();
        for (int r = 0; r < SEARCH_RUNS; r++) fn();
        std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - t0;
        return elapsed.count() / double(SEARCH_RUNS);
    };

    printDoubleSeparator(95);
    std::cout << "SEARCHING ALGORITHMS PERFORMANCE ANALYSIS: Linear vs Early-Exit vs Binary\n";
    printDoubleSeparator(95);
    std::cout << std::left
              << std::setw(20) << "Search By"
              << std::setw(25) << "Linear (s)"
              << std::setw(25) << "Early-Exit (s)"
              << std::setw(25) << "Binary (s)"
              << std::setw(20) << "Fastest"
              << "\n";
    printSeparator(95);

    std::chrono::duration<double> dummy;

    {
        AgeGroup testGroup = GROUP_26_45;

        double lt = timeIt([&]() {
            volatile int hits = 0;
            for (Node* c = head; c; c = c->next)
                if (c->ageGroup == testGroup) hits++;
        });

        mergeSortByAge(dummy); // sort for early-exit and binary

        double et = timeIt([&]() {
            volatile int hits = 0;
            for (Node* c = head; c; c = c->next) {
                if (c->ageGroup > testGroup) break;
                if (c->ageGroup == testGroup) hits++;
            }
        });

        double bt = timeIt([&]() {
            Node* sn = head, *ln = nullptr;
            while (true) {
                Node* mid = getMiddle(sn, ln);
                if (!mid || sn == ln) break;
                if (mid->ageGroup == testGroup) break;
                if (mid->ageGroup < testGroup) sn = mid->next;
                else ln = mid;
            }
        });

        double mn = std::min(lt, std::min(et, bt));
        std::string fastest = (mn == lt) ? "Linear" : (mn == et) ? "Early-Exit" : "Binary";
        std::cout << std::left << std::setw(20) << "Age Group"
                  << std::setw(25) << std::fixed << std::setprecision(10) << lt
                  << std::setw(25) << std::fixed << std::setprecision(10) << et
                  << std::setw(25) << std::fixed << std::setprecision(10) << bt
                  << fastest << "\n";
    }

    {
        std::string testMode = "Car";

        double lt = timeIt([&]() {
            volatile int hits = 0;
            for (Node* c = head; c; c = c->next)
                if (c->modeOfTransport == testMode) hits++;
        });

        bubbleSortByMode(dummy);

        double et = timeIt([&]() {
            volatile int hits = 0;
            for (Node* c = head; c; c = c->next) {
                if (c->modeOfTransport > testMode) break;
                if (c->modeOfTransport == testMode) hits++;
            }
        });

        double bt = timeIt([&]() {
            Node* sn = head, *ln = nullptr;
            while (true) {
                Node* mid = getMiddle(sn, ln);
                if (!mid || sn == ln) break;
                if (mid->modeOfTransport == testMode) break;
                if (mid->modeOfTransport < testMode) sn = mid->next;
                else ln = mid;
            }
        });

        double mn = std::min(lt, std::min(et, bt));
        std::string fastest = (mn == lt) ? "Linear" : (mn == et) ? "Early-Exit" : "Binary";
        std::cout << std::left << std::setw(20) << "Transport Mode"
                  << std::setw(25) << std::fixed << std::setprecision(10) << lt
                  << std::setw(25) << std::fixed << std::setprecision(10) << et
                  << std::setw(25) << std::fixed << std::setprecision(10) << bt
                  << fastest << "\n";
    }

    {
        double testThreshold = 15.0;

        double lt = timeIt([&]() {
            volatile int hits = 0;
            for (Node* c = head; c; c = c->next)
                if (c->dailyDistance > testThreshold) hits++;
        });

        mergeSortByDistance(dummy);

        double et = timeIt([&]() {
            volatile int hits = 0;
            for (Node* c = head; c; c = c->next)
                if (c->dailyDistance > testThreshold) hits++;
        });

        double bt = timeIt([&]() {
            Node* sn = head, *ln = nullptr;
            while (true) {
                Node* mid = getMiddle(sn, ln);
                if (!mid || sn == ln) break;
                if (mid->dailyDistance > testThreshold) ln = mid;
                else sn = mid->next;
            }
        });

        double mn = std::min(lt, std::min(et, bt));
        std::string fastest = (mn == lt) ? "Linear" : (mn == et) ? "Early-Exit" : "Binary";
        std::cout << std::left << std::setw(20) << "Distance > 15km"
                  << std::setw(25) << std::fixed << std::setprecision(10) << lt
                  << std::setw(25) << std::fixed << std::setprecision(10) << et
                  << std::setw(25) << std::fixed << std::setprecision(10) << bt
                  << fastest << "\n";
    }

    printDoubleSeparator(95);
}

void LinkedList::displayInsights() {
    const int NUM_GROUPS = 5;

    double totalEmission[NUM_GROUPS] = {0};
    int count[NUM_GROUPS] = {0};
    std::map<std::string, double> modeEmission;
    std::map<std::string, int> modeCount;
    // Track most preferred mode per age group
    std::map<std::string, int> modeCountPerGroup[NUM_GROUPS];

    Node* current = head;
    while (current) {
        int g = static_cast<int>(current->ageGroup);
        totalEmission[g] += current->carbonEmission;
        count[g]++;
        modeEmission[current->modeOfTransport] += current->carbonEmission;
        modeCount[current->modeOfTransport]++;
        modeCountPerGroup[g][current->modeOfTransport]++;
        current = current->next;
    }

    // Find highest-emitting age group
    int highGroup = 0;
    for (int i = 1; i < NUM_GROUPS; i++) {
        if (totalEmission[i] > totalEmission[highGroup]) highGroup = i;
    }

    // Find highest-emitting transport mode
    std::string highMode = "";
    double highModeEmit  = -1;
    for (auto& kv : modeEmission) {
        if (kv.second > highModeEmit) { highModeEmit = kv.second; highMode = kv.first; }
    }

    // Find most preferred mode per age group
    std::string topModePerGroup[NUM_GROUPS];
    for (int i = 0; i < NUM_GROUPS; i++) {
        int best = 0;
        for (auto& kv : modeCountPerGroup[i]) {
            if (kv.second > best) { best = kv.second; topModePerGroup[i] = kv.first; }
        }
    }

    printDoubleSeparator(80);
    std::cout << "  INSIGHTS FOR THE CITY\n";
    printDoubleSeparator(80);

    std::cout << std::left
              << std::setw(20) << "Age Group"
              << std::setw(10) << "Residents"
              << std::setw(24) << "Total Emission (kg CO2)"
              << std::setw(22) << "Avg per Resident"
              << std::setw(18) << "Top Transport"
              << "\n";
    printSeparator(80);
    for (int i = 0; i < NUM_GROUPS; i++) {
        // Average Emission = Total Emission in Age Group / Number of Residents in Age Group
        double avg = (count[i] > 0) ? totalEmission[i] / count[i] : 0.0;
        std::string marker = (i == highGroup) ? " <-- highest" : "";
        std::cout << std::left
                  << std::setw(20) << ageGroupLabel(static_cast<AgeGroup>(i))
                  << std::setw(10) << count[i]
                  << std::setw(24) << std::fixed << std::setprecision(2) << totalEmission[i]
                  << std::setw(22) << std::fixed << std::setprecision(2) << avg
                  << std::setw(18) << topModePerGroup[i]
                  << marker << "\n";
    }
    printSeparator(80);

    std::cout << "\n  KEY FINDINGS:\n";
    std::cout << "  1. Highest emitting age group : "
              << ageGroupLabel(static_cast<AgeGroup>(highGroup))
              << " (" << std::fixed << std::setprecision(2)
              << totalEmission[highGroup] << " kg CO2/month)\n";
    std::cout << "  2. Highest emitting transport : "
              << highMode << " (" << std::fixed << std::setprecision(2)
              << highModeEmit << " kg CO2/month)\n";
}

// Show sorted result and timing
void LinkedList::sortByAge(int algorithm) {
    std::chrono::duration<double> t;
    if (algorithm == 0) {
        bubbleSortByAge(t);
        printDoubleSeparator(60);
        std::cout << "Bubble Sort by Age completed.\n";
        std::cout << "Time: " << std::fixed << std::setprecision(8) << t.count() << " s\n";
        std::cout << "  Time Complexity: O(n^2)   Space: O(1)\n";
        printDoubleSeparator(60);
    } else {
        mergeSortByAge(t);
        printDoubleSeparator(60);
        std::cout << "  Merge Sort by Age completed.\n";
        std::cout << "  Time: " << std::fixed << std::setprecision(8) << t.count() << " s\n";
        std::cout << "  Time Complexity: O(n log n)  Space: O(log n)\n";
        printDoubleSeparator(60);
    }
    std::cout << "  Sorted records (by Age):\n";
    printSeparator(70);
    std::cout << std::left
              << std::setw(10) << "ID"
              << std::setw(6)  << "Age"
              << std::setw(14) << "Age Group"
              << std::setw(14) << "Transport"
              << std::setw(12) << "Dist(km)"
              << std::setw(14) << "Emission(kg)"
              << "\n";
    printSeparator(70);
    Node* cur = head;
    while (cur) {
        std::cout << std::left
                  << std::setw(10) << cur->residentID
                  << std::setw(6)  << cur->age
                  << std::setw(14) << ageGroupRange(cur->ageGroup)
                  << std::setw(14) << cur->modeOfTransport
                  << std::setw(12) << std::fixed << std::setprecision(1) << cur->dailyDistance
                  << std::setw(14) << std::fixed << std::setprecision(2) << cur->carbonEmission
                  << "\n";
        cur = cur->next;
    }
    printSeparator(70);
    std::cout << "  Total records: " << size << "\n";
}

void LinkedList::sortByDistance(int algorithm) {
    std::chrono::duration<double> t;
    if (algorithm == 0) {
        bubbleSortByDistance(t);
        printDoubleSeparator(65);
        std::cout << "  Bubble Sort by Distance completed.\n";
        std::cout << "  Time: " << std::fixed << std::setprecision(8) << t.count() << " s\n";
        std::cout << "  Time Complexity: O(n^2)   Space: O(1)\n";
        printDoubleSeparator(65);
    } else {
        mergeSortByDistance(t);
        printDoubleSeparator(65);
        std::cout << "  Merge Sort by Distance completed.\n";
        std::cout << "  Time: " << std::fixed << std::setprecision(8) << t.count() << " s\n";
        std::cout << "  Time Complexity: O(n log n)  Space: O(log n)\n";
        printDoubleSeparator(65);
    }
    std::cout << "  Sorted records (by Daily Distance):\n";
    printSeparator(65);
    std::cout << std::left
              << std::setw(10) << "ID"
              << std::setw(6)  << "Age"
              << std::setw(14) << "Transport"
              << std::setw(12) << "Dist(km)"
              << std::setw(14) << "Emission(kg)"
              << "\n";
    printSeparator(65);
    Node* cur = head;
    while (cur) {
        std::cout << std::left
                  << std::setw(10) << cur->residentID
                  << std::setw(6)  << cur->age
                  << std::setw(14) << cur->modeOfTransport
                  << std::setw(12) << std::fixed << std::setprecision(1) << cur->dailyDistance
                  << std::setw(14) << std::fixed << std::setprecision(2) << cur->carbonEmission
                  << "\n";
        cur = cur->next;
    }
    printSeparator(65);
    std::cout << "  Total records: " << size << "\n";
}

void LinkedList::sortByEmission(int algorithm) {
    std::chrono::duration<double> t;
    if (algorithm == 0) {
        bubbleSortByEmission(t);
        printDoubleSeparator(65);
        std::cout << "  Bubble Sort by Emission completed.\n";
        std::cout << "  Time: " << std::fixed << std::setprecision(8) << t.count() << " s\n";
        std::cout << "  Time Complexity: O(n^2)   Space: O(1)\n";
        printDoubleSeparator(65);
    } else {
        mergeSortByEmission(t);
        printDoubleSeparator(65);
        std::cout << "  Merge Sort by Emission completed.\n";
        std::cout << "  Time: " << std::fixed << std::setprecision(8) << t.count() << " s\n";
        std::cout << "  Time Complexity: O(n log n)  Space: O(log n)\n";
        printDoubleSeparator(65);
    }
    std::cout << "  Sorted records (by Carbon Emission, ascending):\n";
    printSeparator(65);
    std::cout << std::left
              << std::setw(10) << "ID"
              << std::setw(6)  << "Age"
              << std::setw(14) << "Transport"
              << std::setw(12) << "Dist(km)"
              << std::setw(14) << "Emission(kg)"
              << "\n";
    printSeparator(65);
    Node* cur = head;
    while (cur) {
        std::cout << std::left
                  << std::setw(10) << cur->residentID
                  << std::setw(6)  << cur->age
                  << std::setw(14) << cur->modeOfTransport
                  << std::setw(12) << std::fixed << std::setprecision(1) << cur->dailyDistance
                  << std::setw(14) << std::fixed << std::setprecision(2) << cur->carbonEmission
                  << "\n";
        cur = cur->next;
    }
    printSeparator(65);
    std::cout << "  Total records: " << size << "\n";
}

// Bubble Sort : O(n^2), swaps node data in-place, O(1) space
void LinkedList::bubbleSortByAge(std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    if (!head) { time = std::chrono::duration<double>(0); return; }
    bool swapped;
    do {
        swapped = false;
        Node* cur = head;
        while (cur->next) {
            if (cur->age > cur->next->age) {
                swapNodeData(cur, cur->next);
                swapped = true;
            }
            cur = cur->next;
        }
    } while (swapped);
    time = std::chrono::high_resolution_clock::now() - start;
}

void LinkedList::bubbleSortByDistance(std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    if (!head) { time = std::chrono::duration<double>(0); return; }
    bool swapped;
    do {
        swapped = false;
        Node* cur = head;
        while (cur->next) {
            if (cur->dailyDistance > cur->next->dailyDistance) {
                swapNodeData(cur, cur->next);
                swapped = true;
            }
            cur = cur->next;
        }
    } while (swapped);
    time = std::chrono::high_resolution_clock::now() - start;
}

void LinkedList::bubbleSortByEmission(std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    if (!head) { time = std::chrono::duration<double>(0); return; }
    bool swapped;
    do {
        swapped = false;
        Node* cur = head;
        while (cur->next) {
            if (cur->carbonEmission > cur->next->carbonEmission) {
                swapNodeData(cur, cur->next);
                swapped = true;
            }
            cur = cur->next;
        }
    } while (swapped);
    time = std::chrono::high_resolution_clock::now() - start;
}

// Pre-sort by mode name for early-exit / binary search
void LinkedList::bubbleSortByMode(std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    if (!head) { time = std::chrono::duration<double>(0); return; }
    bool swapped;
    do {
        swapped = false;
        Node* cur = head;
        while (cur->next) {
            if (cur->modeOfTransport > cur->next->modeOfTransport) {
                swapNodeData(cur, cur->next);
                swapped = true;
            }
            cur = cur->next;
        }
    } while (swapped);
    time = std::chrono::high_resolution_clock::now() - start;
}

// Merge Sort
void LinkedList::mergeSortByAge(std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    head = mergeSort(head, 0);
    time = std::chrono::high_resolution_clock::now() - start;
}

void LinkedList::mergeSortByDistance(std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    head = mergeSort(head, 1);
    time = std::chrono::high_resolution_clock::now() - start;
}

void LinkedList::mergeSortByEmission(std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    head = mergeSort(head, 2);
    time = std::chrono::high_resolution_clock::now() - start;
}

// Recursively split, sort each half, then merge
Node* LinkedList::mergeSort(Node* h, int sortType) {
    if (!h || !h->next) return h;

    // Find mid-point using fast/slow pointer (Tortoise & Hare)
    Node* slow = h;
    Node* fast = h->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* mid  = slow->next;
    slow->next = nullptr;   // split the list

    Node* left  = mergeSort(h,   sortType);
    Node* right = mergeSort(mid, sortType);

    return merge(left, right, sortType);
}

// Merge two sorted sub-lists by chosen sort key
Node* LinkedList::merge(Node* left, Node* right, int sortType) {
    if (!left)  return right;
    if (!right) return left;

    bool takeLeft;
    if (sortType == 0) takeLeft = (left->age <= right->age);
    else if (sortType == 1) takeLeft = (left->dailyDistance <= right->dailyDistance);
    else takeLeft = (left->carbonEmission <= right->carbonEmission);

    if (takeLeft) {
        left->next = merge(left->next, right, sortType);
        return left;
    } else {
        right->next = merge(left, right->next, sortType);
        return right;
    }
}

// Find middle node using slow/fast pointer
Node* LinkedList::getMiddle(Node* start, Node* last) {
    if (!start) return nullptr;
    if (start == last) return start;
    Node* slow = start;
    Node* fast = start->next;
    while (fast != last) {
        fast = fast->next;
        slow = slow->next;
        if (fast != last) fast = fast->next;
    }
    return slow;
}

// Search by Age Group
// Helper: print one resident row
static void printSearchRow(Node* n) {
    std::cout << std::left
              << std::setw(10) << n->residentID
              << std::setw(6)  << n->age
              << std::setw(14) << ageGroupRange(n->ageGroup)
              << std::setw(14) << n->modeOfTransport
              << std::setw(10) << std::fixed << std::setprecision(1)
                               << n->dailyDistance
              << std::setw(14) << std::fixed << std::setprecision(2)
                               << n->carbonEmission
              << std::endl;
}
static void printSearchHeader() {
    std::cout << std::left
              << std::setw(10) << "ID"
              << std::setw(6) << "Age"
              << std::setw(14) << "AgeGroup"
              << std::setw(14) << "Transport"
              << std::setw(10) << "Dist(km)"
              << std::setw(14) << "Emission(kg)"
              << std::endl;
    printSeparator(68);
}

// Linear search : scans every node, O(n)
void LinkedList::linearSearchByAge(AgeGroup group, std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    int  found = 0;
    printDoubleSeparator(68);
    std::cout << "Linear Search (Unsorted) : Age Group: "
              << ageGroupLabel(group) << std::endl;
    printDoubleSeparator(68);
    printSearchHeader();
    Node* cur = head;
    while (cur) {
        if (cur->ageGroup == group) { printSearchRow(cur); found++; }
        cur = cur->next;
    }
    time = std::chrono::high_resolution_clock::now() - start;
    printSeparator(68);
    std::cout << "Matches found : " << found << std::endl;
    std::cout << "Time : " << std::fixed << std::setprecision(8)
              << time.count() << "s | Complexity: O(n)" << std::endl;
    printDoubleSeparator(68);
}

// Early-exit search : stops once past the target group in sorted data, O(k)
void LinkedList::earlyExitSearchByAge(AgeGroup group, std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    int  found = 0;
    printDoubleSeparator(68);
    std::cout << "Early-Exit Search (Sorted) : Age Group: "
              << ageGroupLabel(group) << std::endl;
    printDoubleSeparator(68);
    printSearchHeader();
    Node* cur = head;
    while (cur) {
        if (cur->ageGroup > group) {
            std::cout << "Early exit : passed target group" << std::endl;
            break;
        }
        if (cur->ageGroup == group) { printSearchRow(cur); found++; }
        cur = cur->next;
    }
    time = std::chrono::high_resolution_clock::now() - start;
    printSeparator(68);
    std::cout << "Matches found : " << found << std::endl;
    std::cout << "Time : " << std::fixed << std::setprecision(8)
              << time.count() << "s | Complexity: O(k) where k = matches+1" << std::endl;
    printDoubleSeparator(68);
}

// Binary search : sorted data, finds one match (linked list limitation)
void LinkedList::binarySearchByAge(AgeGroup group, std::chrono::duration<double>& time) {
    auto  start     = std::chrono::high_resolution_clock::now();
    bool  found     = false;
    Node* startNode = head;
    Node* lastNode  = nullptr;

    printDoubleSeparator(68);
    std::cout << "Binary Search (Sorted) : Age Group: "
              << ageGroupLabel(group) << std::endl;
    std::cout << "NOTE: Binary search on a linked list finds the FIRST match only\n"
              << "(random access is O(n); this is for experimental comparison)\n";
    printDoubleSeparator(68);
    printSearchHeader();

    while (true) {
        Node* mid = getMiddle(startNode, lastNode);
        if (!mid) break;
        if (mid->ageGroup == group) {
            printSearchRow(mid);
            std::cout << "First match found : binary search stops here" << std::endl;
            found = true;
            break;
        }
        if (startNode == lastNode) break;
        if (mid->ageGroup < group) startNode = mid->next;
        else                        lastNode  = mid;
    }

    time = std::chrono::high_resolution_clock::now() - start;
    printSeparator(68);
    if (!found) std::cout << "No residents found in this age group." << std::endl;
    std::cout << "Time : " << std::fixed << std::setprecision(8)
              << time.count() << "s | Complexity: O(n) per access (LL limitation)" << std::endl;
    printDoubleSeparator(68);
}

// Linear search first-match only : stops at first hit
void LinkedList::linearSearchFirstByAge(AgeGroup group, std::chrono::duration<double>& time) {
    auto  start = std::chrono::high_resolution_clock::now();
    bool  found = false;
    printDoubleSeparator(68);
    std::cout << "Linear Search - First Match Only (Unsorted) : Age Group: "
              << ageGroupLabel(group) << std::endl;
    printDoubleSeparator(68);
    printSearchHeader();
    Node* cur = head;
    while (cur) {
        if (cur->ageGroup == group) {
            printSearchRow(cur);
            found = true;
            break;
        }
        cur = cur->next;
    }
    time = std::chrono::high_resolution_clock::now() - start;
    printSeparator(68);
    if (!found) std::cout << "No resident found in this age group." << std::endl;
    else        std::cout << "First match found : search stopped early." << std::endl;
    std::cout << "Time : " << std::fixed << std::setprecision(8)
              << time.count() << "s | Complexity: O(n) worst, O(1) best" << std::endl;
    printDoubleSeparator(68);
}

void LinkedList::searchAge(int algorithm, AgeGroup group) {
    std::chrono::duration<double> t;
    if      (algorithm == 0) linearSearchByAge(group, t);
    else if (algorithm == 1) earlyExitSearchByAge(group, t);
    else if (algorithm == 2) binarySearchByAge(group, t);
    else if (algorithm == 3) linearSearchFirstByAge(group, t);
    else std::cout << "Invalid algorithm choice." << std::endl;
}

// Search by Mode of Transport
// Linear search : unsorted, O(n)
void LinkedList::linearSearchByMode(const std::string& mode, std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    int  found = 0;
    printDoubleSeparator(68);
    std::cout << "Linear Search (Unsorted) : Mode: " << mode << std::endl;
    printDoubleSeparator(68);
    printSearchHeader();
    Node* cur = head;
    while (cur) {
        if (cur->modeOfTransport == mode) { printSearchRow(cur); found++; }
        cur = cur->next;
    }
    time = std::chrono::high_resolution_clock::now() - start;
    printSeparator(68);
    std::cout << "Matches found : " << found << std::endl;
    std::cout << "Time : " << std::fixed << std::setprecision(8)
              << time.count() << "s | Complexity: O(n)" << std::endl;
    printDoubleSeparator(68);
}

// Early-exit search : sorted by mode alphabetically, stops after passing target, O(k)
void LinkedList::earlyExitSearchByMode(const std::string& mode, std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    int  found = 0;
    printDoubleSeparator(68);
    std::cout << "Early-Exit Search (Sorted) : Mode: " << mode << std::endl;
    printDoubleSeparator(68);
    printSearchHeader();
    Node* cur = head;
    while (cur) {
        if (cur->modeOfTransport > mode) {
            std::cout << "Early exit : passed target mode alphabetically" << std::endl;
            break;
        }
        if (cur->modeOfTransport == mode) { printSearchRow(cur); found++; }
        cur = cur->next;
    }
    time = std::chrono::high_resolution_clock::now() - start;
    printSeparator(68);
    std::cout << "Matches found : " << found << std::endl;
    std::cout << "Time : " << std::fixed << std::setprecision(8)
              << time.count() << "s | Complexity: O(k)" << std::endl;
    printDoubleSeparator(68);
}

// Binary search by mode : sorted, finds first match only
void LinkedList::binarySearchByMode(const std::string& mode, std::chrono::duration<double>& time) {
    auto  start = std::chrono::high_resolution_clock::now();
    bool  found = false;
    Node* startNode = head;
    Node* lastNode  = nullptr;

    printDoubleSeparator(68);
    std::cout << "Binary Search (Sorted) : Mode: " << mode << std::endl;
    std::cout << "NOTE: Finds first match only (linked list binary search limitation)\n";
    printDoubleSeparator(68);
    printSearchHeader();

    while (true) {
        Node* mid = getMiddle(startNode, lastNode);
        if (!mid) break;
        if (mid->modeOfTransport == mode) {
            printSearchRow(mid);
            std::cout << "First match found : binary search stops here" << std::endl;
            found = true;
            break;
        }
        if (startNode == lastNode) break;
        if (mid->modeOfTransport < mode) startNode = mid->next;
        else                              lastNode  = mid;
    }

    time = std::chrono::high_resolution_clock::now() - start;
    printSeparator(68);
    if (!found) std::cout << "Mode '" << mode << "' not found." << std::endl;
    std::cout << "Time : " << std::fixed << std::setprecision(8)
              << time.count() << "s | Complexity: O(n) per access (LL limitation)" << std::endl;
    printDoubleSeparator(68);
}

// Linear search first-match only : stops at first hit
void LinkedList::linearSearchFirstByMode(const std::string& mode, std::chrono::duration<double>& time) {
    auto  start = std::chrono::high_resolution_clock::now();
    bool  found = false;
    printDoubleSeparator(68);
    std::cout << "Linear Search - First Match Only (Unsorted) : Mode: " << mode << std::endl;
    printDoubleSeparator(68);
    printSearchHeader();
    Node* cur = head;
    while (cur) {
        if (cur->modeOfTransport == mode) {
            printSearchRow(cur);
            found = true;
            break;
        }
        cur = cur->next;
    }
    time = std::chrono::high_resolution_clock::now() - start;
    printSeparator(68);
    if (!found) std::cout << "Mode '" << mode << "' not found." << std::endl;
    else        std::cout << "First match found : search stopped early." << std::endl;
    std::cout << "Time : " << std::fixed << std::setprecision(8)
              << time.count() << "s | Complexity: O(n) worst, O(1) best" << std::endl;
    printDoubleSeparator(68);
}

void LinkedList::searchMode(int algorithm, const std::string& mode) {
    std::chrono::duration<double> t;
    if (algorithm == 0) linearSearchByMode(mode, t);
    else if (algorithm == 1) earlyExitSearchByMode(mode, t);
    else if (algorithm == 2) binarySearchByMode(mode, t);
    else if (algorithm == 3) linearSearchFirstByMode(mode, t);
    else std::cout << "Invalid algorithm choice." << std::endl;
}

// Search by Daily Distance Threshold > X km
// Linear search : unsorted, finds all residents with distance > threshold, O(n)
void LinkedList::linearSearchByDistance(double threshold, std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    int  found = 0;
    printDoubleSeparator(68);
    std::cout << "Linear Search (Unsorted) : Distance > "
              << std::fixed << std::setprecision(1) << threshold << " km" << std::endl;
    printDoubleSeparator(68);
    printSearchHeader();
    Node* cur = head;
    while (cur) {
        if (cur->dailyDistance > threshold) { printSearchRow(cur); found++; }
        cur = cur->next;
    }
    time = std::chrono::high_resolution_clock::now() - start;
    printSeparator(68);
    std::cout << "Matches found : " << found << std::endl;
    std::cout << "Time : " << std::fixed << std::setprecision(8)
              << time.count() << "s | Complexity: O(n)" << std::endl;
    printDoubleSeparator(68);
}

// Early-exit search : sorted ascending; once distance > threshold all remaining qualify
void LinkedList::earlyExitSearchByDistance(double threshold, std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    int  found = 0;
    bool triggered = false;
    printDoubleSeparator(68);
    std::cout << "Early-Exit Search (Sorted) : Distance > "
              << std::fixed << std::setprecision(1) << threshold << " km" << std::endl;
    printDoubleSeparator(68);
    printSearchHeader();
    Node* cur = head;
    while (cur) {
        if (cur->dailyDistance > threshold) {
            if (!triggered) {
                std::cout << "Reached threshold : all remaining nodes qualify" << std::endl;
                triggered = true;
            }
            printSearchRow(cur);
            found++;
        }
        cur = cur->next;
    }
    time = std::chrono::high_resolution_clock::now() - start;
    printSeparator(68);
    std::cout << "Matches found : " << found << std::endl;
    std::cout << "Time : " << std::fixed << std::setprecision(8)
              << time.count() << "s | Complexity: O(n) best case O(k) after threshold" << std::endl;
    printDoubleSeparator(68);
}

// Binary search: sorted, locates boundary where distance > threshold then prints all
void LinkedList::binarySearchByDistance(double threshold, std::chrono::duration<double>& time) {
    auto  start = std::chrono::high_resolution_clock::now();
    bool  found = false;
    Node* startNode = head;
    Node* lastNode = nullptr;

    printDoubleSeparator(68);
    std::cout << "Binary Search (Sorted) : Distance > "
              << std::fixed << std::setprecision(1) << threshold << " km" << std::endl;
    std::cout << "NOTE: Locates first node > threshold; then prints all subsequent\n";
    printDoubleSeparator(68);
    printSearchHeader();

    // Binary search to find the first node with distance > threshold
    Node* firstOver = nullptr;
    Node* sn = head;
    Node* ln = nullptr;
    while (true) {
        Node* mid = getMiddle(sn, ln);
        if (!mid) break;
        if (mid->dailyDistance > threshold) {
            firstOver = mid;
            if (sn == ln) break;
            ln = mid;
        } else {
            if (sn == ln) break;
            sn = mid->next;
        }
    }

    // Print all nodes from firstOver onwards
    int cnt = 0;
    Node* cur = firstOver;
    while (cur) {
        if (cur->dailyDistance > threshold) {
            printSearchRow(cur);
            found = true;
            cnt++;
        }
        cur = cur->next;
    }

    time = std::chrono::high_resolution_clock::now() - start;
    printSeparator(68);
    if (!found) std::cout << "No residents with distance > " << threshold << " km." << std::endl;
    std::cout << "Matches found : " << cnt << std::endl;
    std::cout << "Time : " << std::fixed << std::setprecision(8)
              << time.count() << "s | Complexity: O(log n) locate + O(k) print" << std::endl;
    printDoubleSeparator(68);
}

// Linear search first-match only : stops at first node with distance > threshold
void LinkedList::linearSearchFirstByDistance(double threshold, std::chrono::duration<double>& time) {
    auto start = std::chrono::high_resolution_clock::now();
    bool found = false;
    printDoubleSeparator(68);
    std::cout << "Linear Search - First Match Only (Unsorted) : Distance > "
              << std::fixed << std::setprecision(1) << threshold << " km" << std::endl;
    printDoubleSeparator(68);
    printSearchHeader();
    Node* cur = head;
    while (cur) {
        if (cur->dailyDistance > threshold) {
            printSearchRow(cur);
            found = true;
            break;
        }
        cur = cur->next;
    }
    time = std::chrono::high_resolution_clock::now() - start;
    printSeparator(68);
    if (!found) std::cout << "No resident with distance > " << threshold << " km." << std::endl;
    else std::cout << "First match found : search stopped early." << std::endl;
    std::cout << "Time : " << std::fixed << std::setprecision(8)
              << time.count() << "s | Complexity: O(n) worst, O(1) best" << std::endl;
    printDoubleSeparator(68);
}

void LinkedList::searchDistance(int algorithm, double threshold) {
    std::chrono::duration<double> t;
    if (algorithm == 0) linearSearchByDistance(threshold, t);
    else if (algorithm == 1) earlyExitSearchByDistance(threshold, t);
    else if (algorithm == 2) binarySearchByDistance(threshold, t);
    else if (algorithm == 3) linearSearchFirstByDistance(threshold, t);
    else std::cout << "Invalid algorithm choice." << std::endl;
}