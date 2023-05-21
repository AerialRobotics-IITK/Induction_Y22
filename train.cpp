#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <cstdlib>



class User{
    public:
    std::string username;
    std::string password;
    std::vector<std::string> ticket_list;
    std::string name;
    //constructor initialization
    User(std::string user ,
        std::string passwrd,
        std::string nm) : 
        username(user), 
        password(passwrd), 
        name(nm) {

        }
    User();
    //public:
    std::string get_username()
    {
        std::cout<<" Enter username";
        std::cin>> username;
    }
    //to check if the user is unique or not
    bool unique_user(const std::string& username) {
    for( const auto& user: list_of_users){
        if(user.username== username){
            return true;
        }
    }
    return false;
}
    //for sign up
    std::vector<User> list_of_users;
    void sign_up() {
    int c=1;
    int choice;
    while(c==1){
    User newUser;
    std::cout<<"Enter your name: ";
    std::cin>> newUser.name;
    std::cout<<"\nEnter a username: ";
    std::cin>>newUser.username;
    if(newUser.unique_user(newUser.username)){
        std::cout<< "Username is Taken.\n If you wish to sign up again press 1\n Else press 0";
        std::cin>> c;
        if (c==0)
        {
            break;
        }
    }
    else{
        std::cout<<"Enter password: ";
        std::cin>>newUser.password;
        std::cout<<"\n";
        newUser.list_of_users.push_back(newUser);
        std::cout<<"You have Signed in\n";
    }

    }


}
    //for login
  void login() {
    std::string username;
    std::string password;
    std::cout<<"Enter your username";
    std::cin>>username;
    std::cout<<"\n Enter Password";
    std::cin>>password;
    for(const auto& user:list_of_users){
        if(user.username==username && user.password==password){
            std::cout<<"You have logged in\n";
        }
    }
    
}

    void view_tickets()
    {
        std::cout<< "Name of the User:"<< name;
        for (auto& it:ticket_list)
        {
            std::cout<< it<<' ';
        }
    }
    bool verify_Password(std::string pwd) 
    {
        return (password == pwd);
    }


//to display registered users
void display_users() {
    std::cout<< "Registered Users are: \n";
    for( auto& user:list_of_users) {
        std::cout<<" Name : "<<user.name;
        std::cout<<"\n";
        std::cout<< "Username : "<<user.username;
        std::cout<<"\n";
    }
    
}
};

bool valid_date(int day, int month, int year){
    int a;
    if (month==1 ||month==3|| month==5||month==7||month==8||month==10||month==12)
    {
        if (day<=31 && day>=1)
        {
            if (year==2023){
                a=1;
            }
        }
    }
    else{
        a=0;
    }
    if(month==4||month==6||month==9||month==11)
    {
        if(day<=30 && day>=1)
        {
            if(year==2023)
            {
                a=1;
            }
            
        }
    }
    else{
        a=0;
    }
    if(month==2)
    {
        if (day>=1 && day<=28)
        {
            if(year==2023)
            {
                a=1;
            }
        }
    }
    else{
        a=0;
    }
    if(a==1)
    {
        return true;
    }
    else{
        return false;
    }
}
int no_of_seats=0;
class Passenger: public User{
    private:
    std::string passenger_ID;
    public:
    //constructor initialization
    Passenger( std::string user,
        std::string passwrd,
        std::string nm,
        std::string pass_ID,
        std::string nam,
        int coa):
    User(user, passwrd, nm),
        passenger_ID(pass_ID){

        }
        Passenger();
    

    std::string get_passenger_ID()
    {
        return passenger_ID;
    }

    void book_ticket()
    {   
        Ticket ticket;
        std::cout<<"Enter the day on which you want to book ticket";
        std::cin>> ticket.day;
        std::cout<<"Enter the month of journey";
        std::cin>>ticket.month;
        std::cout<<"Enter year";
        std::cin>>ticket.year;

        if(valid_date(ticket.day,ticket.month,ticket.year)==true)
        {
          std::cout<<"Enter start station";
          std::cin>>ticket.start_station;
          std::cout<<"\nEnter destination";
          std::cin>>ticket.destination;
          int seats[]={1,2,3,4,5,6,7,8};
          int coaches[]={1,2};
          int i=0;
          while(i<8){
          ticket.seat=seats[i];
          i++;
          break;}
          int j=0;
          while(j<2)
          {
            ticket.coach=coaches[j];
            j++;
            break;
          }
          ticket.view_ticket();
          Station station;
          int ds= station.calculate_distance();
          int cost= 100*ds;
          if(i==8 && j==2)
          {
            std::cout<<"Train is full. Ticket could not be booked";
          }
          else{
            std::cout<<"Ticket has been booked.\n";
            std::cout<<"Cost of the ticket is: "<<cost;
          }
        
        }
    }

};
class Ticket_Collector: public User{
    private:
    std::string employee_ID;
    public:
    Ticket_Collector(std::string user, 
    std::string passwrd,
     std::string nm, 
     std::string empId) : 
     User(user, passwrd, nm), 
     employee_ID(empId) {}

