#include "HeaderInclude.h"

namespace{
	int damage_sound;
	int damaged_timer;
	bool damaged_flag;
}
Character::Character(float a, float b, float c, float X, float Y, float Z, int graph){
	x = a;
	y = b;
	z = c;
	RotateX = X;
	RotateY = Y;
	RotateZ = Z;
	life = 10;
	this->graph = graph;
	targetwindow = MV1LoadModel("target.mqo");
	MV1SetScale(targetwindow, VGet(0.025f, 0.025f, 0.025f));
	MV1SetScale(graph, VGet(0.015f, 0.015f, 0.015f));
	for(int i = 0; i < SNUM; i++){
		shot[i].flag = 0;
		shot[i].graph = MV1LoadModel("aaaa.mqo");
	}
	damage_sound = LoadSoundMem("sound/nc84550.mp3");
	ChangeVolumeSoundMem(100, damage_sound);
	damaged_timer = 0;
	damaged_flag = false;
}
void Character::Init(float a, float b, float c, float X, float Y, float Z, int graph){
	x = a;
	y = b;
	z = c;
	RotateX = X;
	RotateY = Y;
	RotateZ = Z;
	RotateZ2 = 0;
	life = 10;
	power = 0;
	this->graph = graph;
	DeathTimer = 180;
	targetwindow = MV1LoadModel("target.mqo");
	MV1SetScale(targetwindow, VGet(0.025f, 0.025f, 0.025f));
	MV1SetScale(graph, VGet(0.06f, 0.06f, 0.06f));
	for(int i = 0; i < SNUM; i++){
		shot[i].flag = 0;
		shot[i].graph = MV1LoadModel("shotp.pmx");
		shot[i].attach = MV1AttachAnim( shot[i].graph, 0, -1, FALSE ) ;
		shot[i].shottime = MV1GetAttachAnimTotalTime( shot[i].graph, shot[i].attach );
		shot[i].playtime = 0;
		MV1SetScale(shot[i].graph, VGet(0.3f, 0.3f, 0.8f));
	}

	//ブーストの初期化
	boost.graph = MV1LoadModel("boost.pmd");
	boost.attach = MV1AttachAnim(boost.graph, 1, -1, FALSE ) ;
	boost.totaltime= MV1GetAttachAnimTotalTime( boost.graph, boost.attach ) ;
	boost.playtime = 0;
	MV1SetScale(boost.graph, VGet(0.11f, 0.11f, 0.11f));
	
	boost2.graph = MV1LoadModel("boost.pmd");
	boost2.attach = MV1AttachAnim(boost2.graph, 2, -1, FALSE ) ;
	boost2.totaltime= MV1GetAttachAnimTotalTime( boost2.graph, boost2.attach ) ;
	boost2.playtime = 0;
	MV1SetScale(boost2.graph, VGet(0.11f, 0.11f, 0.11f));

	shotsound = LoadSoundMem( "sound/shoot1.mp3" );
	 ChangeVolumeSoundMem( 100, shotsound ) ;

}
void Character::Move(){
	if(KeyGet(KEY_INPUT_LEFT)) {
		x-=0.3;
		if(RotateZ < 30.0f){
			RotateZ += 1.0f;
		}
	}
	if(RotateZ > 0 && RotateZ <= 180.0f && KeyGet(KEY_INPUT_LEFT) == 0) RotateZ -= 0.5f;

	if(KeyGet(KEY_INPUT_RIGHT)) {
		x+=0.3;
		if(RotateZ > -30.0f){
			RotateZ -= 1.0f;
		}
	}
	if(RotateZ < 0 && RotateZ >= -180.0f && KeyGet(KEY_INPUT_RIGHT) == 0) RotateZ += 0.5f;

	if(KeyGet(KEY_INPUT_UP)) {
		y+=0.3;
		if(RotateX < 45.0f){
			RotateX += 1.0f;
		}
	}
	if(RotateX >0 && RotateX <= 180.0f && KeyGet(KEY_INPUT_UP) == 0 ) RotateX -= 0.5f;

	if(KeyGet(KEY_INPUT_DOWN)) {
		y-=0.3;
		if(RotateX > -45.0f){
			RotateX -= 1.0f;
		}
	}
	if(RotateX < 0 && RotateX >= -180.0f && KeyGet(KEY_INPUT_DOWN) == 0) RotateX += 0.5f;
	if(KeyGet(KEY_INPUT_Z)){
			RotateZ2 += 36;
	}
	if(KeyGet(KEY_INPUT_Z) == 0 && KeyGet(KEY_INPUT_X) == 0){
		RotateZ2 = 0;
	}
	if(KeyGet(KEY_INPUT_X)){
		if(RotateZ2 < 360){
			RotateZ2 -= 36;
		}
		muteki = 1;
	}
	else{
		muteki = 0;
	}
	if (KeyGet(KEY_INPUT_Z) || KeyGet(KEY_INPUT_X)){
		muteki = 1;
	}
	else{
		muteki = 0;
	}
	if(damaged_flag == true){
		damaged_timer++;
	}
	if (damaged_timer > 60){
		damaged_flag = false;
		damaged_timer = 0;

	}
}

