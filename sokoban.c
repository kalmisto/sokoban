#include <ncurses.h>

char kentta[12][26] = { {' ',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' '},
			{' ',' ','#','#',' ',' ',' ',' ',' ',' ','#','#','#','#',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#'},
			{' ',' ','#','#',' ',' ','[',']',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#'},
			{' ',' ','#','#','#','#','[',']','#','#','#','#','#','#',' ',' ','#','#','#','#',' ',' ',' ',' ','#','#'},
			{' ',' ','#','#',' ',' ',' ',' ','#','#','#','#',' ',' ','[',']',' ',' ','#','#',' ',' ','#','#','#','#'},
			{' ',' ','#','#',' ',' ','[',']','(',')','(',')','(',')','(',')','(',')','(',')',' ',' ','#','#',' ',' '},
			{'#','#','#','#',' ',' ','#','#','#','#','#','#',' ',' ','(',')',' ',' ','#','#',' ',' ','#','#',' ',' '},
			{'#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','[',']','#','#','#','#','#','#','[',']','#','#',' ',' '},
			{'#','#',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ','[',']','X','X','#','#',' ',' '},
			{'#','#','#','#','#','#','#','#','#','#','[',']','#','#',' ',' ','#','#','#','#','#','#','#','#',' ',' '},
			{' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' '},
			{' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' '}};

struct point {
	int y;
	int x;
};

struct point alkukohta;
struct point nykykohta;

int main()
{
	int ch = 0;
	char m;
	int x, y;

	alkukohta.y = 21;
	alkukohta.x = 9;
	initscr();			/* Start curses mode		*/
	raw();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	curs_set(0);			// hide the cursor
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

		void piirra_kentta();
	
	while(ch != 'q')
		ch = getch();			

		switch (ch) {
		case KEY_UP:
			move();
			addch("*");
			break;
		}
		refresh();


    //	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */

	return 0;
}

void 
siirra()

void piirra_kentta() {

	for (y = 0; y < 26; y++) {
		for (x = 0; x < 12; x++) {
			move(x, y);
			char m = kentta[x][y];
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
			addch(kentta[x][y]);
			refresh();
		}
	}
}
