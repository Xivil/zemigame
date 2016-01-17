#pragma once
#include "Character.h"
#include "DxLib.h"
#define ESNUM 20

struct EShot{
	float x;
	float y;
	float z;
	float rx;
	float ry;
	float rz;
	int graph;
	int flag;
};

typedef struct Animation{
	int AttachIndex;
	float AnimTime;
	float TotalTime;
	float AnimSpeed;
}Anim;

class Enemy{
public:
	Enemy();
	Enemy(float x, float y, float z, int life, int timer);
	virtual ~Enemy();
	virtual void Draw();
	void SetX( float x );
	void SetY( float y );
	void SetZ( float z );
	void SetLife( int life );
	void SetTimer( int timer );
	void SetItemflag(int flag);
	void SetAll(float x, float y, float z, int life, int timer, int shotpattern, int movepattern, int Itemflag);
	void EShot();
	void Homing(float px, float py, float pz);

	float GetX();
	float GetY();
	float GetZ();
	
	int GetLife();
	int GetTimer();
	int GetDeathTimer();
	int GetItemflag();
	int GetScore();
	struct EShot es[ESNUM];

	virtual void Move();
	void Death();
protected:
	float x,y,z;
	float RotateX, RotateY, RotateZ;
	int DeathTimer;
	int life, graph, timer, shotpattern, movepattern, Itemflag, score;
	float ShotSpeed;
};

//------------------------------------------
//	ここからボスクラスの定義
//-----------------------------------------
enum BossAnimPettern{
	stand = 8,
	firebomb = 9,
	flight = 10,
	appear = 11,
	dead = 12,
};
#define BSNUM 128

#define ATTACK 1
#define HORIZONTAL 2
#define VERTICAL 4
#define CROSS 8
#define CONTINUITY 16
#define APPROACH 32
#define APPEAR 64
#define STANBY 128
#define HIT 256
#define LEAVE 512
#define DEAD 1024
class Boss : public Enemy{
public:
	Boss();
	virtual ~Boss(){};
	void Init();
	void Draw() override;
	void Move() override;
	void Shot(float x, float y, float z);
	void VerticalShot();
	void ShotDraw();
	void Animation();
	void SetAnimPattern(BossAnimPettern num);
	void SetTarget(float x, float y, float z);
	//int GetAnimPattern();
	int GetGraph();
	int Colision(Character &c, int damagesound);
	void SetFlag(unsigned int f);
	unsigned int GetFlag();
	void HitAnim();
	void LifeDraw();
private:
	BossAnimPettern AnimPattern;
	int AttachIndex;
	float AnimTime;
	float TotalTime;
	float AnimSpeed;
	
	struct EShot bs[BSNUM];
	unsigned int flag;
	float target_z, target_y, target_x;
	MV1_COLL_RESULT_POLY_DIM HitPolyDim;
	int HitEffectGraph[16];
	Anim HitEffect[16];
	VECTOR HitEffectPosition[16];
	int HitEffectFlag[16];
};