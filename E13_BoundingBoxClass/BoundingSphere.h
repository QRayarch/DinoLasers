#ifndef __BSPHERE_H_
#define __BSPHERE_H_

#include "RE\ReEngAppClass.h"
#include "Component.h"
#include "GameObject.h"

using namespace ReEng;

class BoundingSphere : public Component
{
private:
	vector3 m_v3Center;
	float m_fRadius;

public:
	BoundingSphere(std::vector<vector3>listOfVertex);
	bool IsColliding(BoundingSphere* pOther);
	vector3 GetCenterGlobal(void);
	float GetRadius();
	void SetRadius(float);
};

#endif //__BSPHERE_H_