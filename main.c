// private includes //

#include <stdio.h>
#include <stdlib.h>

// private defines //

#define STARTING_BOARD {" |0 1 2 3 4 5 6 7"," *_______________","0|  X   X   X   X","1|X   X   X   X  ","2|  X   X   X   X","3|.   .   .   .   ","4|  .   .   .   .","5|O   O   O   O  ","6|  O   O   O   O","7|O   O   O   O  "};
#define BOARD_SIZE        18
#define BOARD_SIZE_HEIGHT 10
#define QUIT              999
#define MOVE_RIGHT         1
#define MOVE_LEFT          2
#define MOVE_BOTH          3
#define EAT_RIGHT          4
#define EAT_LEFT           5
#define EAT_BOTH           6
#define HUNGRY             0
#define FALSE              0
#define TRUE               1
#define X_WINNER           1
#define Y_WINNER           2

// functions declarations //

void print_board(char [][BOARD_SIZE]);
void place_pawns(char [][BOARD_SIZE]);
void print_play_number(int);
void check_if_answer_is_good(char*);
void assure_that_chosen_coord_are_ok(int*, int*, char, char [][BOARD_SIZE]);
int check_if_player_want_to_continue(int,int);
void print_score(char [][BOARD_SIZE]);
int is_move_legal(char [][BOARD_SIZE], char pawn, int row,int col, int xtarget,int ytarget);
int is_move_edible(char [][BOARD_SIZE], char pawn, int row, int col);
int is_move_simple(char [][BOARD_SIZE], char pawn, int row, int col);
int is_pawn_moveable(char [][BOARD_SIZE], char pawn, int row, int col);
int check_winner(char [][BOARD_SIZE]);
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
int y_target = 0;
int x_target = 0;
char pawn_flag = 'X';
char board_array[BOARD_SIZE_HEIGHT][BOARD_SIZE]={" |0 1 2 3 4 5 6 7"," *_______________","0|  X   X   X   X","1|X   X   X   X  ","2|  X   X   X   X","3|.   .   .   .   ","4|  .   .   .   .","5|O   O   O   O  ","6|  O   O   O   O","7|O   O   O   O  "};

// main function //

int main() {
    printf("Lets play Draughts!\n");
    while(TRUE){
        print_board(board_array);
        print_play_number(play_number_index);
        pawn_moveable = 0;
        if(pawn_flag=='X') {

            printf("Player X - Please enter pawn's location (row number followed by column number):\n");
            while(!pawn_moveable) {
                scanf("%d %d%*c", &x_coordinates, &y_coordinates);
                reset_flag = check_if_player_want_to_continue(x_coordinates, y_coordinates);
                if (reset_flag) {
                    place_pawns(board_array);
                    play_number_index = 1;
                    break;

                }
                else {
                    assure_that_chosen_coord_are_ok(&x_coordinates, &y_coordinates, pawn_flag, board_array);
                    pawn_moveable = is_pawn_moveable(board_array, pawn_flag, x_coordinates + 2, 2 * y_coordinates + 2);
                }
            }
            if(reset_flag){
                reset_flag = 0;
                continue;
            }
            printf("Player X - Please enter pawn's destination (row number followed by column number):\n");
            while (!move_pawn_is_fine) {
                scanf("%d %d%*c",&x_target,&y_target);
                move_pawn_is_fine = is_move_legal(board_array, pawn_flag, x_coordinates + 2, 2 * y_coordinates + 2,x_target + 2,2 * y_target + 2);
            }
            pawn_flag = 'O';
            pawn_moveable = 0;
            move_pawn_is_fine = 0;
        }
        else{ // pawn=='O'
            printf("Player O - Please enter pawn's location (row number followed by column number):\n");
            while(!pawn_moveable) {
                scanf("%d %d%*c", &x_coordinates, &y_coordinates);
                reset_flag = check_if_player_want_to_continue(x_coordinates, y_coordinates);
                if (reset_flag) {
                    place_pawns(board_array);
                    reset_flag = 0;
                    break;
                }
                else {
                    assure_that_chosen_coord_are_ok(&x_coordinates, &y_coordinates, pawn_flag, board_array);
                    pawn_moveable = is_pawn_moveable(board_array, pawn_flag, x_coordinates + 2, 2 * y_coordinates + 2);
                }
            }
            if(reset_flag){
                reset_flag = 0;
                continue;
            }
            printf("Player O - Please enter pawn's destination (row number followed by column number):\n");
            while (!move_pawn_is_fine) {
                scanf("%d %d%*c",&x_target,&y_target);
                move_pawn_is_fine = is_move_legal(board_array, pawn_flag, x_coordinates + 2, 2 * y_coordinates + 2,x_target + 2,2 * y_target + 2);
            }

            pawn_flag = 'X';
            pawn_moveable = 0;
            move_pawn_is_fine = 0;
        }
        play_number_index++;
        print_score(board_array);
    }

}
// end of main function //

