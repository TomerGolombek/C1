// prive includes //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// private defines //

#define BOARD_SIZE 18
#define STARTING_BOARD {" |0 1 2 3 4 5 6 7"," *________________","0|  X   X   X   X","1|X   X   X   X  ","2|  X   X   X   X","3|.   .   .   .   ","4|  .   .   .   .","5|O   O   O   O  ","6|  O   O   O   O","7|O   O   O   O  "};
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
int is_move_legal(char [][BOARD_SIZE]);
int is_pawn_moveable(char [][BOARD_SIZE], char pawn, int row, int col);
int play(char [][BOARD_SIZE]);


// variables declarations //

int play_number_index = 1;
int keep_playing = 1;
int x_coordinates , y_coordinates;
int move_pawn_is_fine;
int reset_flag = 0;
char turn = 'X';
char starting_array[10][BOARD_SIZE]=STARTING_BOARD;
char board_array[10][BOARD_SIZE]=STARTING_BOARD;

// main function //

int main() {
    printf("Lets play Draughts!\n");
    while(1){
        print_play_number(play_number_index);
        if(turn=='X'){

            printf("Player X - Please enter pawn's location (row number followed by column number):\n");
            scanf("%d %d",&x_coordinates,&y_coordinates);
//            assure_that_chosen_coord_are_ok(&x_coordinates, &y_coordinates, turn, board_array);
            reset_flag = check_if_player_want_to_continue(x_coordinates,y_coordinates);
            if(reset_flag)
                reset_board(board_array , starting_array , &reset_flag);
            move_pawn_is_fine = is_move_legal(board_array);
        }
        else{ // turn=='O'
            printf("Player O - Please enter pawn's location (row number followed by column number):\n");
            scanf("%d %d",&x_coordinates,&y_coordinates);
        }
        print_board(board_array);
        play_number_index++;
    }
    return 0;

}
// end of main function //

// functions implements //

int is_move_legal(char board[][BOARD_SIZE]){
    return 0;
}
int is_pawn_moveable(char board[][BOARD_SIZE], char pawn, int row, int col){
    return 0;
}
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
    printf("----------Play number:%d----------",index);
}
void check_if_answer_is_good(char* answer){
    while (*answer!='y'&&*answer!='n'&&*answer!='N'&&*answer!='Y'){
        printf("Would you like to play another game?(y\\n)\n");
        scanf("%c",answer);
        scanf("%c",answer);
    }
    if(*answer!='y'&&*answer!='Y'){
        exit(1);
    }
}
void assure_that_chosen_coord_are_ok(int* x,int* y, char turn, char board[][BOARD_SIZE]) {
    int row,col;
    row  = *x;
    col = *y;
    if (turn == 'X') {
        while (board[row+2][2*col+2] != 'X') {
            printf("Bad pawn's destination please enter pawn's destination again\n");
            scanf("%c %c", x, y);
        }
    } else { //turn=='O'
        while (board[*x][*y] != 'O') {
            printf("Bad pawn's destination please enter pawn's destination again\n");
            scanf("%c %c", x, y);
        }
    }
}

int check_if_player_want_to_continue(int x,int y){
    char keep_playing_answer;
    if (x_coordinates==QUIT||y_coordinates==QUIT) {
        printf("Player X decided to quit!\n");
        printf("Would you like to play another game?(y\\n)\n");
        scanf("%c", &keep_playing_answer);
        scanf("%c", &keep_playing_answer);
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