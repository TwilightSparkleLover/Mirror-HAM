/*
 * Author: Peter Schraut - www.console-dev.de
*/
/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"
#include "bgtext.h"

#include "gfx/Charset.raw.c"
#include "gfx/Charset.pal.c"

/*********************************************************************************
 * Global Variables & Constants
 ********************************************************************************/
 
/*
 * The background text class
*/
CBgText g_BgText;

/*
 * Array with information about what
 * char has what tile index
 * Keep in mind, if you use "map optimizing" with gfx2gba, this wont work
 * as good as you think ...
*/
const TCharIndex g_Chars[] =
{
    {'A',   0},
    {'B',   1},
    {'C',   2},
    {'D',   3},
    {'E',   4},
    {'F',   5},
    {'G',   6},
    {'H',   7},
    {'I',   8},
    {'J',   9},
    {'K',  10},
    {'L',  11},
    {'M',  12},
    {'N',  13},
    {'O',  14},
    {'P',  15},
    {'Q',  16},
    {'R',  17},
    {'S',  18},
    {'T',  19},
    {'U',  20},
    {'V',  21},
    {'W',  22},
    {'X',  23},
    {'Y',  24},
    {'Z',  25},
    {'a',  26},
    {'b',  27},
    {'c',  28},
    {'d',  29},
    {'e',  30},
    {'f',  31},
    {'g',  32},
    {'h',  33},
    {'i',  34},
    {'j',  35},
    {'k',  36},
    {'l',  37},
    {'m',  38},
    {'n',  39},
    {'o',  40},
    {'p',  41},
    {'q',  42},
    {'r',  43},
    {'s',  44},
    {'t',  45},
    {'u',  46},
    {'v',  47},
    {'w',  48},
    {'x',  49},
    {'y',  50},
    {'z',  51},
    {'0',  52},
    {'1',  53},
    {'2',  54},
    {'3',  55},
    {'4',  56},
    {'5',  57},
    {'6',  58},
    {'7',  59},
    {'8',  60},
    {'9',  61},
    {'ß',  62},
    {'Ö',  63},
    {'Ä',  64},
    {'Ü',  65},
    {'ö',  66},
    {'ä',  67},
    {'ü',  68},
    {',',  69},
    {'.',  70},
    {'-',  71},
    {';',  72},
    {':',  73},
    {' ',  74},
    {'#',  75},
    {'^',  76},
    {'+',  77},
    {'*',  78},
    {'@',  79},
    {'!',  80},
    {'"',  81},
    {'§',  82},
    {'$',  83},
    {'\%', 84},
    {'&',  85},
    {'/',  86},
    {'(',  87},
    {')',  88},
    {'=',  89},
    {'?',  90},
    {'|',  91},
    {'\\', 92},
    {'<',  93},
    {'>',  94},
    {'[',  95},
    {']',  96},
    {'{',  97},
    {'}',  98},
    {'¹',  99},
    {'²', 100},
    {'³', 101},
    {'°', 102},
    {' ', 103},
};
    
/*
 * Fill the background text information structure
 * This is required by the class !
*/
const TBgTextInfo g_BgTextInfo =
{
    1,                          // Background we want to use for text output
    8,                          // Tile Width
    8,                          // Tile Height
    (u8*)Charset_Tiles,         // Pointer to tile data
    sizeof(Charset_Tiles),      // Tile data size
    (u16*)Charset_Palette,      // Pointer to palette
    -1,                         // Palette Index, if it's a 16 color palette, -1 = 256 color palette
    256,                        // PaletteSize
    sizeof(g_Chars)/2,          // Number of chars
    (TCharIndex*)g_Chars        // Pointer to CharIndex Information
};

/*********************************************************************************
 * Program entry point
 ********************************************************************************/
int main(void)
{
   // Initialize HAMlib
   // Then we call the single most important function of ham, ham_Init .
   // This function must be called first thing when working with HAMlib,
   // because all ham_* functions will only work correctly after this has been called.
   // Behaviour of HAMlib is undefined if you comment this out.
   ham_Init();

   // Sets the GBAs BGMode to the value specified in bgno
   ham_SetBgMode(0);

   // Init the background text class
   g_BgText.Init(g_BgTextInfo);

   // Print text using the class
   g_BgText.Print   (3,  1, "C++ class to draw text");
   g_BgText.Print   (1,  2, "--------------------------");
   g_BgText.Print   (1,  4, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
   g_BgText.Print   (1,  5, "abcdefghijklmnopqrstuvwxyz");
   g_BgText.Print   (1,  6, "0123456789öäüÖÄÜß,.-;: #^+");
   g_BgText.Print   (1,  7, "*!\"§$\%&/()=?|\\<>[]{}¹²³°");
   g_BgText.PrintEx (1, 11, "1+1 = \"%d\"", 1+1);
   g_BgText.Print   (6, 18, "www.console-dev.de");

   // Endless loop
   while(true)
   {
   }

   return 0;
}


/* END OF FILE */
