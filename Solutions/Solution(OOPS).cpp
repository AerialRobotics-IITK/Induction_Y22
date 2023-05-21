#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Station {
private:
    int x;
    int y;
    std::string name;

public:
    Station(int x, int y,  std::string& stationName)
        : x(x), y(y), name(stationName) {}

    std::string getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
};

class Ticket {
private:
    Station Initial;
    Station Final;
    std::string date;
    int cost;

public:
    int TicketID;

    Ticket(const Station& Initial, const Station& Final, const std::string& date)
        : Initial(Initial), Final(Final), date(date), cost(Initial.getX() + Initial.getY() - Final.getX() - Final.getY()) {}

    void displayTicket() const {
        std::cout << "From " << Initial.getName() << " to " << Final.getName() << " on " << date << std::endl;
        std::cout << "Cost = " << cost << " Ticket ID " << TicketID << std::endl;
    }
};

class User {
private:
    std::string name;
    std::string username;
    std::string passcode;

public:
    std::vector<Ticket> tickets;

    User(const std::string& name, const std::string& username, const std::string& passcode = "")
        : name(name), username(username), passcode(passcode) {}

    void addTicket(const Ticket& addressTicket) {
        tickets.push_back(addressTicket);
    }

    std::string getName() const {
        return name;
    }

    std::string getUsername() const {
        return username;
    }

    bool verifyPass(const std::string& inUser, const std::string& inPass) const {
        return (username == inUser && passcode == inPass);
    }

    void displayBookedTickets() const {
        std::cout << "List of booked tickets for user: " << getName() << std::endl;
        for (const auto& ticket : tickets) {
            ticket.displayTicket();
            std::cout << std::endl;
        }
    }

    void bookTicket() {
        std::string fromStation, toStation, date;
        int x1, x2, y1, y2;
        std::cout << "Enter the Code of the source station: ";
        std::getline(std::cin, fromStation);
        std::cout << "Enter the coordinates of the source station in the form (x,y): ";
        scanf("(%d,%d)", &x1, &y1);
        std::cout << "Enter the Code of the destination station: ";
        std::getline(std::cin, toStation);
        std::cout << "Enter the coordinates of the destination station in the form (x,y): ";
        scanf("(%d,%d)", &x2, &y2);
        std::cout << "Enter the date of the journey (YYYY-MM-DD): ";
        std::getline(std::cin, date);

        Station source(x1, y1, fromStation);
        Station destination(x2, y2, toStation);
        Ticket newTicket(source, destination, date);
        newTicket.TicketID = tickets.size() + 1;
        addTicket(newTicket);

        std::cout << "Ticket booked successfully!" << std::endl;
    }
};

class Train {
private:
    int coaches;
    int berthsPerCoach;
    std::vector<Ticket> bookedTickets;

public:
    void set(int Coaches, int BerthsPerCoach) {
        coaches = Coaches;
        berthsPerCoach = BerthsPerCoach;
    }
    int getAvailableSeats() const {
        return coaches * berthsPerCoach;
    }

    bool bookTicket() {
        if (getAvailableSeats() > 0) {
            coaches--;
            return true;
        }
        return false;
    }

    void printAllTickets() const {
        std::cout << "List of booked tickets for this train:" << std::endl;
        for (const auto& ticket : bookedTickets) {
            ticket.displayTicket();
            std::cout << std::endl;
        }
    }

    void addBookedTicket(const Ticket& ticket) {
        bookedTickets.push_back(ticket);
    }
};

class TrainSchedule {
private:
    std::unordered_map<std::string, Train> trains;

public:
    void addTrain(const std::string& date, const Train& train) {
        trains[date] = train;
    }

    Train* getTrains(std::string date){
        return &(trains[date]);
    }

    std::unordered_map<std::string, Train>& getTrains() {
        return trains;
    }
};

class Passenger : public User {
private:
    int passengerID;

public:
    Passenger(const std::string& name, const std::string& username, const std::string& passcode = "")
        : User(name, username, passcode), passengerID(0) {}

    void getID() const {
        std::cout << "Passenger ID is " << passengerID << std::endl;
    }
};

