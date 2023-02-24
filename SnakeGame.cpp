#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

#define COL 21
#define ROW 51
#define UPDATE_RATE 100

using namespace std;

char mapp[COL][ROW] = {
	{"--------------------------------------------------"},
	{"|                                                |"},
	{"|                                                |"},
	{"|                                                |"},
	{"|                                                |"},
	{"|                                                |"},
	{"|                                                |"},
	{"|                                                |"},
	{"|                                                |"},
	{"|                                                |"},
	{"|                                                |"},
	{"|                                                |"},
	{"|                                                |"},
	{"|                                                |"},
	{"|                                                |"},
	{"|                                                |"},
	{"|                                                |"},
	{"|                                                |"},
	{"|                                                |"},
	{"--------------------------------------------------"}
};

struct Player {
	int position[2], score, dir, tails, tailX[100], tailY[100];
};

Player player;
int TargetPos[2] = { 10, 30 };
int UPDATE_TIME = UPDATE_RATE;
bool game_over = false;

void RefreshTerrain() {
	UPDATE_TIME = UPDATE_RATE;
	system("cls");
	switch (player.dir)
	{
	case 0:
	{
		if (mapp[player.position[0]][player.position[1] + 1] == '|' || mapp[player.position[0]][player.position[1] + 1] == '-' || mapp[player.position[0]][player.position[1] + 1] == char(219)) game_over = true;
		else {
			player.position[1]++;
		}
		break;
	}
	case 1:
	{
		if (mapp[player.position[0]][player.position[1] - 1] == '|' || mapp[player.position[0]][player.position[1] - 1] == '-' || mapp[player.position[0]][player.position[1] - 1] == char(219)) game_over = true;
		else {
			player.position[1]--;
		}
		break;
	}
	case 2:
	{
		if (mapp[player.position[0] - 1][player.position[1]] == '|' || mapp[player.position[0] - 1][player.position[1]] == '-' || mapp[player.position[0] - 1][player.position[1]] == char(219)) game_over = true;
		else {
			player.position[0]--;
		}
		break;
	}
	case 3:
	{
		if (mapp[player.position[0] + 1][player.position[1]] == '|' || mapp[player.position[0] + 1][player.position[1]] == '-' || mapp[player.position[0] + 1][player.position[1]] == char(219)) game_over = true;
		else {
			player.position[0]++;
		}
		break;
	}
	}
	for (int i = 0; i < COL; i++) {
		for (int ii = 0; ii < ROW; ii++) {
			bool success = false;
			if (player.position[0] == i && player.position[1] == ii)
			{
				cout << char(219);
				success = true;
			}
			if (TargetPos[0] == i && TargetPos[1] == ii) {
				if (player.position[0] == i && player.position[1] == ii)
				{
					TargetPos[0] = rand() % (COL - 2) + 1;

					TargetPos[1] = rand() % (ROW - 2) + 1;

					player.tails++;
					player.score++;
				}
				else {
					cout << "O";
					success = true;
				}
			}
			for (int iii = 0; iii < player.tails; iii++) {
				if (player.tailX[iii] == i && player.tailY[iii] == ii) {
					cout << char(219);
					success = true;
				}
				if (player.position[0] == player.tailX[iii] && player.position[1] == player.tailY[iii]) game_over = true;
			}
			if (!success) cout << mapp[i][ii];
		}
		cout << endl;
	}
	if (!game_over)
	{
		int prevX = player.tailX[0];
		int prevY = player.tailY[0];
		int prev2X, prev2Y;
		player.tailX[0] = player.position[0];
		player.tailY[0] = player.position[1];
		for (int i = 1; i < player.tails; i++)
		{
			prev2X = player.tailX[i];
			prev2Y = player.tailY[i];
			player.tailX[i] = prevX;
			player.tailY[i] = prevY;
			prevX = prev2X;
			prevY = prev2Y;

		}
	}
}


int main()
{
	player.position[0] = 15;
	player.position[1] = 35;
	player.score = 0;
	player.dir = 0;
	player.tails = 0;

	RefreshTerrain();


	while (true) {

		if (game_over)
		{
			cout << "Game Over!" << endl;
			cout << "Total points: " << player.score << endl;
			system("pause");
			break;
		}

		if (_kbhit()) {
			char key;
			key = _getch();
			switch (key)
			{
			case 'd': { if (player.dir != 1) player.dir = 0; break; }
			case 'D': { if (player.dir != 1) player.dir = 0; break; }
			case 'a': { if (player.dir != 0) player.dir = 1; break; }
			case 'A': { if (player.dir != 0) player.dir = 1; break; }
			case 'W': { if (player.dir != 3) player.dir = 2; break; }
			case 'w': { if (player.dir != 3) player.dir = 2; break; }
			case 'S': { if (player.dir != 2) player.dir = 3; break; }
			case 's': { if (player.dir != 2) player.dir = 3; break; }
			}
		}

		if (UPDATE_TIME > 0) {
			Sleep(100);
			UPDATE_TIME -= 100;
			if (UPDATE_TIME == 0) RefreshTerrain();
		}
	}
	return 65535;
}