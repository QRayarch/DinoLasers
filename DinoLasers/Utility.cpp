#include "Utility.h"


Utility::Utility()
{
}


Utility::~Utility()
{
}

std::vector<vector3> Utility::GetModelMinMax(String modelName) {
	//Count the points of the incoming list
	std::vector<vector3> vertices = MeshManagerSingleton::GetInstance()->GetVertexList(modelName);
	uint nVertexCount = vertices.size();

	std::vector<vector3> bounds;

	//If there are none just return, we have no information to create the BS from
	if (nVertexCount == 0)
		return bounds;

	//Max and min as the first vector of the list
	vector3 max, min;
	max = min = vertices[0];

	//Get the max and min out of the list
	for (uint nVertex = 1; nVertex < nVertexCount; nVertex++)
	{
		if (min.x > vertices[nVertex].x) //If min is larger than current
			min.x = vertices[nVertex].x;
		else if (max.x < vertices[nVertex].x)//if max is smaller than current
			max.x = vertices[nVertex].x;

		if (min.y > vertices[nVertex].y) //If min is larger than current
			min.y = vertices[nVertex].y;
		else if (max.y < vertices[nVertex].y)//if max is smaller than current
			max.y = vertices[nVertex].y;

		if (min.z > vertices[nVertex].z) //If min is larger than current
			min.z = vertices[nVertex].z;
		else if (max.z < vertices[nVertex].z)//if max is smaller than current
			max.z = vertices[nVertex].z;
	}


	bounds.push_back(min);
	bounds.push_back(max);
	return bounds;
}
