#ifndef __ENEMY__INCLUDE__
#define __ENEMY__INCLUDE__

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
	virtual void EShot();
	void Homing(float px, float py, float pz);

	float GetX();
	float GetY();
	float GetZ();
	
	int GetLife();
	int GetTimer();
	int GetDeathTimer();
	int GetItemflag();

	struct EShot es[ESNUM];

	virtual void Move();
	void Death();
protected:
	float x,y,z;
	float RotateX, RotateY, RotateZ;
	int DeathTimer;
	int life, graph, timer, shotpattern, movepattern, Itemflag;
};

enum BossAnimPettern{
	stand = 8,
	firebomb = 9,

};

class Boss : public Enemy{
public:
	Boss();
	virtual ~Boss(){};
	void Draw() override;
	void Move() override;
	void Animation();
	void SetAnimPattern(BossAnimPettern num);
	//int GetAnimPattern();
private:
	BossAnimPettern AnimPattern;
	int AttachIndex;
	float AnimTime;
	float TotalTime;
	float AnimSpeed;
	
};

#endif