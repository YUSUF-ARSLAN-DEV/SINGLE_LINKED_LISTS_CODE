#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <cmath>

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
struct IndexNode  // this struct will be used to create al inked list of pointers that are pointings towards the original
                    // values that we read 
{
    Node* original_value ; 
    IndexNode* next ; // stores the address of the next node in chain 
}; 

class IndexLinkedList 
{
    public: 
    IndexNode* Head ; // This is the Head of the LinkedList 
    IndexLinkedList() 
    {
        Head = nullptr ; // This Initiates the IndexLinkedList 
    }
    void insert_node (IndexNode * n) 
    {
        n -> next = Head ; // This stores the value of the old head into the next attrbiute of the added node 
        this -> Head = n ; 
    }



};

class LinkedList 
{

    public :
    Node* Head ; 
    LinkedList () 
    {
        Head = nullptr ; // the moment the list is created the first Head is a null ptr 
    } 
    void insert_node (Node*  n )  // what is passed is the memory address of the last created node
    {
       n -> next = Head ; // this perserves the old value of the old  head 
       this -> Head = n ; 
       // in C++ this refrences the memory address of the object not the object it self 
        // take note that we are not taking the object it self but the pointer to it aka the address 
    }
};

// Struct to Access the avlues 

struct AgeCategories 
{
    IndexLinkedList* childrenTeenagers ; 
    IndexLinkedList* universityStudentsYoungAdults ; 
    IndexLinkedList* workingAdultsEarly ; 
    IndexLinkedList* workingAdultsLate ; 
    IndexLinkedList* seniorCitizens ; 
} ; 
// Age Categorization - Basically Createing Multiple Sublinked lists from the original linked lists 

AgeCategories ageCategorization (LinkedList* city )  
{
    IndexLinkedList* children = new IndexLinkedList() ; 
    IndexLinkedList* university = new IndexLinkedList() ; 
    IndexLinkedList* workingearly = new IndexLinkedList() ; 
    IndexLinkedList* workinglate = new IndexLinkedList() ; 
    IndexLinkedList* seniors = new IndexLinkedList() ; // Each list will contain Index Nodes  
    Node* current = city -> Head ;   // This is basically the Head  we will use it to iterate 
    // remember * indicates addresses 
    while (current != nullptr ) // this is how we iterate 
    {
        if ( (current -> Age  >= 6 ) &&  (current -> Age <= 17 ) ) // must be greater than or equal to 6 and less than 
        {
                IndexNode* n = new IndexNode( );
                 // current is an address it self 
                n -> original_value  = current ;  // the value needed
                children -> insert_node(n) ;    
        }
        else if ( (current -> Age  >= 18 ) &&  (current -> Age <= 25 ) ) // must be greater than or equal to 6 and less than 
        {
                IndexNode* n = new IndexNode( );
                 // current is an address it self 
                n -> original_value  = current ;  // the value needed
                university  -> insert_node(n) ;    
        }
        else if ( (current -> Age  >= 26 ) &&  (current -> Age <= 45 ) ) // must be greater than or equal to 6 and less than 
        {
                IndexNode* n = new IndexNode( );
                 // current is an address it self 
                n -> original_value  = current ;  // the value needed
                workingearly -> insert_node(n) ;    
        }
        else if ( (current -> Age  >= 46 ) &&  (current -> Age <= 60 ) ) // must be greater than or equal to 6 and less than 
        {
                IndexNode* n = new IndexNode( );
                 // current is an address it self 
                n -> original_value  = current ;  // the value needed
                workinglate -> insert_node(n) ;    
        }
        else if ( (current -> Age  >= 61 ) &&  (current -> Age <= 100 ) ) // must be greater than or equal to 6 and less than 
        {
                IndexNode* n = new IndexNode( );
                 // current is an address it self 
                n -> original_value  = current ;  // the value needed
                seniors -> insert_node(n) ;    
        }

        // moving to the next value 
        current = current -> next ; // as the address of the next value is stored in this value  
    }
     
    AgeCategories thecity =  AgeCategories() ;
    thecity.childrenTeenagers  = children ; 
    thecity.universityStudentsYoungAdults = university ; 
    thecity.workingAdultsEarly = workingearly ; 
    thecity.workingAdultsLate = workinglate ; 
    thecity.seniorCitizens = seniors ; 
    return thecity ; 

}
// But these SubLinked lists would essence only store memory addresses 

