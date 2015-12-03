#include "ModelRender.h"


ModelRender::ModelRender(String filePath, String modelName)
{
	if (MeshManagerSingleton::GetInstance() != nullptr && MeshManagerSingleton::GetInstance()->m_pModelMngr != nullptr) {
		MeshManagerSingleton::GetInstance()->m_pModelMngr->LoadModel(filePath, modelName);
	}
	else {
		assert(true);
	}
	model = modelName;
}


ModelRender::~ModelRender()
{
}

void ModelRender::Update(float dt) {
	//Okay not actually a render, but good enough
	MeshManagerSingleton::GetInstance()->SetModelMatrix(GetGameObject()->GetWorldMatrix(), model);
	MeshManagerSingleton::GetInstance()->AddInstanceToRenderList(model);
}

String ModelRender::GetModel() { return model; }