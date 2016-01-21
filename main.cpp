#include "HeaderInclude.h"

#define ENUM 60
#define BOSS_TIMER 3200
//関数の定義
void SetCamera(Character &c, Boss &b);
void Colision(P_Shot &s, Enemy &e, int damagesound);
void Colision(P_Shot &s, Boss &b);
void pColision(Character &c, EShot *es);
void ItemColision(Character &c, Item it[INUM], int powerupsound);
void Radar(Enemy e[ENUM], Character &c);
void ScoreDraw();


namespace{
	unsigned int timer = 2000; //ゲーム内での時間を表す
}

//ゲームの状態を表す変数
int gamestate = 0;
int score = 0;
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ), SetGraphMode( 800 , 600 , 32 ) ;
	int input, input_x, input_y;
	//ステージに関する事柄
	int StageGraph = MV1LoadModel("Graph/球体星図ｖ2.mqo");
	int ItemModel = MV1LoadModel("Graph/power.x");
	
	float StageZ = 0;
	float StageRX= 0;
	MV1SetScale(StageGraph, VGet(0.2f, 0.2f, 0.2f));
    SetCameraNearFar( 0.1f, 1000.0f ) ;

	Character *Delta = new Character(0, 10, -10, 0, 0, 0, MV1LoadModel( "AWB-03Vt_v100.pmx" ));//プレイヤーの生成
	Enemy *e = new Enemy[ENUM]; //敵の生成と各変数の代入
	Boss *boss = new Boss();
	int damagesound = LoadSoundMem("sound/damage7.mp3");
	ChangeVolumeSoundMem( 100, damagesound ) ;
	int powerupsound = LoadSoundMem("sound/powerup10.mp3");
	ChangeVolumeSoundMem( 70, powerupsound ) ;
	int music = LoadSoundMem("sound/shooting.mp3");
	ChangeVolumeSoundMem(200, music);
	int boss_music = LoadSoundMem("sound/game_maoudamashii_2_boss03.mp3");
	int gameover_music = LoadSoundMem("sound/loop_21.wav");
	int clear_music = LoadSoundMem("sound/loop_53.wav");
	//アイテムのオブジェクトの生成
	Item *it = new Item[INUM];
	
	//メインループ
    while(!ScreenFlip()&&!ProcessMessage()&&!ClearDrawScreen() && !KeyGet(KEY_INPUT_ESCAPE)){
		int input;
		KeyInput();
		if (KeyGet(KEY_INPUT_T)) gamestate = 0;
		switch(gamestate){
		case -2:
			Description();
			break;
		case -1: //ゲームのシューティング部分に入る前の初期化処理
			ChangeVolumeSoundMem(200, music);
			StopSoundMem(clear_music);
			StopSoundMem(music);
			StopSoundMem(gameover_music);
			PlaySoundMem(music, DX_PLAYTYPE_LOOP);
			gamestate = 1;
			Delta->Init(   0, 10,  20, 0, 0, 0, MV1LoadModel( "Graph/AWB-03Vt_v100.pmx" ));
			
			e[0].SetAll(  -10, 10, 120, 5,   0, 0, 1, 0);
			e[1].SetAll(    0, 10,  120, 5,  60, 0, 1, 0);
			e[2].SetAll(   10, 10,  120, 5, 120, 0, 1, 0);
			e[3].SetAll(   10, 10,  120, 5, 240, 0, 1, 0);
			e[4].SetAll(    0, 10,  120, 5, 300, 0, 1, 1);
			e[5].SetAll(  -10, 10,  120, 5, 360, 0, 1, 0);
			e[6].SetAll(    0, 20, 230, 3, 500, 1, 3, 0);
			e[7].SetAll(  -20, 20, 230, 3, 500, 1, 3, 0);
			e[8].SetAll(   20, 20, 230, 3, 500, 1, 3, 0);
			e[9].SetAll(    0,  0, 230, 3, 700, 1, 4, 1);
			e[10].SetAll( -20,  0, 230, 3, 700, 1, 4, 0);
			e[11].SetAll(  20,  0, 230, 3, 700, 1, 4, 0);
			e[12].SetAll( -20,  10, 150, 4, 900, 1, 5, 0);
			e[13].SetAll(  20,  10, 150, 4, 900, 1, 6, 0);
			e[14].SetAll( -10,  10, 180, 4, 1000, 1, 2, 0);
			e[15].SetAll(  10,  10, 150, 4, 1150, 1, 23, 0);
			e[16].SetAll(  -10,   5, 180, 3, 1300, 1, 7, 0);
			e[17].SetAll(   0,  10, 180, 3, 1360, 1, 7, 1);
			e[18].SetAll(   10,  15, 180, 4, 1420, 1, 7, 0);
			e[19].SetAll(  -10,  15, 180, 5, 1480, 1, 0, 0);
			e[20].SetAll(   10,  15, 180, 5, 1540, 1, 0, 0);
			e[21].SetAll(    0,  10, 120, 7, 1600, 0, 1, 1);
			e[22].SetAll(   10,  15, 150, 5, 1660, 0, 3, 0);
			e[23].SetAll(  -10,  15, 150, 5, 1720, 0, 3, 0);
			e[24].SetAll(  5,  15, 150, 1, 1780, 1, 1, 0);
			e[25].SetAll(  -5,  5, 150, 3, 1840, 1, 1, 0);
			e[26].SetAll(  -5,  10, 120, 4, 1960, -1, 1, 0);
			e[27].SetAll(  -2.5,  10, 120, 4, 1960, -1, 1, 0);
			e[28].SetAll(  0,  10, 120, 3, 1960, -1, 1, 0);
			e[29].SetAll(  2.5,  10, 120, 5, 1960, -1, 1, 0);
			e[30].SetAll(  5,  10, 120, 3, 1960, -1, 1, 0);
			e[31].SetAll(  0,  5, 120, 1, 2080, -1, 1, 0);
			e[32].SetAll(  0,  7.5, 120, 3, 2080, -1, 1, 0);
			e[33].SetAll(  0,  10, 120, 3, 2080, -1, 1, 0);
			e[34].SetAll(  0,  12.5, 120, 3, 2080, -1, 1, 0);
			e[35].SetAll(  0,  15, 120, 5, 2080, -1, 1, 0);
			e[36].SetAll(20, 20, 230, 2, 2200, 1, 3, 0);
			e[37].SetAll(20, 20, 230, 2, 2200, 1, 4, 0);
			e[38].SetAll(0, 10, 120, 2, 2250, 0, 1, 0);
			e[39].SetAll(5, 0, 120, 2, 2250, 0, 1, 0);
			e[40].SetAll(-5, 10, 120, 2, 2250,  0, 1, 0);
			e[41].SetAll(-20, 20, 230, 2, 2400, 1, 3, 0);
			e[42].SetAll(-20, 20, 230, 2, 2400, 1, 4, 0);
			e[43].SetAll(0, 0, 180, 3, 2500, 1, 4, 1);
			e[44].SetAll(-10, 10, 180, 4, 2600, 1, 2, 0);
			e[45].SetAll(10, 10, 180, 4, 2650, 1, 23, 0);
			boss->Init();

			for(int i = 0; i < INUM; i++){
				it[i].Init();
			}
			
			StageZ = 200;
			timer = 0;
			score = 0;
			break;
		case 0://メニュー
			StopSoundMem(clear_music);
			StopSoundMem(gameover_music);
			StopSoundMem(boss_music);
			StopSoundMem(music);
			Menu();
			
			break;
		case 1://ゲーム部分
			if(KeyGet(KEY_INPUT_R))gamestate = -1;
			if (KeyGet(KEY_INPUT_T))gamestate = 0;

			//カメラ
			SetCamera( *Delta , *boss);

			Delta->All();
			//敵の処理
			for(int i = 0; i < ENUM; i++){
				if (e[i].GetLife() == 0 && timer >= 10){
					score += e[i].GetScore();
					e[i].SetLife(-1);
				}
				if(e[i].GetLife() > 0 && timer > e[i].GetTimer() && Delta->GetZ() - 10 < e[i].GetZ() ){
					e[i].Draw();
					
					e[i].Move();
					Delta->Homing(e[i].GetX(), e[i].GetY(), e[i].GetZ());
					for(int l = 0; l < SNUM; l++){
					if(e[i].GetLife() > 0){
						Colision(Delta->shot[l], e[i], damagesound);
					}
					}
					if (e[i].GetZ() >= Delta->GetZ() + 5){
						e[i].Homing(Delta->GetX(), Delta->GetY(), Delta->GetZ());
					}
				}
				e[i].EShot();
				for(int j = 0; j < ESNUM; j++){
					if(e[i].es[j].z < -5){
						e[i].es[j].flag = 0;
					}
				}
			}
			if (timer >= BOSS_TIMER - 200){
				ChangeVolumeSoundMem(BOSS_TIMER - timer, music);
			}
			if (timer >= BOSS_TIMER){

				boss->Draw();
				boss->Move();
				boss->Shot(Delta->GetX(), Delta->GetY(), Delta->GetZ());
				boss->SetTarget(Delta->GetX(), Delta->GetY(), Delta->GetZ());
				boss->Colision(*Delta, damagesound);
				boss->LifeDraw();
				if (CheckSoundMem(music)){
					StopSoundMem(music);
					PlaySoundMem(boss_music, DX_PLAYTYPE_LOOP);
				}
			}

			//プレイヤーと敵弾の衝突判定
			for(int i = 0; i < ENUM; i++){
				pColision(*Delta, e[i].es);
			}

			//アイテム ゲームバランスが悪いので封印します
			/*for(int i = 0; i < ENUM; i++){
				if(e[i].GetItemflag() == 1 && e[i].GetLife() == 0 ){
					for(int l = 0; l < INUM; l++){
						if(it[l].GetFlag() == false){
							it[l].SetState(e[i].GetX(), e[i].GetY(), e[i].GetZ());
							e[i].SetItemflag(0);
							break;
						}
					}
				}
			}*/
			/*for(int i = 0; i < INUM; i ++){
				it[i].Draw();
				if(it[i].GetZ() < Delta->GetZ() - 5.0f){
					it[i].SetFlag( false );
				}
			}
*/


			//	ItemColision( *Delta, it, powerupsound );
			
			//ステージ関係の処理
			MV1DrawModel(StageGraph);
			StageRX += 0.001;
			timer ++;
			MV1SetPosition(StageGraph, VGet( 0, 0, StageZ));
			MV1SetRotationXYZ(StageGraph, VGet(StageRX, 0, 0));

			

			//Radar(e, *Delta);

			//ライフの描画
			Delta->LifeDraw();

			if(boss->GetY() <= -100 && boss->GetLife() <= 0){
				gamestate = 4;
			}
			ScoreDraw();
			break;
		case 2:
			StopSoundMem(music);
			StopSoundMem(boss_music);
			PlaySoundMem(gameover_music, DX_PLAYTYPE_LOOP);
			gamestate = 5;
			break;
		case 5:
			End();
			break;
		case 3:
			Clear();
			break;
		case 4:
			StopSoundMem(boss_music);
			PlaySoundMem(clear_music, DX_PLAYTYPE_LOOP);
			ScoreWrite(score + Delta->GetLife() * 2000);
			ScoreLoad();
			gamestate = 3;
			break;
		
		}
		
    }

    DxLib_End();
    return 0;
}  

