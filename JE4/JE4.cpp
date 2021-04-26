#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include "time.h"
#include <stdio.h>
//#include <dos.h>
//#include <windows.h>

using namespace std;

enum Piece {
	BlackKing = -2,
	Black = -1,
	Empty = 0,
	White = 1,
	WhiteKing = 2
};

struct BoardEval
{
	string move;
	int evaluation;
};

bool isWhite(int board[8][8], unsigned int row, unsigned int collumn) {
	if (board[row][collumn] > Empty) return true;
	else return false;
}

bool isBlack(int board[8][8], unsigned int row, unsigned int collumn) {
	if (board[row][collumn] < Empty) return true;
	else return false;
}



void assignBoard(int board1[8][8], int board2[8][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board1[i][j] = board2[i][j];
		}
	}
}

void printBoard(int board[8][8])
{
	std::cout << "  1 2 3 4 5 6 7 8\n";
	for (int i = 0; i < 8; i++)
	{
		std::cout << i + 1 << " ";
		for (int j = 0; j < 8; j++)
		{
			switch (board[i][j]) {
				case Empty:
					if ((i + j) % 2 == 0)
						std::cout << " " << " ";
					else
						std::cout << "-" << " ";
					break;
				case BlackKing:
					std::cout << "B" << " ";
					break;
				case Black:
					std::cout << "b" << " ";
					break;
				case White:
					std::cout << "w" << " ";
					break;
				case WhiteKing:
					std::cout << "W" << " ";
					break;

			}
			/*
			if (board[i][j] == 0 && (i + j) % 2 == 0)
				std::cout << " " << " ";
			if (board[i][j] == 0 && (i + j) % 2 == 1)
				std::cout << "-" << " ";
			if (board[i][j] == 1)
				std::cout << "w" << " ";
			if (board[i][j] == 2)
				std::cout << "W" << " ";
			if (board[i][j] == -1)
				std::cout << "b" << " ";
			if (board[i][j] == -2)
				std::cout << "B" << " ";
			*/
		}

		std::cout << endl;
	}
}

int isInDanger(int board[8][8], int r, int c, int colour)
{
	if (r == 0 || r == 7 || c == 0 || c == 7)
	{
		return 2;
	}

	if (colour > 0)
	{
		if (board[r - 1][c - 1] < Empty && board[r + 1][c + 1] == Empty)
		{
			return 1;
		}
		if (board[r - 1][c + 1] < Empty && board[r + 1][c - 1] == Empty)
		{
			return 1;
		}
		if (board[r + 1][c - 1] == BlackKing && board[r - 1][c + 1] == Empty)
		{
			return 1;
		}
		if (board[r + 1][c + 1] == BlackKing && board[r - 1][c - 1] == Empty)
		{
			return 1;
		}
	}
	else
	{
		if (board[r + 1][c - 1] > Empty && board[r - 1][c + 1] == Empty)
		{
			return 1;
		}
		if (board[r + 1][c + 1] > Empty && board[r - 1][c - 1] == Empty)
		{
			return 1;
		}
		if (board[r - 1][c - 1] == WhiteKing && board[r + 1][c + 1] == Empty)
		{
			return 1;
		}
		if (board[r - 1][c + 1] == WhiteKing && board[r + 1][c - 1] == Empty)
		{
			return 1;
		}
	}

	return 2;
}

