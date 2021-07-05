/*
    Name: Abdulkadir
    Surname: Pazar
    ID: 150180028
*/
#include "pizza.h"

Pizza::Pizza()
{
    name = "Mozarella";
    size = "medium";
    ingredients[0] = "mozarella";
    crust_type = "normal";
    arrsize = 1;
}

Pizza::Pizza(string newsize, string newcrust, int newtype)
{
    size = newsize;
    crust_type = newcrust;
    if(newtype == 1){
        name = "Chicken";
        ingredients[0] = "mozarella";
        ingredients[1] = "chicken";
        ingredients[2] = "mushroom";
        ingredients[3] = "corn";
        ingredients[4] = "onion";
        ingredients[5] = "tomato";
        arrsize = 6;
    } else if (newtype == 2){
        name = "Broccoli";
        ingredients[0] = "mozarella";
        ingredients[1] = "broccoli";
        ingredients[2] = "pepperoni";
        ingredients[3] = "olive";
        ingredients[4] = "mushroom";
        ingredients[5] = "corn";
        arrsize = 6;
    } else if (newtype == 3){
        name = "Sausage";
        ingredients[0] = "mozarella";
        ingredients[1] = "sausage";
        ingredients[2] = "tomato";
        ingredients[3] = "olive";
        ingredients[4] = "mushroom";
        ingredients[5] = "corn";
        arrsize = 6;
    }
}

Pizza::Pizza(Pizza& copied)
{
    name = copied.name;
    size = copied.size;
    crust_type = copied.crust_type;
    arrsize = copied.arrsize;
    for(int i = 0; i < arrsize; i++){
        ingredients[i] = copied.ingredients[i];
    }
    int removedingredients[MAXINGREDIENT] = {0,0,0,0,0,0};
 
    int input;
    cout << "Please enter the number of the ingredient you want to remove from your pizza" << endl;
    for(int i = 0; i < arrsize; i++)
        cout << i + 1 << ". " << copied.ingredients[i] << endl;

    cout << "press 0 to save it" << endl;
    while(true){
        cin >> input;
        if(input == 0)
            break;
        if(input < arrsize + 1)
            removedingredients[input - 1]++;
    }
    for(int i = 0; i < arrsize; i++){
        if(removedingredients[i] == 1)
            ingredients[i] = "";
    }
}

Pizza::~Pizza()
{

}

Order::Order(const string name, Pizza& firstpizza, int amount, int drinkarr[])
{
    customer = name;
    pizzaarray = new Pizza[amount];
    pizzaarray[0] = firstpizza; 
    pizzacount = amount;

    for(int i = 1; i < amount; i++){
        pizzaarray[i] = *(new Pizza(firstpizza));
    }
    for(int i = 0; i < 4; i++){
        drink[i] = drinkarr[i];
    }
    if (firstpizza.size == "small")
        price = amount * 15;
    if (firstpizza.size == "medium")
        price = amount * 20;
    if (firstpizza.size == "big")
        price = amount * 25;
    price += drink[0] * 4 + drink[1] * 2 + drink[2] * 3 + drink[3] * 3.5;
}

Order::Order(const string name, Pizza& firstpizza, int amount)
{
    customer = name;
    pizzaarray = new Pizza[amount];
    pizzaarray[0] = firstpizza;
    pizzacount = amount; 

    for(int i = 1; i < amount; i++){
        pizzaarray[i] = *(new Pizza(firstpizza));
    }
    for(int i = 0; i < DRINKTYPE; i++){
        drink[i] = 0;
    }
    price = 0;
    if (firstpizza.size == "small")
        price = amount * 15;
    if (firstpizza.size == "medium")
        price = amount * 20;
    if (firstpizza.size == "big")
        price = amount * 25;
}


float Order::getPrice()
{
    return price;
}

void Order::printOrder()
{
    cout << "------------" << endl;
    cout << "Name: " << customer << endl;
    for(int i = 0; i < pizzacount; i++){
        cout << pizzaarray[i].name << " Pizza( ";
        for (int j = 0; j < pizzaarray[i].arrsize; j++){
            cout << pizzaarray[i].ingredients[j];
            if(pizzaarray[i].ingredients[j] != "")
                cout << ", ";
        }
    cout << " )" << endl;
    cout << "Size: " << pizzaarray[i].size << ", Crust: " << pizzaarray[i].crust_type << endl << endl;
    }
    if (drink[0] != 0 || drink[1] != 0 || drink[2] != 0 || drink[3] != 0){
        if(drink[0] != 0){
                cout << drink[0] << " cola,";
        }
        if(drink[1] != 0){
                cout << drink[1] << " soda,";
        }
        if(drink[2] != 0){
                cout << drink[2] << " ice tea,";
        }
        if(drink[3] != 0){
                cout << drink[3] << " fruit juice";
        }    
    }
    cout << endl << "------------" << endl;
}

Order::~Order()
{       
   delete [] pizzaarray;
}

