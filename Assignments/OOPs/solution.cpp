#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
class passenger;
class train;

class city {
    string cityN;
    int xcrd;
    int ycrd;

public:
    city(string cityN, int xcrd, int ycrd)
        : cityN(cityN), xcrd(xcrd), ycrd(ycrd) {}

    string getcityname() const {
        return cityN;
    }

    int getXcrd() const {
        return xcrd;
    }

    int getYCrd() const {
        return ycrd;
    }
};

class ticket {
    string begcity;
    string destcity;
    string date;
    int cost;
    int coachno;
    int seatno;

public:
    Ticket(string begcity, string destcity, string date, int cost, int coachno, int seatno)
        : begcity(begcity), destcity(destcity), date(date),
          cost(cost), coachno(coachno), seatno(seatno) {}

    void printTicket() const {
        cout << "Beginning City: " << begcity << endl;
        cout << "Destination City: " << destcity << endl;
        cout << "Date: " << date << endl;
        cout << "Cost of Ticket: Rs. " << cost << endl;
        cout << "Coach No.: " << coachno << endl << "Seat No.: " << seatno << endl;
    }
};

class Passenger {
    string name;
    string username;
    string password;

public:
    Passenger(string name, string username, string password)
        : name(name), username(username), password(password) {}

    string getusername() const {
        return username;
    }

    string getpassword() const {
        return password;
    }

    Ticket bookTicket(const Train& train, const string& date);
};

class Train {
    City start;
    City end;
    string date;
    vector<pair<int, int>> bookedTickets;

public:
    Train(const City& start, const City& end, string date, const vector<pair<int, int>>& bookedTickets)
        : start(start), end(end), date(date), bookedTickets(bookedTickets) {}

    const City& getscity() const {
        return start;
    }

    const City& getecity() const {
        return end;
    }

    const string& getDate() const {
        return date;
    }

    const vector<pair<int, int>>& getBookedTickets() const {
        return bookedTickets;
    }

    bool isticketavial(int coachNo, int seatNo) const;
    void bookPassengerTicket(int coachNo, int seatNo);
};

Ticket Passenger::bookTicket(const Train& train, const string& date) {
    if (date == train.getdate()) {
        cout << "Sorry, the ticket cannot be booked on the same date as the journey." << endl;
        return Ticket("", "", "", 0, 0, 0);
    }

    const City& startcity = train.getscity();
    const City& endcity = train.getecity();
    int cost = abs(startcity.getXCrd() - endcity.getXCrd()) +
               abs(startcity.getYCrd() - endcity.getYCrd());

    const vector<pair<int, int>>& bookedTickets = train.getBookedTickets();
    int coachNo = 0;
    int seatNo = 0;

    // checking if ticket is aviable coach and seats are in my control i am taking 2 coach and 4 seats in each of them

    for (int c = 1; c <= 2; c++) {
        for (int s = 1; s <= 4; s++) {
            bool isTicketBooked = false;
            for (const auto& ticket : bookedTickets) {
                if (c == ticket.first && s == ticket.second) {
                    isTicketBooked = true;
                    break;
                }
            }
            if (!isTicketBooked) {
                coachno = c;
                seatno = s;
                break;
            }
        }
        if (coachno > 0 && seatno > 0) {
            break;
        }
    }

    if (coachno == 0 || seatno == 0) {
        cout << "Sorry, no seats available." << endl;
        // returning an empty tickets as no tickets are aviable
        return Ticket("", "", "", 0, 0, 0);
    }

    // Booking ticket
    Train& mtrain = const_cast<Train&>(train);
    mtrain.bookPassengerTicket(coachNo, seatNo);
    return Ticket(startcity.getcityname(), endcity.getcityname(), date, cost, coachno, seatno);
}

bool Train::isTicketAvailable(int coachNo, int seatNo) const {
    for (const auto& ticket : bookedTickets) {
        if (coachno == ticket.first && seatno == ticket.second) {
            return false;
        }
    }
    return true;
}

void Train::bookPassengerTicket(int coachno, int seatno) {
    bookedTickets.push_back(make_pair(coachno, seatno));
}

int main() {
    cout << "Welcome to IRCTC!" << endl;

    // make passengers
    vector<Passenger> passengers;
    passengers.emplace_back("atulya", "e", "11");

    // make cities with random coordinates just to know where you are marking
    city kanpur("Kanpur", 10, 10);
    

    // Create trains with the seats and coach you can also atumate this 
    Train t1(kanpur, jaipur, "1st May", { {1, 1}, {1, 2}, {1, 3}, {1, 4}, {2, 1}, {2, 2}, {2, 3}, {2, 4} });

    vector<Train> trains = { t1 };

    int choice;
    cout << "For new user, press 1. For existing user, press 2." << endl;
    cin >> choice;

    if (choice == 1) {
        string name, username, password;
        cout << "Enter Name, Username, and Password: ";
        cin >> name >> username >> password;
        passengers.emplace_back(name, username, password);
        cout << "User successfully registered!" << endl;
    } else if (choice == 2) {
        string username, password;
        cout << "Enter Username and Password: ";
        cin >> username >> password;
        bool loggedIn = false;
        Passenger* loggedInPassenger = nullptr;
        for (auto& passenger : passengers) {
            if (passenger.getusername() == username && passenger.getpassword() == password) {
                loggedIn = true;
                loggedInPassenger = &passenger;
                break;
            }
        }
        if (loggedIn) {
            cout << "Logged in as passenger " << loggedInPassenger->getusername() << endl;

            //  available trains
            cout << "available trains:" << endl;
            for (const auto& train : trains) {
                cout << train.getscity().getcityname() << " to " << train.getecity().getcityname()
                     << " on " << train.getDate() << endl;
            }

            // booking
            string startcity, endcity, date;
            cout << "Enter Start city, End city, and Date (e.g., Kanpur Jaipur 1st May): ";
            cin >> startcity >> endcity >> date;

            Train* selectedTrain = nullptr;
            for (auto& train : trains) {
                if (train.getscity().getcityname() == startcity &&
                    train.getecity().getcityname() == endcity &&
                    train.getDate() == date) {
                    selectedTrain = &train;
                    break;
                }
            }

            if (selectedTrain) {
                Ticket ticket = loggedInPassenger->bookTicket(*selectedTrain, date);
                if (ticket.getbeg() != "") {
                    cout << "Ticket successfully booked!" << endl;
                    ticket.printTicket();
                }
            } else {
                cout << "No matching train found." << endl;
            }
        } else {
            cout << "Invalid username or password." << endl;
        }
    } else {
        cout << "Invalid choice." << endl;
    } return 0;}
    
