#include "HeaderInclude.h"

Item::Item(){
	graph = MV1LoadModel("Graph/power.x");
	flag = false;
	x = 0;
	y = 0;
	z = 0;
	rx = 0;
}
void Item::Init(){
	flag = false;
}
void Item::SetState( float x, float y, float z ){
	flag = true;
	this->x = x;
	this->y = y;
	this->z = z;
	rx = 0;
}
void Item::Draw(){
	if(flag == true){
		MV1DrawModel( graph );
		MV1SetPosition( graph, VGet(x, y, z));
		MV1SetRotationXYZ( graph, VGet(0, rx, 0));
		z -= 0.7f;
		rx -= 0.1f;
	}
}

bool Item::GetFlag(){ return flag; }
void Item::SetFlag( bool flag ){ this->flag = flag; }

float Item::GetX(){ return x; }
float Item::GetY(){ return y; }
float Item::GetZ(){ return z; }


	