// functions implements //

int is_move_legal(char board[][BOARD_SIZE],char pawn, int row,int col, int xtarget, int ytarget){
    int sim_move = is_move_simple(board,pawn,row,col);
    int eat_move = is_move_edible(board,pawn,row,col);
    if (board[xtarget][ytarget] != '.')
        return 0;

    if (pawn == 'X')
        if ((eat_move == EAT_BOTH) && (xtarget == row + 2) && ((ytarget) == col + 4) || (ytarget) == col - 4) {
            return 1;
        } else if ((eat_move == EAT_LEFT) && (xtarget == row + 2) && ((ytarget) == col - 4)) {
            return 1;
        } else if ((eat_move == EAT_RIGHT) && (xtarget == row + 2) && ((ytarget) == col + 4)) {
            return 1;
        } else if ((sim_move == MOVE_BOTH) && (xtarget == row + 1) && ((ytarget == col + 2) || (ytarget == col - 2))) {
            return 1;
        } else if ((sim_move == MOVE_LEFT) && (xtarget == row + 1) && ((ytarget) == col - 2)) {
            return 1;
        } else if ((sim_move == MOVE_RIGHT) && (xtarget == row + 1) && ((ytarget) == col + 2)) {
            return 1;
        } else {
            return 0;
        }

    else { //pawn=='O'
        if ((eat_move == EAT_BOTH) && (xtarget == row - 2) && ((ytarget) == col + 4 || (ytarget) == col - 4)) {
            return 1;
        } else if ((eat_move == EAT_LEFT) && (xtarget == row - 2) && ((ytarget) == col - 4)) {
            return 1;
        } else if ((eat_move == EAT_RIGHT) && (xtarget == row - 2) && ((ytarget) == col + 4)) {
            return 1;
        } else if ((sim_move == MOVE_BOTH) && (xtarget == row + 1) && ((ytarget == col + 2) || (ytarget == col - 2))) {
            return 1;
        } else if ((sim_move == MOVE_LEFT) && (xtarget == row - 1) && ((ytarget) == col - 2)) {
            return 1;
        } else if ((sim_move == MOVE_RIGHT) && (xtarget == row - 1) && ((ytarget) == col + 2)) {
            return 1;
        } else {
            return 0;
        }
    }
}
int is_pawn_moveable(char board[][BOARD_SIZE], char pawn, int row, int col){
    if (is_move_edible(board, pawn, row, col)){
        return 1;
    }
    else return is_move_simple(board, pawn, row, col) ? 1 : 0;
}
int play_single_turn(char board[][BOARD_SIZE], char pawn){
    return 0;
}
int play(char board[][BOARD_SIZE]){
    return 0;
}

