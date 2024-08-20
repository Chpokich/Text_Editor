
#include "kilo.h"


struct editor_config E;
/*** init ***/ 
void init_editor()
{ 
    if(get_window_size(&E.screenrows, &E.screencols) == -1)
        die("getwindowsize"); 
}

int main()
{
    enable_raw_mode(); 
    init_editor(); 
   
   while(1){ 
    editor_refresh_screen(); 
    editor_process_keypress();  
   }

    return 0; 
}
