/*
 Roei Burstein
 CIS 22B
 Fall 2017
 Assignment OEC1
 Problem OEC1
 Car parameters are read from a text file. The car objects then prints out their parameters.
 */

#include <iostream>
#include <fstream>
#include <vector>

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
    Car & operator=(const Car & carB);
    
};

class StringOfCars
{
private:
    vector<Car> carVector;
public:
    StringOfCars()
    {

    }
    StringOfCars(const StringOfCars &c)
    {
        carVector = c.carVector;
    }
    ~StringOfCars()
    {
    }
    void push(Car &c);
    void pop(Car &c);
    void output();
};

void input(StringOfCars &soc);

/* ******************** main ********************
 */
int main()
{
    cout << "Test 1:" << endl;
    Car car1("SP", 34567, "business", 1, "Salt Lake City");
    Car car2;
    car2 = car1;
    car2.output();
    
    cout << "\nTest 2:\n" << endl;
    StringOfCars string1;
    input(string1);
    cout << "STRING 1:" << endl;
    string1.output();
    
    cout << "\nTest 3:\n" << endl;
    Car car3;
    string1.pop(car3);
    cout << "CAR 3:" << endl;
    car3.output();
    cout << "\nSTRING 1:" << endl;
    string1.output();
    
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

/* ******************** Car::operator= ********************
 sets the values in the left hand object from the right hand object
 */
Car & Car::operator=(const Car & carB)
{
    setUp(carB.reportingMark, carB.carNumber, carB.kind, carB.loaded, carB.destination);
    
    return * this;
}
/***************************************************
 StringOfCars Member Functions
 ***************************************************/

/* ******************** StringOfCars::output() ********************
 Prints out car objects in StringOfCars array
 */
void StringOfCars::output()
{
    if(carVector.size() == 0) cout << "NO cars";
    
    for(int i = 0; i < carVector.size(); i++)
    {
        cout << "\nCar Number: " << i + 1 << endl;
        (carVector.at(i)).output();
    }
}

/* ******************** StringOfCars::push() ********************
 Adds car to StringOfCars array
 */
void StringOfCars::push(Car &c)
{
    carVector.push_back(c);
}

/* ******************** StringOfCars::pop() ********************
 Removes car from StringOfCars array and saves it into a different car object
 */
void StringOfCars::pop(Car &c)
{
    if(carVector.size() == 0) cout << "ERROR: No cars in String of Cars";
    else
    {
        c = carVector.back();
        carVector.pop_back();
    }
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
void input(StringOfCars &soc)
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
            soc.push(temp);
        }
        
        else
        {
            cout << "\nError: carType not 'Car'\n";
        }
    }
    inputFile.close();
}
/* Execution results
 Test 1:
 
 Reporting Mark:     SP
 Car Number:         34567
 Kind:               business
 Car is loaded:      true
 Destination:        Salt Lake City
 
 Test 2:
 
 STRING 1:
 
 Car Number: 1
 
 Reporting Mark:     CN
 Car Number:         819481
 Kind:               maintenance
 Car is loaded:      false
 Destination:        NONE
 
 Car Number: 2
 
 Reporting Mark:     SLSF
 Car Number:         46871
 Kind:               business
 Car is loaded:      true
 Destination:        Memphis
 
 Car Number: 3
 
 Reporting Mark:     AOK
 Car Number:         156
 Kind:               tender
 Car is loaded:      true
 Destination:        McAlester
 
 Test 3:
 
 CAR 3:
 
 Reporting Mark:     AOK
 Car Number:         156
 Kind:               tender
 Car is loaded:      true
 Destination:        McAlester
 
 STRING 1:
 
 Car Number: 1
 
 Reporting Mark:     CN
 Car Number:         819481
 Kind:               maintenance
 Car is loaded:      false
 Destination:        NONE
 
 Car Number: 2
 
 Reporting Mark:     SLSF
 Car Number:         46871
 Kind:               business
 Car is loaded:      true
 Destination:        Memphis
 */



