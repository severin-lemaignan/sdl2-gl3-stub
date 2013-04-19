project(sdl2-gl3-stub)
cmake_minimum_required(VERSION 2.8)

include(FindPkgConfig)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
set(LIBS ${LIBS} ${OPENGL_LIBRARY})
add_definitions(`sdl2-config --cflags`)	# SDL CFLAGS
set(LIBS ${LIBS} 'SDL2')

find_package(Assimp REQUIRED)
include_directories(${ASSIMP_INCLUDE_DIRS})
set(LIBS ${LIBS} ${ASSIMP_LIBRARIES})

add_definitions('-DAPPNAME="${PROJECT_NAME}"')

aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${LIBS})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

install(DIRECTORY shaders DESTINATION ${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME})
