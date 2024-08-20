#include "kilo.h" 

/*** output ***/ 
void editor_draw_rows()
{
    int y; 
    for(y = 0; y < E.screenrows; y++){
        write(STDOUT_FILENO, "~\r\n", 3); 
    }
}

void editor_refresh_screen()
{
    write(STDOUT_FILENO, "\x1b[2J", 4); 
    write(STDOUT_FILENO, "\x1b[H", 3);

    editor_draw_rows(); 

    write(STDOUT_FILENO, "\x1b[H", 3);
    
}


