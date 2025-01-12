/**
 * @file Piece.h
 * @brief Definizione della classe Piece che rappresenta un pezzo in una scacchiera.
 */

#pragma once
#include <string>

 /**
  * @class Piece
  * @brief Rappresenta un pezzo su una scacchiera.
  *
  * La classe `Piece` gestisce le informazioni relative a un pezzo su una scacchiera,
  * inclusi ID, posizione (riga e colonna), nome e colore.
  */
class Piece
{
public:

    /**
     * @brief Costruttore di default.
     *
     * Inizializza un oggetto `Piece` senza alcun dato.
     */
    Piece();

    /**
     * @brief Costruttore parametrizzato.
     *
     * Inizializza un pezzo con ID, posizione, nome e colore specificati.
     *
     * @param id ID del pezzo.
     * @param row Riga in cui si trova il pezzo.
     * @param col Colonna in cui si trova il pezzo.
     * @param name Nome del pezzo.
     * @param color Colore del pezzo (0 = nero, 1 = bianco).
     */
    Piece(const int id, const int row, const int col, const std::string name, const bool color);

    // Getter

    /**
     * @brief Restituisce l'ID del pezzo.
     * @return L'ID del pezzo.
     */
    int getId() const;

    /**
     * @brief Restituisce la colonna in cui si trova il pezzo.
     * @return La colonna del pezzo.
     */
    int getCol() const;

    /**
     * @brief Restituisce la riga in cui si trova il pezzo.
     * @return La riga del pezzo.
     */
    int getRow() const;

    /**
     * @brief Restituisce il nome del pezzo.
     * @return Il nome del pezzo come stringa.
     */
    std::string getName() const;

    /**
     * @brief Restituisce il colore del pezzo.
     * @return `true` se il pezzo è bianco, `false` se è nero.
     */
    bool getColor() const;

    /**
     * @brief Controlla se il pezzo è nullo.
     * @return `true` se il pezzo non è valido, `false` altrimenti.
     */
    bool isNull() const;

    // Setter

    /**
     * @brief Imposta una nuova colonna per il pezzo.
     * @param newCol La nuova colonna in cui posizionare il pezzo.
     */
    void setCol(const int newCol);

    /**
     * @brief Imposta una nuova riga per il pezzo.
     * @param newRow La nuova riga in cui posizionare il pezzo.
     */
    void setRow(const int newRow);

    /**
     * @brief Imposta un nuovo nome per il pezzo.
     * @param newName Il nuovo nome da assegnare al pezzo.
     */
    void setName(const std::string newName);

private:

    int _id; ///< ID univoco del pezzo.
    int _col; ///< Colonna in cui si trova il pezzo.
    int _row; ///< Riga in cui si trova il pezzo.
    std::string _name; ///< Nome del pezzo.
    bool _color; ///< Colore del pezzo: `0` per nero, `1` per bianco.
};
