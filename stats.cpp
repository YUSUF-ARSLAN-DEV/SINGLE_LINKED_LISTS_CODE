#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>


enum  class ModeofTransport 
{
    Car , 
    Bus ,
    Bicycle ,
    Walking ,
    Carpool , 
    SchoolBus 
};

ModeofTransport stringToModeOfTransport(const std::string& str) {
    if (str == "Car") return ModeofTransport::Car;
    if (str == "Bus") return ModeofTransport::Bus;
    if (str == "Bicycle") return ModeofTransport::Bicycle;
    if (str == "Walking") return ModeofTransport::Walking;
    if (str == "Carpool") return ModeofTransport::Carpool;
    if (str == "School Bus") return ModeofTransport::SchoolBus;
    return ModeofTransport::Walking; // default fallback
}

int getAgeGroup(int age) {
    if (age >= 6 && age <= 17) return 0;
    if (age >= 18 && age <= 25) return 1;
    if (age >= 26 && age <= 45) return 2;
    if (age >= 46 && age <= 60) return 3;
    if (age >= 61 && age <= 100) return 4;
    return -1;
}

int modeIndex(ModeofTransport mode) {
    switch (mode) {
        case ModeofTransport::Car: return 0;
        case ModeofTransport::Bus: return 1;
        case ModeofTransport::Bicycle: return 2;
        case ModeofTransport::Walking: return 3;
        case ModeofTransport::Carpool: return 4;
        case ModeofTransport::SchoolBus: return 5;
    }
    return 0;
}

const char* modeLabel(int index) {
    switch (index) {
        case 0: return "Car";
        case 1: return "Bus";
        case 2: return "Bicycle";
        case 3: return "Walking";
        case 4: return "Carpool";
        case 5: return "SchoolBus";
        default: return "Unknown";
    }
}

const char* ageGroupLabel(int group) {
    switch (group) {
        case 0: return "6-17";
        case 1: return "18-25";
        case 2: return "26-45";
        case 3: return "46-60";
        case 4: return "61+";
        default: return "Unknown";
    }
}

int cityIndex(const std::string& city) {
    if (city == "A") return 0;
    if (city == "B") return 1;
    if (city == "C") return 2;
    return -1;
}

const char* cityLabel(int index) {
    switch (index) {
        case 0: return "City A";
        case 1: return "City B";
        case 2: return "City C";
        default: return "Unknown";
    }
}

struct DataNode {
    std::string ResidentID;
    int Age;
    ModeofTransport modeoftransport;
    double DailyDistance;
    double CarbonEmissionFactor;
    int AverageDayPerMonth;

    DataNode* next;
};

class DataLinkedList {
public:
    DataNode* Head;

    DataLinkedList() {
        Head = nullptr;
    }

    void insertNode(DataNode* newNode) {
        newNode->next = Head;
        Head = newNode;
    }

    void importFromCSV(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }
        std::string line;
        std::getline(file, line); // Skip header
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string token;
            DataNode* newNode = new DataNode();
            std::getline(ss, newNode->ResidentID, ',');
            std::getline(ss, token, ',');
            newNode->Age = std::stoi(token);
            std::getline(ss, token, ',');
            newNode->modeoftransport = stringToModeOfTransport(token);
            std::getline(ss, token, ',');
            newNode->DailyDistance = std::stod(token);
            std::getline(ss, token, ',');
            newNode->CarbonEmissionFactor = std::stod(token);
            std::getline(ss, token, ',');
            newNode->AverageDayPerMonth = std::stoi(token);
            insertNode(newNode);
        }
    }
};

struct AgeNode {
    std::string City;
    int Age;
    ModeofTransport modeoftransport;
    double carbonEmissions;

    AgeNode* next;
};

class AgeLinkedList {
public:
    AgeNode* Head;

    AgeLinkedList() {
        Head = nullptr;
    }

    void insertNode(AgeNode* newNode) {
        newNode->next = Head;
        Head = newNode;
    }
};

