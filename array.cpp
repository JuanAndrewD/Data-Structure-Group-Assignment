#include "Array.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <cctype>
using namespace std;


// Convert String to Lowercase
string toLowerString(string s) {
    for (char& c : s) c = tolower(c);
    return s;
}

ResidentArray::ResidentArray() : size(0) {}
ResidentArray::~ResidentArray() {}


// Merge Sort Algorithm
void ResidentArray::mergeAge(int left, int mid, int right) {
    int i = left, j = mid + 1, k = 0;
    ArrayResident* temp = new ArrayResident[right - left + 1];
    while (i <= mid && j <= right) {
        if (arr[i].age <= arr[j].age) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (i = left, k = 0; i <= right; i++, k++) arr[i] = temp[k];
    delete[] temp;
}

void ResidentArray::mergeSortAge(int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSortAge(left, mid);
        mergeSortAge(mid + 1, right);
        mergeAge(left, mid, right);
    }
}

void ResidentArray::mergeDistance(int left, int mid, int right) {
    int i = left, j = mid + 1, k = 0;
    ArrayResident* temp = new ArrayResident[right - left + 1];
    while (i <= mid && j <= right) {
        if (arr[i].dailyDistance <= arr[j].dailyDistance) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (i = left, k = 0; i <= right; i++, k++) arr[i] = temp[k];
    delete[] temp;
}

void ResidentArray::mergeSortDistance(int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSortDistance(left, mid);
        mergeSortDistance(mid + 1, right);
        mergeDistance(left, mid, right);
    }
}

void ResidentArray::mergeEmission(int left, int mid, int right) {
    int i = left, j = mid + 1, k = 0;
    ArrayResident* temp = new ArrayResident[right - left + 1];
    while (i <= mid && j <= right) {
        if (arr[i].totalCarbon <= arr[j].totalCarbon) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (i = left, k = 0; i <= right; i++, k++) arr[i] = temp[k];
    delete[] temp;
}

void ResidentArray::mergeSortEmission(int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSortEmission(left, mid);
        mergeSortEmission(mid + 1, right);
        mergeEmission(left, mid, right);
    }
}


// Manage Data
void ResidentArray::readCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Cannot open file: " << filename << endl;
        return;
    }
    string line, token;
    getline(file, line);
    while (getline(file, line) && size < MAX_SIZE) {
        stringstream ss(line);
        getline(ss, arr[size].residentID, ',');
        getline(ss, token, ','); arr[size].age = stoi(token);
        getline(ss, arr[size].transportMode, ',');
        getline(ss, token, ','); arr[size].dailyDistance = stof(token);
        getline(ss, token, ','); arr[size].carbonFactor = stof(token);
        getline(ss, token, ','); arr[size].daysPerMonth = stoi(token);
        arr[size].totalCarbon = arr[size].dailyDistance * arr[size].carbonFactor * arr[size].daysPerMonth;
        size++;
    }
    file.close();
    cout << "Read successfully: " << filename << endl;
}

void ResidentArray::readAllCities() {
    size = 0;
    readCSV("dataset1-cityA.csv");
    readCSV("dataset2-cityB.csv");
    readCSV("dataset3-cityC.csv");
}

void ResidentArray::clearData() {
    size = 0;
}

void ResidentArray::printAll() {
    cout << "\nResidentID\tAge\tMode\tDistance\tTotalCarbon\n";
    for (int i = 0; i < size; i++) {
        cout << arr[i].residentID << "\t" << arr[i].age << "\t" << arr[i].transportMode
            << "\t" << fixed << setprecision(2) << arr[i].dailyDistance
            << "\t" << arr[i].totalCarbon << "\n";
    }
}

// Sorting Algorithms
void ResidentArray::sortByID() {
    if (size <= 1) return;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].residentID > arr[j + 1].residentID) swap(arr[j], arr[j + 1]);
        }
    }
}

