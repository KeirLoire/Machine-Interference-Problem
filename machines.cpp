#include<ctime>
using namespace std;

class Machines{
	private:
		int MC = 0;
		int target = 0;
		int machineCount = 1;
		int days;
		int CL[6];
		int queue = 0;
		bool busy = false;

		void Arrival();
		void Departure();
		void Display();
	public:
		Machines(bool isRandomRepairTime, int machineCount, int days);
		void Start();
};

Machines::Machines(bool isRandomRepairTime, int machineCount, int days)
{
	this->machineCount = machineCount;
	this->days = days;

	// Randomize repair time values
	if (isRandomRepairTime)
	{
		srand(time(0));
		for(int i = 0; i < 5; i++)
		{
			this->CL[i] = rand() % 10;
		}
	}
	else
	{
		this->CL[0] = 1;
		this->CL[1] = 4;
		this->CL[2] = 9;
		this->CL[3] = 4;
		this->CL[4] = 3;
		this->CL[5] = 6;
	}
}

void Machines::Start()
{
	// Display reference
	cout << endl << "MC = master clock";
	cout << endl << "CLx = machines";
	cout << endl << "CL" << this->machineCount + 1 << " = repairman completion time";
	cout << endl << "n = queued machines";
	cout << endl << "R = repairman status";
	cout << endl << "i = machine being repaired";

	// Display header
	cout << endl << endl << setw(6) << "MC";
	for(int i = 0; i <= this->machineCount; i++){
		cout << setw(6) << "CL" + to_string(i + 1);
	}
	cout << setw(5) << "n" << setw(6) << "R" << setw(6) << "i" << "\n";

	// Display initial values
	this->Display();

	// Do while until MC reached maximum days
	while (this->MC <= this->days)
	{
		if(this->MC >= 11)
		{
			// Fast track
			this->Arrival();
			this->Departure();
			this->Display();
		}
		else
		{
			if(this->queue <= 1)
			{
				this->Arrival();
				this->Display();
			}
			else
			{
				this->Departure();
				this->Display();
			}	
		}
		
	}
}

void Machines::Arrival()
{
	this->target++;
	
	if (this->target > this->machineCount)
	{
		this->target = 1;
	}

	for (int i = 0; i <= this->machineCount; i++)
	{
		if (this->target == i + 1)
		{
			this->MC = this->CL[i];
			this->CL[i] = 0;
		}
	}

	if (this->queue == 0)
	{
		this->busy = true;
		this->CL[this->machineCount] = this->MC + 5;
	}

	this->queue++;
}

void Machines::Departure()
{
	this->MC = this->CL[this->machineCount];
	this->queue--;

	if (this->queue == 0)
	{
		this->busy = false;
	}
	else
	{
		this->CL[this->machineCount] = this->MC + 5;

		if (this->target == 1)
		{
			this->CL[this->machineCount - 1] = this->MC + 10;
		}
		else
		{
			this->CL[this->target - 2] = this->MC + 10;
		}
	}
}

void Machines::Display(){
	cout << setw(6) << this->MC;

	for (int i = 0; i <= this->machineCount; i++)
	{
		cout << setw(6) << this->CL[i];
	}

	cout << setw(5) << this->queue;

	if (this->busy)
	{
		cout << setw(6) << "idle";
	}
	else
	{
		cout << setw(6) << "busy";
	}

	cout << setw(6) << "CL" + to_string(this->target) << endl;
}
