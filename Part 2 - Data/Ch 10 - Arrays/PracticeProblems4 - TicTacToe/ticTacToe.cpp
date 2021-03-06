#include <iostream>
#include <string>

using namespace std;

enum TicTacToeSquare
{
	TTTS_Blank,
	TTTS_O,
	TTTS_X
};

void populateGameBoard(TicTacToeSquare array[][3], int size);
string setPlayer(bool playerXInSession);
string translateEnumToString(TicTacToeSquare squareState);
bool validIndex(int boardPosition[], int boardSize);
bool choiceTaken(int boardPosition[], TicTacToeSquare gameBoard[][3]);
void setChoice(int boardPosition[], TicTacToeSquare gameBoard[][3], bool playerXInSession);
TicTacToeSquare choiceSquare(bool playerXInSession);
bool choiceWins(bool playerXInSession, TicTacToeSquare gameBoard[][3], int size);
bool boardIsFull(TicTacToeSquare gameBoard[][3], int size);

int main()
{
	bool gameFinished = false;
	bool playerXInSession = true;
	string player = "";
	int row = 0;
	int column = 0;
	
	// Set up game board
	int const size = 3;
	TicTacToeSquare gameBoard[size][size];
	populateGameBoard(gameBoard, size);

	do
	{
		// Set up current turn
		row = 0;
		column = 0;
		player = setPlayer(playerXInSession);

		// Draw board
		cout << "\n" << "Tic-Tac-Toe\n";
		string horizontalBar = " _";
		for (size_t i = 0; i < size; i++)
		{
			horizontalBar += "__";
		}
		
		for (size_t i = 0; i <= size; i++)
		{
			if (i == 0)
			{
				for (size_t j = 0; j <= size; j++)
				{
					if (j == 0)
					{
						cout << " ";
					}
					else 
					{
						cout << " " << j;
					}
				}
				cout << "\n";
			}
			else
			{
				cout << horizontalBar << "\n";
				for (size_t j = 0; j <= size; j++)
				{
					if (j == 0)
					{
						cout << i;
					}
					else 
					{
						cout << "|" << translateEnumToString(gameBoard[i - 1][j - 1]);
					}
				}
				cout << "|\n";
			}
		}
		cout << horizontalBar << "\n\n";

		cout << "Player " << player << ", choose your next board position to claim:\n";
		
		cout << "Row: \n";
		cin >> row;
		row--;

		cout << "Column: \n";
		cin >> column;
		column--;

		int boardPosition[2] = {row, column};

		// Check that choice is a valid index
		if (!validIndex(boardPosition, size))
		{
			cout << "That is an invalid choice. Please try again.\n";
			continue;
		}

		// Check that choice is not already taken
		if (choiceTaken(boardPosition, gameBoard))
		{
			cout << "That square is already taken. Please try again.\n";
			continue;
		}

		// Assign choice
		setChoice(boardPosition, gameBoard, playerXInSession);

		// Check whether choice wins the game
		if (choiceWins(playerXInSession, gameBoard, size))
		{
			cout << "Player " << player << " wins!\n";
			gameFinished = true;
		}

		// Check whether or the entire board is filled
		if (boardIsFull(gameBoard, size))
		{
			cout << "Board is full. The game is a tie!\n";
			gameFinished = true;
		}

		// Check if game cannot be won before the board is filled
		// Meh

		// Change turns
		playerXInSession = !playerXInSession;
	} while (!gameFinished);
}


void populateGameBoard(TicTacToeSquare array[][3], int size)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			array[i][j] = TTTS_Blank;
		}
	}
}

string setPlayer(bool playerXInSession)
{
	if (playerXInSession)
	{
		return "X";
	}
	return "O";
}

bool validIndex(int boardPosition[], int boardSize)
{
	return (((boardPosition[0] >= 0) && (boardPosition[1] >= 0)) &&
			((boardPosition[0] <= boardSize) && (boardPosition[1] <= boardSize)));
}

bool choiceTaken(int boardPosition[], TicTacToeSquare gameBoard[][3])
{
	return (gameBoard[boardPosition[0]][boardPosition[1]] != TTTS_Blank);
}

void setChoice(int boardPosition[], TicTacToeSquare gameBoard[][3], bool playerXInSession)
{
	gameBoard[boardPosition[0]][boardPosition[1]] = choiceSquare(playerXInSession);
}

TicTacToeSquare choiceSquare(bool playerXInSession)
{
	if (playerXInSession)
	{
		return TTTS_X;
	}
	return TTTS_O;
}

bool choiceWins(bool playerXInSession, TicTacToeSquare gameBoard[][3], int size)
{
	TicTacToeSquare choiceCheck = choiceSquare(playerXInSession);;
	double result;

	// Check rows
	for (size_t i = 0; i < size; i++)
	{
		result = 1;
		for (size_t j = 0; j < size; j++)
		{
			result *= (gameBoard[i][j] == choiceCheck);
		}
		if (result == 1) { return true; }
	}

	// Check columns
	for (size_t i = 0; i < size; i++)
	{
		result = 1;
		for (size_t j = 0; j < size; j++)
		{
			result *= (gameBoard[j][i] == choiceCheck);
		}
		if (result == 1) { return true; }
	}

	// Check diagonals
	result = 1;
	for (size_t i = 0; i < size; i++)
	{
		result *= (gameBoard[i][i] == choiceCheck);
	}
	if (result == 1) { return true; }

	result = 1;
	for (size_t i = 0; i < size; i++)
	{
		int maxIndex = size - 1;
		result *= (gameBoard[maxIndex - i][maxIndex - i] == choiceCheck);
	}
	if (result == 1) { return true; }

	return false;
}

bool boardIsFull(TicTacToeSquare gameBoard[][3], int size)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (gameBoard[i][j] == TTTS_Blank)
			{
				return false;
			}
		}
	}
	return true;
}

string translateEnumToString(TicTacToeSquare squareState)
{
	switch (squareState)
	{
		case TTTS_Blank:
			return " ";
		case TTTS_O:
			return "O";
		case TTTS_X:
			return "X";
		default:
			return "~";
	}
}