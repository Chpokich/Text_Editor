#ifndef KILO 
#define KILO 


/*** includes ***/ 
#include <sys/ioctl.h>
#include <unistd.h> 
#include <termios.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <ctype.h> 
#include <errno.h> 

/*** defines ***/ 
#define CTRL_KEY(k) ((k) & 0x1f)


/*data*/ 
struct editor_config{
  int screenrows;
  int screencols; 
  struct termios orig_termios; 
}; 
extern struct editor_config E;

/*terminal*/
void die(const char *s); 
void disable_raw_mode();
void enable_raw_mode();
char editor_read_key(); 
int get_cursor_position(int *rows, int *cols);
int get_window_size(int *rows, int *cols);

/*output*/ 
void editor_draw_rows(); 
void editor_refresh_screen(); 

/*input*/ 
void editor_process_keypress(); 
#endif 

