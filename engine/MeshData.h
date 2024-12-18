#pragma once

#include "Common.h"

#include <tuple>
#include <vector>
#include <glm/glm.hpp>

/**
 * @class MeshData
 * @brief Rappresenta i dati di una mesh: vertici, facce, normali, coordiante UV.
 *
 * Questa classe gestisce i dati geometrici necessari per renderizzare una mesh nella scena.
 */
class LIB_API MeshData
{
public:

	// Getter
	const std::vector<glm::vec3>& getVertices() const;
	const std::vector<std::tuple<uint32_t, uint32_t, uint32_t>>& getFaces() const;
	const std::vector<glm::vec3>& getNormals() const;
	const std::vector<glm::vec2>& getUVs() const;

	// Setter
	void set_mesh_data(
		const std::vector<glm::vec3> new_vertices,
		const std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> new_faces,
		const std::vector<glm::vec3> new_normals,
		const std::vector<glm::vec2> new_uvs);

private:

	std::vector<glm::vec3> _vertices; ///< Lista dei vertici della mesh.
	std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> _faces; ///< Lista delle facce della mesh.
	std::vector<glm::vec3> _normals;  ///< Lista delle normali della mesh.
	std::vector<glm::vec2> _uvs; ///< Lista delle coordinate UV della mesh.
};
