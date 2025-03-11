cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

ADD_CUSTOM_TARGET( copy_shader_files ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        ${CMAKE_BINARY_DIR}/shaders
        COMMENT "Copying Shaders for target" VERBATIM 
        )

project ("glb-viewer")


add_executable ("${CMAKE_PROJECT_NAME}" "src/main.cpp" "src/glad.c" "src/engine.cpp" "src/shaders.cpp" "src/stb_image.cpp"  "src/mesh.cpp" "src/model.cpp")

add_dependencies("${CMAKE_PROJECT_NAME}" copy_shader_files)

add_subdirectory(thirdparty/glfw-3.4)
add_subdirectory(thirdparty/assimp)



target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE "include")
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glfw assimp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET glb-viewer PROPERTY CXX_STANDARD 20)
endif()
