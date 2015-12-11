#include "AppClass.h"

BoundingObjectManager* BoundingObjectManager::instance = nullptr;
GameObjectManager* GameObjectManager::instance = nullptr;

void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("DINO LASERS"); // Window Name

	BoundingObjectManager* boundingObjMngr = BoundingObjectManager::GetInstance();

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	srand(time(NULL));
	
	level = new TitleScreen();
	level->Load();
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update(false);

	float dt = m_pSystem->LapClock();

	oldLevel = level->NextLevel();
	if (oldLevel != level) {
		if (level != nullptr) {
			delete level;
			level = nullptr;
			std::cout << "NEW LEVEL\n";
		}
		GameObjectManager::GetInstance()->Clear();
		BoundingObjectManager::GetInstance()->Clear();
		level = oldLevel;
		level->Load();
	}
	if (!false) {
		level->Update(dt);
	}
	else {
		level->PausedUpdate(dt);
		MeshManagerSingleton::GetInstance()->PrintLine("PAUSED!!");
	}

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	/*m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("0 FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);	*/
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	level->Render();

	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(level);

	super::Release(); //release the memory of the inherited fields
	BoundingObjectManager::Release();
}