add_executable(maze-generator
    main.cpp
    app.cpp
    app.h
    path.cpp
    path.h
    direction.h
    random.h)
target_link_libraries(maze-generator PRIVATE ImGui-SFML::ImGui-SFML)

if(WIN32)
  if (BUILD_SHARED_LIBS)
    add_custom_command(TARGET maze-generator POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
          $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
          $<TARGET_FILE:sfml-graphics>
          $<TARGET_FILE:sfml-window>
          $<TARGET_FILE:sfml-system>
          $<TARGET_FILE_DIR:maze-generator>)
  endif()
  set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT maze-generator)
endif()