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
    
    int error_n;            // Error Number Place-holder

// BUG: IMPORT local environment to make relative to home. Import Environment
    
    if(argc > 2){           // Check for more than one argument, error.
        extern int errno ;
        error_n = errno;
        fprintf(stderr, "Error in opening %s: %s\n", argv[0], strerror(error_n));
        printf("Hangman Usage: %s <dictionary file>\n If no file is given, dictionary location defaults to DICT_FILE", argv[0]);
        return 7;           // Argument List too Long.
     }else if(argc == 2){       // Check for user-provided dictionary.
         dict_path = argv[1];       // Set to user-provided path.
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
        return 2;       // No such file or directory
    }else{
// MOVE to FUNC dict_pick

        char *tmp_word = NULL;              // Current word in dictionary file.
        size_t tmp_word_sz = 0;             // Size in bytes of current word.
        int l = 1;                          // Line Count
        
// Cycle through dictionary, pick a word at random, return that word.
        while((int)(tmp_word_sz = getline(&tmp_word, &tmp_word_sz, dict)) != -1){ // Until EOF
            if (tmp_word_sz <= MAX_WORD_SZ && tmp_word_sz > 1){
                // Resivoir sampling
/*
                if (tmp_word  if (rand() % n == 0)){
                    
                }
 
 */
/* Debug */     printf("LINE %d... %zu\tbytes...\tWord: %s", l+1, tmp_word_sz, tmp_word);
                
    
                // Pick Word
            }else {
                printf("Incompatable word in dictionary file, LINE %d.\n\tContinuing without errant word.\n", l);
            }
            l++;
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
