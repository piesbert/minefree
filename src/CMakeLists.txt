set(SOURCE_FILES
                main.cpp
                config.cpp
                inputmanager.cpp
                inputevent.cpp
                actionmanager.cpp
                callbackqueue.cpp
                event.cpp
                ogrewrapper.cpp
                fppcamera.cpp
                motionstate.cpp
                quakeconsole.cpp
                command.cpp
                commandmanager.cpp
                )

add_executable(minefree ${SOURCE_FILES} )

set(Config_Path ${CMAKE_BINARY_DIR}/config/)
set(Materials_Path ${CMAKE_BINARY_DIR}/materials)

set(QuakeConsole_Materials ${Materials_Path}/quakeconsole)

configure_file(build.h.in ${CMAKE_BINARY_DIR}/config/build.h)
include_directories(${CMAKE_BINARY_DIR}/config/)
