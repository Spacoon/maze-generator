include(FetchContent)

# SFML
FetchContent_Declare(
  sfml
  URL https://github.com/SFML/SFML/archive/refs/tags/2.6.1.zip
  GIT_TAG 69ea0cd863aed1d4092b970b676924a716ff718b # 2.61
)
add_subdirectory(sfml)

# Dear ImGui
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG 277ae93c41314ba5f4c7444f37c4319cdf07e8cf # 1.90.4
)
FetchContent_MakeAvailable(imgui)

# ImGui-SFML
FetchContent_Declare(
  imgui-sfml
  GIT_REPOSITORY https://github.com/SFML/imgui-sfml
  GIT_TAG de565ac8f2b795dedc0307b60830cb006afd2ecd# 2.6
)
add_subdirectory(imgui-sfml)
