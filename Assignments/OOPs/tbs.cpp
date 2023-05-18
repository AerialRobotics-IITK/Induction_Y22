#include <bits/stdc++.h>
using namespace std;
class user
{
public:
    string username;
    string password;
    string name;
    string list_of_tickets;

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
};
int main() 
{
    user dhruv = user("dhruvmittal","dhruvmittal","Dhruv","kanpur to delhi");

}