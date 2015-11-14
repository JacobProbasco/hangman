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
void check_guess(char *word, char *disp, char *guess_hist, char guess, int app);
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
    
/*debug*/
    printf("%s is now the secret word!\n", secr_word);
    
    // Persistent Throughout Play - Will be saved at end of game
    int round = 0; 		// Number of rounds  played
    int wins = 0;		// Number of wins during this runtime.
    
    // Reset each round
    int game = 1;       // User playing game (yes)
    int appendage;      // Number of body parts left on the man.
    char plyr_guesses[35] = { '\0'};
    char display_string[36] = { '\0' };
    
    while (game == 1){
        // Set up Display Arrays
        for(int i = 0; secr_word[i] != '\n'; i++){
            if (isalpha(secr_word[i])){
                display_string[i] = '_';
            }else{
                secr_word[i] = '\0';
            }
        }
        // Start Play
        if (game > 1){
            printf("Round %d.\nYou have lost %d men so far.\nDo you want to keep playing?\n(y for yes. <!> to quit.)\n", round, (unsigned)round - wins);
        } else {
            printf("ARE YOU READY TO PLAY HANGMAN?\n(y for yes. <!> to quit.)\n");
        }
        
        char input = get_input(*stdin);
        
        if (input == ('y' | 'Y')){
            round++;
        } else {
            game = 0;
        }

    while (round >= 1){
        appendage = 7;
        while (appendage > 0){
            char *word_str = "The Word:\n";
            prnt_array(word_str, display_string);
            char *guess_str = "Guessed So Far:\n";
            prnt_array(guess_str, plyr_guesses);
            
            char guess = get_input(*stdin);
            
            check_guess(secr_word, display_string, plyr_guesses, guess, appendage);

            }
            

            
        }

        }
        return 0;
    }
    
     // Random init
     
     // FUNC setup
     // While round != 0;

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
        get_input(stdin);
        return '\0';
    }
    else if (inpt == ('@' | '#')){
        printf("See you again soon. Current Hangman stats are:\n");
        exit(0);
        return '$';
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


void check_guess(char *word, char *disp, char *guess_hist, char guess, int app){
// X - Check to see if word = the secret word

    int match = 0; // increments when a match is found.
    
    for (int x = 0; x < (int)strlen(word); x++){
        // If guess is secret word
        if (guess == word[x]){
            // Make sure it wasn't guessed before
            for (int y = 0; y < (int)strlen(guess_hist); y++){
                if (guess == guess_hist[y]){
                    printf("You already Guessed that Letter. Try again.");
                    x = 100;
                    y = 100;
                    break;
                } else if (match > 0){
                    disp[x] = guess;
                } else if (match == 0){
                    match++;
                    disp[x] = guess;
                    
                }
            }
        }
        strncat(guess_hist, &guess, 1);

    }
    
    if (match == 0){
        --app;
        printf("Incorrect.\n%d appendages left.", app);
        return;
    }
    
}

void prnt_array(char *title, char *array){
    if(title != NULL){
        printf("%s\n", title);
    }
    for(int i=0; i != '\n'; i++){
        printf("%c ", array[i]);
    }
    printf("\n");
}
