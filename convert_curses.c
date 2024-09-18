
/****************************************************************************

        Program: convert.c

         Author: Scott L. Fehrman, System Analyst
                 PrimeService
                 One Oakbrook Terrace
                 Suite 502
                 Oakbrook Terrace, IL 60181
                 (708) 953-9250

       Function: utility to convert english to metric and vis-versa

          Input: screen, user prompting

         Output: screen, formatted report

      System(s): Sun Microsystems, Inc.       O/S: SunOS 4.0.3 BSD 4.2 unix

          Notes: this program utilitizes the unix "curses" screen management
                 system. when compiling this program the curses and termcap
                 libraries must be linked into the executable code. compile 
                 this program like the following example: 
                          "# cc <prg_name>.c -lcurses -ltermcap"

        History: ( date / rev / by / description )

        01-01-87  0.0  slf  Primos FORTRAN 77 program (Amoco Chemicals)
        01-01-90  1.0  slf  Raw port to "C" (Primos & SunOS)
        05-16-91  2.0  slf  Use unix "curses" screen driver for menus
        06-05-91  2.1  slf  "Mass" was called "Weight" 
                            new category: "acceleration"
                            put main choices in alphabetical order
        09-17-24  2.2  slf  add int return type to main() with return 0

****************************************************************************/

/*** header files ***/

#include <fcntl.h>          
#include <sys/types.h>      
#include <sys/stat.h>       
#include <sys/file.h>       
#include <stdio.h>          
#include <string.h>         
#include <ctype.h>          
#include <curses.h>                /*** UNIX screen control ***/

/*** define fixed values ***/

#define   NUM_ROW  12
#define   NUM_COL  55
#define   OFF_ROW  3
#define   OFF_COL  10
#define   ORG_ROW  (LINES/2) - (NUM_ROW/2) - OFF_ROW
#define   ORG_COL  (COLS/2) - (NUM_COL/2) - OFF_COL
#define   FRAME_X  '*'
#define   FRAME_Y  '*'
#define       MAX  20
#define    DIVIDE  0 
#define  MULTIPLY  1
#define   CELSIUS  2
#define     FAHRN  3

/*** prototypes ***/

void window_acceleration();
void window_area();
void window_density();
void window_energy();
void window_force();
void window_length();
void window_mass();
void window_power();
void window_pressure();
void window_speed();
void window_temperature();
void window_volume();
void window_conversion();
void init_window_env();
void close_window_env();
int get_value();

/*** global variables ***/

   WINDOW   *Main, *Catg, *Conv;

/**********************************************************************/
int main()
/**********************************************************************/
{
   char cMenu_Option = '\0';
   int iFinished = FALSE;
   init_window_env();
   wclear(Main);
   box(Main,FRAME_Y,FRAME_X);
   wmove(Main,5,2);
   mvwprintw(Main,1,1," CONVERT                               rev (2.1_slf) ");
   mvwprintw(Main,3,1,"      (a) ... Acceleration     (g) ... Mass");     
   mvwprintw(Main,4,1,"      (b) ... Area             (h) ... Power");
   mvwprintw(Main,5,1,"      (c) ... Density          (i) ... Pressure");
   mvwprintw(Main,6,1,"      (d) ... Energy           (j) ... Speed");
   mvwprintw(Main,7,1,"      (e) ... Force            (k) ... Temperature");
   mvwprintw(Main,8,1,"      (f) ... Length           (l) ... Volume");
   mvwprintw(Main,10,1,"         <CR> ... Quit     Selection: ");
   do {
      wrefresh(Main);
      cMenu_Option = wgetch(Main);
      switch ( cMenu_Option ) {
         case 'a': case 'A': window_acceleration(); break;
         case 'b': case 'B': window_area();         break;
         case 'c': case 'C': window_density();      break;
         case 'd': case 'D': window_energy();       break;
         case 'e': case 'E': window_force();        break;
         case 'f': case 'F': window_length();       break;
         case 'g': case 'G': window_mass();         break;
         case 'h': case 'H': window_power();        break;
         case 'i': case 'I': window_pressure();     break;
         case 'j': case 'J': window_speed();        break;
         case 'k': case 'K': window_temperature();  break;
         case 'l': case 'L': window_volume();       break;
         case '\n':          iFinished = TRUE;      break;
         default: break;
      }
      touchwin(Main);
   } while ( !iFinished );
   close_window_env();
   return 0;
}

