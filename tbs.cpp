#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctime>
#include<vector>
#include<iterator>
#include<bits/stdc++.h>
using namespace std;


	
	class ticket{

	public:

		string start;
		string end;
		string ticketDate;
		int cost;

		int ticketId;
		
		int getTicket(){
			return ticketId;
		}

		void viewTicket(){

			std::cout << ticketId << endl;
			std::cout << start << endl;
			std::cout << end << endl;
			std::cout << (ticketDate) << endl;
			std::cout << cost << endl; 
			return;
		}

	ticket(string S, string E, int C, string D, int ID){

		start = S;
		end = E;
		cost = C;
		ticketDate = D;
		ticketId = ID;
		}

	};

	class User{

		public:
			string Name;
			int UserID;
			string passWord;

			int verifyPassword(void){

			string pass;
			cout << "please enter your password: ";
			cin >> pass;
			if(pass.compare(passWord)==0) return 1;
			else return 0;

		}

		// User(string n, string p, ticket* t, int un){
		// 	Name = n;
		// 	passWord = p;
		// 	UserID = un;
		// 	userTicket = t;
		// 	}
			ticket* userTicket;
			vector <ticket> Tickets;

		void getUserID(){

				std::cout << UserID << endl;
				return;

			}

		void viewTickets(){
			
			for(ticket& t : Tickets){

				std::cout << (t).start << "\n" << (t).end << "\n" << (t).ticketDate << "$" <<(t).cost << "\n";
			}
		}


	};

	class station{

		public:
			string name;
			int xCoord;
			int yCoord;

			void getCoord(){

				std::cout << "(" << xCoord << "," << yCoord << ")" << endl;
				return;
			}

		station(string n, int x, int y){

			xCoord = x;
			yCoord = y;
			name = n;
		}

	};

	class train{
		public:
			station* trainSource;
			station* trainDest;
			int cost;
			string trainNo;
			vector<int> seats{0,1,2,3,4,5,6,7};
			vector<int> bookedSeats;
			
	// train(station* S, station* D, string t, vector<int> St, int C);
			// int seatPt;


		train(station* S, station* D, string t){
			trainSource = S;
			trainDest = D;
			cost = ((*D).xCoord + (*D).yCoord) - ((*S).xCoord + (*S).yCoord);
			cost = cost>0?cost:-1*cost;
			trainNo = t;

		}
	};

	// vector<int>	makeSeats(vector<int> seat){

	// 		for(int i=0; i<8; i++){
	// 			seat.push_back(i);
	// 		}

	// }

	vector<train> trains;

	class travel{

		public:
			int seat;
			int coach;
			int bookedSeat;
			string source;
			string Destination;
			string currDate;
			void viewPassList();

			void viewJourney(){
				cout << bookedSeat << endl;
				cout << "seat: " << seat << "coach: " << coach;
				std::cout << source << "->" << Destination << endl;
				std::cout << currDate << endl;
			}

	};

	class Passenger: public User{

		public:
			int PassengerID;

			void getPassengerID(){
				cout << PassengerID << endl;
				return;
			}
 
			Passenger(void){
				PassengerID = 0;
				Name = "1";
				passWord ="/";
				UserID = 2;
			};
			Passenger(string N, int UID, string pw,int n){
				PassengerID = n;
				Name = N;
				passWord = pw;
				UserID = UID;
			}

	//booking a ticket
		void bookTicket(vector<train>& trainsCopy,vector<travel>& travels){
			station E("E",4,2);
			string boarding,destination;
			std::cout << "Enter Boarding Station: ";
			std::cin >> boarding;
			std::cout << "Enter Destination: ";
			std::cin >> destination;
			string temp = boarding;
			string reqTrainNo = boarding.compare(destination)>0?destination.append(boarding):boarding.append(destination);
			train reqTrain(&E,&E,"EE");
			vector<train>::iterator itr;
	//checking for seat in required train
			for(itr = trainsCopy.begin();itr!=trainsCopy.end();itr++){
				if(reqTrainNo.compare((*itr).trainNo)==0){
				
					if(((*itr).seats).size() >= 1){
						int seatNo = ((*itr).seats).back();
						cout << "seat: " << (seatNo)%4 << "\ncoach: " << seatNo/4 << endl;
						((*itr).seats).pop_back();
						((*itr).bookedSeats).push_back(PassengerID);
						travel travelTemp;
						travelTemp.source = temp;
						travelTemp.Destination = destination;
						time_t now = time(0);
						char* date = ctime(&now);
						string d = date;
						travelTemp.currDate = d;
						int bookedId = rand();
						travelTemp.bookedSeat = bookedId;
						travelTemp.seat = (seatNo)%4;
						travelTemp.coach = seatNo/4;
						travels.push_back(travelTemp);
						ticket bookedTicket(temp, destination, (*itr).cost, d, bookedId);
						std::cout << "Booked\nBooked ID: " << bookedId;
						bookedTicket.viewTicket();
						Tickets.push_back(bookedTicket);
						break;
					}
					else std::cout << "No Seat\n";
						}
				}
				
			}
	};

	class TicketCollector: public User{

		public:
			int EmployeeID;

		TicketCollector(){
				EmployeeID = 0;
				Name = "1";
				passWord ="/";
				UserID = 2;
			};
		TicketCollector(string N, int UID, string pw,int n){
			EmployeeID = n;
			Name = N;
			passWord = pw;
			UserID = UID;
		}

			void getEmployeeID(){

				cout << EmployeeID << endl;
				return;
			}
	};