void SetCamera(Character &c, Boss &b){
	if (b.GetFlag() & APPEAR && timer >= BOSS_TIMER){
		SetCameraPositionAndTarget_UpVecY(VGet(30, 0, 0), VGet(b.GetX(), b.GetY(), b.GetZ()));
	}
	else if (b.GetFlag() & APPROACH && timer >= BOSS_TIMER){
		SetCameraPositionAndTarget_UpVecY(VGet(0, 12, -15 + c.GetZ()), VGet(b.GetX(), b.GetY() + 5, b.GetZ()));
	}
	else if(c.GetLife() >= 0){
		SetCameraPositionAndTarget_UpVecY( VGet( 0, 12 , -15 + c.GetZ() ), VGet( c.GetRotateZ() / -7, 12.0f + c.GetRotateX() / 7, 30 ) ) ;
	}
	else{
		SetCameraPositionAndTarget_UpVecY(VGet(0, 12, -15 + c.GetZ()), VGet(c.GetX(), 12.0f , 30));
	}
}



void Colision( P_Shot &s, Enemy &e , int damagesound){
	float d;
	d = sqrt((s.x - e.GetX())*(s.x - e.GetX())) + sqrt((s.z - e.GetZ())*(s.z - e.GetZ()));
	d = sqrt(d * d + (s.y - e.GetY()) * (s.y - e.GetY()));
	if(d < 10){
		e.SetLife( e.GetLife() -1 );
		s.flag = 0;
		s.z = 0;
		PlaySoundMem( damagesound , DX_PLAYTYPE_BACK ) ;
		score += 10;
	}
}
void Colision(P_Shot &s, Boss &b, int damagesound){
	

}
void pColision(Character &c, EShot *es){
	
	for(int i = 0; i < ESNUM; i++){
		float d;
		d = sqrt((es[i].x - c.GetX())*( es[i].x - c.GetX())) + sqrt((c.GetZ()- es[i].z)*(c.GetZ() - es[i].z));
		d = sqrt(d * d + (c.GetY() - es[i].y) * (c.GetY() - es[i].y));
		if( d < 3.5){
			
			es[i].flag = 0;
			es[i].z = 100;
			if (!c.muteki){
				c.SetLife(c.GetLife() - 1);
			}
		}
	}
}

