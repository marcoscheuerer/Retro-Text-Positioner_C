#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <time.h>
#include "my_art.h"
#include "my_color.h"

#define clear() printf("\x1b[2J\x1b[H");
#define DEFAULT_TEXT "Hello, World!!!"
#define DEFAULT_COLOR "mixed"
#define DEFAULT_ROW 30
#define DEFAULT_COL 1
#define DEBUG 0

void setLetter(int xPos, int yPos, char letter, char* color);
void setText(int xPos, int yPos, char *text, char* color);
void setTextColor(char* color);
void resetColor();
void textToUpper(char *text);
void textToLower(char *text);
int elementsInRetroLetter(const wchar_t *retroLetter);
int maxWidthRetroLetter(const wchar_t *retroLetter);
const wchar_t* convertToRetroLetter(const wchar_t *ptrLetter, char letter);

enum BOOL { false, true };

/******************************************************************************/
/* Main Function                                                              */
/******************************************************************************/
int main(void)
{
    setlocale(LC_ALL, "");
    enum BOOL anotherText = true;
    char choice;

    srand(time(0));

    char letter,
         num[4],
         text[20],
         color[12];
    int xPos, 
        yPos;

    do
    {
        strcpy(text, " ");
        strcpy(color, " ");
        clear();

        printf("Funny Retro-Text-Positioner\n"
            "===========================\n\n");
        printf("Text to print %s[default: %s]%s: ", BLUE, DEFAULT_TEXT, DEFAULT);
        fgets(text, 20, stdin);
        printf("Available Colors:\nred, green, blue, yellow, magenta, "
            "cyan, black, white, mixed\n");
        printf("Please choose a color you like %s[default: %s}%s: ", BLUE, DEFAULT_COLOR, DEFAULT);
        fgets(color, 12, stdin);
        printf("Row number to print %s[default: %d]%s: ", BLUE, DEFAULT_ROW, DEFAULT);
        fgets(num, 4, stdin);
        //getchar();
        xPos = atoi(num);
        //xPos = getchar(); getchar();
        printf("Column number to print %s[default: %d]%s: ", BLUE, DEFAULT_COL, DEFAULT);
        fgets(num, 4, stdin);
        //getchar();
        yPos = atoi(num);


        if(text[0] == '\n')
            strcpy(text, DEFAULT_TEXT);
        else
            text[strlen(text)-1] = '\0';

        if(color[0] == '\n')
            strcpy(color, DEFAULT_COLOR);
        if(xPos == 0)
            xPos = DEFAULT_ROW;
        if(yPos == 0)
            yPos = DEFAULT_COL;

        //yPos = getchar(); getchar();
        textToLower(color);

        //printf(color);
        setText(xPos, yPos, text, color);

        
        printf("\n\nDo you want to write a new Text [y/n]: ");
        choice = getchar(); getchar();

        if(choice == 'n') 
        {
            printf("no");
            anotherText = false;
        }

    } while (anotherText);

    clear();
    printf("\n\n\t🚀  Thanks for getting retro, after so many years!  🚀\n\n");

    return 0;
}

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/    

/**
 * @brief Prints a retrostyled letter on the console display
 *
 * @param xPos x-Position of letter
 * @param yPos y-Position of letter
 * @param letter ASCII-letter to convert
 * @param color Color of retrostyled letter
 */
void setLetter(int xPos, int yPos, char letter, char* color)
{
    const wchar_t *ptrLetter = NULL;
    wchar_t element;
    int i;
    int row = 0;
    int count = 1;
    int xPos2=0, yPos2=0;

    ptrLetter = convertToRetroLetter(ptrLetter, letter);
    
    setTextColor(color);

    for(i = 0; ptrLetter[i] != '\0'; i++)
    {
        //setTextColor(color);

        element = ptrLetter[i];

        if(element == '\n')
        {
            element = ' ';
            row +=1;
            count = 0;
        }

        xPos2 = xPos + row;
        yPos2 = yPos + count;
        printf("\x1b[%d;%dH%lc", xPos2, yPos2, element);
        count += 1;
    }

    fflush(stdout);

    resetColor();
}

/**
 * @brief Prints the complete text on the screen
 * 
 * @param xPos x-Position of text
 * @param yPos y-Position of letter
 * @param text ascii-text to print retrostyled on screen
 * @param color color of the text
 */
void setText(int xPos, int yPos, char *text, char* color)
{
    int i;
    int space = 1;
    int furtherPos = 0;
    int x = xPos;
    int y = yPos;
    int maxLength;
    const wchar_t *retroLetter = NULL;

    textToUpper(text);
    for(i = 0; text[i] != '\0'; i++)
    {
        retroLetter = convertToRetroLetter(retroLetter, text[i]);
        setLetter(x, y + furtherPos, text[i], color);
        maxLength = maxWidthRetroLetter(retroLetter);
        #if DEBUG
            printf("Width: %d ",maxLength);
        #endif

        furtherPos += (maxLength + space);
    }
}

