#include "Piece.h"


Piece::Piece() 
{
	this->_id = -1;
	this->_row = -1;
	this->_col = -1;
	this->_color = false;
}

Piece::Piece(const int id,  const int row, const int col, const std::string name, const bool color)
{
	this->_id = id;
	this->setCol(col);
	this->setRow(row);
	this->_name = name;
	this->_color = color;
}

bool Piece::isNull() const {
	return _id == -1;
}

// Getter 

int Piece::getId() const
{
	return this->_id;
}

int Piece::getCol() const
{
	return this->_col;
}

int Piece::getRow() const
{
	return this->_row;
}

std::string Piece::getName() const 
{
	return this->_name;
}

bool Piece::getColor() const 
{
	return this->_color;
}


// Setter

void Piece::setCol(int newCol)
{
	this->_col = newCol;
}

void Piece::setRow(int newRow)
{
	this->_row = newRow;
}

void Piece::setName(std::string newName)
{
	this->_name = newName;
}
