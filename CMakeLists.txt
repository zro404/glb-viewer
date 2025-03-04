cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("glb-viewer")

add_executable ("${CMAKE_PROJECT_NAME}" "src/main.cpp" "src/glad.c" "src/engine.cpp" "src/shaders.cpp")

add_subdirectory(thirdparty/glfw-3.4)

target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE "include")
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glfw)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET glb-viewer PROPERTY CXX_STANDARD 20)
endif()
