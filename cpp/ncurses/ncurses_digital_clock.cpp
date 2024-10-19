#include <ncurses.h>
#include <unistd.h>
#include <ctime>
#include <cstring>
#include <iostream>
#include <algorithm>

const std::string MAP[5][10] = {
    {"000", "  1", "222", "333", "4 4", "555", "666", "777", "888", "999"},
    {"0 0", "  1", "  2", "  3", "4 4", "5  ", "6  ", "  7", "8 8", "9 9"},
    {"0 0", "  1", "222", "333", "444", "555", "666", "  7", "888", "999"},
    {"0 0", "  1", "2  ", "  3", "  4", "  5", "6 6", "  7", "8 8", "  9"},
    {"000", "  1", "222", "333", "  4", "555", "666", "  7", "888", "  9"},
};

int fila, columna;

void print_digit(int digit) {
    for (int r = 0; r < 5; r++) {
        move(fila + r, columna);
        printw("%s", MAP[r][digit].data());
    }
}

void print_colon() {
    move(fila + 1, columna);
    printw("%s", ":");
    move(fila + 3, columna);
    printw("%s", ":");
}

void print_clock(int X) {
    int d0 = X / 10, d1 = X % 10;
    print_digit(d0);
    columna += 4;
    print_digit(d1);
    columna += 4;
}

int main() {
    initscr();      // Initialize ncurses
    noecho();       // Disable echoing of input characters
    curs_set(0);    // Hide cursor

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);

    time_t now; tm *t;
    int d0, d1, X;
    const char* line;
    while (true) {
        now = time(0);
        t = localtime(&now);
        //printw("%02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec);

        fila = 1;
        columna = 1;
        move(fila, columna); // Move cursor to top-left corner

        attron(A_BOLD | COLOR_PAIR(1));
        // Hours
        print_clock(t->tm_hour);
        print_colon();
        columna += 2;

        // Minutes
        print_clock(t->tm_min);
        print_colon();
        columna += 2;

        // Seconds
        print_clock(t->tm_sec);
        attroff(A_BOLD | COLOR_PAIR(1));

        refresh(); // Refresh the screen
        usleep(100000); // Delay for 100 milliseconds
    }

    endwin(); // End ncurses mode

    return 0;
}