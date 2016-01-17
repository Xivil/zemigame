#ifndef _CHARACTER_INCLUDE__
#define _CHARACTER_INCLUDE__

#define SNUM 60//弾の最大数

struct P_Shot{
	int flag;
	float x, y, z;
	float rx, ry, rz;
	float angleX, angleY, angleZ;
	int graph;
	float speed;
	int attach;
	float shottime, playtime;
};
struct anim{
	int graph;
	int attach;
	float totaltime;
	float playtime;
	float x, y, z;
};

class Character{
public:
	Character(float a, float b, float c, float RotateX, float RotateY, float RotateZ, int graph);
	~Character();
	void Move();
	void Draw();
	void LifeDraw();
	void Shot();
	void ChargeShot(float ex, float ey, float ez);
	void Init(float a, float b, float c, float RotateX, float RotateY, float RotateZ, int graph);
	void Homing(float x, float y, float z);
	void Death();
	void SetPower(int power);
	float GetX();
	float GetY();
	float GetZ();
	float GetRotateZ(), GetRotateX();
	int GetLife();
	int GetPower();
	void SetLife( int life );

	void All();
	struct P_Shot shot[SNUM];
	struct anim boost;
	struct anim boost2;

	int muteki;
private:
	float x, y, z;

	float RotateX;
	float RotateY;
	float RotateZ;
	float RotateZ2;
	int graph, targetwindow;
	int life;
	int power;
	int DeathTimer;
	
	//チャージ用の変数
	float cx, cy, cz;
	int cflag, ctimer;

	//サウンド用の変数
	int shotsound;
};
#endif