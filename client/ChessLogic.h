#pragma once

#include "ChessBoard.h"
#include "Direction.h"
#include "Piece.h"

#include <Engine.h>
#include <PerspectiveCamera.h> 

class ChessLogic
{
public:

	ChessLogic();


	static void init();
	static void initialPopulate();
	static void selectPiece(const std::string& pieceName);
	static bool checkAndHandleCollisions();
	static void move(Direction direction);
	static void updateBlinking();
	std::vector<Piece> getPieces() const;
	static bool isPieceSelected();
	static void printPieces();

private:

	static void updateGraphics(Direction direction);
	static ChessBoard _chessBoard; // Board per giocare
	static Piece _selectedPiece;	 // Pezzo selezionato
	static std::vector<Piece> _pieces;
	static bool _isPieceSelected;
};