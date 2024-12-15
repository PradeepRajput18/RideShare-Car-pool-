#include<iostream>
#include<bits/stdc++.h>

using namespace std;

class Person {

protected:
    string name;
    int uberID;
    string origin,destination;

public:
    virtual void input(){
        cout<<"Enter name: ";
        cin>>name;
        cout<<"Enter Uber ID:";
        cin>>uberID;
        cout<<"Enter Origin";
        cin>>origin;
        cout<<"Enter Destination";
        cin>>destination;

        transform(origin.begin(),origin.end(),origin.begin(),::toupper);
        transform(destination.begin(),destination.end(),destination.begin(),::toupper);

    };

    virtual void display() const{
        cout<<"Name: "<<name<<"\n Uber ID: "<<uberID<<"\n Origin: "<<origin<<"\n Destination: "<<destination<<endl;
    }

    string getOrigin() const { return origin;}
    string getDestination() const { return destination;}
};


class Driver : public Person {
    string carNo;
    int availableSeats , pricePerKM;

public:
    void input() override {
        Person::input();
        cout<<"Enter Car number: ";
        cin>>carNo;
        cout<<"Enter Available Seats";
        cin>>availableSeats;
        cout<<"Enter Price per KM: ";
        cin>> pricePerKM;
    }

    void display() const override{
        Person::display();

        cout<<"Available Seats"<<availableSeats<<"\nPrice per KM: "<<pricePerKM<<endl;
    }

    int getAvailableSeats() const {
        return availableSeats;
    }

    void bookSeats(int seats){ availableSeats-=seats;}

    string getName() const { return name;}

};


class Passenger : public Person {
    int totalPassengers;

public:
    void input() override{
        Person::input();
        cout<<"Enter total passengers: ";
        cin>>totalPassengers;
    }

    void display() const override{
        Person::display();
        cout<<"Total passangers: "<<totalPassengers<<endl;
    }

    int getTotalPassengers() const { return totalPassengers;}
};



int getLocationIndex( const string& location){
    static const vector<string> locations = {"NEW YORK", "BOSTON", "ATLANTA", "AUGUSTA", 
        "LOS ANGELES", "CHICAGO", "HOUSTON", "PHOENIX", 
        "PHILADELPHIA", "SAN ANTONIO", "SAN DIEGO", "DALLAS", 
        "SAN JOSE", "AUSTIN", "JACKSONVILLE", "FORT WORTH", 
        "COLUMBUS", "CHARLOTTE", "INDIANAPOLIS", "DENVER", 
        "WASHINGTON", "SEATTLE", "BOSTON", "NASHVILLE", 
        "EL PASO", "DETROIT", "MEMPHIS", "PORTLAND", 
        "LAS VEGAS", "LOUISVILLE", "BALTIMORE", "MILWAUKEE"};

    return find(locations.begin(), locations.end(), location) - locations.begin();
};


int main() {
    vector<Driver> drivers;
    vector<Passenger> passengers;

    cout << ":::<====WELCOME TO THE RIDE SHARE====>:::" << endl;

    while (true) {
        cout << "\nEnter 1 for DRIVER, 2 for PASSENGER, 3 to EXIT: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            Driver d;
            d.input();
            drivers.push_back(d);
        } else if (choice == 2) {
            Passenger p;
            p.input();
            passengers.push_back(p);

            cout << "\n==========> AVAILABLE RIDES <==========" << endl;
            int passengerStart = getLocationIndex(p.getOrigin());
            int passengerEnd = getLocationIndex(p.getDestination());

            bool rideFound = false;
            for (size_t i = 0; i < drivers.size(); ++i) {
                int driverStart = getLocationIndex(drivers[i].getOrigin());
                int driverEnd = getLocationIndex(drivers[i].getDestination());

                if ((passengerStart < passengerEnd && driverStart < driverEnd &&
                     passengerStart >= driverStart && passengerEnd <= driverEnd) ||
                    (passengerStart > passengerEnd && driverStart > driverEnd &&
                     passengerStart <= driverStart && passengerEnd >= driverEnd)) {
                    if (p.getTotalPassengers() <= drivers[i].getAvailableSeats()) {
                        drivers[i].display();
                        cout << "Enter " << i + 1 << " to confirm your ride with " << drivers[i].getName() << " or 0 to not confirm it" << endl;
                        rideFound = true;
                    }
                }
            }

            if (rideFound) {
                int confirmChoice;
                cin >> confirmChoice;
                if (confirmChoice > 0 && confirmChoice <= static_cast<int>(drivers.size())) {
                    drivers[confirmChoice - 1].bookSeats(p.getTotalPassengers());
                    cout << "Your ride with " << drivers[confirmChoice - 1].getName() << " has been confirmed." << endl;
                }
            } else {
                cout << "Sorry, no rides available. Please try again." << endl;
            }
        } else if (choice == 3) {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    cout << "Thank you for using RideShare. Have a safe journey!" << endl;
    return 0;
}