void ResidentArray::sortByAgeBubble() {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].age > arr[j + 1].age) swap(arr[j], arr[j + 1]);
        }
    }
}

void ResidentArray::sortByAgeMerge() {
    if (size > 0) mergeSortAge(0, size - 1);
}

void ResidentArray::sortByDistanceBubble() {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].dailyDistance > arr[j + 1].dailyDistance) swap(arr[j], arr[j + 1]);
        }
    }
}

void ResidentArray::sortByDistanceMerge() {
    if (size > 0) mergeSortDistance(0, size - 1);
}

void ResidentArray::sortByEmissionBubble() {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].totalCarbon > arr[j + 1].totalCarbon) swap(arr[j], arr[j + 1]);
        }
    }
}

void ResidentArray::sortByEmissionMerge() {
    if (size > 0) mergeSortEmission(0, size - 1);
}

void ResidentArray::sortByModeBubble() {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (toLowerString(arr[j].transportMode) > toLowerString(arr[j + 1].transportMode)) swap(arr[j], arr[j + 1]);
        }
    }
}


// Searching Algorithms
int ResidentArray::linearSearch(const string& targetID) {
    for (int i = 0; i < size; i++) {
        if (arr[i].residentID == targetID) return i;
    }
    return -1;
}

int ResidentArray::binarySearch(const string& targetID) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid].residentID == targetID) return mid;
        if (arr[mid].residentID < targetID) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void ResidentArray::searchAgeRange(int minAge, int maxAge) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i].age >= minAge && arr[i].age <= maxAge) {
            cout << arr[i].residentID << " (" << arr[i].age << ")\n";
            count++;
        }
    }
    cout << "Total: " << count << endl;
}

void ResidentArray::searchAgeEarlyExit(int minAge, int maxAge) {
    sortByAgeMerge();
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i].age > maxAge) break;
        if (arr[i].age >= minAge) {
            cout << arr[i].residentID << " (" << arr[i].age << ")\n";
            count++;
        }
    }
    cout << "Total: " << count << endl;
}

void ResidentArray::searchAgeBinary(int minAge, int maxAge) {
    sortByAgeMerge();
    int left = 0, right = size - 1, startIdx = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].age >= minAge) { startIdx = mid; right = mid - 1; }
        else left = mid + 1;
    }
    int count = 0;
    if (startIdx != -1) {
        for (int i = startIdx; i < size && arr[i].age <= maxAge; i++) {
            cout << arr[i].residentID << " (" << arr[i].age << ")\n";
            count++;
        }
    }
    cout << "Total: " << count << endl;
}

void ResidentArray::searchTransport(const string& mode) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (toLowerString(arr[i].transportMode) == toLowerString(mode)) {
            cout << arr[i].residentID << "\n";
            count++;
        }
    }
    cout << "Total: " << count << endl;
}

void ResidentArray::searchTransportEarlyExit(const string& mode) {
    sortByModeBubble();
    string target = toLowerString(mode);
    int count = 0;
    for (int i = 0; i < size; i++) {
        string current = toLowerString(arr[i].transportMode);
        if (current > target) break;
        if (current == target) {
            cout << arr[i].residentID << "\n";
            count++;
        }
    }
    cout << "Total: " << count << endl;
}

void ResidentArray::searchTransportBinary(const string& mode) {
    sortByModeBubble();
    string target = toLowerString(mode);
    int left = 0, right = size - 1, startIdx = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        string midMode = toLowerString(arr[mid].transportMode);
        if (midMode >= target) { startIdx = mid; right = mid - 1; }
        else left = mid + 1;
    }
    int count = 0;
    if (startIdx != -1) {
        for (int i = startIdx; i < size && toLowerString(arr[i].transportMode) == target; i++) {
            cout << arr[i].residentID << "\n";
            count++;
        }
    }
    cout << "Total: " << count << endl;
}