int isPassed(int board[8][8], int r, int c, int colour)
{
	if (colour == 1)
	{
		if (r == 2 && c == 1)
		{
			if (board[1][0] >= Empty && board[0][1] >= Empty)
			{
				return 1;
			}
			if (board[1][2] >= Empty && board[0][1] >= Empty && board[0][3] >= Empty)
			{
				return 1;
			}
		}
		if (r == 2 && c == 3)
		{
			if (board[0][1] >= Empty && board[1][2] >= 0 && board[0][3] >= Empty)
			{
				return 1;
			}
			if (board[1][4] >= Empty && board[0][5] >= Empty && board[0][3] >= Empty)
			{
				return 1;
			}
		}
		if (r == 2 && c == 5)
		{
			if (board[1][4] >= Empty && board[0][3] >= Empty && board[0][5] >= Empty)
			{
				return 1;
			}
			if (board[1][6] >= Empty && board[0][5] >= Empty && board[0][7] >= Empty)
			{
				return 1;
			}
		}
		if (r == 2 && c == 7)
		{
			if (board[1][6] >= Empty && board[0][5] >= Empty && board[0][7] >= Empty)
			{
				return 1;
			}
		}

		if (r == 1 && c == 0)
		{
			if (board[0][1] >= Empty)
			{
				return 1;
			}
		}
		if (r == 1 && c == 2)
		{
			if (board[0][1] >= Empty && board[0][3] >= Empty)
			{
				return 1;
			}
		}
		if (r == 1 && c == 4)
		{
			if (board[0][3] >= Empty && board[0][5] >= Empty)
			{
				return 1;
			}
		}
		if (r == 1 && c == 6)
		{
			if (board[0][5] >= Empty && board[0][7] >= Empty)
			{
				return 1;
			}
		}
	}

	if (colour == -1)
	{
		if (r == 5 && c == 6)
		{
			if (board[6][7] <= Empty && board[7][6] <= Empty)
			{
				return 1;
			}
			if (board[6][5] <= Empty && board[7][6] <= Empty && board[7][4] <= Empty)
			{
				return 1;
			}
		}
		if (r == 5 && c == 4)
		{
			if (board[6][5] <= Empty && board[7][6] <= Empty && board[7][4] <= Empty)
			{
				return 1;
			}
			if (board[6][3] <= Empty && board[7][4] <= Empty && board[7][2] <= Empty)
			{
				return 1;
			}
		}
		if (r == 5 && c == 2)
		{
			if (board[6][3] <= Empty && board[7][4] <= Empty && board[7][2] <= Empty)
			{
				return 1;
			}
			if (board[6][1] <= Empty && board[7][2] <= Empty && board[7][0] <= Empty)
			{
				return 1;
			}
		}
		if (r == 5 && c == 0)
		{
			if (board[6][1] <= Empty && board[7][2] <= Empty && board[7][0] <= Empty)
			{
				return 1;
			}
		}

		if (r == 6 && c == 7)
		{
			if (board[7][6] <= Empty)
			{
				return 1;
			}
		}
		if (r == 6 && c == 5)
		{
			if (board[7][6] <= Empty && board[7][4] <= Empty)
			{
				return 1;
			}
		}
		if (r == 6 && c == 3)
		{
			if (board[7][4] <= Empty && board[7][2] <= Empty)
			{
				return 1;
			}
		}
		if (r == 6 && c == 1)
		{
			if (board[7][2] <= Empty && board[7][0] <= Empty)
			{
				return 1;
			}
		}
	}

	return 0;
}

int staticEvaluation(int board[8][8])
{
	int sum = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			sum += board[i][j] * isInDanger(board, i, j, board[i][j]) + isPassed(board, i, j, board[i][j]);
		}
	}

	return sum;
}

bool isOnBoard(int num)
{
	if (num >= 0 && num <= 7)
	{
		return true;
	}
	else
	{
		return false;
	}
}

vector <string> currentAttacks;

