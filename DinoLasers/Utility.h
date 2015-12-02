#pragma once
#include "RE\ReEng.h"

class Utility
{
public:
	Utility();
	~Utility();

	static std::vector<vector3> GetModelMinMax(String);

	template <typename T> static int Sign(T num){
		if (num != 0) return num / std::abs(num);
		else return 0;
	}
};

