
# cmake version
cmake_minimum_required(VERSION 4.0)

# project
project (ouros)

# sources
file(GLOB SOURCES
    "src/*.cpp"
    "Libraries/glad.h"
)
set(EXTRA_SRC 
    "Libraries/glad.c"
)
set(ALL_SOURCES ${SOURCES} ${EXTRA_SRC})

# executable
add_executable(${PROJECT_NAME} ${ALL_SOURCES})

# include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/Libraries/include
)

target_link_libraries(${PROJECT_NAME} 
    ${PROJECT_SOURCE_DIR}/Libraries/lib/glfw3.lib
)
