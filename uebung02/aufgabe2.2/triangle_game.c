#include "triangle_routines.h"
#include <stdio.h>

/* takes a 15er board and converts it to a 25er board */
void convertBoard(int oldBoard[], int newBoard[])
{
    for (int row = 0; row < 5; row++)
    {
        for (int entry = 0; entry < row + 1; entry++)
        {
            newBoard[row * 5 + entry] = oldBoard[row * (row + 1) / 2 + entry];
        }

        for (int entry = row + 1; entry < 5; entry++)
        {
            newBoard[row * 5 + entry] = 2;
        }
    }
    return;
}

/* takes a 25er board and converts it to a 15er board */
void convertBoardBack(int oldBoard[], int newBoard[])
{
    for (int row = 0; row < 5; row++)
    {
        for (int entry = 0; entry < row + 1; entry++)
        {
            newBoard[row * (row + 1) / 2 + entry] = oldBoard[row * 5 + entry];
        }
    }
    return;
}

/* takes a 25er board and prints it */
void print_board(int board[])
{
    int tmpBoard[15];
    convertBoardBack(board, tmpBoard);
    triangle_print(tmpBoard);
}

/* Return the number of entries on the board. */
int nentries(int board[])
{
    int size = 25;  // TODO maybe calculate size
    int n    = 0;   // number of entries
    for (int i = 0; i < size; i++)
    {
        if (board[i] == 1)
        {
            n++;
        }
    }
    return n;
}


/* Return 1 if the move is valid on this board, otherwise return 0. */
int valid_move(int board[], int move[])
{
    /*
        start field has to have a peg on it
        skipped field has to have a peg on it
        end field has to be empty
    */
    if (board[move[0]] != 1 || board[move[1]] != 1 || board[move[2]] != 0)
    {
        return 0;
    }

    /*
        check if any of the elements from the move array is 2 (which means that it is out of bounce)
        and check if number in move is bigger than 24 or smaller than 0, which would be an invalid
        move
    */
    for (int i = 0; i < 3; i++)
    {
        if (board[move[i]] == 2 || move[i] > 24 || move[i] < 0)
        {
            return 0;
        }
    }

    // only diagonal moves (that skip at max one row) are valid
    if (move[0] - 5 == move[1] && move[0] - 10 == move[2])  // move top right
    {
        return 1;
    }
    else if (move[0] - 6 == move[1] && move[0] - 12 == move[2])  // move top left
    {
        return 1;
    }
    else if (move[0] + 5 == move[1] && move[0] + 10 == move[2])  // move bottom left
    {
        return 1;
    }
    else if (move[0] + 6 == move[1] && move[0] + 12 == move[2])  // move bottom right
    {
        return 1;
    }

    // only horizontal moves (that skip tat max one element) are valid
    else if (move[0] - 1 == move[1] && move[0] - 2 == move[2])  // move left
    {
        return 1;
    }
    else if (move[0] + 1 == move[1] && move[0] + 2 == move[2])  // move right
    {
        return 1;
    }

    return 0;
}


/* Make a move on this board. */
void make_move(int board[], int move[])
{
    // check if the move is valid
    if (valid_move(board, move) == 1)
    {
        // remove the pegs that are jumped over
        board[(move[1])] = 0;
        // remove the peg that is jumped from
        board[move[0]] = 0;
        // place the peg that is jumped to
        board[move[2]] = 1;
    }
    return;
}


/* Unmake this move on this board. */
void unmake_move(int board[], int move[])
{
    // undo what make_move did (, but only if the "reverse" move is valid)
    // TODO if check maybe?
    board[move[0]] = 1;
    board[move[1]] = 1;
    board[move[2]] = 0;
}

/*
 * Solve the game starting from this board. Return 1 if the game can
 * be solved; otherwise return 0. Do not permanently alter the board
 * passed in. Once a solution is found, print the boards making up
 * the solution in reverse order.
 */
int solve(int board[])
{
    // check if the board is already solved
    if (nentries(board) == 1)
    {
        print_board(board);
        return 1;
    }
    else if (nentries(board) == 0)
    {
        return 0;
    }

    // start with one peg on the board and try all possible moves with a depth first search
    for (int i = 0; i < 25; i++)
    {
        if (board[i] != 1)
        {
            continue;
        }

        // all possible moves
        int moves[6][3] = {
            { i, i - 5, i - 10 },  // move top right
            { i, i - 6, i - 12 },  // move top left
            { i, i + 5, i + 10 },  // move bottom left
            { i, i + 6, i + 12 },  // move bottom right
            { i, i - 1, i - 2 },   // move left
            { i, i + 1, i + 2 }    // move right
        };

        // try all possible moves
        for (int j = 0; j < 6; j++)
        {
            // check if the move is valid
            if (valid_move(board, moves[j]) == 1)
            {
                // make the move
                make_move(board, moves[j]);
                // check recursively if the move leads to a solution
                if (solve(board) == 1)
                {
                    // print the board
                    print_board(board);
                    // undo the move
                    unmake_move(board, moves[j]);
                    return 1;
                }
                else
                {
                    // if not, undo the move
                    unmake_move(board, moves[j]);
                }
            }
        }
    }
    return 0;
}


int main(int argc, char** argv)
{
    int board[15];
    triangle_input(board);

    printf("\n--------------------------------\n");

    int copiedBoard[25];
    convertBoard(board, copiedBoard);

    // print array, 5 entries per line
    printf("Board: ");
    for (int i = 0; i < 25; i++)
    {
        printf("%d ", copiedBoard[i]);
        if (i % 5 == 4)
        {
            printf("\n");
        }
    }

    if (solve(copiedBoard) == 0)
    {
        printf("No solution found.\n");
    }
    else
    {
        print_board(copiedBoard);
        printf("Solution found.\n");
    }
    return 0;
}