void ResidentArray::searchDistance(float threshold) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i].dailyDistance > threshold) {
            cout << arr[i].residentID << "\n";
            count++;
        }
    }
    cout << "Total: " << count << endl;
}

void ResidentArray::searchDistanceEarlyExit(float threshold) {
    sortByDistanceMerge();
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i].dailyDistance > threshold) {
            cout << arr[i].residentID << " (" << arr[i].dailyDistance << "km)\n";
            count++;
        }
    }
    cout << "Total: " << count << endl;
}

void ResidentArray::searchDistanceBinary(float threshold) {
    sortByDistanceMerge();
    int left = 0, right = size - 1, startIdx = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].dailyDistance > threshold) { startIdx = mid; right = mid - 1; }
        else left = mid + 1;
    }
    int count = 0;
    if (startIdx != -1) {
        for (int i = startIdx; i < size; i++) {
            cout << arr[i].residentID << " (" << arr[i].dailyDistance << "km)\n";
            count++;
        }
    }
    cout << "Total: " << count << endl;
}


// Analytics & Performance
void ResidentArray::displayAnalytics() {
    double ageTotalEmission[5] = { 0 };
    int ageCount[5] = { 0 };
    string modes[] = { "Car", "Bus", "Bicycle", "Walking", "Carpool", "School Bus" };
    int modeCount[5][6] = { {0} };
    double ageModeEmission[5][6] = { {0.0} };
    double modeTotalEmission[6] = { 0 };
    double cityTotalEmission[3] = { 0 };

    for (int i = 0; i < size; i++) {
        int group = -1;
        if (arr[i].age >= 6 && arr[i].age <= 17) group = 0;
        else if (arr[i].age >= 18 && arr[i].age <= 25) group = 1;
        else if (arr[i].age >= 26 && arr[i].age <= 45) group = 2;
        else if (arr[i].age >= 46 && arr[i].age <= 60) group = 3;
        else if (arr[i].age >= 61 && arr[i].age <= 100) group = 4;

        if (group != -1) {
            ageTotalEmission[group] += arr[i].totalCarbon;
            ageCount[group]++;
            for (int j = 0; j < 6; j++) {
                if (arr[i].transportMode == modes[j]) {
                    modeCount[group][j]++;
                    ageModeEmission[group][j] += arr[i].totalCarbon;
                    modeTotalEmission[j] += arr[i].totalCarbon;
                    break;
                }
            }
        }
        if (!arr[i].residentID.empty()) {
            char city = arr[i].residentID[0];
            if (city == 'A') cityTotalEmission[0] += arr[i].totalCarbon;
            else if (city == 'B') cityTotalEmission[1] += arr[i].totalCarbon;
            else if (city == 'C') cityTotalEmission[2] += arr[i].totalCarbon;
        }
    }

    string groupNames[] = { "6-17", "18-25", "26-45", "46-60", "61-100" };
    cout << "\n=== Detailed Age Group Analysis ===\n";
    for (int i = 0; i < 5; i++) {
        cout << "\nAge Group: " << groupNames[i] << endl;
        cout << string(75, '-') << "\n";
        cout << left << setw(20) << "Mode" << setw(10) << "Count" << setw(22) << "Total Emission (kg)" << setw(20) << "Avg per Resident" << "\n";

        for (int m = 0; m < 6; m++) {
            if (modeCount[i][m] > 0) {
                double avgPerRes = ageModeEmission[i][m] / modeCount[i][m];
                cout << left << setw(20) << modes[m]
                    << setw(10) << modeCount[i][m]
                    << setw(22) << fixed << setprecision(2) << ageModeEmission[i][m]
                    << setw(20) << avgPerRes << endl;
            }
        }
        cout << "\nTotal Emission for Age Group: " << ageTotalEmission[i] << " kg CO2\n";
    }

    cout << "\n=== Emissions Per Dataset ===\n";
    cout << left << setw(30) << "City A (Metropolitan):" << cityTotalEmission[0] << " kg\n";
    cout << left << setw(30) << "City B (University):" << cityTotalEmission[1] << " kg\n";
    cout << left << setw(30) << "City C (Suburban):" << cityTotalEmission[2] << " kg\n";

    cout << "\n=== Total Emissions Per Transport Mode ===\n";
    for (int m = 0; m < 6; m++) {
        cout << left << setw(20) << modes[m] << ": " << modeTotalEmission[m] << " kg\n";
    }
}

