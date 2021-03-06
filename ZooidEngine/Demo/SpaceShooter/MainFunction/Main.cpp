#include "ZooidEngine/ZEGameContext.h"
#include "ZooidEngine/MainFunction/MainFunctions.h"
#include "ZooidEngine/UnitTest/UnitTest.h"
#include "ZooidEngine/Renderer/DrawList.h"

#include "MainFunctions.h"

int main(int argc, char** argv) {

	// Init Engine
	ZE::GameContext gameContext;

	ZE::MainSetup(&gameContext);

	SpaceShooter::MainSetup(&gameContext);

	// Main Loop
	while (!gameContext.getRenderer()->IsClose()) {
		ZE::MainThreadJob(&gameContext);
	}

	gameContext.getDrawList()->Reset();

	SpaceShooter::MainClean(&gameContext);

	ZE::MainClean(&gameContext);

	return 0;

}