/**********************************************************************/
void window_acceleration()
/**********************************************************************/
{
   int iFinished = FALSE;
   int iOperator;
   float fFactor;
   char szFrom[MAX], szTo[MAX];
   char cOption;
   wclear(Catg); box(Catg,FRAME_Y,FRAME_X);
   mvwprintw(Catg,1,1,"          --->     ACCELERATION      <---        ");
   mvwprintw(Catg,4,1,"  (a) ... m/sec sq.     -      ft/sec sq. ... (c)");
   mvwprintw(Catg,5,1,"  (b) ... m/sec sq.     -      in/sec sq. ... (d)");
   mvwprintw(Catg,8,1,"          <CR> ... Quit          Selection: ");
   do {
      wrefresh(Catg);
      cOption = wgetch(Catg);
      switch ( cOption ) {
         case 'a': case 'A': 
            strcpy(szFrom,"m/sec sq."); strcpy(szTo,"ft/sec sq.");
            fFactor = 0.3048; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'b': case 'B':
            strcpy(szFrom,"m/sec sq."); strcpy(szTo,"in/sec sq.");
            fFactor = 0.02540; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'c': case 'C': 
            strcpy(szFrom,"ft/sec sq."); strcpy(szTo,"m/sec sq.");
            fFactor = 0.3048; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'd': case 'D': 
            strcpy(szFrom,"in/sec sq."); strcpy(szTo,"m/sec sq.");
            fFactor = 0.02540; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case '\n':          iFinished = TRUE;      break;
         default: break;
      }
      if ( iFinished ) {
         wclear(Catg); wrefresh(Catg);
      }
      else {
         touchwin(Catg);
      }
   } while ( !iFinished );
   return;
}

/**********************************************************************/
void window_area()
/**********************************************************************/
{
   int iFinished = FALSE;
   int iOperator;
   float fFactor;
   char szFrom[MAX], szTo[MAX];
   char cOption;
   wclear(Catg); box(Catg,FRAME_Y,FRAME_X);
   mvwprintw(Catg,1,1,"           --->         AREA         <---        ");
   mvwprintw(Catg,3,1,"   (a) ... sq. centimeters  -  sq. inches ... (d)");
   mvwprintw(Catg,4,1,"   (b) ... sq. meters       -   sq. yards ... (e)");
   mvwprintw(Catg,5,1,"   (c) ... sq. kilometers   -   sq. miles ... (f)");
   mvwprintw(Catg,7,1,"           <CR> ... Quit        Selection: ");
   do {
      wrefresh(Catg);
      cOption = wgetch(Catg);
      switch ( cOption ) {
         case 'a': case 'A': 
            strcpy(szFrom,"sq. centimeters"); strcpy(szTo,"sq. inches");
            fFactor = 6.4516; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'b': case 'B':
            strcpy(szFrom,"sq. meters"); strcpy(szTo,"sq. yards");
            fFactor = 0.83612736; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'c': case 'C': 
            strcpy(szFrom,"sq. kilometers"); strcpy(szTo,"sq. miles");
            fFactor = 2.50; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'd': case 'D': 
            strcpy(szFrom,"sq. inches"); strcpy(szTo,"sq. centimeters");
            fFactor = 6.4516; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'e': case 'E': 
            strcpy(szFrom,"sq. yards"); strcpy(szTo,"sq. meters");
            fFactor = 0.83612736; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'f': case 'F': 
            strcpy(szFrom,"sq. miles"); strcpy(szTo,"sq. kilometers");
            fFactor = 2.50; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case '\n':          iFinished = TRUE;      break;
         default: break;
      }
      if ( iFinished ) {
         wclear(Catg); wrefresh(Catg);
      }
      else {
         touchwin(Catg);
      }
   } while ( !iFinished );
   return;
}

