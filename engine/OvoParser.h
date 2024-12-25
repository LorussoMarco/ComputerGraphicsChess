#pragma once

#include <unordered_map>

#include "Common.h"
#include "Mesh.h"
#include "Node.h"
#include "Light.h"
#include "Material.h"
#include "MeshData.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include <filesystem>

/**
 * @brief Un parser per il caricamento di grafi di scena da file ovo.
 *
 * La classe OVOParser fornisce funzionalit    per caricare e analizzare i dati delle scene dal formato di file OVO.
 * Converte i dati di questi file in una struttura di grafo di scena composta da nodi, mesh, materiali e luci.
 * Il parser supporta le seguenti funzionalit   :
 *
 * - Caricamento di un grafo di scena completo da un file OVO.
 * - Analisi dei chunk di dati corrispondenti a diversi elementi della scena come nodi, mesh, materiali e luci.
 *
 * La classe dispone di metodi statici per analizzare i diversi tipi di chunk e un metodo per estrarre stringhe dai dati grezzi.
 * Mantiene inoltre una mappa di materiali per evitare definizioni ridondanti di materiali all'interno della scena.
 */
class LIB_API OVOParser
{
public:

    static std::shared_ptr<Node> fromFile(const std::string filePath);

private:

    static std::pair<std::shared_ptr<Node>, uint32_t>        parseNodeChunk(const uint8_t* chunkData, const uint32_t chunkSize);
    static std::pair<std::shared_ptr<Mesh>, uint32_t>        parseMeshChunk(const uint8_t* chunkData, const uint32_t chunkSize);
    static std::pair<std::shared_ptr<Material>, std::string> parseMaterialChunk(const uint8_t* chunkData, const uint32_t chunkSize);
    static std::pair<std::shared_ptr<Light>, uint32_t>       parseLightChunk(const uint8_t* chunkData, const uint32_t chunkSize);

    static std::string parseString(const uint8_t* data);

    static std::unordered_map<std::string, std::shared_ptr<Material>> materials; ///> Mappa dei materiali
};
