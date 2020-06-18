// RTS.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <vector>
#include <string>

#include "raylib.h"
#include "Vec2.h"
#include "Define.h"
#include "Map.h"
#include "Unit.h"
#include "Node.h"

#include "SoundManager.h"

void GestionCamera(Camera2D& camera, Vector2& CursorCamPos, Vector2& OldCursorCamPos)
{
	CursorCamPos = GetMousePosition();

	if ((CursorCamPos.x >= GetScreenWidth() - CURSORRADIUS / 2))
	{
		CursorCamPos = OldCursorCamPos;
		camera.target.x++;
	}
	else if (CursorCamPos.x <= CURSORRADIUS / 2)
	{
		CursorCamPos = OldCursorCamPos;
		camera.target.x--;
	}
	else if ((CursorCamPos.y >= (GetScreenHeight() - CURSORRADIUS / 2)))
	{
		CursorCamPos = OldCursorCamPos;
		camera.target.y++;
	}
	else if (CursorCamPos.y <= CURSORRADIUS / 2)
	{
		CursorCamPos = OldCursorCamPos;
		camera.target.y--;
	}


	// TODO : A debug, Cercle ne suit pas la souris
	camera.zoom += ((float)GetMouseWheelMove() * 0.05f);

	if (camera.zoom > 2.0f) 
		camera.zoom = 2.0f;
	else if (camera.zoom < 0.5f) 
		camera.zoom = 0.5f;
}

int main()
{
	InitAudioDevice();              // Initialize audio device

	SoundManager soundManager;
	soundManager.AddMusicAmbients("resources/musics/bad-romance.mp3");
	soundManager.AddMusicAmbients("resources/musics/take-on-me.mp3");
	soundManager.AddMusicAmbients("resources/musics/what-is-love.mp3");
	soundManager.AddMusicAmbients("resources/musics/metallica-seek-destroy.mp3");
	soundManager.AddMusicAmbients("resources/musics/i-want-to-break-free.mp3");

	InitWindow(SCREENWIDTH, SCREENHEIGHT, "RTS starting Window");

	SetTargetFPS(60);

	Vector2 CursorCamPos = { -100.0f, -100.0f };
	Vector2 OldCursorCamPos = { -100.0f, -100.0f };
	Color CursorColor = DARKBLUE;

	Camera2D camera = { 0 };
	camera.target = { 0,0 };
	camera.offset = { 0, 0 };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	Unit unit;
	Map map;

	bool collision = false;


	for (int i = 0; i < SIZEMAP * SIZEMAP; i++)
		map.cases.push_back(Node());

	while (!WindowShouldClose())
	{
		soundManager.Update();

		// ======Camera=========
		GestionCamera(camera, CursorCamPos, OldCursorCamPos);
		// ====================

		// DEplacement de L'IA
		unit.MoveAI(camera, CursorCamPos, map);

		bool collision = false; int temp = -1;
		if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
		{
			for (int i = 0; i < SIZEMAP; i++)
			{
				for (int j = 0; j < SIZEMAP; j++)
				{
					Rectangle rec = { (float)i * SIZECASE, (float)j * SIZECASE, SIZECASE, SIZECASE };
					Vector2 point = { CursorCamPos.x / camera.zoom + camera.target.x, CursorCamPos.y / camera.zoom + camera.target.y };
					if (CheckCollisionPointRec(point, rec))
					{
						collision = true;
						temp = i * SIZEMAP + j;
						break;
					}
				}
				if (collision)
					break;
			}

			if (temp >= 0)
			{
				if (map.cases[temp].state == State::OBSTACLE)
					map.cases[temp].state = State::WALKABLE;
				else
				{
					map.cases[temp].state = State::OBSTACLE;
				}
			}
		}

		// =================
		// Draw
		BeginDrawing();

		ClearBackground(RAYWHITE);

		BeginMode2D(camera);
		DrawCircleV({ CursorCamPos.x / camera.zoom + camera.target.x, CursorCamPos.y / camera.zoom + camera.target.y }, CURSORRADIUS, CursorColor);

		map.Draw();
		
		unit.Draw();

		EndMode2D();
		EndDrawing();
		// ========
		OldCursorCamPos = CursorCamPos;
	}

	soundManager.Close();

	CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