class Admin {
private:
    std::string adminID;
    std::string adminPassword;

public:
    Admin(const std::string& id, const std::string& password)
        : adminID(id), adminPassword(password) {
    }

    bool authenticate(const std::string& id, const std::string& password) {
        return (id == adminID && password == adminPassword);
    }

    void printAllTickets(TrainSchedule& trainSchedule) {
        for (auto& trainPair : trainSchedule.getTrains()) {
            Train& train = trainPair.second;
            train.printAllTickets();
        }
    }
};

int main() {

    std::vector<Passenger> passengers;
    TrainSchedule trainSchedule;
    std::string input;
    // Admin details
    std::string adminID = "admin123";
    std::string adminPassword = "password123";
    Admin admin(adminID, adminPassword);
    // Adding sample trains to the schedule
    Train train1;
    train1.set(2, 4);
    Train train2;
    train2.set(2, 4);
    trainSchedule.addTrain("2023-05-21", train1);
    trainSchedule.addTrain("2023-05-22", train2);
    //Prepopulating

    while (true) {
        std::cout << "1. Passenger Login" << std::endl;
        std::cout << "2. Sign Up as a new Passenger" << std::endl;
        std::cout << "3. List Passengers" << std::endl;
        std::cout << "4. Admin Login" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::getline(std::cin, input);

        if (input == "1") {
            // Code for passenger login
            std::cout << "Enter your username: ";
            std::getline(std::cin, input);

            auto passenger = passengers.begin();
            bool found = 0;
            for(; passenger != passengers.end(); passenger++)
                if( passenger->getUsername() == input ) {
                    found = 1;
                    break;
                }
            

            if (found == 1) {
                std::cout << "Enter your password: ";
                std::getline(std::cin, input);
                if (passenger->verifyPass(passenger->getUsername(), input)) {
        std::cout << "Welcome, " << passenger->getName() << "!" << std::endl;
        while (true) {
                    std::cout << "1. View booked tickets" << std::endl;
                    std::cout << "2. Book a new ticket" << std::endl;
                    std::cout << "3. Logout" << std::endl;
                    std::cout << "Enter your choice: ";
                    std::getline(std::cin, input);

                    if (input == "1") {
                        passenger->displayBookedTickets();
                    } else if (input == "2") {
                        std::cout << "Enter the date of the journey (YYYY-MM-DD): ";
                        std::getline(std::cin, input);
                        Train* train = trainSchedule.getTrains(input);
                        if (train) {
                            if (train->bookTicket()) {
                                passenger->bookTicket();
                                std::cout << "Ticket booked successfully!" << std::endl;
                            } else {
                                std::cout << "No seats available on the selected date." << std::endl;
                            }
                        } else {
                            std::cout << "No train available on the selected date." << std::endl;
                        }
                    } else if (input == "3") {
                        std::cout << "Logged out successfully." << std::endl;
                        break;
                    } else {
                        std::cout << "Invalid choice. Please try again." << std::endl;
                    }
                }
            } else {
                std::cout << "Invalid password" << std::endl;
            }
        }
            else {
                std::cout << "Passenger not found." << std::endl;
            }
        } else if (input == "2") {
            std::string name, username, passcode;
            std::cout << "Enter your name: ";
            std::getline(std::cin, name);
            std::cout << "Enter a username: ";
            std::getline(std::cin, username);
            std::cout << "Enter a passcode: ";
            std::getline(std::cin, passcode);

            passengers.emplace_back(name, username, passcode);
            std::cout << "Passenger created successfully!" << std::endl;
        }
        else if (input == "3") {
            std::cout << "List of passengers:" << std::endl;
            for ( auto& passenger : passengers) {
                std::cout << "- " << passenger.getName() << std::endl;
            }
        } else if (input == "4") {
            std::string adminID, adminPassword;
            std::cout << "Enter Admin ID: ";
            std::getline(std::cin, adminID);
            std::cout << "Enter Admin Password: ";
            std::getline(std::cin, adminPassword);

            if (admin.authenticate(adminID, adminPassword)) {
                admin.printAllTickets(trainSchedule);
            } else {
                std::cout << "Invalid Admin ID or Password. Access Denied!" << std::endl;
            }
        } else if (input == "5") {
            break;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}