/*
    Name: Abdulkadir
    Surname: Pazar
    ID: 150180028
*/

#include <iostream>
#include <string>

#define MAXINGREDIENT 6
#define DRINKTYPE 4
using namespace std;

class Pizza{
    friend class Order;
    friend class Orderlist;
    string name;
    string size;
    string ingredients[MAXINGREDIENT];
    string crust_type;
    int arrsize;

    public:
    Pizza();
    Pizza(string size, string crust_type, int type);
    Pizza(Pizza&);
    ~Pizza();
};

class Order{
    friend class Ordernode;
    friend class Orderlist;
    string customer;
    Pizza* pizzaarray;
    int drink[DRINKTYPE];
    float price;
    int pizzacount;

    public:
    Order(const string, Pizza&, int, int[]);
    Order(const string, Pizza&, int);
    float getPrice();
    void printOrder();
    ~Order();
};

class Ordernode{
    friend class Orderlist;
    Order* order;
    Ordernode* next;

    public:
    Ordernode(Order*);
};

class Orderlist{
    int n;
    Ordernode* head;

    public:
    Orderlist();
    void takeOrder(Order&);
    void listOrders();
    void deliverOrders();
    ~Orderlist();
};
