add_executable(${LIGHT_YEARS_GAME_TARGET_NAME}
    src/gameFramework/GameApplication.hpp
    src/gameFramework/GameApplication.cpp

    src/spaceship/Spaceship.hpp
    src/spaceship/Spaceship.cpp

    src/player/PlayerSpaceship.hpp
    src/player/PlayerSpaceship.cpp

    src/weapon/Shooter.hpp
    src/weapon/Shooter.cpp

    src/weapon/BulletShooter.hpp
    src/weapon/BulletShooter.cpp

    src/weapon/Bullet.hpp
    src/weapon/Bullet.cpp

	src/gameplay/HealthComponent.cpp
	src/gameplay/HealthComponent.hpp

	src/vfx/Explosion.cpp
	src/vfx/Explosion.hpp

	src/enemy/EnemySpaceship.cpp
	src/enemy/EnemySpaceship.hpp

	src/enemy/Vanguard.cpp
	src/enemy/Vanguard.hpp

	src/level/GameLevelOne.cpp
	src/level/GameLevelOne.hpp

	src/stage/VanguardStage.cpp
	src/stage/VanguardStage.cpp

	src/enemy/TwinBlade.cpp
	src/enemy/TwinBlade.hpp

	src/stage/TwinBladeStage.cpp
	src/stage/TwinBladeStage.hpp

	src/enemy/Octagon.cpp
	src/enemy/Octagon.hpp

	src/stage/OctagonStage.cpp
	src/stage/OctagonStage.hpp

	src/enemy/UFO.cpp
	src/enemy/UFO.hpp

	src/stage/UfoStage.cpp
	src/stage/UfoStage.hpp

	src/weapon/ThreeWayShooter.cpp
	src/weapon/ThreeWayShooter.hpp

	src/weapon/MultiShooter.cpp
	src/weapon/MultiShooter.hpp

	src/weapon/FrontalWiper.cpp
	src/weapon/FrontalWiper.hpp

	src/player/Reward.cpp
	src/player/Reward.hpp

	src/player/Player.cpp
	src/player/Player.hpp

	src/player/PlayerManager.cpp
	src/player/PlayerManager.hpp

	src/widgets/GameplayHUD.cpp
	src/widgets/GameplayHUD.hpp

	src/level/MainMenuLevel.cpp
	src/level/MainMenuLevel.hpp

	src/widgets/MainMenuHUD.cpp
	src/widgets/MainMenuHUD.hpp

	src/stage/ChaosStage.cpp
	src/stage/ChaosStage.hpp

	src/enemy/Boss.cpp
	src/enemy/Boss.hpp

	src/enemy/BossStage.cpp
	src/enemy/BossStage.hpp
)

target_include_directories(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC
	include/
	src/
	src/enemy
	src/gameFramework
	src/gameplay
	src/level
	src/spaceship
	src/player
	src/stage
	src/vfx
	src/weapon
	src/widgets
)

target_link_libraries(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC ${LIGHT_YEARS_ENGINE_TARGET_NAME})

function(CopyLibDirToTarget LIB_NAME TARGET_NAME)
	add_custom_command(TARGET ${TARGET_NAME}
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