     std::string get_employee_id(){
        return employee_ID;
     }

};

//station and coordinates
class Station {
private:
    std::string name;
    int x_coord_initial;
    int y_coord_initial;
    int x_coord_final;
    int y_coord_final;

public:
    Station(std::string nm, int xi, int yi,int xf,int yf) :
     name(nm), x_coord_initial(xi), y_coord_initial(yi),x_coord_final(xf), y_coord_final(yf) {}
    Station();
    void getCoordinates() {
        std::cout << "Station: " << name ;
        std::cout <<"\n";
        std::cout << "Initial Coordinates:\n " ;
        std::cout<< "x coordinate: "<<x_coord_initial;
        std::cout<<"\n";
        std::cout<<"y coordinate: "<<y_coord_initial<<"\n";
        std::cout << "Final Coordinates:\n " ;
        std::cout<< "x coordinate: "<<x_coord_final;
        std::cout<<"\n";
        std::cout<<"y coordinate: "<<y_coord_final<<"\n";
    }
    int calculate_distance()
    {
       int x=std::abs(x_coord_final - x_coord_initial);
       int  y=std::abs(y_coord_final - y_coord_initial);
       int distance= x+y;
       return distance;
    }
};

std::string coaches() {
    std::array<std::string,8>coaches;
    coaches={"A","B","C","D","E","F","G","H"};
    int i=0;
    std::cout<<"The coach is "<< coaches[i];
    i++;   
    }
int seats(){
   std::array<int,30>seats;
   for(int i=1;i<=30;i++){
        seats[i]=i;
    int j=0;
    std::cout<<"The seat is: "<<seats[i];
    i++;
}}


class Ticket {
    public:
    std::string start_station;
    std::string destination;
    int day;
    int month;
    int year;
    int seat;
    int coach;
    public:
    // constructor initialization
    Ticket(std::string s_station,
    std::string dest,
    int d, int m, int y,
    int st,
    int coa):
    start_station(s_station),
    destination(dest),
    day(d),month(m),year(y),
    seat(st),
    coach(coa) {}
    Ticket();
    Station station;

    int dis= station.calculate_distance();
    int cost=100*dis;
    //methods
    void view_ticket()
    {
        std::cout<< " Start Station: "<< start_station;
        std::cout<< "\n";
        std::cout<< " Destination: " << destination;
        std::cout<< "\n";
        std::cout<< "Day"<<day;
        std::cout<<"\nMonth "<<month;
        std::cout<<"\nYear "<<year;
        std::cout<< "\n";
        std::cout<< "Seat: "<< seat;
        std::cout<< "\n";
        std::cout<< "Coach Number: "<<coach;
        std::cout<< "\n";
        std::cout<< "Cost: "<<cost;
        
    
    }
};

class Travel {
private:
    std::vector<Passenger> list_of_passengers;
    std::string startStation;
    std::string destination;
    std::string date;

public:
    Travel(std::string start, std::string dest, std::string dt) : startStation(start), destination(dest), date(dt) {}
    Travel();
    void viewPassengerList() {
        std::cout << "Passenger List for Travel on " << date << "\n";
        for (Passenger& passenger : list_of_passengers) {
            std::cout <<"User: " <<passenger.get_username();
            std::cout<< " - Passenger ID: " << passenger.get_passenger_ID();
        }
    }

    void viewJourney() {
        std::cout << "Journey Details\n"  ;
        std::cout << "Start Station: " << startStation;
        std::cout<<"\n"; 
        std::cout << "Destination: " << destination ;
        std::cout<<"\n";
        std::cout << "Date: " << date ;
        std::cout<<"\n";
    }

    void addPassenger( Passenger& passenger) {
        list_of_passengers.push_back(passenger);
    }
};
int main()
{
    User newUser;
    while(true)
    {
        std::cout<< " 1: SIGN UP\n";
        std::cout<< "2: LOGIN\n";
        std::cout<<"3:EXIT\n";
        std::cout<<"Enter your choice";

        int c;//choice
        std::cin>>c;
        if(c==1){
             
             newUser.sign_up();
        }
            
        if(c==2){
            newUser.login();
             
            int choice;
            
            std::cout<< "TO VIEW JOURNEY DETAILS PRESS 1";
            std::cin>>choice;
            std::cout<<"\n";
            if(choice==1)
            {   Travel travel;
                travel.viewJourney();
            }
            choice=0;
            std::cout<<"TO BOOK A TICKET PRESS 2";
            std::cin>>choice;
            std::cout<<"\n";
            if(choice==2){
                Passenger passenger;
                passenger.book_ticket();
                std::cout<<"Your coach is: "<<coaches()<<"\n";
                std::cout<<"Your seat is: "<<seats()<<"\n";
            }
            }
            if(c==3){
            break; }
            else{
            
            continue;
        }

    }
}