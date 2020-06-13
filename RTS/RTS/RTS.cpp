// RTS.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <vector>

#include "raylib.h"
#include "Vec2.h"

#define SCREENWIDTH 800
#define SCREENHEIGHT 450

#define CURSORRADIUS 20

#define SIZEMAP 5
#define SIZECASE 100

enum class State
{
	WALKABLE,
	OBSTACLE
};

struct Case
{
	State state = State::WALKABLE;
};

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
}

void MoveIA(Camera2D& camera, Vector2& CursorCamPos, QXvec2& IAGoalPos, QXvec2& IAPos)
{
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		IAGoalPos = { CursorCamPos.x + camera.target.x, CursorCamPos.y + camera.target.y };
	}

	if ((IAGoalPos - IAPos).Length() > 10)
		IAPos = IAPos + (IAGoalPos - IAPos).Normalize() * 10;
}

int main()
{
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

	QXvec2 IAPos = { 150,150 };
	QXvec2 IAvecDir = { 0,0 };
	QXvec2 IAGoalPos = { 150,150 };

	bool collision = false;

	Case cases[SIZEMAP * SIZEMAP];

	while (!WindowShouldClose())
	{
		// ======Camera=========
		GestionCamera(camera, CursorCamPos, OldCursorCamPos);
		// ====================

		// DEplacement de L'IA
		MoveIA(camera, CursorCamPos, IAGoalPos, IAPos);

		bool collision = false;
		if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
		{
			for (int i = 0; i < SIZEMAP; i++)
			{
				for (int j = 0; j < SIZEMAP; j++)
				{
					Rectangle rec = { (float)i * SIZECASE, (float)j * SIZECASE, SIZECASE, SIZECASE };
					Vector2 point = { CursorCamPos.x + camera.target.x, CursorCamPos.y + camera.target.y };
					if (CheckCollisionPointRec(point, rec))
					{
						collision = true;
						if (cases[i * j].state == State::OBSTACLE)
							cases[i * j].state = State::WALKABLE;
						else
						{
							cases[i * j].state = State::OBSTACLE;
							std::cout << "stter obstacle" << std::endl;
						}
						break;
					}
				}
				if (collision)
					break;
			}
		}

		// =================
		// Draw
		BeginDrawing();

		ClearBackground(RAYWHITE);

		BeginMode2D(camera);
		DrawCircleV({ CursorCamPos.x + camera.target.x, CursorCamPos.y + camera.target.y}, CURSORRADIUS, CursorColor);

			//DrawRectangleLines
			DrawText("move ball with mouse and click mouse button to change color", 10, 10, 20, DARKGRAY);

			
			for (int i = 0; i < SIZEMAP; i++)
			{
				for (int j = 0; j < SIZEMAP; j++)
				{
					Case tmp = cases[i * j];
					if (tmp.state == State::WALKABLE)
						DrawRectangleLines(i * SIZECASE, j * SIZECASE, SIZECASE, SIZECASE, MAROON);
					else
					{
						DrawRectangle(i * SIZECASE, j * SIZECASE, SIZECASE, SIZECASE, BLACK);
					}
				}
			}

			DrawRectangle(IAPos.x - SIZECASE / 4, IAPos.y - SIZECASE / 4, SIZECASE/2, SIZECASE/2, GREEN);

			EndMode2D();
		EndDrawing();
		// ========
		OldCursorCamPos = CursorCamPos;
	}

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
