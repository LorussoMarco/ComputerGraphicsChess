#include "Piece.h"

/**
 * @brief Costruttore di default della classe Piece.
 *
 * Inizializza un oggetto Piece con valori predefiniti:
 * - ID: -1 (indicando un pezzo nullo)
 * - Riga: -1
 * - Colonna: -1
 * - Colore: false (nero)
 */
Piece::Piece()
{
	this->_id = -1;
	this->_row = -1;
	this->_col = -1;
	this->_color = false;
}

/**
 * @brief Costruttore parametrico della classe Piece.
 *
 * Inizializza un oggetto Piece con i valori forniti.
 *
 * @param id L'identificativo univoco del pezzo.
 * @param row La riga in cui si trova il pezzo.
 * @param col La colonna in cui si trova il pezzo.
 * @param name Il nome del pezzo.
 * @param color Il colore del pezzo (`false` per nero, `true` per bianco).
 */
Piece::Piece(const int id, const int row, const int col, const std::string name, const bool color)
{
	this->_id = id;
	this->setCol(col);
	this->setRow(row);
	this->_name = name;
	this->_color = color;
}

/**
 * @brief Determina se il pezzo è nullo.
 *
 * Un pezzo è considerato nullo se il suo ID è -1.
 *
 * @return `true` se il pezzo è nullo, `false` altrimenti.
 */
bool Piece::isNull() const {
	return _id == -1;
}

// Getter 

/**
 * @brief Restituisce l'identificativo univoco del pezzo.
 *
 * @return L'ID del pezzo.
 */
int Piece::getId() const
{
	return this->_id;
}

/**
 * @brief Restituisce la colonna in cui si trova il pezzo.
 *
 * @return La colonna del pezzo.
 */
int Piece::getCol() const
{
	return this->_col;
}

/**
 * @brief Restituisce la riga in cui si trova il pezzo.
 *
 * @return La riga del pezzo.
 */
int Piece::getRow() const
{
	return this->_row;
}

/**
 * @brief Restituisce il nome del pezzo.
 *
 * @return Il nome del pezzo come stringa.
 */
std::string Piece::getName() const
{
	return this->_name;
}

/**
 * @brief Restituisce il colore del pezzo.
 *
 * @return `true` se il pezzo è bianco, `false` se è nero.
 */
bool Piece::getColor() const
{
	return this->_color;
}


// Setter

/**
 * @brief Imposta la colonna del pezzo.
 *
 * @param newCol La nuova colonna da assegnare al pezzo.
 */
void Piece::setCol(int newCol)
{
	this->_col = newCol;
}

/**
 * @brief Imposta la riga del pezzo.
 *
 * @param newRow La nuova riga da assegnare al pezzo.
 */
void Piece::setRow(int newRow)
{
	this->_row = newRow;
}

/**
 * @brief Imposta il nome del pezzo.
 *
 * @param newName Il nuovo nome da assegnare al pezzo.
 */
void Piece::setName(std::string newName)
{
	this->_name = newName;
}