Ordernode::Ordernode(Order* order)
{
    this->order = order;
    this->next = NULL;
}

Orderlist::Orderlist()
{
    n = 0;
    head = NULL;
}

void Orderlist::takeOrder(Order& order)
{
    Ordernode* newnode = new Ordernode(&order);
    Ordernode* temp = head;
    if(head == NULL){
        head = newnode;
    } else{
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newnode;
    }
    order.printOrder();
    cout << "Your order is saved, it will be delivered when it is ready..." << endl;
    n++;
}

void Orderlist::listOrders()
{
    int item = 1; 
    Ordernode* temp = head;
    while(temp != NULL){
        cout << item << endl;
        item++;
        (*(temp->order)).printOrder();
        temp = temp->next;
    }
}

void Orderlist::deliverOrders()
{
    listOrders();
    Ordernode* temp = head;
    Ordernode* tmp;
    string check, name, code;
    cout << "Please write the customer name in order to deliver his/her order: ";
    cin >> name;
    while(temp->order->customer != name){
        tmp = temp;
        temp = temp->next;
    }
    cout << "Following order is delivering..." << endl;
    (*temp->order).printOrder();
    cout << "Do you have a promotion code? (y/n)" << endl;
    cin >> check;
    if(check == "n"){
        cout << "Total price: " << (*(temp->order)).getPrice() << endl;
        cout << "The order is delivered successfully!" << endl;
    }else if(check == "y"){
        cout << "Please enter your code: " << endl;
        getline(cin, code);
        getline(cin, code);
        if(code.compare("I am a student") == 0){
            cout << "Discounted price: " << 0.9 * (*(temp->order)).getPrice() << endl;
            cout << "The order is delivered successfully!" << endl;
        }
    }

    if (temp==head){
        head = temp->next;
        delete temp->order;
        delete temp;
    }else{
        tmp->next = temp->next;
        delete temp->order;
        delete temp;
    }
}

Orderlist::~Orderlist()
{
    /*Ordernode* temp = head;
    while(head != NULL){
        head = temp->next;
        delete temp->order;
        delete temp;
    }
    */
}

int main()
{
    Orderlist list;
    while(true){
        int input, pizzatype, drinkinput, amount;
        int drink[4] = {0,0,0,0};
        string size,crust,name;
        bool hasDrinks = true;
        Order* orderptr;
        Pizza* pizzaptr;
        cout << "Welcome to Unicorn Pizza!" << endl;
        cout << "1. Add an order" << endl;
        cout << "2. List orders" << endl;
        cout << "3. Deliver orders" << endl;
        cout << "4. Exit" << endl;
        cout << "Choose what to do: " << endl;
        cin >> input;
        if(input == 1){
            cout << "Pizza Menu" << endl;
            cout << "1. Chicken Pizza (mozarella, chicken, mushroom, corn, olive, onion, tomato)" << endl;
            cout << "2. Broccoli Pizza (mozarella, broccoli, pepperoni, olive, corn, onion)" << endl;
            cout << "3. Sausage Pizza (mozarella, sausage, tomato, olive, mushroom, corn)" << endl;
            cout << "0. Back to main menu" << endl;
            cin >> pizzatype;
            cout << "Select size: small (15 TL), medium (20 TL), big (25 TL)" << endl;
            cin >> size;
            cout << "Select crust type: thin, normal, thick" << endl;
            cin >> crust;
            cout << "Enter the amount: ";
            cin >> amount;
            if (pizzatype != 0){
                pizzaptr = new Pizza(size,crust,pizzatype);

                cout << "Please choose a drink: " << endl;
                cout << "0. no drink" << endl;
                cout << "1. cola 4 TL" << endl;
                cout << "2. soda 2 TL" << endl;
                cout << "3. ice tea 3 TL" << endl;
                cout << "4. fruit juice 3.5 TL" << endl;
                cout << "Press -1 to save your order" << endl;
                while(true){
                    cin >> drinkinput;
                    if(drinkinput == -1){
                        break;
                    }
                    if(drinkinput == 0){
                        drink[0] = 0;
                        drink[1] = 0;
                        drink[2] = 0;
                        drink[3] = 0;
                        hasDrinks = false;
                    }
                    if(drinkinput != 0){
                        drink[drinkinput - 1]++;
                        hasDrinks = true;
                    }
                }
                cout << "Please enter your name:" << endl;
                cin >> name;

                if(hasDrinks){
                    orderptr = new Order(name, *pizzaptr, amount, drink);
                    list.takeOrder(*orderptr);
                }else{
                    orderptr = new Order(name, *pizzaptr, amount);
                    list.takeOrder(*orderptr);
                }    
            }
        }
        if(input == 2){
            list.listOrders();
        }
        if(input == 3){
            list.deliverOrders();
        }
        if (input == 4){
            cout << "Goodbye...";
            break;
        }
    }
    return 0;
}