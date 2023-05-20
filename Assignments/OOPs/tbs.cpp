#include <bits/stdc++.h>
using namespace std;
class ticket
{
    public:
    pair<int,int> startpoint;
    pair<int,int> endpoint;
    pair<pair<int,int>,pair<int,int>> ticketcoordinates[1000];
    string date;
    int cost;
};

class user
{
public:
    string username;
    string password;
    string name;
    int nt = 0; //number of tickets 
    ticket* usertickets;

    void bookTicket(int a,int b,int c,int d)
    {
        nt++;
        (((*usertickets).ticketcoordinates[nt]).first).first = a;
        (((*usertickets).ticketcoordinates[nt]).first).second = b;
        (((*usertickets).ticketcoordinates[nt]).second).first = c;
        (((*usertickets).ticketcoordinates[nt]).second).second = d;
    }


};

user* userdata[1000]; //array of pointer to users
ticket* ticketdata[1000];//array of pointer to tickets
int nuser= 0; //number of users
int* nuserptr = &nuser;
 
void newpassengerregister(int* nuserptr,user* Flag)
    { 
        string Name,Username,Password,List_of_tickets;
        cout<< "Enter name\n";
        cin>>(*Flag).name;
        cout<<"Enter username\n";
        cin>>(*Flag).username;
        cout<<"Enter password\n";
        cin>>(*Flag).password;
        (*nuserptr)+=1;
        userdata[*nuserptr] = Flag;
    }
 
int main() 

{
    // int* nuserptr = &nuser;
    // *nuserptr=0;
    // cout<<"\n"<<*nuserptr<<"\n";
    cout<<"Type RP to signup as passenger\n"<<
                "LP to login as passenger\n";
    string loginpage;
    cin>> loginpage;
    if(loginpage == "RP")
        {
            user temp;
            userdata[nuser] = &temp;
            newpassengerregister(nuserptr,userdata[*nuserptr]);
            cout<<"User successfully registered with unique id "<<*nuserptr<<"\n";
            main();

        }
     else if(loginpage == "LP")
       {
        int tempid;    //for verification
        string temppass;
        cout<<"Enter uid(unique id) ";
        cin>>tempid;
        cout<<"Enter password ";
        cin>>temppass;

        if((*(userdata[tempid])).password == temppass)
        {
            string bookorview;
            cout<<"logged in successfully \n";
            cout<<"Type viewtickets to view old tickets\nor\nbookticket to book new ticket\nor\nR to return to login portal ";
            cin>>bookorview;
            while(bookorview!="R")
            {
              if(bookorview == "viewtickets")
               {
                   for(int i=0;i<(*(userdata[tempid])).nt;i++)
                   {
                        cout<<"Journey "<<i<<" details\nsource - ";
                        cout<<(((*((*(userdata[tempid])).usertickets)).ticketcoordinates[i]).first).first;
                        cout<<","<<(((*((*(userdata[tempid])).usertickets)).ticketcoordinates[i]).first).second;
                        cout<<"\ndestination - "<<(((*((*(userdata[tempid])).usertickets)).ticketcoordinates[i]).second).first;
                        cout<<","<<(((*((*(userdata[tempid])).usertickets)).ticketcoordinates[i]).second).second;




                   }
               }
              else if(bookorview == "bookticket")
              {
                int sp1,sp2; //starting point
                int ep1,ep2; //end point
                cout<<"enter starting station ";
                cin>>sp1>>sp2;
                cout<<"enter destination";
                cin>>ep1>>ep2;
                (*(userdata[tempid])).bookTicket(sp1,sp2,ep1,ep2);
                cout<<"ticket book successfully";
    
                
              }   
            }
        
        


        }
        


        else
        {
            cout<<"wrong unique id or password \nPlease try again\n";
            main();
        }
       }
       

    
    cout<<"\n\n\n"<<"\n"<<*nuserptr;   // 
    return 0;
}