#include "triangle_routines.h"
#include <stdio.h>

int depth = 0;


/**
 * convert the index of 15er board to the index of 25er board
 * @param index the index of 15er board
 * @return the index of 25er board
 */
int convertIndex(int index)
{
    int row = index / 5;
    int col = index % 5;
    return row * 5 + col + row;
}


/**
 * convert the index of 25er board to the index of 15er board
 * @param index the index of 25er board
 * @return the index of 15er board
 */
int convertIndexBack(int i) {}


/**
 * takes a 15er board and converts it to a 25er board
 * @param oldBoard the 15er board
 * @param newBoard the 25er board
 */
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

/**
 * takes a 25er board and converts it to a 15er board
 * @param oldBoard the 25er board
 * @param newBoard the 15er board
 */
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

/**
 * takes a 25er board and prints it
 * @param board the 25er board
 */
void print_board(int board[])
{
    int tmpBoard[15];
    convertBoardBack(board, tmpBoard);
    triangle_print(tmpBoard);
}

/**
 * returns the number of entries on the board
 * @param board the 25er board
 * @return the number of entries on the board
 */
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


/**
 * check if the move is valid
 * @param board 25er board
 * @param move the move as a 3 tuple, in order: start, jump, end
 * @return 1 if the move is valid, 0 otherwise
 */
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


/**
 * make a move on this board
 * @param board 25er board
 * @param move the move as a 3 tuple, in order: start, jump, end
 */
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


/**
 * unmake this move on this board
 * @param board 25er board
 * @param move the move as a 3 tuple, in order: start, jump, end
 */
void unmake_move(int board[], int move[])
{
    /* undo what make_move did (, but only if the "reverse" move is valid)
       there could be some more checks that are not done, because the unmake_move function is only
       called after a valid move was made
    */
    if (board[move[0]] == 0 && board[move[1]] == 0 && board[move[2]] == 1 && move[0] >= 0
        && move[0] <= 24 && move[1] >= 0 && move[1] <= 24 && move[2] >= 0 && move[2] <= 24)
    {
        board[move[0]] = 1;
        board[move[1]] = 1;
        board[move[2]] = 0;
    }
}

/**
 * Solve the game starting from this board. Return 1 if the game can
 * be solved; otherwise return 0. Do not permanently alter the board
 * passed in. Once a solution is found, print the boards making up
 * the solution in reverse order.
 * 
 * @param board 25er board
 * @return 1 if the game can be solved, 0 otherwise
 */
int solve(int board[])
{
    // check if the board is already solved
    if (nentries(board) == 1)
    {
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
                depth++;
                if (solve(board) == 1)
                {
                    // print the board
                    printf("\n-------------------------------------\n");
                    printf("Step %d:\n", depth);
                    print_board(board);
                    // undo the move
                    unmake_move(board, moves[j]);
                    depth--;
                    return 1;
                }
                else
                {
                    // if not, undo the move
                    unmake_move(board, moves[j]);
                    depth--;
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

    int copiedBoard[25];
    convertBoard(board, copiedBoard);

    if (solve(copiedBoard) == 0)
    {
        printf("No solution found.\n");
    }
    else
    {
        printf("\n-------------------------------------\n");
        printf("Step %d (starting board):\n", depth);
        print_board(copiedBoard);
        printf("\n-------------------------------------\n");
        printf("Solution found.\n");
    }
    return 0;
}