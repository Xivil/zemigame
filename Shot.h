#ifndef __SHOT_INCLUDE_
#define __SHOT_INCLUDE_

class Shot{
public:
	Shot();
	Shot(float a,float  b, float c);

	float x;
	float y;
	float z;

};

float ShotToTargetXY(float AtackX, float AtackZ, float DefenseX, float DefenseZ);
#endif