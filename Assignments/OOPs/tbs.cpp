#include <bits/stdc++.h>
using namespace std;
class user
{
private:
    string username;
    string password;
    string name;
    string list_of_tickets;
public:
    user(string Username,
         string Password,
         string Name,
         string List_of_tickets
        ) 
    {
        username = Username;
        password = Password;
        name = Name;
        list_of_tickets = List_of_tickets;         
    }
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
 void registe(int flag,user Flag)
    { 
        string Name,Username,Password,List_of_tickets;
        cout<< "Enter name\n";
        cin>>Name;
        cout<<"Enter username\n";
        cin>>Username;
        cout<<"Enter password\n";
        cin>>Password;
        Flag = user(Username,Password,Name,List_of_tickets);
    }
int main() 

{
    int flag = 0; //number of users
    
}