void possibleAttacks(int board[8][8], int row, int column, string previousMoves) //previousMove initially "column+row"
{
	int newBoard[8][8];
	string move;
	bool isAttackFinished = true;

	int colour = board[row][column];

	if (colour > 0)
	{
		assignBoard(newBoard, board);

		if (isOnBoard(row - 1) && isOnBoard(column - 1) && isOnBoard(row - 2) && isOnBoard(column - 2))
		{
			if (board[row - 1][column - 1] < Empty && board[row - 2][column - 2] == Empty)
			{
				isAttackFinished = false;

				move = previousMoves;

				move += "-" + to_string(row) + to_string(column) + "-" + to_string(row - 1) + to_string(column - 1);

				if (row - 2 == 0)
				{
					newBoard[row][column] = 0;
					newBoard[row - 1][column - 1] = 0;
					newBoard[row - 2][column - 2] = WhiteKing;
					possibleAttacks(newBoard, row - 2, column - 2, move);
				}
				else
				{
					newBoard[row][column] = 0;
					newBoard[row - 1][column - 1] = 0;
					newBoard[row - 2][column - 2] = colour;
					possibleAttacks(newBoard, row - 2, column - 2, move);
				}
			}
		}

		assignBoard(newBoard, board);

		if (isOnBoard(row - 1) && isOnBoard(column + 1) && isOnBoard(row - 2) && isOnBoard(column + 2))
		{
			if (board[row - 1][column + 1] < Empty && board[row - 2][column + 2] == Empty)
			{
				isAttackFinished = false;

				move = previousMoves;

				move += "-" + to_string(row) + to_string(column + 2) + "-" + to_string(row - 1) + to_string(column + 3);

				if (row - 2 == 0)
				{
					newBoard[row][column] = 0;
					newBoard[row - 1][column + 1] = 0;
					newBoard[row - 2][column + 2] = WhiteKing;
					possibleAttacks(newBoard, row - 2, column + 2, move);
				}
				else
				{
					newBoard[row][column] = 0;
					newBoard[row - 1][column + 1] = 0;
					newBoard[row - 2][column + 2] = colour;
					possibleAttacks(newBoard, row - 2, column + 2, move);
				}
			}
		}
	}

	if (colour < 0)
	{
		assignBoard(newBoard, board);

		if (isOnBoard(row + 1) && isOnBoard(column - 1) && isOnBoard(row + 2) && isOnBoard(column - 2))
		{
			if (board[row + 1][column - 1] > Empty && board[row + 2][column - 2] == Empty)
			{
				isAttackFinished = false;

				move = previousMoves;

				move += "-" + to_string(row + 2) + to_string(column) + "-" + to_string(row + 3) + to_string(column - 1);

				if (row + 2 == 7)
				{
					newBoard[row][column] = 0;
					newBoard[row + 1][column - 1] = 0;
					newBoard[row + 2][column - 2] = BlackKing;
					possibleAttacks(newBoard, row + 2, column - 2, move);
				}
				else
				{
					newBoard[row][column] = 0;
					newBoard[row + 1][column - 1] = 0;
					newBoard[row + 2][column - 2] = colour;
					possibleAttacks(newBoard, row + 2, column - 2, move);
				}
			}
		}

		assignBoard(newBoard, board);

		if (isOnBoard(row + 1) && isOnBoard(column + 1) && isOnBoard(row + 2) && isOnBoard(column + 2))
		{
			if (board[row + 1][column + 1] > Empty && board[row + 2][column + 2] == Empty)
			{
				isAttackFinished = false;

				move = previousMoves;

				move += "-" + to_string(row + 2) + to_string(column + 2) + "-" + to_string(row + 3) + to_string(column + 3);

				if (row - 2 == 7)
				{
					newBoard[row][column] = 0;
					newBoard[row + 1][column + 1] = 0;
					newBoard[row + 2][column + 2] = BlackKing;
					possibleAttacks(newBoard, row + 2, column + 2, move);
				}
				else
				{
					newBoard[row][column] = 0;
					newBoard[row + 1][column + 1] = 0;
					newBoard[row + 2][column + 2] = colour;
					possibleAttacks(newBoard, row + 2, column + 2, move);
				}
			}
		}
	}

	if (colour == 2)
	{
		assignBoard(newBoard, board);

		if (isOnBoard(row + 1) && isOnBoard(column - 1) && isOnBoard(row + 2) && isOnBoard(column - 2))
		{
			if (board[row + 1][column - 1] < Empty && board[row + 2][column - 2] == Empty)
			{
				isAttackFinished = false;

				move = previousMoves;

				move += "-" + to_string(row + 2) + to_string(column) + "-" + to_string(row + 3) + to_string(column - 1);

				newBoard[row][column] = 0;
				newBoard[row + 1][column - 1] = 0;
				newBoard[row + 2][column - 2] = WhiteKing;
				possibleAttacks(newBoard, row + 2, column - 2, move);
			}
		}

		assignBoard(newBoard, board);

		if (isOnBoard(row + 1) && isOnBoard(column + 1) && isOnBoard(row + 2) && isOnBoard(column + 2))
		{
			if (board[row + 1][column + 1] < Empty && board[row + 2][column + 2] == Empty)
			{
				isAttackFinished = false;

				move = previousMoves;

				move += "-" + to_string(row + 2) + to_string(column + 2) + "-" + to_string(row + 3) + to_string(column + 3);

				newBoard[row][column] = 0;
				newBoard[row + 1][column + 1] = 0;
				newBoard[row + 2][column + 2] = WhiteKing;
				possibleAttacks(newBoard, row + 2, column + 2, move);
			}
		}
	}

	if (colour == -2)
	{
		assignBoard(newBoard, board);

		if (isOnBoard(row - 1) && isOnBoard(column - 1) && isOnBoard(row - 2) && isOnBoard(column - 2))
		{
			if (board[row - 1][column - 1] > Empty && board[row - 2][column - 2] == Empty)
			{
				isAttackFinished = false;

				move = previousMoves;

				move += "-" + to_string(row) + to_string(column) + "-" + to_string(row - 1) + to_string(column - 1);

				newBoard[row][column] = 0;
				newBoard[row - 1][column - 1] = 0;
				newBoard[row - 2][column - 2] = BlackKing;
				possibleAttacks(newBoard, row - 2, column - 2, move);
			}
		}

		assignBoard(newBoard, board);

		if (isOnBoard(row - 1) && isOnBoard(column + 1) && isOnBoard(row - 2) && isOnBoard(column + 2))
		{
			if (board[row - 1][column + 1] > Empty && board[row - 2][column + 2] == Empty)
			{
				isAttackFinished = false;

				move = previousMoves;

				move += "-" + to_string(row) + to_string(column + 2) + "-" + to_string(row - 1) + to_string(column + 3);

				newBoard[row][column] = 0;
				newBoard[row - 1][column + 1] = 0;
				newBoard[row - 2][column + 2] = BlackKing;
				possibleAttacks(newBoard, row - 2, column + 2, move);
			}
		}
	}

	if (isAttackFinished && previousMoves.length() > 2)
	{
		currentAttacks.push_back(previousMoves);
	}
}

