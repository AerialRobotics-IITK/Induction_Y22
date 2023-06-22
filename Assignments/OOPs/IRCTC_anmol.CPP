#include<iostream>
#include<vector>
#include<fstream>
#include<string.h>
#include<unistd.h>
#include<bits/stdc++.h>
#include<math.h>

using namespace std;     

#define adminID "admin"
#define adminPASS "admin"
string current;
float ticketconst=1;

struct coordinates{
float x;
float y;};

struct date{
    unsigned int d;
    unsigned int m;
    unsigned int y;
};

typedef struct date date;
typedef struct coordinates CRDNTS;


class user {
    protected:
    int log=0;
    protected: 
    string username,password,usr,pass;
    string name;
    public: user(){
        username = '\0';
        password = '\0';
        name[0]= '\0';
    }
    public: void login(){
        cout<<"\t\t\tUSERNAME:";
        cin>>username;
        cout<<"\t\t\tPASSWORD:";
        cin>>password;
        ifstream input("data.txt");
        while(input>>usr>>pass>>name){
            if(usr==username && pass==password){
                log=1;
                system("clear");
                current=username;
            }
        }
        input.close();
        if(log==1){
            cout<<"LOGGED IN SUCCESSFULLY!\n";
            sleep(2);
        }
        else{
            system("clear");
            cout<<"PLEASE ENTER CORRECT CREDENTIALS\n";
            sleep(2);
            login();
        }
    };

    void registration();

    

};

class ticket{
    public:
    int start,dest;
    date traveldate;
    float cost;
    string name;
    string seat;
    ticket(){
        start=0;
        dest=0;
        traveldate.d=0;
        traveldate.m=0;
        traveldate.y=0;

    }

    public: void TravelList(int checkstart,int checkdest, date checkdate){
        int c;
        ifstream input("tickets.txt");
        cout<<"\t\tPassenger list is:\n\n";
        while(input>>name>>start>>dest>>(traveldate.d)>>(traveldate.m)>>(traveldate.y)>>cost>>seat){
            
            if(start==checkstart && dest==checkdest && checkdate.d==traveldate.d && checkdate.m==traveldate.m && checkdate.y==traveldate.y){
                
                cout<<"\t\t"<<name<<" "<<seat<<endl;
                
            }
        }
        cout<<"Press 1 to go back: ";
        cin>>c;
        return ;


    };

    public: int CheckTicket(date checkdate){
    ifstream input("tickets.txt");
        while(input>>name>>start>>dest>>(traveldate.d)>>(traveldate.m)>>(traveldate.y)>>cost>>seat){
            if((name==current) && checkdate.d==traveldate.d && checkdate.m==traveldate.m && checkdate.y==traveldate.y){
                return 1;
            }
        };
        return 0;
    };    
    public: void ViewTicket(string check){
        string c;
        ifstream input("tickets.txt");
        while(input>>name>>start>>dest>>(traveldate.d)>>(traveldate.m)>>(traveldate.y)>>cost>>seat){
            

        if(name==check){
        cout<<"\n\n";
        cout<<"\t\t\tTicket is Under the Name: "<<name<<endl;
        cout<<"\t\t\tStart Station: "<<start<<endl;
        cout<<"\t\t\tDestination Station: "<<dest<<endl;
        cout<<"\t\t\tSeat:"<<seat<<endl;
        cout<<"\t\t\tTravel Date: "<<traveldate.d<<"-"<<traveldate.m<<"-"<<traveldate.y<<endl;
        cout<<"\t\t\tCost:"<<cost<<endl;};}
        input.close();

        cout<<"Press 1 to go back: ";
        cin>>c;

    }
    public: string CheckCountReturnCoach(int checkstart,int checkdest, date checkdate){
        string seat;
        int count=0;
        int startcheck;
        int destcheck;
        ifstream input("tickets.txt");
        date checkdate2;
        while(input>>name>>startcheck>>destcheck>>(checkdate2.d)>>(checkdate2.m)>>(checkdate2.y)>>cost>>seat){
            if((checkstart==startcheck) && (checkdest==destcheck) && (checkdate.d==checkdate2.d) && (checkdate.m==checkdate2.m) && (checkdate.y==checkdate2.y) ){
                if(name==current){
                    return "NO";
                }
                else{
                    count++;
                }
                
            }
        }
        if(0<=count && count<=3){
            seat[0]='A';
            seat[1]=count+1;
            seat[2]='\0';
            return seat;
        }
        else if(3<count && count<=7){
            seat[0]='B';
            seat[1]=count+1;
            seat[2]='\0';
            return seat;
        }
        return "NO";

    }
    
};

class passenger: public user{
    public: passenger(){
        username = '\0';
        password = '\0';
        name[0] = '\0';
    };

    public: void BookTicket();

};



class ticketcollector: public user{
    

