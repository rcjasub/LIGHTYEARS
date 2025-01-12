cmake_minimum_required(VERSION 3.27.7)

project(LightYears
		VERSION 1.0.0
		LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS       OFF)


add_executable(${LIGHT_YEARS_GAME_TARGET_NAME}
${CMAKE_CURRENT_SOURCE_DIR}/src/GameFramework/gameApplication.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/GameFramework/gameApplication.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/Weapon/Weapon.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/Weapon/Weapon.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/Weapon/Bullet.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/Weapon/Bullet.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/Weapon/BulletShooter.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/Weapon/BulletShooter.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/Weapon/ThreeWayShooter.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/Weapon/ThreeWayShooter.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/Weapon/FrontalWiper.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/Weapon/FrontalWiper.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/Player/PlayerSpaceShip.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/Player/PlayerSpaceShip.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/Player/Player.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/Player/Player.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/Player/PlayerManager.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/Player/PlayerManager.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/Player/Reward.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/Player/Reward.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/SpaceShip/SpaceShip.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/SpaceShip/SpaceShip.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/GamePlay/HealthComponent.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/GamePlay/HealthComponent.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/VFX/Explosion.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/VFX/Explosion.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/VFX/Explosion.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/VFX/Explosion.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/EnemySpaceShip.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/EnemySpaceShip.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/Vanguard.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/Vanguard.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/Levels/GameLevel1.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/Levels/GameLevel1.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/VanguardStage.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/VanguardStage.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/TwinBlade.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/TwinBlade.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/TwinBladeStage.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/TwinBladeStage.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/Hexagon.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/Hexagon.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/HexagonStage.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/HexagonStage.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/UFO.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/UFO.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/UFOStage.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/UFOStage.cpp

)

target_include_directories(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include

)

target_link_libraries(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC ${LIGHT_YEARS_ENGINE_TARGET_NAME})

function(CopyLibDirToTarget LIB_NAME TARGET_NAME)
add_custom_command(  
	TARGET ${TARGET_NAME}
	POST_BUILD
	COMMAND
	${CMAKE_COMMAND} -E copy_directory
	$<TARGET_FILE_DIR:${LIB_NAME}>
	$<TARGET_FILE_DIR:${TARGET_NAME}>
)
endfunction()

CopyLibDirToTarget(${LIGHT_YEARS_ENGINE_TARGET_NAME} ${LIGHT_YEARS_GAME_TARGET_NAME})

set(RESOURCE_FOLDER_NAME "assets")
set(RESOURCE_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_FOLDER_NAME}")

add_custom_command(
	TARGET ${LIGHT_YEARS_GAME_TARGET_NAME} 
	POST_BUILD
	COMMAND 
	${CMAKE_COMMAND} -E copy_directory
	${RESOURCE_SRC_DIR}
	$<TARGET_FILE_DIR:${LIGHT_YEARS_GAME_TARGET_NAME}>/${RESOURCE_FOLDER_NAME}
)

configure_file(
	"config.h.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/config.h" ESCAPE_QUOTES
)