void Character::Draw(){
	MV1DrawModel( graph );
	MV1SetPosition( graph, VGet(x, y + 1, z ) ) ;
	MV1SetPosition( targetwindow, VGet( x +  -10 * tan(RotateZ * PI/   180), (y + 10 * tan(RotateX * PI/ 180)), z + 10));
	MV1SetRotationXYZ( graph, VGet( -RotateX * DX_PI_F / 180.0f, (RotateY +180) * DX_PI_F / 180.0f, (RotateZ+ RotateZ2 + 180) * DX_PI_F / 180.0f ));
	MV1SetOpacityRate(graph, !(damaged_timer % 2));
	if(life >= 0){
		//MV1DrawModel( targetwindow );
		MV1DrawModel( boost.graph );
		MV1DrawModel( boost2.graph );
	}
	//ブースト関連
	boost.playtime += 1.0f;
	if( boost.playtime >= boost.totaltime ) boost.playtime = 0.0f;
	MV1SetAttachAnimTime( boost.graph, boost.attach, boost.playtime );
	MV1SetPosition( boost.graph, VGet(x , y, z ));
	MV1SetRotationXYZ( boost.graph, VGet( -RotateX * DX_PI_F / 180.0f, (RotateY +180) * DX_PI_F / 180.0f, (RotateZ+ RotateZ2 + 180) * DX_PI_F / 180.0f ));

	boost2.playtime += 1.0f;
	if( boost2.playtime >= boost2.totaltime ) boost2.playtime = 0.0f;
	MV1SetAttachAnimTime( boost2.graph, boost2.attach, boost2.playtime );
	MV1SetPosition( boost2.graph, VGet( x, y, z ));
	MV1SetRotationXYZ( boost2.graph, VGet( -RotateX * DX_PI_F / 180.0f, (RotateY +180) * DX_PI_F / 180.0f, (RotateZ+ RotateZ2 + 180) * DX_PI_F / 180.0f ));
}

void Character::LifeDraw(){
	int color = GetColor(0, 128, 0);
	//L
	DrawBox(10, 600 - 30, 13, 600- 10, color, TRUE);
	DrawBox(10, 600 - 13, 20, 600- 10, color, TRUE);

	//I
	DrawBox(28, 600 - 30, 31, 600 - 10, color, TRUE);

	//F
	DrawBox(39, 600 - 30, 42, 600- 10, color, TRUE);
	DrawBox(39, 600 - 30, 49, 600- 27, color, TRUE);
	DrawBox(39, 600 - 21, 49, 600-18, color, TRUE);

	//E
	DrawBox(57, 600 - 30, 60, 600- 10, color, TRUE);
	DrawBox(57, 600 - 30, 66, 600- 27, color, TRUE);
	DrawBox(57, 600 - 21, 66, 600-18, color, TRUE);
	DrawBox(57, 600 - 13, 66, 600- 10, color, TRUE);

	//GRAPH
	for(int i = 0; i < life; i++){
		DrawCircle(85 + i * 25, 600 - 20, 10, GetColor(255, 180, 0), TRUE);
	}
}