/**
 * @brief Sets the color of the text with defined colors
 * 
 * @param color color to pick from a color list
 */
void setTextColor(char* color)
{
    int randNumber;
    char letterColor[12] = { '\0' };

    const char *ptrColor = NULL;

    const char colors[][10] = { "black", "red", "green", "yellow", "blue", "magenta", "cyan", "white" };

    strcpy(letterColor, color);

    if(strcmp(color, "mixed") == 0)
    {
        randNumber = rand() % 8;
        strcpy(letterColor, colors[randNumber]);
    }

    if(strcmp(letterColor, "black") == 0)
        ptrColor = BLACK;
    else if(strcmp(letterColor, "red") == 0)
        ptrColor = RED;
    else if(strcmp(letterColor, "green") == 0)
        ptrColor = GREEN;
    else if(strcmp(letterColor, "yellow") == 0)
        ptrColor = YELLOW;
    else if(strcmp(letterColor, "blue") == 0)
        ptrColor = BLUE;
    else if(strcmp(letterColor, "magenta") == 0)
        ptrColor = MAGENTA;
    else if(strcmp(letterColor, "cyan") == 0)
        ptrColor = CYAN;
    else if(strcmp(letterColor, "white") == 0)
        ptrColor = WHITE;
    else
        ptrColor = DEFAULT;

    printf("%s", ptrColor);
}

/**
 * @brief Resets the color to the system color
 * 
 */
void resetColor()
{
    printf("%s", RESET);
}

/**
 * @brief Change the complete text to uppercase
 * 
 * @param text text to change into upper letters
 */
void textToUpper(char *text)
{
    int i;

    for(i = 0; text[i] != '\0'; i++)
        text[i] = toupper(text[i]);
    text[i] = '\0';
}

/**
 * @brief Change the complete text to lowercase
 * 
 * @param text text to change into lower letters
 */
void textToLower(char *text)
{
    int i;

    for(i = 0; text[i] != '\n'; i++)
        text[i] = tolower(text[i]);
    text[i] = '\0';
}

/**
 * @brief Calculates the complete elements in a retrostyled letter
 * 
 * @param retroLetter Retrostyled letter to calculate
 * @return Returns the complete elements of a resrostyled letter
 */
int elementsInRetroLetter(const wchar_t *retroLetter)
{
    return (int)wcslen(retroLetter);
}

/**
 * @brief Calculates the maximum elements in a line of the retrostyled letter
 * 
 * @param retroLetter Retrostyled letter to calculate
 * @return Returns the complete elements of a resrostyled letter
 */
int maxWidthRetroLetter(const wchar_t *retroLetter)
{
    int i;
    int lineLength = 0;
    int maxLineLength = 0;
    int maxElements = elementsInRetroLetter(retroLetter);

    for(i = 0; i < maxElements; i++)
    {
        lineLength++;
        
        if(retroLetter[i] == '\n')
        {
            if(maxLineLength < lineLength)
                maxLineLength = lineLength;

            lineLength = 0;
        }
    }

    return maxLineLength;
}

/**
 * @brief Converts ASCII Letter to retrostyled letter
 * 
 * @param ptrLetter Retrostyled letter
 * @param letter ASCII letter
 * @return Returns the retrostyled letter chosen by ASCII letter
 */
const wchar_t* convertToRetroLetter(const wchar_t *ptrLetter, char letter)
{
    switch(letter)
    {
        case ' ': ptrLetter = EMPTY; break;
        case 'A': ptrLetter = retroA; break;
        case 'B': ptrLetter = retroB; break;
        case 'C': ptrLetter = retroC; break;
        case 'D': ptrLetter = retroD; break;
        case 'E': ptrLetter = retroE; break;
        case 'F': ptrLetter = retroF; break;
        case 'G': ptrLetter = retroG; break;
        case 'H': ptrLetter = retroH; break;
        case 'I': ptrLetter = retroI; break;
        case 'J': ptrLetter = retroJ; break;
        case 'K': ptrLetter = retroK; break;
        case 'L': ptrLetter = retroL; break;
        case 'M': ptrLetter = retroM; break;
        case 'N': ptrLetter = retroN; break;
        case 'O': ptrLetter = retroO; break;
        case 'P': ptrLetter = retroP; break;
        case 'Q': ptrLetter = retroQ; break;
        case 'R': ptrLetter = retroR; break;
        case 'S': ptrLetter = retroS; break;
        case 'T': ptrLetter = retroT; break;
        case 'U': ptrLetter = retroU; break;
        case 'V': ptrLetter = retroV; break;
        case 'W': ptrLetter = retroW; break;
        case 'X': ptrLetter = retroX; break;
        case 'Y': ptrLetter = retroY; break;
        case 'Z': ptrLetter = retroZ; break;
        case '!': ptrLetter = retroEXMARK; break;
        case '?': ptrLetter = retroQMARK; break;
        case ',': ptrLetter = retroCOMMA; break;
        case '.': ptrLetter = retroDOT; break;
        case '-': ptrLetter = retroDASH; break;
    }
    return ptrLetter;
}