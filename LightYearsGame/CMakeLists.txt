add_executable(${LIGHT_YEARS_GAME_TARGET_NAME} 
${CMAKE_CURRENT_SOURCE_DIR}/include/GameFramework/gameApplication.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/GameFramework/gameApplication.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/Weapon/Weapon.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/Weapon/Weapon.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/Weapon/Bullet.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/Weapon/Bullet.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/Weapon/BulletShooter.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/Weapon/BulletShooter.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/Weapon/ThreeWayShooter.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/Weapon/ThreeWayShooter.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/Weapon/FrontalWiper.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/Weapon/FrontalWiper.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/Player/PlayerSpaceShip.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/Player/PlayerSpaceShip.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/Player/Reward.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/Player/Reward.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/SpaceShip/SpaceShip.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/SpaceShip/SpaceShip.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/GamePlay/HealthComponent.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/GamePlay/HealthComponent.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/VFX/Explosion.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/VFX/Explosion.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/VFX/Explosion.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/VFX/Explosion.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/EnemySpaceShip.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/Enemy/EnemySpaceShip.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/Vanguard.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/Enemy/Vanguard.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/Levels/GameLevel1.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/Levels/GameLevel1.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/VanguardStage.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/Enemy/VanguardStage.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/TwinBlade.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/Enemy/TwinBlade.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/TwinBladeStage.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/Enemy/TwinBladeStage.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/Hexagon.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/Enemy/Hexagon.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/HexagonStage.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/Enemy/HexagonStage.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/UFO.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/Enemy/UFO.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/UFOStage.h
${CMAKE_CURRENT_SOURCE_DIR}/SRC/Enemy/UFOStage.cpp

)

target_include_directories(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC
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