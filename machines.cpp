#include<ctime>
using namespace std;
using namespace eku;

class machines{
	private:
		int MC;
		int target;
		int workstations;
		int days;
		int CL[6];
		int queue;
		int busy;
		bool random;
		string mode;
	public:
		machines(bool input);
		void setworkstations(int input);
		void setdays(int input);
		void nextevent();
		void arrival();
		void departure();
		void displaycolumn();
		void displaycells();
};

machines::machines(bool input){
	MC = 0;
	target = 0;
	queue = 0;
	busy = 0;
	mode = "Default";
	random = input;
}

void machines::setworkstations(int input){
	workstations = input;
	if(random){
		srand(time(0));
		for(int i=0; i<5; i++){
			CL[i] = rand() % 10;
		}
	}
	else{
		CL[0] = 1;
		CL[1] = 4;
		CL[2] = 9;
		CL[3] = 4;
		CL[4] = 3;
		CL[5] = 6;
	}
}

void machines::setdays(int input){
	days = input;
}

void machines::nextevent(){
	while(MC <= days){
		if(MC >= 11){
			arrival();
			departure();
			mode = "Departure";
			displaycells();
		}
		else{
			if(queue<=1){
				mode = "Arrival";
				arrival();
				displaycells();
			}
			else{
				mode = "Departure";
				departure();
				displaycells();
			}	
		}
		
	}
}

void machines::arrival(){
	target = target + 1;
	if(target > workstations){
		target = 1;
	}
	for(int i=0; i<=workstations; i++){
		if(target == i+1){
			MC = CL[i];
			CL[i] = 0;
		}
	}
	if(queue == 0){
		busy = 1;
		CL[workstations] = MC + 5;
		queue = queue + 1;
	}
	else{
		queue = queue + 1;
	}
}

void machines::departure(){
	MC = CL[workstations];
	queue = queue - 1;
	if(queue == 0){
		busy = 0;
	}
	else{
		CL[workstations] = MC + 5;
		if(target == 1){
			CL[workstations-1] = MC + 10;
		}
		else{
			CL[target - 2] = MC + 10;
		}
	}
}

void machines::displaycolumn(){
		cout<<yellow<<setw(4)<<"MC";
	for(int i=0; i<=workstations; i++){
		cout<<setw(6)<<"CL"<<i+1;
	}
	cout<<setw(7)<<"n"<<setw(6)<<"R"<<setw(6)<<"i"<<setw(13)<<"Mode"<<green<<"\n";
}

void machines::displaycells(){
	cout<<setw(6)<<white<<MC;
	if(mode == "Arrival"){cout<<green;Beep(1000+MC, 200);}
	else if(mode == "Departure"){cout<<red;Beep(1200+MC, 200);}
	for(int i=0; i<= workstations; i++){
		cout<<setw(6)<<CL[i];
	}
	cout<<setw(7)<<queue<<setw(6);
	if(busy == 0){
		cout<<"idle";
	}
	else{
		cout<<"busy";
	}
	cout<<setw(6)<<target<<setw(13)<<mode<<"\n";
}
