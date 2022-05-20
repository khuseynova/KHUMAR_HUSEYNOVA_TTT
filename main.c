
#include <stdio.h>
#include <stdlib.h>

char** init_board();
void draw_board(char** board);
int isdraw(char** board);
char check(char** board, int i, int j);

int main() {
    char** gameBoard = init_board();
    char gameWinner = '\0';
    char row;
    char col;
    char turn = 'X';

    while(!gameWinner && !isdraw(gameBoard)) {
        draw_board(gameBoard);

        // Read Move
        printf("Player %c, make your move (write row and column): ", turn);
        fflush(stdout);
        scanf(" %c %c", &row, &col);

        // Make move if square is free
        int columnI = row - 'A';
        int rowI = col - '1';
        if (gameBoard[rowI][columnI] == ' ') {
            gameBoard[rowI][columnI] = turn;
            if (turn == 'X') {
                turn = 'O';
            } else {
                turn = 'X';
            }
            gameWinner = check(gameBoard, rowI, columnI);
        } else {
            printf("Square is already filled,choose another one.\n");
        }
    }


    draw_board(gameBoard);
    if (gameWinner == 'X' || gameWinner == 'O') {
        printf("Congratulations %c!\n", gameWinner);
    } else {
        printf("Game ends in a draw.\n");
    }

    return 0;
}

char** init_board() {
    char** B = calloc(3, sizeof(char*));
    for(int i = 0; i < 3; ++i) {
        B[i] = calloc(3, sizeof(char));
    }

    for(int j=0; j < 3; ++j) {
        for(int k=0; k < 3; ++k) {
            B[j][k] = ' ';
        }
    }

    return B;
}
void draw_board(char** board) {
    printf(" |A|B|C|\n");
    for(int i = 0; i < 3; ++i) {
        printf("%d|", i+1);
        for(int j = 0; j < 3; ++j) {
            printf("%c|", board[i][j]);
        }
        printf("\n");
    }
}

int isdraw(char** board) {
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }

    return 1;
}

char check(char** board, int i, int j) {
    if (board[i][j] == board[i][(j+1)%3]
        && board[i][j] == board[i][(j+2)%3])
    {
        // got a column
        return board[i][j];
    }
    else if (board[i][j] == board[(i+1)%3][j]
             && board[i][j] == board[(i+2)%3][j])
    {
        // got a row
        return board[i][j];
    }
    else if (i == j && board[i][j] == board[(i+1)%3][(j+1)%3]
             && board[i][j] == board[(i+2)%3][(j+2)%3])
    {
        // got the forward diagonal
        return board[i][j];
    }
    else if (i+j == 2 && board[i][j] == board[(i+2)%3][(j+1)%3]
             && board[i][j] == board[(i+1)%3][(j+2)%3])
    {
        // got the reverse diagonal
        return board[i][j];
    }
    else {
        // got nothing
        return 0;
    }
}