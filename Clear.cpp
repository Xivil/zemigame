#include "HeaderInclude.h"
namespace {
	int clear_graph = 0;
}
void Clear(){
	if (clear_graph == 0)
	{
		clear_graph = LoadGraph("Graph/clear.png");
	}
	DrawGraph(0, 0, clear_graph, TRUE);
	ScoreRankDraw();
}