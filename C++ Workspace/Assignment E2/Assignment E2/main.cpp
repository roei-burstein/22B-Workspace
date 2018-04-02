/*
 Roei Burstein
 CIS 22B
 Fall 2017
 Assignment E
 Problem E2
 Car parameters are read from a text file. The car objects then prints out their parameters.
 */

#include <iostream>
#include <fstream>
using namespace std;

class Car
{
protected:
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
    virtual ~Car() {}
    friend bool operator==(const Car &car1, const Car &car2);
    void setUp(string reportingMark, int carNumber, string kind, bool loaded, string destination);
    void output();
    virtual void setKind(string &kind);
    Car & operator=(const Car & carB);
    
};

class FreightCar : public Car
{
public:
    FreightCar():Car()
    {
        setUp("", 0, "otherFreight", false, "NONE");
    };
    FreightCar(const FreightCar &c):Car(c)
    {
        setUp(c.reportingMark, c.carNumber, c.kind, c.loaded, c.destination);
    };
    FreightCar(string reportingMark, int carNumber, string kind, bool loaded, string destination):Car(reportingMark, carNumber, kind, loaded, destination)
    {
        setUp(reportingMark, carNumber, kind, loaded, destination);
    };
    void setKind(string &k);
    FreightCar & operator=(const FreightCar & carB);

};

class PassengerCar : public Car
{
public:
    PassengerCar():Car()
    {
        setUp("", 0, "otherPassenger", false, "NONE");
    };
    PassengerCar(const PassengerCar &c):Car(c)
    {
        setUp(c.reportingMark, c.carNumber, c.kind, c.loaded, c.destination);
    };
    PassengerCar(string reportingMark, int carNumber, string kind, bool loaded, string destination):Car(reportingMark, carNumber, kind, loaded, destination)
    {
        setUp(reportingMark, carNumber, kind, loaded, destination);
    };
    void setKind(string &k);
    PassengerCar & operator=(const PassengerCar & carB);

    
};

class StringOfCars
{
private:
    static const int ARRAY_SIZE = 10;
    Car **ptr;
    int carCount;
    
public:
    StringOfCars()
    {
        ptr = new Car*[ARRAY_SIZE];
        for(int i = 0; i < ARRAY_SIZE; i++){
            ptr[i] = 0;
        }
        carCount = 0;
    }
    StringOfCars(const StringOfCars &c)
    {
        ptr = new Car*[ARRAY_SIZE];
        carCount = c.carCount;
        for(int i = 0; i < ARRAY_SIZE; i++){
            ptr[i] = c.ptr[i];
        }
    }
    ~StringOfCars()
    {
        for(int i = 0; i < carCount; i++)
        {
            pop(*ptr[i]);
        }
        delete [] ptr;
    }
    void push(const Car &c);
    void pop(Car &c);
    void output();
};

void input(StringOfCars &soc);

/* ******************** main ********************
 */
int main()
{
    Car *car1 = new Car("SLSF", 46871, "wrecker", true, "Memphis");
    car1->output();
    FreightCar *car2 = new FreightCar("MP", 98765, "gondola", true, "Saint Louis");
    car2->output();
    PassengerCar *car3 = new PassengerCar("PAPX", 145, "combine", true, "Tucson");
    car3->output();
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
    reportingMark = rm;
    carNumber = cn;
    kind = k;
    loaded = l;
    destination = d;
    (*this).setKind(k);
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

/* ******************** Car::setKind ********************
 sets the 'kind' field for the Car object
 */
void Car::setKind(string &k)
{
    if(k != "business" && k != "maintenance") kind = "other";
}

/***************************************************
 FreightCar Member Functions
 ***************************************************/

/* ******************** FreightCar::operator= ********************
 sets the values in the left hand object from the right hand object
 */
FreightCar & FreightCar::operator=(const FreightCar & carB)
{
    setUp(carB.reportingMark, carB.carNumber, carB.kind, carB.loaded, carB.destination);
    
    return * this;
}

/* ******************** FreightCar::setKind ********************
 sets the 'kind' field for the FreightCar object
 */
void FreightCar::setKind(string &k)
{
    if(k != "box" && k != "tank" && k != "flat") kind = "otherFreight";
}

/***************************************************
 PassengerCar Member Functions
 ***************************************************/

/* ******************** PassengerCar::operator= ********************
 sets the values in the left hand object from the right hand object
 */
PassengerCar & PassengerCar::operator=(const PassengerCar & carB)
{
    setUp(carB.reportingMark, carB.carNumber, carB.kind, carB.loaded, carB.destination);
    
    return * this;
}

/* ******************** PassengerCar::setKind ********************
 sets the 'kind' field for the PassengerCar object
 */
void PassengerCar::setKind(string &k)
{
    if(k != "chair" && k != "sleeper") kind = "otherPassenger";
}

/***************************************************
 Car Friend Functions
 ***************************************************/

/* ******************** operator== ********************
 Compares two car objects to see if they equal
 */
bool operator==(const Car &car1, const Car &car2)
{
    return (car1.reportingMark == car2.reportingMark && car1.carNumber == car2.carNumber);
}

/***************************************************
 StringOfCars Member Functions
 ***************************************************/

/* ******************** StringOfCars::output() ********************
 Prints out car objects in StringOfCars array
 */
void StringOfCars::output()
{
    if(carCount == 0) cout << "NO cars";
    
    for(int i = 0; i < carCount; i++)
    {
        cout << "\nCar Number: " << i + 1 << endl;
        (*ptr[i]).output();
    }
    
    
}

/* ******************** StringOfCars::push() ********************
 Adds car to StringOfCars array
 */
void StringOfCars::push(const Car &c)
{
    Car*car = new Car;
    *car = c;
    if(carCount < ARRAY_SIZE)
    {
        ptr[carCount] = car;
        carCount++;
    }
    else cout << "Car array is full, cannot add car";
}

/* ******************** StringOfCars::pop() ********************
 Removes car from StringOfCars array and saves it into a different car object
 */
void StringOfCars::pop(Car &c)
{
    if(carCount == 0) cerr << "ERROR: No cars in String of Cars";
    else
    {
        c = *ptr[carCount - 1];
        delete ptr[carCount - 1];
        carCount--;
    }
}

/***************************************************
 Global Functions
 ***************************************************/

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
            cerr << "\nError: carType not 'Car'\n";
        }
    }
    inputFile.close();
}
/* Execution results
 Reporting Mark:     SLSF
 Car Number:         46871
 Kind:               other
 Car is loaded:      true
 Destination:        Memphis
 
 Reporting Mark:     MP
 Car Number:         98765
 Kind:               otherFreight
 Car is loaded:      true
 Destination:        Saint Louis
 
 Reporting Mark:     PAPX
 Car Number:         145
 Kind:               otherPassenger
 Car is loaded:      true
 Destination:        Tucson
 */
