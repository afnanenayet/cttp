/* cttp.c   Afnan Enayet
 *
 * The main file for the cttp program. It contains the main function and logic
 * for the dispatch of cttp
 */

#include <stdbool.h>
#include <stdio.h>

/****** function prototypes ******/

bool arg_check(int argc, char *argv[]);
void print_usage();

/****** function definitions ******/

int main(int argc, char *argv[]) {
    bool run = arg_check(argc, argv);

    // If arguments are invalid, print proper usage and exit
    // otherwise start main program
    if (!run) {
        print_usage();
        return 1;
    } else {
        // TODO dispatch program
    }

    return 0;
}

/* Checks the arguments to see if they are valid or not. If they are, the
 * function will return true. It will also print error messages as
 * necessary to stdout/stderr indicating which arguments are invalid
 */
bool arg_check(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "not enough arguments given\n");
        return false;
    } else {
        printf("url: %s%s on port %s\n", argv[1], argv[2], argv[3]);
        return true;
    }
}

/* Prints instructions on how to use the program to STDOUT
*/
void print_usage() {
    printf("usage: cttp [base url] [extra path (optional)] [port (optional, "
            "default: 80)]\n");
}
