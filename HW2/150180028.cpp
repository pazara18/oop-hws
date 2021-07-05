/*
    Name: Abdulkadir
    Surname: Pazar
    ID: 150180028

    Can compile normally
*/

#include <iostream>
#include <string>

using namespace std;


class Person{
    protected:
    string name;
    string surname;

    public:
    Person(){//Default constructor
        name = "";
        surname = "";
    }
    Person(const string& new_name, const string& new_surname){
        name = new_name;
        surname = new_surname;
    }
    Person(const Person& copied){//Copy constructor
        name = copied.name;
        surname = copied.surname;
    }
    virtual void print() const{cout << name << " " << surname << " ";};
};

class Courier : public Person{
    friend class CourierNode;
    string vehicle;
    public:
    Courier():Person(){//Default constructor
        vehicle = "";
    }
    Courier(const string& new_name,const string& new_surname, const string & vehicle_type):Person(new_name,new_surname){
        if(vehicle_type != "car" && vehicle_type != "motorcycle" && vehicle_type != "bicycle"){
            cout << "Enter a correct vehicle type please" << endl << "Exiting...";
            exit(1);
        }
        vehicle = vehicle_type;
    }
    Courier(const Courier& copied):Person(copied){//Copy constructor
        vehicle = copied.vehicle;
    }
    void print() const{
        Person::print();
        cout << vehicle << endl;
    }
    bool operator==(Courier& compared){//Checks for equality between couriers
        return (name == compared.name && surname == compared.surname && vehicle == compared.vehicle);
    }
    string getVehicle(){return vehicle;}
};

class CourierNode{
    friend class Business;
    Courier courier;
    CourierNode* next;

    public:
    CourierNode(Courier& added){
        courier = added;
        next = NULL;
    }
};

class Owner : public Person{
    float ownership;
    public:
    Owner():Person(){
        ownership = 0;
    }
    Owner(const string& new_name,const string& new_surname):Person(new_name,new_surname){
        ownership = 0;
    }
    Owner(const Owner& copied):Person(copied){
        ownership = copied.ownership;
    }
    void print() const{
        Person::print();
        cout << ownership << endl;
    }
    void setOwnership(float new_ownership){ownership = new_ownership;}
};

class Business{
    string name;
    string address;
    Owner* owner_array;
    int owner_number;
    CourierNode* chead;

    public:
    Business(const string& new_name, const string& new_address, Owner* owner_arr, int owner_num);
    void hire_courier(Courier&);
    void fire_courier(Courier&);
    void list_couriers();
    void list_owners();
    int calculate_shipment_capacity();
    Courier& operator[](int);
    void operator()();
    ~Business();
};

Business::Business(const string& new_name, const string& new_address, Owner* owner_arr, int owner_num)
{
    name = new_name;
    address = new_address;
    owner_number = owner_num;
    chead = NULL;
    owner_array = new Owner[owner_num];
    for(int i = 0; i < owner_num; i++){
        owner_array[i] = owner_arr[i];
        owner_array[i].setOwnership(100/owner_num);
    }
}

void Business::hire_courier(Courier& hired)
{
    CourierNode* nn = new CourierNode(hired);
    CourierNode* temp = chead;
    if (chead == NULL){
        chead = nn;
        return;
    }
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = nn;
}

void Business::fire_courier(Courier& fired)
{
    CourierNode* temp = chead;
    CourierNode* tmp = chead;
    if(fired == chead->courier){
        chead = chead->next;
        delete temp;
        return;
    }
    while(temp != NULL){
        if (temp->courier == fired)
            break;
        if (temp->next == NULL){
            cout << "Courier not found" << endl;
            getchar();
            exit(1);
        }        
        tmp = temp;
        temp = temp->next;
    }
    tmp->next = temp->next;
    delete temp;
}

void Business::list_couriers()
{
    CourierNode* temp = chead;
    while(temp != NULL){
        temp->courier.print();
        temp = temp->next;
    }
}

void Business::list_owners()
{
    for(int i = 0; i < owner_number; i++)
        owner_array[i].print();
}

int Business::calculate_shipment_capacity()
{
    int capacity = 0;
    CourierNode* temp = chead;
    while(temp != NULL){
        if (temp->courier.getVehicle() == "car")
            capacity += 200;
        if (temp->courier.getVehicle() == "motorcycle")
            capacity += 35;
        if (temp->courier.getVehicle() == "bicycle")
            capacity += 10;
        temp = temp->next;
    }
    return capacity;
}

Courier& Business::operator[](int index)
{
    CourierNode* temp = chead;
    for(int i = 0; i < index; i++){
        if(temp->next == NULL){
            cout << "Invalid index" << endl;
            exit(1);
        }
        temp = temp->next;
    }
    return temp->courier;
}

void Business::operator()()
{
    cout << name << " " << address << endl;
    list_owners();
    list_couriers();
}

Business::~Business()
{
    delete [] owner_array;
    CourierNode* temp = chead;
    while(chead != NULL){
        temp = chead;
        chead = chead->next;
        delete temp;
    }
}

int main(){
    // Create owners of the business
    //Constructor parameters: name, surname
    Owner o1 = Owner("Owner_name1", "surname1");
    Owner o2 = Owner("Owner_name2", "surname2");
    Owner* owner_arr = new Owner[2];
    owner_arr[0] = o1;
    owner_arr[1] = o2;    

    //Crete the business itself
    //Constructor parameters: name, address, owner_array, number_of_owners
    Business atlas = Business("Atlas", "Maslak Istanbul/Turkey", owner_arr, 2);
    
    // Print owner info to screen: name, surname, ownership
    atlas.list_owners();

    // Add new employees
    // Constructor parameters: name, surname, vehicle_type
    Courier c1 = Courier("Courier", "surname1", "car");
    Courier c2 = Courier("Courier", "surname2", "motorcycle");
    Courier c3 = Courier("Courier", "surname3", "motorcycle");    

    atlas.hire_courier(c1);
    atlas.hire_courier(c2);
    atlas.hire_courier(c3);


    // Print business info to screen
    // Name, address, owners, couriers
    atlas();

    // Get courier with index 1 and remove it from the list/array
    Courier cour = atlas[1];
    atlas.fire_courier(cour);
    
    // Print remaining couriers
    atlas.list_couriers();
    
    // Print current maximum shipment capacity
    std::cout << atlas.calculate_shipment_capacity() << std::endl;
    return 0;
}