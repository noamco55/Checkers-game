

#include "Main Header.h"



/***  PROTOTYPES  ***/


void PlayGame(Board board, Player starting_player);
void printBoard(Board board);
void printPlusMinusLine();
void printNumbersForCols();
void checkIfToolInEndBoard(Board board, Player playerTurn, int* ENDGAME);
void checkToolsLeft(Board board, Player playerTurn, int* ENDGAME);
void checkToolsLeft(Board board, Player rival, int* ENDGAME);

/***  IMTLEMENTS  ***/

void PlayGame(Board board, Player starting_player)
{
	int ENDGAME = 0;
	printBoard(board);
	int MakeCapture = 0;
	Player playerTurn = starting_player;

	while (!ENDGAME)
	{
		if (playerTurn == 'T')
			printf("Player TOP_DOWN's turn\n");
		else
			printf("Player BOTTOM_UP's turn\n");

		Turn(board, playerTurn);
		checkIfToolInEndBoard(board, playerTurn, &ENDGAME);
		if (playerTurn == 'T')
			playerTurn = 'B';
		else
			playerTurn = 'T';
		if (!ENDGAME)
			checkToolsLeft(board, playerTurn, &ENDGAME);
	}
}

void checkIfToolInEndBoard(Board board, Player playerTurn, int* ENDGAME)
{
	int i;

	if (playerTurn == 'T')
	{
		for (i = 0; i < BOARD_SIZE && !*ENDGAME; i++)
		{
			if (board[BOARD_SIZE - 1][i] == playerTurn)
				*ENDGAME = 1;
		}
	}
	else
	{
		for (i = 0; i < BOARD_SIZE && !*ENDGAME; i++)
		{
			if (board[0][i] == playerTurn)
				*ENDGAME = 1;
		}
	}
}

void checkToolsLeft(Board board, Player rival, int* ENDGAME)
{
	int i, j;

	for (i = 0; i < BOARD_SIZE && !*ENDGAME; i++)
	{
		for (j = 0; j < BOARD_SIZE && !*ENDGAME; j++)
		{
			if (board[i][j] == rival)
				*ENDGAME = 1;
		}
	}
}

void printBoard(Board board)
{
	int i, j, row, col;
	char sign = '+';

	printPlusMinusLine();
	printNumbersForCols();
	printPlusMinusLine();

	for (i = 0; i < BOARD_SIZE; i++)
	{
		printf("|%c", 'A' + i);
		for (j = 0; i < BOARD_SIZE; i++)
		{
			printf("|%c", board[i][j]);
		}
		printf("|\n");
		printPlusMinusLine();
	}

}

void printPlusMinusLine()
{
	int i;

	for (i = 0; i < BOARD_SIZE * 2; i++)
	{
		if (i % 2 == 0)
			printf("+");
		else
			printf("-");
	}
	printf("\n");
}

void printNumbersForCols()
{
	int i;

	printf("| ");
	for (i = 1; i <= BOARD_SIZE; i++)
	{
		printf("|%d", i);
	}
	printf("|\n");
}
