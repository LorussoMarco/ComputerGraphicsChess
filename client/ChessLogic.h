#pragma once

#include "Direction.h"
#include "Piece.h"

#include <engine.h>
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
    static std::vector<Piece> getPieces(); // Modificato per essere statico
    static bool isPieceSelected();
    static void printPieces();
    static void undoLastMove();
    static void redoLastMove();

    /**
     * @brief Resetta lo stato logico del gioco di scacchi.
     *
     * Questa funzione ripristina la logica degli scacchi, reimpostando la scacchiera
     * e ripopolando i pezzi nello stato iniziale.
     */
    static void resetLogic();

    static bool isWhiteTurn();
    static void setWhiteTurn(bool isWhite);

    static bool isMoveInProgress();
    static void setMoveInProgress(bool isInProgress);
    static std::string getWinner();

private:
    static void updateGraphics(Direction direction);
    static Piece _selectedPiece;   // Pezzo selezionato
    static std::vector<Piece> _pieces; // Stato dei pezzi
    static bool _isPieceSelected;
    static bool _isWhiteTurn;
    static bool _isMoveInProgress;
    static std::string _winner;
};
