#include "HeaderInclude.h"

Enemy::Enemy(){

	life = 0;
	graph = MV1LoadModel("Graph/Tブースター.pmx");
	MV1SetScale( graph, VGet(0.5f, 0.5f, 0.5f));
}
Enemy::Enemy(float x, float y, float z, int life, int timer){
	this->x = x;
	this->y = y;
	this->z = z;
	this->life = life;
	this->timer = timer;
	graph = MV1LoadModel("R-13A.pmd");
	MV1SetScale( graph, VGet(0.025f, 0.025f, 0.025f));
}

Enemy::~Enemy(){}

void Enemy::Draw(){

	MV1DrawModel( graph );
	MV1SetPosition( graph, VGet(x, y, z) ) ;
	timer ++;
	if(z < -20){
		life = 0;
	}
}

void Enemy::SetX( float x ){
	this->x = x;
}

void Enemy::SetY( float y ){
	this->y = y;
}

void Enemy::SetZ( float z ){
	this->z = z;
}
void Enemy::SetLife( int life){
	this->life = life;
}

void Enemy::SetTimer( int timer){
	this->timer = timer;
}
void Enemy::SetItemflag(int flag){
	this->Itemflag = flag;
}
void Enemy::SetAll( float x, float y, float z, int life, int timer, int shotpattern, int movepattern , int Itemflag){
	SetX(x);
	SetY(y);
	SetZ(z);
	SetLife(life);
	SetTimer(timer);
	this->Itemflag = Itemflag; 
	this->shotpattern = shotpattern;
	this->movepattern = movepattern;
	for(int i = 0; i < ESNUM; i++){
		es[i].graph = MV1LoadModel("aaaa.mqo");
		es[i].flag = 0;
		MV1SetScale(es[i].graph, VGet(0.01f, 0.01f, 0.01f));

	}
	DeathTimer = 120;
}

void Enemy::EShot(){

	if(timer % 120 == 1){
		for(int i = 0; i < ESNUM; i++){
			if(es[i].flag == 0 && shotpattern == 0){
				es[i].flag = 1;
				es[i].x = x;
				es[i].y = y;
				es[i].z = z;
				break;
			}
		}
	}
	for(int i = 0; i < ESNUM; i++){
		if(es[i].flag  == 1){
			es[i].z -= 1.0f;
			MV1SetPosition( es[i].graph, VGet(es[i].x, es[i].y, es[i].z) );
			MV1DrawModel( es[i].graph );
				if(es[i].z < -10){
					es[i].flag = 0;
			}
		
		}
		if(es[i].flag == 2 ){
			es[i].x -= es[i].rx;
			es[i].y -= es[i].ry;
			es[i].z -= es[i].rz;
			MV1SetPosition( es[i].graph, VGet(es[i].x, es[i].y, es[i].z) );
			MV1DrawModel( es[i].graph );
				if(es[i].z < -10){
					es[i].flag = 0;
			}
		}
	}
	
}
void Enemy::Homing(float px, float py, float pz){
		if(timer % 60 == 1){
			for(int i = 0; i < ESNUM; i++){
			if(es[i].flag == 0 && shotpattern == 1){
				es[i].flag = 2;
				es[i].x = x;
				es[i].y = y;
				es[i].z = z;

				float sbx = x - px;
				float sby = y - py;
				float sbz = z - pz;
				float sb = sqrt( sbx * sbx + sbz * sbz ) ;
				es[i].rx = sbx / sb * 1.5f;
				es[i].rz = sbz / sb * 1.5f;
				es[i].ry = sby / sqrt(sb * sb + py * py) * 1.5f;
				break;
				
			}
			}
		}
}

float Enemy::GetX(){ return x ;}
float Enemy::GetY(){ return y ;}
float Enemy::GetZ(){ return z ;}
int Enemy::GetLife(){ return life; }
int Enemy::GetTimer(){ return timer; }
int Enemy::GetItemflag(){ return Itemflag; }

void Enemy::Move(){ 
	z -= 0.5f;
	if(movepattern == 0){
		x = x - sin(PI/2/60*timer) * 0.5f;
		y = y - sin(PI/2/30*timer) * 0.5f;
		
	}
	if(movepattern == 1){

	}
	if(movepattern == 2){
		z += 0.5;
		if(timer % 60 == 0){
			x += 30.0f;
			z -= 15.0f;
		}
		if(timer % 60 == 30){
			 x -= 30.0f;
			 z -= 15.0f;
		}
		
	}
	if(movepattern == 23){
		z += 0.5;
		if(timer % 60 == 0){
			x -= 30.0f;
			z -= 15.0f;
		}
		if(timer % 60 == 30){
			 x += 30.0f;
			 z -= 15.0f;
		}
		
	}
	if(movepattern == 3){
		z -= 1.0f;
		y = y - sin(PI/2/60*timer) * 0.5f;
	}
	if(movepattern == 4){
		z -= 1.0f;
		y = y + sin(PI/2/60*timer) * 0.5f;
	}
	if(movepattern == 5 ){
		x += 0.3;
		z -= 0.4;
	}
	if(movepattern == 6 ){
		x -= 0.3;
		z -= 0.4;
	}
	if(movepattern == 7){
		z -= 1.0f;
		x = x - sin(PI/2/60*timer) * 0.5f;
	}

}

void Enemy::Death(){
	float x = 0.3f, y = 0.3f, z =0.3f;
	if(life <= 0 ){
		DeathTimer --;
		RotateY --;
		RotateX --;
		MV1SetScale(graph, VGet( x, y , z));
	}
	if( life == 0){
		graph = MV1LoadModel("爆発消x1.pmd");
		life --;
	}
}

Boss::Boss(){
	
	graph = MV1LoadModel("Graph/Active Frame/Active Frame.pmx");
	if (!graph){
		DxLib_End();
	}
	SetAnimPattern(stand);
	AnimSpeed = 0.8;
	AnimTime = 0.0f;
}

void Boss::Draw(){
	Animation();
	Enemy::Draw();
}

void Boss::Move(){
	
}

void Boss::Animation(){
	AnimTime += AnimSpeed;
	if (AnimTime >= TotalTime){
		AnimTime = 0.0f;
	}
	MV1SetAttachAnimTime(graph, AttachIndex, AnimTime);
	DrawFormatString(0, 200, GetColor(255, 255, 255), "%f", TotalTime);
}

void Boss::SetAnimPattern(BossAnimPettern num){
	AnimPattern = num;
	AttachIndex = MV1AttachAnim(graph, AnimPattern, -1, FALSE);

	//	MMDで作成したアニメーションと再生時間のフレームに誤差が生じてしまった上に
	//	直せないので手動で入力
	switch(AnimPattern){
	case stand:
	case firebomb:
		TotalTime = 45.0f;
		break;
	default:
		TotalTime = MV1GetAnimTotalTime(graph, AttachIndex);
		break;
	}

}
