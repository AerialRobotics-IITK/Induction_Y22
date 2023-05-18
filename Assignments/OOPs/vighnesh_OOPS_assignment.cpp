#include <iostream>
#include <vector>
#include <cmath>

class Passenger {
private:
    std::string name;
    std::string username;
    std::string password;
public:
    Passenger(const std::string& name, const std::string& username, const std::string& password)
        : name(name), username(username), password(password) {}

    const std::string& getUsername() const {
        return username;
    }

    // Other getter methods for name and password

    void bookTicket(const std::string& startLocation, const std::string& endLocation, const std::string& date);
};

class Train {
private:
    std::string startLocation;
    std::string endLocation;
    std::string date;
    std::vector<std::vector<bool>> seats;  // Matrix to track seat availability
public:
    Train(const std::string& startLocation, const std::string& endLocation, const std::string& date)
        : startLocation(startLocation), endLocation(endLocation), date(date) {
        seats.resize(2, std::vector<bool>(4, true));  // Initialize all seats as available
    }

    bool bookSeat(int coach, int seat) {
        if (coach < 1 || coach > 2 || seat < 1 || seat > 4) {
            std::cout << "Invalid coach or seat number!\n";
            return false;
        }
        if (!seats[coach - 1][seat - 1]) {
            std::cout << "Seat already booked!\n";
            return false;
        }
        seats[coach - 1][seat - 1] = false;  // Mark seat as booked
        return true;
    }

    double calculateTicketCost() const {
        // Calculate ticket cost based on distance (Euclidean or Manhattan distance)
        // You can implement your own calculation logic here
        double distance = calculateDistance(startLocation, endLocation);
        return distance * 10.0;  // Assuming $10 per unit distance
    }

    const std::string& getStartLocation() const {
        return startLocation;
    }

    const std::string& getEndLocation() const {
        return endLocation;
    }

    const std::string& getDate() const {
        return date;
    }

private:
    double calculateDistance(const std::string& loc1, const std::string& loc2) const {
        // Implement your own distance calculation logic here
        // Example: Euclidean distance between two points (x1, y1) and (x2, y2)
        // double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
        // Return the calculated distance
    }
};

void Passenger::bookTicket(const std::string& startLocation, const std::string& endLocation, const std::string& date) {
    Train train(startLocation, endLocation, date);
    double ticketCost = train.calculateTicketCost();
    std::cout << "Ticket cost: $" << ticketCost << std::endl;

    int coach, seat;
    std::cout << "Enter coach number (1 or 2): ";
    std::cin >> coach;
    std::cout << "Enter seat number (1-4): ";
    std::cin >> seat;

    bool booked = train.bookSeat(coach, seat);
    if (booked) {
        std::cout << "Ticket booked successfully!\n";
        // Create and assign the ticket to the passenger here
    } else { std::cout << "Ticket booking failed!\n";
    }
}

int main() {
    // Sample usage of the Train Booking System
    Passenger passenger("John Doe", "john123", "password");

    // Login or signup logic goes here

    std::string startLocation, endLocation, date;
    std::cout << "Enter start location: ";
    std::cin >> startLocation;
    std::cout << "Enter end location: ";
    std::cin >> endLocation;
    std::cout << "Enter date: ";
    std::cin >> date;

    passenger.bookTicket(startLocation, endLocation, date);

    return 0;
}