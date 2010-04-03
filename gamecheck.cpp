#include "ai.hpp"
/*
 * function  for running the game
 */
int ai::start (bool ai_turn) {
	reset();
	ai_was_first = ai_turn;
	int win = 0;
	int move;
	while (check_cat() == false && win == 0) {
		print();
		if(ai_turn == true) {
			move = ai_move();
			bord[move] = 'o';
		}else{
			move = user();
			bord[move] = 'x';
		}
		ai_turn = !ai_turn;
		win = check_win();
	}
	print();
	if(win == 1 || win == 0) {
		ai_learn(win == 1);
	}
	return win;
}

void ai::reset () {
	history.clear();
	for(int a=0;a < (int)sizeof(bord);a++)
		bord[a] =' ';
}

void ai::print_history () {
	for (int a = 0;a<(int)history.size();a++) {
		(*print_function)(history[a].bord);
		cout<<"# is " <<history[a].move<<endl<<endl;
	}
}

/*
 * function for dealing with the game bord
 */

bool ai::check_cat() { // return false if it is not a cats game
	for(int a =0;a<9;a++) {
		if(bord[a] == ' ')
			return false;
	}
	return true;
}

int ai::check_bord_row (int a, int b, int c) {
	if(bord[a] == bord[b] && bord[a] == bord[c]) {
		if(bord[a] == 'x') return 1;
		else if(bord[a] == 'o') return 2;
		else return 0;
	}else
		return 0;
}

int ai::check_win () {
	if(check_bord_row(0,1,2) != 0) // accross
		return check_bord_row(0,1,2);
	else if(check_bord_row(3,4,5) != 0)
		return check_bord_row(3,4,5);
	else if(check_bord_row(6,7,8) != 0)
		return check_bord_row(6,7,8);
	else if(check_bord_row(0,3,6) != 0) // down
		return check_bord_row(0,3,6);
	else if(check_bord_row(1,4,7) != 0) 
		return check_bord_row(1,4,7);
	else if(check_bord_row(2,5,8) != 0)
		return check_bord_row(2,5,8);
	else if(check_bord_row(0,4,8) != 0) // angle
		return check_bord_row(0,4,8);
	else if(check_bord_row(2,4,6) != 0)
		return check_bord_row(2,4,6);
	else
		return 0;
}

