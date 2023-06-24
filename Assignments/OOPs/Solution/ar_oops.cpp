#include<bits/stdc++.h>
using namespace std;

class User{
    private:
        string Username;
        string Password;
        string list_of_tickets;
        string Name;

    public:
        void setusername(string username){
            Username = username;
        }
        void setname(string name){
            Name = name;
        }
        void setpassword(string password){
            Password = password;
        }
        void getUsername(){
            cout << Username << endl;
        }
        void getName(){
            cout << Name << endl;
        }
        string getPassword(){
            return Password;
        }
};

class Ticket{
    public:
        string Start_City;
        string Destination;
        string Date;

        int getCost(){
            return Cost;
        }

        void ViewTicket(){
            cout << Start_City<<endl;
            cout << Destination<<endl;
            cout << Date<<endl;
            cout << getCost();
            cout << "\n";
        }

        void setCost(int cost){
            Cost = cost;
        }

        bool isDateBooked(const string& username, const string& date) const {
            auto it = bookedDates.find(username);
            if (it != bookedDates.end()) {
                const set<string>& bookedDatesForUser = it->second;
                return bookedDatesForUser.find(date) != bookedDatesForUser.end();
            }
            return false;
        }

        void bookTicket(const string& username, const string& date) {
            bookedDates[username].insert(date);
        }

    private:
        int Cost;
        map<string, set<string>> bookedDates;

};

class City {
    private:
        string name;
        int xCoordinate;
        int yCoordinate;

    public:
        City(const string& cityName, int x, int y) {
            name = cityName;
            xCoordinate = x;
            yCoordinate = y;
        }

        string getName() const {
            return name;
        }

        int getXCoordinate() const {
            return xCoordinate;
        }

        int getYCoordinate() const {
            return yCoordinate;
        }
};

class Travel{
    public:

};

/*class Station{
    public:
        string Name;
        int x_coordinate;
        int y_coordinate;

        void getCoordinate(){
            cout << Name<<endl;
            cout << "(" <<x_coordinate<<","<<y_coordinate<<")";
        }

        friend istream& operator>>(istream& input, Station& obj) {
        input >> obj.x_coordinate;
        return input;
    }
};*/

class Passenger: public User{
    private:
        int passengerID;

    public:
        int getpassengerID(){
            return passengerID;
        }
};

class Ticket_Collector{
    private:
        int employee_id;

    public:
        int getemployeeID(){
            return employee_id;
        }

};


vector<string> Username_list;
vector<string> Password_list;

bool checkname(string name){
    for (int i =0; i< name.length(); i++){
        if ((name[i] >= 'a' && name[i]<='z') || (name[i]>='A' && name[i]<='Z') || name[i]==' '){
            continue;
        }
        else{
            return false;
            break;
        }
    }
    return true;
}

float calc_cost(int x1 ,int y1, int x2, int y2){
    float cost;
    cost = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    cost = round(cost * 100) / 100;
    return cost;
}

bool checkusername(string username){
    for (int i =0; i< username.length(); i++){
        if ((username[i] >= 'a' && username[i]<='z') || (username[i]>='A' && username[i]<='Z') || (username[i]>='0' && username[i]<='9')){
            continue;
        }
        else{
            return false;
            break;
        }
    }
    return true;
}

int check_user_pass(vector<string> v, string K, vector<string> x, string M)
{
    auto it = find(v.begin(), v.end(), K);
    int index;

    if (it != v.end())
    {
        index = it - v.begin();
    }

    else {
        index = -1 ;
    }

    if(index == -1){
        return -1;
    }
    else if(x[index] == M){
        return 1;
    }
    else{
        return 0;
    }
}
/*
int generateRandomSeat() {
    return rand() % 30 + 1;
}

char generateRandomCoach() {
    char coachLetters[] = {'A', 'B'};
    return coachLetters[rand() % 2];
}

bool assignSeat(set<string>& bookedSeats, vector<string>& passengers, string passengerName, string date) {
    // Check if all seats are booked
    if (bookedSeats.size() == 240) {
        cout << "Sorry, all seats are booked for this date." << endl;
        return false;
    }

    // Generate a random seat and coach
    char coach = generateRandomCoach();
    int seat = generateRandomSeat();

    // Check if the seat is already booked
    string seatKey = coach + to_string(seat) + "_" + date;
    if (bookedSeats.find(seatKey) != bookedSeats.end()) {
        // Seat is already booked, try again
        return assignSeat(bookedSeats, passengers, passengerName, date);
    }

    // Assign the seat to the passenger
    passengers.push_back(passengerName);
    bookedSeats.insert(seatKey);
    cout << "Seat assigned to " << passengerName << ": Coach " << coach << ", Seat " << seat << ", Date " << date << endl;
    return true;
}
*/

