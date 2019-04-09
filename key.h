#include <ncurses.h>
int kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

int key_listener()
{
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    int c=0,c1=0;
    scrollok(stdscr, TRUE);
    while (1) {
        if (kbhit()) {
            c1 = c1 + (int)(getch());

            refresh();
        /*  
              27 + 91 + 65 = 183  -> for up                             \
              27 + 91 + 66 = 184  -> for down                    ========\      JUGAAD KEYBOARD LISTENER
              27 + 91 + 67 = 185  -> for right                   ========/
              27 + 91 + 68 = 186  -> for left                          /
        */ 
            c++;

            if(c==3)
            break;
        }
    }


    switch (c1)
    {
        case 183:
            return 1;
            break;
        case 184:
            return 2;
            break;
        case 185:
            return 3;
            break;
        case 186:
            return 4;
            break;    
    
        default:
            return 0;
            break;
    }
}