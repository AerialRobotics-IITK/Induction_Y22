#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class city {
    string cityN;
    int xcrd;
    int ycrd;

public:
    void set(string CityN, int Xcrd, int Ycrd) {
        cityN = CityN;
        xcrd = Xcrd;
        ycrd = Ycrd;
    }

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

class Ticket {
    string begcity;
    string destcity;
    string date;
    int cost;
    int coachno;
    int seatno;

public:
    Ticket(string Begcity, string Destcity, string Date, int Cost, int Coachno, int Seatno) {
        begcity = Begcity;
        destcity = Destcity;
        date = Date;
        cost = Cost;
        coachno = Coachno;
        seatno = Seatno;
    }

    void printTicket() const {
        cout << "Beginning City: " << begcity << endl;
        cout << "Destination City: " << destcity << endl;
        cout << "Date: " << date << endl;
        cout << "Cost of Ticket: Rs. " << cost << endl;
        cout << "Coach No.: " << coachno << endl << "Seat No.: " << seatno << endl;
    }
    string getbeg() {
        return begcity;
    }
};

class Train {
    city start;
    city end;
    string date;
    vector<pair<int, int>> bookedTickets;

public:
    Train(const city& Start, const city& End, string Date, const vector<pair<int, int>>& BookedTickets) {
        start = Start;
        end = End;
        date = Date;
        bookedTickets = BookedTickets;
    }

    const city& getscity() const {
        return start;
    }

    const city& getecity() const {
        return end;
    }

    const string& getDate() const {
        return date;
    }

    const vector<pair<int, int>>& getBookedTickets() const {
        return bookedTickets;
    }

    bool isTicketAvailable(int coachNo, int seatNo) const;
    void bookPassengerTicket(int coachNo, int seatNo);
};
class Passenger {
    string name;
    string username;
    string password;

public:
    Passenger(string Name, string Username, string Password) {
        name = Name;
        username = Username;
        password = Password;
    }

    string getusername() const {
        return username;
    }

    string getpassword() const {
        return password;
    }

    Ticket bookTicket(const Train& train, const string& date);
};

Ticket Passenger::bookTicket(const Train& train, const string& date) {
    if (date == train.getDate()) {
        cout << "Sorry, the ticket cannot be booked on the same date as the journey." << endl;
        return Ticket("", "", "", 0, 0, 0);
    }

    const city& startcity = train.getscity();
    const city& endcity = train.getecity();
    int cost = abs(startcity.getXcrd() - endcity.getXcrd()) +
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
                coachNo = c;
                seatNo = s;
                break;
            }
        }
        if (coachNo > 0 && seatNo > 0) {
            break;
        }
    }

    if (coachNo == 0 || seatNo == 0) {
        cout << "Sorry, no seats available." << endl;
        // returning an empty tickets as no tickets are aviable
        return Ticket("", "", "", 0, 0, 0);
    }

    // Booking ticket
    Train& mtrain = const_cast<Train&>(train);
    mtrain.bookPassengerTicket(coachNo, seatNo);
    return Ticket(startcity.getcityname(), endcity.getcityname(), date, cost, coachNo, seatNo);
}

bool Train::isTicketAvailable(int coachNo, int seatNo) const {
    for (const auto& ticket : bookedTickets) {
        if (coachNo == ticket.first && seatNo == ticket.second) {
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
    city kanpur;
    kanpur.set("Kanpur", 10, 10);
    city jaipur;
    jaipur.set("Kanpur", 20, 20);
    

    // Create trains with the seats and coach you can also atumate this 
    Train t1(kanpur, jaipur, "1st May", {{1, 1}, {1, 2}, {1, 3}, {1, 4}, {2, 1}, {2, 2}, {2, 3}, {2, 4}});

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
    

