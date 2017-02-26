#include<iostream>
#include<iomanip>
#include<string>
#include<windows.h>
#include<conio.h>
#include"concol.h"
#include"machines.cpp"
#include<stdexcept>
#include<cstdlib>
using namespace std;
using namespace eku;

void displayart();

struct console{
	console( unsigned width, unsigned height ){
		SMALL_RECT r;
		COORD      c;
		hConOut = GetStdHandle( STD_OUTPUT_HANDLE );
		if (!GetConsoleScreenBufferInfo( hConOut, &csbi ))
		  throw runtime_error( "You must be attached to a human." );
		
		r.Left   =
		r.Top    = 0;
		r.Right  = width -1;
		r.Bottom = height -1;
		SetConsoleWindowInfo( hConOut, TRUE, &r );
		
		c.X = width;
		c.Y = height;
		SetConsoleScreenBufferSize( hConOut, c );
	}
	~console(){
		SetConsoleTextAttribute(    hConOut,        csbi.wAttributes );
		SetConsoleScreenBufferSize( hConOut,        csbi.dwSize      );
		SetConsoleWindowInfo(       hConOut, TRUE, &csbi.srWindow    );
	}
	void color( WORD color = 0x07 ){
		SetConsoleTextAttribute( hConOut, color );
	}
	HANDLE                     hConOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
};
  
console con( 100, 100 );

int main(void){
	SetConsoleTitle("Machine Interference Simulation");
	concolinit();
	displayart();
	char input;
	bool random;
	while(true){
		cout<<"Generate random numbers for clocks (Y/N)?";
		input = getche();
		if(input == 'y' || input == 'Y' || input == 'n' || input == 'N'){
			switch(input){
				case 'y':
					random = true;
					break;
				case 'Y':
					random = true;
					break;
				case 'n':
					random = false;
					break;
				case 'N':
					random = false;
					break;
			}
			cout<<endl;
			break;
		}
		else{
			cout<<"  Invalid input."<<endl;
		}
	}
	machines initialize(random);
	cout<<endl<<"Enter number of maximum days: ";
	int days = 0;
	cin>>days;
	initialize.setdays(days);
	while(true){
		cout<<"Enter number of Workstations (Maximum is 5): ";
		input = getche();
		if(input == '5' || input == '4' || input == '3' || input == '2' || input == '1'){
			switch(input){
				case '5':
					initialize.setworkstations(5);
					break;
				case '4':
					initialize.setworkstations(4);
					break;
				case '3':
					initialize.setworkstations(3);
					break;
				case '2':
					initialize.setworkstations(2);
					break;
				case '1':
					initialize.setworkstations(1);
					break;
			}
			cout<<endl<<endl;
			initialize.displaycolumn();
			initialize.nextevent();
			break;
		}
		else{
			cout<<endl<<endl<<"Invalid input.";
		}
	}
}

void displayart(){
	cout<<blue<<"                                        MMMMMMMM              MMMMMMMM"<<endl;
	cout<<"                                        MMMMMMMMMMMMMM   MMMMMMMMMMMMM"<<endl;
	cout<<"                                        MMMM   MMMMMMMMMMMMMMMM   MMMM"<<endl;
	cout<<"                                        MMMM                      MMMM"<<endl;
	cout<<"                                        MMMM         "<<white<<"AAAA"<<blue<<"         MMMM"<<endl;
	cout<<"                                        MMMM        "<<white<<"AAAAAA"<<blue<<"        MMMM"<<endl;
	cout<<"                                        MMMM       "<<white<<"AAA  AAA"<<blue<<"       MMMM"<<endl;
	cout<<"                                        MMMM      "<<white<<"AAA    AAA"<<blue<<"      MMMM"<<endl;
	cout<<"                                        MMMM     "<<white<<"AAAAAAAAAAAA"<<blue<<"     MMMM"<<endl;
	cout<<"                                        MMMM    "<<white<<"AAAAAAAAAAAAAA"<<blue<<"    MMMM"<<endl;
	cout<<"                                        MMMM   "<<white<<"AAA          AAA"<<blue<<"   MMMM"<<endl;
	cout<<"                                        MMMM  "<<white<<"AAA            AAA"<<blue<<"  MMMM"<<endl;
	cout<<"                                        MMMM "<<white<<"AAA              AAA"<<blue<<" MMMM"<<endl;
	cout<<"                                        MMMM                      MMMM"<<endl;
	cout<<"                                         MMMM   "<<white<<"CHESTER-AYALA"<<blue<<"   MMMM"<<endl;
	cout<<"                                          MMMM                  MMMM"<<endl;
	cout<<"                                            MMMMMMMMMMMMMMMMMMMMMM"<<endl;
	cout<<"                                                MMMMMMMMMMMMMM"<<endl<<endl;
}
