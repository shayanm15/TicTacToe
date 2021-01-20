#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "ttt.h"

int main( int argc, char **argv) { 


    int init_position;
    init_position = 0;
    int node_counter;

    init_boards();

    init_board(START_BOARD);
    
    join_graph(START_BOARD);


   while ( HSIZE > init_position) {

        if ( !(htable[init_position].init != 1) ) { /* Check if the entires in the hashtable have init value of 1 */

            node_counter = node_counter + 1; /* If so, increase the count_node plus 1  */
        } 

        init_position = init_position + 1;  /* Move to the bext position */
    }

    printf("%d\n", node_counter);

    return 0;
}