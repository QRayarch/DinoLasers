#include "BoundingBox.h"
//  BoundingBox
void BoundingBox::Init(void)
{
	matrix = IDENTITY_M4;

	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);

	m_v3HalfWidth = vector3(0.0f);
	ignoreResolutionMask = 4;
}
void BoundingBox::Swap(BoundingBox& other)
{
	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);

	std::swap(m_v3HalfWidth, other.m_v3HalfWidth);
	std::swap(ignoreResolutionMask, other.ignoreResolutionMask);
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
	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	m_v3HalfWidth = other.m_v3HalfWidth;
	ignoreResolutionMask = other.ignoreResolutionMask;
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
	matrix = IDENTITY_M4;
	std::vector<vector3> vertices;
	vertices.reserve(8);

	vector3 fullWidth = box->GetHalfWidth();
	fullWidth.x *= 2;
	fullWidth.y *= 2;
	fullWidth.z *= 2;

	vertices.push_back((box->m_v3Min));
	vertices.push_back((vector3(box->m_v3Max.x, box->m_v3Min.y, box->m_v3Min.z)));
	vertices.push_back((vector3(box->m_v3Min.x, box->m_v3Min.y, box->m_v3Max.z)));
	vertices.push_back((vector3(box->m_v3Max.x, box->m_v3Min.y, box->m_v3Max.z)));

	vertices.push_back((vector3(box->m_v3Min.x, box->m_v3Max.y, box->m_v3Min.z)));
	vertices.push_back((vector3(box->m_v3Max.x, box->m_v3Max.y, box->m_v3Min.z)));
	vertices.push_back((vector3(box->m_v3Min.x, box->m_v3Max.y, box->m_v3Max.z)));
	vertices.push_back((box->m_v3Max));

	RecalculateBounds(vertices);
}

void BoundingBox::Update(float dt) {
	matrix = GetGameObject()->GetWorldMatrix();
}

void BoundingBox::RecalculateBounds(std::vector<vector3>& a_lVectorList) {//HOT
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
		if (m_v3Min.x > a_lVectorList[nVertex].x) //If min is larger than current//HOT
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
	m_v3HalfWidth.x = (m_v3Max.x - m_v3Min.x) / 2.0f; // glm::distance(vector3(m_v3Min.x, 0.0f, 0.0f), vector3(m_v3Max.x, 0.0f, 0.0f)) / 2.0f;//HOT
	m_v3HalfWidth.y = (m_v3Max.y - m_v3Min.y) / 2.0f; //glm::distance(vector3(0.0f, m_v3Min.y, 0.0f), vector3(0.0f, m_v3Max.y, 0.0f)) / 2.0f;//HOT
	m_v3HalfWidth.z = (m_v3Max.z - m_v3Min.z) / 2.0f; //glm::distance(vector3(0.0f, 0.0f, m_v3Min.z), vector3(0.0f, 0.0f, m_v3Max.z)) / 2.0f;
}

//Accessors
vector3 BoundingBox::GetCenterLocal(void){ return m_v3Center; }
vector3 BoundingBox::GetCenterGlobal(void){ return ToGlobal(m_v3Center); }
vector3 BoundingBox::GetHalfWidth(void){ return m_v3HalfWidth; }

vector3 BoundingBox::ToGlobal(vector3 vec) {
	return vector3(matrix * vector4(vec, 1.0f));
}

