#ifndef __MY_COLOR_H__
#define __MY_COLOR_H__

const char *RESET = "\033[00m";

// Forground Colors in Terminal
const char *BLACK    = "\033[30m";
const char *RED      = "\033[31m";
const char *GREEN    = "\033[32m";
const char *YELLOW   = "\033[33m";
const char *BLUE     = "\033[34m";
const char *MAGENTA  = "\033[35m";
const char *CYAN     = "\033[36m";
const char *WHITE    = "\033[37m";
const char *DEFAULT  = "\033[39m";  // depends on OS

// Background Colors in Terminal
const char *BLACK_BG   = "\033[40m";
const char *RED_BG     = "\033[41m";
const char *GREEN_BG   = "\033[42m";
const char *YELLOW_BG  = "\033[43m";
const char *BLUE_BG    = "\033[44m";
const char *MAGENTA_BG = "\033[45m";
const char *CYAN_BG    = "\033[46m";
const char *WHITE_BG    = "\033[47m";
const char *DEFAULT_BG = "\033[49m";     // depends on OS

// Additional BG-Colors in Terminal
const char *DARK_GRAY_ABG    = "\033[100m";
const char *LIGHT_RED_ABG    = "\033[101m";
const char *LIGHT_GREEN_ABG  = "\033[102m";
const char *YELLOW_ABG       = "\033[103m";
const char *LIGHT_BLUE_ABG   = "\033[104m";
const char *LIGHT_PURPLE_ABG = "\033[105m";
const char *TEAL_ABG         = "\033[106m";
const char *WHITE_ABG        = "\033[107m";

#endif
