#include "BoundingBox.h"
//  BoundingBox
void BoundingBox::Init(void)
{
	m_m4ToWorld = IDENTITY_M4;
	isVisible = true;

	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);

	m_v3HalfWidth = vector3(0.0f);


	normals.push_back(REAXISX);
	normals.push_back(REAXISY);
	normals.push_back(REAXISZ);
}
void BoundingBox::Swap(BoundingBox& other)
{
	std::swap(m_m4ToWorld, other.m_m4ToWorld);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);

	std::swap(normals, other.normals);

	std::swap(m_v3HalfWidth, other.m_v3HalfWidth);
}
void BoundingBox::Release(void)
{

}
//The big 3
BoundingBox::BoundingBox(std::vector<vector3> a_lVectorList)
{
	//Init the default values
	Init();

	RecalculateBounds(a_lVectorList);

}

BoundingBox::BoundingBox(BoundingBox const& other)
{
	m_m4ToWorld = other.m_m4ToWorld;
	isVisible = other.isVisible;

	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	normals = other.normals;

	m_v3HalfWidth = other.m_v3HalfWidth;
}
BoundingBox& BoundingBox::operator=(BoundingBox const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		BoundingBox temp(other);
		Swap(temp);
	}
	return *this;
}
BoundingBox::~BoundingBox(){ Release(); };

void BoundingBox::RealignBox(BoundingBox* const box) {
	std::vector<vector3> vertices;

	isVisible = true;

	vector3 fullWidth = box->GetHalfWidth();
	fullWidth.x *= 2;
	fullWidth.y *= 2;
	fullWidth.z *= 2;

	vertices.push_back(box->ToGlobal(box->m_v3Min));
	vertices.push_back(box->ToGlobal(vector3(box->m_v3Max.x, box->m_v3Min.y, box->m_v3Min.z)));
	vertices.push_back(box->ToGlobal(vector3(box->m_v3Min.x, box->m_v3Min.y, box->m_v3Max.z)));
	vertices.push_back(box->ToGlobal(vector3(box->m_v3Max.x, box->m_v3Min.y, box->m_v3Max.z)));

	vertices.push_back(box->ToGlobal(vector3(box->m_v3Min.x, box->m_v3Max.y, box->m_v3Min.z)));
	vertices.push_back(box->ToGlobal(vector3(box->m_v3Max.x, box->m_v3Max.y, box->m_v3Min.z)));
	vertices.push_back(box->ToGlobal(vector3(box->m_v3Min.x, box->m_v3Max.y, box->m_v3Max.z)));
	vertices.push_back(box->ToGlobal(box->m_v3Max));

	RecalculateBounds(vertices);
}

void BoundingBox::RecalculateBounds(std::vector<vector3> a_lVectorList) {
	//Count the points of the incoming list
	uint nVertexCount = a_lVectorList.size();

	//If there are none just return, we have no information to create the BS from
	if (nVertexCount == 0)
		return;

	//Max and min as the first vector of the list
	m_v3Max = m_v3Min = a_lVectorList[0];

	//Get the max and min out of the list
	for (uint nVertex = 1; nVertex < nVertexCount; nVertex++)
	{
		if (m_v3Min.x > a_lVectorList[nVertex].x) //If min is larger than current
			m_v3Min.x = a_lVectorList[nVertex].x;
		else if (m_v3Max.x < a_lVectorList[nVertex].x)//if max is smaller than current
			m_v3Max.x = a_lVectorList[nVertex].x;

		if (m_v3Min.y > a_lVectorList[nVertex].y) //If min is larger than current
			m_v3Min.y = a_lVectorList[nVertex].y;
		else if (m_v3Max.y < a_lVectorList[nVertex].y)//if max is smaller than current
			m_v3Max.y = a_lVectorList[nVertex].y;

		if (m_v3Min.z > a_lVectorList[nVertex].z) //If min is larger than current
			m_v3Min.z = a_lVectorList[nVertex].z;
		else if (m_v3Max.z < a_lVectorList[nVertex].z)//if max is smaller than current
			m_v3Max.z = a_lVectorList[nVertex].z;
	}

	//with the max and the min we calculate the center
	m_v3Center = (m_v3Min + m_v3Max) / 2.0f;

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidth.x = glm::distance(vector3(m_v3Min.x, 0.0f, 0.0f), vector3(m_v3Max.x, 0.0f, 0.0f)) / 2.0f;
	m_v3HalfWidth.y = glm::distance(vector3(0.0f, m_v3Min.y, 0.0f), vector3(0.0f, m_v3Max.y, 0.0f)) / 2.0f;
	m_v3HalfWidth.z = glm::distance(vector3(0.0f, 0.0f, m_v3Min.z), vector3(0.0f, 0.0f, m_v3Max.z)) / 2.0f;
}

