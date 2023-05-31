#include<iostream>
#include<string.h>
#include<math.h>
#include<vector>
#include <utility>
#include <ctime>
using namespace std;
long long total_User=0;
struct Date{
    int day;int month ;int year;
};

struct Coordinates{
    float x;
    float y;
};

typedef struct Date Date;
typedef struct Coordinates Coordinates;
float calculate_distance(Coordinates c1, Coordinates c2) {
    return pow(pow(c1.x-c2.x, 2)+pow(c1.y-c2.y, 2), 0.5);
}

//Funtion related to dates
//compares which date comes when
bool compare_date(Date d1, Date d2) {
    if( d1.year != d2.year || d1.month != d2.month || d1.day != d2.day )
        return 0;
    return 1;
}
//check if the date is real
bool possible_date(Date booking_Date){
        if( booking_Date.day < 0 || booking_Date.day> 31 || booking_Date.month < 1 || booking_Date.month> 12 || booking_Date.year < 0 ){
            return 0;
        }
        else 
        return 1;

}
//returns the current date
Date current_date(){
    Date current_Date;
    time_t now=time(0);
    tm *local_time = localtime(&now);
    current_Date.year=1900 + local_time->tm_year;
    current_Date.month=1 + local_time->tm_mon;
    current_Date.day= local_time->tm_mday ;
    return current_Date;
}
//check if the booking_Date is after current_Date
bool check_date(Date booking_Date) {
    if(!(possible_date(booking_Date))){
        return 0;
    }
    Date current_Date = current_date();
    if( booking_Date.year < current_Date.year )
        return 0;
    else if( booking_Date.year == current_Date.year )
       { if( booking_Date.month < current_Date.month )
            return 0;
        else if( booking_Date.month == current_Date.month )
            {if( booking_Date.day <= current_Date.day)
                return 0;}}
    return 1;
} 

//Here we begin defining the essential classes

//Station class
class Station{
    public:
        string name;
        Coordinates coordinates;
        string get_name(){
            return name;
        }
        Coordinates get_coordinates(){
            return coordinates;
        }
        void display_name(){
            cout<<name<<endl;
        }
        void display_coordinates(){
            cout<<"("<<coordinates.x<<","<<coordinates.y<<")"<<endl;
        }
        Station(); //default constructor
        Station(string name,Coordinates coordinates);//constructor
};


//Ticket class
class Ticket{
    private:
        float unitcost=10;
        float basecost=20;
    protected:
        Station start,end;
        int coach ,seat;
        Date date;
        float cost;
    public:
        pair<pair<string,string>, Date> get_travel_detail() { //to find the travel details kahan se kahan and when
            pair<pair<string,string>, Date> journey;
            journey.first.first=start.name;
            journey.first.second=end.name;

            journey.second = date;
            return journey;
        }
        void display_travel_detail() { //to DISPLAY the travel details kahan se kahan and when
            cout<<"date of travelling "<<date.day<<'/'<<date.month<<'/'<<date.year<<endl;
            cout<<"departure :"<<start.name<<endl;
            cout<<"destination :"<<end.name<<endl;
        }
        void display_ticket(){
            cout<<"Departure station "<<start.name<<endl;
            cout<<"Destination station "<<end.name<<endl;
            cout<<"Date: "<<date.day<<"/"<<date.month<<"/"<<date.year<<endl;
            cout<<"Coach "<<coach<<endl;
            cout<<"Seat no. "<<seat<<endl;
            cout<<"Cost of ticket "<<cost<<endl;
        }
        pair<int,int> get_coach_seat(){
            // aage use aayega user class mai in search method
            pair<int, int> coachseat;
            coachseat.first=coach;
            coachseat.second=seat;
            return coachseat;
        }
        void display_coach_seat(){
            cout<<"Coach no. "<<coach<<endl;
            cout<<"Seat no. "<<seat<<endl;
        }
        Ticket();
        Ticket(string start,string end,Date date,int coach,int seat);

};
//Travel class
class Travel{
    public:
        string start,end;
        Date date;
        vector<pair<string,int> > passenger_list;//yahan pehle mai passenger and second mai coach no. hai
        Station start_station,end_station;
        void display_passenger_list(){
            for(int i=0;i<passenger_list.size();i++){
                cout<<"Passenger name "<<passenger_list[i].first<<"   ";
                cout<<"Passenger coach"<<passenger_list[i].second<<endl;
            }
        }
        void display_journey(){
            cout<<"Starting station:  "<<start_station.coordinates.x<<" , "<<start_station.coordinates.y<<endl;
            cout<<"Final station:  "<<end_station.coordinates.x<<" , "<<end_station.coordinates.y<<endl;
            cout<<"Date of journey "<<date.day<<'/'<<date.month<<'/'<<date.year<<endl;
            //work under progress 


        }
        bool check_ticket(){
            if(passenger_list.size()<8){
                return true;
            }
            else{
                return false;
            }
        }
        int number_passenger(){
            return passenger_list.size();
        }
        Travel();
        Travel(string start,string end,Date date);
};