//--- Non Standard Singleton Methods
bool BoundingBox::IsColliding(BoundingBox* const colliding)
{
	if (colliding->DoesUseSAT()) {
		return CheckSATCollision(colliding, ContactManifold());
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
void BoundingBox::CalculateAABBOverlap(BoundingBox* const colliding, ContactManifold& contact) {
	vector3 axis = vector3(0.0f, 0.0f, 0.0f);
	//Bounds of this collider

	float left = colliding->GetMin().x - GetMax().x; //minBX - maxX;
	float right = colliding->GetMax().x - GetMin().x; //maxBX - minX;
	float up = colliding->GetMin().y - GetMax().y; //minBY - maxY;
	float down = colliding->GetMax().y - GetMin().y; //maxBY - minY;
	float in = colliding->GetMin().z - GetMax().z; //minBZ - maxZ;
	float out = colliding->GetMax().z - GetMin().z; //maxBZ - minZ;

	if (glm::abs(left) < right)
	{
		axis.x = left;
	}
	else
	{
		axis.x = right;
	}
	if (glm::abs(up) < down)
	{
		axis.y = up;
	}
	else
	{
		axis.y = down;
	}
	if (glm::abs(in) < out)
	{
		axis.z = in;
	}
	else
	{
		axis.y = out;
	}
	
	/*if (glm::abs(axis.x) < glm::abs(axis.y))
	{
		if (glm::abs(axis.y) < glm::abs(axis.z))
		{
			axis.z = 0;
		}
		axis.y = 0;
	}
	else
	{
		if (glm::abs(axis.x) < glm::abs(axis.z))
		{
			axis.z = 0;
		}
		axis.x = 0;
	}*/
	for (int i = 0; i < 3; i++) {
		if (ignoreResolutionMask == i) {
			axis[i] = 0;
		}
	}
	contact.penetration = axis.length(); // 2.0f;
	contact.axis = glm::normalize(axis);

	vector3 translation = colliding->GetCenterGlobal() - GetCenterGlobal();
	for (int i = 0; i < 3; i++) {
		if (translation[i] < 0) {
			contact.axis[i] *= -1;
		}
	}
	/*if (ignoreResolutionMask == 2) {
		if (glm::dot(, contact.axis) < 0) {//if (translation[i] > 0) {
			contact.axis *= -1;
		}
	}
	else {
		if (glm::dot(colliding->GetCenterGlobal() - GetCenterGlobal(), contact.axis) > 0) {//if (translation[i] > 0) {
			contact.axis *= -1;
		}
	}*/

}


bool BoundingBox::CheckSATCollision(BoundingBox* const colliding, ContactManifold& contact) {
	contact.penetration = 1000000;

	std::vector<vector3> objectANormals = std::vector<vector3>();
	objectANormals.reserve(3);
	std::vector<vector3> objectBNormals = std::vector<vector3>();
	objectBNormals.reserve(3);
	GetLocalNormals(objectANormals);
	colliding->GetLocalNormals(objectBNormals);

	float ra, rb;
	matrix3 R, AbsR;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			R[i][j] = glm::dot(objectANormals[i], objectBNormals[j]);

		}
	}

	vector3 translation = colliding->GetCenterGlobal() - GetCenterGlobal();
	translation = vector3(glm::dot(translation, objectANormals[0]), glm::dot(translation, objectANormals[1]), glm::dot(translation, objectANormals[2]));

	


	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			AbsR[i][j] = std::abs(R[i][j]) + std::numeric_limits<float>::epsilon();
		}
	}

	float dist;
	float overlap;

	//std::cout << "\n\n\n";
	for (int i = 0; i < 3; i++) {
		ra = m_v3HalfWidth[i];
		rb = colliding->GetHalfWidth()[0] * AbsR[i][0] + colliding->GetHalfWidth()[1] * AbsR[i][1] + colliding->GetHalfWidth()[2] * AbsR[i][2];
		dist = translation[i];
		if (std::abs(dist) > ra + rb) return false;
		if (i != ignoreResolutionMask) {
			overlap = std::abs(dist - ra - rb);
			if (overlap < contact.penetration) {
				contact.penetration = overlap;
				contact.axis = glm::normalize(objectANormals[i]);
				if (glm::dot(translation, contact.axis) < 0) {//if (translation[i] > 0) {
					contact.axis *= -1;
				}
				//std::cout << translation[i] << "\n";
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		ra = m_v3HalfWidth[0] * AbsR[0][i] + m_v3HalfWidth[1] * AbsR[1][i] + m_v3HalfWidth[2] * AbsR[2][i];
		rb = colliding->GetHalfWidth()[i];
		dist = translation[0] * R[0][i] + translation[1] * R[1][i] + translation[2] * R[2][i];
		if (std::abs(dist) > ra + rb) return false;
		if (i != ignoreResolutionMask) {
			overlap = std::abs(dist - ra - rb);
			if (overlap < contact.penetration) {
				contact.penetration = overlap;
				contact.axis = glm::normalize(objectBNormals[i]);
				
				if (glm::dot(translation, contact.axis) < 0) {//if (translation[i] > 0) {
					contact.axis *= -1;
				}
				//std::cout << dist << "\n";
			}
		}
	}

	ra = m_v3HalfWidth[1] * AbsR[2][0] + m_v3HalfWidth[2] * AbsR[1][0];
	rb = colliding->GetHalfWidth()[1] * AbsR[0][2] + colliding->GetHalfWidth()[2] * AbsR[0][1];
	if (std::abs(translation[2] * R[1][0] - translation[1] * R[2][0]) > ra + rb) return false;

	ra = m_v3HalfWidth[1] * AbsR[2][1] + m_v3HalfWidth[2] * AbsR[1][1];
	rb = colliding->GetHalfWidth()[0] * AbsR[0][2] + colliding->GetHalfWidth()[2] * AbsR[0][0];
	if (std::abs(translation[2] * R[1][1] - translation[1] * R[2][1]) > ra + rb) return false;

	ra = m_v3HalfWidth[1] * AbsR[2][2] + m_v3HalfWidth[2] * AbsR[1][2];
	rb = colliding->GetHalfWidth()[0] * AbsR[0][1] + colliding->GetHalfWidth()[1] * AbsR[0][0];
	if (std::abs(translation[2] * R[1][2] - translation[1] * R[2][2]) > ra + rb) return false;

	ra = m_v3HalfWidth[0] * AbsR[2][0] + m_v3HalfWidth[2] * AbsR[0][0];
	rb = colliding->GetHalfWidth()[1] * AbsR[1][2] + colliding->GetHalfWidth()[2] * AbsR[1][1];
	if (std::abs(translation[0] * R[2][0] - translation[2] * R[0][0]) > ra + rb) return false;

	ra = m_v3HalfWidth[0] * AbsR[2][1] + m_v3HalfWidth[2] * AbsR[0][1];
	rb = colliding->GetHalfWidth()[0] * AbsR[1][2] + colliding->GetHalfWidth()[2] * AbsR[1][0];
	if (std::abs(translation[0] * R[2][1] - translation[2] * R[0][1]) > ra + rb) return false;

	ra = m_v3HalfWidth[0] * AbsR[2][2] + m_v3HalfWidth[2] * AbsR[0][2];
	rb = colliding->GetHalfWidth()[0] * AbsR[1][1] + colliding->GetHalfWidth()[1] * AbsR[1][0];
	if (std::abs(translation[0] * R[2][2] - translation[2] * R[0][2]) > ra + rb) return false;

	ra = m_v3HalfWidth[0] * AbsR[1][0] + m_v3HalfWidth[1] * AbsR[0][0];
	rb = colliding->GetHalfWidth()[1] * AbsR[2][2] + colliding->GetHalfWidth()[2] * AbsR[2][1];
	if (std::abs(translation[1] * R[0][0] - translation[0] * R[1][0]) > ra + rb) return false;

	ra = m_v3HalfWidth[0] * AbsR[1][1] + m_v3HalfWidth[1] * AbsR[0][1];
	rb = colliding->GetHalfWidth()[0] * AbsR[2][2] + colliding->GetHalfWidth()[2] * AbsR[2][0];
	if (std::abs(translation[1] * R[0][1] - translation[0] * R[1][1]) > ra + rb) return false;

	ra = m_v3HalfWidth[0] * AbsR[1][2] + m_v3HalfWidth[1] * AbsR[0][2];
	rb = colliding->GetHalfWidth()[0] * AbsR[2][1] + colliding->GetHalfWidth()[1] * AbsR[2][0];
	if (std::abs(translation[1] * R[0][2] - translation[0] * R[1][2]) > ra + rb) return false;

	if (contact.penetration == 1000000) {
		contact.penetration = 0;
	}

	return true;
}

bool BoundingBox::DoesUseSAT() {
	return false;
}

vector3 BoundingBox::GetMin() { return m_v3Min; }
vector3 BoundingBox::GetMax() { return m_v3Max; }

void BoundingBox::GetLocalNormals(std::vector<vector3>& normals) {
	matrix4 worldMatrix = GetGameObject()->GetWorldMatrix();
	normals.push_back(vector3(worldMatrix[0][0], worldMatrix[0][1], worldMatrix[0][2]));
	normals.push_back(vector3(worldMatrix[1][0], worldMatrix[1][1], worldMatrix[1][2]));
	normals.push_back(vector3(worldMatrix[2][0], worldMatrix[2][1], worldMatrix[2][2]));
}

void BoundingBox::SetIgnoreAxis(uint newAxis) {
	ignoreResolutionMask = newAxis;
}