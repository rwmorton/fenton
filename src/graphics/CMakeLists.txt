add_library(VertexBuffer_obj STATIC VertexBuffer.cpp)
add_library(Renderer_obj STATIC Renderer.cpp)

target_include_directories(VertexBuffer_obj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(Renderer_obj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
