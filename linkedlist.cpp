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
    cout << "Total residents: " << res_count << endl;
}
int main () 
{
    /* Working on Question 4 */ 
    // age categorization 
    /*
    LinkedList* citya = implement_dataset("citya.csv");
    LinkedList* cityb = implement_dataset("cityb.csv");
    LinkedList* cityc = implement_dataset("cityc.csv");
    AgeCategories cityACategories = ageCategorization(citya) ;  // Each object has 5 IndexLists - aka a logic filtering done for the categories 
    AgeCategories cityBCategories = ageCategorization(cityb);
    AgeCategories cityCCategories = ageCategorization(cityc) ;
    dominantTransport(cityACategories.childrenTeenagers , cityBCategories.childrenTeenagers,cityCCategories.childrenTeenagers,"Children and Teenagers") ;
    dominantTransport(cityACategories.universityStudentsYoungAdults, cityBCategories.universityStudentsYoungAdults, cityCCategories.universityStudentsYoungAdults, "University Students and Young Adults");
    dominantTransport(cityACategories.workingAdultsEarly, cityBCategories.workingAdultsEarly, cityCCategories.workingAdultsEarly, "Working Adults Early");
    dominantTransport(cityACategories.workingAdultsLate, cityBCategories.workingAdultsLate, cityCCategories.workingAdultsLate, "Working Adults Late");
    dominantTransport(cityACategories.seniorCitizens, cityBCategories.seniorCitizens, cityCCategories.seniorCitizens, "Senior Citizens");
    */ 
   // 


    
    
    
    
    
    


    /*  Question 5 a start 
    LinkedList* citya = implement_dataset("citya.csv");
    LinkedList* cityb = implement_dataset("cityb.csv");
    LinkedList* cityc = implement_dataset("cityc.csv");
   
    cout << "The total Carbon Emissions for city a is " << calculate_total_emissions(citya) <<endl ; 
    cout << "The total Carbon Emissions for city b is " << calculate_total_emissions(cityb) <<endl ;
    cout << "The total Carbon Emissions for city c is " << calculate_total_emissions(cityc) <<endl  ;

     Question 5 a  end  */


    
     
}