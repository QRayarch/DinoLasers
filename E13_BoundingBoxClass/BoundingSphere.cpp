#include "BoundingSphere.h"

BoundingSphere::BoundingSphere(std::vector<vector3> listOfVertex){
	m_m4ToWorld = IDENTITY_M4;

	vector3 vMin, vMax;
	
	vMin = vMax = listOfVertex[0];

	for (uint i = 1; i < listOfVertex.size(); i++)
	{
		if (vMax.x < listOfVertex[i].x)
			vMax.x = listOfVertex[i].x;
		else if (vMin.x > listOfVertex[i].x)
			vMin.x = listOfVertex[i].x;

		if (vMax.y < listOfVertex[i].y)
			vMax.y = listOfVertex[i].y;
		else if (vMin.y > listOfVertex[i].y)
			vMin.y = listOfVertex[i].y;

		if (vMax.z < listOfVertex[i].z)
			vMax.z = listOfVertex[i].z;
		else if (vMin.z > listOfVertex[i].z)
			vMin.z = listOfVertex[i].z;
	}

	m_v3Center = (vMax + vMin) / 2.0f;

	m_fRadius = 0.0f;
	float fDistance;
	for (uint i = 0; i < listOfVertex.size(); i++)
	{
		fDistance = glm::distance(m_v3Center, listOfVertex[i]);
		if (m_fRadius < fDistance)
			m_fRadius = fDistance;
	}
}
bool BoundingSphere::IsColliding(BoundingSphere* pOther){
	return glm::distance(pOther->m_v3Center, this->m_v3Center) <= pOther->m_fRadius + this->m_fRadius;
}

void BoundingSphere::SetModelMatrix(matrix4 a_m4ToWorld){ m_m4ToWorld = a_m4ToWorld; }
vector3 BoundingSphere::GetCenterGlobal(void){ return vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f)); }
float BoundingSphere::GetRadius(){ return m_fRadius; }
void BoundingSphere::SetRadius(float radius) {
	m_fRadius = radius;
}