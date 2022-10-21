#include "tests/testApp.hpp"
#include "tests/testVertexBuffer.hpp"

int main() {
    // TestApp app(800,600,"app",true,false);
    TestVBO app(800,600,"test vertex buffer",true,false);

    app.run();

    return 0;
}