void print_board(char board[][BOARD_SIZE]){
    int i, j;
    for (i = 0; i < BOARD_SIZE_HEIGHT; i++) {
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
    while (board[row + 2][2 * col + 2] != (pawn == 'X' ? 'X' : 'O')) {
        printf("Bad pawn's destination please enter pawn's destination again\n");
        scanf("%d %d%*c", x, y);
        row = *x;
        col = *y;
    }
}

int check_if_player_want_to_continue(int x,int y){
    char keep_playing_answer;
    if (x==QUIT||y==QUIT) {
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
int check_winner(char board[][BOARD_SIZE]){
    int x_score=12,y_score=12;
    int i, j;
    for (i = 0; i < BOARD_SIZE - 8; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if(board[i][j]=='X'){
                y_score--;
            }
            if(board[i][j]=='O'){
                x_score--;
            }
        }
    }
    if(x_score==12){
        printf("Wooohooo! player X Won!");
        return 1;
    }
    if(y_score==12){
        printf("Wooohooo! player O Won!");
        return 1;
    }
    return 0;
}

void place_pawns(char board[][BOARD_SIZE]){
    int i, j;
    char temp[BOARD_SIZE_HEIGHT][BOARD_SIZE]={" |0 1 2 3 4 5 6 7"," *_______________","0|  X   X   X   X","1|X   X   X   X  ","2|  X   X   X   X","3|.   .   .   .   ","4|  .   .   .   .","5|O   O   O   O  ","6|  O   O   O   O","7|O   O   O   O  "};
    for (i = 0; i < BOARD_SIZE - 8; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = temp[i][j];
        }
    }
}
void print_score(char board[][BOARD_SIZE]){
    int x_score=12,y_score=12;
    int i, j;
    for (i = 0; i < BOARD_SIZE - 8; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if(board[i][j]=='X'){
                y_score--;
            }
            if(board[i][j]=='O'){
                x_score--;
            }
        }
    }
    printf("X score:%d       O score:%d\n",x_score,y_score);
}
int is_move_edible(char board[][BOARD_SIZE], char pawn, int row, int col){
    if (pawn=='X'){
        if((col==2&&row<=7)||(col==4&&row<=7)) {
            return board[row + 1][col + 2] == 'O' && board[row + 2][col + 4] == '.' ? EAT_RIGHT : HUNGRY;
        }
        else if((col==16&&row<=7)||(col==14&&row<=7)){
            return board[row + 1][col - 2] == 'O' && board[row + 2][col - 4] == '.' ? EAT_LEFT : HUNGRY;
        }
        else if(row<=7){
            if ((board[row+1][col-2]=='O'&&board[row+2][col-4]=='.')&&(board[row + 1][col + 2] == 'O' && board[row + 2][col + 4] == '.')){
                return EAT_BOTH;
            }
            else if((board[row+1][col-2]=='O'&&board[row+2][col-4]=='.')) {
                return EAT_LEFT;
            }
            else return board[row + 1][col + 2] == 'O' && board[row + 2][col + 4] == '.' ? EAT_RIGHT : HUNGRY;
        }
        else{
            return HUNGRY;
        }

    }
    else{ //pawn=='O'
        if((col==2&&row>=4)||(col==4&&row>=4)) {
            return board[row - 1][col + 2] == 'X' && board[row - 2][col + 4] == '.' ? EAT_RIGHT : HUNGRY;
        }
        else if((col==16&&row>=5)||(col==14&&row>=5)){
            return board[row - 1][col - 2] == 'X' && board[row - 2][col - 4] == '.' ? EAT_LEFT : HUNGRY;
        }
        else if(row>=4){
            if((board[row-1][col-2]=='X'&&board[row-2][col-4]=='.')&&(board[row - 1][col + 2] == 'X' && board[row - 2][col + 4] == '.')){
                return EAT_BOTH;
            }
            else if((board[row-1][col-2]=='X'&&board[row-2][col-4]=='.')) {
                return EAT_LEFT;
            }
            else return board[row - 1][col + 2] == 'X' && board[row - 2][col + 4] == '.' ? EAT_RIGHT : HUNGRY;
        }
        else{
            return HUNGRY;
        }
    }
}
int is_move_simple(char board[][BOARD_SIZE], char pawn, int row, int col) {
    if (pawn == 'X'){
        if(col==2&&row<=8) {
            return board[row + 1][col + 2] == '.' ? MOVE_RIGHT : FALSE;
        }
        else if(col==16&&row<=8){
            return board[row + 1][col - 2] == '.' ? MOVE_LEFT : FALSE;
        }
        else if(row<=8){
            if ((board[row+1][col-2]=='.')&&(board[row + 1][col + 2] == '.')){
                return MOVE_BOTH;
            }
            else if(board[row+1][col-2]=='.') {
                return MOVE_LEFT;
            }
            else return board[row + 1][col + 2] == '.' ? MOVE_RIGHT : FALSE;
        }
        else{
            return FALSE;
        }
    }else{ //pawn == 'O'
        if(col==2&&row>=3) {
            if (board[row - 1][col + 2] == '.' ) {
                return MOVE_RIGHT;
            }
            else {
                return FALSE;
            }
        }
        else if(col==16&&row>=3){
            return board[row - 1][col - 2] == '.' ? MOVE_LEFT : FALSE;
        }
        else if(row>=3){
            if((board[row - 1][col - 2]=='.')&&(board[row - 1][col + 2] == '.')){
                return MOVE_BOTH;
            }
            else if(board[row - 1][col - 2]=='.') {
                return MOVE_LEFT;
            }
            else return board[row - 1][col + 2] == '.' ? MOVE_RIGHT : FALSE;
        }
        else{
            return FALSE;
        }
    }
}
