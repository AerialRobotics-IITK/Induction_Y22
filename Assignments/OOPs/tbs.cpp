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
         string List_of_tickets,
        ) 
    {
        username = Username;
        password = Password;
        name = Name;
        list_of_tickets = List_of_tickets;         
    }
    void register()
    { 
        string Name,Username,Password;
        cout>> "Enter Name\n";
        cin<<"Name";
        cout>>"Enter username\n";
        cin<<"Username";
        cout<<"Enter password\n";
        cin>>"Password";
        user(Username,Password,Name,List_of_tickets);
        
    }
    // void setName(string Name)
    // {
    //     name = Name;
    // }

    
    
};
int main() 

{
    int flag = 0;
    user dhruv = user("dhruvmittal","dhruvmittal","Dhruv","kanpur to delhi");

}