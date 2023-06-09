// private includes //

#include <stdio.h>
#include <stdlib.h>

// private defines //

#define BOARD_SIZE        20
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
#define YES                1
#define NO                 2

// functions declarations //

void print_board(char [][BOARD_SIZE]);
void place_pawns(char [][BOARD_SIZE]);
void print_play_number(int);
void check_if_answer_is_good(char*);
void assure_that_chosen_coord_are_ok(int*, int*, char, char [][BOARD_SIZE]);
void change_place(char board[][BOARD_SIZE],char pawn, int row,int col, int xtarget, int ytarget,int y_target,int y_coord);
void print_score(char [][BOARD_SIZE]);
int check_if_player_want_to_continue(char board[][BOARD_SIZE],int,int,char );
int is_move_legal(char [][BOARD_SIZE], char pawn, int row,int col, int xtarget,int ytarget);
int is_move_edible(char [][BOARD_SIZE], char pawn, int row, int col);
int is_move_simple(char [][BOARD_SIZE], char pawn, int row, int col);
int is_pawn_moveable(char [][BOARD_SIZE], char pawn, int row, int col);
int check_winner(char [][BOARD_SIZE]);
int play(char [][BOARD_SIZE]);
int play_single_turn(char [][BOARD_SIZE],char pawn);
int check_reset(char [][BOARD_SIZE]);
int pawns_amount(char [][BOARD_SIZE], char pawn);


// variables declarations //


char boards_array[BOARD_SIZE_HEIGHT][BOARD_SIZE]={"  |0 1 2 3 4 5 6 7 ","  *----------------"," 0|  X   X   X   X "," 1|X   X   X   X   "," 2|  X   X   X   X "," 3|.   .   .   .    "," 4|  .   .   .   . "," 5|O   O   O   O   "," 6|  O   O   O   O "," 7|O   O   O   O   "};
char end_game;

// main function //

int main() {
    while(TRUE){
        printf("Lets play Draughts!\n");
        printf("\n");
        play(boards_array);
        printf("Would you like to play another game?(y\\n)\n");
        scanf("%c%*c", &end_game);
        check_if_answer_is_good(&end_game);
        if(end_game=='y'||end_game=='Y')
            place_pawns(boards_array);
        else{
            break;
        }
    }
    return 0;
}
// end of main function //

// functions implements //

