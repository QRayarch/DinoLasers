#ifndef __BSPHERE_H_
#define __BSPHERE_H_

#include "RE\ReEngAppClass.h"

using namespace ReEng;

class BoundingSphere 
{
private:
	matrix4 m_m4ToWorld = IDENTITY_M4;
	vector3 m_v3Center;
	float m_fRadius;

public:
	BoundingSphere(std::vector<vector3>listOfVertex);
	bool IsColliding(BoundingSphere* pOther);
	void SetModelMatrix(matrix4 a_m4ToWorld);
	vector3 GetCenterGlobal(void);
	float GetRadius();
	void SetRadius(float);
};

#endif //__BSPHERE_H_