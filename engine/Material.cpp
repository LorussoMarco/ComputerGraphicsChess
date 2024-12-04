#include "Material.h"

#include <GL/freeglut.h>
#include <glm/gtc/type_ptr.hpp>


/**
 * @brief Costruttore di default per la classe Material.
 *
 * Questo costruttore crea una nuova istanza di `Material` con i seguenti parametri di default:
 *
 * - Colore di emissione: (0.0f, 0.0f, 0.0f) (Nero / Nessuna emissione)
 * - Colore ambientale: (0.75f, 0.75f, 0.75f) (Grigio chiaro)
 * - Colore diffuso: (0.75f, 0.75f, 0.75f) (Grigio chiaro)
 * - Colore speculare: (0.75f, 0.75f, 0.75f) (Grigio chiaro)
 * - Lucentezza: 64.0f (Influisce su quanto il materiale riflette la luce speculare)
 * - Valore alpha: 1.0f (Opaco, nessuna trasparenza)
 * - Texture: Nessuna texture applicata (nullptr)
 *
 * Il materiale inizializzato con questi valori predefiniti e visivamente neutro e non ha alcuna texture applicata,
 * rendendolo un punto di partenza per ulteriori modifiche e personalizzazioni.
 */
Material::Material()
    : Object("Material")
{
    this->setEmissionColor(glm::vec3(0.0f, 0.0f, 0.0f));
    this->setAmbientColor(glm::vec3(0.75f, 0.75f, 0.75f));
    this->setDiffuseColor(glm::vec3(0.75f, 0.75f, 0.75f));
    this->setSpecularColor(glm::vec3(0.75f, 0.75f, 0.75f));
    this->setShininess(64.0f);
    this->setAlpha(1.0f);
    this->setTexture(nullptr);
}

///// Getter

/**
 * @brief Restituisce il colore di emissione del materiale.
 *
  Il colore di emissione determina la quantita di luce che il materiale emette autonomamente.
 *
 * @return Il colore di emissione del materiale.
 */
glm::vec3 LIB_API Material::getEmissionColor() const {
    return _emissionColor;
}

///// Setter

/**
 * @brief Cambia il colore di emissione di questo materiale.
 *
 * Imposta il colore di emissione, che rappresenta la luce che il materiale emette come se fosse una fonte luminosa.
 *
 * @param newColor Il nuovo colore di emissione del materiale.
 */
void LIB_API Material::setEmissionColor(const glm::vec3 newColor)
{
    this->_emissionColor = newColor;
}

/**
 * @brief Cambia il colore ambientale di questo materiale.
 *
 * Imposta il colore ambientale, che e il colore riflesso dal materiale quando colpito dalla luce ambientale.
 *
 * @param newColor Il nuovo colore ambientale del materiale.
 */
void LIB_API Material::setAmbientColor(const glm::vec3 newColor)
{
    this->_ambientColor = newColor;
}

/**
 * @brief Cambia il colore diffuso di questo materiale.
 *
 * Imposta il colore diffuso, che e il colore visibile del materiale quando colpito dalla luce diretta.
 *
 * @param newColor Il nuovo colore diffuso del materiale.
 */
void LIB_API Material::setDiffuseColor(const glm::vec3 newColor)
{
    this->_diffuseColor = newColor;
}

/**
 * @brief Cambia il colore speculare di questo materiale.
 *
 * Imposta il colore speculare, che determina il colore dei riflessi lucidi e brillanti sulla superficie del materiale.
 *
 * @param newColor Il nuovo colore speculare del materiale.
 */
void LIB_API Material::setSpecularColor(const glm::vec3 newColor)
{
    this->_specularColor = newColor;
}

/**
 * @brief Cambia il valore di lucentezza di questo materiale.
 *
 * Imposta il valore di lucentezza, che influisce su quanto il materiale riflette la luce speculare e quanto e concentrato il riflesso.
 *
 * @param newShininess Il nuovo valore di lucentezza del materiale.
 */
void LIB_API Material::setShininess(const float newShininess)
{
    this->_shininess = newShininess;
}

/**
 * @brief Cambia il valore alpha di questo materiale.
 *
 * Imposta il valore alpha, che determina l'opacita del materiale. Valori bassi indicano maggiore trasparenza.
 *
 * @param newAlpha Il nuovo valore alpha del materiale.
 */
void LIB_API Material::setAlpha(const float newAlpha)
{
    this->_alpha = newAlpha;
}

/**
 * @brief Imposta la texture di questo materiale.
 *
 * Se `new_texture` e nullptr, non viene applicata alcuna texture al materiale.
 *
 * @param newTexture La nuova texture da applicare al materiale.
 */
void LIB_API Material::setTexture(const std::shared_ptr<Texture> newTexture)
{
    this->_texture = newTexture;
}

///// Render material

/**
 * @brief Renderizza il materiale utilizzando le impostazioni correnti.
 *
 * Questa funzione viene chiamata automaticamente da MyEngine.
 * Non bisogna chiamare manualmente questa funzione.
 *
 * La funzione applica gli attributi del materiale come il colore di emissione, ambientale, diffuso
 * e speculare, oltre al valore di lucentezza. Se e presente una texture, viene renderizzata anch'essa.
 *
 * @param viewMatrix La matrice da utilizzare per il rendering dell'oggetto.
 */
void LIB_API Material::render(const glm::mat4 viewMatrix) const
{
    // Disabilita la texture. 
    glDisable(GL_TEXTURE_2D);

    // Il colore del materiale deve essere applicato sia alle front che back face.
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(this->_emissionColor));
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(this->_ambientColor));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(this->_diffuseColor));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(this->_specularColor));
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->_shininess);

    // Verifica se il materiale ha una texture.
    if (this->_texture != nullptr)
    {
        // Chiama il metodo render della texture. 
        this->_texture->render(viewMatrix);
    }
}
