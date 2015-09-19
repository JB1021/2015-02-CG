#pragma once
class Ball
{
public:
	Ball();
	~Ball();

	void Init(int xx, int yy, int radius);
	void Update(float dt);
	void Render();
	
	bool IsGone();

	float x;
	float y;
	float z;
	float radius;

	float xSpeed;
	float ySpeed;
	float zSpeed;

	int r;
	int g;
	int b;

private:
	float rX;
	float rY;
	float rZ;



};

