/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/10
----------------------------------------------*/
#pragma once
#ifndef __BOUNDINGBOX_H_
#define __BOUNDINGBOX_H_

#include "RE\ReEng.h"

class SATBoundingBox;


//System Class
class BoundingBox
{
	matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate
	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the box Class
	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the box Class
	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the box Class
	vector3 m_v3HalfWidth = vector3(0.0f);//Will store half the size of all sides

	bool isVisible;
public:
	/*
	Method: BoundingBox
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	BoundingBox(std::vector<vector3> a_lVectorList);
	/*
	Method: BoundingBox
	Usage: Copy Constructor
	Arguments: class object to copy
	Output: class object instance
	*/
	BoundingBox(BoundingBox const& other);
	/*
	Method: operator=
	Usage: Copy Assignment Operator
	Arguments: class object to copy
	Output: ---
	*/
	BoundingBox& operator=(BoundingBox const& other);
	/*
	Method: ~BoundingBox
	Usage: Destructor
	Arguments: ---
	Output: ---
	*/
	~BoundingBox(void);

	/*
	Method: Swap
	Usage: Changes object contents for other object's
	Arguments:
	other -> object to swap content from
	Output: ---
	*/
	void Swap(BoundingBox& other);

	/*
	Method: SetToWorldMatrix
	Usage: Sets the Bounding Box into world coordinates
	Arguments:
	matrix4 a_m4ToWorld -> Model to World matrix
	Output: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld);

	/*
	Method: GetToWorldMatrix
	Usage: Gets the Bounding Box into world coordinates
	Arguments:---
	Output: matrix4 -> Model to World matrix
	*/
	matrix4 GetModelMatrix(void);

	/*
	Method: GetCenter
	Usage: Gets the Bounding Box's center in local coordinates
	Arguments: ---
	Output: vector3 -> Center's of the box in local coordinates
	*/
	vector3 GetCenterLocal(void);

	/*
	Method: GetCenterGlobal
	Usage: Gets the Bounding Box's center in global coordinates
	Arguments: ---
	Output: vector3 -> Center's of the box in global coordinates
	*/
	vector3 GetCenterGlobal(void);

	/*
	Method: GetHalfWidth
	Usage: Gets the Bounding Box sizes for all sides (divided in half)
	Arguments: ---
	Output: vector3 -> HalfWidth Vector
	*/
	vector3 GetHalfWidth(void);

	/*
	Method: IsColliding
	Usage: Asks if there is a collision with another Bounding Box Object
	Arguments:
	BoundingBox* const a_pOther -> Other object to check collision with
	Output: bool -> check of the collision
	*/
	virtual bool IsColliding(BoundingBox* const );

	void RealignBox(BoundingBox* const);

	vector3 GetMin();
	vector3 GetMax();

	void SetVisibility(bool);

	bool CheckSATCollision(BoundingBox* const);
	std::vector<vector3> GetLocalNormals();

private:
	/*
	Method: Release
	Usage: Deallocates member fields
	Arguments: ---
	Output: ---
	*/
	void Release(void);
	/*
	Method: Init
	Usage: Allocates member fields
	Arguments: ---
	Output: ---
	*/
	void Init(void);

	vector3 ToGlobal(vector3);

	void RecalculateBounds(std::vector<vector3>);

	bool CheckAABBCollision(BoundingBox* const);

	vector2 Project(vector3);

	bool IsOverlapping(vector2 a, vector2 b);

protected:
	virtual bool DoesUseSAT();
};

#endif //__BoundingBox_H__
