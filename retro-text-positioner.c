#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
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

int main(void)
{
    setlocale(LC_ALL, "");
    enum BOOL anotherText = true;
    char choice;

    char letter,
         text[20] = DEFAULT_TEXT,
         color[12] = DEFAULT_COLOR;
    int xPos = DEFAULT_ROW, 
        yPos = DEFAULT_COL;

    do
    {
    
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
        scanf("%d", &xPos);
        printf("Column number to print %s[default: %d]%s: ", BLUE, DEFAULT_COL, DEFAULT);
        scanf("%d", &yPos);
        textToLower(color);

        //printf(color);
        setText(xPos, yPos, text, color);

        getchar();
        printf("\n\nDo you want to write a new Text [y/n]: ");
        choice = getchar(); getchar();

        if(choice == 'n') 
        {
            printf("no");
            anotherText = false;
        }

    } while (anotherText);

    clear();
    printf("\n\nThanks for getting retro, ║ after so many years!\n\n");

    return 0;
}
    
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
    resetColor();
}

void setTextColor(char* color)
{
    const char *ptrColor = NULL;

    if(strcmp(color, "black") == 0)
        ptrColor = BLACK;
    else if(strcmp(color, "red") == 0)
        ptrColor = RED;
    else if(strcmp(color, "green")==0)
        ptrColor = GREEN;
    else if(strcmp(color, "yellow")==0)
        ptrColor = YELLOW;
    else if(strcmp(color, "blue")==0)
        ptrColor = BLUE;
    else if(strcmp(color, "magenta")==0)
        ptrColor = MAGENTA;
    else if(strcmp(color, "cyan")==0)
        ptrColor = CYAN;
    else if(strcmp(color, "white")==0)
        ptrColor = WHITE;
    else
        ptrColor = DEFAULT;

    printf("%s", ptrColor);
}

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

void resetColor()
{
    printf("%s", RESET);
}

void textToUpper(char *text)
{
    int i;

    for(i = 0; text[i] != '\n'; i++)
        text[i] = toupper(text[i]);
    text[i] = '\0';
}

void textToLower(char *text)
{
    int i;

    for(i = 0; text[i] != '\n'; i++)
        text[i] = tolower(text[i]);
    text[i] = '\0';
}

int elementsInRetroLetter(const wchar_t *retroLetter)
{
    return (int)wcslen(retroLetter);
}

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