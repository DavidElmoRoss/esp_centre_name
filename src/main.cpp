/*
    Title:  Program to generate output to the PC screen
    Author: Your NAME, STUDENT ID, COURSE CODE, Lab Section
    Date:   Today's Date
    Description:    This program will ask for your NAME then output it centered
                    on row 12. This program will also allow for Deleting chars
                    (0x7F).
                    MAX varies the width of your screen - default 80
*/

// Include Section
#include "arduino.h"

// Define Section
#define MAX 80                          // Maximum Screen Size

//Function Prototype Section
void clear(void);                       // function to clear the screen
void position(int x, int y);            // function to position cursor

// Global Variable Section
unsigned char name[MAX];               // Name has MAX number of characters
int i,x;
char input;

void setup()                           // Arduino Setup Function - instructions done only once
{
   Serial.begin(9600);
}

void loop()                            // Arduino LOOP Function - instructions repeated
{ 
  for(;;)                              // endless loop inside loop function
  {
    clear();                            // clear the screen
    position(1,1);                      // position cursor at (1,1)
    i=0;                                // set index of name[] array to 0
    printf("Input ALL your name ? ");   // prompt for user name
    fflush(stdout);                     // flush output to screen
    while (Serial.available() <= 0) ;   // while no characters from keyboard - stay here
    input = (char)Serial.read();        // input variable gets char of what is read from keyboard
    name[0]=input;                      // first element of array gets input char
    (char)Serial.write(input);          // echo this character to screen
    fflush(stdout);                     // flush output to screen
    while(name[i]!=0x0d)                // while not <return> or <enter>
    {
      ++i;                              // move to next element of array
      while (Serial.available() <= 0) ; // while no characters from keyboard - stay here
         input = (char)Serial.read();   // input variable gets char of what is read from keyboard
         name[i]=input;                 // array element i gets input char
         (char)Serial.write(input);     // input character written to output buffer
        fflush(stdout);                 // output buffer flushed to screen
        if(name[i]==0x08)               // if <DEL> char 
        {
        input=name[i];                 // input char gets array value at index i
            --i;                        // move index back one for <DEL>
            --i;                        // move index back one for char
        }
    
    }
    name[i]='\0';                       // replace <return> with <null>

   x=(MAX-i)/2;                         // calculate centre for name
   position(12,x);                      // position cursor at (12,x)
   printf("%s",name);                   // print name on screen
   fflush(stdout);
   printf("\n\nPlease wait 5 seconds ");
   fflush(stdout);                      // output Wait 5 seconds
   
   do                                   // do while loop to empty keyboard input buffer
   {                                    // which is terminated when you hit ENTER '\n'
   while(Serial.available())
   input = (char)Serial.read();
   }while(input!='\n');
   delay(5000);                         // delay 5 seconds or 5000 milliseconds
  }
}
void clear(void)
{
       printf("\e[2J");                    // \e[2J clears the screen
       fflush(stdout);                     // flush output to screen
}
void position(int x, int y)
{
      printf("\e[%d;%dH",x,y);              // position cursor at (x,y)
      fflush(stdout);                       // flush output to screen
}
