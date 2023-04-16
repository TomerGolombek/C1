// prive includes // mashu mashu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// private defines //

#define TRUE 1
#define BOARD_SIZE 18
#define STARTING_BOARD {" |0 1 2 3 4 5 6 7"," *________________","0|  X   X   X   X","1|X   X   X   X  ","2|  O   X   X   X","3|.   .   .   .   ","4|  .   .   .   .","5|O   O   O   O  ","6|  O   O   O   O","7|O   O   O   O  "};
#define QUIT 999

// functions declarations //

void place_pawns(char [][BOARD_SIZE]);
void print_board(char [][BOARD_SIZE]);
void reset_board(char [][BOARD_SIZE],char [][BOARD_SIZE],int*);
void print_play_number(int);
void check_if_answer_is_good(char*);
void assure_that_chosen_coord_are_ok(int*, int*, char, char [][BOARD_SIZE]);
int check_if_player_want_to_continue(int,int);
int is_move_legal(char [][BOARD_SIZE]);
int is_move_edible(char [][BOARD_SIZE], char pawn, int row, int col);
//int simple_move(char [][BOARD_SIZE]);
//int edible_move(char [][BOARD_SIZE]);
// int is_pawn_moveable(char [][BOARD_SIZE], char pawn, int row, int col);
//int is_pawn_blocked(char [][BOARD_SIZE], char pawn, int row, int col);
//int is_pawn_on_edge(char [][BOARD_SIZE], char pawn, int row, int col);
//int is_enemy_near(char [][BOARD_SIZE], char pawn, int row, int col));
//int is_friend_near(char [][BOARD_SIZE], char pawn, int row, int col));
int play(char [][BOARD_SIZE]);


// variables declarations //

int pawn_moveable = 0;
int pawn_edible = 0;
int move_legal = 0;
int play_number_index = 1;
int keep_playing = 1;
int x_coordinates , y_coordinates;
int move_pawn_is_fine;
int reset_flag = 0;
char pawn_flag = 'X';
char starting_array[10][BOARD_SIZE]=STARTING_BOARD;
char board_array[10][BOARD_SIZE]=STARTING_BOARD;

// main function //

int main() {
    printf("Lets play Draughts!\n");
    while(TRUE){
        print_board(board_array);
        print_play_number(play_number_index);
        if(pawn_flag=='X'){

            printf("Player X - Please enter pawn's location (row number followed by column number):\n");
            scanf("%d %d%*c",&x_coordinates,&y_coordinates);
            reset_flag = check_if_player_want_to_continue(x_coordinates,y_coordinates);
            if(reset_flag)
                reset_board(board_array , starting_array , &reset_flag);
            else {
                move_pawn_is_fine = is_move_legal(board_array);
                assure_that_chosen_coord_are_ok(&x_coordinates, &y_coordinates, pawn_flag, board_array);
//                while(!pawn_moveable) {
//                    pawn_moveable = is_pawn_moveable();
//                }
//                while(!move_legal) {
//                    move_legal = is_move_legal();
//                }
                 while(!pawn_edible){
                        pawn_edible = is_move_edible(board_array,pawn_flag,2*x_coordinates,2*y_coordinates+2);
                  }
            }
            pawn_flag = 'O';
        }
        else{ // pawn=='O'
            printf("Player O - Please enter pawn's location (row number followed by column number):\n");
            scanf("%d %d%*c",&x_coordinates,&y_coordinates);
            reset_flag = check_if_player_want_to_continue(x_coordinates,y_coordinates);
            if(reset_flag)
                reset_board(board_array , starting_array , &reset_flag);
            else {
                move_pawn_is_fine = is_move_legal(board_array);
                assure_that_chosen_coord_are_ok(&x_coordinates, &y_coordinates, pawn_flag, board_array);
            }
            pawn_flag = 'X';
        }
        play_number_index++;
    }
    return 0;

}
// end of main function //

// functions implements //

