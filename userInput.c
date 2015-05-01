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


  mvprintw (0, 0, "Hello, world!");
  int ch;

  while (true)
    {
      clear();
      ch = getch ();
      switch (ch)
	{
	case KEY_LEFT:
	  printw ("Left arrow is pressed\n");
	  break;
	case KEY_RIGHT:
	  printw ("Right arrow is pressed\n");
	case 'x':
	  break;
	default:
	  printw ("The pressed key is ");
	  attron (A_BOLD);
	  printw ("%c", ch);
	  attroff (A_BOLD);
	}
      refresh ();
      sleep (1);
    }
  endwin ();
}

void screenDraw() {
	refresh ();
}