// helper method to transform string into enum

ModeofTransport stringToTransport (string value ) 
{
    if (value == "Car")        return ModeofTransport :: Car ; 
    if (value == "Bus")        return ModeofTransport:: Bus ; 
    if (value == "Bicycle")    return ModeofTransport :: Bicycle ;
    if (value == "Walking")    return ModeofTransport :: Walking ;
    if (value == "Carpool")    return ModeofTransport :: Carpool ; 
    if (value == "School Bus")    return ModeofTransport :: SchoolBus ;
    return ModeofTransport :: Walking ; // as the default return statement 
}
int count_residents_a  = 0 ; 
int count_residents_b = 0 ; 
int count_residents_c = 0 ;  

LinkedList*  implement_dataset (string file_name ) 
{
    // reading the csv file 
    // expected column order when reading the data 
    // ResidentID , Age , ModeofTransport , DailyDistance , CarbonEmissionFactor , AverageDayPerMonth
    ifstream file(file_name) ;
    string line ; 
    LinkedList* city = new LinkedList() ;  // this creates a pointer in the stack that refrences a memory address on the heap 
    getline(file,line ) ;
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
             
           else if (index ==1 ) {age = stoi(token); }
            
           else  if (index == 2 ) {transport = stringToTransport(token);}
             
            else if (index == 3 ) {dailydistance = stod(token);}
             
            else if (index == 4) {carbonEmissionFactor = stod(token) ;}
            
            else if (index == 5 ) {averageDayPerMonth = stoi(token) ;}
            index ++ ; 
        }
        // we are done parsing the line now createn a token for each line parsen 
        // creating a variable that stores the address to a location in the heap 
        Node* n = new Node() ;  
        n -> ResidentId  = residentId ; 
        n -> Age = age ; 
        n -> transport = transport ; 
        n-> DailyDistance =  dailydistance ; 
        n -> CarbonEmissionFactor =  carbonEmissionFactor ; 
        n -> AverageDayPerMonth =  averageDayPerMonth ; 
        // this basiaclly populates the attributes of the node n  ( take note n is an address)
        n -> next = nullptr ; 
        city -> insert_node(n) ;// now we have inserted the node 
        if (file_name == "citya.csv") count_residents_a ++ ; 
        else if (file_name == "cityb.csv") count_residents_b ++ ; 
        else if (file_name == "cityc.csv") count_residents_c ++ ;   
    }
    return city ; 

}
double calculate_total_emissions(LinkedList* c) 
{
    // formula for total emissions CarbonEmission rate / km * Daily distance (no of Km moved )  * No of days 
    double total = 0 ; 
    Node* current =  c -> Head ; 
    while (current != nullptr ) 
    {
        total +=( (current -> CarbonEmissionFactor) * (current -> DailyDistance ) * (current -> AverageDayPerMonth) ); 
        current = current -> next ; // here we are basically traversing into the next node 
    }
    return total ; 
}

void ageGroupQuantifier(IndexLinkedList* city, int& total_car, int& total_bicycle, int& total_bus, int& total_walking, int& total_carpool, int& total_schoolbus, int& res_count, double& total_emissions)
{
    IndexNode* current = city->Head;
    while (current != nullptr)
    {
        if (current->original_value->transport == ModeofTransport::Car) total_car++;
        else if (current->original_value->transport == ModeofTransport::Bicycle) total_bicycle++;
        else if (current->original_value->transport == ModeofTransport::Bus) total_bus++;
        else if (current->original_value->transport == ModeofTransport::Walking) total_walking++;
        else if (current->original_value->transport == ModeofTransport::Carpool) total_carpool++;
        else if (current->original_value->transport == ModeofTransport::SchoolBus) total_schoolbus++;
        total_emissions += current->original_value->CarbonEmissionFactor * current->original_value->DailyDistance * current->original_value->AverageDayPerMonth;
        res_count++;
        current = current->next;
    }
}

