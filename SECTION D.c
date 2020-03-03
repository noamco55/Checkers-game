
#include "Main Header.h"


/*** PROTOTYPES ***/


void Turn(Board board, Player player);
void UpDateBoard(Board board, SingleSourceMovesList* BestMove, Player player);
void printMove(SingleSourceMovesList* move);
void freeList(SingleSourceMovesList* List);
void DeleteFromBeginningOfList(SingleSourceMovesList* List);
void freeMuletipleLists(MultipleSourceMovesList* MainList);

/*** IMPLEMENTS ***/

void Turn(Board board, Player player)
{
	unsigned short MaxCaptures = 0, CurrCaptures;
	MultipleSourceMovesList* AllToolsMovesList = FindAllPossiblePlayerMoves(board, player);

	MultipleSourceMovesListCell* CurrAllToolsMovesListCell = AllToolsMovesList->head;

	SingleSourceMovesList* singleMovesList;

	SingleSourceMovesList* BestMove = NULL;

	while (CurrAllToolsMovesListCell)
	{
		singleMovesList = CurrAllToolsMovesListCell->single_source_moves_list;
		CurrCaptures = singleMovesList->tail->captures;
		if (MaxCaptures < CurrCaptures)
		{
			MaxCaptures = CurrCaptures;
			BestMove = singleMovesList;
		}
		else if (MaxCaptures == CurrCaptures)
		{
			if (BestMove == NULL)
				BestMove = singleMovesList;
			else if (singleMovesList->tail->position->row == 'A' || singleMovesList->tail->position->row == 'H')
				BestMove = singleMovesList;
		}
		CurrAllToolsMovesListCell = CurrAllToolsMovesListCell->next;
	}

	UpDateBoard(board, BestMove, player);

	printMove(BestMove);

	freeMuletipleLists(AllToolsMovesList);
}

void UpDateBoard(Board board, SingleSourceMovesList* BestMove, Player player)
{
	int change;
	Player rival;
	UpDatePlayerRivalChange(&change, player, &rival);

	SingleSourceMovesListCell* currMove = BestMove->head;

	checkersPos* prevPos;
	prevPos = createPos();

	if (BestMove->tail->captures == 0)
	{
		board[BestMove->head->position->row - 'A'][BestMove->head->position->col - '1'] = ' ';
		board[BestMove->tail->position->row - 'A'][BestMove->tail->position->col - '1'] = player;
	}
	else
	{
		prevPos->col = currMove->position->col;
		prevPos->row = currMove->position->row;
		currMove = currMove->next;
		while (currMove)
		{
			board[prevPos->row - 'A'][prevPos->col - '1'] = ' ';
			board[currMove->position->row - 'A'][currMove->position->col - '1'] = player;
			if (prevPos->col - '1' - currMove->position->col - '1' > 0)
				board[prevPos->row - 'A' - change][prevPos->col - '1' - 1] = ' ';
			else
				board[prevPos->row - 'A' - change][prevPos->col - '1' + 1] = ' ';

			prevPos->col = currMove->position->col;
			prevPos->row = currMove->position->row;
			currMove = currMove->next;
		}
	}


}

void printMove(SingleSourceMovesList* move)
{
	SingleSourceMovesListCell* currTool = move->head;

	printf("%c%c", currTool->position->row, currTool->position->col);
	currTool = currTool->next;

	while (currTool)
	{
		printf("->");
		printf("%c%c", currTool->position->row, currTool->position->col);

		currTool = currTool->next;
	}
	printf("\n");
}

void freeMuletipleLists(MultipleSourceMovesList* MainList)
{
	MultipleSourceMovesListCell* del_cell = MainList->head;

	while (MainList->head)
	{
		del_cell = MainList->head;
		MainList->head = MainList->head->next;
		if (MainList->head == NULL)
			MainList->tail = NULL;
		freeList(del_cell->single_source_moves_list);
		free(del_cell);
	}
	free(MainList);
}

void freeList(SingleSourceMovesList* List)
{
	while (List->head)
		DeleteFromBeginningOfList(List);
	free(List);
}

void DeleteFromBeginningOfList(SingleSourceMovesList* List)
{
	SingleSourceMovesListCell* del_cell = List->head;

	List->head = List->head->next;
	if (List->head == NULL)
		List->tail = NULL;
	free(del_cell->position);
	free(del_cell);
}
