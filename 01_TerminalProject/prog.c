#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define KEY_ESC 27


int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    if (argc != 2) {
        printf("Usage : %s [file]\n", argv[0]);
        return 0;
    }

    struct stat sb;
    if (stat(argv[1], &sb) == -1) {
        printf("Cannot access to file : %s \n", argv[1]);
        return 0;
    }

    FILE *file = fopen(argv[1], "r");
    char *buf = (char *) malloc(sb.st_size);

    int size=0;
    char **lines = NULL;

    while (!feof(file))
    {
        memset(buf, 0, sizeof(buf));
        fgets(buf, sb.st_size, file);

        if (!lines)
            lines = malloc(++size * sizeof(char*));
        else
            lines = realloc(lines, ++size * sizeof(char *));

        lines[size-1] = strdup(buf);
    }
    fclose(file);

    initscr();

    start_color();
    init_pair(1,  COLOR_WHITE,   COLOR_RED);
    init_pair(2,  COLOR_GREEN,   COLOR_BLACK);
    init_pair(3,  COLOR_BLUE,    COLOR_YELLOW);

    cbreak();
    keypad(stdscr, TRUE);
    refresh();

    attrset(COLOR_PAIR(1));
    printw("File: %s, len: %ld", argv[1], sb.st_size);

    int startx  = 4, starty  = 3,
        scrollx = 0, scrolly = 0;

    int height = (LINES - starty) / 2,
        width  = (COLS  - startx) / 2;

    WINDOW *box_win  = newwin(height+1, width+1, starty, startx);

    wrefresh(box_win);

    int num_len = sprintf(buf, "%d", size);
    sprintf(buf, "%%%dd: %%.%ds", num_len, width-num_len-3);
    char *mask = strdup(buf);

    int l, ch;
    char *str;
    const char *key = "";
    while (ch != KEY_ESC)
    {
        wclear(box_win);

        for (l = 0; l < height; l++) {
            str = (l+scrolly < size && scrollx < strlen(lines[l+scrolly])) ? lines[l+scrolly]+scrollx : "";
            mvwprintw(box_win, l+1, 1, mask, l+scrolly+1, str);
        }

        wattron(box_win, COLOR_PAIR(2));
        box(box_win, 0, 0);
        mvwprintw(box_win, 0, 2, "%s", key);
        wattroff(box_win, COLOR_PAIR(2));
        wrefresh(box_win);

        switch (ch = getch()) {
            case KEY_RIGHT: scrollx ++;  break;
            case KEY_DOWN:  scrolly ++;  break;
            case KEY_NPAGE: scrolly += height;  break;
            case KEY_UP:    scrolly -= (scrolly > 0) ? 1 : 0;  break;
            case KEY_LEFT:  scrollx -= (scrollx > 0) ? 1 : 0;  break;
            case KEY_PPAGE: scrolly -= (scrolly < height) ? scrolly : height;  break;
        }
        key = keyname(ch);
    }

    endwin();

    free(buf);
    free(mask);

    while (size > 0)
        free(lines[--size]);

    return 0;
}
