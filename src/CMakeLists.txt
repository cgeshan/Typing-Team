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

message(STATUS "Copying media files")

# Set the source directory to the current directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Set the destination directory to a subdirectory called "media" in the build directory
set(DEST_DIR ${CMAKE_BINARY_DIR}/)

# Determine if the operating system is macOS
if(APPLE)
  # Copy the media folder, excluding .wav files due to yssimplesound issue
  message(STATUS "Game music is not playable on MAC OSX")
  file(GLOB MEDIA_FILES ${SOURCE_DIR}/media/*)
  foreach(MEDIA_FILE ${MEDIA_FILES})
    get_filename_component(MEDIA_FILENAME ${MEDIA_FILE} NAME)
    if(NOT ${MEDIA_FILENAME} MATCHES ".*\\.wav")
      file(COPY ${MEDIA_FILE} DESTINATION ${DEST_DIR}/media)
    endif()
  endforeach()

else()
  # Copy the entire media folder
  file(COPY ${SOURCE_DIR}/media DESTINATION ${DEST_DIR})

endif()# Copy the media folder using the file command

