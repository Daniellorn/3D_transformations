cmake_minimum_required(VERSION 3.20)
project(Grafikav2)

if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


add_executable(projekt src/main.cpp src/glad.c "src/Shader.h" "src/Shader.cpp" "src/ErrorHandling.h" "src/ErrorHandling.cpp" )
target_include_directories(projekt PUBLIC dependencies/GLFW/include)
target_link_libraries(projekt PUBLIC ${CMAKE_SOURCE_DIR}/dependencies/GLFW/lib/glfw3.lib )


set_property(TARGET projekt PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:projekt>")


if (CMAKE_VERSION VERSION_GREATER 3.15)
  set_property(TARGET projekt PROPERTY CXX_STANDARD 20)
endif()