/**********************************************************************/
void window_density()
/**********************************************************************/
{
   int iFinished = FALSE;
   int iOperator;
   float fFactor;
   char szFrom[MAX], szTo[MAX];
   char cOption;
   wclear(Catg); box(Catg,FRAME_Y,FRAME_X);
   mvwprintw(Catg,1,1,"      --->             DENSITY             <---    ");
   mvwprintw(Catg,2,1,"                (mass / cubic length)             ");
   mvwprintw(Catg,4,1,"  (a) ... grams/centimeter   -  pounds/inch ... (d)");
   mvwprintw(Catg,5,1,"  (b) ... grams/centimeter   -  pounds/foot ... (e)");
   mvwprintw(Catg,6,1,"  (c) ... kilograms/meter    -  pounds/foot ... (f)");
   mvwprintw(Catg,8,1,"          <CR> ... Quit        Selection: ");
   do {
      wrefresh(Catg);
      cOption = wgetch(Catg);
      switch ( cOption ) {
         case 'a': case 'A': 
            strcpy(szFrom,"grams/cubic cm"); strcpy(szTo,"lbs/cubic inch");
            fFactor = 27.67783006; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'b': case 'B':
            strcpy(szFrom,"grams/cubic cm"); strcpy(szTo,"lbs/cubic foot");
            fFactor = 0.01601794; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'c': case 'C': 
            strcpy(szFrom,"kilograms/cubic m"); strcpy(szTo,"lbs/cubic foot");
            fFactor = 16.01794009; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'd': case 'D': 
            strcpy(szFrom,"lbs/cubic inch"); strcpy(szTo,"grams/cubic cm");
            fFactor = 27.67783006; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'e': case 'E': 
            strcpy(szFrom,"lbs/cubic foot"); strcpy(szTo,"grams/cubic cm");
            fFactor = 0.01601794; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'f': case 'F': 
            strcpy(szFrom,"lbs/cubic foot"); strcpy(szTo,"kilograms/cubic m");
            fFactor = 16.01794009; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case '\n':          iFinished = TRUE;      break;
         default: break;
      }
      if ( iFinished ) {
         wclear(Catg); wrefresh(Catg);
      }
      else {
         touchwin(Catg);
      }
   } while ( !iFinished );
   return;
}

/**********************************************************************/
void window_energy()
/**********************************************************************/
{
   int iFinished = FALSE;
   int iOperator;
   float fFactor;
   char szFrom[MAX], szTo[MAX];
   char cOption;
   wclear(Catg); box(Catg,FRAME_Y,FRAME_X);
   mvwprintw(Catg,1,1,"             --->      ENERGY      <---        ");
   mvwprintw(Catg,4,1,"     (a) ... BTUs     -     foot/pounds ... (b)");
   mvwprintw(Catg,7,1,"             <CR> ... Quit          Selection: ");
   do {
      wrefresh(Catg);
      cOption = wgetch(Catg);
      switch ( cOption ) {
         case 'a': case 'A': 
            strcpy(szFrom,"BTUs"); strcpy(szTo,"foot/pounds");
            fFactor = 0.00128535; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'b': case 'B':
            strcpy(szFrom,"foot/pounds"); strcpy(szTo,"BTUs");
            fFactor = 0.00128535; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case '\n':          iFinished = TRUE;      break;
         default: break;
      }
      if ( iFinished ) {
         wclear(Catg); wrefresh(Catg);
      }
      else {
         touchwin(Catg);
      }
   } while ( !iFinished );
   return;
}

/**********************************************************************/
void window_force()
/**********************************************************************/
{
   int iFinished = FALSE;
   int iOperator;
   float fFactor;
   char szFrom[MAX], szTo[MAX];
   char cOption;
   wclear(Catg); box(Catg,FRAME_Y,FRAME_X);
   mvwprintw(Catg,1,1,"          --->          FORCE          <---        ");
   mvwprintw(Catg,3,1,"  (a) ... newtons           -        pounds ... (c)");
   mvwprintw(Catg,4,1,"  (b) ... newton/meters     -    pound/feet ... (d)");
   mvwprintw(Catg,7,1,"          <CR> ... Quit          Selection: ");
   do {
      wrefresh(Catg);
      cOption = wgetch(Catg);
      switch ( cOption ) {
         case 'a': case 'A': 
            strcpy(szFrom,"newtons"); strcpy(szTo,"pounds");
            fFactor = 4.44839858; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'b': case 'B':
            strcpy(szFrom,"newton/meters"); strcpy(szTo,"pound/feet");
            fFactor = 14.59; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'c': case 'C': 
            strcpy(szFrom,"pounds"); strcpy(szTo,"newtons");
            fFactor = 4.44839858; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'd': case 'D': 
            strcpy(szFrom,"pound/feet"); strcpy(szTo,"newton/meters");
            fFactor = 14.59; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case '\n':          iFinished = TRUE;      break;
         default: break;
      }
      if ( iFinished ) {
         wclear(Catg); wrefresh(Catg);
      }
      else {
         touchwin(Catg);
      }
   } while ( !iFinished );
   return;
}

