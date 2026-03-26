#include <iostream> 
#include <string> 
using namespace std ; 
enum  class ModeofTransport 
{
    Car , 
    Bus ,
    Bicycle ,
    Walking
};
struct Node 
{
    string ResidentId  ;
    int Age ; 
    ModeofTransport transport ; 
    int DailyDistance ; 
    double CarbonEmissionFactor  ;  // The unit is Kg CO ? / Km per kelimoter 
    int  AverageDayPerMonth ; // refers to the reported number of days in which the person reported using that mode of transport 


    Node* next ; // next is the address of the next node 
};

int getAgeGroup(int age)
{
    if (age >= 6  && age <= 17)  return 0 ;
    if (age >= 18 && age <= 25)  return 1 ;
    if (age >= 26 && age <= 45)  return 2 ;
    if (age >= 46 && age <= 60)  return 3 ;
    if (age >= 61 && age <= 100) return 4 ;
    return -1 ;
}

string getAgeGroupLabel(int group)
{
    switch (group)
    {
        case 0 : return "6-17   : Children & Teenagers" ;
        case 1 : return "18-25  : University Students / Young Adults" ;
        case 2 : return "26-45  : Working Adults (Early Career)" ;
        case 3 : return "46-60  : Working Adults (Late Career)" ;
        case 4 : return "61-100 : Senior Citizens / Retirees" ;
        default: return "Unknown" ;
    }
}

string getTransportLabel(int t)
{
    switch (t)
    {
        case 0 : return "Car" ;
        case 1 : return "Bus" ;
        case 2 : return "Bicycle" ;
        case 3 : return "Walking" ;
        default: return "Unknown" ;
    }
}

class LinkedList
{
    public :
    Node* Head ;

    void analyzeAgeGroups()
    {
        int    transportCount[5][4] = {} ; // [group][transport]
        double totalEmissions[5]    = {} ;
        int    residentCount[5]     = {} ;

        Node* current = Head ;
        while (current != nullptr)
        {
            int group = getAgeGroup(current->Age) ;
            if (group != -1)
            {
                transportCount[group][(int)current->transport]++ ;
                totalEmissions[group] += current->DailyDistance * current->CarbonEmissionFactor * current->AverageDayPerMonth ;
                residentCount[group]++ ;
            }
            current = current->next ;
        }

        cout << "\n========== Age Group Analysis ==========\n" ;
        for (int g = 0 ; g < 5 ; g++)
        {
            cout << "\nAge Group: " << getAgeGroupLabel(g) << "\n" ;

            if (residentCount[g] == 0)
            {
                cout << "  No residents in this group.\n" ;
                continue ;
            }

            int maxCount = 0, preferredTransport = 0 ;
            for (int t = 0 ; t < 4 ; t++)
            {
                if (transportCount[g][t] > maxCount)
                {
                    maxCount = transportCount[g][t] ;
                    preferredTransport = t ;
                }
            }

            cout << "  Most Preferred Transport     : " << getTransportLabel(preferredTransport) << " (" << maxCount << " residents)\n" ;
            cout << "  Total Carbon Emissions       : " << totalEmissions[g] << " Kg CO2\n" ;
            cout << "  Avg Carbon Emission/Resident : " << totalEmissions[g] / residentCount[g] << " Kg CO2\n" ;
        }
        cout << "\n=========================================\n" ;
    }
};

int main () 
{
    
     
}