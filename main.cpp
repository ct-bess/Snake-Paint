/* main.cpp
 *  This is a prototype, and just for fun
 */

#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <vector>

using namespace std;

// TODO: Game screen, status screen
WINDOW* wnd;

int init() {

  wnd = initscr();
  cbreak();
  noecho();
  keypad( wnd, 1 );
  nodelay( wnd, 1 );
  curs_set( 0 );

  start_color();

  if ( !has_colors() ) { return -1; }

  //         n, forground(char), background
  init_pair( 0, COLOR_BLACK, COLOR_WHITE );
  init_pair( 1, COLOR_WHITE, COLOR_BLACK );
  init_pair( 2, COLOR_WHITE, COLOR_MAGENTA );
  init_pair( 3, COLOR_YELLOW, COLOR_CYAN );
  init_pair( 4, COLOR_BLACK, COLOR_GREEN );

  return 1;

}

int main( void ) {

  int init_status = init();
  if ( init_status < 0 ) { 

    endwin();
    return 0;

  }

  srand( time( NULL ) );
  int rng = 0;

  int maxx = 0;
  int maxy = 0;

  // Player variables
  int myx = 1;
  int myy = 1;
  int in_char = 0;
  int mydir = 3;
  char mydisp = '@';

  getmaxyx( wnd, maxy, maxx );
  wborder( wnd, 0, 0, 0, 0, 0, 0, 0, 0 );

  attron( A_BOLD );
  attron( COLOR_PAIR( 2 ) );  

  int tick = 0;
  for (;;) {

    // Draw tail
    mvaddch( myy, myx, ' ' );

    in_char = getch();

    if ( in_char != ERR ) {

      switch ( in_char ) {

        case 'q':
          endwin();
          return 0;

        case KEY_UP:
          mydir = 0;
          break;

        case KEY_DOWN:
          mydir = 1;
          break;

        case KEY_LEFT:
          mydir = 2;
          break;

        case KEY_RIGHT:
          mydir = 3;
          break;

      }

    }

    switch ( mydir ) {

      // UP
      case 0:
        --myy;
        break;

      // DOWN
      case 1:
        ++myy;
        break;

      // LEFT
      case 2:
        --myx;
        break;

      // RIGHT
      case 3:
        ++myx;
        break;

    }

    if ( myy < 0 ) {

      myy = maxy - 1;

    }

    if ( myx < 0 ) {

      myx = maxx - 1;

    }

    myy = myy % maxy;
    myx = myx % maxx;

    // Draw head
    mvaddch( myy, myx, mydisp );

    refresh();
    nanosleep((const struct timespec[]){{0, 50000000L}}, NULL);

    // For fun
    ++tick;
    tick = tick % 179;

    rng = ( rand() % 4 ) + 1;
    //if ( ( tick / rng ) < 10 ) {

     //attron( COLOR_PAIR( 3 ) );

    //}

    
    if ( ( tick % 3 ) == 0  ) {

      //mydir = tick % 4;
      switch ( rng ) {

        case 1:
          mydir = 0;
          attron( COLOR_PAIR( 1 ) );
          break;

        case 2:
          mydir = 1;
          attron( COLOR_PAIR( 2 ) );
          break;

        case 3:
          mydir = 2;
          attron( COLOR_PAIR( 3 ) );
          break;

        case 4:
          mydir = 3;
          attron( COLOR_PAIR( 4 ) );
          break;

      }

    }

  } // end event loop

  endwin();
  return 0;

}
