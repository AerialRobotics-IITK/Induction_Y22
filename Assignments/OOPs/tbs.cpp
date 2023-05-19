#include<iostream>
#include <bits/stdc++.h>
using namespace std;

class user
{
public:
    string username;
    string password;
    string name;
    int nt = 0; //number of tickets
    pair<int,int> tickets[100];
 
    


    void viewTickets()
    {
        
        for(int i=0;i<nt;i++)
            {
            cout<<tickets[i].first <<" "<<tickets[i].second;
            i++;
            }
    }
    void bookTicket
    // user(string Username,
    //      string Password,
    //      string Name,
    //      string List_of_tickets)
    // {
    //     username = Username;
    //     password = Password;
    //     name = Name;
    //     list_of_tickets = List_of_tickets;         
    // }
    // void register()
    // { 
    //     string Name,Username,Password;
    //     cout>> "Enter Name\n";
    //     cin<<"Name";
    //     cout>>"Enter username\n";
    //     cin<<"Username";
    //     cout<<"Enter password\n";
    //     cin>>"Password";
    //     user(Username,Password,Name,List_of_tickets);
        
    // }
    // void setName(string Name)
    // {
    //     name = Name;
    // }

    
    
};
user* userdata[1000]; //array of pointer to users
int flag = 0; //number of users
int* flagptr = &flag;
 void newpassengerregister(int* flagptr,user* Flag)
    { 
        string Name,Username,Password,List_of_tickets;
        cout<< "Enter name\n";
        cin>>(*Flag).name;
        cout<<"Enter username\n";
        cin>>(*Flag).username;
        cout<<"Enter password\n";
        cin>>(*Flag).password;
        (*flagptr)+=1;
        userdata[*flagptr] = Flag;
    }
 
int main() 

{
    // int flag; //number of users
    // int* flagptr = &flag;
    // *flagptr=0;
    // cout<<"\n"<<*flagptr<<"\n";
    cout<<"Press RP to signup as passenger\n"<<
                "LP to login as passenger\n";
    string loginpage;
    cin>> loginpage;
    if(loginpage == "RP")
        {
            // (*flagptr)+=1;
            user temp;
            userdata[flag] = &temp;
            newpassengerregister(flagptr,userdata[*flagptr]);
            cout<<"User successfully registered with unique id "<<*flagptr<<"\n";

        }


        
    else if(loginpage == "LP")
       {
        int tempid;
        string temppass;
        cout<<"Enter uid(unique id) ";
        cin>>tempid;
        cout<<"Enter password ";
        cin>>temppass;
        if((*(userdata[tempid])).password == temppass)
        {
            cout<<"logged in successfully \n";
        }
        else
        {
            cout<<"wrong unique id or password \nPlease try again\n";
        }
       }
       main();

    
    cout<<"\n\n\n"<<"\n"<<*flagptr;    
    return 0;
}