#include <assert.h>
#include <cmath>
#include <iostream>

#include <glm/glm.hpp>

#include "Camera.h"
#include "Light.h"
#include "Engine.h"
#include "Node.h"
#include "Object.h"
#include "OvoParser.h"
#include "PerspectiveCamera.h"

int main()
{
	///// Object
	std::cout << "Testing Object " << std::endl;
	std::shared_ptr<Object> object = std::make_shared<Node>("NodeType");

	// Test per il nome dell'oggetto
	object->setName("camera001");
	assert(object->getName() == "camera001");

	// Test per l'id dell'oggetto
	assert(object->getId() == 1);

	// Creiamo un altro oggetto per verificare che l'ID venga incrementato
	std::shared_ptr<Object> anotherObject = std::make_shared<Node>("AnotherNodeType");
	assert(anotherObject->getId() == 2);

	// Test per il tipo dell'oggetto
	assert(object->getType() == "NodeType");

	// Modifica il tipo
	object->setType("NewNodeType");
	assert(object->getType() == "NewNodeType");

	// Test del reset del generatore di ID
	Object::resetIdGenerator();
	std::shared_ptr<Object> resetObject = std::make_shared<Node>("ResetNodeType");
	assert(resetObject->getId() == 0);

	Object::resetIdGenerator();

	///// Node
	std::cout << "Testing Node " << std::endl;
	std::shared_ptr<Node> node = std::make_shared<Node>();

	// Test delle proprieta iniziali del nodo
	assert(node->getPosition() == glm::vec3(0.0f, 0.0f, 0.0f));
	assert(node->getRotation() == glm::vec3(0.0f, 0.0f, 0.0f));
	assert(node->getScale() == glm::vec3(1.0f, 1.0f, 1.0f));
	assert(node->getPriority() == 0);
	assert(node->getLocalMatrix() == glm::mat4(1.0f));

	// Modifica delle proprieta e verifica
	node->setPosition(glm::vec3(10.0f, 5.0f, 0.0f));
	assert(node->getPosition() == glm::vec3(10.0f, 5.0f, 0.0f));

	node->setRotation(glm::vec3(45.0f, 0.0f, 90.0f));
	assert(node->getRotation() == glm::vec3(45.0f, 0.0f, 90.0f));

	node->setScale(glm::vec3(2.0f, 2.0f, 2.0f));
	assert(node->getScale() == glm::vec3(2.0f, 2.0f, 2.0f));

	node->setPriority(5);
	assert(node->getPriority() == 5);

	// Verifica della matrice locale dopo aver impostato posizione, rotazione e scala
	glm::mat4 localMatrix = node->getLocalMatrix();
	assert(localMatrix != glm::mat4(1.0f));  // Dopo le trasformazioni, non dovrebbe essere la matrice di identita

	// Aggiunta e verifica dei figli
	std::shared_ptr<Node> childNode1 = std::make_shared<Node>();
	std::shared_ptr<Node> childNode2 = std::make_shared<Node>();
	node->addChild(childNode1);
	node->addChild(childNode2);

	auto children = node->getChildren();
	assert(children.size() == 2);
	assert(children[0] == childNode1);
	assert(children[1] == childNode2);

	///// Camera
	std::cout << "Testing Camera " << std::endl;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>("CameraType");

	// Test dei valori di default
	assert(camera->getPosition() == glm::vec3(0.0f, 0.0f, 0.0f));
	assert(camera->getRotation() == glm::vec3(0.0f, 0.0f, 0.0f));
	assert(camera->getScale() == glm::vec3(1.0f, 1.0f, 1.0f));
	assert(camera->getPriority() == 2);  // Priorit di default impostata nel costruttore
	assert(camera->getInverseMatrix() == glm::inverse(camera->getLocalMatrix()));

	///// PerspectiveCamera
	std::cout << "Testing PerspectiveCamera " << std::endl;
	std::shared_ptr<PerspectiveCamera> cameraPersp = std::make_shared<PerspectiveCamera>();

	// Test dei valori di default ereditati da Camera
	assert(cameraPersp->getPosition() == glm::vec3(0.0f, 0.0f, 0.0f));
	assert(cameraPersp->getRotation() == glm::vec3(0.0f, 0.0f, 0.0f));
	assert(cameraPersp->getScale() == glm::vec3(1.0f, 1.0f, 1.0f));
	assert(cameraPersp->getPriority() == 2);

	///// Light
	std::cout << "Testing Light " << std::endl;

	// Resetta l'ID delle luci per assicurarsi che parta da 0
	Light::resetNextLightId();

	std::shared_ptr<Light> light1 = std::make_shared<Light>("PointLight");

	// Test dei valori di default
	assert(light1->getPosition() == glm::vec3(0.0f, 0.0f, 0.0f));
	assert(light1->getRotation() == glm::vec3(0.0f, 0.0f, 0.0f));
	assert(light1->getScale() == glm::vec3(1.0f, 1.0f, 1.0f));
	assert(light1->getPriority() == 1);  // Priorit predefinita impostata nel costruttore

	///// PointLight
	std::cout << "Testing PointLight " << std::endl;

	Light::resetNextLightId();
	std::shared_ptr<PointLight> pointLight = std::make_shared<PointLight>();
	assert(pointLight->getType() == "PointLight");

	///// DirectionalLight
	std::cout << "Testing DirectionalLight " << std::endl;

	Light::resetNextLightId();
	std::shared_ptr<DirectionalLight> directionalLight = std::make_shared<DirectionalLight>();
	assert(directionalLight->getType() == "DirectionalLight");

	///// SpotLight
	std::cout << "Testing SpotLight " << std::endl;

	Light::resetNextLightId();
	std::shared_ptr<SpotLight> spotLight = std::make_shared<SpotLight>();
	assert(spotLight->getType() == "SpotLight");

	Light::resetNextLightId();

	///// Material
	std::cout << "Testing Material " << std::endl;

	// Creazione di un oggetto Material
	std::shared_ptr<Material> material = std::make_shared<Material>();
	assert(material->getEmissionColor() == glm::vec3(0.0f, 0.0f, 0.0f));  // Nero

	///// Mesh
	std::cout << "Testing Mesh " << std::endl;
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();

	// Test del materiale di default
	std::shared_ptr<Material> defaultMaterial = mesh->getMaterial();
	assert(defaultMaterial != nullptr);
	// Verifica che le ombre siano abilitate per default
	assert(mesh->getShadows() == true);

	// Creazione di un nuovo materiale e assegnazione alla mesh
	std::shared_ptr<Material> newMaterial = std::make_shared<Material>();
	newMaterial->setDiffuseColor(glm::vec3(1.0f, 0.0f, 0.0f));  // Imposta il colore diffuso a rosso
	mesh->setMaterial(newMaterial);
	assert(mesh->getMaterial() == newMaterial);

	// Verifica che le ombre siano disabilitate
	mesh->setShadows(false);
	assert(mesh->getShadows() == false);

	///// MeshData
	std::cout << "Testing MeshData " << std::endl;

	MeshData meshData;

	// Dati di esempio
	std::vector<glm::vec3> vertices = {
		{0.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f}
	};

	std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> faces = {
		{0, 1, 2}
	};

	std::vector<glm::vec3> normals = {
		{0.0f, 0.0f, 1.0f}
	};

	std::vector<glm::vec2> uvs = {
		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{0.0f, 1.0f}
	};

	// Impostazione dei dati della mesh
	meshData.set_mesh_data(vertices, faces, normals, uvs);

	// Verifica che i dati siano stati correttamente impostati
	assert(meshData.getVertices().size() == 3);  // Dovrebbe contenere 3 vertici
	assert(meshData.getVertices()[0] == glm::vec3(0.0f, 0.0f, 0.0f));
	assert(meshData.getVertices()[1] == glm::vec3(1.0f, 0.0f, 0.0f));
	assert(meshData.getVertices()[2] == glm::vec3(0.0f, 1.0f, 0.0f));

	assert(meshData.getFaces().size() == 1);  // Dovrebbe contenere 1 faccia
	assert(meshData.getFaces()[0] == std::make_tuple(0, 1, 2));

	assert(meshData.getNormals().size() == 1);  // Dovrebbe contenere 1 normale
	assert(meshData.getNormals()[0] == glm::vec3(0.0f, 0.0f, 1.0f));

	assert(meshData.getUVs().size() == 3);  // Dovrebbe contenere 3 coordinate UV
	assert(meshData.getUVs()[0] == glm::vec2(0.0f, 0.0f));
	assert(meshData.getUVs()[1] == glm::vec2(1.0f, 0.0f));
	assert(meshData.getUVs()[2] == glm::vec2(0.0f, 1.0f));

	///// List
	std::cout << "Testing List " << std::endl;

	// Creazione di un oggetto List
	List list;

	// Creazione di alcuni nodi di test
	std::shared_ptr<Node> node1 = std::make_shared<Node>("Camera");
	std::shared_ptr<Node> node2 = std::make_shared<Node>("Light");
	std::shared_ptr<Node> node3 = std::make_shared<Node>("Mesh");

	// Creazione di una lista di rendering
	std::vector<std::pair<std::shared_ptr<Node>, glm::mat4>> testListRendering = {
		{node1, glm::mat4(1.0f)},
		{node2, glm::mat4(1.0f)},
		{node3, glm::mat4(1.0f)}
	};

	// Impostazione della lista di rendering nella classe List
	list.setListRendering(testListRendering);

	// Verifica che la lista sia stata impostata correttamente
	assert(list.getListRendering().size() == 3);
	assert(list.getListRendering()[0].first->getType() == "Camera");
	assert(list.getListRendering()[1].first->getType() == "Light");
	assert(list.getListRendering()[2].first->getType() == "Mesh");

	std::cout << "All tests passed!" << std::endl;

	return 0;
}
