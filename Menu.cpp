#include "HeaderInclude.h"

void Menu(){

	int Cr = GetColor( 255 , 255 , 255 ) ;

	DrawString( 1024/2 , 768/2 - 30 , "�RD�V���[�e�B���O�Q�[��" , Cr );
	if(KeyGet(KEY_INPUT_SPACE)){
				gamestate = -1;
	}
}

void End(){
	DrawString( 1024/2, 768/ 2 - 30, "GameOver\nPress R Button", GetColor(255, 255, 255));
		if(KeyGet(KEY_INPUT_R)){
			gamestate = -1;
		}
}