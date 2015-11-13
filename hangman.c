//  Code by jacobprobasco@gmail.com
//  10NOV2015
//  jacobprobasco@outlook.com

////////Change to ~/.words/////////
// Set Default Dictionary File Locaiton
#define DICT_FILE "/hangman/words"

// Set Maximum Acceptable Word Size
#define MAX_WORD_SZ 35  // Size is supercalifragilisticexpialidocious +1 for \n

#include <stdio.h>
#include <errno.h>      // Error Handling
#include <string.h>
#include <stdlib.h>
#include <time.h>

int dict_pick(char *chosen_word, char *d_path, int *err);

int main(int argc, char *argv[]){
    srand(time(NULL));      // For picking a random word from the dictionary.

    char *dict_path = "DICT_FILE";   // Actual path to dictionary file.
    int error_n;            // Error Number Place-holder
    char secr_word[36] = { '\0' };
    extern int errno ;
    
    if(argc > 2){           // Check for more than one argument, error.
        error_n = errno;
        fprintf(stderr, "Error in opening %s: %s\n", argv[0], strerror(error_n));
        printf("Hangman Usage: %s <dictionary file>\n If no file is given, dictionary location defaults to DICT_FILE", argv[0]);
        return 7;           // Argument List too Long.
    }else if(argc == 2){       // Check for user-provided dictionary.
        dict_path = argv[1];       // Set to user-provided path.
    }else{
        dict_path = DICT_FILE;
// BUG: IMPORT local environment to make relative to home. Import Environment
    }
    
    dict_pick(secr_word, dict_path, &errno);
    

    
}

int dict_pick(char *chosen_word, char *d_path, int *err){


    FILE *dict;             // Pointer to dictionary file stream.
    
    // Open Dictionary
    
    dict = fopen(d_path, "r");
    
    // Address Errors in Opening Dictionary
    if (dict == NULL){
        fprintf(stderr, " Error opening dictionary file at %s\n %s\n", d_path, strerror(*err));
        return 2;       // No such file or directory
    }else{
        // MOVE to FUNC dict_pick
        
        char *tmp_word = NULL;              // Current word in dictionary file.
        size_t tmp_word_sz = 0;             // Size in bytes of current word.
        int l = 1;                          // Line Count
        
        // Cycle through dictionary, pick a word at random, return that word.
        while((int)(tmp_word_sz = getline(&tmp_word, &tmp_word_sz, dict)) != -1){ // Until EOF
            /*debug*/   printf("CHECKING: %s\n", tmp_word);
            if (tmp_word_sz <= MAX_WORD_SZ && tmp_word_sz > 1){
                // Resavoir sampling to pick a random word from the file.
                if ((rand() / (float)RAND_MAX) <= (1.0 / l)) {
                    strncpy(chosen_word, tmp_word, 36);
                    /*debug*/           printf("Setting: %s\n", chosen_word);
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
        /* Debug */         printf("%s is now the secret word! at %zu\tbytes...\tWord: %s", chosen_word, tmp_word_sz, tmp_word);
        //BUG - Do error checking on characters
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