    public: void login(){
        cout<<"\t\t\tUSERNAME:";
        cin>>username;
        cout<<"\t\t\tPASSWORD:";
        cin>>password;
        
        if(username==adminID && password==adminPASS){
            cout<<"LOGGED IN AS Ticket Collector\n";
            sleep(2);
            system("clear");
        }
        else{
            cout<<"PLEASE ENTER CORRECT CREDENTIALS\n";
            sleep(2);
            system("clear");
            login();
        }
    };


};

class station{
    private:
        string name;
        CRDNTS position;
        unsigned int ID;
    public:
    CRDNTS getCoordinates(int x) {
            ifstream input("stations.txt");
            while(input>>name>>ID>>position.x>>position.y){
                if(ID==x){
                    return position;
            }
            }}

    station(){
        position.x=0;
        position.y=0;
        name='\0';
        ID=0;
    };         

    public: void stationset(float X,float Y, string NAME, unsigned int id){
        position.x=X;
        position.y=Y;
        name=NAME;
        ID=id;
        ofstream f1("stations.txt", ios::app);
        f1<<name<<" "<<ID<<" "<<position.x<<" "<<position.y<<" "<<endl;
    }
    
};

void public_menu(){
    system("clear");
    int c;
    passenger base;
    ticket booking;
    cout<<"\t\t\t____________________________________________________________\n\n";
    cout<<"\t\t\t                       IRCTC TICKETING                      \n";
    cout<<"\t\t\t____________________________________________________________\n\n";
    cout<<"\t PRESS 1 TO VIEW BOOKING HISTORY\n";
    cout<<"\t PRESS 2 TO BOOK TICKET\n";
    cout<<"\t PRESS 3 TO LOGOUT\n";
    cout<<"\n\t\t Please select from options above\n\n";
    cin>>c;
     
    switch(c){
        case 1:
                booking.ViewTicket(current);
                break;
        case 2: 
                base.BookTicket();
                break;

        case 3:
                return;
                
        default:
                system("clear");
                cout<<"Please enter a valid choice\n\n"<<endl;
                sleep(2);
                public_menu();
}
public_menu();
};

void admin_menu(){
    ticket check;
    system("clear");
    int c;
    cout<<"\t\t\t____________________________________________________________\n\n";
    cout<<"\t\t\t                       IRCTC TICKETING                      \n";
    cout<<"\t\t\t____________________________________________________________\n\n";
    cout<<"\t PRESS 1 TO VIEW PASSENGER LIST\n";
    cout<<"\t PRESS 2 TO SHOW ALL STATIONS\n";
    cout<<"\t PRESS 3 TO ADD A STATION\n";
    cout<<"\t PRESS 4 TO LOGOUT\n";
    cout<<"\n\t\t Please select from options above\n\n";
    cin>>c;
    system("clear");
    ifstream input("stations.txt");
    string name;
    float x;
    float y;
    int id;
    
    int idstart;
    int iddest;
    date checkdate;
    station newstation;
     switch(c){
        case 1:
                cout<<"\t\t\tPlease enter details of train to check from the possible combination of the following\n\n";
                
                cout<<"-------------------------------------------------------------------------------------------\n";
                cout<<"|                       |            |                          |                         |\n";
                cout<<"|         NAME          |      ID    |         X-POS            |         Y-POS           |\n";
                cout<<"|                       |            |                          |                         |\n";
                cout<<"-------------------------------------------------------------------------------------------\n";
                while(input>>name>>id>>x>>y){
                    cout<<name<<"                     "<<id<<"               "<<x<<"                     "<<y<<endl;};
                cout<<"-------------------------------------------------------------------------------------------\n";
                cout<<"Enter ID of start station: ";
                cin>>idstart;
                cout<<"Enter ID of destination station: ";
                cin>>iddest;
                cout<<"Enter day of journey: ";
                cin>>checkdate.d;
                cout<<"Enter month of journey: ";
                cin>>checkdate.m;
                cout<<"Enter year of journey: ";
                cin>>checkdate.y;
                check.TravelList(idstart,iddest,checkdate);


                admin_menu();
        case 2: 
                system("clear");
                
                cout<<"\t\t\tPlease enter details of train to check from the possible combination of the following\n\n";
                
                cout<<"-------------------------------------------------------------------------------------------\n";
                cout<<"|                       |            |                          |                         |\n";
                cout<<"|         NAME          |      ID    |         X-POS            |         Y-POS           |\n";
                cout<<"|                       |            |                          |                         |\n";
                cout<<"-------------------------------------------------------------------------------------------\n";
                while(input>>name>>id>>x>>y){
                    cout<<name<<"                     "<<id<<"               "<<x<<"                     "<<y<<endl;};
                cout<<"-------------------------------------------------------------------------------------------\n";
                cout<<"\nPress 1 to go back:";
                cin>>c;
                admin_menu();

        case 3:
                
                system("clear");
                cout<<"\t\t\t Enter Name of Station to add: ";
                cin>>name;
                cout<<"\t\t\t Enter Station ID: ";
                cin>>id;
                cout<<"\t\t\t Enter X-POS: ";
                cin>>x;
                cout<<"\t\t\t Enter Y-POS: ";
                cin>>y;
                newstation.stationset(x,y,name,id);
                admin_menu();


        
        case 4:
                return;
                
        default:
                system("clear");
                cout<<"Please enter a valid choice\n\n"<<endl;
                sleep(2);
                public_menu();
}
}

