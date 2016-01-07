#include "Shot.h"
#include <math.h>

Shot::Shot( float a, float b, float c ){
	x = a;
	y = b;
	z = c;
}


float ShotToTargetXY(float AtackX, float AtackZ, float DefenseX, float DefenseZ){
	float sbx = AtackX - DefenseX;
	float sbz = AtackZ - DefenseZ;
	float sb = sqrt( sbx * sbx + sbz * sbz);
	return sb;
}