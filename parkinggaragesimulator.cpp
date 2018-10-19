/*Garage project (project 3) for CS 112. This simulates a parking service in multiple garages. From the project description: 
"When a car arrives it tries to park in the LOWER WEST. If no room it goes to the UPPER WEST...If still no room it waits in EAST.
When a car departs a message should indicate where it departed from (i.e. which garage). If there is a car waiting to get in the 
garage (because both are full) then the first car in the EAST must be moved into the garage that now has room and a message stating  
this must appear. When a car exits either WEST garage (but NOT EAST) the parking fee must be also be displayed as follows :
If the car is at the front of the queue, fee is $0, if second in the queue $10, if third or further back, $25. When we exit 
the program it should indicate how many cars are in each garage and the total of the fees collected." */

#include <iostream> 
#include <queue>
#include <string> // license plates are strings
using namespace std;

int fees = 0; // running counter of total fees
string card; // car to be picked up (car to be parked, cara, is delcared in the arrival function)
queue<string> lowerwest; // queue representing lower west garage
queue<string> upperwest; // queue representing upper west garage
queue<string> east; // queue representing east garage
queue<string> temp; // temporary queue for when a car is picked up - all the cars in card's garage except for card are placed here, then placed back in the garage in order.

void prompt(); // asks the user if they want to park a car, pick one up, or exit the program.
void arrival(); // parks an inputted car in either lower west, upper west, or east garage depending on parking availability. if all garages are full, user is told to park on main campus.
int find(); // takes an inputted car to be picked up and returns which garage the car is in (or if there is no such car in the garages).
void departure(); // removes the inputted car from its garage, prints the fee for the removal of the car. if there are cars in east garage, the front car is moved to a west garage.

int main()
{
	prompt();
	return 0;
}

void prompt()
{
	char choice;
	cout << "What would you like to do? Press a for arrival, d to depart, e to exit \n";
	cin >> choice;
	if (choice == 'a')
	{
		arrival();
		prompt();
	}
	if (choice == 'd')
	{
		departure();
		prompt();
	}
	if (choice == 'e')
	{
		cout << "There are currently:  \n";
		cout << lowerwest.size() << " cars in the Lower West Garage \n";
		cout << upperwest.size() << " cars in the Upper West Garage \n";
		cout << east.size() << " cars in the East Garage \n";
		cout << "Total fees collected: $" << fees;
	}
}

void arrival()
{
	cout << "Enter license plate: \n";
	string cara;
	cin >> cara;
	if (lowerwest.size() == 6 and upperwest.size() == 6 and east.size() == 5)
		cout << "All garages are full, park on main campus. \n";
	if (lowerwest.size() == 6 and upperwest.size() == 6 and east.size() < 5)
	{
		east.push(cara);
		cout << "Both West Garages are full - your car was parked in the East Garage and will be moved to a West garage at the earliest opening. \n";
	}
	if (lowerwest.size() == 6 and upperwest.size() < 6)
	{
		upperwest.push(cara);
		cout << "Lower West Garage is full, your car was parked in the Upper West Garage. \n";
	}
	if (lowerwest.size() < 6)
	{
		lowerwest.push(cara);
		cout << "Your car was parked in the Lower West Garage. \n";
	}
}

int find() //takes an inputted car and finds which garage it's in
{
	int garagenumber = 0; //lowerwest = 1, upperwest = 2, east = 3, 0 = car isn't found
	bool found = false;
	cout << "Enter the license plate of the car you're retrieving: \n";
	cin >> card;
	queue <string> lw1 = lowerwest;
	queue <string> uw1 = upperwest;
	queue <string> e1 = east;
	int uwlength = uw1.size(), lwlength = lw1.size(), elength = e1.size();
	while (!lw1.empty())
	{
		if (lw1.front() == card)
		{
			garagenumber = 1;
			found = true;
			break;
		}
		if (lw1.front() != card)
			lw1.pop();		
	}
	if (found == false)
	{
		while (!uw1.empty())
		{
			if (uw1.front() == card)
			{
				garagenumber = 2;
				found = true;
				break;
			}
			if (uw1.front() != card)
				uw1.pop();
		}
	}
	if (found == false)
	{
		while (!e1.empty())
		{
			if (e1.front() == card)
			{
				garagenumber = 3;
				found = true;
				break;
			}
			if (e1.front() != card)
				e1.pop();
		}
	}
	return garagenumber;
}

