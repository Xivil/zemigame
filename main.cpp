#include "HeaderInclude.h"

#define ENUM 40
//関数の定義
void SetCamera(Character &c);
void Colision(P_Shot &s, Enemy &e, int damagesound);
void pColision(Character &c, EShot *es);
void ItemColision(Character &c, Item it[INUM], int powerupsound);
void Radar(Enemy e[ENUM], Character &c);

//ゲームの状態を表す変数
int gamestate = 0;
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ), SetGraphMode( 800 , 600 , 32 ) ;
	//ステージに関する事柄
	int StageGraph = MV1LoadModel("Graph/球体星図ｖ2.mqo");
	int ItemModel = MV1LoadModel("Graph/power.x");
	
	float StageZ = 0;
	float StageRX= 0;
	MV1SetScale(StageGraph, VGet(0.2f, 0.2f, 0.2f));
    SetCameraNearFar( 0.1f, 1000.0f ) ;
	unsigned int timer = 0; //ゲーム内での時間を表す

	Character *Delta = new Character(0, 10, -10, 0, 0, 0, MV1LoadModel( "AWB-03Vt_v100.pmx" ));//プレイヤーの生成
	Enemy *e = new Enemy[ENUM]; //敵の生成と各変数の代入
	Boss *boss = new Boss();
	int damagesound = LoadSoundMem("sound/damage7.mp3");
	ChangeVolumeSoundMem( 140, damagesound ) ;
	int powerupsound = LoadSoundMem("sound/powerup10.mp3");
	ChangeVolumeSoundMem( 140, powerupsound ) ;
		
	//アイテムのオブジェクトの生成
	Item *it = new Item[INUM];
			
	//メインループ
    while(!ScreenFlip()&&!ProcessMessage()&&!ClearDrawScreen() && !KeyGet(KEY_INPUT_ESCAPE)){
		KeyInput();
		switch(gamestate){
		case -1: //ゲームのシューティング部分に入る前の初期化処理
			gamestate = 1;
			Delta->Init(   0, 10,  -10, 0, 0, 0, MV1LoadModel( "Graph/AWB-03Vt_v100.pmx" ));
			
			e[0].SetAll(  -10, 10, 90, 5,   0, 0, 1, 0);
			e[1].SetAll(    0, 10,  90, 5,  60, 0, 1, 0);
			e[2].SetAll(   10, 10,  90, 5, 120, 0, 1, 0);
			e[3].SetAll(   10, 10,  90, 5, 240, 0, 1, 0);
			e[4].SetAll(    0, 10,  90, 5, 300, 0, 1, 1);
			e[5].SetAll(  -10, 10,  90, 5, 360, 0, 1, 0);
			e[6].SetAll(    0, 20, 200, 5, 500, 1, 3, 0);
			e[7].SetAll(  -20, 20, 200, 5, 500, 1, 3, 0);
			e[8].SetAll(   20, 20, 200, 5, 500, 1, 3, 0);
			e[9].SetAll(    0,  0, 200, 5, 700, 1, 4, 1);
			e[10].SetAll( -20,  0, 200, 5, 700, 1, 4, 0);
			e[11].SetAll(  20,  0, 200, 5, 700, 1, 4, 0);
			e[12].SetAll( -20,  10, 120, 5, 900, 1, 5, 0);
			e[13].SetAll(  20,  10, 120, 5, 900, 1, 6, 0);
			e[14].SetAll( -10,  10, 150, 5, 1000, 1, 2, 0);
			e[15].SetAll(  10,  10, 120, 5, 1150, 1, 23, 0);
			e[16].SetAll(  -10,   5, 150, 5, 1300, 1, 7, 0);
			e[17].SetAll(   0,  10, 150, 5, 1360, 1, 7, 1);
			e[18].SetAll(   10,  15, 150, 5, 1420, 1, 7, 0);
			e[19].SetAll(  -10,  15, 150, 5, 1480, 1, 0, 0);
			e[20].SetAll(   10,  15, 150, 5, 1540, 1, 0, 0);
			e[21].SetAll(    0,  10, 90, 5, 1600, 0, 1, 1);
			e[22].SetAll(   10,  15, 120, 5, 1660, 0, 3, 0);
			e[23].SetAll(  -10,  15, 120, 5, 1720, 0, 3, 0);
			e[24].SetAll(  5,  15, 120, 5, 1780, 1, 1, 0);
			e[25].SetAll(  -5,  5, 120, 5, 1840, 1, 1, 0);
			e[26].SetAll(  -5,  10, 90, 12, 1960, -1, 1, 0);
			e[27].SetAll(  -2.5,  10, 90, 12, 1960, -1, 1, 0);
			e[28].SetAll(  0,  10, 90, 12, 1960, -1, 1, 0);
			e[29].SetAll(  2.5,  10, 90, 12, 1960, -1, 1, 0);
			e[30].SetAll(  5,  10, 90, 12, 1960, -1, 1, 0);
			e[31].SetAll(  0,  5, 90, 12, 2080, -1, 1, 0);
			e[32].SetAll(  0,  7.5, 90, 12, 2080, -1, 1, 0);
			e[33].SetAll(  0,  10, 90, 12, 2080, -1, 1, 0);
			e[34].SetAll(  0,  12.5, 90, 12, 2080, -1, 1, 0);
			e[35].SetAll(  0,  15, 90, 12, 2080, -1, 1, 0);

			boss->SetAll(0, 10, 100, 500, 0, 0, 0, 0);

			for(int i = 0; i < INUM; i++){
				it[i].Init();
			}
			
			StageZ = 200;
			timer = 0;
			break;
		case 0://メニュー

			Menu();
	
			
			break;
		case 1://ゲーム部分
			if(KeyGet(KEY_INPUT_R))gamestate = -1;
			//カメラ
			SetCamera( *Delta );

			Delta->All();
			//敵の処理
		/*	for(int i = 0; i < ENUM; i++){
				if(e[i].GetLife() > 0 && timer > e[i].GetTimer() && Delta->GetZ() < e[i].GetZ() ){
					e[i].Draw();
					e[i].EShot();
					e[i].Homing(Delta->GetX(), Delta->GetY(), Delta->GetZ());
					e[i].Move();
					Delta->Homing(e[i].GetX(), e[i].GetY(), e[i].GetZ());
					for(int l = 0; l < SNUM; l++){
					if(e[i].GetLife() > 0){
						Colision(Delta->shot[l], e[i], damagesound);
					}
					}
				}
			
				for(int j = 0; j < ESNUM; j++){
					if(e[i].es[j].z < -5){
						e[i].es[j].flag = 0;
					}
				}
			}*/
			boss->Draw();
			boss->Move();

			//プレイヤーと敵弾の衝突判定
			for(int i = 0; i < ENUM; i++){
				pColision(*Delta, e[i].es);
			}

			//アイテム
			for(int i = 0; i < ENUM; i++){
				if(e[i].GetItemflag() == 1 && e[i].GetLife() == 0 ){
					for(int l = 0; l < INUM; l++){
						if(it[l].GetFlag() == false){
							it[l].SetState(e[i].GetX(), e[i].GetY(), e[i].GetZ());
							e[i].SetItemflag(0);
							break;
						}
					}
				}
			}
			for(int i = 0; i < INUM; i ++){
				it[i].Draw();
				if(it[i].GetZ() < Delta->GetZ() - 5.0f){
					it[i].SetFlag( false );
				}
			}



			ItemColision( *Delta, it, powerupsound );
			DrawFormatString( 0 , 15,GetColor(255,255,255) , "%d\n",0);
			//ステージ関係の処理
			MV1DrawModel(StageGraph);
			StageRX += 0.001;
			timer ++;
			MV1SetPosition(StageGraph, VGet( 0, 0, StageZ));
			MV1SetRotationXYZ(StageGraph, VGet(StageRX, 0, 0));

			

			Radar(e, *Delta);

			//ライフの描画
			Delta->LifeDraw();

			if(timer > 2400){
				gamestate = 3;
			}
			break;
		case 2:
			End();
			break;
		
		case 3:
			
				Clear();
			break;
		}
		
    }

    DxLib_End();
    return 0;
}  

void SetCamera( Character &c){
	if(c.GetLife() >= 0){
		SetCameraPositionAndTarget_UpVecY( VGet( 0, 12 , -15 + c.GetZ() ), VGet( c.GetRotateZ() / -7, 12.0f + c.GetRotateX() / 7, 10 ) ) ;
	}
	else{
		SetCameraPositionAndTarget_UpVecY( VGet( 0, 12 , -10 + c.GetZ() ), VGet( 0, 12.0f, 10 ) ) ;
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
	}
}
void pColision(Character &c, EShot *es){
	
	for(int i = 0; i < ESNUM; i++){
		float d;
		d = sqrt((es[i].x - c.GetX())*( es[i].x - c.GetX())) + sqrt((c.GetZ()- es[i].z)*(c.GetZ() - es[i].z));
		d = sqrt(d * d + (c.GetY() - es[i].y) * (c.GetY() - es[i].y));
		if( d < 4){
			c.SetLife( c.GetLife() -1 );
			es[i].flag = 0;
			es[i].z = 100;
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