void dominantTransport(IndexLinkedList* citya, IndexLinkedList* cityb, IndexLinkedList* cityc, string group)
{
    int total_car = 0, total_bicycle = 0, total_bus = 0, total_walking = 0, total_carpool = 0, total_schoolbus = 0;
    int res_count = 0;
    double total_emissions = 0;

    ageGroupQuantifier(citya, total_car, total_bicycle, total_bus, total_walking, total_carpool, total_schoolbus, res_count, total_emissions);
    ageGroupQuantifier(cityb, total_car, total_bicycle, total_bus, total_walking, total_carpool, total_schoolbus, res_count, total_emissions);
    ageGroupQuantifier(cityc, total_car, total_bicycle, total_bus, total_walking, total_carpool, total_schoolbus, res_count, total_emissions);

    int highest = total_car; string highest_label = "Car";
    if (total_bicycle > highest) { highest = total_bicycle; highest_label = "Bicycle"; }
    if (total_bus > highest) { highest = total_bus; highest_label = "Bus"; }
    if (total_walking > highest) { highest = total_walking; highest_label = "Walking"; }
    if (total_carpool > highest) { highest = total_carpool; highest_label = "Carpool"; }
    if (total_schoolbus > highest) { highest = total_schoolbus; highest_label = "SchoolBus"; }

    cout << "Age Group: " << group << endl;
    cout << "Most common transport: " << highest_label << " with count: " << highest << endl;
    cout << "Total emissions: " << total_emissions << " Kg CO2" << endl;
    cout << "Average Carbon Emissions per resident in the Age Group of: " << group<<" " << total_emissions / res_count <<endl  ; 
}
// ── Question 5 helpers ───────────────────────────────────────────────────────

string getTransportLabel(ModeofTransport t)
{
    if (t == ModeofTransport::Car)       return "Car";
    if (t == ModeofTransport::Bus)       return "Bus";
    if (t == ModeofTransport::Bicycle)   return "Bicycle";
    if (t == ModeofTransport::Walking)   return "Walking";
    if (t == ModeofTransport::Carpool)   return "Carpool";
    if (t == ModeofTransport::SchoolBus) return "School Bus";
    return "Unknown";
}

// Q5b + Q5d : takes a sub-linked list (IndexLinkedList) as argument,
//             iterates with if statements, prints a text-based table
void printEmissionTable(IndexLinkedList* ageGroup, string groupLabel, string datasetLabel)
{
    int    countCar = 0, countBus = 0, countBicycle = 0, countWalking = 0, countCarpool = 0, countSchoolBus = 0;
    double emCar    = 0, emBus    = 0, emBicycle    = 0, emWalking    = 0, emCarpool    = 0, emSchoolBus    = 0;
    double groupTotal = 0;

    IndexNode* current = ageGroup->Head;
    while (current != nullptr)
    {
        Node* r = current->original_value;
        double emission = r->CarbonEmissionFactor * r->DailyDistance * r->AverageDayPerMonth;
        if      (r->transport == ModeofTransport::Car)       { countCar++;       emCar       += emission; }
        else if (r->transport == ModeofTransport::Bus)       { countBus++;       emBus       += emission; }
        else if (r->transport == ModeofTransport::Bicycle)   { countBicycle++;   emBicycle   += emission; }
        else if (r->transport == ModeofTransport::Walking)   { countWalking++;   emWalking   += emission; }
        else if (r->transport == ModeofTransport::Carpool)   { countCarpool++;   emCarpool   += emission; }
        else if (r->transport == ModeofTransport::SchoolBus) { countSchoolBus++; emSchoolBus += emission; }
        groupTotal += emission;
        current = current->next;
    }

    cout << "Age Group: " << groupLabel << " [" << datasetLabel << "]\n";
    cout << "---------------------------------------\n";
    cout << left
         << setw(20) << "Mode of Transport"
         << setw(10) << "Count"
         << setw(28) << "Total Emission (kg CO2)"
         << "Average per Resident\n";

    string labels[6] = { "Car", "Bus", "Bicycle", "Walking", "Carpool", "School Bus" };
    int    counts[6] = { countCar, countBus, countBicycle, countWalking, countCarpool, countSchoolBus };
    double emits[6]  = { emCar,    emBus,    emBicycle,    emWalking,    emCarpool,    emSchoolBus    };

    for (int i = 0; i < 6; i++)
    {
        if (counts[i] > 0)
        {
            double avg = emits[i] / counts[i];
            cout << left
                 << setw(20) << labels[i]
                 << setw(10) << counts[i]
                 << setw(28) << emits[i]
                 << avg << "\n";
        }
    }
    cout << "---------------------------------------\n";
    cout << "Total Emission for Age Group: " << groupTotal << " kg CO2\n\n";
}

