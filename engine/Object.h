#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Common.h"


/**
 * @class Object
 * @brief Rappresenta un oggetto di base all'interno del sistema.
 *
 * La classe Object fornisce una base comune a tutti gli oggetti nel sistema.
 * Ogni oggetto ha un identificatore univoco, un tipo e un nome associato.
 * La classe serve per essere di base per altre classi.
 */
class LIB_API Object
{
public:

    Object() = default;
    Object(const std::string type);

    // getter
    int getId() const;
    std::string getName() const;
    const std::string getType() const;

    // setter
    void setName(const std::string newName);
    void setType(const std::string& type);

    // viewMatrix = matriceCameraInversa * world matrix --> (eye coords)
    virtual void render(const glm::mat4 viewMatrix) const = 0;

    static void resetIdGenerator();

private:

    int _id;  ///< Identificatore univoco dell'oggetto.
    std::string _name; ///< Nome dell'oggetto
    std::string _type; ///< Tipo dell'oggetto.

    static int nextId; ///< Prossimo id da usare.
};