
#include "Main Header.h"


/*** IMPLEMENTS ***/

// this function reads a short int from a binary file and set the board based on the data on the file 
void LoadBoard(char* filename, Board board)
{
	int row = 0, col;
	unsigned short line;
	unsigned short mask = 0xc000;
	FILE* fptr;

	fptr = fopen(filename, "rb");
	checkFile(fptr);

	while (!feof(fptr))
	{
		fread(&line, sizeof(unsigned short), 1, fptr);
		for (col = 0; col < BOARD_SIZE; col++)
		{
			if (line & mask == 0)
				board[row][col] = ' ';
			else if ((line & mask) << col * 2 + 1 == 0)
				board[row][col] = 'B';
			else
				board[row][col] = 'T';
			mask = mask >> 2;
		}
		row++;
		mask = 0xc000;
	}

	fclose(fptr);
}