/**********************************************************************/
void window_length()
/**********************************************************************/
{
   int iFinished = FALSE;
   int iOperator;
   char cOption;
   char szFrom[MAX], szTo[MAX];
   float fFactor;
   wclear(Catg); box(Catg,FRAME_Y,FRAME_X);
   mvwprintw(Catg,1,1,"              --->      LENGTH      <---        ");
   mvwprintw(Catg,3,1,"      (a) ... millimeters    -    inches ... (d)");
   mvwprintw(Catg,4,1,"      (b) ... meters         -      feet ... (e)");
   mvwprintw(Catg,5,1,"      (c) ... kilometers     -     miles ... (f)");
   mvwprintw(Catg,7,1,"              <CR> ... Quit        Selection: ");
   do {
      wrefresh(Catg);
      cOption = wgetch(Catg);
      switch ( cOption ) {
         case 'a': case 'A': 
            strcpy(szFrom,"millimeters"); strcpy(szTo,"inches");
            fFactor = 25.4; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'b': case 'B':
            strcpy(szFrom,"meters"); strcpy(szTo,"feet");
            fFactor = 0.3048; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'c': case 'C': 
            strcpy(szFrom,"kilometers"); strcpy(szTo,"miles");
            fFactor = 1.609344; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'd': case 'D': 
            strcpy(szFrom,"inches"); strcpy(szTo,"millimeters");
            fFactor = 25.4; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'e': case 'E': 
            strcpy(szFrom,"feet"); strcpy(szTo,"meters");
            fFactor = 0.3048; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'f': case 'F': 
            strcpy(szFrom,"miles"); strcpy(szTo,"kilometers");
            fFactor = 1.609344; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case '\n':          iFinished = TRUE;      break;
         default: break;
      }
      if ( iFinished ) {
         wclear(Catg); wrefresh(Catg);
      }
      else {
         touchwin(Catg);
      }
   } while ( !iFinished );
   return;
}

/**********************************************************************/
void window_mass()
/**********************************************************************/
{
   int iFinished = FALSE;
   int iOperator;
   float fFactor;
   char szFrom[MAX], szTo[MAX];
   char cOption;
   wclear(Catg); box(Catg,FRAME_Y,FRAME_X);
   mvwprintw(Catg,1,1,"              --->       MASS       <---        ");
   mvwprintw(Catg,3,1,"      (a) ... grams        -      ounces ... (d)");
   mvwprintw(Catg,4,1,"      (b) ... grams        -      pounds ... (e)");
   mvwprintw(Catg,5,1,"      (c) ... kilograms    -      pounds ... (f)");
   mvwprintw(Catg,7,1,"                <CR> ... Quit        Selection: ");
   do {
      wrefresh(Catg);
      cOption = wgetch(Catg);
      switch ( cOption ) {
         case 'a': case 'A': 
            strcpy(szFrom,"grams"); strcpy(szTo,"ounces");
            fFactor = 28.349523125; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'b': case 'B':
            strcpy(szFrom,"grams"); strcpy(szTo,"pounds");
            fFactor = 453.5923699; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'c': case 'C': 
            strcpy(szFrom,"kilograms"); strcpy(szTo,"pounds");
            fFactor = 0.4535923699; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'd': case 'D': 
            strcpy(szFrom,"ounces"); strcpy(szTo,"grams");
            fFactor = 28.349523125; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'e': case 'E': 
            strcpy(szFrom,"pounds"); strcpy(szTo,"grams");
            fFactor = 453.5923699; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'f': case 'F': 
            strcpy(szFrom,"pounds"); strcpy(szTo,"kilograms");
            fFactor = 0.4535923699; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case '\n':          iFinished = TRUE;      break;
         default: break;
      }
      if ( iFinished ) {
         wclear(Catg); wrefresh(Catg);
      }
      else {
         touchwin(Catg);
      }
   } while ( !iFinished );
   return;
}