int is_move_legal(char board[][BOARD_SIZE]){
    return 0;
}
//int is_pawn_moveable(char board[][BOARD_SIZE], char pawn, int row, int col){
   //int left = 0;
   //int right = 0;
   //
   // if pawn == 'X' {
   //
   //
   //
   //
   //
   //
   //
   // }

  //  return 0;
//}
int play_single_turn(char board[][BOARD_SIZE], char pawn){
    return 0;
}
int play(char board[][BOARD_SIZE]){
    return 0;
}
void place_pawns(char board[][BOARD_SIZE]){
}
void print_board(char board[][BOARD_SIZE]){
    int i, j;
    for (i = 0; i < BOARD_SIZE - 8; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

void print_play_number(int index){
    printf("----------Play number:%d----------\n",index);
}
void check_if_answer_is_good(char* answer){
    while (*answer!='y'&&*answer!='n'&&*answer!='N'&&*answer!='Y'){
        printf("Would you like to play another game?(y\\n)\n");
        scanf("%c%*c",answer);
    }
    if(*answer!='y'&&*answer!='Y'){
        exit(1);
    }
}
void assure_that_chosen_coord_are_ok(int* x,int* y, char pawn, char board[][BOARD_SIZE]) {
    int row,col;
    row  = *x;
    col = *y;
    if (pawn == 'X') {
        while (board[row+2][2*col+2] != 'X') {
            printf("Bad pawn's destination please enter pawn's destination again\n");
            scanf("%d %d%*c", x, y);
            row  = *x;
            col = *y;
        }
    } else { //pawn=='O'
        while (board[row+2][2*col+2] != 'O') {
            printf("Bad pawn's destination please enter pawn's destination again\n");
            scanf("%d %d%*c", x, y);
            row  = *x;
            col = *y;
        }
    }
}

int check_if_player_want_to_continue(int x,int y){
    char keep_playing_answer;
    if (x_coordinates==QUIT||y_coordinates==QUIT) {
        printf("Player X decided to quit!\n");
        printf("Would you like to play another game?(y\\n)\n");
        scanf("%c%*c", &keep_playing_answer);
        check_if_answer_is_good(&keep_playing_answer);
        if (keep_playing_answer == 'y' || keep_playing_answer == 'Y') {
            return 1;
        }
    }
    return 0;
}

void reset_board(char board1[][BOARD_SIZE],char board2[][BOARD_SIZE],int* reset){
    int i, j;
    for (i = 0; i < BOARD_SIZE - 8; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            board1[i][j] = board2[i][j];
        }
    }
    *reset = 0;

}
int is_move_edible(char board[][BOARD_SIZE], char pawn, int row, int col){
    if (pawn=='X'){
        if(col==2&&row<=7) {
            if (board[row + 1][col + 2] == 'O' && board[row + 2][col + 4] == '.') {
                return 1;
            }
            else {
                return 0;
            }
        }
        else if(col==16&&row<=7){
            if(board[row+1][col-2]=='O'&&board[row+2][col-4]=='.') {
                return 1;
            }
            else {
                return 0;
            }
        }
        else if(row<=7){
            if((board[row+1][col-2]=='O'&&board[row+2][col-4]=='.')||board[row + 1][col + 2] == 'O' && board[row + 2][col + 4] == '.') {
                return 1;
            }
            else {
                return 0;
            }
        }
        else{
            return 0;
        }

    }
    else{ //pawn=='O'
        if(col==2&&row>=4) {
            if (board[row - 1][col + 2] == 'X' && board[row - 2][col + 4] == '.') {
                return 1;
            }
            else {
                return 0;
            }
        }
        else if(col==16&&row>=5){
            if(board[row-1][col-2]=='X'&&board[row-2][col-4]=='.') {
                return 1;
            }
            else {
                return 0;
            }
        }
        else if(row>=4){
            if((board[row-1][col-2]=='X'&&board[row-2][col-4]=='.')||board[row - 1][col + 2] == 'X' && board[row - 2][col + 4] == '.') {
                return 1;
            }
            else {
                return 0;
            }
        }
        else{
            return 0;
        }
    }
}