//User class
class User{
    protected:
        string username,password;
        long long int id;
    public:
        string name;
        vector<Ticket>ticket_his;
        string get_username(){
            return username;
        }
        string get_name(){
            return name;
        }
        string get_password(){
            return password;
        }
        void display_ticket(){
            for (int i=0;i<ticket_his.size();i++){
                cout<<"Ticket no."<<i<<endl;
                ticket_his[i].display_ticket();
            }
        }
        void search_ticket(string start, string end, Date date) {
            int flag=0; 
            for(auto itr= ticket_his.begin(); itr != ticket_his.end(); itr++){
                pair<pair<string,string>, Date> journey = itr->get_travel_detail();
                if( journey.first.first == start && journey.first.second == end && compare_date(journey.second, date) == 1 )
                    flag=1; 
                    itr->display_coach_seat();
                 
            }

            if(flag==0){
                cout<<"Ticket not found"<<endl;
                return ;
            }
        }
        
        bool Verify_password(string Password){
            if(password!=Password){
                return false;
            }
            else{
                return true;
            }
        }
        User();
        User(string username,string password,string name,long long int id);
};

//Passenger class
class Passenger:public User{
    public:
        long long get_passenger_id() {
            return User::id;}
         bool book_ticket(string start, string end,Date date){
            int coach,seat;
            Travel travel(start,end,date);
            if(travel.check_ticket()){
                if(travel.number_passenger()>4){
                    coach=1;
                    seat=travel.number_passenger()-4;
                }
                else{
                    coach=0;
                    seat=travel.number_passenger();
                }
                Ticket ticket(start, end, date, coach, seat);
                User::ticket_his.push_back(ticket);
                return 1;
                //travel.passenger_list.push_back(Passenger);//check karr iska sahi syntax

            }
            else{
                //cout<<"Sorry no tickets are available"<<endl;
                return 0;
            }


         }
     Passenger(string username,string password,string name,long long int id);
        };

//TC class
class TC: public User{
    private:
        long long employeeid;
    public:
        long long get_employee_id() {
            return employeeid;
        }
        void setEmployeeID(long long ID) {
            employeeid = ID;
        }
        TC(string username,string password,string name,long long int employeeid);

};