/**********************************************************************/
void window_power()
/**********************************************************************/
{
   int iFinished = FALSE;
   int iOperator;
   float fFactor;
   char szFrom[MAX], szTo[MAX];
   char cOption;
   wclear(Catg); box(Catg,FRAME_Y,FRAME_X);
   mvwprintw(Catg,1,1,"             --->       POWER       <---        ");
   mvwprintw(Catg,4,1,"     (a) ... BTUs/hour - foot-lbs/second ... (b)");
   mvwprintw(Catg,7,1,"             <CR> ... Quit          Selection: ");
   do {
      wrefresh(Catg);
      cOption = wgetch(Catg);
      switch ( cOption ) {
         case 'a': case 'A': 
            strcpy(szFrom,"BTUs/hour"); strcpy(szTo,"foot-lbs/second");
            fFactor = 4.62748727; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'b': case 'B':
            strcpy(szFrom,"foot-lbs/second"); strcpy(szTo,"BTUs/hour");
            fFactor = 4.62748727; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case '\n':          iFinished = TRUE;      break;
         default: break;
      }
      if ( iFinished ) {
         wclear(Catg); wrefresh(Catg);
      }
      else {
         touchwin(Catg);
      }
   } while ( !iFinished );
   return;
}

/**********************************************************************/
void window_pressure()
/**********************************************************************/
{
   int iFinished = FALSE;
   int iOperator;
   float fFactor;
   char szFrom[MAX], szTo[MAX];
   char cOption;
   wclear(Catg); box(Catg,FRAME_Y,FRAME_X);
    mvwprintw(Catg,1,1,"          --->        PRESSURE         <---        ");
   mvwprintw(Catg,2,1,"               ( force / sq. length )              ");
   mvwprintw(Catg,4,1," (a) ... newton/m   (Pa)  - pound/in  (psi) ... (c)");
   mvwprintw(Catg,5,1," (b) ... newton/mm  (mPa) - pound/in  (psi) ... (d)");
   mvwprintw(Catg,9,1,"         <CR> ... Quit      Selection: ");
   do {
      wrefresh(Catg);
      cOption = wgetch(Catg);
      switch ( cOption ) {
         case 'a': case 'A': 
            strcpy(szFrom,"newton/m (Pa)"); strcpy(szTo,"pound/in (psi)");
            fFactor = 6896.5517; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'b': case 'B':
            strcpy(szFrom,"newton/mm (mPa)"); strcpy(szTo,"pound/in (psi)");
            fFactor = 0.0068965517; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'c': case 'C': 
            strcpy(szFrom,"pound/in (psi)"); strcpy(szTo,"newton/m (Pa)");
            fFactor = 6896.5517; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'd': case 'D': 
            strcpy(szFrom,"pound/in (psi)"); strcpy(szTo,"newton/mm (mPa)");
            fFactor = 0.0068965517; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case '\n':          iFinished = TRUE;      break;
         default: break;
      }
      if ( iFinished ) {
         wclear(Catg); wrefresh(Catg);
      }
      else {
         touchwin(Catg);
      }
   } while ( !iFinished );
   return;
}

/**********************************************************************/
void window_speed()
/**********************************************************************/
{
   int iFinished = FALSE;
   int iOperator;
   float fFactor;
   char szFrom[MAX], szTo[MAX];
   char cOption;
   wclear(Catg); box(Catg,FRAME_Y,FRAME_X);
   mvwprintw(Catg,1,1,"          --->          SPEED          <---        ");
   mvwprintw(Catg,3,1,"  (a) ... meters/second     -   feet/second ... (c)");
   mvwprintw(Catg,4,1,"  (b) ... kilometers/hour   -    miles/hour ... (d)");
   mvwprintw(Catg,7,1,"          <CR> ... Quit          Selection: ");
   do {
      wrefresh(Catg);
      cOption = wgetch(Catg);
      switch ( cOption ) {
         case 'a': case 'A': 
            strcpy(szFrom,"meters/second"); strcpy(szTo,"feet/second");
            fFactor = 0.30478513; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'b': case 'B':
            strcpy(szFrom,"kilometers/hour"); strcpy(szTo,"miles/hour");
            fFactor = 1.60926939; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'c': case 'C': 
            strcpy(szFrom,"feet/second"); strcpy(szTo,"meters/second");
            fFactor = 0.30478513; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'd': case 'D': 
            strcpy(szFrom,"miles/hour"); strcpy(szTo,"kilometers/hour");
            fFactor = 1.60926939; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case '\n':          iFinished = TRUE;      break;
         default: break;
      }
      if ( iFinished ) {
         wclear(Catg); wrefresh(Catg);
      }
      else {
         touchwin(Catg);
      }
   } while ( !iFinished );
   return;
}

