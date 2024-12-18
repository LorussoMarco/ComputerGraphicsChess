#pragma once

// Migliora la qualita delle texture quando sono viste da angoli inclinati.
// Piu alto e il valore, piu dettagliata sara la texture.
#define GL_TEXTURE_MAX_ANISOTROPY_EXT        0x84FE

// Quanto puoi aumentare la qualita delle texture sulla tua scheda grafica.
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT    0x84FF

#include "Common.h"
#include "Object.h"

/**
 * @brief Rappresenta una texture, che consente di applicare immagini su un modello 3D.
 *
 * La classe `Texture` rappresenta una texture che viene applicata sui modelli 3D,
 * permettendo di visualizzare immagini sulle superfici delle mesh. Gestisce il caricamento
 * di un'immagine da un percorso specificato e la renderizzazione della texture sugli oggetti 3D.
 */
class LIB_API Texture : public Object
{
public:

    // Carica un'immagine da un percorso specificato.
    Texture(const std::string path);
    ~Texture();

    void render(const glm::mat4 viewMatrix) const override;

private:

    void* _bitmap; ///< Puntatore ai dati dell'immagine in memoria.
    unsigned int _textureId; ///< Identificatore della texture OpenGL.
};
