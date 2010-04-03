//============================================================================
// Name        : tic-tac-to.cpp
// Author      : Matthew Francis-Landau
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "ai.hpp"
using namespace std;


void print_bord(char bord[9]) {
	cout 
	<< bord[0]  << '|' << bord[1] << '|' << bord[2] << "          " << "1|2|3" << endl
	<< "-+-+-" << "          " << "-+-+-" << endl
	<< bord[3] << '|' << bord[4] << '|' << bord[5] << "          " << "4|5|6" << endl
	<< "-+-+-" << "          " << "-+-+-" << endl
	<< bord[6] << '|' << bord[7] << '|' << bord[8] << "          " << "7|8|9" << endl << endl;
	
}

int user_input () {
	int place;
	cout << "Enter the Number of the place that you would like to go\n";
	cin>>place;
	return --place;
}

int main(int argc, char *argv[]) {
	ai *a;
	a = new ai(&print_bord, &user_input);
	bool turn = false;
	int user_score = 0;
	int ai_score = 0;
	int last = -1;
	while (true) {
		try {
			last = a->start(turn);
			a->reset();
			turn = !turn;
			if(last == 1) user_score++;
			else if(last == 2) ai_score++;
			cout<<"User: "<<user_score<<"\nAi: "<<ai_score<<endl;
		}catch(char * e) {
			cout<<"error: "<<e;
			break;
		}
	}
	delete a;
	//cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
