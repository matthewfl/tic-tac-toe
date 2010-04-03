#ifndef AI_HPP_
#define AI_HPP_

#include <iostream>
using namespace std;
#include <vector>
#include <string.h>

/* 0|1|2
 * -+-+-
 * 3|4|5
 * -+-+-
 * 6|7|8
 * 
 * The AI is O
 * and the player is X
 */


struct moves {
	int move;
	char bord[9];
	bool win;
};

class ai {
private:
	char bord[9];
	bool ai_was_first;
	vector<moves> history;
	void (*print_function)(char[9]);
	int (*user_input)();
	/*
	 * the funcitons for handling the bord and the user
	 */
	void print () {
		(*print_function)(bord);
	}
	void print_history ();
	int user () {
		int move = 4;
		do {
			try {
				move = (*user_input)();
			}catch (char *e) {}
		}while (bord[move] == 'x' || bord[move] == 'o');
		struct moves a;
		strcpy(a.bord, bord);
		a.move = move;
		history.push_back(a);
		bord[move] = 'x';
		return move;
	}
	int check_win ();
	int check_bord_row (int a, int b, int c);
	bool check_cat();
	/*
	 * functions for the ai and parts of the learing system
	 */
	vector<moves> knowledge;
	int ai_move();
	int check_can_win ();
	int check_can_win_row (int a, int b, int c);
	int get_bad_ai_move ();
	void ai_learn (bool win);
	int search_knowledge ();
	void print_knowledge ();
	
	int roatate (int p, int times);
	void roatate_bord (char *move[9]);
public:
	ai (void (*print)(char[9]), int (*user)()) :
		print_function(print), user_input(user) // print function, get user input
		{
			reset();
		} 
	
	int start (bool ai_first);
	void reset ();
	~ai () {}
};

#endif /*AI_HPP_*/
