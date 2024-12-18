#include <iostream>
void testCamera();
void testLight();
void testList();
void testMaterial();
void testMeshData();
void testMesh();
void testNode();
void testObject();
void testTexture();
void testEngine();

int main() {
    std::cout << "=== Running All Tests ===" << std::endl;

    testCamera();
    testLight();
    testList();
    testMaterial();
    testMeshData();
    testMesh();
    testNode();
    testObject();
    testTexture();
    testEngine();

    std::cout << "\n=== All Tests Completed ===" << std::endl;
    return 0;
}
