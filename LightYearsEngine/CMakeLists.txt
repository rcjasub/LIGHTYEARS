cmake_minimum_required(VERSION 3.27.7)

project(LightYears
        VERSION 1.0.0
        LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS       OFF)

# Add the engine's source files as a static library
add_library(${LIGHT_YEARS_ENGINE_TARGET_NAME} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/PhysicsSystem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SRC/framework/PhysicsSystem.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/application.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SRC/framework/application.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/MessUtility.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SRC/framework/MessUtility.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/AssetsManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SRC/framework/AssetsManager.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Object.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SRC/framework/Object.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Actor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SRC/framework/Actor.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/world.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SRC/framework/world.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/core.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SRC/framework/core.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Delegate.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SRC/framework/Delegate.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/VFX/Particle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SRC/VFX/Particle.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/EntryPoint.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SRC/EntryPoint.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/TimerManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SRC/framework/TimerManager.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/GamePlay/GameStage.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SRC/GamePlay/GameStage.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/GamePlay/WaitStage.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SRC/GamePlay/WaitStage.cpp
)

# Include directories for the engine target
target_include_directories(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Fetch and link SFML libraries
include(FetchContent)

set(SFML_LIB_NAME SFML)
FetchContent_Declare(
    ${SFML_LIB_NAME}
    GIT_REPOSITORY https://github.com/SFML/SFML
    GIT_TAG 2.5.1
    GIT_SHALLOW FALSE
)
FetchContent_MakeAvailable(${SFML_LIB_NAME})

target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

# Fetch and link Box2D library
set(BOX2D_LIB_NAME Box2D)
FetchContent_Declare(
    ${BOX2D_LIB_NAME}
    GIT_REPOSITORY https://github.com/erincatto/box2d
    GIT_TAG v2.4.1
    GIT_SHALLOW FALSE
)
FetchContent_MakeAvailable(${BOX2D_LIB_NAME})

target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC
    box2d
)

# Function to copy libraries to the target after building
function(CopyLibToTarget LIB_NAME TARGET_NAME)
    add_custom_command(TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:${LIB_NAME}>
        $<TARGET_FILE_DIR:${TARGET_NAME}>
    )
endfunction()

# Copy the SFML and Box2D libraries to the engine target after build
CopyLibToTarget(sfml-graphics ${LIGHT_YEARS_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-window ${LIGHT_YEARS_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-system ${LIGHT_YEARS_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-audio ${LIGHT_YEARS_ENGINE_TARGET_NAME})

CopyLibToTarget(box2d ${LIGHT_YEARS_ENGINE_TARGET_NAME})
