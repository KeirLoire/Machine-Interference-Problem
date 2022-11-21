#include<iostream>
#include<iomanip>
#include<string>
#include<cstdlib>
#include<cctype>

#include"machines.cpp"

using namespace std;

int main(void)
{
	bool isRandomRepairTime;
	int workstationCount = 1;
	int days = 0;

	while (true)
	{
		char input;

		cout << "Generate random values for repair time (Y/N): ";
		cin >> input;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << endl << "Invalid input." << endl;
		}
		else
		{
			input = tolower(input);
			if (input == 'y' || input == 'n')
			{
				isRandomRepairTime = (input == 'y');
				break;
			}
			else
			{
				cout << endl << "Invalid input." << endl;
			}
		}
	}

	while (true)
	{
		cout << endl << "Enter number of workstations to be repaired (Maximum is 5): ";
		cin >> workstationCount;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << endl << "Invalid input." << endl;
		}
		else
		{
			if (workstationCount > 5 || workstationCount < 1)
			{
				cout << endl << "Must be within 0 to 5 range." << endl;
			}
			else break;
		}
	}

	while (true)
	{
		cout << endl << "Enter number of maximum days (Max MC): ";
		cin >> days;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << endl << "Invalid input." << endl;
		}
		else break;
	}

	Machines m(isRandomRepairTime, workstationCount, days);
	m.Start();
}