// Q5c : compare the same age group across all three datasets
void compareAcrossDatasets(IndexLinkedList* a, IndexLinkedList* b, IndexLinkedList* c, string groupLabel)
{
    cout << "===== Comparing Datasets | Age Group: " << groupLabel << " =====\n\n";
    printEmissionTable(a, groupLabel, "City A");
    printEmissionTable(b, groupLabel, "City B");
    printEmissionTable(c, groupLabel, "City C");
}

// ── Question 6 helpers ───────────────────────────────────────────────────────

enum class SortKey { Age, DailyDistance, CarbonEmission };

string getSortKeyLabel(SortKey key)
{
    if (key == SortKey::Age)           return "Age";
    if (key == SortKey::DailyDistance) return "Daily Distance";
    return "Carbon Emission";
}

double getSortValue(Node* n, SortKey key)
{
    if (key == SortKey::Age)           return (double)n->Age;
    if (key == SortKey::DailyDistance) return n->DailyDistance;
    return n->CarbonEmissionFactor * n->DailyDistance * n->AverageDayPerMonth;
}

int countNodes(LinkedList* list)
{
    int count = 0;
    Node* cur = list->Head;
    while (cur != nullptr) { count++; cur = cur->next; }
    return count;
}

// Bubble sort on linked list — swaps node data, not pointers
void bubbleSortLinkedList(LinkedList* list, SortKey key)
{
    if (list->Head == nullptr) return;
    bool swapped = true;
    while (swapped)
    {
        swapped = false;
        Node* cur = list->Head;
        while (cur->next != nullptr)
        {
            if (getSortValue(cur, key) > getSortValue(cur->next, key))
            {
                Node* nx = cur->next;
                string          tmpId  = cur->ResidentId;           cur->ResidentId           = nx->ResidentId;           nx->ResidentId           = tmpId;
                int             tmpAge = cur->Age;                  cur->Age                  = nx->Age;                  nx->Age                  = tmpAge;
                ModeofTransport tmpT   = cur->transport;            cur->transport            = nx->transport;            nx->transport            = tmpT;
                double          tmpDd  = cur->DailyDistance;        cur->DailyDistance        = nx->DailyDistance;        nx->DailyDistance        = tmpDd;
                double          tmpCef = cur->CarbonEmissionFactor; cur->CarbonEmissionFactor = nx->CarbonEmissionFactor; nx->CarbonEmissionFactor = tmpCef;
                int             tmpDpm = cur->AverageDayPerMonth;   cur->AverageDayPerMonth   = nx->AverageDayPerMonth;   nx->AverageDayPerMonth   = tmpDpm;
                swapped = true;
            }
            cur = cur->next;
        }
    }
}