// user sign up


//for passenger or admin login 
	int PassengerLogin(Passenger& activePassTemp, vector<Passenger>& Passengers){
		std::cout << "Enter PassengerID: ";
		std::cin >> (activePassTemp).PassengerID;
	//password verification
		 vector<Passenger>::iterator itr1;
		for(itr1 = Passengers.begin();itr1 != Passengers.end();itr1++){
			cout << "done";
			if((activePassTemp).PassengerID == (*itr1).PassengerID){
				if((*itr1).verifyPassword()==1){
					(activePassTemp) = (*itr1);
					return 1;
					}
				else {

					cout << "Wrong!\n";
					return 0;
				}
			}
		}
		 if(itr1 == Passengers.end()) std::cout << "Passenger not found.";

	}

	Passenger* PassengerPtr(Passenger& activePassTemp, vector<Passenger>& Passengers){
	//password verification
		 vector<Passenger>::iterator itr1;
		for(itr1 = Passengers.begin();itr1 != Passengers.end();itr1++){
			cout << "done";
			if((activePassTemp).PassengerID == (*itr1).PassengerID){
				
					Passenger* (activePassPtr) = &(*itr1);
					return activePassPtr;
			}
		}
	}

	// void TcLogin(TicketCollector& activeTcTemp,vector<TicketCollector> Tcs);

	void newUserLogin(User& tempUser,vector<User>& tempusers){
		cout << "Name: ";
		cin >> tempUser.Name;
		cout << "UserID: ";
		cin >> tempUser.UserID;
		cout << tempUser.UserID;
		cout << "Password: ";
		cin >> tempUser.passWord;
		cout << tempUser.passWord;
		tempusers.push_back(tempUser);
		cout << "done";
	}

	int TcLogin(TicketCollector& activeTcTemp, vector<TicketCollector>& TcsCopy);