vector <string> vectorPossibleCaptures(int board[8][8], int row, int column)
{
	currentAttacks.clear();
	possibleAttacks(board, row, column, to_string(row + 1) + to_string(column + 1));
	return currentAttacks;
}

vector <string> findAllAttacks(int board[8][8], bool white)
{
	vector <string> attacks;
	vector <string> allAttacks;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i % 2 == 0 && j % 2 == 0) continue;
			if (i % 2 == 1 && j % 2 == 1) continue;
			if (white == 1 && isWhite(board,i,j) || white == 0 && isBlack(board, i, j))
			{
				attacks = vectorPossibleCaptures(board, i, j);
			}

			for (int n = 0; n < attacks.size(); n++)
			{
				allAttacks.push_back(attacks[n]);
			}
		}
	}

	sort(allAttacks.begin(), allAttacks.end());
	auto iter = unique(allAttacks.begin(), allAttacks.end());
	allAttacks.erase(iter, allAttacks.end());

	return allAttacks;
}

vector <string> possibleMoves(int board[8][8], int row, int column)
{
	vector <string> allPossibleMoves;

	string move;

	int colour = board[row][column];

	if (colour > 0 || colour == -2)
	{
		if (isOnBoard(row - 1) && isOnBoard(column - 1))
		{
			if (board[row - 1][column - 1] == Empty)
			{
				move = to_string(row + 1) + to_string(column + 1) + "-" + to_string(row) + to_string(column);
				allPossibleMoves.push_back(move);
			}
		}

		if (isOnBoard(row - 1) && isOnBoard(column + 1))
		{
			if (board[row - 1][column + 1] == Empty)
			{
				move = to_string(row + 1) + to_string(column + 1) + "-" + to_string(row) + to_string(column + 2);
				allPossibleMoves.push_back(move);
			}
		}
	}

	if (colour < 0 || colour == 2)
	{
		if (isOnBoard(row + 1) && isOnBoard(column - 1))
		{
			if (board[row + 1][column - 1] == Empty)
			{
				move = to_string(row + 1) + to_string(column + 1) + "-" + to_string(row + 2) + to_string(column);
				allPossibleMoves.push_back(move);
			}
		}

		if (isOnBoard(row + 1) && isOnBoard(column + 1))
		{
			if (board[row + 1][column + 1] == Empty)
			{
				move = to_string(row + 1) + to_string(column + 1) + "-" + to_string(row + 2) + to_string(column + 2);
				allPossibleMoves.push_back(move);

			}
		}
	}

	return allPossibleMoves;
}

vector <string> findAllMoves(int board[8][8], bool white)
{
	vector <string> moves;
	vector <string> allMoves;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (white == 1 && isWhite(board, i, j) || white == 0 && isBlack(board, i, j))
				moves = possibleMoves(board, i, j);

			for (int n = 0; n < moves.size(); n++)
			{
				allMoves.push_back(moves[n]);
			}
		}
	}

	sort(allMoves.begin(), allMoves.end());
	auto iter = unique(allMoves.begin(), allMoves.end());
	allMoves.erase(iter, allMoves.end());

	return allMoves;
}

