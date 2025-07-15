#include <iostream>
#include <graphics.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
using namespace std;

int num = 0;
int i, j;
int result;       

void reveal(int gameBoard[][20], int x, int y);

int main()
{
    initgraph(500, 500);
    IMAGE img[12];
    loadimage(&img[0], L"0.jpg", 25, 25);
    loadimage(&img[1], L"1.jpg", 25, 25);
    loadimage(&img[2], L"2.jpg", 25, 25);
    loadimage(&img[3], L"3.jpg", 25, 25);
    loadimage(&img[4], L"4.jpg", 25, 25);
    loadimage(&img[5], L"5.jpg", 25, 25);
    loadimage(&img[6], L"6.jpg", 25, 25);
    loadimage(&img[7], L"7.jpg", 25, 25);
    loadimage(&img[8], L"8.jpg", 25, 25);
    loadimage(&img[9], L"雷.jpg", 25, 25);
    loadimage(&img[10], L"标记.jpg", 25, 25);
    loadimage(&img[11], L"地图.jpg", 25, 25);

    while (true)
    {
        int gameBoard[20][20] = { 0 };
        num = 0;
        srand(static_cast<unsigned int>(time(nullptr)));

        for (int mineCount = 0; mineCount < 20; mineCount++)
        {
            int row = rand() % 20;
            int col = rand() % 20;
            if (gameBoard[row][col] == 0)
                gameBoard[row][col] = -1;
            else
                mineCount--;
        }

        for (i = 0; i < 20; i++)
        {
            for (j = 0; j < 20; j++)
            {
                if (gameBoard[i][j] != -1)
                {
                    int m, n;
                    for (m = i - 1; m <= i + 1; m++)
                    {
                        for (n = j - 1; n <= j + 1; n++)
                        {
                            if ((m >= 0 && m < 20) && (n >= 0 && n < 20))
                            {
                                if (gameBoard[m][n] == -1)
                                    gameBoard[i][j]++;
                            }
                        }
                    }
                }
            }
        }

        for (i = 0; i < 20; i++)
        {
            for (j = 0; j < 20; j++)
            {
                putimage(i * 25, j * 25, &img[11]);
            }
        }

        HWND hwnd = GetHWnd();
        ExMessage msg = { 0 };
        while (true)
        {
            if (peekmessage(&msg, EX_MOUSE))
            {
                if (msg.message == WM_LBUTTONDOWN)
                {
                    int gridX = msg.x / 25;
                    int gridY = msg.y / 25;

                    if (gridX >= 0 && gridX < 20 && gridY >= 0 && gridY < 20)
                    {
                        if (gameBoard[gridX][gridY] < -1)
                            gameBoard[gridX][gridY] += 20;

                        if (gameBoard[gridX][gridY] > -1)
                        {
                            if (gameBoard[gridX][gridY] < 10)
                            {
                                gameBoard[gridX][gridY] += 10;
                                num++;
                                if (gameBoard[gridX][gridY] == 10)
                                    reveal(gameBoard, gridX, gridY);
                            }
                        }
                        else
                        {
                            putimage(gridX * 25, gridY * 25, &img[9]);
                            result = MessageBoxA(hwnd, "你输了", "游戏结束", MB_OK);
                            break;
                        }
                    }
                }
                if (msg.message == WM_RBUTTONDOWN)
                {
                    int gridX = msg.x / 25;
                    int gridY = msg.y / 25;

                    if (gridX >= 0 && gridX < 20 && gridY >= 0 && gridY < 20)
                    {
                        if (gameBoard[gridX][gridY] < -1)
                        {
                            putimage(gridX * 25, gridY * 25, &img[11]);
                            gameBoard[gridX][gridY] += 20;
                        }
                        else if (gameBoard[gridX][gridY] < 10 && gameBoard[gridX][gridY] > -2)
                        {
                            putimage(gridX * 25, gridY * 25, &img[10]);
                            gameBoard[gridX][gridY] -= 20;
                        }
                    }
                }
            }

            for (i = 0; i < 20; i++)
            {
                for (j = 0; j < 20; j++)
                {
                    if (gameBoard[i][j] >= 10 && gameBoard[i][j] <= 18)
                    {
                        putimage(i * 25, j * 25, &img[gameBoard[i][j] - 10]);
                    }
                }
            }

            if (num == 380)
            {
                result = MessageBoxA(hwnd, "你赢了", "游戏结束", MB_OK);
                break;
            }
        }

        if (result == IDOK)
        {
            result = MessageBoxA(hwnd, "还想再玩一局吗", "游戏结束", MB_YESNO);
            if (result == IDNO)
                break;
        }
    }

    closegraph();
    return 0;
}

void reveal(int gameBoard[][20], int x, int y)
{
    int m, n;
    for (m = x - 1; m <= x + 1; m++)
    {
        for (n = y - 1; n <= y + 1; n++)
        {
            if (m >= 0 && m < 20 && n >= 0 && n < 20)
            {
                if (gameBoard[m][n] != -1 && gameBoard[m][n] < 10)
                {
                    if (gameBoard[m][n] == 0)
                    {
                        gameBoard[m][n] = 10;
                        num++;
                        reveal(gameBoard, m, n);
                    }
                    else
                    {
                        gameBoard[m][n] += 10;
                        num++;
                    }
                }
            }
        }
    }
}