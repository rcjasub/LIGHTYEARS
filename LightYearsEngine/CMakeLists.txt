add_library(${LIGHT_YEARS_ENGINE_TARGET_NAME} STATIC
	src/framework/Application.hpp
	src/framework/Application.cpp

	src/framework/World.hpp
	src/framework/World.cpp

	src/framework/Actor.hpp
	src/framework/Actor.cpp

	src/framework/AssetManager.hpp
	src/framework/AssetManager.cpp

	src/framework/Object.hpp
	src/framework/Object.cpp

	src/framework/Delegate.cpp
	src/framework/Delegate.hpp

	src/framework/Core.hpp
	src/framework/Core.cpp

	src/framework/MathUtility.hpp
	src/framework/MathUtility.cpp

	src/framework/PhysicsSystem.hpp
	src/framework/PhysicsSystem.cpp

	src/EntryPoint.h
	src/EntryPoint.cpp

	src/vfx/Particle.cpp
	src/vfx/Particle.hpp

	src/framework/TimerManager.cpp
	src/framework/TimerManager.hpp

	src/gameplay/GameStage.cpp
	src/gameplay/GameStage.hpp

	src/gameplay/WaitStage.cpp
	src/gameplay/WaitStage.hpp

	src/widgets/HUD.cpp
	src/widgets/HUD.hpp

	src/widgets/Widget.cpp
	src/widgets/Widget.hpp

	src/widgets/TextWidget.cpp
	src/widgets/TextWidget.hpp

	src/widgets/ValueGauge.cpp
	src/widgets/ValueGauge.hpp

	src/widgets/ImageWidget.cpp
	src/widgets/ImageWidget.hpp

	src/widgets/Button.cpp
	src/widgets/Button.hpp

	src/framework/BackDropActor.cpp
	src/framework/BackDropActor.hpp

	src/framework/BackGroundLayer.cpp
	src/framework/BackGroundLayer.hpp

	src/engine/Vector2D.hpp
)

target_include_directories(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC
	src/engine
	src/framework
	src/gameplay
	src/vfx
	src/widgets
)

function(CopyLibToTarget LIB_NAME TARGET_NAME)
	add_custom_command(TARGET ${TARGET_NAME}
			POST_BUILD
			COMMAND
			${CMAKE_COMMAND} -E copy_if_different
			$<TARGET_FILE:${LIB_NAME}>
			$<TARGET_FILE_DIR:${TARGET_NAME}>
	)
endfunction()

include(FetchContent)
option(SFML "SFML" OFF)
option(BOX2D "BOX2D" OFF)
option(SDL2 "SDL2" OFF)
option(IMUGUI "IMUGUI" OFF)
option(GLFW "GLFW" OFF)

if(${SFML})
	set(SFML_LIB_NAME SFML)

	FetchContent_Declare(
		${SFML_LIB_NAME}
		GIT_REPOSITORY https://github.com/SFML/SFML
		GIT_TAG 2.5.1
		GIT_SHALLOW FALSE
	)

	FetchContent_MakeAvailable(${SFML_LIB_NAME})

	target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-graphics)
	target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-window)
	target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-system)
	target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-audio)

	CopyLibToTarget(sfml-graphics ${LIGHT_YEARS_ENGINE_TARGET_NAME})
	CopyLibToTarget(sfml-window ${LIGHT_YEARS_ENGINE_TARGET_NAME})
	CopyLibToTarget(sfml-system ${LIGHT_YEARS_ENGINE_TARGET_NAME})
	CopyLibToTarget(sfml-audio ${LIGHT_YEARS_ENGINE_TARGET_NAME})
endif (${SFML})

if(${BOX2D})
	MESSAGE(STATUS "BOX2D: ${BOX2D} - Fetching BOX2D")
	option(BOX2D_BUILD_UNIT_TESTS "build box2d unit tests" OFF)
	set(BOX2D_LIB_NAME Box2D)
	FetchContent_Declare(
			${BOX2D_LIB_NAME}
			GIT_REPOSITORY https://github.com/erincatto/box2d
			GIT_TAG v2.4.1
			GIT_SHALLOW FALSE
	)

	FetchContent_MakeAvailable(${BOX2D_LIB_NAME})
	target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC box2d)
	CopyLibToTarget(box2d ${LIGHT_YEARS_ENGINE_TARGET_NAME})
endif(${BOX2D})

