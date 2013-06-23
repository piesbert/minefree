project (minefree)
cmake_minimum_required (VERSION 2.6)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
subdirs (src config)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ansi -Wall -pedantic")

set(CMAKE_MODULE_PATH "modules")

if(UNIX)
        if(EXISTS "/usr/share/OGRE/cmake")
                set(CMAKE_MODULE_PATH "/usr/share/OGRE/cmake/modules")
                set(OGRE_SAMPLES_INCLUDEPATH "/usr/share/OGRE/samples/Common/include/")
        else()
                message(SEND_ERROR "Failed to find module path.")
        endif(EXISTS "/usr/share/OGRE/cmake")
endif(UNIX)

find_package(SDL REQUIRED)
find_package(OGRE REQUIRED)
find_package(OIS REQUIRED)

message(${OGRE_PLUGIN_DIR_TMP} "****************************")

link_libraries (
        ${SDL_LIBRARY}
        SDLmain
        ${OGRE_LIBRARIES}
        OIS
        )
