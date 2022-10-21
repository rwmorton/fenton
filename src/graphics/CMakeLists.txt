add_library(VertexBuffer_obj STATIC VertexBuffer.cpp)
add_library(Renderer_obj STATIC Renderer.cpp)
add_library(Shader_obj STATIC Shader.cpp)

target_include_directories(VertexBuffer_obj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(Renderer_obj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(
    Shader_obj
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../core/include
)