string generateSeatAssignment() {
    char coach = 'A' + rand() % 2;
    int seat = 1 + rand() % 30;
    return string(1, coach) + "-" + to_string(seat);
}

bool areAllSeatsBooked(const set<string>& bookedSeats) {
    return bookedSeats.size() == 2 * 30;
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(int day, int month, int year) {
    if (year < 0 || month < 1 || month > 12 || day < 1)
        return false;

    const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDay = daysInMonth[month - 1];

    if (month == 2 && isLeapYear(year))
        maxDay++;

    return day <= maxDay;
}

int main(){

    srand(time(0));

    Username_list.push_back("san23");
    Password_list.push_back("pass");

    Passenger Sanskar;
    Sanskar.setname("Sanskar Yaduka");
    Sanskar.setusername("Sanskar1234");
    Sanskar.setpassword("my train");

    Passenger Aman;
    Aman.setname("Aman Singh Gill");
    Aman.setusername("Amangill23");
    Aman.setpassword("gill gill");

    Passenger Dhruv;
    Dhruv.setname("Dhruv Mittal");
    Dhruv.setusername("Dhruv22");
    Dhruv.setpassword("password");

    Passenger Anmoldeep;
    Anmoldeep.setname("Anmoldeep Singh Dhillon");
    Anmoldeep.setusername("Anmoldeepdhillon8888");
    Anmoldeep.setpassword("pass123");

    City Kanpur("Kanpur",10,50);

    City Delhi("Delhi",30,40);

    City Mumbai("Mumbai",80,60);

    City Lucknow("Lucknow",70,70);
   /* Lucknow.Name = "Lucknow";
    Lucknow.x_coordinate = 70;
    Lucknow.y_coordinate = 70;*/

    vector<City> cities;
    cities.push_back(Kanpur);
    cities.push_back(Delhi);
    cities.push_back(Mumbai);
    cities.push_back(Lucknow);

    set<string> bookedSeats;

    Ticket ticket;

    vector<string> passengers;

    label1:
    cout<<"\n";
    string username;
   /*string password;*/
    cout << "Login by entering Username and Password"<<endl;
    cout << "If you are a new user, sign up by typing 0 in username "<<endl;
    cout << "Enter login Username: ";
    getline(cin,username);
    /*cout << "Enter login Password: ";
    getline(cin,password);*/

    if (username == "0" /*&& password == "0"*/){
        label2:
        cout <<"Enter your Name, Username and Password for sign up."<<endl;
       /* cout << "The first letter of the Name and Username must be capital."<<endl;*/
        cout << "Enter Name: ";
        string name;
        getline(cin,name);
        if (checkname(name)){
            Passenger passenger_1;
            passenger_1.setname(name);
            label3:
            cout << "Enter Username: ";
            string newuser;
            getline(cin,newuser);
            if (checkusername(newuser)){
                if(find(Username_list.begin(),Username_list.end(),newuser) != Username_list.end()){
                    cout<< "Username alreday exist."<<endl;
                    goto label1;
                }
                else{
                    passenger_1.setusername(newuser);
                    Username_list.push_back(newuser);
                    label4:
                    cout << "Enter Password: ";
                    string password;
                    cin.ignore();
                    getline(cin,password);
                    if (password.empty()){
                        cout << "Password Cannot be Empty." <<endl;
                        goto label4;
                    }
                    else{
                        passenger_1.setpassword(password);
                        Password_list.push_back(password);
                        system("cls");
                        goto label1;
                    }
                }
            }
            else{
                cout << "Invalid Useranme." <<endl;
                goto label3;
            }
        }
        else{
            cout << "Invalid Name." <<endl;
            goto label2;
        }
    }
    else if (checkusername(username)){
        label6:
        cout << "Enter Password: ";
        string password;
        cin.ignore();
        getline(cin,password);
        if (password.empty()){
            cout << "Password Cannot be Empty." <<endl;
            goto label6;
        }
        else if(check_user_pass(Username_list,username,Password_list,password)==-1){
            cout << "Username doesn't exist."<<endl;
            goto label1;
        }
        else if(check_user_pass(Username_list,username,Password_list,password)==0){
            cout << "Incorrect Password."<<endl;
            goto label1;
        }
        else if(check_user_pass(Username_list,username,Password_list,password)==1){
            string start_location;
            string final_location;
            label10:
            cout<<"\n";
            cout << "Welcome to ticket booking platform."<<endl;
            label7:
            cout << "Enter Starting location : ";
            cin >> start_location;
            /*if(find(cities.begin(),cities.end(),start_location) != cities.end()){
                cout << "Enter Final location : ";
                cin >> final_location;
                if(find(cities.begin(),cities.end(),final_location) != cities.end()){
                    cout<<"d";
                }
            }*/
            bool found_1 = false;
            for (const auto& city_1 : cities) {
                if (city_1.getName() == start_location) {
                    int x1, y1;
                    x1 = city_1.getXCoordinate();
                    y1 = city_1.getYCoordinate();
                    label8 :
                    cout <<"Enter final location : ";
                    cin >> final_location;
                    cin.ignore();

                    bool found_2 = false;

                    for (const auto& city_2 : cities) {
                        if (city_2.getName() == final_location){
                            int x2, y2;
                            x2 = city_2.getXCoordinate();
                            y2 = city_2.getYCoordinate();
                            label9 :
                            cout << "Enter the date of travel (DD/MM/YY): ";
                            string date;
                            getline(cin, date);
                            stringstream ss(date);
                            int day, month, year;
                            char slash1, slash2;

                            if (ss >> day >> slash1 >> month >> slash2 >> year && slash1 == '/' && slash2 == '/' && isValidDate(day, month, year)) {
                                if (ticket.isDateBooked(username, date)) {
                                    cout <<"You have already booked a ticket on that date."<<endl;
                                    goto label11;
                                }
                                else if (areAllSeatsBooked(bookedSeats)) {
                                    cout << "Sorry, all seats are booked on the specified date." << endl;
                                    label11:
                                    cout << "Do you want to book another ticket? (y/n): ";
                                    char choice;
                                    cin >> choice;

                                    choice = tolower(choice);

                                    if(choice == 'n'){
                                        goto exit;
                                    }
                                    else if(choice == 'y'){
                                        goto label10;
                                    }
                                    else{
                                        cout << "Enter a valid choice."<<endl;
                                        goto label11;
                                    }

                                }
                                else {
                                    string assignedSeat;
                                    while (true) {
                                        assignedSeat = generateSeatAssignment();
                                        if (bookedSeats.count(assignedSeat) == 0) {
                                            bookedSeats.insert(assignedSeat);
                                            break;
                                        }
                                    }

                                    cout << "Seat assigned: " << assignedSeat << " on " << date << endl;
                                    cout<< "The cost of the ticket is: ";
                                    cout << calc_cost(x1,y1,x2,y2);
                                    ticket.bookTicket(username, date);
                                    cout<<"\n";
                                    goto label11;
                                    found_2 = true;
                                    break;
                                        }
                            }
                            else {
                                cout << "Date is invalid." << endl;
                                goto label9;
                            }
                        }
                    }
                    if (!found_2) {
                        cout << "Invalid Location." <<endl;
                        goto label8;
                    }

                    found_1 = true;
                    break;
                }
            }

            if (!found_1) {
                cout << "City not found." << endl;
                goto label7;
            }


        }

    }

    else{
        cout << "Invalid Useranme." <<endl;
        goto label1;
    }

    exit:
    system("cls");

    cout<<"Do you want to go to login portal?"<<endl;
    char choice;
    cin >> choice;
    if(choice=='y' || choice == 'Y'){
        system("cls");
        goto label1;
    }


    return 0;
}
