#pragma once
#ifndef __SATBOUNDINGBOX_H_
#define __SATBOUNDINGBOX_H_
#include "BoundingBox.h"

class SATBoundingBox : public BoundingBox
{
public:
	SATBoundingBox(std::vector<vector3>);
	~SATBoundingBox();
	SATBoundingBox(SATBoundingBox const&);
	SATBoundingBox& operator=(SATBoundingBox const&);

	bool IsColliding(BoundingBox* const);
protected:
	bool DoesUseSAT();
};

#endif //__SATBOUNDINGBOX_H_

