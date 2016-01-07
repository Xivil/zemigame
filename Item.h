# ifndef __ITEM__HEDAR__
# define __ITEM__HEDAR__

#define INUM 5

class Item{
public:
	Item();
	void Init();
	void SetState( float x, float y, float z );
	void Draw();
	bool GetFlag();
	void SetFlag( bool flag );
	float GetX();
	float GetY();
	float GetZ();
private:
	float x, y, z;
	float rx;
	int graph;
	bool flag;
};

#endif