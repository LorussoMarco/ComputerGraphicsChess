#pragma once
#include <string>

class Piece
{
public:

	Piece();
	Piece(const int id, const int row, const int col, const std::string name,const bool color);

	// Getter
	int getId() const;
	int getCol() const;
	int getRow() const;
	std::string getName() const;
	bool getColor() const;

	// Setter
	void setCol(const int newCol);
	void setRow(const int newRow);
	void setName(const std::string newName);

private:

	int _id;	// Id 
	int _col;	// Colonna in cui è il pezzo
	int _row;	// Riga in qui è il pezzo
	std::string _name; //Nome del pezzo
	bool _color; //0->black,1->white
};
