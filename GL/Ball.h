#pragma once
class Ball
{
public:
	Ball();
	~Ball();

	void Init(int xx, int yy);
	void Update(float dt);
	void Render();

	bool IsGone();

private:
	float x;
	float y;
	float z;

	float rX;
	float rY;
	float rZ;

	float speed;
};