void Character::Shot(){
	if(KeyGet(KEY_INPUT_U)) power = 2;
	if(KeyGet(KEY_INPUT_SPACE) % 5 == 1 && muteki == 0){
		PlaySoundMem( shotsound , DX_PLAYTYPE_BACK ) ;

		for(int i = 0; i < SNUM; i++){
			if(shot[i].flag == 0){
				shot[i].flag = 1;
				shot[i].x = x;
				shot[i].y = y;
				shot[i].z = z;
				shot[i].angleX = RotateX;
				shot[i].angleY = RotateY;
				shot[i].angleZ = RotateZ;
				shot[i].playtime =0.0f;
				float sbx =  1 * tan((RotateZ * PI/ 180));
				float sb =  ((sbx * sbx) + 1 * 1);
				float sby = sb * tan((RotateX * PI/ 180));
				shot[i].rx = sbx / sb * 10.0f;
				shot[i].rz = 1 / sb * 10.0f;
				shot[i].ry = sby / sqrt(sb * sb + sby * sby) * 8.0f;
				MV1SetRotationXYZ( shot[i].graph, VGet(( shot[i].angleX / 1.5)* DX_PI_F / 180.0f, ((shot[i].angleZ  + 180 ) * -1) * DX_PI_F / 180.0f, 0 * DX_PI_F / 180.0f ));
				break;
				
			}
			
		}

	}
	if(KeyGet(KEY_INPUT_SPACE) % 5 == 1 && power == 1 ){
		PlaySoundMem( shotsound , DX_PLAYTYPE_BACK ) ;
		for(int i = 0; i < SNUM; i++){
			if(shot[i].flag == 0){
				shot[i].flag = 1;
				shot[i].x = x - 2;
				shot[i].y = y;
				shot[i].z = z;
				shot[i + 1].flag = 1;
				shot[i + 1].x = x + 2;
				shot[i + 1].y = y;
				shot[i + 1].z = z;
				shot[i].angleX = RotateX;
				shot[i].angleY = RotateY;
				shot[i].angleZ = RotateZ;
				shot[i].playtime =0.0f;
				shot[i + 1].angleX = RotateX;
				shot[i + 1].angleY = RotateY;
				shot[i + 1].angleZ = RotateZ;
				shot[i + 1].playtime =0.0f;
				float sbx =  1 * tan((RotateZ * PI/ 180));
				float sb =  ((sbx * sbx) + 1 * 1);
				float sby = sb * tan((RotateX * PI/ 180));
				shot[i].rx = sbx / sb * 10.0f;
				shot[i].rz = 1 / sb * 10.0f;
				shot[i].ry = sby / sqrt(sb * sb + sby * sby) * 8.0f;
				MV1SetRotationXYZ( shot[i].graph, VGet(( shot[i].angleX / 1.5)* DX_PI_F / 180.0f, ((shot[i].angleZ  + 180 ) * -1) * DX_PI_F / 180.0f, 0 * DX_PI_F / 180.0f ));
				shot[i + 1].rx = sbx / sb * 10.0f;
				shot[i + 1].rz = 1 / sb * 10.0f;
				shot[i + 1].ry = sby / sqrt(sb * sb + sby * sby) * 8.0f;
				MV1SetRotationXYZ( shot[i + 1].graph, VGet(( shot[i + 1].angleX / 1.5)* DX_PI_F / 180.0f, ((shot[i + 1].angleZ  + 180 ) * -1) * DX_PI_F / 180.0f, 0 * DX_PI_F / 180.0f ));
				break;
				
			}
			
		}

	}
	if(KeyGet(KEY_INPUT_SPACE) % 5 == 1 && power >= 2 ){
		PlaySoundMem( shotsound , DX_PLAYTYPE_BACK ) ;
		for(int i = 0; i < SNUM; i++){
			if(shot[i].flag == 0){
				shot[i].flag = 1;
				shot[i].x = x;
				shot[i].y = y;
				shot[i].z = z;
				shot[i].angleX = RotateX;
				shot[i].angleY = RotateY;
				shot[i].angleZ = RotateZ;
				shot[i].playtime =0.0f;

				shot[i + 1].flag = 1;
				shot[i + 1].x = x + 4;
				shot[i + 1].y = y;
				shot[i + 1].z = z;
				shot[i + 1].angleX = RotateX;
				shot[i + 1].angleY = RotateY;
				shot[i + 1].angleZ = RotateZ;
				shot[i + 1].playtime =0.0f;

				shot[i + 2].flag = 1;
				shot[i + 2].x = x - 4;
				shot[i + 2].y = y;
				shot[i + 2].z = z;
				shot[i + 2].angleX = RotateX;
				shot[i + 2].angleY = RotateY;
				shot[i + 2].angleZ = RotateZ;
				shot[i + 2].playtime =0.0f;

				float sbx =  1 * tan((RotateZ * PI/ 180));
				float sb =  ((sbx * sbx) + 1 * 1);
				float sby = sb * tan((RotateX * PI/ 180));
				shot[i].rx = sbx / sb * 10.0f;
				shot[i].rz = 1 / sb * 10.0f;
				shot[i].ry = sby / sqrt(sb * sb + sby * sby) * 8.0f;
				MV1SetRotationXYZ( shot[i].graph, VGet(( shot[i].angleX / 1.5)* DX_PI_F / 180.0f, ((shot[i].angleZ  + 180 ) * -1) * DX_PI_F / 180.0f, 0 * DX_PI_F / 180.0f ));

				shot[i + 1].rx = sbx / sb * 10.0f;
				shot[i + 1].rz = 1 / sb * 10.0f;
				shot[i + 1].ry = sby / sqrt(sb * sb + sby * sby) * 8.0f;
				MV1SetRotationXYZ( shot[i + 1].graph, VGet(( shot[i + 1].angleX / 1.5)* DX_PI_F / 180.0f, ((shot[i + 1].angleZ  + 180 ) * -1) * DX_PI_F / 180.0f, 0 * DX_PI_F / 180.0f ));

				shot[i + 2].rx = sbx / sb * 10.0f;
				shot[i + 2].rz = 1 / sb * 10.0f;
				shot[i + 2].ry = sby / sqrt(sb * sb + sby * sby) * 8.0f;
				MV1SetRotationXYZ( shot[i + 2].graph, VGet(( shot[i + 2].angleX / 1.5)* DX_PI_F / 180.0f, ((shot[i + 2].angleZ  + 180 ) * -1) * DX_PI_F / 180.0f, 0 * DX_PI_F / 180.0f ));
				break;
				
			}
			
		}

	}

	for(int i = 0; i < SNUM; i++){
		if(shot[i].flag == 1){
			shot[i].z += shot[i].rz;
			shot[i].x -= shot[i].rx;
			shot[i].y += shot[i].ry;
			MV1SetPosition( shot[i].graph, VGet(shot[i].x, shot[i].y, shot[i].z) );
			MV1DrawModel( shot[i].graph );
			
			MV1SetAttachAnimTime( shot[i].graph, shot[i].attach, shot[i].playtime ) ;
			
			shot[i].playtime += 2.0f;
			
			if(shot[i].playtime >= shot[i].shottime ) shot[i].playtime = 0;
			
			if(shot[i].z > z + 300.0f){
				shot[i].flag = 0;
				shot[i].playtime = 0.0f;
			}
		}
		if(shot[i].flag == 2){
			shot[i].x -= shot[i].rx;
			shot[i].y -= shot[i].ry;
			shot[i].z -= shot[i].rz;
			
			MV1SetScale(shot[i].graph, VGet(0.05f, 0.05f, 0.005f));
			MV1SetPosition( shot[i].graph, VGet(shot[i].x, shot[i].y, shot[i].z) );
			MV1DrawModel( shot[i].graph );
			
			if(shot[i].z > 100){
				shot[i].flag = 0;
			}
		}
	}

}