// Bubble sort on a plain Node array (next pointer field is unused)
void bubbleSortArray(Node* arr, int n, SortKey key)
{
    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (getSortValue(&arr[j], key) > getSortValue(&arr[j + 1], key))
            {
                Node tmp   = arr[j];
                arr[j]     = arr[j + 1];
                arr[j + 1] = tmp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Print first maxRows entries of a sorted linked list
void printSortedResults(LinkedList* list, string datasetLabel, string sortKeyLabel, int maxRows)
{
    cout << "Sorted Results [" << datasetLabel << "] by " << sortKeyLabel
         << " (top " << maxRows << "):\n";
    cout << left
         << setw(6)  << "Rank"
         << setw(14) << "ResidentID"
         << setw(6)  << "Age"
         << setw(14) << "Transport"
         << setw(14) << "Daily Dist"
         << "Carbon Emission\n";
    cout << string(68, '-') << "\n";

    Node* cur = list->Head;
    int rank = 1;
    while (cur != nullptr && rank <= maxRows)
    {
        double emission = cur->CarbonEmissionFactor * cur->DailyDistance * cur->AverageDayPerMonth;
        cout << left
             << setw(6)  << rank
             << setw(14) << cur->ResidentId
             << setw(6)  << cur->Age
             << setw(14) << getTransportLabel(cur->transport)
             << setw(14) << cur->DailyDistance
             << emission << "\n";
        cur  = cur->next;
        rank++;
    }
    cout << "\n";
}

// Run sorting experiment: copy to array, sort both, time both, display comparison table
void sortingExperiment(LinkedList* list, string datasetLabel, SortKey key)
{
    using namespace chrono;
    int    n        = countNodes(list);
    string keyLabel = getSortKeyLabel(key);

    // Copy linked list into a plain array (captures same initial order)
    Node* arr = new Node[n];
    Node* cur = list->Head;
    for (int i = 0; i < n; i++) { arr[i] = *cur; cur = cur->next; }

    // Time array bubble sort
    auto t1 = high_resolution_clock::now();
    bubbleSortArray(arr, n, key);
    auto t2 = high_resolution_clock::now();
    double arrTime = duration<double, milli>(t2 - t1).count();

    // Time linked list bubble sort (list still in original order)
    t1 = high_resolution_clock::now();
    bubbleSortLinkedList(list, key);
    t2 = high_resolution_clock::now();
    double llTime = duration<double, milli>(t2 - t1).count();

    // Memory
    long long llMem  = (long long)n * sizeof(Node);                       // node data + embedded next ptr
    long long arrMem = (long long)n * (sizeof(Node) - sizeof(Node*));     // data only, no next ptr needed

    // Display sorted results (top 10 from linked list)
    printSortedResults(list, datasetLabel, keyLabel, 10);

    // Display comparison table
    cout << "===== Bubble Sort Comparison: by " << keyLabel << " [" << datasetLabel << "] =====\n";
    cout << left
         << setw(22) << "Structure"
         << setw(12) << "Elements"
         << setw(14) << "Time (ms)"
         << setw(22) << "Memory (bytes)"
         << setw(16) << "Time Complexity"
         << "Space Complexity\n";
    cout << string(88, '-') << "\n";
    cout << left
         << setw(22) << "Singly Linked List"
         << setw(12) << n
         << setw(14) << llTime
         << setw(22) << llMem
         << setw(16) << "O(n^2)"
         << "O(1) extra\n";
    cout << left
         << setw(22) << "Array"
         << setw(12) << n
         << setw(14) << arrTime
         << setw(22) << arrMem
         << setw(16) << "O(n^2)"
         << "O(n) for copy\n";
    cout << string(88, '-') << "\n";
    cout << "Note: LL node = " << sizeof(Node) << " bytes (data + "
         << sizeof(Node*) << "-byte next ptr). Array element = "
         << sizeof(Node) - sizeof(Node*) << " bytes (no next ptr).\n\n";

    delete[] arr;
}

IndexLinkedList* linear_search (LinkedList* list, int targetAge)
{
    IndexLinkedList* results = new IndexLinkedList();
    Node* current = list->Head;
    while (current != nullptr)
    {
        if (current->Age == targetAge)
        {
            IndexNode* n = new IndexNode();
            n->original_value = current;
            results->insert_node(n);
        }
        current = current->next;
    }
    return results;
}

IndexLinkedList* linear_search (LinkedList * list , ModeofTransport targetTransport )
{
    Node* current = list -> Head ; 
    IndexLinkedList * result = new IndexLinkedList() ; 
    while (current != nullptr ){
        if (current -> transport == targetTransport ) 
        {
            IndexNode * n = new IndexNode() ; 
            n->original_value = current ; // now we are saving the value of original into the refrence node basically storing a pointer to the original node so that search is logical no recopying 
            result -> insert_node(n) ; 

        }
    }
    return result ; 
}

IndexLinkedList* linear_search (LinkedList* list, double targetEmission)
{
    IndexLinkedList* results = new IndexLinkedList();
    Node* current = list->Head;
    while (current != nullptr)
    {
        double emission = current->CarbonEmissionFactor * current->DailyDistance * current->AverageDayPerMonth;
        if (abs(emission - targetEmission) < 1e-6) // using a small epsilon for floating-point comparison
        {
            IndexNode* n = new IndexNode();
            n->original_value = current;
            results->insert_node(n);
        }
        current = current->next;
    }
    return results;
}   

// ─────────────────────────────────────────────────────────────────────────────

int main ()
{
    /* Working on Question 4 */ 
    // age categorization  + Total Carbon Emissions + Average Carbon Emissions per resident . 
    LinkedList* citya = implement_dataset("citya.csv");
    LinkedList* cityb = implement_dataset("cityb.csv");
    LinkedList* cityc = implement_dataset("cityc.csv");
    AgeCategories cityACategories = ageCategorization(citya) ;  // Each object has 5 IndexLists - aka a logic filtering done for the categories 
    AgeCategories cityBCategories = ageCategorization(cityb);
    AgeCategories cityCCategories = ageCategorization(cityc) ;

    /*
    dominantTransport(cityACategories.childrenTeenagers , cityBCategories.childrenTeenagers,cityCCategories.childrenTeenagers,"Children and Teenagers") ;
    dominantTransport(cityACategories.universityStudentsYoungAdults, cityBCategories.universityStudentsYoungAdults, cityCCategories.universityStudentsYoungAdults, "University Students and Young Adults");
    dominantTransport(cityACategories.workingAdultsEarly, cityBCategories.workingAdultsEarly, cityCCategories.workingAdultsEarly, "Working Adults Early");
    dominantTransport(cityACategories.workingAdultsLate, cityBCategories.workingAdultsLate, cityCCategories.workingAdultsLate, "Working Adults Late");
    dominantTransport(cityACategories.seniorCitizens, cityBCategories.seniorCitizens, cityCCategories.seniorCitizens, "Senior Citizens");
    */

    /* Question 5 */

    // 5a - Total carbon emissions per dataset
     /*
    cout << "Total Carbon Emissions for City A: " << calculate_total_emissions(citya) << " kg CO2\n";
    cout << "Total Carbon Emissions for City B: " << calculate_total_emissions(cityb) << " kg CO2\n";
    cout << "Total Carbon Emissions for City C: " << calculate_total_emissions(cityc) << " kg CO2\n";
    */

    // 5b, 5c, 5d - Emissions per mode of transport, compared across datasets and age groups

    compareAcrossDatasets(cityACategories.childrenTeenagers,            cityBCategories.childrenTeenagers,            cityCCategories.childrenTeenagers,            "6-17 (Children & Teenagers)");
    compareAcrossDatasets(cityACategories.universityStudentsYoungAdults, cityBCategories.universityStudentsYoungAdults, cityCCategories.universityStudentsYoungAdults, "18-25 (University Students)");
    compareAcrossDatasets(cityACategories.workingAdultsEarly,           cityBCategories.workingAdultsEarly,           cityCCategories.workingAdultsEarly,           "26-45 (Working Adults Early)");
    compareAcrossDatasets(cityACategories.workingAdultsLate,            cityBCategories.workingAdultsLate,            cityCCategories.workingAdultsLate,            "46-60 (Working Adults Late)");
    compareAcrossDatasets(cityACategories.seniorCitizens,               cityBCategories.seniorCitizens,               cityCCategories.seniorCitizens,               "61-100 (Senior Citizens)");

    /* Question 6 */
    sortingExperiment(citya, "City A", SortKey::Age);
    sortingExperiment(cityb, "City B", SortKey::DailyDistance);
    sortingExperiment(cityc, "City C", SortKey::CarbonEmission);
    Node* current = citya -> Head ; 

    while (current != nullptr ) 
    {
        cout << current ->  Age <<endl ; 
        current = current -> next ; // I wanna see if ages are actually sorted 

    }
    
   // Question 7 Implementing search algorithm 

   // In essence this is an attempt to apply Jump search on the sorted List of city A - which 
   // is sorted by Age : 




    
    
    
    
    
    


  


    
     
}