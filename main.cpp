#include <iostream>
#include <string>

using namespace std;

class Address{
    private:
        string city;
        string street;
    public:
        void setAddress(string c, string s){
            city = c;
            street = s;
        }

        string getFullAddress(){
            string full_address = street + "," + city;
            return full_address;
        }
};

class User{
    private:
        string username;
    public:
        User(string u="guest"){
            username = u;
        }
        string getName(){
            return username;
        }
};

class Category{
    private:
        string category_name;
    public:
        void setCategory(string n){
            category_name = n;
        }
        string getCategory(){
            return category_name;
        }
};

class Supplier {
    private:
        string company_name;
    public:
        void setSupplier(string n){
            company_name = n; 
        }
        string getSupplier(){
            return company_name;
        }
};

class Product {
    private:
        string name;
        double price;
        Category category;
        Supplier supplier;
    public:
        Product(string n = "none", double p = 0.0){
            name = n;
            price = p;
        }
        void setDetails(Category c, Supplier s){
            category = c;
            supplier = s;
        }
        void changePrice(double p){
            price = p;
        }
        void showProduct() {
            cout <<"Product: "<<name<<" ["<<category.getCategory()<<"] by "<< supplier.getSupplier()<<" - $"<<price<<endl;
        }
};

class Review{
    private:
        int rating;
        string comment;
    public:
        void addReview(int r, string c){
            rating = r;
            comment = c;
        }
        void showReview(){
            cout<<"Review: "<<rating<<"/5 - "<<comment<<endl;
        }
};

class Order{
    private:
        int id;
        string status;
    public:
        Order(int i=0, string s="none"){
            id = i;
            status = s;
        }
        void setStatus(string s){
            status = s;
        }
       
        string getOrderInfo(){
            return "Order [" + to_string(id) +"]"  + " Status: " + status;
        }
};

class DiscountCard {
private:
    int discount_percent;
public:
    DiscountCard(int d=0){
        discount_percent = d;
    }
    void setDiscount(int p){
        discount_percent = p;
    }
    int getDiscount(){
        return discount_percent;
    }
};

class Customer{
    private:
        User profile;
        Address shipping_info;
        Order current_order;
        DiscountCard card;
    public:
        Customer(User u, Address a){
            profile = u;
            shipping_info = a;
        }
        void assignOrder(Order o){
            current_order = o;
        }
        void giveCard(DiscountCard c){
            card = c;
        }
        void showInfo(){
            cout <<"Customer: " <<profile.getName()<<endl;
            cout <<"Address: " <<shipping_info.getFullAddress()<<endl;
            cout <<"Active: " <<current_order.getOrderInfo()<<endl;
            cout <<"Discount: "<<card.getDiscount()<<"%"<< endl;
        }
};

class Store {
private:
    string store_name;
    bool is_open;
public:
    Store(string n){
        store_name = n;
        is_open = false;
    }
    void openStore(){
        is_open = true;
    }
    void welcome() {
        string temp = "CLOSED";
        if(is_open){
            temp = "OPEN";
        }
        cout<<"Welcome to "<<store_name<<" we are currently "<<temp<<endl;
    }
};

int main() {
    //Przygotowanie podstawowych informacji
    Address myAddr;
    myAddr.setAddress("Warsaw", "Lipowa 12");

    User myUser("Kacper");

    Category myCat;
    myCat.setCategory("Electronics");

    Supplier mySup;
    mySup.setSupplier("Asus");

    //Tworzenie produktu i zmiana jego ceny 
    Product myProd("Gaming Laptop", 1500.0);
    myProd.setDetails(myCat, mySup);
    myProd.showProduct();
    myProd.changePrice(1399.99); 
    myProd.showProduct();
    cout<<endl;

    //Dodanie opinii
    Review myRev;
    myRev.addReview(5, "Fast and reliable, worth every penny!");

    //Obsługa zamówienia i karty rabatowej
    Order myOrder(1001, "Pending");
    myOrder.setStatus("In Delivery"); 

    DiscountCard myCard;
    myCard.setDiscount(10); //10 procent rabatu

    //Łączenie wszystkiego w obiekcie Customer
    Customer myCust(myUser, myAddr);
    myCust.assignOrder(myOrder); //Klient otrzymuje zamówienie
    myCust.giveCard(myCard);     

    //Zarządzanie sklepem
    Store myStore("Allegro");
    
    //Sprawdzamy stan przed otwarciem
    myStore.welcome(); 
    
    myStore.openStore(); //Otwieramy sklep
    
    //Sprawdzamy stan po otwarciu
    myStore.welcome();
    cout<<endl;

    //Wyświetlenie pełnych informacji o kliencie
    myCust.showInfo();
    myRev.showReview();

    return 0;
}