void executeAction(int board[8][8], string move, int outBoard[8][8])
{
	assignBoard(outBoard, board);

	int colourOfFigure = board[move[0] - 1 - '0'][move[1] - 1 - '0'];
	bool isPromoted = false;

	for (int i = 0; i < move.length(); i += 3)
	{
		int row = move[i] - 1 - '0';
		int column = move[i + 1] - 1 - '0';

		outBoard[row][column] = 0;

		if ((colourOfFigure == 1 && row == 0) || (colourOfFigure == -1 && row == 7))
		{
			isPromoted = true;
		}
	}

	int lastHopRow = move[move.length() - 2] - 1 - '0';
	int lastHopColumn = move[move.length() - 1] - 1 - '0';

	outBoard[lastHopRow][lastHopColumn] = colourOfFigure + colourOfFigure * isPromoted;
}

vector <string> findPossibleActions(int board[8][8], int colour)
{
	vector <string> attacks = findAllAttacks(board, colour > 0);
	vector <string> moves = findAllMoves(board, colour > 0);

	if (attacks.size() == 0)
	{
		return moves;
	}
	else
	{
		return attacks;
	}
}

BoardEval minMax(int board[8][8], int depth, int alpha, int beta, bool isWhite)
{
	BoardEval bEval;

	if (depth == 0)
	{
		bEval.move = "";
		bEval.evaluation = staticEvaluation(board);
		return bEval;
	}

	auto possibleActions = findPossibleActions(board, isWhite);

	if (possibleActions.size() == 0)
	{
		auto evaluation = staticEvaluation(board);
		auto isWhiteWon = evaluation > 0;
		bEval.move = "";
		bEval.evaluation = isWhiteWon ? 999 : -999;
		return bEval;
	}

	auto bestEval = (isWhite ? -1 : 1) * 999;
	string bestAction;

	for (int i = 0; i < possibleActions.size(); i++)
	{
		auto action = possibleActions[i];
		int previewBoard[8][8];
		executeAction(board, action, previewBoard);
		auto potentialBEval = minMax(previewBoard, depth - 1, alpha, beta, isWhite == false);
		auto eval = potentialBEval.evaluation;

		if (isWhite)
		{
			if (eval > bestEval) // || eval == bestEval && rand() % 100 < 1) //randomness
			{
				bestEval = eval;
				bestAction = action;
			}

			alpha = max(alpha, eval);

			if (beta <= alpha)
			{
				break;
			}

		}
		else
		{
			if (eval < bestEval) //|| eval == bestEval && rand() % 100 < 1) //randomness
			{
				bestEval = eval;
				bestAction = action;
			}

			beta = min(beta, eval);

			if (beta <= alpha)
			{
				break;
			}
		}
	}

	bEval.move = bestAction;
	bEval.evaluation = bestEval;

	return bEval;
}

void printStringVector(vector <string> allAtk)
{
	std::cout << "size: " << allAtk.size() << endl;

	for (int i = 0; i < allAtk.size(); i++)
	{
		std::cout << allAtk[i] << endl;
	}

	std::cout << endl;
}

