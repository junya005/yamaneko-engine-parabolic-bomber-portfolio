cmake_minimum_required(VERSION 3.15)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(Hackathon_Tobasu CXX)

set(TARGET_NAME Hackathon_Tobasu)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ASSETS_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set(ASSETS_DEST_DIR "$<TARGET_FILE_DIR:${TARGET_NAME}>/assets")

# 依存パッケージの検索
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(glad REQUIRED)
find_package(imgui REQUIRED)
find_package(assimp REQUIRED)
find_package(OpenGL REQUIRED)

# 実行ファイルの設定
add_executable(${PROJECT_NAME} 
    src/main.cpp
    engine/Window.cpp
    engine/Renderer.cpp
    engine/TextRenderer.cpp
    engine/AssetManager.cpp
    engine/Input.cpp
)

# ターゲットにライブラリをリンク
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
    glad::glad
    imgui::imgui
    assimp::assimp
    OpenGL::GL
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    third_party/tweeny/include
)

add_custom_command(
    TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${ASSETS_SRC_DIR}"
            "${ASSETS_DEST_DIR}"
)