if(${SDL2})
	set(FETCHCONTENT_QUIET FALSE)

	# glm
	FetchContent_Declare(
			GLM
			GIT_REPOSITORY  https://github.com/g-truc/glm.git
			GIT_TAG         0.9.9.8
			GIT_SHALLOW     TRUE
			GIT_PROGRESS    TRUE
	)
	FetchContent_MakeAvailable(GLM)

	# glfw
	FetchContent_Declare(
			GLFW
			GIT_REPOSITORY  https://github.com/glfw/glfw.git
			GIT_TAG         3.3.8
			GIT_SHALLOW     TRUE
			GIT_PROGRESS    TRUE
	)
	FetchContent_MakeAvailable(GLFW)

	# imgui
	FetchContent_Declare(
			IMGUI
			GIT_REPOSITORY  https://github.com/ocornut/imgui.git
			GIT_TAG         v1.89.7
			GIT_SHALLOW     TRUE
			GIT_PROGRESS    TRUE
	)
	FetchContent_MakeAvailable(IMGUI)

	option(SDL2MIXER_MOD OFF)
	option(SDL2MIXER_WAVPACK OFF)
	option(SDL2MIXER_MIDI_FLUIDSYNTH OFF)
	option(SDL2MIXER_OPUS OFF)
	option(SDL2MIXER_FLAC_LIBFLAC OFF)
	option(SDL2MIXER_MOD_XMP OFF)

	# sdl2
	FetchContent_Declare(
			SDL2
			GIT_REPOSITORY  https://github.com/libsdl-org/SDL
			GIT_TAG         release-2.28.1
			GIT_SHALLOW TRUE
			GIT_PROGRESS    TRUE
	)
	FetchContent_MakeAvailable(SDL2)

	# sdl2_image
	FetchContent_Declare(
			SDL2_IMAGE
			GIT_REPOSITORY  https://github.com/libsdl-org/SDL_image
			GIT_TAG         release-2.6.3
			GIT_SHALLOW TRUE
			GIT_PROGRESS    TRUE
	)

	set(SDL2IMAGE_INSTALL OFF)
	set(BUILD_SHARED_LIBS FALSE)

	FetchContent_MakeAvailable(SDL2_IMAGE)

	# sdl2_mixer
	FetchContent_Declare(
			SDL2_MIXER
			GIT_REPOSITORY  https://github.com/libsdl-org/SDL_mixer.git
			GIT_TAG         release-2.6.3
			GIT_SHALLOW TRUE
			GIT_PROGRESS    TRUE
	)
	FetchContent_MakeAvailable(SDL2_MIXER)

	# sdl2_ttf
	FetchContent_Declare(
			SDL2_TTF
			GIT_REPOSITORY  https://github.com/libsdl-org/SDL_ttf.git
			GIT_TAG          release-2.20.2
			GIT_SHALLOW     TRUE
			GIT_PROGRESS    TRUE
	)
	FetchContent_MakeAvailable(SDL2_TTF)

	set(SDL_LIBRARIES
			${SDL_LIBRARIES}
			SDL2::SDL2main
			SDL2::SDL2-static
			SDL2_image::SDL2_image-static
			SDL2_mixer::SDL2_mixer-static
			SDL2_ttf::SDL2_ttf-static)

	include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR} ${glm_SOURCE_DIR})
endif(${SDL2})

if (${IMUGUI})
	add_library(imgui STATIC
			# Main Imgui files
			${CMAKE_BINARY_DIR}/_deps/imgui-src/imgui.cpp
			${CMAKE_BINARY_DIR}/_deps/imgui-src/imgui.h
			${CMAKE_BINARY_DIR}/_deps/imgui-src/imgui_draw.cpp
			${CMAKE_BINARY_DIR}/_deps/imgui-src/imgui_tables.cpp
			${CMAKE_BINARY_DIR}/_deps/imgui-src/imgui_widgets.cpp
			${CMAKE_BINARY_DIR}/_deps/imgui-src/imgui_demo.cpp
			# SDL2+OpenGL-specific files
			${CMAKE_BINARY_DIR}/_deps/imgui-src/backends/imgui_impl_sdl2.cpp
			${CMAKE_BINARY_DIR}/_deps/imgui-src/backends/imgui_impl_sdl2.h
			${CMAKE_BINARY_DIR}/_deps/imgui-src/backends/imgui_impl_opengl3.cpp
			${CMAKE_BINARY_DIR}/_deps/imgui-src/backends/imgui_impl_opengl3.h)
	add_library(imgui::imgui ALIAS imgui)

	target_link_libraries(imgui
			PUBLIC
			glfw
			$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
			$<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
	)
	target_include_directories(imgui PUBLIC libs/imgui/ libs/imgui/backends/)
endif ()