void ItemColision(Character &c, Item it[INUM], int powerupsound){
	for(int i = 0; i < INUM; i++){
		if(it[i].GetX() - 3.0f < c.GetX()  &&  c.GetX() < it[i].GetX() + 3.0f &&
			it[i].GetY() - 3.0f < c.GetY() && c.GetY() < it[i].GetY() + 3.0f &&
			it[i].GetZ() - 3.0f < c.GetZ() && c.GetZ() < it[i].GetZ() + 3.0f
			&& it[i].GetFlag() == true){
				c.SetPower(c.GetPower() + 1);
				it[i].SetFlag( false );
				PlaySoundMem( powerupsound , DX_PLAYTYPE_BACK ) ;
		}
	}
}

void Radar(Enemy e[ENUM], Character &c){
	DrawBox( 0 , 0 , 150 , 150 , GetColor(0,0,100) , TRUE) ; 
	for(int i = 0; i < ESNUM; i++){
		if(e[i].GetLife() > 0 && e[i].GetZ() > c.GetZ()){
			DrawCircle((e[i].GetX() * 1.8) + 75, (e[i].GetZ() * (-1))+110, 5, GetColor(255,255,0),TRUE );
		}
	}
}

void ScoreDraw(){
	DrawFormatString(600, 10, GetColor(230, 230, 230), "SCORE %d", score);
}