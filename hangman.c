//  Code by jacobprobasco@gmail.com
//  10NOV2015
//  jacobprobasco@outlook.com

////////Change to ~/.words/////////
// Set Default Dictionary File Locaiton
#define DICT_FILE "/hangman/words"

// Set Maximum Acceptable Word Size
#define MAX_WORD_SZ 36  // Size is supercalifragilisticexpialidocious +2

#include <stdio.h>
#include <errno.h>      // Error Handling
#include <string.h>
#include <stdlib.h>
#include <time.h>

// void dict_pick(FILE *dict, long dict_sz, char s_word);
// int check_print(char guess, char s_word, int round);

int main(int argc, char *argv[]){
    // ADD Random init initialize


    FILE *dict;             // Pointer to dictionary file stream.
    char *dict_path = "DICT_FILE";   // Actual path to dictionary file.
    char *tmp_word = NULL;  // Current word in dictionary file.
    size_t tmp_len = 0;     // Length of current word.
    ssize_t word_sz;
    
    int error_n;            // Error Number Place-holder

// BUG: IMPORT local environment to make relative to home. Import Environment
    
    if(argc > 2){           // Check for more than one argument, error.
        extern int errno ;
        error_n = errno;
        fprintf(stderr, "Error in opening %s: %s\n", argv[0], strerror(error_n));
        printf("Hangman Usage: %s <dictionary file>\n If no file is given, dictionary location defaults to DICT_FILE", argv[0]);
        return 7;           // Argument List too Long.
     }else if(argc == 2){       // Check for user-provided dictionary.
         dict_path = argv[1]; // Set to user-provided path.
     }else{
         dict_path = DICT_FILE;
     }
    
    // Open Dictionary

    dict = fopen(dict_path, "r");
    
    // Address Errors in Opening Dictionary
    if (dict == NULL){
        extern int errno ;
        error_n = errno;
        fprintf(stderr, " Error opening dictionary file at %s\n %s\n", dict_path, strerror(error_n));
        return 2;           // No such file or directory
    }else{
        for (int i = 0 ; i >= 0; i++){  // Counter for line number
            while ((word_sz = getline(&tmp_word, &tmp_len, dict)) != -1) {
                if (word_sz <= MAX_WORD_SZ && word_sz > 1){
    /* Debug */     printf("Length of Current line is: %zu bytes.\n", word_sz);
    /* Debug */     printf("%s", tmp_word);
                } else if (word_sz > 36 || word_sz <= 1){
                    printf("Found word of incompatible size on line %s in dictionary file.\nContinuing without errant word.", tmp_word);
                }
            }
        }
        free(tmp_word);
        fclose(dict);
        exit(0);
    }
}

/*
// Reset each round
int play = 1;		// User playing (yes)
int gues = 0;		// Numb. guesses in current round

// Persistent each round
int round = 1; 		// Number of rounds  played
int wins = 0;		// Number of wins

char word;			// Word chosen from dictionary

// Random init

// FUNC setup
// While round != 0;
// From "~/.words", choose random word, store into an array that is the size of that dictionary word. */
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
*/
