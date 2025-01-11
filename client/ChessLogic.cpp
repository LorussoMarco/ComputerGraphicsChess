#include "ChessLogic.h"
#include <iomanip>

ChessBoard ChessLogic::_chessBoard;
std::vector<Piece> ChessLogic::_pieces;
Piece ChessLogic::_selectedPiece;
bool ChessLogic::_isPieceSelected = false;
bool ChessLogic::_isWhiteTurn = true;
bool ChessLogic::_isMoveInProgress = false;
std::string ChessLogic::_winner = "None";
bool isRedoPossible = false;
static glm::vec3 _redoPosition;

static Piece _lastSelectedPiece;
static glm::vec3 _originalPosition;
std::shared_ptr<Node> eliminatedPieceNode = nullptr;
Piece eliminatedPiece = Piece();
static int oldRow;
static int oldCol;

static int _redoRow;
static int _redoCol;

std::string ChessLogic::getWinner()
{
	return _winner;
}

bool ChessLogic::isWhiteTurn()
{
	return _isWhiteTurn;
}

void ChessLogic::setWhiteTurn(bool isWhite)
{
	_isWhiteTurn = isWhite;
}

bool ChessLogic::isMoveInProgress()
{
	return _isMoveInProgress;
}

void ChessLogic::setMoveInProgress(bool isInProgress)
{
	_isMoveInProgress = isInProgress;
}

bool ChessLogic::isPieceSelected()
{
	return _isPieceSelected;
}

ChessLogic::ChessLogic()
{
	this->_chessBoard = ChessBoard();
	this->_pieces = {};
}

std::vector<Piece> ChessLogic::getPieces()
{
	return _pieces;
}


bool ChessLogic::checkAndHandleCollisions()
{

	bool sameColor = false;
	_isPieceSelected = false;
	for (auto it = _pieces.begin(); it != _pieces.end(); )
	{

		// Costruisci il nome completo del pezzo corrente nell'iterazione
		std::string currentColor = it->getColor() ? "White" : "Black";
		std::string currentFullName = currentColor + it->getName() + "." + std::to_string(it->getId());

		// Costruisci il nome completo del pezzo selezionato
		std::string selectedColor = _selectedPiece.getColor() ? "White" : "Black";
		std::string selectedFullName = selectedColor + _selectedPiece.getName() + "." + std::to_string(_selectedPiece.getId());

		if (it->getCol() == _selectedPiece.getCol() &&
			it->getRow() == _selectedPiece.getRow() &&
			currentFullName != selectedFullName
			) // Confronta i nomi completi
		{

			if (it->getColor() == _selectedPiece.getColor())
			{
				sameColor = true;
				break;
			}

			if (it->getName() == "King")
			{
				_winner = _selectedPiece.getColor() ? "White" : "Black";
				std::cout << "Il re è stato catturato! Vince il giocatore " << _winner << "!" << std::endl;
				return true; // Indica che la collisione ha portato alla vittoria
			}

			// Trova il nodo del pezzo nella scena
			std::shared_ptr<Node> pieceNode = std::dynamic_pointer_cast<Node>(
				Engine::findObjectByName(currentFullName)
			);

			// Rimuovi il nodo dalla scena se esiste
			if (pieceNode)
			{

				eliminatedPieceNode = pieceNode;
				Engine::removeObject(pieceNode); // Rimuovi il nodo dalla scena
				_isPieceSelected = false;

				std::cout << "Removed piece from scene: " << currentFullName << std::endl;
			}
			eliminatedPiece = *it;
			// Rimuovi il pezzo dal vettore
			it = _pieces.erase(it); // Rimuove l'elemento e restituisce un iteratore valido
			_selectedPiece = Piece();
			_isMoveInProgress = false;
			_isWhiteTurn = !_isWhiteTurn;
			return true; // Esci dopo aver gestito la collisione
		}
		else
		{
			++it; // Incrementa l'iteratore solo se non si rimuove nulla
		}

	}
	if (sameColor == true) {
		_isPieceSelected = true;
	}
	else
	{
		_selectedPiece = Piece();
		_isMoveInProgress = false;
		_isWhiteTurn = !_isWhiteTurn;
	}
	return false; // Nessuna collisione trovata
}



// Imposta la callback del lampeggio
void ChessLogic::init()
{
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
		checkAndHandleCollisions();
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
			// Consenti solo di selezionare pezzi del colore corretto
			if (piece.getColor() != _isWhiteTurn)
			{
				std::cout << "Non è il turno del giocatore " << (piece.getColor() ? "bianco" : "nero") << "." << std::endl;
				return;
			}

			_lastSelectedPiece = piece;
			std::shared_ptr<Node> node = std::dynamic_pointer_cast<Node>(Engine::findObjectByName(fullName));
			if (node) {
				_originalPosition = node->getPosition();
				oldRow = piece.getRow();
				oldCol = piece.getCol();
				std::cout << "[DEBUG] Original position stored for piece " << pieceName << ": " << glm::to_string(_originalPosition) << std::endl;
			}

			_selectedPiece = piece; // Copia diretta del pezzo trovato
			std::cout << "Selected piece: " << piece.getRow() << ":::::" << piece.getCol() << std::endl;
			_isPieceSelected = true;
			_isMoveInProgress = true;
			break;
		}
	}

	std::cout << "Selected piece: " << pieceName << std::endl;
}

