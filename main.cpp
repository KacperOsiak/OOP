#include <iostream>
#include <string>

using namespace std;

class Address; 
class Review; 
class DiscountCard; 
class User; 
class Order;

void compareCities(const Address& a1, const Address& a2);
bool isTopRated(const Review& r);
void adminResetDiscount(DiscountCard& dc);
void printSensitiveData(const User& u);
void forceOrderStatus(Order& o, string newStatus);

class Address{
    private:
        string city;
        string street;
    public:
        Address(string city, string street){
            this->city = city;
            this->street = street;
        }

        friend class Customer;
        friend void compareCities(const Address& a1, const Address& a2);

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

        friend class Customer;
        friend void printSensitiveData(const User& u);

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
        
        friend class Product;

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

        friend class Product;

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

        friend class Store;
        
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

        friend bool isTopRated(const Review& r);

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

        friend class Customer;
        friend void forceOrderStatus(Order& o, string newStatus);

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

    friend class Customer;
    friend void adminResetDiscount(DiscountCard& dc);

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
        //BEZPOŚREDNIO do profile->name(przyjźń)
        cout << "Przetwarzanie dla: " << profile->name << endl; 

        if(card != nullptr) {
            // Zamiast calculateDiscountedPrice(), card->discount
            double finalPrice = card->calculateDiscountedPrice(totalAmount);
            cout<<"Cena po rabacie: PLN" << finalPrice << endl;
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

void compareCities(const Address& a1, const Address& a2) {
    if(a1.city == a2.city) cout <<"Ta sama lokalizacja." << endl;
    else cout << "Rozne miasta." << endl;
}

bool isTopRated(const Review& r) {
    return r.rating == 5; 
}

void adminResetDiscount(DiscountCard& dc) {
    dc.discount = 0; 
}

void printSensitiveData(const User& u) {
    cout << "[Admin Log]: User " << u.name << " (Email: " << u.email << ")" << endl;
}

void forceOrderStatus(Order& o, string newStatus) {
    o.status = newStatus; //nadpisanie statusu
}

int main() {
    //Stworzenie sklepu i powitanie
    Store myStore("Allegro Lokalnie", true);
    myStore.mainPage();

    //Przygotowanie danych
    User* u = new User("Kacper", "kacper@mail.pl");
    Address* a1 = new Address("Bydgoszcz", "Dluga 10");
    Address* a2 = new Address("Bydgoszcz", "Krotka 2"); // drugi adres do porownania
    
    Customer* cust = new Customer(u, a1);
    DiscountCard* card = new DiscountCard(20);
    Order* ord = new Order(123, "Pending");
    
    cust->setCard(card);
    cust->setCurrentOrder(ord);

    //Testowanie 5 funkcji zaprzyjaznionych
    cout<<"\n--- TEST 5 FUNKCJI ZAPRZYJAZNIONYCH ---"<<endl;
    
    //Funkcja 1: Porównanie miast 
    compareCities(*a1, *a2); 

    //Funkcja 2: Sprawdzenie czy opinia jest TOP 
    Review rev(5, "Bardzo polecam!");
    if(isTopRated(rev)) cout<<"Opinia zweryfikowana jako: TOP RATED"<<endl;

    //Funkcja 3: Logi admina (dostęp do u.name i u.email)
    printSensitiveData(*u);

    //Funkcja 4: Reset rabatu przez admina (bezpośrednia zmiana dc.discount)
    adminResetDiscount(*card);
    cout<<"Rabat po interwencji admina: "<<card->getDiscount()<<"%"<<endl;

    //Funkcja 5: Wymuszenie statusu zamówienia (zmiana o.status)
    forceOrderStatus(*ord, "CANCELED_BY_ADMIN");
    cout<<"Status zamowienia po wymuszeniu: " << ord->getStatus() << endl;

    //4.Test Friend Class (Dostęp wewnatrz Customera)
    cust->processPayment(200);

    //sprzatanie
    delete cust; // To usunie profil, adres, zamowienie i karte
    delete a2;   // Ten adres nie byl w Customerze, usuwamy go osobno

    return 0;
}