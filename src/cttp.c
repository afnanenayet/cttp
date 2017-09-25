/* cttp.c   Afnan Enayet
 *
 * The main file for the cttp program. It contains the main function and logic 
 * for the dispatch of cttp
 */

#include <stdio.h>
#include <stdbool.h>

/****** function prototypes ******/

bool arg_check(int argc, char *argv[]);

/****** function definitions ******/

int main(int argc, char *argv[])
{
    bool run = arg_check(argc, argv);
    return run;
}

/* Checks the arguments to see if they are valid or not. If they are, the 
 * function will return true. It will also print error messages as 
 * necessary to stdout/stderr indicating which arguments are invalid
 */
bool arg_check(int argc, char *argv[])
{
    if (argc < 2) {
        printf("not enough arguments given\n");
        return false;
    } else {
        printf("url: %s\n", argv[1]);
        return true;
    }
}

