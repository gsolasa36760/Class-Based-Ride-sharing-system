#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// -------- Base Ride Class --------
class Ride {
protected:
    string rideID;
    string pickupLocation;
    string dropoffLocation;
    double distance;
    double duration; // in minutes

public:
    Ride(string id, string pickup, string dropoff, double dist, double dur)
        : rideID(id), pickupLocation(pickup), dropoffLocation(dropoff), distance(dist), duration(dur) {}

    virtual double fare() const = 0;

    virtual void rideDetails() const {
        cout << "Ride ID: " << rideID << endl;
        cout << "Pickup: " << pickupLocation << endl;
        cout << "Dropoff: " << dropoffLocation << endl;
        cout << "Distance: " << distance << " miles" << endl;
        cout << "Duration: " << duration << " mins" << endl;
    }

    virtual ~Ride() {}
};

// -------- StandardRide --------
class StandardRide : public Ride {
public:
    StandardRide(string id, string pickup, string dropoff, double dist, double dur)
        : Ride(id, pickup, dropoff, dist, dur) {}

    double fare() const override {
        return 2.5 + (1.2 * distance);
    }

    void rideDetails() const override {
        cout << "[Standard Ride]" << endl;
        Ride::rideDetails();
        cout << fixed << setprecision(2) << "Fare: $" << fare() << endl;
    }
};

// -------- PremiumRide --------
class PremiumRide : public Ride {
public:
    PremiumRide(string id, string pickup, string dropoff, double dist, double dur)
        : Ride(id, pickup, dropoff, dist, dur) {}

    double fare() const override {
        return 5.0 + (2.0 * distance);
    }

    void rideDetails() const override {
        cout << "[Premium Ride]" << endl;
        Ride::rideDetails();
        cout << fixed << setprecision(2) << "Fare: $" << fare() << endl;
    }
};

// -------- CarpoolRide --------
class CarpoolRide : public Ride {
    int passengers;
public:
    CarpoolRide(string id, string pickup, string dropoff, double dist, double dur, int pax)
        : Ride(id, pickup, dropoff, dist, dur), passengers(pax) {}

    double fare() const override {
        return (1.0 + (0.9 * distance)) / passengers;
    }

    void rideDetails() const override {
        cout << "[Carpool Ride]" << endl;
        Ride::rideDetails();
        cout << "Passengers: " << passengers << endl;
        cout << fixed << setprecision(2) << "Fare per passenger: $" << fare() << endl;
    }
};

// -------- Driver --------
class Driver {
private:
    string driverID;
    string name;
    double rating;
    vector<Ride*> completedRides;

public:
    Driver(string id, string n, double r) : driverID(id), name(n), rating(r) {}

    void addRide(Ride* ride) {
        completedRides.push_back(ride);
    }

    void getDriverInfo() const {
        cout << "Driver ID: " << driverID << endl;
        cout << "Name: " << name << endl;
        cout << "Rating: " << rating << endl;
        cout << "Total Rides Completed: " << completedRides.size() << endl;
    }
};

// -------- Rider --------
class Rider {
private:
    string riderID;
    string name;
    vector<Ride*> rideHistory;

public:
    Rider(string id, string n) : riderID(id), name(n) {}

    void requestRide(Ride* ride) {
        rideHistory.push_back(ride);
    }

    void viewRides() const {
        cout << "Rider ID: " << riderID << endl;
        cout << "Name: " << name << endl;
        cout << "Ride History:" << endl;

        for (Ride* ride : rideHistory) {
            ride->rideDetails();
            cout << "-------------------" << endl;
        }
    }
};

// -------- Main --------
int main() {
    // Creating Rides
    Ride* ride1 = new StandardRide("R101", "Lakeview", "City Center", 4.5, 14);
    Ride* ride2 = new PremiumRide("R102", "Downtown", "Airport", 9.0, 25);
    Ride* ride3 = new CarpoolRide("R103", "Library", "University", 5.0, 15, 2);
    Ride* ride4 = new PremiumRide("R104", "Museum", "Opera House", 6.5, 20);

    // Driver
    Driver driver("D300", "Samantha Reed", 4.7);
    driver.addRide(ride1);
    driver.addRide(ride2);
    driver.addRide(ride3);
    driver.addRide(ride4);

    // Rider
    Rider rider("U400", "David Morgan");
    rider.requestRide(ride1);
    rider.requestRide(ride4);
    rider.requestRide(ride3);

    // Display Info
    driver.getDriverInfo();
    cout << endl;
    rider.viewRides();

    // Clean up
    delete ride1;
    delete ride2;
    delete ride3;
    delete ride4;

    return 0;
}