int main(){

	vector<User> users;
	User Admin;
	users.push_back(Admin);
	vector<travel>travels;
	station A("A",5,9);
	station B("B",6,2);
	station C("C",3,8);
	station D("D",1,4);
	train AB(&A,&B,"AB");
	train AC(&A,&C,"AC");
	train AD(&A,&D,"AD");
	train BD(&B,&D,"BD");
	train CD(&C,&D,"CD");
	train BC(&B,&C,"BC");
	vector<Passenger> Passengers;
	Passenger a("a",1,"aa",11);
	Passenger b("b",2,"bb",22);
	Passenger c("c",3,"cc",33);
	Passenger d("d",4,"dd",44);
	Passenger e("e",5,"ee",55);
	Passenger f("f",6,"ff",66);
	Passenger g("g",7,"gg",77);
	Passenger h("h",8,"hh",88);
	Passenger i("i",9,"b",99);
	Passengers.push_back(a);
	Passengers.push_back(b);
	Passengers.push_back(c);
	Passengers.push_back(d);
	Passengers.push_back(e);
	Passengers.push_back(f);
	Passengers.push_back(g);
	Passengers.push_back(h);
	Passengers.push_back(i);
	vector<TicketCollector> Tcs;
	vector<train> trains;
	trains.push_back(AB);
	trains.push_back(AC);
	trains.push_back(AD);
	trains.push_back(BC);
	trains.push_back(BD);
	trains.push_back(CD);
	time_t now = time(0);
	char* date = ctime(&now);
	std::cout << date << endl; // print local date and time.
	while(1){
		std::cout << "" << "Welcome" << endl << "New User -> 0\nPassenger Login -> 1\nTC Login -> 2\nview Travels -> 3";
		int selector;
		std::cin >> selector;
		switch(selector){

			case 0: {
				User newUser;
				newUserLogin(newUser,users);
				int flag;
				cout << "Passenger -> 0\nTC -> 1\n";
				cin >> flag;
					switch(flag){
						case 0: {
							int CurrPassID;
							cout << "PassengerID: ";
							cin >> CurrPassID;
							Passenger newPass(newUser.Name,newUser.UserID,newUser.passWord,CurrPassID);
							cout << CurrPassID << endl;
							Passengers.push_back(newPass);
						}
						break;
						case 1:{
							int CurrTCID;
							cout << "TCID: ";
							cin >> CurrTCID;
							TicketCollector newTC(newUser.Name,newUser.UserID,newUser.passWord,CurrTCID);
							cout << CurrTCID << endl;
							Tcs.push_back(newTC);
						}
						break;
					}
				}
			break;
			case 1: {
				cout << "Welcome!";
				Passenger activePass;
				while(!PassengerLogin(activePass,Passengers));
				Passenger* activePassRef = PassengerPtr(activePass,Passengers);
				while(1){
					cout << "Book Tickets -> 0\nGet PassengerID -> 1\nview tickets -> 2\nGet UserID -> 3\nHome -> 4\n";
					int flag;
					cin >> flag;
					if(flag==4)break;
					switch(flag){
						case 0:{ 

							if(((*activePassRef).Tickets).size()==1){
								cout <<	"Already booked for today\n";
								break;
							}
							(*activePassRef).bookTicket(trains,travels);
							}
						break;
						case 1: (*activePassRef).getPassengerID();
						break;
						case 2: {
							if(((*activePassRef).Tickets).size()==0) cout << "No tickets\n";
							(*activePassRef).viewTickets();
						}
						break;
						case 3: (*activePassRef).getUserID();
						break;
					}
				}
			};
			break;
			case 2: {
				cout << "Welcome!";
				TicketCollector activeTc;
				while(!TcLogin(activeTc,Tcs));
				activeTc.getEmployeeID();
			}
			break;
			case 3: {
					vector<travel>::iterator itr3;
					for(itr3 = travels.begin();itr3 != travels.end(); itr3++){
						(*itr3).viewJourney();
				}

			}
			break;
		}
	}
}

	int TcLogin(TicketCollector& activeTcTemp, vector<TicketCollector>& TcsCopy){
		std::cout << "Enter TCID: ";
		std::cin >> (activeTcTemp).EmployeeID;
	//password verification
		 vector<TicketCollector>::iterator itr1;
		for(itr1 = TcsCopy.begin();itr1 != TcsCopy.end();itr1++){
			cout << "done";
			if((activeTcTemp).EmployeeID == (*itr1).EmployeeID){
				if((*itr1).verifyPassword()==1){
					(activeTcTemp) = (*itr1);
					return 1;
					}
				else {

					cout << "Wrong!\n";
					return 0;
				}
			}
		}
		 if(itr1 == TcsCopy.end()) std::cout << "Tc not found.";

	}







 





			

