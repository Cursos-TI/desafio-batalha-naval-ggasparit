#include <stdio.h>
#include <stdbool.h>

#define BOARD_SIZE 10
#define SHIP_SIZE  3
#define WATER      0
#define SHIP_VAL   3


void init_board(int b[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            b[i][j] = WATER;
}

void print_board(int b[BOARD_SIZE][BOARD_SIZE]) {
  
    printf("   ");
    for (int c = 0; c < BOARD_SIZE; c++) 
        printf("%c ", 'A' + c);
    printf("\n");

    
    for (int r = 0; r < BOARD_SIZE; r++) {
        printf("%2d ", r);  
        for (int c = 0; c < BOARD_SIZE; c++)
            printf("%d ", b[r][c]);
        printf("\n");
    }
}

void build_ship_positions(int r0, int c0, int horizontal,
                          int rows[SHIP_SIZE], int cols[SHIP_SIZE]) {
    for (int k = 0; k < SHIP_SIZE; k++) {
        rows[k] = r0 + (horizontal ? 0 : k);
        cols[k] = c0 + (horizontal ? k : 0);
    }
}

bool can_place_ship(int b[BOARD_SIZE][BOARD_SIZE],
                    int rows[SHIP_SIZE], int cols[SHIP_SIZE]) {
    for (int k = 0; k < SHIP_SIZE; k++) {
        int r = rows[k], c = cols[k];
        if (r < 0 || r >= BOARD_SIZE || c < 0 || c >= BOARD_SIZE)
            return false;
        if (b[r][c] != WATER)
            return false;
    }
    return true;
}

void place_ship(int b[BOARD_SIZE][BOARD_SIZE],
                int rows[SHIP_SIZE], int cols[SHIP_SIZE]) {
    for (int k = 0; k < SHIP_SIZE; k++)
        b[rows[k]][cols[k]] = SHIP_VAL;
}

int main(void) {
    int board[BOARD_SIZE][BOARD_SIZE];
    init_board(board);

    // Navio 1: horizontal em (linha 2, coluna B → c=1)
    int n1_r0 = 2, n1_c0 = 1, n1_horizontal = 1;

    // Navio 2: vertical em (linha 5, coluna H → c=7)
    int n2_r0 = 5, n2_c0 = 7, n2_horizontal = 0;

    int n1_rows[SHIP_SIZE], n1_cols[SHIP_SIZE];
    int n2_rows[SHIP_SIZE], n2_cols[SHIP_SIZE];

    build_ship_positions(n1_r0, n1_c0, n1_horizontal, n1_rows, n1_cols);
    build_ship_positions(n2_r0, n2_c0, n2_horizontal, n2_rows, n2_cols);

    if (!can_place_ship(board, n1_rows, n1_cols)) {
        printf("Navio 1 inválido.\n");
        return 1;
    }
    place_ship(board, n1_rows, n1_cols);

    if (!can_place_ship(board, n2_rows, n2_cols)) {
        printf("Navio 2 inválido.\n");
        return 1;
    }
    place_ship(board, n2_rows, n2_cols);

    print_board(board);
    return 0;
}


