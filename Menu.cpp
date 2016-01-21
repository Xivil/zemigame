#include "HeaderInclude.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
namespace {
	unsigned int flag = 0;
	int graph = 0;
	int star[6];
	int cr[2];
	int x[64];
	int y[64];
	int star_flag[64];
	int star_color[64];
	int timer = 0;
	int button1 = 0;
	int start_sound = 0;
	int score[11];	//	第11番目の要素はプレイした時のスコアを入れる
	int gameover_graph = 0;
	int gameover_music = 0;
	int a  = - 1;
	int input = 0;
	int InputX = 0, InputY = 0;
	int pad[3] = {0, 0, 0};
}

void Menu(){
	timer++;
	ScoreLoad();
	if (graph == 0)
	{
		graph = LoadGraph("Graph/titile.png");
	}
	if (button1 == 0){
		button1 = LoadSoundMem("sound/button01a.mp3");
		ChangeVolumeSoundMem(70, button1);
	}
	if (start_sound == 0){
		start_sound = LoadSoundMem("sound/se_maoudamashii_onepoint10.mp3");
	}
	LoadDivGraph("Graph/star.png", 6, 6, 1, 25, 25, star);
	
	if (timer % 30 == 0){
		for (int i = 0; i < 64; i++){
			if (star_flag[i] == 0)
			{
				star_flag[i] = 1;
				y[i] = 0;
				x[i] = rand() % 770 + 1;
				star_color[i] = rand() % 6;
				break;

			}
		}
	}
	
	DrawGraph(0, 0, graph, TRUE);
	for (int i = 0; i < 64; i++){
		if (star_flag[i]){
			DrawGraph(x[i], y[i], star[star_color[i]], TRUE);
			y[i] += 1;
			if (y[i] >= 800){
				star_flag[i] = 0;
			}
		}
	}

	input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	GetJoypadAnalogInput(&InputX, &InputY, DX_INPUT_KEY_PAD1);
	if (input & PAD_INPUT_LEFT || InputX){
		pad[0] ++;
	}
	else{
		pad[0] = 0;
	}
	if (input & PAD_INPUT_RIGHT){
		pad[1] ++;
	}
	else{
		pad[1] = 0;
	}
	if (input & PAD_INPUT_1 || input & PAD_INPUT_2 || input & PAD_INPUT_3 || input & PAD_INPUT_4){
		pad[2] ++;
	}
	else{
		pad[2] = 0;
	}
	if (KeyGet(KEY_INPUT_SPACE) == 1 || pad[2] == 1){
		if (flag % 2 == 0){
			gamestate = -1;
			DrawString(650, 550, "Now Loading...", GetColor(255, 255, 255), GetColor(167, 22, 45));
			PlaySoundMem(start_sound, DX_PLAYTYPE_BACK);
		}
		else{
			PlaySoundMem(button1, DX_PLAYTYPE_BACK);
			gamestate = -2;
		}
		graph = 0;
	}
	if (KeyGet(KEY_INPUT_LEFT) == 1 || KeyGet(KEY_INPUT_RIGHT) == 1 || pad[0] == 1 || pad[1] == 1){
		flag++;
		PlaySoundMem(button1, DX_PLAYTYPE_BACK);
	}
	if (flag % 2 == 0){
		cr[0] = GetColor(255,255,255);
		cr[1] = GetColor(100, 100, 100);
	}
	else{
		cr[1] = GetColor(255, 255, 255);
		cr[0] = GetColor(100, 100, 100);
	}
	DrawFormatString(350, 500, cr[0], "START");
	DrawFormatString(450, 500, cr[1], "説明");
	DrawFormatString(370, 550, GetColor(255, 255, 255), "press space");
	DrawFormatString(330, 450, GetColor(0, 255, 255), "Hi-Score %d", score[0]);
	
}

void Description(){
	if (graph == 0)
	{
		graph = LoadGraph("Graph/description.png");
	}
	
	DrawGraph(0, 0, graph, TRUE);

	input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (input & PAD_INPUT_1 || input & PAD_INPUT_2 || input & PAD_INPUT_3 || input & PAD_INPUT_4){
		pad[2] ++;
	}
	else{
		pad[2] = 0;
	}
	if (KeyGet(KEY_INPUT_SPACE) == 1 || pad[2] == 1){
		gamestate = 0;
		graph = 0;
	}
}

void End(){
	if (gameover_graph == 0){
		gameover_graph = LoadGraph("Graph/player_dead.png");
	}

	DrawGraph(0, 0, gameover_graph, TRUE);
	if(KeyGet(KEY_INPUT_R)){
		gamestate = -1;
	}
	
}

void ScoreLoad(){
	FILE *f;
	double c = 0;
	char buf[100];
	for (int i = 0; i < 11; i++){
		score[i] = 0;
	}
	string s;
	f = fopen("score.txt", "r");
	int col = 0;

	while (1){
		while (1){
			c = fgetc(f);
			if (c == EOF){
				goto out;
			}
			if (c != ' ' && c != '\n'){
				s += c;
			}
			else { break; }

		}
		score[col] = atoi(s.c_str());

		s.clear();

		if (c == '\n'){
			col ++;
		}
	}
out:
	fclose(f);
}

void ScoreWrite(int play_score){
	ScoreLoad();
	score[10] = play_score;
	ScoreSort(score, 11);
	FILE *f;
	f = fopen("score.txt", "w+");
	for (int i = 0; i < 10; i++){
		fprintf_s(f, "%d\n", score[i]);
	}
	fclose(f);
}

void ScoreRankDraw(){
	char buf[10][64];
	memset(buf, '0', 100);
	DrawString(300, 110, "SCORE RANKING", GetColor(0, 255, 255));
	for (int i = 0; i < 10; i++){
		sprintf_s(buf[i], "No%d. %d", i + 1, score[i]);
		DrawString(300, 150 + i * 30, buf[i], GetColor(0, 255, 255));
		if (i == a){
			DrawTriangle(260, 150 + i * 30, 290, 160 + i * 30, 260, 170 + i * 30, GetColor(255, 0, 0), TRUE);
		}
	}
	
}

#define INT_SWAP(a,b) int tmp=a;a=b;b=tmp
void ScoreSort(int* pData, int Amount, int Dammy){
	a = -1;
	for (int i = 0; i < 10; i++){
		if (score[i] <= score[10]){
			a = i;
			break;
		}
	}
	for (int i = Amount; i > 1; --i){
		for (int k = 1; k < i; k++){
			if (pData[k - 1] < pData[k]){
				INT_SWAP(pData[k - 1], pData[k]);
			}
		}
	}
}