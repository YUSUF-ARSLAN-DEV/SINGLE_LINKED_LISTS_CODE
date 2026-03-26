#include <iostream> 
#include <string> 
#include <fstream> 
#include <sstream> 

using namespace std ; 
enum  class ModeofTransport 
{
    Car , 
    Bus ,
    Bicycle ,
    Walking ,
    Carpool , 
    SchoolBus 
};
struct Node 
{
    string ResidentId  ;
    int Age ; 
    ModeofTransport transport ; 
    double  DailyDistance ; 
    double CarbonEmissionFactor  ;  // The unit is Kg CO ? / Km per kelimoter 
    int  AverageDayPerMonth ; // refers to the reported number of days in which the person reported using that mode of transport 


    Node* next ; // next is the address of the next node 
};

class LinkedList 
{
    public :
    Node* Head ; 
};

// helper method to transform string into enump 

ModeofTransport stringToTransport (string value ) 
{
    if (value == "Car")        return ModeofTransport :: Car ; 
    if (value == "Bus")        return ModeofTransport:: Bus ; 
    if (value == "Bicycle")    return ModeofTransport :: Bicycle ;
    if (value == "Walking")    return ModeofTransport :: Walking ;
    if (value == "Carpool")    return ModeofTransport :: Carpool ; 
    if (value == "School Bus")    return ModeofTransport :: SchoolBus ;
}

int main () 
{
    // reading the csv file 
    // expected column order when reading the data 
    // ResidentID , Age , ModeofTransport , DailyDistance , CarbonEmissionFactor , AverageDayPerMonth
    ifstream file("citya.csv") ;
    string line ; 
    
    while (getline(file,line)) 
    {
        int index = 0 ;  // reset  the column index for each line 
        // declaring variables for tokenization 
        string residentId ; 
        int age ; 
        ModeofTransport transport ; 
        double dailydistance ; 
        double carbonEmissionFactor ; 
        int averageDayPerMonth ; 
        
        stringstream ss(line) ; // we are parsing the line as a string stream 
            // this so that we can perform the tokenization process 
        string token ; 
        while (getline(ss,token,',') ) // this continue to read the line until no more delimeters
        {
            if (index == 0 ) {residentId = token ; }
            index ++ ; 
            if (index ==1 ) {age = stoi(token); }
            index ++ ; 
            if (index == 2 ) {transport = stringToTransport(token);}
            index ++ ; 
            if (index == 3 ) {dailydistance = stod(token);}
            index ++ ; 
            if (index == 4) {carbonEmissionFactor = stod(token) ;}
            index ++ ;
            if (index == 5 ) {averageDayPerMonth = stoi(token) ;}
        }
        // we are done parsing the line now createn a token for each line parsen 
        // test
    }
     
}