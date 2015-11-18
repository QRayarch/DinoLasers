#include "Transform.h"

void Transform::Init() {
	position = vector3();
	orientation = quaternion();
	scale = vector3(1, 1, 1);
}

void Transform::Release(void)
{
}

void Transform::Swap(Transform& other)
{
	std::swap(position, other.position);
	std::swap(orientation, other.orientation);
	std::swap(scale, other.scale);
}

Transform::Transform()
{
	Init();
}

Transform::Transform(vector3 pos) {
	Init();
	position = pos;
}

Transform::Transform(vector3 pos, quaternion ort, vector3 scl) {
	Init();
	position = pos;
	orientation = ort;
	scale = scl;
}


Transform::Transform(Transform const& other) {
	position = other.position;
	orientation = other.orientation;
	scale = other.scale;
}

Transform::~Transform()
{

}

Transform& Transform::operator=(Transform const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		Transform temp(other);
		Swap(temp);
	}
	return *this;
}

matrix4 Transform::GetMatrix() {
	return glm::translate(position) * glm::mat4_cast(orientation) * glm::scale(scale);
}


void Transform::SetPosition(vector3 newPos) { position = newPos; }
vector3 Transform::GetPosition() { return position; }
void Transform::SetOrentation(quaternion newOrt) { orientation = newOrt; }
quaternion Transform::GetOrientation() { return orientation; }
void Transform::SetScale(vector3 newScl) { scale = newScl; }
vector3 Transform::GetScale() { return scale; }
void Transform::SetPositionOrientation(vector3 newPos, quaternion newOrt) { SetPosition(newPos); SetOrentation(newOrt); }
void Transform::SetAll(vector3 newPos, quaternion newOrt, vector3 newScl) { SetPosition(newPos); SetOrentation(newOrt); SetScale(newScl); }
vector3 Transform::GetForward() {
	return vector3(glm::mat4_cast(orientation)[2][0], glm::mat4_cast(orientation)[2][1], glm::mat4_cast(orientation)[2][2]);
}
vector3 Transform::GetRight(){
	return vector3(glm::mat4_cast(orientation)[0][0], glm::mat4_cast(orientation)[0][1], glm::mat4_cast(orientation)[0][2]);
}
vector3 Transform::GetUp(){
	return vector3(glm::mat4_cast(orientation)[1][0], glm::mat4_cast(orientation)[1][1], glm::mat4_cast(orientation)[1][2]);
}