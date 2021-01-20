#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "ttt.h"


void init_boards() {

    int init_postion;
    init_postion = 0;

    while ( HSIZE > init_postion) {

        htable[init_postion].init = 0; /* Set the init variable to be 0 in each structure, to show it is empty */
        init_postion++;
    }


}

int depth( Board board ) {

    int init_postion;
    init_postion = 0;
    int numof_o;
    numof_o = 0;

      int numof_x;
    numof_x = 0;

      int numof_x_o;
    numof_o = 0;

    char X_symbol = 'X';
    char O_symbol = 'O';

    int max_position = 9;

    while (max_position > init_postion) { /* Keep looping until the init position is greater than 9 meaning exceeding the table */

        if ( !(board[pos2idx[init_postion]] != O_symbol) ) { 

            numof_o = numof_o +1;   /* Increase the number of O count if the position in the array pos2idx contains the char 'O' */

        } else if (!(board[pos2idx[init_postion]] != X_symbol)) {

              numof_x = numof_x +1; /* Increase the number of X count if the position in the array pos2idx contains the char 'X' */

        }

        init_postion = init_postion + 1;
    }

    numof_x_o = numof_x + numof_o; /* Add the total number of X and O */



     return numof_x_o;  /* Return the total count */
}


    
   


char winner( Board board ) {

    int init_postion;
    init_postion = 0;

    int max_position;
    max_position = 9;

    char X_symbol = 'X';
    char O_symbol = 'O';
    char dash = '-';




    if ( !(depth(board) != max_position)) {

        return dash;  /* If the depth of the board is 9 meaning that the table is full, the game is over and represent this with a '-' */
    }


   while( 8 > init_postion) {


        if (board[pos2idx[WINS[init_postion][0]]] == O_symbol) { /* Check if there is a 'O' at the init position  */

            if ( board[pos2idx[WINS[init_postion][1]]] == O_symbol) { /* Check if there is another 'O' at the init position vertically, horizontally, or diagional */

                if (board[pos2idx[WINS[init_postion][2]]] == O_symbol) {  /* Check if there is 3rd 'O' at the init position vertically, horizontally, or diagional */

                    return O_symbol; /*Return 'O' has the winner */
                }

            }

        } else if (board[pos2idx[WINS[init_postion][0]]] == X_symbol && board[pos2idx[WINS[init_postion][1]]] == X_symbol && board[pos2idx[WINS[init_postion][2]]] == X_symbol) {

             /* Like 'O' check for three consecutive 'X' vertically, horizontally, and diagonal */

            return X_symbol; /*Return 'X' has the winner */
        
        }


        init_postion = init_postion +1;

    }




    return '?'; /* Return question mark if the winner is unknown */
}





char turn( Board board ) {

    int max_position = 9;
    char X_symbol = 'X';
    char O_symbol = 'O';


    if ( ! (depth(board) != max_position) ) { 

        return '-'; /* If the board is full where the depth value is 9, return a '-' for turn indicating no more turns */

    } else if (!(winner(board) !=  X_symbol ) ) {

        return '-'; /* If the board has a winner of player 'X', return a '-' for turn indicating no more turns */

    } else if (!(winner(board) != O_symbol) ) {

        return '-'; /* If the board has a winner of player 'O', return a '-' for turn indicating no more turns */
    }


    if (depth(board) % 2) {

        return O_symbol; /* If the depth is a even number, that means that its player 2 turn, hence 'O' turn  */

    } else {

        return X_symbol; /* Otherwise its 'X' turn  */
    }

}


void init_board( Board board ) {

    htable[board_hash(board)].init = 1;

    htable[board_hash(board)].depth = depth(board);

    htable[board_hash(board)].winner = winner(board);

    htable[board_hash(board)].turn = turn(board);

    strcpy(htable[board_hash(board)].board, board);
}




