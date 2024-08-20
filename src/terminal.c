#include "kilo.h"

/*** terminal ***/ 

void die(const char *s)
{
    write(STDOUT_FILENO, "\x1b[2J", 4); 
    write(STDOUT_FILENO, "\x1b[H", 3); 

    perror(s); 
    exit(1); 
}

void disable_raw_mode(){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios); 
}

void enable_raw_mode()
{
    if(tcgetattr(STDIN_FILENO, &E.orig_termios) == -1)
        die("tcgetattr");

    atexit(disable_raw_mode);  
    
    struct termios raw = E.orig_termios; 

    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON); 
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8); 
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); 
    raw.c_cc[VMIN] = 0;  
    raw.c_cc[VTIME] = 1; 

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr"); 
        
}

char editor_read_key()
{
    int nread; 
    char c; 
    while((nread = read(STDIN_FILENO, &c, 1)) != 1){
        if(nread == -1 && errno != EAGAIN)
            die("read");
    }
    return c; 
}

int get_cursor_position(int *rows, int *cols)
{
    if(write(STDOUT_FILENO, "\x1b[6n", 4) != 4)
        return -1; 
    printf("\r\n"); 
    char c;
    while(read(STDIN_FILENO, &c, 1) == 1){
        if(iscntrl(c)){
            printf("%d\r\n", c);
        }else{
            printf("%d ('%c')\r\n",c,c);
        }
    }
   editor_read_key(); 
  return -1;  
}

int get_window_size(int *rows, int *cols){
    struct winsize ws; 

    if(1 || ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0){
        if(write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12)
            return -1;
        return get_cursor_position(rows, cols); 
    }else{
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return 0;  
    }
}


