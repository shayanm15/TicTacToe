#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ttt.h"

int main( int argc, char **argv) {

    if (argc < 2) {
        exit(1);
    }

    init_boards();

    init_board(START_BOARD);

    join_graph(START_BOARD);

    compute_score();

    int index;
    index = argc -1;

    while (index > 0) {
        
    int hash = atoi(argv[argc - index]);

    print_node(htable[hash]);
    index--;

}

    return 0;
}