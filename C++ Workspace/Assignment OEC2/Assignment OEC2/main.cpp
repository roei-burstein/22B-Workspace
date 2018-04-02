/*
 Roei Burstein
 CIS 22B
 Fall 2017
 Assignment OEC2
 Problem OEC2
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
class StringOfCars;

template <class T>
class Node
{
private:
    Node* next;
    T * data;
    Node()
    {
        next = 0;
        data = 0;
    }
    
public:
    friend class StringOfCars;
};


class StringOfCars
{
private:
    Node<Car>* head;
    Node<Car>* tail;
    
public:
    StringOfCars()
    {
        head = 0;
        tail = 0;
    }
    StringOfCars(const StringOfCars &c)
    {
        Node<Car> *currentNodePtr;
        head = 0;
        tail = 0;
        head = c.head;
        if(c.head != 0)
        {
            currentNodePtr = c.head;
            while (currentNodePtr != 0)
            {
                push(*(currentNodePtr->data));
                currentNodePtr = (currentNodePtr->next);
            }
        }
        
        
    }
    ~StringOfCars()
    {
        Node<Car> *currentNodePtr;
        Node<Car> *previousNodePtr;
        currentNodePtr = head;
        while (currentNodePtr != 0)
        {
            delete (currentNodePtr->data);
            previousNodePtr = currentNodePtr;
            currentNodePtr = currentNodePtr->next;
            delete previousNodePtr;
        }
    }
    void push(const Car &c);
    void push(const FreightCar &c);
    void push(const PassengerCar &c);
    void pop(Car &c);
    void output();
};

void input(StringOfCars &soc);

/* ******************** main ********************
 */
int main()
{
    StringOfCars soc;
    input(soc);
    soc.output();
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
    Node<Car> *currentNodePtr = head;
    
    if(head == 0)
    {
        cout << "No cars in list" << endl;
    }
    
    else
    {
        while(currentNodePtr != 0)
        {
            currentNodePtr->data->output();
            currentNodePtr = (currentNodePtr->next);
        }
    }
}

/* ******************** StringOfCars::push() ********************
 Adds Car to StringOfCars array
 */
void StringOfCars::push(const Car &c)
{
    Car *currentCarPtr = new Car(c);
    Node<Car> *currentNodePtr = new Node<Car>;
    currentNodePtr->next = 0;
    currentNodePtr->data = currentCarPtr;
    
    if (head == 0)
    {
        head = currentNodePtr;
        tail = currentNodePtr;
    }
    
    else
    {
        tail->next = currentNodePtr;
        tail = currentNodePtr;
    }
}

/* ******************** StringOfCars::push() ********************
 Adds FreightCar to StringOfCars array
 */
void StringOfCars::push(const FreightCar &c)
{
    FreightCar *currentCarPtr = new FreightCar(c);
    Node<Car> *currentNodePtr = new Node<Car>;
    currentNodePtr->next = 0;
    currentNodePtr->data = currentCarPtr;
    
    if (head == 0)
    {
        head = currentNodePtr;
        tail = currentNodePtr;
    }
    
    else
    {
        tail->next = currentNodePtr;
        tail = currentNodePtr;
    }
}

/* ******************** StringOfCars::push() ********************
 Adds PassengerCar to StringOfCars array
 */
void StringOfCars::push(const PassengerCar &c)
{
    PassengerCar *currentCarPtr = new PassengerCar(c);
    Node<Car> *currentNodePtr = new Node<Car>;
    currentNodePtr->next = 0;
    currentNodePtr->data = currentCarPtr;
    
    if (head == 0)
    {
        head = currentNodePtr;
        tail = currentNodePtr;
    }
    
    else
    {
        tail->next = currentNodePtr;
        tail = currentNodePtr;
    }
}

/* ******************** StringOfCars::pop() ********************
 Removes car from StringOfCars array and saves it into a different car object
 */
/*void StringOfCars::pop(Car &c)
 {
 if(carCount == 0) cerr << "ERROR: No cars in String of Cars";
 else
 {
 c = *ptr[carCount - 1];
 delete ptr[carCount - 1];
 carCount--;
 }
 }
 */

/***************************************************
 Global Functions
 ***************************************************/

/* ******************** input ********************
 Takes the reporting mark, car number, kind, loaded, and destination as value parameters
 Values read from a text file
 */
void input(StringOfCars &soc)
{
    string reportingMark, kind, destination, carType, order;
    int carNumber;
    bool loaded;
    string loadedString;
    
    ifstream inputFile;
    inputFile.open("/Users/roeibustein/Documents/Car1.txt");
    if(!inputFile.is_open())
    {
        fprintf(stderr, "Error Opening File\n");
        exit(1);
    }
    while(inputFile.peek() != EOF)
    {
        
        inputFile >> carType >> order >> reportingMark >> carNumber >> kind >> loadedString;
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
        
        else if(carType == "FreightCar")
        {
            FreightCar temp(reportingMark, carNumber, kind, loaded, destination);
            soc.push(temp);
        }
        
        else if (carType == "PassengerCar")
        {
            PassengerCar temp(reportingMark, carNumber, kind, loaded, destination);
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
 Kind:               other
 Car is loaded:      true
 Destination:        McAlester
 
 Reporting Mark:     MKT
 Car Number:         123456
 Kind:               tank
 Car is loaded:      false
 Destination:        Fort Worth
 
 Reporting Mark:     MP
 Car Number:         98765
 Kind:               box
 Car is loaded:      true
 Destination:        Saint Louis
 
 Reporting Mark:     SP
 Car Number:         567890
 Kind:               flat
 Car is loaded:      true
 Destination:        Chicago
 
 Reporting Mark:     GMO
 Car Number:         7878
 Kind:               otherFreight
 Car is loaded:      true
 Destination:        Mobile
 
 Reporting Mark:     KCS
 Car Number:         7893
 Kind:               chair
 Car is loaded:      true
 Destination:        Kansas City
 
 Reporting Mark:     PAPX
 Car Number:         145
 Kind:               sleeper
 Car is loaded:      true
 Destination:        Tucson
 
 Reporting Mark:     GN
 Car Number:         744
 Kind:               otherPassenger
 Car is loaded:      false
 Destination:        NONE
 */