vector<Passenger> all_Passenger_list;
vector<TC> all_Ticket_Collector_list;
vector<Travel> all_Travel_list;
vector<Station> all_Station_list;
void admin_command(){
    string command;
    cout<<"Enter 1 for login"<<endl;
    cout<<"Enter 2 for  signup"<<endl;
    cout<<"Enter 3 to go back to the previous window"<<endl;
    cout<<endl;
    cin>>command;
    if(command=="1"){
        int flag=0;
        string username,password;
        cout<<"Username :";
        cin>>username;
        vector <TC> ::iterator i;
        for ( i=all_Ticket_Collector_list.begin();i!=all_Ticket_Collector_list.end();i++){
            if(i->get_username()==username){
                flag=1;
                break;
            }
        }
        if(flag==0){
            cout<<"Username not found"<<endl;
            return;
        }
        else{
            cout<<endl;
            cout<<"Password :";
            cin>>password;
            cout<<endl;
            if(i->get_password()!=password){
                cout<<"Incorrect password"<<endl;
                return;
            }
            else{
                int cmd=0;
                cout<<"Enter 1 to show passenger"<<endl;
                cout<<"Enter 2 to show passenger detail"<<endl;
                cout<<"Enter 3 to show travel detail"<<endl;
                cout<<"Enter 4 to add a station"<<endl;
                cout<<"Enter 5 to show station details"<<endl;
                cout<<"Enter 6 to show stations"<<endl;
                cout<<"Enter 7 to logout"<<endl;
                cin>>cmd;
                
               {     if(cmd==1){
                        
                        for( auto i =all_Passenger_list.begin();i!=all_Passenger_list.end();i++){
                            cout<<i->get_name()<<endl;
                        }
                        return;
                }
                    if(cmd==2){
                        string passenger_name;
                        cout<<"Please passenger's name :";
                        cin>>passenger_name;
                        vector<Passenger> ::iterator i;
                        for( i =all_Passenger_list.begin();i!=all_Passenger_list.end();i++){
                            if(i->get_name()==passenger_name){
                                break;
                            }
                        }   
                        cout<<"Name of the passenger"<<passenger_name<<endl;
                        cout<<"Username of the passenger"<<i->get_username()<<endl;
                        cout<<"ID of the passenger"<<i->get_passenger_id()<<endl;
                        return;
                    }
                    if(cmd==3){
                        
                        for ( auto i=all_Travel_list.begin();i!=all_Travel_list.end();i++){
                            i->display_journey();
                            i->display_passenger_list();
                        }
                        return;
                    }
                    if(cmd==4){
                        string name;
                        Coordinates coordinates;
                        cout<<"Enter the name of the station";
                        cin>>name;
                        cout<<"Enter the Coordinates of station (x,y)  :";
                        cin>>coordinates.x>>coordinates.y;
                        cout<<endl;
                        Station station(name,coordinates);
                        all_Station_list.push_back(station);
                        return;
                                        }
                    if(cmd==5){
                        string station_name;
                        cout<<"Enter the name of the staion :";
                        cin >>station_name;
                        //vector<Station>::iterator i;
                        for ( auto i=all_Station_list.begin();i!=all_Station_list.end();i++){
                            if(i->get_name()==station_name){
                                i->get_coordinates();
                            }
                        }
                        return;
                    }
                    if(cmd==6){
                        for (auto i=all_Station_list.begin();i!=all_Station_list.end();i++){
                        
                                i->get_coordinates();
                            
                        }
                        return;
                    }
                    if(cmd==7){
                        return;
                    }
                    else{
                        cout<<"ERROR"<<endl;
                        return;
                }
               }
            }

        }

    }

    else if(command=="2"){
        string admin_pass;
        cout<<"Enter Admin Pass: ";
        cin>>admin_pass;
        if( admin_pass != "ADMIN_PASS" ) {//admin passs is ADMIN_PASS
            cout << "Incorrect admin pass" << endl;
            return;
        }
        else{

                string username,password,re_password,name;
    bool flag=1;
    while(flag){
        flag=0;
        cout<<"Enter a username :";
        cin>>username;
        for (auto i=all_Ticket_Collector_list.begin();i!=all_Ticket_Collector_list.end();i++){
            if(i->get_username()==username){
                flag=1;
                cout<<"Please try another username this is already taken"<<endl;
                continue;
            }
        }}
    flag=1;
    while(flag){
        flag=0;
        cout<<"Enter password :";
        cin>>password;
        cout<<endl;
        cout<<"confirm password :";
        cin>>re_password;
        cout<<endl;
        if(password==re_password){
            break;
        }
        else{
            cout<<"Try Again"<<endl;
            flag=1;
        }
    }
    cout<<"Please enter your name :";
    cin>>name;
    TC tc(name,username,password,++total_User);
    all_Ticket_Collector_list.push_back(tc);
    cout<<"Your account is created successfully"<<endl;

    
        }
        
    }
    else{
        return;
    }
}
void passenger_command(){
    string command;
    cout<<"Enter 1 for login"<<endl;
    cout<<"Enter 2 for  signup"<<endl;
    cout<<"Enter 3 to go back to the previous window"<<endl;
    cout<<endl;
    cin>>command;
    if(command=="1"){
        int flag=0;
        string username,password;
        cout<<"Username :";
        cin>>username;
        vector<Passenger>::iterator i;
        for ( i=all_Passenger_list.begin();i!=all_Passenger_list.end();i++){
            if(i->get_username()==username){
                flag=1;
                break;
            }
        }
        if(flag==0){
            cout<<"Username not found"<<endl;
            return;
        }
        else{
            cout<<endl;
            cout<<"Password :";
            cin>>password;
            cout<<endl;
            if(i->get_password()!=password){
                cout<<"Incorrect password"<<endl;
                return;
            }
            else{
                int cmd;
                cout<<"press 1 to book ticker"<<endl;
                cout<<"press 2 to show the Ticket history"<<endl;
                cout<<"press 3 to logout"<<endl;
                cin>>cmd;
                {
                    if(cmd==1){
                        Date booking_Date;
                        string start_station,end_station;
                        cout<<"Enter the date of travel :dd/mm/yyyy :";
                        cin>>booking_Date.day>>booking_Date.month>>booking_Date.year;
                        if(check_date(booking_Date)){
                            int outcome=0;
                            outcome=i->book_ticket(start_station,end_station,booking_Date);
                            if(outcome){
                                cout<<"Ticket booked successfully"<<endl;
                            }
                            else{
                                cout<<"Ticket not Available"<<endl;
                            }
                        }
                        else{
                            cout<<"Invalid Date"<<endl;
                            return;
                        }
                    }
                    else if(cmd==2){
                        cout<<"showing the tickect history:"<<endl;
                        i->display_ticket();
                        return;
                    }
                    else if(cmd==3){
                        cout<<"loging out ...."<<endl;
                        return;
                    }
                    else{
                        cout<<"ERROR"<<endl;
                        return;
                    }
                        
                }
                
            }
        }  
    
    
    }

    else if(command=="2")
{
    string username,password,re_password,name;
    bool flag=1;
    while(flag){
        flag=0;
        cout<<"Enter a username :";
        cin>>username;
        vector<Passenger>::iterator i;
        for ( i=all_Passenger_list.begin();i!=all_Passenger_list.end();i++){
            if(i->get_username()==username){
                flag=1;
                cout<<"Please try another username this is already taken"<<endl;
                continue;
            }
        }
    flag=1;
    while(flag){
        flag=0;
        cout<<"Enter password :";
        cin>>password;
        cout<<endl;
        cout<<"confirm password :";
        cin>>re_password;
        cout<<endl;
        if(password==re_password){
            break;
        }
        else{
            cout<<"Try Again"<<endl;
            flag=1;
        }
    }
    cout<<"Please enter your name :";
    cin>>name;
    Passenger passenger(name,username,password,++total_User);
    all_Passenger_list.push_back(passenger);
    cout<<"Your account is created successfully"<<endl;

    
    }
}
else{
    return;
}
}


int main(){
    string command="";
    cout<< "Railway login"<<endl<<endl;
    cout<<"admin -login / signup"<<endl;
    cout<<"passenger -login / signup"<<endl;
    cout<< "help    exit"<<endl<<endl;
    while(command!="exit"){
        cin>>command;
        if(command=="admin"){
            admin_command();
        }
        else if (command=="passenger"){
            passenger_command();
        }
        else if(command=="help")
        {
            cout << "Commands" << endl;
            cout << "admin     - Administrator Log In/ signup" << endl;
            cout << "passenger - Passenger Log In/ signup" << endl;
            cout << "exit      - exit from the program" << endl << endl;
            
        }
        else if(command!="exit"){
            cout<<"ERROR please try again"<<endl;
        }
        
    }
    

}

