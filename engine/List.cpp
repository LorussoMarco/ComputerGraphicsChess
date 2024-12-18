#include "List.h"
#include "Node.h"
#include <algorithm>

// Getter

/**
 * @brief Restituisce una referenza alla lista degli oggetti da renderizzare.
 *
 * @return Una referenza a `std::vector<std::pair<std::shared_ptr<Node>, glm::mat4>>` che contiene
 *         tutti i nodi e le loro matrici di trasformazione globale da renderizzare.
 */
LIB_API std::vector<std::pair<std::shared_ptr<Node>, glm::mat4>>& List::getListRendering() {
    return _listRendering;
}

// Setter

/**
 * @brief Imposta la lista degli oggetti da renderizzare.
 *
 * @param newListRendering Il nuovo vettore di coppie di nodi e matrici di trasformazione
 *                         da impostare come lista di rendering.
 */
void LIB_API List::setListRendering(std::vector<std::pair<std::shared_ptr<Node>, glm::mat4>> newListRendering) {
    _listRendering = newListRendering;
}

/**
 * @brief Restituisce una lista di oggetti da renderizzare all'interno della scena.
 *
 * Questa funzione crea una lista di nodi e le loro matrici di trasformazione globale
 * a partire da un nodo radice della scena e una matrice di trasformazione globale del nodo padre.
 * La funzione e' ricorsiva e itera attraverso tutti i nodi figli del nodo radice per costruire
 * la lista completa di nodi da renderizzare.
 *
 * @param scene_root Il nodo radice della scena. Questo nodo e i suoi figli verranno aggiunti alla lista di rendering.
 * @param parentWorldMatrix La matrice di trasformazione globale del nodo padre, utilizzata per calcolare
 *        la matrice di trasformazione globale di ogni nodo nella scena.
 *
 * @return Un vettore di coppie `std::pair<std::shared_ptr<Node>, glm::mat4>`, dove ogni coppia contiene
 *         un puntatore condiviso a un nodo (`std::shared_ptr<Node>`) e la sua matrice di trasformazione globale (`glm::mat4`).
 *         Questo vettore rappresenta la lista degli oggetti da renderizzare nella scena.
 */
std::vector<std::pair<std::shared_ptr<Node>, glm::mat4>> LIB_API List::pass(const std::shared_ptr<Node> sceneRoot, const glm::mat4 parentWorldMatrix)
{
    std::vector<std::pair<std::shared_ptr<Node>, glm::mat4>> renderListPass;

    // World matrix = world matrix del nodo padre (parentWorldMatrix) * local matrix del nodo
    renderListPass.push_back(std::make_pair(sceneRoot, parentWorldMatrix * sceneRoot->getLocalMatrix()));

    // Itera su tutti i nodi figli del nodo radice. 
    for (const auto& child : sceneRoot->getChildren())
    {
        // Chiama ricorsivamente la funzione pass per ottenere la lista di rendering dei nodi figli.
        std::vector<std::pair<std::shared_ptr<Node>, glm::mat4>> childRenderList = List::pass(child, parentWorldMatrix * sceneRoot->getLocalMatrix());

        // Aggiunge tutti gli elementi (da childRenderList.begin() a childRenderList.end()) nel vettore renderListPass. 
        renderListPass.insert(renderListPass.end(), childRenderList.begin(), childRenderList.end());
    }
    return renderListPass;
}

/**
 * @brief Riordina la lista degli oggetti da renderizzare in base alla priorita.
 *
 * L'ordine di importanza:
 * - Camera
 * - Light
 * - Resto (Mesh)
 *
 * L'oggetto con la priorita maggiore viene renderizzato per primo. (primi nella lista)
 */
void List::sortListRendering()
{
    std::sort(_listRendering.begin(), _listRendering.end(), [](const std::pair<std::shared_ptr<Node>, glm::mat4> a, const std::pair<std::shared_ptr<Node>, glm::mat4> b) {
        return a.first->getPriority() > b.first->getPriority();
        });
}

///// Render List

/**
 * @brief Renderizza tutti gli oggetti nella lista di rendering.
 *
 * Questo metodo itera su ciascun nodo nella lista di rendering e lo renderizza.
 *
 * @param inversaCamera La matrice inversa della camera.
 *
 * La funzione calcola la viewMatrix per ogni nodo come:
 * - viewMatrix = inversaCamera * node.second (world matrix del nodo)
 */
void LIB_API List::render(const glm::mat4 inversaCamera) const
{
    glm::mat4 viewMatrix(1.0f);

    // Per ogni elemento della lista
    for (const auto& node : _listRendering)
    {
        // calcola la viewMatrix per il nodo
        viewMatrix = inversaCamera * node.second;
        node.first->render(viewMatrix);
    }
}
