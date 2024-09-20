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
	Rectangle sourceRec;
	Rectangle btnBounds;
	bool btnAction;
}ActionButton;

int main ()
{
	// Tell the window to use vysnc and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	const int screenWidth = 1200;
    const int screenHeight = 800;
	InitWindow(screenWidth, screenHeight, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");
	Texture2D buttonTexture = LoadTexture("line.png"); // Load button texture


    Rectangle sourceRec = { 0, 0, (float)buttonTexture.width, (float)buttonTexture.height };
	// Define button bounds on screen
    Rectangle btnBounds = { 10.0f, 10.0f, (float)buttonTexture.width, (float)buttonTexture.height };
	
	ActionButton pointBtn = {buttonTexture, sourceRec, btnBounds, false};           // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
    //pointBtn.btnAction = false;         // Button action should be activated

    Vector2 mousePoint = { 0.0f, 0.0f };

    SetTargetFPS(60);
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		mousePoint = GetMousePosition();
        pointBtn.btnAction = false;

		// Check button state
        if (CheckCollisionPointRec(mousePoint, pointBtn.btnBounds))
        {
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) pointBtn.btnAction = true;
        }

        if (pointBtn.btnAction)
        {
			// TODO: Any desired action
            for(int i=0; i<100; i++){
				DrawPixel(100+i, 100+i, PURPLE);
			}            
        }

        // Calculate button frame rectangle to draw depending on button state
        sourceRec.y = (float)pointBtn.texture.height;
        //----------------------------------------------------------------------------------


		// drawing
		BeginDrawing();

		// Setup the backbuffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font
		DrawText("Hello Raylib", 200,200,20,BLACK);
		DrawTextureRec(pointBtn.texture, sourceRec, (Vector2){ pointBtn.btnBounds.x, pointBtn.btnBounds.y }, WHITE); // Draw button frame
		// draw our texture to the screen
		//DrawTexture(wabbit, 400, 200, WHITE);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);
	UnloadTexture(buttonTexture);

	// destory the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}