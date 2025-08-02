#include "raylib.h"
#include "resource_dir.h"	
#include <string>

  	const int screenWidth = 800;
    const int screenHeight = 800;
	int playerscore = 0;
	int aiscore = 0;
	


	Vector2 playerstartpoint = {20, 325};
	Vector2 playerendpoint = {20, 475};
	Vector2 leftPadlePos = {20, 325};
	Vector2 rightPadlePos = {760, 325};
	Vector2 ballcoord = {400, 400};
	Vector2 ballvelocity ={5,0};
	void movement();void collision();void ball();void ai();void ballReset();
int main ()
{
 
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(	screenWidth, screenHeight 	, "Pong");
	SearchAndSetResourceDir("resources");
	

	
	
	while (!WindowShouldClose())		
	{
		std::string scoreStr = std::to_string(playerscore) + " : " + std::to_string(aiscore);
		BeginDrawing();
		ClearBackground(BLACK);
		//DrawLineEx(playerstartpoint, playerendpoint, 10.0f, BLUE); 
		DrawRectangleLines(leftPadlePos.x, leftPadlePos.y,  18, 150, WHITE); 
		DrawRectangleLines(rightPadlePos.x, rightPadlePos.y,  18, 150, WHITE); 
		DrawText(scoreStr.c_str(), (screenWidth - MeasureText(scoreStr.c_str(), 100))/2, 0, 100, WHITE);
		movement();
		collision();
		ball();
		ai();
		EndDrawing();
	}	
	





	CloseWindow();
	return 0;
}
void movement()
	{
		if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
		{
			leftPadlePos.y -= 10;
		}
		if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
		{
			leftPadlePos.y += 10;
		}
	}

void collision()
	{
		if(leftPadlePos.y <= 0)
		{
			leftPadlePos.y = 0;
			
			
		}
		if(leftPadlePos.y+150 >= 800)
		{
			leftPadlePos.y = 650;
			
			
		}
		if(rightPadlePos.y <= 0)
		{
			rightPadlePos.y = 0;
			
			
		}
		if(rightPadlePos.y+150 >= 800)
		{
			rightPadlePos.y = 650;
			
			
		}
		
	}
void ball()
{
	DrawCircle(  ballcoord.x,  ballcoord.y,   18,  WHITE);
	ballcoord.x += ballvelocity.x;
	ballcoord.y += ballvelocity.y;

	if (ballcoord.x > 800)
	{
		ballReset();
		playerscore++;
	}
	if (ballcoord.x < 0)
	{
		ballReset();
		aiscore++;
	}
	if (ballcoord.y > 800)
	{
		ballvelocity.y *= -1;
	}
	if (ballcoord.y < 0)
	{
		ballvelocity.y *= -1;
	}
	if (CheckCollisionCircleRec(ballcoord, 18, { leftPadlePos.x, leftPadlePos.y, 18, 150}) && ballvelocity.x < 0)
	{
		ballvelocity.x *= -1;
		float relativeIntersectY = (leftPadlePos.y + 75) - ballcoord.y;
        float normalizedRelativeIntersectionY = relativeIntersectY/(75);
        ballvelocity.y = -normalizedRelativeIntersectionY * 5.0f;
		
	}
	if (CheckCollisionCircleRec(ballcoord, 18, { rightPadlePos.x, rightPadlePos.y, 18, 150}) && ballvelocity.x > 0)
	{
		ballvelocity.x *= -1;
		float relativeIntersectY = (rightPadlePos.y + 75) - ballcoord.y;
        float normalizedRelativeIntersectionY = relativeIntersectY/(75);
        ballvelocity.y = -normalizedRelativeIntersectionY * 5.0f;
	}


	

}
void ai()
{
	float predictedY = 325.0f;
	if(ballvelocity.x > 0)
	{
		float distanceToright = (screenWidth - 20.0f - 18.0f) - ballcoord.x;
		float timeToRight = distanceToright / ballvelocity.x;
		predictedY = ballcoord.y + (ballvelocity.y * timeToRight)-75.0f;
	}
	if(rightPadlePos.y != predictedY)
	{
		if(rightPadlePos.y > predictedY)
		{
			rightPadlePos.y -= 2;
		}
		if(rightPadlePos.y < predictedY)
		{
			rightPadlePos.y += 2;
		}
	}


}
void ballReset()
{
	ballcoord.x = 400;
	ballcoord.y = 400;
	ballvelocity.x *= -1;
}