/**********************************************************************/
void window_temperature()
/**********************************************************************/
{
   int iFinished = FALSE;
   int iOperator;
   float fFactor;
   char szFrom[MAX], szTo[MAX];
   char cOption;
   wclear(Catg); box(Catg,FRAME_Y,FRAME_X);
   mvwprintw(Catg,1,1,"             --->    TEMPERATURE     <---        ");
   mvwprintw(Catg,4,1,"     (a) ... celsius     -      farenheit ... (b)");
   mvwprintw(Catg,7,1,"             <CR> ... Quit        Selection: ");
   do {
      wrefresh(Catg);
      cOption = wgetch(Catg);
      switch ( cOption ) {
         case 'a': case 'A': 
            strcpy(szFrom,"celsius"); strcpy(szTo,"farenheit");
            fFactor = 6.4516; iOperator = CELSIUS;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'b': case 'B':
            strcpy(szFrom,"farenheit"); strcpy(szTo,"celsius");
            fFactor = 0.83612736; iOperator = FAHRN;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case '\n':          iFinished = TRUE;      break;
         default: break;
      }
      if ( iFinished ) {
         wclear(Catg); wrefresh(Catg);
      }
      else {
         touchwin(Catg);
      }
   } while ( !iFinished );
   return;
}

/**********************************************************************/
void window_volume()
/**********************************************************************/
{
   int iFinished = FALSE;
   int iOperator;
   float fFactor;
   char szFrom[MAX], szTo[MAX];
   char cOption;
   wclear(Catg); box(Catg,FRAME_Y,FRAME_X);
   mvwprintw(Catg,1,1,"          --->          VOLUME        <---        ");
   mvwprintw(Catg,3,1,"  (a) ... milliliters       - fluid ounces ... (h)");
   mvwprintw(Catg,4,1,"  (b) ... liters            - cubic inches ... (i)");
   mvwprintw(Catg,5,1,"  (c) ... liters            -      gallons ... (j)");
   mvwprintw(Catg,6,1,"  (d) ... liters            -   cubic feet ... (k)");
   mvwprintw(Catg,7,1,"  (e) ... cubic meters      -   cubic feet ... (l)");
   mvwprintw(Catg,8,1,"  (f) ... cubic meters      -      gallons ... (m)");
   mvwprintw(Catg,9,1,"  (g) ... cubic centimeters - cubic inches ... (n)");
   mvwprintw(Catg,10,1,"         <CR> ... Quit      Selection: ");
   do {
      wrefresh(Catg);
      cOption = wgetch(Catg);
      switch ( cOption ) {
         case 'a': case 'A': 
            strcpy(szFrom,"milliliters"); strcpy(szTo,"fluid ounces");
            fFactor = 29.57353; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'b': case 'B':
            strcpy(szFrom,"liters"); strcpy(szTo,"cubic inches");
            fFactor = 0.016387064; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'c': case 'C': 
            strcpy(szFrom,"liters"); strcpy(szTo,"gallons");
            fFactor = 3.785411784; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'd': case 'D':
            strcpy(szFrom,"liters"); strcpy(szTo,"cubic feet");
            fFactor = 28.31684396; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'e': case 'E':
            strcpy(szFrom,"cubic meters"); strcpy(szTo,"cubic feet");
            fFactor = 0.028316846592; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'f': case 'F':
            strcpy(szFrom,"cubic meters"); strcpy(szTo,"gallons");
            fFactor = 0.00378541; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'g': case 'G':
            strcpy(szFrom,"cubic centimeters"); strcpy(szTo,"cubic inches");
            fFactor = 16.387064; iOperator = DIVIDE;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'h': case 'H': 
            strcpy(szFrom,"fluid ounces"); strcpy(szTo,"milliliters");
            fFactor = 29.57353; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'i': case 'I': 
            strcpy(szFrom,"cubic inches"); strcpy(szTo,"liters");
            fFactor = 0.016387064; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'j': case 'J': 
            strcpy(szFrom,"gallons"); strcpy(szTo,"liters");
            fFactor = 3.785411784; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'k': case 'K':
            strcpy(szFrom,"cubic feet"); strcpy(szTo,"liters");
            fFactor = 28.31684396; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'l': case 'L':
            strcpy(szFrom,"cubic feet"); strcpy(szTo,"cubic meters");
            fFactor = 0.028316846592; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'm': case 'M':
            strcpy(szFrom,"gallons"); strcpy(szTo,"cubic meters");
            fFactor = 0.00378541; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case 'n': case 'N':
            strcpy(szFrom,"cubic inches"); strcpy(szTo,"cubic centimeters");
            fFactor = 16.387064; iOperator = MULTIPLY;
            window_conversion(szFrom,szTo,fFactor,iOperator);
            break;
         case '\n':          iFinished = TRUE;      break;
         default: break;
      }
      if ( iFinished ) {
         wclear(Catg); wrefresh(Catg);
      }
      else {
         touchwin(Catg);
      }
   } while ( !iFinished );
   return;
}