int main()
{
	srand(time(NULL));

	
	int board[8][8] = { 0,-1, 0,-1, 0,-1, 0,-1,
					   -1, 0,-1, 0,-1, 0,-1, 0,
						0,-1, 0,-1, 0,-1, 0,-1,
						0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0,
						1, 0, 1, 0, 1, 0, 1, 0,
						0, 1, 0, 1, 0, 1, 0, 1,
						1, 0, 1, 0, 1, 0, 1, 0, };
	
	/*
	int board[8][8] = { 0, 0, 0, 0, 0, 0, 0, 0,
					    0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 1, 0, 1, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0,
						0, 1, 0, 1, 0, 1, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0,
						0, 1, 0, 0, 0, 0, 0, 0,
						0, 0, -2, 0, 0, 0, 0, 0, };
	*/

	printBoard(board);

	auto action = "67-56-45-34-23";
	int previewBoard[8][8];

	bool gameOver = false;
	bool isWhite = true;

	int gameMode = 0;
	int drawCounter = 0;
	string playerMove;
	bool isLegalMove = false;
	vector <string> possibleActions;

	std::cout << "Player vs Player: 1" << endl << "Player vs Computer: 2" << endl << "Computer vs Computer: 3" << endl;

	do
	{
		std::cout << "Select proper game mode : ";
		cin >> gameMode;
		std::cout << endl;
	} while (gameMode != 1 && gameMode != 2 && gameMode != 3);

	if (gameMode == 1)
	{
		while (!gameOver)
		{
			BoardEval eval = minMax(board, 3, -1000, 1000, isWhite);

			if (eval.move == "")
			{
				gameOver = true;
				std::cout << "GAME OVER" << endl;
			}
			else
			{
				if (isWhite)
				{
					isLegalMove = false;

					while (isLegalMove == false)
					{
						std::cout << "White to move: ";
						cin >> playerMove;
						isLegalMove = false;
						possibleActions = findPossibleActions(board, isWhite);

						for (int i = 0; i < possibleActions.size(); i++)
						{
							if (possibleActions[i] == playerMove)
							{
								isLegalMove = true;
							}
						}
					}

					executeAction(board, playerMove, previewBoard);

					printBoard(previewBoard);

					std::cout << "Evaluation: " << eval.evaluation << endl;

					assignBoard(board, previewBoard);

					isWhite = !isWhite;
				}
				else
				{
					isLegalMove = false;

					while (isLegalMove == false)
					{
						std::cout << "Black to move: ";
						cin >> playerMove;
						isLegalMove = false;
						possibleActions = findPossibleActions(board, isWhite);

						for (int i = 0; i < possibleActions.size(); i++)
						{
							if (possibleActions[i] == playerMove)
							{
								isLegalMove = true;
							}
						}
					}

					executeAction(board, playerMove, previewBoard);

					printBoard(previewBoard);

					std::cout << "Evaluation: " << eval.evaluation << endl;

					assignBoard(board, previewBoard);

					isWhite = !isWhite;
				}
			}
		}
	}

	if (gameMode == 2)
	{
		while (!gameOver)
		{
			BoardEval eval = minMax(board, 3, -1000, 1000, isWhite);

			if (eval.move == "")
			{
				gameOver = true;
				std::cout << "GAME OVER" << endl;
			}
			else
			{
				if (isWhite)
				{
					isLegalMove = false;

					do
					{
						

						possibleActions = findPossibleActions(board, isWhite);

						for (string action : possibleActions) {
							std::cout << action << "\n";
						}

						std::cout << "Provide move in form [r][c]-[r][c] like 63-52 or 56-45-34 with all traversed squares\n";
						std::cout << "White to move: ";
						cin >> playerMove;

						for (string legalAction : possibleActions)
						{
							if (legalAction == playerMove)
							{
								
								isLegalMove = true;
								break;
							}
						}

						if (!isLegalMove) std::cout << "Illegal move, provide a proper one!\n";

					} while (isLegalMove == false);

					executeAction(board, playerMove, previewBoard);

					printBoard(previewBoard);

					std::cout << "Evaluation: " << eval.evaluation << "\n\n";

					assignBoard(board, previewBoard);

					isWhite = !isWhite;
				}
				else
				{
					BoardEval eval = minMax(board, 3, -1000, 1000, isWhite);
					std::cout << "Black move : ";
					std::cout << eval.move << "\n";

					if (eval.move == "")
					{
						gameOver = true;
						std::cout << "GAME OVER" << endl;
					}
					else
					{
						executeAction(board, eval.move, previewBoard);

						printBoard(previewBoard);

						std::cout << "Evaluation: " << eval.evaluation << "\n\n";
					}

					assignBoard(board, previewBoard);

					isWhite = !isWhite;
				}
			}
		}
	}

	if (gameMode == 3)
	{
		int moves = 0;
		int depth = 3;
		isWhite = false;

		BoardEval eval = minMax(board, depth, -1000, 1000, isWhite);

		while (!gameOver)
		{
			moves++;
			depth = isWhite ? 3 : 3;

			if (isWhite) std::cout << "White move : ";
			else std::cout << "Black move : ";

			eval = minMax(board, depth, -1000, 1000, isWhite);

			if (eval.move == "")
			{
				gameOver = true;
				std::cout << "GAME OVER" << endl;
				std::cout << "Moves : " << moves << "\n";
			}
			else
			{
				std::cout << eval.move << "\n";
				executeAction(board, eval.move, previewBoard);
				//system("cls");
				printBoard(previewBoard);

				std::cout << "Evaluation: " << eval.evaluation << "\n\n";
			}

			assignBoard(board, previewBoard);

			isWhite = !isWhite;

			//Sleep(500);
		}
	}
}