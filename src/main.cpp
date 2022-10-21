#include "tests/testApp.hpp"
#include "tests/testVertexBuffer.hpp"
#include "tests/testShader.hpp"

int main() {
    // TestApp app(800,600,"test app",true,false);
    // TestVBO app(800,600,"test vertex buffer",true,false);
    TestShader app(800,600,"test shader",true,false);

    app.run();

    return 0;
}