void ResidentArray::displayMemoryUsage() {
    size_t totalBytes = sizeof(ArrayResident) * size;
    float kb = (float)totalBytes / 1024.0f;
    cout << "Memory Usage: " << fixed << setprecision(2) << kb << " KB (" << totalBytes << " bytes)" << endl;
}

void ResidentArray::runExperiment(string command, string target, int algo) {
    clock_t start = clock();
    string taskName = "";
    int searchResult = -1;

    if (command == "bubble_age") { taskName = "Bubble Sort (Age)"; sortByAgeBubble(); }
    else if (command == "merge_age") { taskName = "Merge Sort (Age)"; sortByAgeMerge(); }
    else if (command == "bubble_distance") { taskName = "Bubble Sort (Distance)"; sortByDistanceBubble(); }
    else if (command == "merge_distance") { taskName = "Merge Sort (Distance)"; sortByDistanceMerge(); }
    else if (command == "bubble_emission") { taskName = "Bubble Sort (Emission)"; sortByEmissionBubble(); }
    else if (command == "merge_emission") { taskName = "Merge Sort (Emission)"; sortByEmissionMerge(); }

    else if (command == "linear_id") { taskName = "Linear Search (ID)"; searchResult = linearSearch(target); }
    else if (command == "binary_id") { taskName = "Binary Search (ID)"; sortByID(); searchResult = binarySearch(target); }

    else if (command == "search_age") {
        taskName = (algo == 0) ? "Linear Search (Age Group)" : (algo == 1) ? "Early-Exit Search (Age Group)" : "Binary Search (Age Group)";
        int g = stoi(target);
        int minA = 0, maxA = 0;
        if (g == 0) { minA = 6; maxA = 17; }
        else if (g == 1) { minA = 18; maxA = 25; }
        else if (g == 2) { minA = 26; maxA = 45; }
        else if (g == 3) { minA = 46; maxA = 60; }
        else if (g == 4) { minA = 61; maxA = 100; }
        if (algo == 0) searchAgeRange(minA, maxA);
        else if (algo == 1) searchAgeEarlyExit(minA, maxA);
        else searchAgeBinary(minA, maxA);
    }
    else if (command == "search_transport") {
        taskName = (algo == 0) ? "Linear Search (Transport Mode)" : (algo == 1) ? "Early-Exit Search (Transport Mode)" : "Binary Search (Transport Mode)";
        if (algo == 0) searchTransport(target);
        else if (algo == 1) searchTransportEarlyExit(target);
        else searchTransportBinary(target);
    }
    else if (command == "search_distance") {
        taskName = (algo == 0) ? "Linear Search (Distance Threshold)" : (algo == 1) ? "Early-Exit Search (Distance Threshold)" : "Binary Search (Distance Threshold)";
        if (algo == 0) searchDistance(stof(target));
        else if (algo == 1) searchDistanceEarlyExit(stof(target));
        else searchDistanceBinary(stof(target));
    }

    double duration = (double)(clock() - start) / CLOCKS_PER_SEC;

    cout << "\n==========================================" << endl;
    cout << "EXPERIMENT : " << taskName << endl;
    if (command == "linear_id" || command == "binary_id") {
        if (searchResult != -1) cout << "STATUS     : Found at index " << searchResult << endl;
        else cout << "STATUS     : Not Found" << endl;
    }
    cout << "TIME SPENT : " << fixed << setprecision(8) << duration << "s" << endl;
    displayMemoryUsage();
    cout << "==========================================" << endl;
}