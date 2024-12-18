#include "Mesh.h"

#include <GL/freeglut.h>

bool Mesh::isColorPickingMode = false;

/**
 * Costruttore della classe Mesh.
 *
 * Crea una nuova istanza di Mesh con i seguenti parametri di default:
 * - Materiale di default: viene assegnato un nuovo oggetto `Material` alla mesh.
 * - ombre: abilitate per la mesh.
 *
 * @brief Inizializza una mesh vuota con un materiale di default e l'attivazione delle ombre.
 */
Mesh::Mesh()
    : Node{ "Mesh" }
{
    // La mesh ha un materiale di default
    this->setMaterial(std::make_shared<Material>());
    this->setShadows(true);
}

///// Getter

/**
 * Restituisce se questa mesh proietta ombre o meno.
 *
 * @return `true` se la mesh proietta ombre; `false` altrimenti.
 */
bool LIB_API Mesh::getShadows() const
{
    return this->_castShadows;
}

/**
 * Restituisce il materiale utilizzato da questa mesh.
 *
 * @return Un puntatore condiviso al materiale utilizzato da questa mesh.
 */
std::shared_ptr<Material> LIB_API Mesh::getMaterial() const
{
    return this->_material;
}

///// Setter

/**
 * Cambia il materiale applicato a questa mesh.
 *
 * @param newMaterial Il nuovo materiale da applicare alla mesh.
 */
void LIB_API Mesh::setMaterial(const std::shared_ptr<Material> newMaterial)
{
    this->_material = newMaterial;
}

/**
 * Imposta se questa mesh deve proiettare ombre o meno.
 *
 * @param newShadows Se true, la mesh proietta ombre; se false, non proietta ombre.
 */
void LIB_API Mesh::setShadows(const bool newShadows)
{
    this->_castShadows = newShadows;
}

/**
 * Imposta i dati della mesh.
 *
 * @param data I nuovi dati della mesh da applicare.
 */
void LIB_API Mesh::setMeshData(const MeshData& data)
{
    _meshData = data;
}

///// Render Mesh

/**
 * Renderizza la mesh nella scena.
 *
 * Questa funzione viene chiamata automaticamente da MyEngine e non bisogna chiamarla manualmente.
 *
 * @param viewMatrix La matrice di vista da utilizzare per renderizzare questo oggetto.
 */
void LIB_API Mesh::render(const glm::mat4 viewMatrix) const
{
    Node::render(viewMatrix);

    // Se si ha cliccato bisogna renderizzare la scena in questo modo:
    if (Mesh::isColorPickingMode)
    {
        // Usa il colore basato sull'ID dell'oggetto.
        int id = this->getId();

        // glColor4f accetta parametri da 0 a 1 percio dividiamo l'id.
        float idRange;
        idRange = id / 255.0f;

        // Disabilita l'illuminazione e il texture mapping.
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);

        // Imposta il colore per la mesh che sto renderizzando.
        glColor4f(idRange, idRange, idRange, 1.0f);

        // Itera su ciascuna faccia (triangolo) della mesh.
        for (const auto& face : _meshData.getFaces())
        {
            glBegin(GL_TRIANGLES);

            // std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> _faces;
            // -> prende il primo vertice della face
            const glm::vec3 vertex_0 = _meshData.getVertices()[std::get<0>(face)];
            const glm::vec3 vertex_1 = _meshData.getVertices()[std::get<1>(face)];
            const glm::vec3 vertex_2 = _meshData.getVertices()[std::get<2>(face)];

            glVertex3f(vertex_0.x, vertex_0.y, vertex_0.z);
            glVertex3f(vertex_1.x, vertex_1.y, vertex_1.z);
            glVertex3f(vertex_2.x, vertex_2.y, vertex_2.z);

            glEnd();
        }

        // Riabilita l'illuminazione e il texture mapping.
        glEnable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
    }
    // Renderizza la scena normalmente con l'illuminazione.
    else
    {
        // Render del materiale
        this->_material->render(viewMatrix);

        // Itera su ciascuna faccia (triangolo) della mesh.
        for (const auto& face : _meshData.getFaces())
        {
            glBegin(GL_TRIANGLES);

            const glm::vec3 vertex_0 = _meshData.getVertices()[std::get<0>(face)];
            const glm::vec3 vertex_1 = _meshData.getVertices()[std::get<1>(face)];
            const glm::vec3 vertex_2 = _meshData.getVertices()[std::get<2>(face)];

            const glm::vec3 normal_0 = _meshData.getNormals()[std::get<0>(face)];
            const glm::vec3 normal_1 = _meshData.getNormals()[std::get<1>(face)];
            const glm::vec3 normal_2 = _meshData.getNormals()[std::get<2>(face)];

            const glm::vec2 uv_0 = _meshData.getUVs()[std::get<0>(face)];
            const glm::vec2 uv_1 = _meshData.getUVs()[std::get<1>(face)];
            const glm::vec2 uv_2 = _meshData.getUVs()[std::get<2>(face)];

            // Imposta le coordinate UV e le normali
            glTexCoord2f(uv_0.x, uv_0.y);
            glNormal3f(normal_0.x, normal_0.y, normal_0.z);
            glVertex3f(vertex_0.x, vertex_0.y, vertex_0.z);

            glTexCoord2f(uv_1.x, uv_1.y);
            glNormal3f(normal_1.x, normal_1.y, normal_1.z);
            glVertex3f(vertex_1.x, vertex_1.y, vertex_1.z);

            glTexCoord2f(uv_2.x, uv_2.y);
            glNormal3f(normal_2.x, normal_2.y, normal_2.z);
            glVertex3f(vertex_2.x, vertex_2.y, vertex_2.z);

            glEnd();
        }
    }
}
