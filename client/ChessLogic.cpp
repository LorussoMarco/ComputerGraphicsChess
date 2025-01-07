#include "ChessLogic.h"

ChessBoard ChessLogic::_chessBoard;
std::vector<Piece> ChessLogic::_pieces;
Piece ChessLogic::_selectedPiece;

ChessLogic::ChessLogic()
{
	this->_chessBoard = ChessBoard();
	this->_pieces = {};
}

std::vector<Piece> ChessLogic::getPieces() const
{
	return this->_pieces;
}

// Imposta la callback del lampeggio
void ChessLogic::init()
{
	initialPopulate();
	Engine::setBlinkingCallback(ChessLogic::updateBlinking);
	
}

void ChessLogic::selectPiece(const std::string& pieceName)
{
	// Resetta il colore di emissione del pezzo precedentemente selezionato
	std::string color = _selectedPiece.getColor() ? "White" : "Black";
	std::string fullName = color + _selectedPiece.getName() + "." + std::to_string(_selectedPiece.getId());

	std::shared_ptr<Mesh> prevSelectedPieceMesh = std::dynamic_pointer_cast<Mesh>(
		Engine::findObjectByName(fullName)
	);
	if (prevSelectedPieceMesh != nullptr)
	{
		prevSelectedPieceMesh->getMaterial()->setEmissionColor(glm::vec3(0.0f, 0.0f, 0.0f)); // Colore nero
	}

	if (pieceName == "none") 
	{
		_selectedPiece = Piece();
		return;
	}

	// Trova la mesh del nuovo pezzo selezionato
	std::shared_ptr<Mesh> selectedPieceMesh = std::dynamic_pointer_cast<Mesh>(
		Engine::findObjectByName(pieceName)
	);
	if (!selectedPieceMesh)
	{
		std::cerr << "Error: Piece mesh not found for name: " << pieceName << std::endl;
		return;
	}

	// Trova il pezzo nella lista `_pieces` e aggiorna `_selectedPiece`
	for (const auto& piece : _pieces)
	{
		// Costruisci il nome completo del pezzo per confrontarlo con `pieceName`
		std::string color = piece.getColor() ? "White" : "Black";
		std::string fullName = color + piece.getName() + "." + std::to_string(piece.getId());

		if (fullName == pieceName)
		{
			_selectedPiece = piece; // Copia diretta del pezzo trovato
			break;
		}
	}

	std::cout << "Selected piece: " << pieceName << std::endl;

}





// Esegue una mossa nella direction passata come parametro
void ChessLogic::move(const Direction direction)
{
	// Variabili per tracciare le nuove coordinate
	int newRow = _selectedPiece.getRow();
	int newCol = _selectedPiece.getCol();

	// Calcola le nuove coordinate in base alla direzione
	switch (direction)
	{
	case Direction::UP:
		if (newRow > 0) newRow--;
		break;

	case Direction::LEFT:
		if (newCol > 0) newCol--;
		break;

	case Direction::DOWN:
		if (newRow < 7) newRow++;
		break;

	case Direction::RIGHT:
		if (newCol < 7) newCol++;
		break;

	default:
		std::cerr << "Error: Invalid direction!" << std::endl;
		return;
	}

	// Controlla se la posizione è cambiata
	if (newRow == _selectedPiece.getRow() && newCol == _selectedPiece.getCol())
	{
		// Nessun movimento valido, esci senza aggiornare
		std::cout << "Move out of range. No update performed." << std::endl;
		return;
	}

	// Aggiorna le coordinate del pezzo
	_selectedPiece.setRow(newRow);
	_selectedPiece.setCol(newCol);

	// Stampa la posizione aggiornata
	std::cout << "Row: " << _selectedPiece.getRow() << ", Col: " << _selectedPiece.getCol() << std::endl;

	// Aggiorna la grafica
	ChessLogic::updateGraphics(direction);
}


void ChessLogic::updateGraphics(Direction direction)
{
	// Costruisci il nome completo del pezzo selezionato
	std::string selectedColor = _selectedPiece.getColor() ? "White" : "Black";
	std::string selectedFullName = selectedColor + _selectedPiece.getName() + "." + std::to_string(_selectedPiece.getId());

	// Trova il nodo corrispondente al pezzo selezionato
	std::shared_ptr<Node> pieceNode = std::dynamic_pointer_cast<Node>(
		Engine::findObjectByName(selectedFullName)
	);

	if (!pieceNode)
	{
		std::cerr << "Error: Node not found for selected piece: " << selectedFullName << std::endl;
		return;
	}

	// Ottieni la posizione corrente del nodo
	glm::vec3 currentPosition = pieceNode->getPosition();

	// Calcola la nuova posizione in base alla direzione
	glm::vec3 offset;
	switch (direction)
	{
	case Direction::UP:
		offset = glm::vec3(3.0f, 0.0f, 0.0f); // Spostamento verso l'alto
		break;
	case Direction::DOWN:
		offset = glm::vec3(-3.0f, 0.0f, 0.0f); // Spostamento verso il basso
		break;
	case Direction::LEFT:
		offset = glm::vec3(0.0f, 0.0f, -3.0f); // Spostamento a sinistra
		break;
	case Direction::RIGHT:
		offset = glm::vec3(0.0f, 0.0f, 3.0f); // Spostamento a destra
		break;
	default:
		std::cerr << "Error: Invalid direction!" << std::endl;
		return;
	}

	glm::vec3 newPosition = currentPosition + offset;

	// Imposta la nuova posizione
	pieceNode->setPosition(newPosition);

}