//Accessors
void BoundingBox::SetModelMatrix(matrix4 a_m4ToWorld){ m_m4ToWorld = a_m4ToWorld; }
matrix4 BoundingBox::GetModelMatrix(void){ return m_m4ToWorld; }
vector3 BoundingBox::GetCenterLocal(void){ return m_v3Center; }
vector3 BoundingBox::GetCenterGlobal(void){ return vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f)); }
vector3 BoundingBox::GetHalfWidth(void){ return m_v3HalfWidth; }

vector3 BoundingBox::ToGlobal(vector3 vec) {
	return vector3(m_m4ToWorld * vector4(vec, 1.0f));
}

//--- Non Standard Singleton Methods
bool BoundingBox::IsColliding(BoundingBox* const colliding)
{
	if (colliding->DoesUseSAT()) {
		return CheckSATCollision(colliding);
	}
	return CheckAABBCollision(colliding);
}

bool BoundingBox::CheckAABBCollision(BoundingBox* const colliding) {
	//Get all vectors in global space
	vector3 v3Min = ToGlobal(m_v3Min);
	vector3 v3Max = ToGlobal(m_v3Max);

	vector3 v3MinO = colliding->ToGlobal(colliding->m_v3Min);
	vector3 v3MaxO = colliding->ToGlobal(colliding->m_v3Max);

	/*
	Are they colliding?
	For boxes we will assume they are colliding, unless at least one of the following conditions is not met
	*/
	bool bColliding = true;

	//Check for X
	if (v3Max.x < v3MinO.x)
		bColliding = false;
	if (v3Min.x > v3MaxO.x)
		bColliding = false;

	//Check for Y
	if (v3Max.y < v3MinO.y)
		bColliding = false;
	if (v3Min.y > v3MaxO.y)
		bColliding = false;

	//Check for Z
	if (v3Max.z < v3MinO.z)
		bColliding = false;
	if (v3Min.z > v3MaxO.z)
		bColliding = false;

	return bColliding;
}

bool BoundingBox::CheckSATCollision(BoundingBox* const colliding) {
	std::vector<vector3> objectANormals = GetGlobalNormals();
	std::vector<vector3> objectBNormals = colliding->GetGlobalNormals();


	int AONSize = objectANormals.size();
	int BONSize = objectBNormals.size();

	std::vector<vector3> crossProd;

	for (int x = 0 ; x < AONSize ; x++)
	{
		for (int y = 0 ; y < BONSize ; y++)
		{
			crossProd.push_back(  glm::cross(objectANormals[x], objectBNormals[y])  );
		}
	}

	int CPSize = crossProd.size();

	for (int z = 0; z < CPSize; z++)
	{
		vector2 pA;
		vector2 pB; //and j
	for (int i = 0; i < objectANormals.size(); i++)
	{
		vector2 p1 = Project(objectANormals[i]);
		vector2 p2 = Project(objectBNormals[i]);

		if (!IsOverlapping) return false;
	}
	for (int i = 0; i < objectBNormals.size(); i++)
	{
		vector2 p1 = Project(objectANormals[i]);
		vector2 p2 = Project(objectBNormals[i]);

		if (!IsOverlapping) return false;
	}

	return true;
}

vector2 BoundingBox::Project(vector3 normal) {
	vector2 bounds;

	std::vector<vector3> vertices;
	vertices.push_back(ToGlobal(m_v3Min));
	vertices.push_back(ToGlobal(vector3(m_v3Max.x, m_v3Min.y, m_v3Min.z)));
	vertices.push_back(ToGlobal(vector3(m_v3Min.x, m_v3Min.y, m_v3Max.z)));
	vertices.push_back(ToGlobal(vector3(m_v3Max.x, m_v3Min.y, m_v3Max.z)));

	vertices.push_back(ToGlobal(vector3(m_v3Min.x, m_v3Max.y, m_v3Min.z)));
	vertices.push_back(ToGlobal(vector3(m_v3Max.x, m_v3Max.y, m_v3Min.z)));
	vertices.push_back(ToGlobal(vector3(m_v3Min.x, m_v3Max.y, m_v3Max.z)));
	vertices.push_back(ToGlobal(m_v3Max));

	bounds.x = glm::dot(normal, vertices[0]);
	bounds.y = bounds.x;

	for (int v = 1; v < vertices.size(); v++) {
		float proj = glm::dot(normal, vertices[v]);
		if (proj > bounds.y) {
			bounds.y = proj;
		}
		else if (proj < bounds.x) {
			bounds.x = proj;
		}
	}

	return bounds;
}

bool BoundingBox::DoesUseSAT() {
	return false;
}

vector3 BoundingBox::GetMin() { return m_v3Min; }
vector3 BoundingBox::GetMax() { return m_v3Max; }

void BoundingBox::SetVisibility(bool newVisibility) {
	isVisible = newVisibility;
}

std::vector<vector3> BoundingBox::GetGlobalNormals()
{
	std::vector<vector3> gNormals = std::vector<vector3>();
	for (int i = 0; i < normals.size(); i++)
	{
		gNormals.push_back(ToGlobal(normals[i]));
	}
	return gNormals;
}

bool BoundingBox::IsOverlapping(vector2 a, vector2 b)
{
	return a.y > b.x || b.y > a.x;
}