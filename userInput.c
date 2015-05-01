#include <ncurses.h>
#include <unistd.h>

int
main (int argc, char *argv[])
{
  //initializing curses
  initscr ();
  raw ();
  keypad (stdscr, TRUE);
  noecho ();
  curs_set (FALSE);

  //building the window
  WINDOW *local_win;
	int starty = (LINES - 30) / 2;
	int startx = (COLS - 100) / 2;	
	local_win = newwin(30, 100, starty, startx);
        wborder(local_win, '|', '|', '-', '-', '+', '+', '+', '+');
	mvprintw(starty - 1, startx + 40, "PARALLEL PONG SSE693");
	refresh();
	wrefresh(local_win);


  int ch;

  while (true)
    {
      //clear();
      ch = getch ();
      switch (ch)
	{
	case KEY_LEFT:
	  printw ("Left arrow is pressed\n");
	  break;
	case KEY_RIGHT:
	  printw ("Right arrow is pressed\n");
	  break;
	case 'x':
	  endwin ();
	  return(1);
	  break;
	default:
	  printw ("The pressed key is ");
	  attron (A_BOLD);
	  printw ("%c", ch);
	  attroff (A_BOLD);
	}
      //refresh ();
      //sleep (1);
    }
  endwin ();
}

void screenDraw() {
	//Draw paddles
	//Draw Ball
	refresh ();
}
