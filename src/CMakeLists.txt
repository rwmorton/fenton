add_subdirectory(core)
add_subdirectory(graphics)
add_subdirectory(extern)
add_subdirectory(tests)

add_executable(main main.cpp)

# target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# core
target_link_libraries(main App_obj)
target_link_libraries(main InputRegistry_obj)
target_link_libraries(main EventRegistry_obj)
target_link_libraries(main CallbackMap_obj)
target_link_libraries(main Clock_obj)

# graphics
target_link_libraries(main VertexBuffer_obj)
target_link_libraries(main Renderer_obj)

# extern
target_link_libraries(main glad_obj)
target_link_libraries(main glfw)
target_link_libraries(main GL)
