#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string companyName = "Kabarak Motors";

class Vehicle {
protected:
    string brand;
    string model;
public:
    static int count;
    
    Vehicle(string b, string m) {
        brand = b;
        model = m;
        count++;
    }
    
    virtual void displayInfo() {
        cout << "Brand: " << brand << ", Model: " << model << endl;
    }
    
    void updateModel() {
        string newModel;
        cout << "Enter new model: ";
        cin >> newModel;
        model = newModel;
    }
    
    virtual string getFileData() {
        return brand + " " + model;
    }
    
    virtual ~Vehicle() {}
};

int Vehicle::count = 0;

class Car : public Vehicle {
private:
    int seats;
public:
    Car(string b, string m, int s) : Vehicle(b, m) {
        if (s < 0)
            throw invalid_argument("Seats cannot be negative!");
        seats = s;
    }
    
    void displayInfo() override {
        cout << "Car -> Brand: " << brand
             << ", Model: " << model
             << ", Seats: " << seats << endl;
    }
    
    string getFileData() override {
        return "Car " + brand + " " + model + " Seats:" + to_string(seats);
    }
};

class Motorbike : public Vehicle {
private:
    int engineCapacity;
public:
    Motorbike(string b, string m, int ec) : Vehicle(b, m) {
        if (ec < 0)
            throw invalid_argument("Engine capacity cannot be negative!");
        engineCapacity = ec;
    }
    
    void displayInfo() override {
        cout << "Motorbike -> Brand: " << brand
             << ", Model: " << model
             << ", Engine Capacity: " << engineCapacity << "cc" << endl;
    }
    
    string getFileData() override {
        return "Motorbike " + brand + " " + model +
               " Engine:" + to_string(engineCapacity);
    }
};

int main() {
    cout << "Company Name: " << companyName << endl << endl;
    
    Vehicle* vehicles[4];
    
    try {
        vehicles[0] = new Car("Toyota", "Corolla", 5);
        vehicles[1] = new Car("Honda", "Civic", 4);
        vehicles[2] = new Motorbike("Yamaha", "YZF", 600);
        vehicles[3] = new Motorbike("Suzuki", "GSX", 750);
    } catch (exception &e) {
        cout << "Error: " << e.what() << endl;
        return 0;
    }
    
    cout << "Total vehicles created: " << Vehicle::count << endl << endl;
    
    cout << "Displaying Vehicle Details:\n";
    for (int i = 0; i < 4; i++) {
        vehicles[i]->displayInfo();
    }
    
    ofstream fout("vehicles.txt");
    for (int i = 0; i < 4; i++) {
        fout << vehicles[i]->getFileData() << endl;
    }
    fout.close();
    
    cout << "\nVehicle details written to vehicles.txt\n";
    
    cout << "\nData read from file:\n";
    ifstream fin("vehicles.txt");
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
    fin.close();
    
    for (int i = 0; i < 4; i++) {
        delete vehicles[i];
    }
    
    return 0;
}
