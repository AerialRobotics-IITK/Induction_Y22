#include <bits/stdc++.h>
using namespace std;

class user
{
public:
    string username;
    string password;
    string name;
    string list_of_tickets;

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
user* userdata[1000];
 void newregister(int* flagptr,user* Flag)
    { 
        string Name,Username,Password,List_of_tickets;
        cout<< "Enter name\n";
        cin>>(*Flag).name;
        cout<<"Enter username\n";
        cin>>(*Flag).username;
        cout<<"Enter password\n";
        cin>>(*Flag).password;
        userdata[*flagptr] = Flag;
        (*flagptr)++;

    
        
    }
int main() 

{
    user number1;
    // user* userdata[];
    user* ptr1 = &number1;
    int flag = 0; //number of users
    int* flagptr = &flag;
    newregister(flagptr,ptr1);
    cout<<"\n"<<number1.name<<*flagptr;    
}