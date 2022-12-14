/* Author: Cornelius Marx */
#include "LevelFactory.hpp"

/* include level header */
#include "level/LevelEmpty.hpp"
#include "level/LevelSVG.hpp"


LevelFactory::LevelFactory()
{
	/*** adding levels to register ***/

	// empty with border
	REGISTER_LEVEL(LevelEmpty,"empty", "", "Empty level with border");

	// static
	REGISTER_LEVEL_FUNC(LevelFactory::createLevelRandom, "random", "[--dynamic]""[--human]",
								"Randomized static Level and optional dynamic obstacles (flag --dynamic)");

	// static
	REGISTER_LEVEL_FUNC(LevelFactory::createLevelCustom, "custom", "[--dynamic]""[--human]",
								"Custom static Level and optional dynamic obstacles (flag --dynamic)");

	// static
	REGISTER_LEVEL_FUNC(LevelFactory::createLevelHuman, "human", "[--dynamic]""[--human]",
								"Custom static Level and optional dynamic obstacles (flag --dynamic)");

	// static
	REGISTER_LEVEL_FUNC(LevelFactory::createLevelMaze, "maze", "[--dynamic]""[--human]",
								"Custom static Level and optional dynamic obstacles (flag --dynamic)");

	// svg
	REGISTER_LEVEL(LevelSVG, "svg", "", "Levels loaded from svg-files");
	#ifdef USE_ROS
	// static map
	REGISTER_LEVEL_FUNC(LevelFactory::createLevelScenario, "scenario", "[--dynamic]",
								"Static Map Level and optional dynamic obstacles (flag --dynamic)");
	#endif
}