void departure()
{
	int garagenum = find();
	if (garagenum == 0)
		cout << "Car not found! \n";
	bool found = false;
	if (garagenum == 1)
	{
		int spacecounter = 0;
		while (!lowerwest.empty())
		{
			if (lowerwest.front() != card)
			{
				temp.push(lowerwest.front());
				lowerwest.pop();
				if (found == false)
					spacecounter += 1;
			}
			else
			{
				lowerwest.pop();
				found = true;
				spacecounter += 1;
			}
		}
		while (!temp.empty())
		{
			lowerwest.push(temp.front());
			temp.pop();
		}
		cout << "Your car departed from Lower West. Your fee is: ";
		if (spacecounter < 2)
			cout << "$0 \n";
		if (spacecounter == 2)
		{
			cout << "$10 \n";
			fees += 10;
		}
		if (spacecounter > 2)
		{
			cout << "$25 \n";
			fees += 25;
		}
		if (east.size() > 0) // moves front car in east to the garage
		{
			lowerwest.push(east.front());
			cout << "Car with license plate " << east.front() << " was moved to the Lower West Garage. \n";
			east.pop();
		}
		cout << "There are currently:  \n";
		cout << lowerwest.size() << " cars in the Lower West Garage \n";
		cout << upperwest.size() << " cars in the Upper West Garage \n";
		cout << east.size() << " cars in the East Garage \n";
		cout << "Total fees collected: $" << fees << "\n";
	}
	if (garagenum == 2)
	{
		int spacecounter = 0;
		while (!upperwest.empty())
		{
			if (upperwest.front() != card)
			{
				temp.push(upperwest.front());
				upperwest.pop();
				if (found == false)
					spacecounter += 1;
			}
			else
			{
				upperwest.pop();
				found = true;
				spacecounter += 1;
			}
		}
		while (!temp.empty())
		{
			upperwest.push(temp.front());
			temp.pop();
		}
		cout << "Your car departed from Upper West. Your fee is: ";
		if (spacecounter < 2)
			cout << "$0 \n";
		if (spacecounter == 2)
		{
			cout << "$10 \n";
			fees += 10;
		}
		if (spacecounter > 2)
		{
			cout << "$25 \n";
			fees += 25;
		}
		if (east.size() > 0) //moves front car in east to the garage
		{
			upperwest.push(east.front());
			cout << "Car with license plate " << east.front() << " was moved to the Upper West Garage. \n";
			east.pop();
		}
		cout << "There are currently:  \n";
		cout << lowerwest.size() << " cars in the Lower West Garage \n";
		cout << upperwest.size() << " cars in the Upper West Garage \n";
		cout << east.size() << " cars in the East Garage \n";
		cout << "Total fees collected: $" << fees << "\n";
	}
	if (garagenum == 3)
	{
		while (!east.empty())
		{
			if (east.front() != card)
			{
				temp.push(east.front());
				east.pop();
			}
			else
				east.pop();
		}
		while (!temp.empty())
		{
			east.push(temp.front());
			temp.pop();
		}
		cout << "Your car departed from East. There are no fees. \n";
		cout << "There are currently:  \n";
		cout << lowerwest.size() << " cars in the Lower West Garage \n";
		cout << upperwest.size() << " cars in the Upper West Garage \n";
		cout << east.size() << " cars in the East Garage \n";
		cout << "Total fees collected: $" << fees << "\n";
	}
}
