#pragma once


#include "Material.h"
#include "Node.h"
#include "MeshData.h"
#include "Common.h"
#include "Shadow.h"

/**
 * @class Mesh
 * @brief Rappresenta una mesh che viene renderizzata all'interno di una scena.
 *
 * Una mesh e una rappresentazione tridimensionale di una forma. Essa include dati di geometria,
 * come vertici e facce, e viene associata a un materiale per definire l'aspetto visivo
 * della superficie. Le mesh possono anche proiettare ombre.
 *
 */
class LIB_API Mesh : public Node
{
public:

    Mesh();

    // Getter
    bool getShadows() const;
    std::shared_ptr<Material> getMaterial() const;
    const MeshData& getMeshData() const;

    // Setter
    void setMaterial(const std::shared_ptr<Material> newMaterial);
    void setShadows(const bool newCastShadows);
    void setMeshData(const MeshData& data);
    void initializeShadow();

    void render(const glm::mat4 viewMatrix) const override;

    // Indica se renderizzare una Mesh solo con i colori e niente illuminazione
    static bool isColorPickingMode;

private:

    MeshData _meshData; ///< Dati della mesh, inclusi vertici e facce.
    std::shared_ptr<Material> _material; ///< Materiale associato alla mesh.
    bool _castShadows; ///< Indica se la mesh deve proiettare ombre.
    std::shared_ptr<Shadow> _shadow;

};

