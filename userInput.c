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
      ch = getch ();
      switch (ch)
	{
	case KEY_LEFT:
	case KEY_UP:
	  //printw ("Left arrow is pressed\n");
	  player.y++;
	  break;
	case KEY_RIGHT:
	case KEY_DOWN:
	  //printw ("Right arrow is pressed\n");
	  player.y--;
	  break;
	case 'x':
	  endwin ();
	  return(1);
	  break;
	default:
		screenDraw();
	}
    }
  endwin ();
}

void screenDraw() {
	//Clear the contents of the window
	wclear(local_win);

	int i;
	//Draw paddles
	for (i = 0; i < player.height; i++) {
		mvprintw(starty + player.height, startx + player.x, "||");
	}

        for (i = 0; i < ai.height; i++) {
                mvprintw(starty + ai.height, startx + ai.x, "||");
        }


	//Draw ball
	mvprintw(starty + ball.y, startx + ball.x, "o");

	//Draw screen
	refresh ();
	wrefresh(local_win);
}
