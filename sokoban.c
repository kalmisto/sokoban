#include <ncurses.h>

#include "sokoban.h"

struct point ak; /* aloituskohta */
struct point nk; /* nykykohta */

int main()
{
	int ch = 0;

	ak.x = 20;
	ak.y = 8;
	initscr();			/* Start curses mode		*/
	raw();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	curs_set(0);			/* hide the cursor		*/
	noecho();			/* Don't echo() while we do getch */

	if (has_colors()) {
		start_color();

		/*
		* Simple color assignment, often all we need.  Color pair 0 cannot
		* be redefined.  This example uses the same value for the color
		* pair as for the foreground color, though of course that is not
		* necessary:
		*/
		init_pair(1, COLOR_BLUE,     COLOR_BLUE);
		init_pair(2, COLOR_GREEN,   COLOR_BLACK);
		init_pair(3, COLOR_YELLOW,  COLOR_CYAN);
		init_pair(4, COLOR_BLUE,    COLOR_WHITE);
		init_pair(5, COLOR_CYAN,    COLOR_MAGENTA);
		init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(7, COLOR_WHITE,   COLOR_GREEN);
	}

	piirra_kentta();
	nk = ak;

	while(ch != 'q') {
		ch = getch();
		kentta[nk.y][nk.x] = ' ';
		kentta[nk.y][nk.x + 1] = ' ';

		if (ch == 'q') {
			break;
		}
		siirra(ch, &nk);
		kentta[nk.y][nk.x] = 'X';
		kentta[nk.y][nk.x + 1] = 'X';
		piirra_kentta();
		refresh();
	}
	endwin();			/* End curses mode		  */

	return 0;
}

void
siirra(int input, struct point *nk) {
	switch (input) {
	case KEY_UP:
		if (kentta[nk->y - 1][nk->x] != '#') {
			if(kentta[nk->y - 1][nk->x] == '[' && kentta[nk->y - 2][nk->x] != '#' && kentta[nk->y - 2][nk->x] != '[') {
				kentta[nk->y - 1][nk->x] = 'X';
				kentta[nk->y - 1][nk->x + 1] = 'X';
				kentta[nk->y - 2][nk->x] = '[';
				kentta[nk->y - 2][nk->x + 1] = ']';
				nk->y = nk->y -1;
				break;
			} else if(kentta[nk->y - 1][nk->x] != '[') {
				kentta[nk->y - 1][nk->x] = 'X';
				kentta[nk->y - 1][nk->x + 1] = 'X';
				nk->y = nk->y -1;
				break;
			}
		}
		break;
	case KEY_RIGHT:
		if (kentta[nk->y][nk->x + 2] != '#') {
			if(kentta[nk->y][nk->x + 2] == '[' && kentta[nk->y][nk->x + 4] != '#' && kentta[nk->y][nk->x + 4] != '[') {
				kentta[nk->y][nk->x + 2] = 'X';
				kentta[nk->y][nk->x + 3] = 'X';
				kentta[nk->y][nk->x + 4] = '[';
				kentta[nk->y][nk->x + 5] = ']';
				nk->x = nk->x + 2;
				break;
			} else if(kentta[nk->y][nk->x + 2] != '[') {
				kentta[nk->y][nk->x + 2] = 'X';
				kentta[nk->y][nk->x + 3] = 'X';
				nk->x = nk->x + 2;
				break;
			}
		}
		break;
	case KEY_LEFT:
		if (kentta[nk->y][nk->x - 2] != '#') {
			if(kentta[nk->y][nk->x - 2] == '[' && kentta[nk->y][nk->x - 4] != '#' && kentta[nk->y][nk->x - 4] != '[') {
				kentta[nk->y][nk->x - 2] = 'X';
				kentta[nk->y][nk->x - 1] = 'X';
				kentta[nk->y][nk->x - 4] = '[';
				kentta[nk->y][nk->x - 3] = ']';
				nk->x = nk->x - 2;
				break;
			} else if(kentta[nk->y][nk->x - 2] != '[') {
				kentta[nk->y][nk->x - 2] = 'X';
				kentta[nk->y][nk->x - 1] = 'X';
				nk->x = nk->x - 2;
				break;
			}
		}
		break;
	case KEY_DOWN:
		if (kentta[nk->y + 1][nk->x] != '#') {
			if(kentta[nk->y + 1][nk->x] == '[' && kentta[nk->y + 2][nk->x] != '#' && kentta[nk->y + 2][nk->x] != '[') {
				kentta[nk->y + 1][nk->x] = 'X';
				kentta[nk->y + 1][nk->x + 1] = 'X';
				kentta[nk->y + 2][nk->x] = '[';
				kentta[nk->y + 2][nk->x + 1] = ']';
				nk->y = nk->y +1;
				break;
			} else if(kentta[nk->y + 1][nk->x] != '[') {
				kentta[nk->y + 1][nk->x] = 'X';
				kentta[nk->y + 1][nk->x + 1] = 'X';
				nk->y = nk->y +1;
				break;
			}
		}
		break;
	}
}

void piirra_kentta(void) {
	int x = 0;
	int y = 0;
	int i = 0;
	char m ;
	for (x = 0; x < 26; x++) {
		for (y = 0; y < 12; y++) {
			move(y, x);
			m = kentta[y][x];
			attrset(COLOR_PAIR(6));
			if (m == '#') {
				attrset(COLOR_PAIR(1));
			}
			else if (m == '(' || m == ')' ) {
				attrset(COLOR_PAIR(2));
			}
			else if (m == '[' || m == ']') {
				attrset(COLOR_PAIR(7));
			}
			else if (m == 'X') {
				attrset(COLOR_PAIR(4));
			}
			addch(kentta[y][x]);
			refresh();
		}
	}
	attrset(COLOR_PAIR(2));
	for (i = 0; i < 8; i++) {
		if (kentta[kohteet[i][1]][kohteet[i][0]] == ' ') {
			move(kohteet[i][1],kohteet[i][0]);
			addch('(');
			move(kohteet[i][1],kohteet[i][0] + 1);
			addch(')');
		}
	}

}

