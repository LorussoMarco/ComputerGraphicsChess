#include <iostream>
#include "Object.h"

class TestObject : public Object {
public:
    TestObject(const std::string& type) : Object(type) {}

    // Implementazione obbligatoria del metodo virtuale puro
    void render(const glm::mat4 viewMatrix) const override {
        // Metodo vuoto per il test
    }
};

void testObjectConstructor() {
    std::cout << "=== Test Costruttore Object ===" << std::endl;
    Object::resetIdGenerator(); // Resetta il contatore ID a 0

    TestObject obj1("TypeA");
    TestObject obj2("TypeB");

    std::cout << "Oggetto 1 ID: " << obj1.getId() << " (Expected: 0)" << std::endl;
    std::cout << "Oggetto 1 Nome: " << obj1.getName() << " (Expected: [0])" << std::endl;
    std::cout << "Oggetto 1 Tipo: " << obj1.getType() << " (Expected: TypeA)" << std::endl;

    std::cout << "Oggetto 2 ID: " << obj2.getId() << " (Expected: 1)" << std::endl;
    std::cout << "Oggetto 2 Nome: " << obj2.getName() << " (Expected: [1])" << std::endl;
    std::cout << "Oggetto 2 Tipo: " << obj2.getType() << " (Expected: TypeB)" << std::endl;
}

void testObjectSetters() {
    std::cout << "\n=== Test Setter Object ===" << std::endl;
    TestObject obj("InitialType");

    obj.setName("NewName");
    obj.setType("NewType");

    std::cout << "Nome modificato: " << obj.getName() << " (Expected: NewName)" << std::endl;
    std::cout << "Tipo modificato: " << obj.getType() << " (Expected: NewType)" << std::endl;
}

void testResetIdGenerator() {
    std::cout << "\n=== Test Reset ID Generator ===" << std::endl;
    Object::resetIdGenerator();

    TestObject obj1("TypeX");
    TestObject obj2("TypeY");

    std::cout << "Oggetto 1 ID dopo reset: " << obj1.getId() << " (Expected: 0)" << std::endl;
    std::cout << "Oggetto 2 ID dopo reset: " << obj2.getId() << " (Expected: 1)" << std::endl;
}

void testObject() {
    testObjectConstructor();
    testObjectSetters();
    testResetIdGenerator();

}