int main(){
    system("clear");
    int c;
    int log;
    passenger base;
    ticketcollector tc;
    cout<<"\t\t\t____________________________________________________________\n\n";
    cout<<"\t\t\t                       IRCTC TICKETING                      \n";
    cout<<"\t\t\t____________________________________________________________\n\n";
    cout<<"\t PRESS 1 TO LOGIN\n";
    cout<<"\t PRESS 2 TO LOGIN AS TICKET COLLECTOR\n";
    cout<<"\t PRESS 3 TO REGISTER\n";
    cout<<"\n\t\t Please select from options above\n\n";
    cin>>c;
    cout<<endl;
    
    switch(c){
        case 1:
                base.login();
                public_menu();
                main();                
        case 2: 
                tc.login();
                admin_menu();
                main();

        case 3:
                base.registration();
                main();
                break;
        default:
                system("clear");
                cout<<"Please enter a valid choice\n\n"<<endl;
                main();                
    }
}

void user::registration(){
        system("clear");
        log=1;
        cout<<"Enter New Username and Password, Followed by your Legal Name\n";
        cout<<"\t\t\tUSERNAME:";
        cin>>username;
        ifstream input("data.txt");
        while(input>>usr){
            if(usr==username){
                log=0;
                system("clear");
            }
        }
        input.close();
        if(log==0){
            system("clear");
            cout<<"USERNAME UNAVAILABLE!\n\n";
            sleep(2);
            registration();
        }
        cout<<"\t\t\tPASSWORD:";
        cin>>password;
        cout<<"\t\t\tENTER YOUR LEGAL NAME:";
        cin>>name;
        cout<<"\n\t\t\tREGISTERED SUCCESSFULY!";
        ofstream f1("data.txt", ios::app);
        f1<<username<<" "<<password<<" "<<name<<endl;
        system("clear");
    };

void passenger::BookTicket(){
    system("clear");
    passenger base;
    station check;
    system("clear");
    ticket booking;
    string name;
    float x;
    float y;
    int cost;
    int id;
    int idstart;
    int iddest;
    int c;
    char seat[2];
    ifstream input("stations.txt");
    date traveldate;
    cout<<"-------------------------------------------------------------------------------------------\n";
    cout<<"|                       |            |                          |                         |\n";
    cout<<"|         NAME          |      ID    |         X-POS            |         Y-POS           |\n";
    cout<<"|                       |            |                          |                         |\n";
    cout<<"-------------------------------------------------------------------------------------------\n";
    while(input>>name>>id>>x>>y){
        cout<<name<<"                     "<<id<<"               "<<x<<"                     "<<y<<endl;

    }
    cout<<"-------------------------------------------------------------------------------------------\n";
    cout<<"\t\tPlease enter Departure Station ID:";
    cin>>(idstart);
    cout<<"\t\tPlease enter Destination Station ID:";
    cin>>(iddest);
    cout<<"\t\tPlease enter travel DAY:";
    cin>>traveldate.d;
    cout<<"\t\tPlease enter travel MONTH:";
    cin>>traveldate.m;
    cout<<"\t\tPlease enter travel YEAR:";
    cin>>traveldate.y;
    if(booking.CheckTicket(traveldate)){
        cout<<"YOU ALREADY HAVE A TICKET ON THIS DAY\n";
        sleep(2);
        base.BookTicket();
    }
    cost=ticketconst*(fabs((check.getCoordinates(idstart).x)-(check.getCoordinates(iddest).x))+fabs((check.getCoordinates(idstart).y)-(check.getCoordinates(iddest).y)));
    seat[0] = booking.CheckCountReturnCoach(idstart,iddest,traveldate)[0];
    seat[1] = booking.CheckCountReturnCoach(idstart,iddest,traveldate)[1];
    if(strcmp(seat,"NO")==0){
        cout<<"TICKET NOT AVAILABLE\n";
        sleep(2);
        base.BookTicket();
    }

    ofstream output("tickets.txt",ios::app);
    output<<::current<<" "<<idstart<<" "<<iddest<<" "<<traveldate.d<<" "<<traveldate.m<<" "<<traveldate.y<<" "<<cost<<" "<<seat[0]<<(int)seat[1]<<endl;
    output.close();
    system("clear");
    cout<<"\t\t\tTICKET BOOKED SUCCESFULLY\n";
    cout<<"\t\t\tTOTAL COST:"<<cost<<endl;
    cout<<"\n\n\t\t\t PRESS 1 TO GO BACK: ";
    cin>>c;


    
};

