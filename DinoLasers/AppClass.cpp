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
	
	level = new TestLevel();
	level->Load();
	//Initialize positions
	/*m_v3O1 = vector3(-2.5f, 0.0f, 0.0f);
	m_v3O2 = vector3(2.5f, 0.0f, 1.0f);
	playerRotation = quaternion(vector3(0.0f));
	playerPosition = vector3(0.0f, 0.0f, 0.0f);
	forward = vector3(0.0f, 0.0f, 0.1f);

	groundPoints.push_back(vector3(100.0f, 0.0f, 100.0f));
	groundPoints.push_back(vector3(-100.0f, 0.0f, 100.0f));
	groundPoints.push_back(vector3(-100.0f, 0.0f, -100.0f));
	groundPoints.push_back(vector3(100.0f, 0.0f, -100.0f));


	spacing = 5.0f;
	cameraTarget = playerPosition;
	cameraPosition = vector3(cameraTarget.x, cameraTarget.y + spacing, cameraTarget.z - spacing);
	
	m_pCameraMngr->SetPositionTargetAndView(cameraPosition, cameraTarget, vector3(0.0f, 1.0f, 0.0f));*/
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

	/*steve->GetTransform().SetOrentation(playerRotation);

	creeper->GetTransform().SetPosition(m_v3O2);
	creeper->GetTransform().SetOrentation(m_qArcBall);
	
	cameraTarget = static_cast<vector3>(glm::translate(m_pMeshMngr->GetModelMatrix("Steve"), vector3(0, 0.8f, 0))[3]);
	cameraPosition = static_cast<vector3>(glm::translate(m_pMeshMngr->GetModelMatrix("Steve"), vector3(0, 2, -spacing))[3]);
	
	m_pCameraMngr->SetPositionTargetAndView(cameraPosition, cameraTarget, vector3(0, 1, 0));*/

	//Add a representation of the Spheres to the render list

	//Adds all loaded instance to the render list
	//m_pMeshMngr->AddInstanceToRenderList("ALL");

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