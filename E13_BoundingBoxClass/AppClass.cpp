#include "AppClass.h"

BoundingObjectManager* BoundingObjectManager::instance = nullptr;
GameObjectManager* GameObjectManager::instance = nullptr;

void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("MyBoundingSphereClass example"); // Window Name

	BoundingObjectManager* boundingObjMngr = BoundingObjectManager::GetInstance();

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Initialize positions
	m_v3O1 = vector3(-2.5f, 0.0f, 0.0f);
	m_v3O2 = vector3(2.5f, 0.0f, 0.0f);
	playerRotation = quaternion(vector3(0.0f));

	groundPoints.push_back(vector3(100.0f, 0.0f, 100.0f));
	groundPoints.push_back(vector3(-100.0f, 0.0f, 100.0f));
	groundPoints.push_back(vector3(-100.0f, 0.0f, -100.0f));
	groundPoints.push_back(vector3(100.0f, 0.0f, -100.0f));


	spacing = 5.0f;
	cameraTarget = m_v3O1;
	cameraPosition = vector3(cameraTarget.x, cameraTarget.y + spacing, cameraTarget.z - spacing);
	steveMatrix = glm::translate(m_v3O1);
	
	//m_pCameraMngr->SetTarget(cameraTarget);
	//m_pCameraMngr->SetPosition(cameraPosition);
	m_pCameraMngr->SetPositionTargetAndView(cameraPosition, cameraTarget, vector3(0.0f, 1.0f, 0.0f));

	//Load Models
	m_pMeshMngr->LoadModel("Minecraft\\MC_Steve.obj", "Steve");
	m_pMeshMngr->LoadModel("Minecraft\\MC_Creeper.obj", "Creeper");	

	steve = BoundingObjectManager::GetInstance()->AddBox(m_pMeshMngr->GetVertexList("Steve"));
	creeper = BoundingObjectManager::GetInstance()->AddBox(m_pMeshMngr->GetVertexList("Creeper"));
	ground = BoundingObjectManager::GetInstance()->AddBox(groundPoints);

	//
	Component* mR = new ModelRender("Minecraft\\MC_Steve.obj", "Steve");
	GameObject go;
	go.AddComponent(mR);

	//GameObjectManager::GetInstance()->AddGameObject(go);
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update(false);

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	BoundingObjectManager::GetInstance()->CheckCollisions();
	GameObjectManager::GetInstance()->Update(0);//TODO: ADD DELTA TIME

	ArcBall();

	steveMatrix = glm::translate(m_v3O1);

	//Set the model matrices for both objects and Bounding Spheres
	m_pMeshMngr->SetModelMatrix(steveMatrix * ToMatrix4(playerRotation), "Steve");
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O2), "Creeper");


	BoundingObjectManager::GetInstance()->SetModelMatrix(steve, m_pMeshMngr->GetModelMatrix("Steve"));
	BoundingObjectManager::GetInstance()->SetModelMatrix(creeper, m_pMeshMngr->GetModelMatrix("Creeper"));
	
	cameraTarget = static_cast<vector3>(glm::translate(m_pMeshMngr->GetModelMatrix("Steve"), vector3(0, 0, 0))[3]);
	cameraPosition = static_cast<vector3>(glm::translate(m_pMeshMngr->GetModelMatrix("Steve"), vector3(0, 0, -spacing))[3]);
	
	m_pCameraMngr->SetPositionTargetAndView(cameraPosition, cameraTarget, vector3(0, 1, 0));

	//m_pBB1->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Steve"));
	//reAlign->RealignBox(m_pBB1);
	//m_pBB2->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Creeper"));

	//Add a representation of the Spheres to the render list

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}

	m_pMeshMngr->AddPlaneToQueue(matrix4(IDENTITY_M4) * glm::rotate(matrix4(IDENTITY_M4), 90.0f, vector3(1.0f, 0.0f, 0.0f)) *glm::scale(vector3(100.0f)), REBROWN);
	
	GameObjectManager::GetInstance()->Render();
	BoundingObjectManager::GetInstance()->Draw();

	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
	BoundingObjectManager::Release();
}

void AppClass::CameraRotateUp(float degrees)
{
	//vector3 temp = cameraPosition;
	//cameraPosition = cameraTarget;
	//cameraPosition *= glm::rotate(matrix4(IDENTITY_M4), degrees, vector3(1.0f, 0.0f, 0.0f));
	//cameraPosition += temp;
}