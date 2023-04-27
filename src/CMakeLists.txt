if(APPLE)
	message(STATUS "MAC OSX found! Building with MACOSX_BUNDLE")
        add_executable(main MACOSX_BUNDLE Menu.cpp
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

else()
        if(MSVC)
                message(STATUS "MSVC found!")

        else()
                message(STATUS "UNIX OS found!")
        endif()

        add_executable(main Menu.cpp Menu.h
                            Rover.cpp Rover.h
                            yspng.cpp yspng.h
                            Galaga.cpp Galaga.h
                            tutorial.cpp tutorial.h
                            overworld.cpp overworld.h
                            textinput.cpp textinput.h
                            textstring.cpp textstring.h
                            minigame_mars.cpp minigame_mars.h
                            minigame_rockets.cpp minigame_rockets.h

                            ysglfontdata.c)
    
endif()


target_link_libraries(main fssimplewindow yssimplesound)

add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/media/
                ${CMAKE_CURRENT_BINARY_DIR}/media/)
                
add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/media/*
                ${CMAKE_CURRENT_BINARY_DIR}/media/)