void join_graph( Board board ) {



    int init_postion;


    int max_position;
    max_position = 9;


    char X_symbol = 'X';
    char O_symbol = 'O';



   
    if ( !(winner(board) != X_symbol) || !(winner(board) != O_symbol) ) { /* Check if the winner is found of 'X' or 'O'  */

        init_postion = 0;                       /* If there is a winner, set the init value to be 0  */

     while ( max_position > init_postion) {

            htable[board_hash(board)].move[init_postion] = -1; /* Once the game is over, set all the hashvalues in the hashtable to be -1  */

            init_postion = init_postion +1;
        }



    } else {

        init_postion = 0;

     while (max_position > init_postion) {


            if (!(board[pos2idx[init_postion]] != O_symbol)) {  /* Check if there is peice of 'O' in the init position  */

                htable[board_hash(board)].move[init_postion] = -1; /* Store the value of -1 */

            } else if (!(board[pos2idx[init_postion]] != X_symbol))  { /* Check if there is peice of 'X' in the init position  */


                htable[board_hash(board)].move[init_postion] = -1; /* Store the value of -1 */
          


            } else {  /* If the index in the string contains the number postion and not 'X' or 'O'  */

                char copy_board[BSIZE];
                strcpy(copy_board, board); /* Copy the board  */

                if (!(turn(board) != O_symbol)) {

                    copy_board[pos2idx[init_postion]] = O_symbol; /* If it is 'O' turn, then store 'O' at the position  */

                } else {

                    copy_board[pos2idx[init_postion]] = X_symbol;   /* If it is 'X' turn, then store 'X' at the position  */ 
                }

                htable[board_hash(board)].move[init_postion] = board_hash(copy_board);

                if (!(htable[board_hash(copy_board)].init != 0)) { /* Check if the hashtable contains an entry for the new board string meaning init is 0  */
                    init_board(copy_board);    /* Call init_board function */
                    join_graph(copy_board);    /* Recursive call join_graph */
                }
            }

            init_postion = init_postion +1;
        }


    }



}









void compute_score() {

  
char X_symbol = 'X';

char O_symbol = 'O';

char dash = '-';


int score_refer;

int score_won = 1;
int score_tie =  0;
int score_won_O = -1;

 int init_postion;
 int init_postion2;
 int init_postion3;

init_postion2 = 9;

  int max_position= 9;

  while (init_postion2 > 0) {

    init_postion = 0;

        while (HSIZE > init_postion) {

            if ( !(htable[init_postion].depth != init_postion2)) {

                if ( !(winner(htable[init_postion].board) != dash) ) {  /* Check if the winner is a dash meaning no winner is found  */

                    htable[init_postion].score = score_tie;             /* If so, set the score to be 0 since it is a tie and no one won  */

                } else if (!(winner(htable[init_postion].board) != O_symbol)) { /* Check if the winner is 'O' */

                    htable[init_postion].score = score_won_O;                   /* If so, set the score to be -1, meaning that 'O' player won */

                }  else if(!(winner(htable[init_postion].board) != X_symbol)) { /* Check of the winner is 'X' */

                    htable[init_postion].score = score_won;                     /* If so, set the score to be 1, meaning that 'X' player won */

                } else {

                  

                    if ( !(htable[init_postion].turn != O_symbol) || !(htable[init_postion].turn != dash)) {  /* If it is 'O' turn */

                        

                        init_postion3 = score_tie;


                        score_refer = score_won;  /* Set score to the score when 'X' wins */

                        while (max_position > init_postion3) {  /* Keep looping until the max postion in the tic tac toe board is reached  */

                            if ( !(htable[init_postion].move[init_postion3] == score_won_O) && (score_refer > htable[htable[init_postion].move[init_postion3]].score) ) {  /* If the score is not eqaul to score of the 'O' player   */


                                score_refer = htable[htable[init_postion].move[init_postion3]].score;       /* Set score eqaul to the min number of choild nodes in the move array  */
                            }


                            init_postion3 = init_postion3 + 1;
                        }

            

                    } else {



                        init_postion3 = score_tie; 



                        score_refer = score_won_O; /* Set score to the score when 'O' wins */



                        while ( max_position > init_postion3) { /* Keep looping until the max postion in the tic tac toe board is reached  */


                            if ( !(htable[init_postion].move[init_postion3] == score_won_O) && (score_refer < htable[htable[init_postion].move[init_postion3]].score ) ) { /* If the score is not eqaul to score of the 'O' player   */


                                score_refer = htable[htable[init_postion].move[init_postion3]].score; /* Set score eqaul to the max number of choild nodes in the move array  */
                            }

                            init_postion3 = init_postion3 + 1;
                        } 

                      
                       
                    }

                    htable[init_postion].score = score_refer;  /* Store the value of score  */
                }  
            }

            init_postion = init_postion + 1;
        }

        init_postion2 = init_postion2 - 1;
    } 

}





int best_move( int board ) {
    return 0;
} 