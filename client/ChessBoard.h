#pragma once

#include <iostream>
#include <vector>
#include "Mesh.h"

// Rappresenta la board per giocare (matrice)
class ChessBoard
{
public:

	ChessBoard();

	// Getter
	std::vector<std::vector<int>> getBoard() const;
	int getSize() const;
	int getCell(const int row, const int col) const;

	// Setter
	void setCell(const int row, const int col, const int value);
	void setSize(const int newSize);

	void clean();

private:

	int _size; // Size board
	std::vector<std::vector<int>> _board; // Matrice di interi
};
