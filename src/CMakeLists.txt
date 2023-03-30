if(MSVC)
	set(EXE_TYPE WIN32)

elseif(APPLE)
	set(EXE_TYPE MACOSX_BUNDLE)

elseif()
    set(EXE_TYPE )
    
endif()

add_executable(main ${EXE_TYPE}     Menu.cpp
                                    Rover.cpp
                                    yspng.cpp
                                    Galaga.cpp
                                    tutorial.cpp
                                    overworld.cpp
                                    textinput.cpp
                                    textstring.cpp
                                    minigame_mars.cpp
                                    minigame_rockets.cpp

                                    ysglfontdata.c

                                    Menu.h
                                    Rover.h
                                    yspng.h
                                    Galaga.h
                                    tutorial.h
                                    overworld.h
                                    textinput.h
                                    textstring.h
                                    ysglfontdata.h
                                    minigame_mars.h
                                    genericchararray.h
                                    minigame_rockets.h)

target_link_libraries(main fssimplewindow yssimplesound)

add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/media/*
                ${CMAKE_CURRENT_BINARY_DIR}/media)