/**********************************************************************/
void window_conversion(szFrom, szTo, fFactor, iOperator)
/**********************************************************************/
char *szFrom, *szTo;
float fFactor;
int iOperator;
{
   int iRow = 5, iCol = 24;
   float fValue = 0.0;
   wclear(Conv);
   box(Conv,FRAME_Y,FRAME_X);
   mvwprintw(Conv,2,1,"            %s to %s", szFrom, szTo);
   mvwprintw(Conv,5,1," %20s: ", szFrom);
   mvwprintw(Conv,6,1," %20s: ", szTo);
   mvwprintw(Conv,9,1," <CR> ... Quit  Value: ");
   wrefresh(Conv);
   while ( get_value(iRow+4,iCol,&fValue) ) {
      mvwprintw(Conv,iRow,iCol,"%g           ",fValue);
      switch ( iOperator ) {
         case DIVIDE: 
            mvwprintw(Conv,iRow+1,iCol,"%g           ",fValue/fFactor);
            break;
         case MULTIPLY: 
            mvwprintw(Conv,iRow+1,iCol,"%g           ",fValue*fFactor);
            break;
         case CELSIUS:
            mvwprintw(Conv,iRow+1,iCol,"%g           ",(fValue*9.0/5.0)+32.0);
            break;
         case FAHRN:
            mvwprintw(Conv,iRow+1,iCol,"%g           ",(fValue-32.0)*5.0/9.0);
            break;
         default: break;
      }
      wrefresh(Conv);
   }
   wclear(Conv); wrefresh(Conv);
   return;
}

/**********************************************************************/
int get_value(iRow,iCol,fValue)
/**********************************************************************/
int iRow, iCol;
float *fValue;
{
   char cChar;
   int iDone = FALSE;
   int iReturn_Value = FALSE;
   *fValue = 0.0;
   echo();
   mvwprintw(Conv,iRow,iCol,"                              "); 
   wmove(Conv,iRow,iCol); wrefresh(Conv); 
   wscanw(Conv,"%g\n",fValue); fflush(stdin);
   if ( *fValue != 0 ) iReturn_Value = TRUE;
   noecho();
   return(iReturn_Value);
}

/**********************************************************************/
void init_window_env()
/**********************************************************************/
{
   initscr();
   noecho();
   cbreak();
   Main = newwin(NUM_ROW, NUM_COL, ORG_ROW, ORG_COL);
   Catg = newwin(NUM_ROW, NUM_COL, ORG_ROW+(1*OFF_ROW), ORG_COL+(1*OFF_COL));
   Conv = newwin(NUM_ROW, NUM_COL, ORG_ROW+(2*OFF_ROW), ORG_COL+(2*OFF_COL));
   refresh();
   return;
}

/**********************************************************************/
void close_window_env()
/**********************************************************************/
{
   clear();refresh();
   nocbreak();
   echo();
   endwin();
   return;
}