void ChessLogic::updateBlinking() {
	// Costruisci il nome completo del pezzo selezionato
	std::string color = _selectedPiece.getColor() ? "White" : "Black";
	std::string fullName = color + _selectedPiece.getName() + "." + std::to_string(_selectedPiece.getId());

	// Trova la mesh del pezzo selezionato
	std::shared_ptr<Mesh> selected_piece_mesh = std::dynamic_pointer_cast<Mesh>(Engine::findObjectByName(fullName));
	if (selected_piece_mesh != nullptr) {
		// Ottieni l'emissione corrente
		glm::vec3 currentEmission = selected_piece_mesh->getMaterial()->getEmissionColor();

		// Modifica l'emissione
		static bool increasing = true;
		if (increasing) {
			currentEmission += glm::vec3(0.2f); // Aumenta l'intensità
			if (currentEmission.r >= 1.0f) {
				increasing = false; // Inizia a diminuire quando l'intensità raggiunge il massimo
			}
		}
		else {
			currentEmission -= glm::vec3(0.2f); // Diminuisci l'intensità
			if (currentEmission.r <= 0.0f) {
				increasing = true; // Inizia a aumentare quando l'intensità raggiunge il minimo
			}
		}

		// Imposta la nuova emissione
		selected_piece_mesh->getMaterial()->setEmissionColor(currentEmission);
	}
}










void ChessLogic::initialPopulate()
{
	// Pedoni neri
	_pieces.push_back(Piece(10, 1, 0, "Pawn", 0));
	_pieces.push_back(Piece(11, 1, 1, "Pawn", 0));
	_pieces.push_back(Piece(12, 1, 2, "Pawn", 0));
	_pieces.push_back(Piece(13, 1, 3, "Pawn", 0));
	_pieces.push_back(Piece(14, 1, 4, "Pawn", 0));
	_pieces.push_back(Piece(15, 1, 5, "Pawn", 0));
	_pieces.push_back(Piece(16, 1, 6, "Pawn", 0));
	_pieces.push_back(Piece(9, 1, 7, "Pawn", 0));

	// Pedoni bianchi
	_pieces.push_back(Piece(8, 6, 0, "Pawn", 1));
	_pieces.push_back(Piece(9, 6, 1, "Pawn", 1));
	_pieces.push_back(Piece(10, 6, 2, "Pawn", 1));
	_pieces.push_back(Piece(11, 6, 3, "Pawn", 1));
	_pieces.push_back(Piece(12, 6, 4, "Pawn", 1));
	_pieces.push_back(Piece(13, 6, 5, "Pawn", 1));
	_pieces.push_back(Piece(14, 6, 6, "Pawn", 1));
	_pieces.push_back(Piece(15, 6, 7, "Pawn", 1));

	// Torri nere
	_pieces.push_back(Piece(3, 0, 0, "Rook", 0));
	_pieces.push_back(Piece(2, 0, 7, "Rook", 0));

	// Torri bianche
	_pieces.push_back(Piece(3, 7, 0, "Rook", 1));
	_pieces.push_back(Piece(2, 7, 7, "Rook", 1));

	// Cavalli neri
	_pieces.push_back(Piece(2, 0, 1, "Knight", 0));
	_pieces.push_back(Piece(3, 0, 6, "Knight", 0));

	// Cavalli bianchi
	_pieces.push_back(Piece(2, 7, 1, "Knight", 1));
	_pieces.push_back(Piece(3, 7, 6, "Knight", 1));

	// Alfieri neri
	_pieces.push_back(Piece(3, 0, 2, "Bishop", 0));
	_pieces.push_back(Piece(2, 0, 5, "Bishop", 0));

	// Alfieri bianchi
	_pieces.push_back(Piece(2, 7, 2, "Bishop", 1));
	_pieces.push_back(Piece(3, 7, 5, "Bishop", 1));

	// Regina nera
	_pieces.push_back(Piece(1, 0, 3, "Queen", 0));

	// Regina bianca
	_pieces.push_back(Piece(1, 7, 3, "Queen", 1));

	// Re nero
	_pieces.push_back(Piece(1, 0, 4, "King", 0));

	// Re bianco
	_pieces.push_back(Piece(1, 7, 4, "King", 1));
}