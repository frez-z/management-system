//
// Created by Farez on 22/1/2022.
//

#ifndef MANAGEMENT_SYSTEM_CONSOLE_H
#define MANAGEMENT_SYSTEM_CONSOLE_H

#define BR "\n" // break line

#define RED "\033[91m" // foreground red
#define GREEN "\033[92m" // foreground green
#define YELLOW "\033[93m" // foreground yellow
#define BLUE "\033[94m" // foreground blue
#define MAGENTA "\033[95m" // foreground magenta
#define CYAN "\033[96m" // foreground cyan
#define WHITE "\033[97m" // foreground white

#define RED_BACK "\033[101m" // background red
#define GREEN_BACK "\033[102m" // background green
#define YELLOW_BACK "\033[103m" // background yellow
#define BLUE_BACK "\033[104m" // background blue
#define MAGENTA_BACK "\033[105m" // background magenta
#define CYAN_BACK "\033[106m" // background cyan
#define WHITE_BACK "\033[107m" // background white

#define RST "\033[0m" // reset colour to default

#define DB_FILE "database\\database.sqlite" // database file
#define DB_DIR "database" // database directory

void createConsoleWindow(short width, short length);

void moveCursor(short x, short y);

void delay(int millisecond);

#endif //MANAGEMENT_SYSTEM_CONSOLE_H
