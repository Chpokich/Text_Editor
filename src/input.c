#include "kilo.h" 

/*** input ***/ 
void editor_process_keypress()
{
    char c = editor_read_key(); 
    switch(c){
        case CTRL_KEY('q'):
        write(STDOUT_FILENO, "\x1b[2J", 4); 
        write(STDOUT_FILENO, "\x1b[H", 3); 
        exit(0);
        break; 
    }

}


