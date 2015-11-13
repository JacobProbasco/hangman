//  Code by jacobprobasco@gmail.com
//  10NOV2015
//  jacobprobasco@outlook.com

////////Change to ~/.words/////////
// Set Default Dictionary File Locaiton
#define DICT_FILE getenv("HOME"), strncat(dict_path, "/.words", 7);

// Set Maximum Acceptable Word Size
#define MAX_WORD_SZ 35  // Size is supercalifragilisticexpialidocious +1 for \n

#include <stdio.h>
#include <errno.h>      // Error Handling
#include <string.h>
#include <stdlib.h>
#include <time.h>

int dict_pick(char *chosen_word, char *d_path, int *err);

int main(int argc, char *argv[]){
    // External resources
    srand((int)time(NULL));             // For dict_pick()
    extern int errno ;                  // Error handling

    char *dict_path = "DICT_FILE";      // Actual path to dictionary file.
    int error_n;                        // Place-holder, error number
    char secr_word[36] = { '\0' };      // Place-holder, secret word

    if(argc > 2){                       // Check for more than one argument, error.
        error_n = errno;
        fprintf(stderr, "Error in opening %s: %s\n", argv[0], strerror(error_n));
        printf("Hangman Usage: %s <dictionary file absolute path>\n If no file is given, dictionary location defaults to DICT_FILE", argv[0]);
        return 7;                       // Argument List too Long.
    }else if(argc == 2){                // Check for user-provided dictionary.
        dict_path = argv[1];            // Set to user-provided path.
    }else{
        // Set default path to Dictionary file.
        dict_path = DICT_FILE
    }
    
    // Pick a word from the dictionary
    dict_pick(secr_word, dict_path, &errno);
    
/*debug*/
    printf("%s is now the secret word!\n", secr_word);
    
    
    
    
}

int dict_pick(char *chosen_word, char *d_path, int *err){

    FILE *dict;                    // Pointer to dictionary file stream.
    dict = fopen(d_path, "r");
    
    // Account for Errors in Opening Dictionary File
    if (dict == NULL){
        fprintf(stderr, " Error opening dictionary file at %s\n %s\n", d_path, strerror(*err));
        return 2;                           // No such file or directory
    }else{
    
        char *tmp_word = NULL;              // Current word in dictionary file.
        size_t tmp_word_sz = 0;             // Size in bytes of current word.
        int l = 1;                          // Line Count
        
        // Cycle through dictionary, pick a word at random, return that word.
        while((int)(tmp_word_sz = getline(&tmp_word, &tmp_word_sz, dict)) != -1){
                   // Populate tmp_word one line at a time until EOF
// debug    printf("CHECKING: %s\n", tmp_word);
            if (tmp_word_sz <= MAX_WORD_SZ && tmp_word_sz > 1){
                // Resavoir sampling to pick a random word from the file.
                if ((rand() / (float)RAND_MAX) <= (1.0 / l)) {
                    strncpy(chosen_word, tmp_word, 36);
// debug            printf("Setting: %s\n", chosen_word);
                }else{
                    continue;
                }
                l++;
            }
            // Pick Word
            else {
                //                printf("Incompatable word in dictionary file, LINE %d.\n\tContinuing without errant word.\n", l);
            }
        }

// BUG - Do error checking on characters
        free(tmp_word);
        fclose(dict);
    }
    return 0;
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
