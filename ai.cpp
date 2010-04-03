#include "ai.hpp"

/*
 * TODO: in the knowledge set X as first player and o as the second player
 * TODO: Check that the bord is roating corectly
 */

template <typename T, int size> bool equal_arrays (T a[size], T b[size]) {
	//cout<<"checking arrays: "<<size<<endl<<a<<endl<<b;
	for(int i = size-1; i >= 0;i--) {
		if(a[i] != b[i])
			return false;
	}
	return true;
}

int ai::ai_move() {
	int move;
	move = check_can_win();
	if(move != -1) 
		return move;
	move = search_knowledge();
	if(move != -1 && bord[move] == ' ')
		return move;
	move = get_bad_ai_move();
	return move;
}


void ai::ai_learn (bool win) {
	for(int a = history.size();a>=0;a--) {
		history[a].win = win;
		if(ai_was_first == true) {
			for(int i = 8;i>=0;i--) {
				if(history[a].bord[i] == 'x') history[a].bord[i] = 'o';
				else if(history[a].bord[i] == 'o') history[a].bord[i] = 'x';
			}
		}
		knowledge.push_back(history[a]);
	}
	//print_knowledge();
}

void ai::print_knowledge () {
	for (int a = (int)knowledge.size();a>0;a--) {
			(*print_function)(knowledge[a].bord);
			cout<<"# is " <<knowledge[a].move<<endl<<"win: "<<knowledge[a].win<<endl;
		}
}

int ai::search_knowledge () {
	if(knowledge.size() <= 0) return -1;
	char working[9];
	strcpy(working, bord);
	if(ai_was_first == true) {
		for(int i = 0;i<9;i++) {
			if(working[i] == 'x') working[i] = 'o';
			else if (working[i] == 'o') working[i] = 'x';
		}
	}
	bool was_win = false;
	int chose = -1;
	for(int rot = 4;rot>=0;rot--) {
		//cout<<"knowledge size: "<<knowledge.size();
		for(int at = knowledge.size();at > 0;at--) {
			if(equal_arrays<char, 9>(knowledge[at].bord, working) == true) {
				try {
				if(knowledge[at].win == true && was_win == false) {
					chose = knowledge[at].move;
					was_win = true;
					break;
				}else
					chose = knowledge[at].move;
				}catch(char *e) {cout<<e<<endl;}
			}
		}
		chose = roatate(chose,rot);
		if(bord[chose] != ' ') {
			was_win = false;
			chose = -1;
		}
		if (was_win == true) 
			return chose;
		/*
		 * roatate the game bord
		 */
		char ret[9];
		for(int a = 0;a<9;a++)
			ret[a] = working[roatate(a,1)];
		strcpy(working, ret);
	}
	
	return chose;
}

int ai::roatate (int p, int times) {
	for (;times > 0;times--) {
		switch (p) {
		case 0:
			p = 6;
			break;
		case 1:
			p = 3;
			break;
		case 2:
			p = 0;
			break;
		case 3:
			p = 7;
			break;
		case 5:
			p = 1;
			break;
		case 6:
			p = 8;
			break;
		case 7:
			p = 5;
			break;
		case 8:
			p = 2;
			break;
		}
	}
	return p;
}
int ai::get_bad_ai_move () {
	cout<<"random move\n";
	int p = 0;
	int moves[] = {4,0,2,8,6,3,1,5,7};
	/*do {
		p = rand()%9;
	}while (bord[p] == 'x' || bord[p] == 'o');*/
	for(int i=0;bord[p] != ' ';i++) {
		if(i<(int)sizeof(moves))
			p=moves[i];
		else
			p=rand()%9;
	}
	return p;
}
/*
 * check to see if the system can win
 */

int ai::check_can_win () {
	if(check_can_win_row(0,1,2) != -1) // accross
		return check_can_win_row(0,1,2);
	else if(check_can_win_row(3,4,5) != -1)
		return check_can_win_row(3,4,5);
	else if(check_can_win_row(6,7,8) != -1)
		return check_can_win_row(6,7,8);
	else if(check_can_win_row(0,3,6) != -1) // down
		return check_can_win_row(0,3,6);
	else if(check_can_win_row(1,4,7) != -1) 
		return check_can_win_row(1,4,7);
	else if(check_can_win_row(2,5,8) != -1)
		return check_can_win_row(2,5,8);
	else if(check_can_win_row(0,4,8) != -1) // angle
		return check_can_win_row(0,4,8);
	else if(check_can_win_row(2,4,6) != -1)
		return check_can_win_row(2,4,6);
	else
		return -1;
}

int ai::check_can_win_row (int a, int b, int c) {
	if(bord[a] == 'x' || bord[b] =='x' || bord[c] == 'x')
		return -1;
	if (bord[a] == 'o') {
		if(bord[b] == 'o')
			return c;
		else if(bord[c] == 'o')
			return b;
	}else if(bord[b] == 'o' && bord[c] == 'o')
		return a;
	else
		return -1;
	
	return -1;
}