int main() {
    DataLinkedList cityA;
    cityA.importFromCSV("citya.csv");
    
    DataLinkedList cityB;
    cityB.importFromCSV("cityb.csv");

    DataLinkedList cityC;
    cityC.importFromCSV("cityc.csv");

    //Compare carbon emissions and mode preferences across datasets and age groups using text-based tables.

    AgeLinkedList Groups;

    for (DataNode* nodeA = cityA.Head; nodeA != nullptr; nodeA = nodeA->next) {
        Groups.insertNode(new AgeNode{ "A", nodeA->Age, nodeA->modeoftransport, nodeA->DailyDistance * nodeA->CarbonEmissionFactor * nodeA->AverageDayPerMonth });
    }
    for (DataNode* nodeB = cityB.Head; nodeB != nullptr; nodeB = nodeB->next) {
        Groups.insertNode(new AgeNode{ "B", nodeB->Age, nodeB->modeoftransport, nodeB->DailyDistance * nodeB->CarbonEmissionFactor * nodeB->AverageDayPerMonth });
    }
    for (DataNode* nodeC = cityC.Head; nodeC != nullptr; nodeC = nodeC->next) {
        Groups.insertNode(new AgeNode{ "C", nodeC->Age, nodeC->modeoftransport, nodeC->DailyDistance * nodeC->CarbonEmissionFactor * nodeC->AverageDayPerMonth });
    }

    // get the average carbon emissions for each city, age group, and mode of transport
    const int cities = 3;
    const int ageGroups = 5;
    const int transportTypes = 6;
    double totalEmissions[cities][ageGroups][transportTypes] = {};
    int counts[cities][ageGroups][transportTypes] = {};

    for (AgeNode* node = Groups.Head; node != nullptr; node = node->next) {
        int city = cityIndex(node->City);
        if (city < 0) continue;
        int group = getAgeGroup(node->Age);
        if (group < 0) continue;
        int transport = modeIndex(node->modeoftransport);
        totalEmissions[city][group][transport] += node->carbonEmissions;
        counts[city][group][transport]++;
    }

    const int cityWidth = 10;
    const int ageWidth = 10;
    const int transportWidth = 15;
    const int avgWidth = 20;
    const int countWidth = 8;

    struct Row {
        int city;
        int ageGroup;
        int transport;
        double avgEmissions;
        int count;
    };

    Row rows[90];
    int rowCount = 0;
    for (int city = 0; city < cities; ++city) {
        for (int group = 0; group < ageGroups; ++group) {
            for (int transport = 0; transport < transportTypes; ++transport) {
                if (counts[city][group][transport] == 0) continue;
                rows[rowCount++] = {city, group, transport,
                                    totalEmissions[city][group][transport] / counts[city][group][transport],
                                    counts[city][group][transport]};
            }
        }
    }

    auto printFullSeparator = [&]() {
        std::cout << "+" << std::string(cityWidth, '-')
                  << "+" << std::string(ageWidth, '-')
                  << "+" << std::string(transportWidth, '-')
                  << "+" << std::string(avgWidth, '-')
                  << "+" << std::string(countWidth, '-')
                  << "+" << std::endl;
    };

    auto printPartialSeparator = [&]() {
        std::cout << "+" << std::string(cityWidth, ' ')
                  << "+" << std::string(ageWidth, '-')
                  << "+" << std::string(transportWidth, '-')
                  << "+" << std::string(avgWidth, '-')
                  << "+" << std::string(countWidth, '-')
                  << "+" << std::endl;
    };

    printFullSeparator();
    std::cout << "| " << std::left << std::setw(cityWidth - 1) << "City"
              << "| " << std::left << std::setw(ageWidth - 1) << "Age"
              << "| " << std::left << std::setw(transportWidth - 1) << "Transport"
              << "| " << std::left << std::setw(avgWidth - 1) << "Avg Emissions"
              << "| " << std::left << std::setw(countWidth - 1) << "Count"
              << "|" << std::endl;
    printFullSeparator();

    for (int i = 0; i < rowCount; ++i) {
        const Row& row = rows[i];
        const bool isFirstCityRow = (i == 0) || (rows[i - 1].city != row.city);
        bool sameCityNext = false;
        if (i + 1 < rowCount) {
            sameCityNext = (rows[i + 1].city == row.city);
        }

        std::cout << "| " << std::left << std::setw(cityWidth - 1) << (isFirstCityRow ? cityLabel(row.city) : "")
                  << "| " << std::left << std::setw(ageWidth - 1) << ageGroupLabel(row.ageGroup)
                  << "| " << std::left << std::setw(transportWidth - 1) << modeLabel(row.transport)
                  << "| " << std::right << std::setw(avgWidth - 2) << std::fixed << std::setprecision(2) << row.avgEmissions << " "
                  << "| " << std::right << std::setw(countWidth - 2) << row.count << " "
                  << "|" << std::endl;

        if (sameCityNext) {
            printPartialSeparator();
        } else {
            printFullSeparator();
        }
    }

    return 0;
}