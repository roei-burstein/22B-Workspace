/*
 Roei Burstein
 CIS 22B
 Fall 2017
 Assignment D
 Problem D1
 Car parameters are read from a text file. The car objects then prints out their parameters.
 */

#include <iostream>
#include <fstream>
using namespace std;

class Car
{
private:
    int carNumber;
    bool loaded;
    string reportingMark, kind, destination;
public:
    Car()
    {
        setUp("", 0, "other", false, "NONE");
    }
    Car(const Car &c)
    {
        setUp(c.reportingMark, c.carNumber, c.kind, c.loaded, c.destination);
    }
    Car(string reportingMark, int carNumber, string kind, bool loaded, string destination)
    {
        setUp(reportingMark, carNumber, kind, loaded, destination);
    }
    ~Car() {}
    friend bool operator==(const Car &car1, const Car &car2);
    void setUp(string reportingMark, int carNumber, string kind, bool loaded, string destination);
    void output();
};

void input();

/* ******************** main ********************
 */
int main()
{
    input();
}
/***************************************************
 Car Member Functions
 ***************************************************/

/* ******************** Car::setUp ********************
 Takes 5 parameters by value: reporting mark, car number, kind, loaded, and destination
 Inputs these paramaters into the Car class' variables
 */
void Car::setUp(string rm, int cn, string k, bool l, string d)
{
    
    reportingMark = rm, carNumber = cn, kind = k, loaded = l, destination = d;
}

/* ******************** Car::output ********************
 Prints the reporting mark, car number, kind, loaded, and destination in a neat format
 */
void Car::output()
{
    string isLoaded;
    if(loaded) isLoaded = "true";
    else isLoaded = "false";
    cout << "\nReporting Mark: \t" << reportingMark << "\nCar Number: \t\t" << carNumber << "\nKind: \t\t\t\t" << kind << "\nCar is loaded: \t\t" << isLoaded << "\nDestination: \t\t" << destination << endl;
}

/***************************************************
 Global Functions
 ***************************************************/

/* ******************** operator== ********************
 Compares two car objects to see if they equal
 */
bool operator==(const Car &car1, const Car &car2)
{
    return (car1.reportingMark == car2.reportingMark && car1.carNumber == car2.carNumber);
}

/* ******************** input ********************
 Takes the reporting mark, car number, kind, loaded, and destination as value parameters
 Values read from a text file
 */
void input()
{
    string reportingMark, kind, destination, carType;
    int carNumber;
    bool loaded;
    string loadedString;
    
    ifstream inputFile;
    inputFile.open("/Users/roeibustein/Documents/Assignment D1/Assignment D1/Car.txt");
    if(!inputFile.is_open())
    {
        fprintf(stderr, "Error Opening File\n");
        exit(1);
    }
    while(inputFile.peek() != EOF)
    {
        
        inputFile >> carType >> reportingMark >> carNumber >> kind >> loadedString;
        if(loadedString == "true") loaded = true;
        else if(loadedString == "false") loaded = false;
        else cout << "There has been a problem with loaded";
        while(inputFile.peek() == ' ')
        {
            inputFile.get();
        }
        
        getline(inputFile, destination, '\n');
        
        if(carType == "Car")
        {
            Car temp(reportingMark, carNumber, kind, loaded, destination);
            temp.output();
        }
        
        else
        {
            cout << "\nError: carType not 'Car'\n";
        }
    }
    inputFile.close();
}
/* Execution results
 Reporting Mark:     CN
 Car Number:         819481
 Kind:               maintenance
 Car is loaded:      false
 Destination:        NONE
 
 Reporting Mark:     SLSF
 Car Number:         46871
 Kind:               business
 Car is loaded:      true
 Destination:        Memphis
 
 Reporting Mark:     AOK
 Car Number:         156
 Kind:               tender
 Car is loaded:      true
 Destination:        McAlester
 */

