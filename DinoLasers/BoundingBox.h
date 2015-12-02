/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/10
----------------------------------------------*/
#pragma once
#ifndef __BOUNDINGBOX_H_
#define __BOUNDINGBOX_H_

#include "RE\ReEng.h"
#include "Updateable.h"
#include "GameObject.h"
#include "ContactManifold.h"

class SATBoundingBox;


//System Class
class BoundingBox : public Updateable
{
	matrix4 matrix;
	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the box Class
	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the box Class
	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the box Class
	vector3 m_v3HalfWidth = vector3(0.0f);//Will store half the size of all sides
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

	void Update(float);
	void RealignBox(BoundingBox* const);

	vector3 GetMin();
	vector3 GetMax();

	bool CheckSATCollision(BoundingBox* const, ContactManifold&);
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

	bool IsOverlapping(vector2, vector2);

	float GetOverlap(vector2, vector2);

protected:
	virtual bool DoesUseSAT();
};

#endif //__BoundingBox_H__
