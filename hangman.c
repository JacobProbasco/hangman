//  Code by jacobprobasco@gmail.com
//  10NOV2015
//  jacobprobasco@outlook.com

#include <stdio.h>
///////CHANGE to ARG c ARG v//////
int main(void){

/* Reset each round */
int play = 1;		// User playing (yes)
int gues = 0;		// Numb. guesses in current round

/* Persistent each round */
int round = 1; 		// Number of rounds  played
int wins = 0;		// Number of wins

char word;			// Word chosen from dictionary

// Random init

// FUNC setup
/* While round != 0;
 * From "~/.words", choose random word, store into an array that is the size of that dictionary word. */
// Count the number of letters in the word.
// Put the number of blanks in the word into an array of the same size.

/* FUNC check_print
 * If (Check for win state)
 * // Optional: Clear the screen.
 * Draw the number of blanks along with correct guesses so far.
 * Prompt and recieve guess. *** only one letter ***
 * Iterate through word finding instances of those letters
 * If found, set print array to that value.
 * Print array
}
