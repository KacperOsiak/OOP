#include <iostream>
#include <string>

using namespace std;

class Address{
    private:
        string city;
        string street;
    public:
        Address(string city, string street){
            this->city = city;
            this->street = street;
        }

        string getCity() const {return this->city;}
        string getStreet() const {return this->street;}
        string getAddress() const {return this->street + "," + this->city;}

        void setCity(string city){this->city = city;}
        void setStreet(string street){this->street = street;}

        ~Address(){
            cout<<"[Destruktor]: Usunieto adres: "<<this->city<<", "<<this->street<<endl;
        }
};

class User{
    private:
        string name;
        string email;
    public:
        User(string name="guest", string email="not_provided"){
            this->name = name;
            this->email = email;
        }

        string getName() const {return this->name;}
        string getEmail() const {return this->email;}

        void setName(string name){this->name = name;}
        void setEmail(string email){this->email = email;}

        ~User(){
            cout<<"[Destruktor]: Usunieto profil uzytkownika: "<<this->name<<endl;
        }
};

class Category{
    private:
        string name;
        string description;
    public:
        Category(string name, string description="empty"){
            this->name = name;
            this->description = description;
        }
        
        string getName() const {return this->name;}
        string getDescription() const {return this->description;}

        void setName(string name){this->name = name;}
        void setDescription(string description){this->description = description;}

        ~Category(){
            cout<<"[Destruktor]: Usunieto kategorie: "<<this->name<<endl;
        }
};

class Supplier {
    private:
        string name;
        string country;
    public:
        Supplier(string name, string country="Poland"){
            this->name = name;
            this->country = country;
        }

        string getName() const {return this->name;}
        string getCountry() const {return this->country;}

        void setName(string name){this->name = name;}
        void setCountry(string country){this->country = country;}

        bool isForeignSupplier() const {
            if(this->country != "Poland"){
                return true;
            }
            return false;
        }
        
        ~Supplier(){
            cout<<"[Destruktor]: Usunieto dostawce: "<<this->name<<endl;
        }
};

class Product {
    private:
        string name;
        double price;
        Category* category;
        Supplier* supplier;
    public:
        Product(string name = "none", double price = 0.0){
            this->name = name;
            this->price = price;
            this->category = nullptr;
            this->supplier = nullptr;
        }
        
        string getName() const {return this->name;}
        double getPrice() const {return this->price;}
        Category* getCategory() const {return this->category;}
        Supplier* getSupplier() const {return this->supplier;}

        void setName(string name){this->name = name;}
        void setPrice(double price){this->price = price;}
        void setCategory(Category* category){this->category = category;}
        void setSupplier(Supplier* supplier){this->supplier = supplier;}

        ~Product(){
            cout<<"[Destruktor]: Usunieto produkt: "<<this->name<<endl;
        }
};

class Review{
    private:
        int rating;
        string comment;
        const int MAX_RATING = 5;
    public:
        Review(int rating, string comment="-"){
            setRating(rating);
            this->comment = comment;
        }
        int getRating() const {return this->rating;}
        string getComment() const {return this->comment;}

        void setRating(int rating) {
            if(rating > MAX_RATING){
                this->rating = MAX_RATING; 
            }else if(rating < 1){
                this->rating = 1; 
            }else{
                this->rating = rating;
            }
        }
        void setComment(string comment){this->comment = comment;}

        void showReview() const {
            cout<<"Review: "<<this->rating<<"/5 - "<<this->comment<<endl;
        }
        ~Review(){
            cout<<"[Destruktor]: Usunieto opinie"<<endl;
        }
};

class Order{
    private:
        int id;
        string status;
    public:
        Order(int id=0, string status="pending"){
            this->id = id;
            this->status = status;
        }
        int getID() const {return this->id;}
        string getStatus() const {return this->status;}
        string getInfo() const {
            return "Order [" + to_string(id) +"]"  + " Status: " + status;
        }

        void setStatus(string status){this->status = status;}

        bool isSent() const {
        if(this->status == "Shipped" || this->status == "Delivered"){
            return true;
        }
        return false;
        }

        ~Order(){
            cout<<"[Destruktor]: Usunieto zamowienie nr: "<<this->id<<endl;
        }

};

class DiscountCard {
private:
    int discount;
public:
    DiscountCard(int discount=0){
        setDiscount(discount);
    }

    void setDiscount(int discount){
        if(discount < 0){
            this->discount = 0;
        }else if(discount > 100){
            this->discount = 100;
        }else{
            this->discount = discount;
        }
    }
    
    int getDiscount() const {return this->discount;}

    double calculateDiscountedPrice(double original_price) const {
        double multiplier = (100.0 - this->discount) / 100.0;
        return original_price * multiplier;
    }

    ~DiscountCard(){
            cout<<"[Destruktor]: Karta rabatowa o ("<<this->discount<<"%) została usunieta"<<endl;
        }
};

class Customer {
private:
    User* profile;
    Address* shipping_info;
    Order* current_order;
    DiscountCard* card;

public:
    Customer(User* profile, Address* shipping_info) {
        this->profile = profile;
        this->shipping_info = shipping_info;
        this->current_order = nullptr;
        this->card = nullptr;
    }

    User* getProfile() const { return this->profile; }
    Address* getShippingInfo() const { return this->shipping_info; }
    Order* getCurrentOrder() const { return this->current_order; }
    DiscountCard* getCard() const { return this->card; }

    void setProfile(User* profile) { this->profile = profile; }
    void setShippingInfo(Address* shipping_info) { this->shipping_info = shipping_info; }
    void setCurrentOrder(Order* current_order) { this->current_order = current_order; }
    void setCard(DiscountCard* card) { this->card = card; }


    void processPayment(double totalAmount) const {
        cout << "[Platnosc]: Przetwarzanie dla " << this->profile->getName() << endl;
        if (this->card != nullptr) {
            double finalPrice = this->card->calculateDiscountedPrice(totalAmount);
            cout << " -> Cena po rabacie: $" << finalPrice << endl;
        } else {
            cout << " -> Cena bez rabatu: $" << totalAmount << endl;
        }
    }

    ~Customer() {
        cout << "\n[Destruktor Customer]: Usuwanie obiektow zaleznych..." << endl;
        if (this->profile != nullptr) delete this->profile;
        if (this->shipping_info != nullptr) delete this->shipping_info;
        if (this->current_order != nullptr) delete this->current_order;
        if (this->card != nullptr) delete this->card;
    }
};

class Store {
private:
    string name;
    bool is_open;
public:
    Store(string name, bool is_open = true){
        this->name = name;
        this->is_open = is_open;
    }

    string getName() const {return this->name;}
    bool getIsOpen() const {return this->is_open;}

    void setName(string name){this->name = name;}
    void setIsOpen(bool is_open){this->is_open = is_open;}

    void mainPage() {
        if(this->is_open){
            cout<<"Nasz sklep jest otwarty zapraszamy!"<<endl;
        }else{
            cout<<"Niesety jestesmy zamknieci :("<<endl;
        }
    }

    ~Store() {
        cout<<"[Destruktor]: Zamykanie systemu sklepu " << this->name<< endl;
    }
};

int main() {
    return 0;
}