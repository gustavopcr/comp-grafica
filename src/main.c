/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

For a C++ project simply rename the file to .cpp and re-run the build script 

-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event 
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial 
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you 
--  wrote the original software. If you use this software in a product, an acknowledgment 
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir


typedef struct{
	Texture2D texture;
	Rectangle source;
	Rectangle bounds;
	bool action;
}ActionButton;


void initActionButton(ActionButton* ab, Texture2D t, Rectangle source, Rectangle bounds, bool action){
	ab->texture = t;
	ab->source = source;
	ab->bounds = bounds;
	ab->action = action;
}


void doAction(char action, Vector2* pointsArr){
	switch(action){
		case 1:

			break;
		default:
	}
}

int main ()
{
	// Tell the window to use vysnc and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	SetTargetFPS(60);

	char actionMode = 0; // cada byte representa uma funcionalidade
	const char LINE_MODE = 1; // gerar pontos ao clicar

	// Create the window and OpenGL context
	const int screenWidth = 1200;
    const int screenHeight = 800;
	InitWindow(screenWidth, screenHeight, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	Vector2 pointsArr[3] = { {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}};
	Texture2D buttonTexture = LoadTexture("line.png"); // Load button texture
    Rectangle sourceRec = { 0, 0, (float)buttonTexture.width, (float)buttonTexture.height };
    Rectangle boundsRec = { 10.0f, 10.0f, (float)buttonTexture.width, (float)buttonTexture.height };
	ActionButton btnPoint = {buttonTexture, sourceRec, boundsRec, false};           // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
    Vector2 mousePoint = { 0.0f, 0.0f };
	int i = 0;

	
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
        btnPoint.action = false;

		// Check button state
        if (CheckCollisionPointRec(mousePoint, btnPoint.bounds))
        {
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
				btnPoint.action = true;
				actionMode += LINE_MODE;
			}
		}

		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
			mousePoint = GetMousePosition();
			if(actionMode == 1){
				pointsArr[i++] = GetMousePosition();
			}
			printf("x:%f y:%f\n", mousePoint.x, mousePoint.y);
		}
        // Calculate button frame rectangle to draw depending on button state
        sourceRec.y = (float)btnPoint.texture.height;
        //----------------------------------------------------------------------------------

		//doAction(actionMode, i, &pointsArr);
		
		
		// drawing
		BeginDrawing();

		// Setup the backbuffer for drawing (clear color and depth buffers)
		//ClearBackground(BLACK);
		// draw some text using the default font
		DrawText("Hello Raylib", 200,200,20,BLACK);
		DrawTextureRec(btnPoint.texture, sourceRec, (Vector2){ btnPoint.bounds.x, btnPoint.bounds.y }, WHITE); // Draw button frame
		// draw our texture to the screen
		//DrawTexture(wabbit, 400, 200, WHITE);

		if(i==3){
			for(int p=0; p<3; p++){
				DrawPixelV(pointsArr[p], PURPLE);
			}
			i=0;
		}

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(buttonTexture);

	// destory the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}