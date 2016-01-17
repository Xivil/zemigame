#include "HeaderInclude.h"

//namespace{
//	int HitEffectGraph[16];
//	float AttachIndex[16];
//	float AnimTime[16];
//	float position[16][3];
//}
namespace {
	int count = 0;
	int boss_attack_sound;
}
Enemy::Enemy(){

	life = -1;
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
	ShotSpeed = 1.5f;
}

Enemy::~Enemy(){}

void Enemy::Draw(){

	MV1DrawModel( graph );
	MV1SetPosition( graph, VGet(x, y, z) ) ;
	timer ++;
	if(z < 0){
		life = -1;
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
	score = life * 100;
	DeathTimer = 120;
}

void Enemy::EShot(){

	
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
	if (timer % 120 == 1){
		for (int i = 0; i < ESNUM; i++){
			if (es[i].flag == 0 && shotpattern == 0){
				es[i].flag = 1;
				es[i].x = x;
				es[i].y = y;
				es[i].z = z;
				break;
			}
		}
	}
		if(timer % 45 == 1){
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
int Enemy::GetScore(){ return score; }

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
	boss_attack_sound = LoadSoundMem("sound/bomb.mp3");
	ChangeVolumeSoundMem(125, boss_attack_sound);
	score = 20000;
}

#define LIFE 200

void Boss::Init(){
	x = 0;
	y = -200;
	z = 130;
	life = LIFE;
	SetAnimPattern(appear);
	AnimSpeed = 0.8;
	AnimTime = 0.0f;
	for (int i = 0; i < BSNUM; i++){
		bs[i].flag = 0;
		bs[i].graph = 0;
	}
	timer = 0;
	flag = 0 + APPEAR;

	ShotSpeed = 1.5f;
	for (int i = 0; i < 16; i++){
		HitEffectGraph[i] = MV1LoadModel("Graph/消せる爆発/リング３連.pmd");
		HitEffectPosition[i] = VGet(0, 0, 0);
		HitEffect[i].AnimTime = 0.0f;
		HitEffect[i].TotalTime = 5.0f;
		HitEffectFlag[i] = 0;
	}
}
void Boss::Draw(){
	Animation();
	Enemy::Draw();
}


//	ボスのアニメーション全般
void Boss::Move(){
	static float fall = 0;
	if (flag & APPEAR){
		
		timer--;
		
		if (y >= -19){
			flag &= ~APPEAR;
			SetAnimPattern(appear);
			flag |= STANBY;
		}
		else{
			AnimTime -= AnimSpeed;
			y++;
		}
	}
	else if (flag & STANBY){
		timer--;
		if (AnimTime >= TotalTime - 1){
			flag &= ~STANBY;
			flag |= HORIZONTAL;
			SetAnimPattern(stand);
		}
	}
	else if(life >= 1){
		y = y + sin(PI * 2 / 120 * timer);
	}
	else if(life == 0 && !(flag & DEAD)){
		flag |= DEAD;
		SetAnimPattern(dead);
		fall = 0;
	}
	if (flag & DEAD){
		y -= fall;
		fall += 0.8;
	}
	if (!(flag & CROSS) && life <= LIFE / 2){
		AnimSpeed = 1.0f;
		ShotSpeed = 2.0f;
		flag |= CROSS;
	}
	MV1RefreshCollInfo(graph, -1);
	if (flag & ATTACK)
	{
		
	}
}

void Boss::Shot(float px, float py, float pz){
	if (timer  == 119){
		SetAnimPattern(firebomb);
		flag |= HORIZONTAL;
	}
	if (count == 6){
		flag &= ~HORIZONTAL + ~VERTICAL;
		flag |= APPROACH;
	}
	
	if (AnimPattern == firebomb && AnimTime >= 20 && !(flag & ATTACK) && flag & HORIZONTAL){
		float len = 3;
			for (int i = 0; i < BSNUM; i++){
				if (bs[i].flag == 0){
					if (bs[i].graph == 0){
						bs[i].graph = MV1LoadModel("aaaa.mqo");
						MV1SetScale(bs[i].graph, VGet(0.01f, 0.01f, 0.01f));
					}
					bs[i].flag = 1;
					bs[i].x = x;
					bs[i].y = y + 40;
					bs[i].z = z;

					float sbx = x - target_x;
					float sby = y - target_y + 40;
					float sbz = z - target_z;
					float sb = sqrt(sbx * sbx + sbz * sbz);
					bs[i].rx = sbx / sb * ShotSpeed;
					bs[i].rz = sbz / sb * ShotSpeed;
					bs[i].ry = sby / sqrt(sb * sb + py * py) * ShotSpeed;

					break;
				}
			}
			for (int i = 0; i < BSNUM; i++){
				if (bs[i].flag == 0){
					if (bs[i].graph == 0){
						bs[i].graph = MV1LoadModel("aaaa.mqo");
						MV1SetScale(bs[i].graph, VGet(0.01f, 0.01f, 0.01f));
					}
					bs[i].flag = 1;
					bs[i].x = x;
					bs[i].y = y + 40;
					bs[i].z = z;

					float sbx = x - px - len;
					float sby = y - py + 40;
					float sbz = z - pz;
					float sb = sqrt(sbx * sbx + sbz * sbz);
					bs[i].rx = sbx / sb * ShotSpeed;
					bs[i].rz = sbz / sb * ShotSpeed;
					bs[i].ry = sby / sqrt(sb * sb + py * py) * ShotSpeed;

					break;
				}
			}
			for (int i = 0; i < BSNUM; i++){
				if (bs[i].flag == 0){
					if (bs[i].graph == 0){
						bs[i].graph = MV1LoadModel("aaaa.mqo");
						MV1SetScale(bs[i].graph, VGet(0.01f, 0.01f, 0.01f));
					}
					bs[i].flag = 1;
					bs[i].x = x;
					bs[i].y = y + 40;
					bs[i].z = z;

					float sbx = x - px + len;
					float sby = y - py + 40;
					float sbz = z - pz;
					float sb = sqrt(sbx * sbx + sbz * sbz);
					bs[i].rx = sbx / sb * ShotSpeed;
					bs[i].rz = sbz / sb * ShotSpeed;
					bs[i].ry = sby / sqrt(sb * sb + py * py) * ShotSpeed;

					break;
				}
			}
			for (int i = 0; i < BSNUM; i++){
				if (bs[i].flag == 0){
					if (bs[i].graph == 0){
						bs[i].graph = MV1LoadModel("aaaa.mqo");
						MV1SetScale(bs[i].graph, VGet(0.01f, 0.01f, 0.01f));
					}
					bs[i].flag = 1;
					bs[i].x = x;
					bs[i].y = y + 40;
					bs[i].z = z;

					float sbx = x - px + len * 2;
					float sby = y - py + 40;
					float sbz = z - pz;
					float sb = sqrt(sbx * sbx + sbz * sbz);
					bs[i].rx = sbx / sb * ShotSpeed;
					bs[i].rz = sbz / sb * ShotSpeed;
					bs[i].ry = sby / sqrt(sb * sb + py * py) * ShotSpeed;

					break;
				}
			}
			for (int i = 0; i < BSNUM; i++){
				if (bs[i].flag == 0){
					if (bs[i].graph == 0){
						bs[i].graph = MV1LoadModel("aaaa.mqo");
						MV1SetScale(bs[i].graph, VGet(0.01f, 0.01f, 0.01f));
					}
					bs[i].flag = 1;
					bs[i].x = x;
					bs[i].y = y + 40;
					bs[i].z = z;

					float sbx = x - px + len * -2;
					float sby = y - py + 40;
					float sbz = z - pz;
					float sb = sqrt(sbx * sbx + sbz * sbz);
					bs[i].rx = sbx / sb * ShotSpeed;
					bs[i].rz = sbz / sb * ShotSpeed;
					bs[i].ry = sby / sqrt(sb * sb + py * py) * ShotSpeed;

					break;
				}
			}
			flag |= ATTACK + VERTICAL;
			flag &= ~HORIZONTAL;
			count++;
			PlaySoundMem(boss_attack_sound, DX_PLAYTYPE_BACK);
	}

	if (AnimPattern == firebomb && AnimTime >= 20 && !(flag & ATTACK) && flag & VERTICAL){
		float len = 3;
		for (int i = 0; i < BSNUM; i++){
			if (bs[i].flag == 0){
				if (bs[i].graph == 0){
					bs[i].graph = MV1LoadModel("aaaa.mqo");
					MV1SetScale(bs[i].graph, VGet(0.01f, 0.01f, 0.01f));
				}
				bs[i].flag = 1;
				bs[i].x = x;
				bs[i].y = y + 40;
				bs[i].z = z;

				float sbx = x - target_x;
				float sby = y - target_y + 40;
				float sbz = z - target_z;
				float sb = sqrt(sbx * sbx + sbz * sbz);
				bs[i].rx = sbx / sb * ShotSpeed;
				bs[i].rz = sbz / sb * ShotSpeed;
				bs[i].ry = sby / sqrt(sb * sb + py * py) * ShotSpeed;

				break;
			}
		}
		for (int i = 0; i < BSNUM; i++){
			if (bs[i].flag == 0){
				if (bs[i].graph == 0){
					bs[i].graph = MV1LoadModel("aaaa.mqo");
					MV1SetScale(bs[i].graph, VGet(0.01f, 0.01f, 0.01f));
				}
				bs[i].flag = 1;
				bs[i].x = x;
				bs[i].y = y + 40;
				bs[i].z = z;

				float sbx = x - px;
				float sby = y - py + 40 - len;
				float sbz = z - pz;
				float sb = sqrt(sbx * sbx + sbz * sbz);
				bs[i].rx = sbx / sb * ShotSpeed;
				bs[i].rz = sbz / sb * ShotSpeed;
				bs[i].ry = sby / sqrt(sb * sb + py * py) * ShotSpeed;

				break;
			}
		}
		for (int i = 0; i < BSNUM; i++){
			if (bs[i].flag == 0){
				if (bs[i].graph == 0){
					bs[i].graph = MV1LoadModel("aaaa.mqo");
					MV1SetScale(bs[i].graph, VGet(0.01f, 0.01f, 0.01f));
				}
				bs[i].flag = 1;
				bs[i].x = x;
				bs[i].y = y + 40;
				bs[i].z = z;

				float sbx = x - px;
				float sby = y - py + 40 + len;
				float sbz = z - pz;
				float sb = sqrt(sbx * sbx + sbz * sbz);
				bs[i].rx = sbx / sb * ShotSpeed;
				bs[i].rz = sbz / sb * ShotSpeed;
				bs[i].ry = sby / sqrt(sb * sb + py * py) * ShotSpeed;

				break;
			}
		}
		for (int i = 0; i < BSNUM; i++){
			if (bs[i].flag == 0){
				if (bs[i].graph == 0){
					bs[i].graph = MV1LoadModel("aaaa.mqo");
					MV1SetScale(bs[i].graph, VGet(0.01f, 0.01f, 0.01f));
				}
				bs[i].flag = 1;
				bs[i].x = x;
				bs[i].y = y + 40;
				bs[i].z = z;

				float sbx = x - px ;
				float sby = y - py + 40 + len * 2;
				float sbz = z - pz;
				float sb = sqrt(sbx * sbx + sbz * sbz);
				bs[i].rx = sbx / sb * ShotSpeed;
				bs[i].rz = sbz / sb * ShotSpeed;
				bs[i].ry = sby / sqrt(sb * sb + py * py) * ShotSpeed;

				break;
			}
		}
		for (int i = 0; i < BSNUM; i++){
			if (bs[i].flag == 0){
				if (bs[i].graph == 0){
					bs[i].graph = MV1LoadModel("aaaa.mqo");
					MV1SetScale(bs[i].graph, VGet(0.01f, 0.01f, 0.01f));
				}
				bs[i].flag = 1;
				bs[i].x = x;
				bs[i].y = y + 40;
				bs[i].z = z;

				float sbx = x - px ;
				float sby = y - py + 40 + len * -2;
				float sbz = z - pz;
				float sb = sqrt(sbx * sbx + sbz * sbz);
				bs[i].rx = sbx / sb * ShotSpeed;
				bs[i].rz = sbz / sb * ShotSpeed;
				bs[i].ry = sby / sqrt(sb * sb + py * py) * ShotSpeed;

				break;
			}
		}
		flag |= ATTACK;
		flag &= ~VERTICAL;
		flag |= HORIZONTAL;
		count++;
		PlaySoundMem(boss_attack_sound, DX_PLAYTYPE_BACK);
	}

	if (AnimPattern == firebomb && AnimTime >= 20 && !(flag & ATTACK) && flag & CROSS){
		float len = 3;
		for (int i = 0; i < BSNUM; i++){
			if (bs[i].flag == 0){
				if (bs[i].graph == 0){
					bs[i].graph = MV1LoadModel("aaaa.mqo");
					MV1SetScale(bs[i].graph, VGet(0.01f, 0.01f, 0.01f));
				}
				bs[i].flag = 1;
				bs[i].x = x;
				bs[i].y = y + 40;
				bs[i].z = z;

				float sbx = x - target_x;
				float sby = y - target_y + 40;
				float sbz = z - target_z;
				float sb = sqrt(sbx * sbx + sbz * sbz);
				bs[i].rx = sbx / sb * ShotSpeed;
				bs[i].rz = sbz / sb * ShotSpeed;
				bs[i].ry = sby / sqrt(sb * sb + py * py) * ShotSpeed;

				break;
			}
		}
		for (int i = 0; i < BSNUM; i++){
			if (bs[i].flag == 0){
				if (bs[i].graph == 0){
					bs[i].graph = MV1LoadModel("aaaa.mqo");
					MV1SetScale(bs[i].graph, VGet(0.01f, 0.01f, 0.01f));
				}
				bs[i].flag = 1;
				bs[i].x = x;
				bs[i].y = y + 40;
				bs[i].z = z;

				float sbx = x - px;
				float sby = y - py + 40 - len;
				float sbz = z - pz;
				float sb = sqrt(sbx * sbx + sbz * sbz);
				bs[i].rx = sbx / sb * ShotSpeed;
				bs[i].rz = sbz / sb * ShotSpeed;
				bs[i].ry = sby / sqrt(sb * sb + py * py) * ShotSpeed;

				break;
			}
		}
		for (int i = 0; i < BSNUM; i++){
			if (bs[i].flag == 0){
				if (bs[i].graph == 0){
					bs[i].graph = MV1LoadModel("aaaa.mqo");
					MV1SetScale(bs[i].graph, VGet(0.01f, 0.01f, 0.01f));
				}
				bs[i].flag = 1;
				bs[i].x = x;
				bs[i].y = y + 40;
				bs[i].z = z;

				float sbx = x - px;
				float sby = y - py + 40 + len;
				float sbz = z - pz;
				float sb = sqrt(sbx * sbx + sbz * sbz);
				bs[i].rx = sbx / sb * ShotSpeed;
				bs[i].rz = sbz / sb * ShotSpeed;
				bs[i].ry = sby / sqrt(sb * sb + py * py) * ShotSpeed;

				break;
			}
		}
		for (int i = 0; i < BSNUM; i++){
			if (bs[i].flag == 0){
				if (bs[i].graph == 0){
					bs[i].graph = MV1LoadModel("aaaa.mqo");
					MV1SetScale(bs[i].graph, VGet(0.01f, 0.01f, 0.01f));
				}
				bs[i].flag = 1;
				bs[i].x = x;
				bs[i].y = y + 40;
				bs[i].z = z;

				float sbx = x - px;
				float sby = y - py + 40 + len * 2;
				float sbz = z - pz;
				float sb = sqrt(sbx * sbx + sbz * sbz);
				bs[i].rx = sbx / sb * ShotSpeed;
				bs[i].rz = sbz / sb * ShotSpeed;
				bs[i].ry = sby / sqrt(sb * sb + py * py) * ShotSpeed;

				break;
			}
		}
		for (int i = 0; i < BSNUM; i++){
			if (bs[i].flag == 0){
				if (bs[i].graph == 0){
					bs[i].graph = MV1LoadModel("aaaa.mqo");
					MV1SetScale(bs[i].graph, VGet(0.01f, 0.01f, 0.01f));
				}
				bs[i].flag = 1;
				bs[i].x = x;
				bs[i].y = y + 40;
				bs[i].z = z;

				float sbx = x - px;
				float sby = y - py + 40 + len * -2;
				float sbz = z - pz;
				float sb = sqrt(sbx * sbx + sbz * sbz);
				bs[i].rx = sbx / sb * ShotSpeed;
				bs[i].rz = sbz / sb * ShotSpeed;
				bs[i].ry = sby / sqrt(sb * sb + py * py) * ShotSpeed;

				break;
			}
		}
		for (int i = 0; i < BSNUM; i++){
			if (bs[i].flag == 0){
				if (bs[i].graph == 0){
					bs[i].graph = MV1LoadModel("aaaa.mqo");
					MV1SetScale(bs[i].graph, VGet(0.01f, 0.01f, 0.01f));
				}
				bs[i].flag = 1;
				bs[i].x = x;
				bs[i].y = y + 40;
				bs[i].z = z;

				float sbx = x - px - len;
				float sby = y - py + 40;
				float sbz = z - pz;
				float sb = sqrt(sbx * sbx + sbz * sbz);
				bs[i].rx = sbx / sb * ShotSpeed;
				bs[i].rz = sbz / sb * ShotSpeed;
				bs[i].ry = sby / sqrt(sb * sb + py * py) * ShotSpeed;

				break;
			}
		}
		for (int i = 0; i < BSNUM; i++){
			if (bs[i].flag == 0){
				if (bs[i].graph == 0){
					bs[i].graph = MV1LoadModel("aaaa.mqo");
					MV1SetScale(bs[i].graph, VGet(0.01f, 0.01f, 0.01f));
				}
				bs[i].flag = 1;
				bs[i].x = x;
				bs[i].y = y + 40;
				bs[i].z = z;

				float sbx = x - px + len;
				float sby = y - py + 40;
				float sbz = z - pz;
				float sb = sqrt(sbx * sbx + sbz * sbz);
				bs[i].rx = sbx / sb * ShotSpeed;
				bs[i].rz = sbz / sb * ShotSpeed;
				bs[i].ry = sby / sqrt(sb * sb + py * py) * ShotSpeed;

				break;
			}
		}
		for (int i = 0; i < BSNUM; i++){
			if (bs[i].flag == 0){
				if (bs[i].graph == 0){
					bs[i].graph = MV1LoadModel("aaaa.mqo");
					MV1SetScale(bs[i].graph, VGet(0.01f, 0.01f, 0.01f));
				}
				bs[i].flag = 1;
				bs[i].x = x;
				bs[i].y = y + 40;
				bs[i].z = z;

				float sbx = x - px + len * 2;
				float sby = y - py + 40;
				float sbz = z - pz;
				float sb = sqrt(sbx * sbx + sbz * sbz);
				bs[i].rx = sbx / sb * ShotSpeed;
				bs[i].rz = sbz / sb * ShotSpeed;
				bs[i].ry = sby / sqrt(sb * sb + py * py) * ShotSpeed;

				break;
			}
		}
		for (int i = 0; i < BSNUM; i++){
			if (bs[i].flag == 0){
				if (bs[i].graph == 0){
					bs[i].graph = MV1LoadModel("aaaa.mqo");
					MV1SetScale(bs[i].graph, VGet(0.01f, 0.01f, 0.01f));
				}
				bs[i].flag = 1;
				bs[i].x = x;
				bs[i].y = y + 40;
				bs[i].z = z;

				float sbx = x - px + len * -2;
				float sby = y - py + 40;
				float sbz = z - pz;
				float sb = sqrt(sbx * sbx + sbz * sbz);
				bs[i].rx = sbx / sb * ShotSpeed;
				bs[i].rz = sbz / sb * ShotSpeed;
				bs[i].ry = sby / sqrt(sb * sb + py * py) * ShotSpeed;

				break;
			}
		}
		flag |= ATTACK;
		count++;
		PlaySoundMem(boss_attack_sound, DX_PLAYTYPE_BACK);
	}

	if (flag & APPROACH){

		if (AnimPattern != flight && !(flag & CONTINUITY)){
			SetAnimPattern(flight);
			flag &= ~HORIZONTAL + ~VERTICAL + ~CROSS;
		}
		if (!(flag & CONTINUITY)){
			z -= 2;
		}
		if (z <= 80 && AnimPattern == flight){
			flag |= CONTINUITY;
			SetAnimPattern(firebomb);
		}
		if (AnimPattern == firebomb && AnimTime >= 20 && (int(AnimTime) % 5 == 0) && flag & CONTINUITY){
			float len = 3;
			for (int i = 0; i < BSNUM; i++){
				if (bs[i].flag == 0){
					if (bs[i].graph == 0){
						bs[i].graph = MV1LoadModel("aaaa.mqo");
						MV1SetScale(bs[i].graph, VGet(0.01f, 0.01f, 0.01f));
					}
					bs[i].flag = 1;
					bs[i].x = x;
					bs[i].y = y + 40;
					bs[i].z = z;

					float sbx = x - target_x;
					float sby = y - target_y + 40;
					float sbz = z - target_z;
					float sb = sqrt(sbx * sbx + sbz * sbz);
					bs[i].rx = sbx / sb * ShotSpeed;
					bs[i].rz = sbz / sb * ShotSpeed;
					bs[i].ry = sby / sqrt(sb * sb + py * py) * ShotSpeed;

					break;
				}
			}
			flag |= ATTACK;
			count += 100;
			PlaySoundMem(boss_attack_sound, DX_PLAYTYPE_BACK);
		}
	}
	if (count >= 2100){
		count = 0;
		flag |= LEAVE;
		flag &= ~APPROACH;
	}
	if (flag & LEAVE){
		z += 1;
		if (z >= 130){
			flag &= ~LEAVE;
			flag &= ~CONTINUITY;

			if (life <= LIFE / 2)
			{
				flag |= CROSS;
			}
			else{
				flag |= HORIZONTAL;
			}
			count = 0;
		}
	}
	if (AnimPattern == firebomb && AnimTime == 0) flag &= ~ATTACK;

	for (int i = 0; i < BSNUM; i++){
		if (bs[i].flag)
		{
			bs[i].x -= bs[i].rx;
			bs[i].y -= bs[i].ry;
			bs[i].z -= bs[i].rz;
			MV1SetPosition(bs[i].graph, VGet(bs[i].x, bs[i].y, bs[i].z));
			MV1DrawModel(bs[i].graph);
			if (bs[i].z < -10){
				bs[i].flag = 0;
			}
		}
	}	
	
}
void Boss::ShotDraw(){

}
void Boss::Animation(){
	AnimTime += AnimSpeed;
	if (AnimTime >= TotalTime){
		AnimTime = 0.0f;
	}
	MV1SetAttachAnimTime(graph, AttachIndex, AnimTime);
	HitAnim();
}

void Boss::SetAnimPattern(BossAnimPettern num){
	AnimPattern = num;
	
	MV1DetachAnim(graph, AttachIndex);
	
	AttachIndex = MV1AttachAnim(graph, AnimPattern, -1, FALSE);
	AnimTime = 0;
	//	MMDで作成したアニメーションと再生時間のフレームに誤差が生じてしまった上に
	//	直せないので手動で入力
	switch(AnimPattern){
	case stand:
		TotalTime = 45.0f;
		break;
	default:
		TotalTime = MV1GetAnimTotalTime(graph, AttachIndex);
		break;
	}

}

void Boss::SetTarget(float x, float y, float z){
	target_x = x;
	target_y = y;
	target_z = z;
}

int Boss::GetGraph(){
	return graph;
}
int Boss::Colision(Character &c, int damagesound){
	for (int i = 0; i < SNUM; i++){
		if (c.shot[i].flag){
			HitPolyDim = MV1CollCheck_Sphere(graph, -1, VGet(c.shot[i].x, c.shot[i].y, c.shot[i].z), 2.0f);
			if (HitPolyDim.HitNum >= 1){
				life --;
				c.shot[i].flag = 0;
				for (int i = 0; i < 16; i++){
					if (HitEffectFlag[i] == 0){
						HitEffectPosition[i] = HitPolyDim.Dim->HitPosition;
						HitEffectFlag[i] = 1;
					}
				}
				flag |= HIT;
				PlaySoundMem(damagesound, DX_PLAYTYPE_BACK);
			}
		}
	}
	for (int i = 0; i < BSNUM; i++){
		if (bs[i].flag){
			float d;
			d = sqrt((bs[i].x - c.GetX())*(bs[i].x - c.GetX())) + sqrt((c.GetZ() - bs[i].z)*(c.GetZ() - bs[i].z));
			d = sqrt(d * d + (c.GetY() - bs[i].y) * (c.GetY() - bs[i].y));
			if (d < 4){
				c.SetLife(c.GetLife() - 1);
				bs[i].flag = 0;
				bs[i].z = 100;
			}
		}
	}
	return 1;
}
unsigned int Boss::GetFlag(){
	return flag;
}


void Boss::HitAnim(){
	for (int i = 0; i < 16; i++){
		if (HitEffectFlag[i] == 1){
			MV1DrawModel(HitEffectGraph[i]);
			MV1SetPosition(HitEffectGraph[i], HitEffectPosition[i]);
			MV1SetScale(HitEffectGraph[i], VGet(3, 3, 3));
			HitEffect[i].AnimTime++;
			if (HitEffect[i].AnimTime >= HitEffect[i].TotalTime){
				HitEffectFlag[i] = 0;
				HitEffect[i].AnimTime = 0.0f;
			}
			
		}
	}
}

void Boss::LifeDraw(){
	DrawBox(20, 20, 20 + life * 2, 50, GetColor(0, 255, 0), TRUE);
}