void ChessLogic::redoLastMove()
{
	if (isRedoPossible) 
	{
		std::string fullName = (_lastSelectedPiece.getColor() ? "White" : "Black") +
			_lastSelectedPiece.getName() + "." + std::to_string(_lastSelectedPiece.getId());

		auto node = std::dynamic_pointer_cast<Node>(Engine::findObjectByName(fullName));
		if (node) 
		{
			node->setPosition(_redoPosition);
			for (auto& piece : _pieces) {
				if (piece.getId() == _lastSelectedPiece.getId() && piece.getName() == _lastSelectedPiece.getName() && piece.getColor() == _lastSelectedPiece.getColor())
				{
					piece.setRow(_redoRow);
					piece.setCol(_redoCol);
					_selectedPiece = piece;
					checkAndHandleCollisions();
				}
			}
		}


	}
}


void ChessLogic::undoLastMove() {
	if (_lastSelectedPiece.isNull()) {
		std::cout << "[Info] Nessuna mossa da annullare." << std::endl;
		return;
	}
	if (eliminatedPieceNode != nullptr)
	{
		Engine::getScene()->addChild(eliminatedPieceNode);
		eliminatedPieceNode = nullptr;
		_pieces.push_back(eliminatedPiece);
	}

	// Trova il nodo corrispondente al pezzo selezionato
	std::string fullName = (_lastSelectedPiece.getColor() ? "White" : "Black") +
		_lastSelectedPiece.getName() + "." + std::to_string(_lastSelectedPiece.getId());

	auto node = std::dynamic_pointer_cast<Node>(Engine::findObjectByName(fullName));
	if (node) {
		// Ripristina la posizione originale
		_redoPosition = node->getPosition();
		 
		node->setPosition(_originalPosition);
		std::cout << "[Debug] Position restored for piece " << fullName << ": " << glm::to_string(_originalPosition) << std::endl;

		// Aggiorna lo stato logico del pezzo
		for (auto& piece : _pieces) {
			if (piece.getId() == _lastSelectedPiece.getId() && piece.getName() == _lastSelectedPiece.getName() && piece.getColor() == _lastSelectedPiece.getColor()) {
				_redoRow = piece.getRow();
				_redoCol = piece.getCol();

				piece.setRow(oldRow);
				piece.setCol(oldCol);
				break;
			}
		}
		isRedoPossible = true;
		
		_isPieceSelected = false;
		_isMoveInProgress = false;
		_isWhiteTurn = !_isWhiteTurn;
	}
	else {
		std::cout << "[Error] Node not found for piece: " << fullName << std::endl;
	}
}





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
		std::cout << "Move out of range. No update performed." << std::endl;
		return;
	}

	// Aggiorna le coordinate del pezzo selezionato
	_selectedPiece.setRow(newRow);
	_selectedPiece.setCol(newCol);

	// Aggiorna le coordinate nel vettore `_pieces`
	for (auto& piece : _pieces)
	{
		if (piece.getId() == _selectedPiece.getId() &&
			piece.getName() == _selectedPiece.getName() &&
			piece.getColor() == _selectedPiece.getColor())
		{
			piece.setRow(newRow);
			piece.setCol(newCol);
			break;
		}
	}

	// Aggiorna la grafica
	ChessLogic::updateGraphics(direction);

	// Segna che la mossa è in corso
	_isMoveInProgress = true;

	std::cout << "Mossa in corso. Row: " << _selectedPiece.getRow() << ", Col: " << _selectedPiece.getCol() << std::endl;
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
		offset = glm::vec3(2.85f, 0.0f, 0.0f); // Spostamento verso l'alto
		break;
	case Direction::DOWN:
		offset = glm::vec3(-2.85f, 0.0f, 0.0f); // Spostamento verso il basso
		break;
	case Direction::LEFT:
		offset = glm::vec3(0.0f, 0.0f, -2.85f); // Spostamento a sinistra
		break;
	case Direction::RIGHT:
		offset = glm::vec3(0.0f, 0.0f, 2.85f); // Spostamento a destra
		break;
	default:
		std::cerr << "Error: Invalid direction!" << std::endl;
		return;
	}

	glm::vec3 newPosition = currentPosition + offset;

	// Imposta la nuova posizione
	pieceNode->setPosition(newPosition);

	printPieces();

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

void ChessLogic::printPieces()
{
	std::cout << "========================================================\n";
	std::cout << "| ID  | Name       | Color   | Row | Col |\n";
	std::cout << "========================================================\n";

	for (const auto& piece : _pieces)
	{
		std::string color = piece.getColor() ? "White" : "Black";
		std::cout << "| " << std::setw(3) << piece.getId() << " | "
			<< std::setw(10) << piece.getName() << " | "
			<< std::setw(7) << color << " | "
			<< std::setw(3) << piece.getRow() << " | "
			<< std::setw(3) << piece.getCol() << " |\n";
	}

	std::cout << "========================================================\n";
}

/**
 * @brief Resetta lo stato logico del gioco di scacchi.
 *
 * Questa funzione reimposta la scacchiera, cancella tutti i pezzi attuali
 * e ripopola la scacchiera con i pezzi iniziali.
 */
void ChessLogic::resetLogic()
{
	// Resetta la scacchiera
	_chessBoard = ChessBoard();

	// Cancella i pezzi esistenti
	_pieces.clear();

	// Resetta il pezzo selezionato
	_selectedPiece = Piece();
	_isPieceSelected = false;
	_isMoveInProgress = false;
	_isWhiteTurn = true;
	_winner = "None";

	// Ripopola i pezzi iniziali
	initialPopulate();

	std::cout << "[Info] Chess logic successfully reset." << std::endl;

	// Stampa i pezzi attuali per conferma
	printPieces();
}