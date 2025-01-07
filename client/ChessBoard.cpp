#include "ChessBoard.h"

ChessBoard::ChessBoard()
{
	this->setSize(8);

	// Inizializza la matrice con dimensione 8x8 e tutti i valori a 0
	this->_board = std::vector<std::vector<int>>(this->getSize(), std::vector<int>(this->getSize(), 0));
}

// Getter

std::vector<std::vector<int>> ChessBoard::getBoard() const
{
	return this->_board;
}

int ChessBoard::getSize() const
{
	return this->_size;
}

int ChessBoard::getCell(const int row, const int col) const
{
	return this->_board[row][col];
}

// Setter
void ChessBoard::setCell(const int row, const int col, const int value)
{
	this->_board[row][col] = value;
}


void ChessBoard::setSize(const int newSize)
{
	this->_size = newSize;
}


//  Imposta ogni cella della matrice a 0
void ChessBoard::clean()
{
	for (auto& row : _board)
		std::fill(row.begin(), row.end(), 0);
}