int is_move_legal(char board[][BOARD_SIZE],char pawn, int row,int col, int xtarget, int ytarget){
    int sim_move = is_move_simple(board,pawn,row,col);
    int eat_move = is_move_edible(board,pawn,row,col);
    if (board[xtarget][ytarget] != '.')
        return 0;

    if (pawn == 'X')
        if (((eat_move == EAT_BOTH) && (xtarget == row + 2) && ((ytarget) == col + 4) || (ytarget) == col - 4)||((eat_move == EAT_LEFT) && (xtarget == row + 2) && ((ytarget) == col - 4)
        )||((eat_move == EAT_RIGHT) && (xtarget == row + 2) && ((ytarget) == col + 4))||((sim_move == MOVE_BOTH) && (xtarget == row + 1) && ((ytarget == col + 2) || (ytarget == col - 2)))
        ||((sim_move == MOVE_LEFT) && (xtarget == row + 1) && ((ytarget) == col - 2))||((sim_move == MOVE_RIGHT) && (xtarget == row + 1) && ((ytarget) == col + 2))) {
            return 1;
        } else {
            return 0;
        }

    else { //pawn=='O'
        if (((eat_move == EAT_BOTH) && (xtarget == row - 2) && ((ytarget) == col + 4 || (ytarget) == col - 4))||((eat_move == EAT_LEFT) && (xtarget == row - 2) && ((ytarget) == col - 4))
        ||((eat_move == EAT_RIGHT) && (xtarget == row - 2) && ((ytarget) == col + 4))||((sim_move == MOVE_BOTH) && (xtarget == row - 1) && ((ytarget == col + 2) || (ytarget == col - 2)))
        ||((sim_move == MOVE_LEFT) && (xtarget == row - 1) && ((ytarget) == col - 2))||((sim_move == MOVE_RIGHT) && (xtarget == row - 1) && ((ytarget) == col + 2))) {
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

int pawns_amount(char board[][BOARD_SIZE], char pawn){
    int i, j, amount=0;
    for (i = 0; i < BOARD_SIZE_HEIGHT; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
             if(board[i][j]==pawn){
                 amount++;
             }
        }
    }
    return amount;
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
}
void assure_that_chosen_coord_are_ok(int* x,int* y, char pawn, char board[][BOARD_SIZE]) {
    int row,col;
    row  = *x;
    col = *y;
    while (board[row + 2][2 * col + 3] != (pawn == 'X' ? 'X' : 'O')) {
        printf("Bad pawn's destination please enter pawn's destination again\n");
        scanf("%d %d%*c", x, y);
        row = *x;
        col = *y;
    }
}

int check_if_player_want_to_continue(char board[][BOARD_SIZE] , int x,int y, char pawn){
    char keep_playing_answer;
    if (x==QUIT||y==QUIT) {
        printf("Player %c decided to quit!\n", pawn);
        print_board(board);
        printf("\n");
        printf("Would you like to play another game?(y\\n)\n");
        scanf("%c%*c", &keep_playing_answer);
        check_if_answer_is_good(&keep_playing_answer);
        if (keep_playing_answer == 'y' || keep_playing_answer == 'Y') {
            return YES;
        } else{
            return NO;
        }
    }
    return 0;
}
int check_winner(char board[][BOARD_SIZE]){
    int x_score=12,y_score=12;
    int i, j;
    for (i = 0; i < BOARD_SIZE - 10; i++) {
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
        printf("Wooohooo! player X Won!\n");
        print_board(board);
        printf("\n");
        return 1;
    }
    if(y_score==12){
        printf("Wooohooo! player O Won!\n");
        print_board(board);
        printf("\n");
        return 1;
    }
    for (j = 0; j < BOARD_SIZE; j++) {
        if (board[2][j]=='O'){
            printf("Wooohooo! player O Won!\n");
            print_board(board);
            printf("\n");
            return 1;
        }
        if (board[9][j]=='X'){
            printf("Wooohooo! player X Won!\n");
            print_board(board);
            printf("\n");
            return 1;
        }
    }

    return 0;
}

void place_pawns(char board[][BOARD_SIZE]){
    int i, j;
    char temp[BOARD_SIZE_HEIGHT][BOARD_SIZE]={"  |0 1 2 3 4 5 6 7 ","  *----------------"," 0|  X   X   X   X "," 1|X   X   X   X   "," 2|  X   X   X   X "," 3|.   .   .   .    "," 4|  .   .   .   . "," 5|O   O   O   O   "," 6|  O   O   O   O "," 7|O   O   O   O   "};
    for (i = 0; i < BOARD_SIZE - 10; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = temp[i][j];
        }
    }
}
void print_score(char board[][BOARD_SIZE]){
    int x_score=12,y_score=12;
    int i, j;
    for (i = 0; i < BOARD_SIZE - 10; i++) {
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
void change_place(char board[][BOARD_SIZE],char pawn, int row,int col, int xtarget, int ytarget,int y_target_org,int y_coord){
    if (pawn == 'X'){
        if (y_coord % 2 ==  y_target_org % 2)/*eat mode*/ {
            board[row][col]= '.';
            board[xtarget][ytarget] =  'X';
            board[row+1][(col+ytarget)/2] = '.';
            printf("Ho nice move! you got him...\n");

        }
        else /*regular move mod*/{
            board[row][col]= '.';
            board[xtarget][ytarget] =  'X';
        }
    }

    else  /*pawn == 'O'*/ {

        if (y_coord % 2 ==  y_target_org % 2) /*eat mode*/ {
            board[row][col]= '.';
            board[xtarget][ytarget] =  'O';
            board[row-1][(col+ytarget)/2] = '.';
            printf("Ho nice move! you got him...\n");
        }
        else /*regular move mod*/{
            board[row][col]= '.';
            board[xtarget][ytarget] =  'O';
        }
    }
}
int check_reset(char board[][BOARD_SIZE]){
    char temp[BOARD_SIZE_HEIGHT][BOARD_SIZE]={"  |0 1 2 3 4 5 6 7 ","  *----------------"," 0|  X   X   X   X "," 1|X   X   X   X   "," 2|  X   X   X   X "," 3|.   .   .   .    "," 4|  .   .   .   . "," 5|O   O   O   O   "," 6|  O   O   O   O "," 7|O   O   O   O   "};
    int i,j;
    for (i = 0; i < BOARD_SIZE - 10; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if(board[i][j]!=temp[i][j])
                return 0;
        }
        }
    return 1;

}
int play_single_turn(char board_array[][BOARD_SIZE], char pawn_flag){
    int pawn_moveable = 0 , x_coordinates = 0, y_coordinates = 0 , reset_flag   , move_pawn_is_fine = 0 ,x_target = 0, y_target = 0,pawn_pre , pawn_after;
    char opposite_pawn = pawn_flag == 'X'? 'O' :'X';
    printf("Player %c - Please enter pawn's location (row number followed by column number):\n",pawn_flag);
    while(!pawn_moveable) {
        scanf("%d %d%*c", &x_coordinates, &y_coordinates);
        reset_flag = check_if_player_want_to_continue(board_array, x_coordinates, y_coordinates,pawn_flag);
        if (reset_flag==YES) {
            place_pawns(board_array);
            return 0;
        }
        if(reset_flag==NO){
            exit(1);
        }
        else {
            assure_that_chosen_coord_are_ok(&x_coordinates, &y_coordinates, pawn_flag, board_array);
            pawn_moveable = is_pawn_moveable(board_array, pawn_flag, x_coordinates + 2, 2 * y_coordinates + 3);
            if(!pawn_moveable){
                printf("This pawn has nowhere to move!\n");
                printf("Player %c - Bad pawn's selection please enter pawn's location again:\n",pawn_flag);
            }
        }
    }
    printf("Player %c - Please enter pawn's destination (row number followed by column number):\n",pawn_flag);
    while (!move_pawn_is_fine) {
        scanf("%d %d%*c",&x_target,&y_target);
        move_pawn_is_fine = is_move_legal(board_array, pawn_flag, x_coordinates + 2, 2 * y_coordinates + 3,x_target + 2,2 * y_target + 3);
        if(!move_pawn_is_fine){
            printf("Player %c - Bad pawn's destination please enter pawn's destination again:\n",pawn_flag);
        }
    }
    pawn_pre = pawns_amount(board_array,opposite_pawn);
    change_place(board_array,pawn_flag,x_coordinates+2,2*y_coordinates+3,x_target+2,2 * y_target + 3,y_target,y_coordinates);
    pawn_after = pawns_amount(board_array,opposite_pawn);
    return pawn_pre - pawn_after ;
}

int play(char board[][BOARD_SIZE]){
    int is_eaten =0;
    int play_number_index=1;
    char pawn_flag = 'X';
    print_play_number(play_number_index);
    print_board(board);
    while(TRUE){
        is_eaten+=play_single_turn(board,pawn_flag);
        play_number_index++;
        if (check_winner(board)){
            break;
        }
        print_score(board);
        if(check_reset(board)) {
            play_number_index = 1;
            pawn_flag = 'O';
        }
        print_play_number(play_number_index);
        printf("\n");
        print_board(board);
        printf("\n");
        pawn_flag = pawn_flag == 'X' ? 'O' : 'X';
    }
    return 0;
}


