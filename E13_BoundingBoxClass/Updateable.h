#pragma once
class Updateable
{
public:
	Updateable();
	~Updateable();

	virtual void Update(float) = 0;
};

