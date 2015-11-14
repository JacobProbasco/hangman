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
#include <string.h>     // Concatenation of chars
#include <ctype.h>      // Character managment
#include <stdlib.h>
#include <time.h>

int dict_pick(char *chosen_word, char *d_path, int *err);
char get_input(FILE stdin);
int check_guess(char *word, char *disp, char *guess_hist, char guess, int app);
void prnt_array(char *title, char *array);

int main(int argc, char *argv[]){
    
    // External resources
    srand((int)time(NULL));             // For dict_pick()
    extern int errno ;                  // Error handling

    char *dict_path = "DICT_FILE";      // Actual path to dictionary file.
    int error_n;                        // Place-holder, error number
    char secr_word[36] = { '\0' };      // Place-holder, secret word
    
// Manage optional command-line arguments
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
    
/*debug*/   printf("%s is now the secret word!\n", secr_word);
    
// Game Setup
/// Persistent Variables
/// Saved at end of game or on error.
    int playing = 1;
    int round = 0; 		// Number of rounds  played. When negative, game exits.
    int wins = 0;		// Number of wins during this runtime.
    while (playing == 1){
    // Prompt Player to Start Round or continue based on whether this is the initial round.
        if (round > 0){
            printf("Round %d.\nYou have lost %d men so far.\nDo you want to keep playing?\n(y for yes. <!> to quit.)\n", round, (unsigned)round - wins);
        } else {
            printf("ARE YOU READY TO PLAY HANGMAN?\n(y for yes. <!> to quit.)\n");
        }
        
    // Request input
        char input = get_input(*stdin);
        
// Start Move this to get_input
        if (input == ('y' | 'Y')){
            round++;
            
        } else if(input == ('n' | 'N')){
            
        } else if(input == ( '@' )){
            round = -1;
        } else {
            printf("Invalid input.\n(type y for yes or <!> to quit.");
        }
// End Move this to get_input
        
        for ( ;round >= 1; round++){
        // Reset each round
            int appendage = 7;      // Number of body parts left on the man.
            char plyr_guesses[35] = { '\0' };
            char display_string[36] = { '\0' };
            int turns = 1;          // Number of turns.
            
            // Set up Display Arrays
            // Put the number of blanks in the word into an array of the same size.
            for(int i = 0; i < (int)strlen(secr_word); i++){
                if (isalpha(secr_word[i])
                    && (secr_word[i] != '\n')){
                    display_string[i] = '_';
                }else{
                    secr_word[i] = '\0';
                }
            }
            
            for (; turns > 0; turns++){
                
                char *word_str = "The Word:\n";
                prnt_array(word_str, display_string);
                char *guess_str = "Guessed So Far:\n";
                prnt_array(guess_str, plyr_guesses);
                
                char guess = get_input(*stdin);
                int g_result = check_guess(secr_word, display_string, plyr_guesses, guess, appendage);
                
                if (g_result == 0){
// CREATE AND CALL Function to Save round data
                    turns = -1;
                    round = 0;
                    playing = 0;
                }
                
            }
            
        }
        
    }
    return 0;
}

// ADD Stats


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
                    strcpy(chosen_word, tmp_word);
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
        free(tmp_word);
        fclose(dict);
    return 0;
}
}

char get_input(FILE stdin){
    char inpt;
    
    printf("Enter character: ");
    inpt = fgetc(&stdin);

    if (inpt == '!'){
        printf("Are you sure you want to quit? Type @ to confirm; # to play more.\n");
        return get_input(stdin);
        
    }
    else if (inpt == ('@' | '#')){
        printf("See you again soon. Current Hangman stats are:\n");
        exit(0);
        return '@';
    }
    
    if(isalpha(inpt)){
        return inpt;
    }else {
        printf("Your input must be a letter.\n");
        get_input(stdin);
        return inpt;
    }
    return '!';
}


int check_guess(char *word, char *disp, char *guess_hist, char guess, int app){
    int match = 0;          // increments when a match is found.
// X - Check to see if word guessed before
    for (int x = 0; x < (int)strlen(word); x++){
        if (guess == guess_hist[x]){
            printf("You already Guessed that Letter. Try again.\n");
            return 1;       // Returns 1 to game; still playing.
        }
    }
// Y - Check to see if word = the secret word; then check for win.
    for (int y = 0; y < (int)strlen(word); y++){
        if (guess == word[y]){
            disp[y] = guess;        // Set corresponding display character to the guess.
            match++;
            
            int wincrement = 0;
            
            if (disp[y] == word[y]){
                wincrement++;
                if (wincrement == (int)strlen(word)){
                    return 0;       // Return 0; User won.
                }
            } else if (match > 0){
                return 1;           // Return 1; Still Playing
            }
        }
    }
    if (match > 0){
        strncat(guess_hist, &guess, 1);
    } else {
        printf("Incorrect.\n%d appendages left.", app);
        // Add a body part to the gallows
        app++;
        if (app == 6){
            return -1;              // return -1, user lost
        } else {
            return 1;
        }
    }
    return -2;                      // Error
}


void prnt_array(char *title, char *array){
// FLOURISH: Clear Screen to refresh.
// FLOURISH: Print the man to be hung.

    if(title != NULL){
        printf("%s\n", title);
    }
    for(int i=0; i != '\n'; i++){
        printf("%c ", array[i]);
    }
    printf("\n");

}
