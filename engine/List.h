#pragma once

#include "Node.h"
#include "Common.h"

/**
 * @class List
 * @brief Gestisce una lista di nodi e le loro matrici di trasformazione per il rendering.
 *
 * La classe `List` mantiene una lista di nodi e le relative matrici di trasformazione
 * che sono utilizzate per il rendering. La lista viene utilizzata per ordinare e
 * gestire il rendering degli oggetti nella scena.
 */
class LIB_API List : public Object {

public:

	List() = default;

	// Getter
	std::vector<std::pair<std::shared_ptr<Node>, glm::mat4>>& getListRendering();

	// Setter
	void setListRendering(std::vector<std::pair<std::shared_ptr<Node>, glm::mat4>> newListRendering);

	void sortListRendering();

	static std::vector<std::pair<std::shared_ptr<Node>, glm::mat4>> pass(const std::shared_ptr<Node> sceneRoot, const glm::mat4 parentWorldMatrix);

	// Perche ha inversaCamera e non viewMatrix: 
	// Altrimenti non potevo passargli le matrici e rendirizzarre tutta la lista
	void render(const glm::mat4 inversaCamera) const override;

private:

	///< Lista del nodo e matrice per il rendering.
	std::vector<std::pair<std::shared_ptr<Node>, glm::mat4>> _listRendering;
};