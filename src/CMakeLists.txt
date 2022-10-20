add_subdirectory(core)

add_executable(main main.cpp)

target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(main App_obj)
target_link_libraries(main InputRegistry_obj)
target_link_libraries(main EventRegistry_obj)
target_link_libraries(main CallbackMap_obj)
target_link_libraries(main Clock_obj)

target_link_libraries(main GLEW)
target_link_libraries(main glfw)
target_link_libraries(main GL)