void Character::ChargeShot( float ex, float ey, float ez ){

}

float Character::GetRotateZ(){
	return RotateZ;
}
float Character::GetRotateX(){
	return RotateX;
}

void Character::Homing( float x, float y, float z ){
	if(KeyGet(KEY_INPUT_N) % 15 == 1 ){
		for(int i = 0; i < SNUM; i++){
			if(shot[i].flag == 0){
				shot[i].flag = 2;
				shot[i].x = this->x;
				shot[i].y = this->y;
				shot[i].z = this->z;
				shot[i].speed = 4.0f;

				float sbx = this->x - x;
				float sby = this->y - y;
				float sbz = this->z - z;
				float sb = sqrt( sbx * sbx + sbz * sbz ) ;
				shot[i].rx = sbx / sb * shot[i].speed;
				shot[i].rz = sbz / sb * shot[i].speed;
				shot[i].ry =sby / sqrt(sb * sb + y * y) * shot[i].speed;
				break;
				
			}
			
		}

	}	
}
void Character::Death(){
	if(KeyGet(KEY_INPUT_L)) life = 0;
	float x = 0.3f, y = 0.3f, z =0.3f;
	if(life <= 0 ){
		DeathTimer --;
		RotateY --;
		RotateX --;
		MV1SetScale(graph, VGet( x, y , z));
		if(DeathTimer == 0) gamestate = 2;
	}
	if( life == 0){
		graph = MV1LoadModel("Graph/消せる爆発/爆発消x1.pmd");
		life --;
	}
}

void Character::SetPower( int power ){
	this->power = power;
}

void Character::All(){
	Draw();
	if( life > 0 ){
		Move();
		Shot();
	}
	Death();
	
}

int Character::GetLife(){ return life; }
int Character::GetPower(){ return power; }
void Character::SetLife( int life){ 
	if(damaged_flag == false && muteki == 0)
	{
		PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
		this->life = life;
		damaged_flag = true;
		
	}
	
	
}

float Character::GetX(){return x;}
float Character::GetY(){return y;}
float Character::GetZ(){return z;}

