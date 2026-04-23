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
    protected:
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

        virtual ~User(){
            cout<<"[Destruktor]: Usunieto profil uzytkownika: "<<this->name<<endl;
        }
};

class Admin : public User {
private:
    int permission_level;
public:
    Admin(string name, string email, int level) : User(name, email) {
        this->permission_level = level;
    }

    ~Admin() {
        cout << "[Destruktor]: Usunieto uprawnienia administracyjne poziomu: " << this->permission_level << endl;
    }

    void systemMaintenance() {
        cout << "[System]: Administrator " << this->name << " rozpoczyna procedure konserwacji." << endl;
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
    protected:
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

        virtual ~Product(){
            cout<<"[Destruktor]: Usunieto produkt: "<<this->name<<endl;
        }
};


class Electronics : public Product {
protected:
    int warranty_period;
public:
    Electronics(string name, double price, int warranty) : Product(name, price) {
        this->warranty_period = warranty;
    }

    virtual ~Electronics() {
        cout << "[Destruktor]: Zakonczono cykl serwisowy dla elektroniki." << endl;
    }
};

class Computer : public Electronics {
protected:
    string cpu_model;
    int ram_amount;
public:
    Computer(string name, double price, int warranty, string cpu, int ram) 
        : Electronics(name, price, warranty) {
        this->cpu_model = cpu;
        this->ram_amount = ram;
    }

    virtual ~Computer() {
        cout << "[Destruktor]: Zarchiwizowano konfiguracje jednostki obliczeniowej." << endl;
    }
};

class Laptop : public Computer {
protected:
    double screen_size;
    int battery_life;
public:
    Laptop(string name, double price, int warranty, string cpu, int ram, double screen, int battery) 
        : Computer(name, price, warranty, cpu, ram) {
        this->screen_size = screen;
        this->battery_life = battery;
    }

    virtual ~Laptop() {
        cout << "[Destruktor]: Usunieto parametry mobilne urzadzenia." << endl;
    }
};

class GamingLaptop : public Laptop {
private:
    string gpu_model;
    int refresh_rate;
public:
    GamingLaptop(string name, double price, int warranty, string cpu, int ram, double screen, int battery, string gpu, int hz) 
        : Laptop(name, price, warranty, cpu, ram, screen, battery) {
        this->gpu_model = gpu;
        this->refresh_rate = hz;
    }

    void displaySpecs() const {
        cout << "--- SPECYFIKACJA LAPTOPA GAMINGOWEGO ---" << endl;
        cout << "Model: " << this->name << " | Procesor: " << this->cpu_model << endl;
        cout << "Grafika: " << this->gpu_model << " | Odswiezanie: " << this->refresh_rate << "Hz" << endl;
    }

    ~GamingLaptop() {
        cout << "[Destruktor]: Usunieto konfiguracje wysokiej wydajnosci." << endl;
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
    Store myStore("Tech-Premium", true);
    myStore.mainPage();
    //Tworzenie obiektow
    Category* cat = new Category("Sprzet Komputerowy", "Urzadzenia o wysokiej wydajnosci");
    Supplier* sup = new Supplier("MSI Polska", "Poland");

    // Tworzenie najbardziej wyspecjalizowanego obiektu
    GamingLaptop* myGamingLaptop = new GamingLaptop(
        "MSI Raider GE78", // Product::name
        15500.0,           // Product::price
        24,                // Electronics::warranty_period
        "Intel i9-13980HX",// Computer::cpu_model
        64,                // Computer::ram_amount
        17.3,              // Laptop::screen_size
        99,                // Laptop::battery_life
        "RTX 4090",        // GamingLaptop::gpu_model
        240                // GamingLaptop::refresh_rate
    );
    myGamingLaptop->setCategory(cat);
    myGamingLaptop->setSupplier(sup);
    
    // Wywołanie metody z poziomu 5, która korzysta z atrybutów poziomów 1 i 3
    myGamingLaptop->displaySpecs();

    Admin* sysAdmin = new Admin("Rafal", "admin@techpremium.pl", 10);
    
    // Wywołanie metody specyficznej dla klasy Admin, korzystającej z pola klasy User
    sysAdmin->systemMaintenance();
    
    // Test funkcji zaprzyjaznionej korzystajacej z klasy nadrzednej (User)
    printSensitiveData(*sysAdmin);

    // TEST INTEGRACJI Z KLASA CUSTOMER
    User* clientProfile = new User("Jan Kowalski", "j.kowalski@poczta.pl");
    Address* clientAddr = new Address("Warszawa", "Marszalkowska 10");
    Customer* client = new Customer(clientProfile, clientAddr);
    
    DiscountCard* goldCard = new DiscountCard(15);
    client->setCard(goldCard);
    
    // Przetwarzanie platnosci za laptopa z wykorzystaniem dziedziczonej ceny
    client->processPayment(myGamingLaptop->getPrice());

    //CZYSZCZENIE PAMIECI
    delete client;          // Usuwa Customer, profil User i Address
    delete myGamingLaptop;  // Wywoluje 5 destruktorow: GamingLaptop -> Laptop -> Computer -> Electronics -> Product
    delete sysAdmin;        // Wywoluje 2 destruktory: Admin -> User
    delete cat;             
    delete sup;             

    return 0;
    
}