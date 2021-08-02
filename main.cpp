#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <Windows.h>

using namespace std;

//			ОБЪЯВЛЕНИЕ ПЕРЕМЕННЫХ

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
bool bIsGameOver = false;

int iHeroX = 0;															// координаты героя
int iHeroY = 0;
int iHeroDirX = 0;														// координаты вектора направления ероя
int iHeroDirY = 0;
time_t start;															// время начала игры
time_t finish;															// текущее время
clock_t start_t;														// время в мили секундах для регулирования плотности потока машин и скорости машин
clock_t finish_t;
int timer_t = 0;														// вычисляем милисекунды start_t - finish_t
int timer = 0;															// вычисляем таймер игры start - finish

const int H_FIELD = 50;													// размер игрового поля 50 х 10 клеток
const int W_FIELD = 10;
char Pixel[W_FIELD][H_FIELD];											// массив который будет каждый цикл игры отрисовываться в консоли

const char GAME_FIELD[W_FIELD][H_FIELD] = { "F###########TXr#################################T",				// константный символьный массив
											"I                                               <",				// каждый символ копируется в Pixel[][]
											"I                                               <",				// и заменяется посимвольно на ASCII графику
											"I                                               <",				// в Setup()
											"z                                               <",
											">                                               t",
											">                                               I",
											">                                               I",
											">                                               I",
											"L############################v@L################J" };    

//			ОБЯВЛЕНИЕ МЕТОДОВ

void Draw();
void Input();
void Logic();
void Setup();
void MoveHeroTo(int, int);
void MoveCarToRight(int, int);
void MoveCarToLeft(int, int);

//			main точка входа в программу

int main()
{
	Setup();															// Начальные установки
	while (!bIsGameOver)												// Главный цикл игры
	{
		Draw();															// Функция отрисовки кадра 
		Input();														// Функция ввода игроком клавиш управления 
		Logic();														// Функция логики игры
	}
	return 0;
}

void Logic()
{
	if (timer_t % 1 == 0)				// speed						// каждую милисекунду запускаются 2 цикла сканирования поля 
	{
		for (int x = 1; x < 5; x++)
		{
			for (int y = 0; y < H_FIELD; y++)
			{
				MoveCarToLeft(x, y);									// для каждой клетки половины поля вызывается функция MoveCarToLeft 
			}
		}
		for (int x = 9; x > 4; x--)
		{
			for (int y = 50; y > 1; y--)
			{
				MoveCarToRight(x, y);
			}
		}
	}
	if(timer_t % 15 == 0)				// traffic density				// каждые 10 милисекунд переменной car присваивается значение от 1 до 8 
	{
	int car = (rand() % 8 + 1);
	bool bIsTargetPixelFree = true;										// создаем переменную флаг проверяющую свободна ли клетка
	switch (car)
	{
	case 1:																// первая линия движения машинок
		bIsTargetPixelFree = false;
		switch (Pixel[1][47])											// если начальное положение занято другой машинкой ставим флаг false
		{
		case 58:
		case -2:
			bIsTargetPixelFree = false;
			break;
		default:														// во всех остальных случаях ставим флаг true
			bIsTargetPixelFree = true;
			break;
		}
		if (bIsTargetPixelFree)											// если клетка начального положения свободна отрисовываем появление машики 
		{
			Pixel[1][47] = 58;				//    :<
			Pixel[1][46] = 58;				//   ::<
			Pixel[1][47] = -2;				//   :E<
			Pixel[1][45] = 58;				//  ::E<
			Pixel[1][46] = -2;				//  :EE<
			Pixel[1][44] = 58;				// ::EE<
			Pixel[1][45] = -2;				// :EEE<
			Pixel[1][47] = 32;				// :EE <
			car = 0;
			MoveCarToLeft(1, 44);										// и подталкиваем ее вперед с начальными координатами (а зачем?)
		}
		break;
	case 2:
		bIsTargetPixelFree = false;
		switch (Pixel[2][47])
		{
		case 58:
		case -2:
			bIsTargetPixelFree = false;
			break;
		default:
			bIsTargetPixelFree = true;
			break;
		}
		if (bIsTargetPixelFree)
		{
			Pixel[2][47] = 58;
			Pixel[2][46] = 58;
			Pixel[2][47] = -2;
			Pixel[2][45] = 58;
			Pixel[2][46] = -2;
			Pixel[2][44] = 58;
			Pixel[2][45] = -2;
			Pixel[2][47] = 32;
			MoveCarToLeft(2, 44);
			car = 0;
		}
		break;
	case 3:
		bIsTargetPixelFree = false;
		switch (Pixel[3][47])
		{
		case 58:
		case -2:
			bIsTargetPixelFree = false;
			break;
		default:
			bIsTargetPixelFree = true;
			break;
		}
		if (bIsTargetPixelFree)
		{
			Pixel[3][47] = 58;
			Pixel[3][46] = 58;
			Pixel[3][47] = -2;
			Pixel[3][45] = 58;
			Pixel[3][46] = -2;
			Pixel[3][44] = 58;
			Pixel[3][45] = -2;
			Pixel[3][47] = 32;
			MoveCarToLeft(3, 44);
			car = 0;
		}
		break;
	case 4:
		bIsTargetPixelFree = false;
		switch (Pixel[4][47])
		{
		case 58:
		case -2:
			bIsTargetPixelFree = false;
			break;
		default:
			bIsTargetPixelFree = true;
			break;
		}
		if (bIsTargetPixelFree)
		{
			Pixel[4][47] = 58;
			Pixel[4][46] = 58;
			Pixel[4][47] = -2;
			Pixel[4][45] = 58;
			Pixel[4][46] = -2;
			Pixel[4][44] = 58;
			Pixel[4][45] = -2;
			Pixel[4][47] = 32;
			MoveCarToLeft(4, 44);
			car = 0;
		}
		break;
	case 5:
		bIsTargetPixelFree = false;
		switch (Pixel[5][1])
		{
		case 58:
		case -2:
			bIsTargetPixelFree = false;
			break;
		default:
			bIsTargetPixelFree = true;
			break;
		}
		if (bIsTargetPixelFree)
		{
			Pixel[5][1] = 58;				// >:
			Pixel[5][2] = 58;				// >::
			Pixel[5][1] = -2;				// >E:
			Pixel[5][3] = 58;				// >E::
			Pixel[5][2] = -2;				// >EE:	
			Pixel[5][4] = 58;				// >EE::
			Pixel[5][3] = -2;				// >EEE:
			Pixel[5][1] = 32;				// > EE:
			MoveCarToRight(5, 4);
			car = 0;
		}
		break;
	case 6:
		bIsTargetPixelFree = false;
		switch (Pixel[6][1])
		{
		case 58:
		case -2:
			bIsTargetPixelFree = false;
			break;
		default:
			bIsTargetPixelFree = true;
			break;
		}
		if (bIsTargetPixelFree)
		{
			Pixel[6][1] = 58;
			Pixel[6][2] = 58;
			Pixel[6][1] = -2;
			Pixel[6][3] = 58;
			Pixel[6][2] = -2;
			Pixel[6][4] = 58;
			Pixel[6][3] = -2;
			Pixel[6][1] = 32;
			MoveCarToRight(6, 4);
			car = 0;
		}
		break;
	case 7:
		bIsTargetPixelFree = false;
		switch (Pixel[7][1])
		{
		case 58:
		case -2:
			bIsTargetPixelFree = false;
			break;
		default:
			bIsTargetPixelFree = true;
			break;
		}
		if (bIsTargetPixelFree)
		{
			Pixel[7][1] = 58;
			Pixel[7][2] = 58;
			Pixel[7][1] = -2;
			Pixel[7][3] = 58;
			Pixel[7][2] = -2;
			Pixel[7][4] = 58;
			Pixel[7][3] = -2;
			Pixel[7][1] = 32;
			MoveCarToRight(7, 4);
			car = 0;
		}
		break;
	case 8:
		bIsTargetPixelFree = false;
		switch (Pixel[8][1])
		{
		case 58:
		case -2:
			bIsTargetPixelFree = false;
			break;
		default:
			bIsTargetPixelFree = true;
			break;
		}
		if (bIsTargetPixelFree)
		{
			Pixel[8][1] = 58;
			Pixel[8][2] = 58;
			Pixel[8][1] = -2;
			Pixel[8][3] = 58;
			Pixel[8][2] = -2;
			Pixel[8][4] = 58;
			Pixel[8][3] = -2;
			Pixel[8][1] = 32;
			MoveCarToRight(8, 4);
			car = 0;
		}
		break;
	default:
		break;
	}
	}
	time(&finish);
}

void MoveCarToRight(int x, int y)										// функция движения слева направо
{
	if (Pixel[x][y] == 58 && Pixel[x][y + 1] == 32)						// функция отрисовки анимации движения машинки
	{
		Pixel[x][y + 1] = 58;				// > EE::
		Pixel[x][y] = -2;					// > EEE:		
		Pixel[x][y - 2] = 32;				// >  EE:
		Pixel[5][0] = 16;					// >
		Pixel[6][0] = 16;					// >
		Pixel[7][0] = 16;					// >
		Pixel[8][0] = 16;					// >
	}
	else if (Pixel[x][y] == 58 && Pixel[x][y+1] == 2)					// проверка на столкновение  с героем
	{
		system("cls");
		cout << "\n\n\n\t GAME OVER \n\n\n";
		cout << "\tYour Time: " << timer << endl << endl << endl;
		system("pause > NULL");
		bIsGameOver = true;
	}
	else if (Pixel[x][y] == 58 && Pixel[x][y + 1] != 32)				// отрисовка анимации при въезда в стенку игрового поля
	{
		char PrevPixel = Pixel[x][y + 1];	// ... EE:| 5,49
		Pixel[x][y + 1] = 58;				// ... EE::
		Pixel[x][y] = -2;					// ... EEE:
		Pixel[x][y - 2] = 32;				// ...  EE: 	
		Pixel[x][y + 1] = PrevPixel;		// ...  EE|
		Pixel[x][y - 1] = 32;				// ...   E|
		Pixel[x][y] = 32;					// ...    |
	}

}

void MoveCarToLeft(int x, int y)										// функция движения справа налево (комментарии для MoveCarToRight)
{
	if (Pixel[x][y] == 58 && Pixel[x][y - 1] == 32)
	{
		Pixel[x][y - 1] = 58;				// ::EE
		Pixel[x][y] = -2;					// :EEE
		Pixel[x][y + 2] = 32;				// :EE
		Pixel[1][48] = 17;					// <
		Pixel[2][48] = 17;					// <
		Pixel[3][48] = 17;					// <
		Pixel[4][48] = 17;					// <
	}
	else if(Pixel[x][y] == 58 && Pixel[x][y - 1] == 2)
	{
		system("cls");
		cout << "\n\n\n\t GAME OVER \n\n\n";
		cout << "\tYour Time: " << timer << endl << endl << endl;
		system("pause > NULL");
		bIsGameOver = true;
	}
	else if (Pixel[x][y] == 58 && Pixel[x][y - 1] != 32)
	{
		char PrevPixel = Pixel[x][y - 1];	// |:EE
		Pixel[x][y - 1] = 58;				// ::EE
		Pixel[x][y] = -2;					// :EEE 
		Pixel[x][y + 2] = 32;				// :EE
		Pixel[x][y - 1] = PrevPixel;		// |EE
		Pixel[x][y + 1] = 32;				// |E 
		Pixel[x][y] = 32;					// |
	}
}

void MoveHeroTo(int x, int y)											// функция движения героя
{
	if (x <= W_FIELD - 1 && x >= 0 && y <= H_FIELD - 1 && y >= 0)
	{
		char TargetPixel = Pixel[x][y];									// проверяем клетку-цель свободна ли она
		bool bIsTargetPixelFree = false;
		switch (TargetPixel)
		{
		case 58:		// car bumper (, ), :							// клетка бампера машинки 
			system("cls");
			cout << "\n\n\n\t GAME OVER \n\n\n";
			cout << "\tYour Time: " << timer << endl << endl << endl;
			system("pause > NULL");
			bIsGameOver = true;
			break;
		case -70:		// I wall left and right						// клетки границы игрового поля
		case -51:		// # wall top and bot
		case -2:		// H car body
		case -43:		// r door
		case -66:		// v door
		case -45:		// z corner road
		case -73:		// t corner road
		case -44:		// L corner, door
		case -55:		// F corner
		case -72:		// T corner, door
		case -68:		// J corner
		case 16:		// <
		case 17:		// >
			bIsTargetPixelFree = false;
			break;
		case 126:		// X exit										// клетка выхода с уровня
			bIsTargetPixelFree = true;
			system("cls");
			cout << "\n\n\n\t YOU WIN \n\n\n";
			cout << "\tYour Time: " << timer << endl << endl << endl;
			system("pause > NULL");
			bIsTargetPixelFree = true;
			bIsGameOver = true;
			break;
		default:
			bIsTargetPixelFree = true;
			break;
		}
		if (bIsTargetPixelFree)											// анимация движения героя
		{
			Pixel[iHeroX][iHeroY] = 32;									// стираем клетку там где героя был
			iHeroX = x;													// берем новые координаты героя
			iHeroY = y;
			Pixel[iHeroX][iHeroY] = 2;									// рисуем героя с новыми координатами
		}
	}
}

void Draw()																// функция отрисовки кадра в консоли
{
	COORD position;														// создаем координаты позиции курсора
	position.X = 0;														// и помещаем их в 0.0
	position.Y = 0;
	SetConsoleCursorPosition(hConsole, position);						// передаем координаты в консольное окно

	CONSOLE_CURSOR_INFO cursorInfo;										// создаем  переменную информации о курсоре
	cursorInfo.bVisible = 0;											// делаем его невидимым, чтобы убрать мерцание
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &cursorInfo);						// передаем в консольное окно

	cout << "\n\t    ** Crossy Roads  **\n\n";							// каждый цикл рисуем название игры и посимвольно поле игры
	for (int x = 0; x < W_FIELD; x++)
	{
		for (int y = 0; y < H_FIELD; y++)
		{
			switch (Pixel[x][y])
			{
			case -37:
				cout << Pixel[x][y];
				break;
			case 2:
				cout << Pixel[x][y];
				break;
			default:
				cout << Pixel[x][y];
				break;
			}
		}
		cout << endl;
	}
	finish_t = clock();
	time(&finish);
	timer_t = finish_t - start_t;
	timer = finish - start;												// высчитываем таймер в секудах от начала вызова функции Setup()
	cout << "Time: " << timer << endl;									// и отрисовываем его внизу поля
}

void Setup()															// функция начальных установок
{
	time(&start);														// запускаем таймер в секундах
	start_t = clock();													// запускаем таймер в милисекундах
	srand(time(0));
	for (int x = 0; x < W_FIELD; x++)
	{
		for (int y = 0; y < H_FIELD - 1; y++)
		{
			switch (GAME_FIELD[x][y])									// берем из константного символьного поля символы	
			{															// и меняем их на ASCII графику уже в игровом поле Pixel[][]
			case'@':
				iHeroX = x;
				iHeroY = y;
				Pixel[x][y] = 2;			// hero
				break;
			case'(':
				Pixel[x][y] = 58;			// bumper
				break;
			case')':
				Pixel[x][y] = 58;			// bumper
				break;
			case'H':
				Pixel[x][y] = -2;			// car body
				break;
			case'F':
				Pixel[x][y] = -55;			// corner
				break;
			case'T':
				Pixel[x][y] = -72;			// corner, door
				break;
			case't':
				Pixel[x][y] = -73;			// corner road
				break;
			case'L':
				Pixel[x][y] = -44;			// corner, door
				break;
			case'z':
				Pixel[x][y] = -45;			// corner road
				break;
			case'J':
				Pixel[x][y] = -68;			// corner
				break;
			case'I':
				Pixel[x][y] = -70;			// wall left and right
				break;
			case'#':
				Pixel[x][y] = -51;			// wall top and bot
				break;
			case'r':
				Pixel[x][y] = -43;			// door
				break;
			case'v':
				Pixel[x][y] = -66;			// door
				break;
			case'>':
				Pixel[x][y] = 16;			// road direction
				break;
			case'<':
				Pixel[x][y] = 17;			// road direction
				break;
			case'X':
				Pixel[x][y] = 126;			// ~ exit
				break;
			default:
				Pixel[x][y] = 32;			// space
				break;
			}
		}
	}
}

void Input()															// функция ввода клавиш управления
{
	if (_kbhit()) {														// если клавиша нажата
		switch (_getch()) {												// подбираем ее методом _getch()
		case 'a':
			iHeroDirX = 0;
			iHeroDirY = -1;
			MoveHeroTo(iHeroDirX + iHeroX, iHeroDirY + iHeroY);			// в зависимости какая клавиша была нажата, вызываем функцию MoveHeroTo с координатами вектора движения
			break;
		case 'd':
			iHeroDirX = 0;
			iHeroDirY = 1;
			MoveHeroTo(iHeroDirX + iHeroX, iHeroDirY + iHeroY);
			break;
		case 'w':
			iHeroDirX = -1;
			iHeroDirY = 0;
			MoveHeroTo(iHeroDirX + iHeroX, iHeroDirY + iHeroY);
			break;
		case 's':
			iHeroDirX = 1;
			iHeroDirY = 0;
			MoveHeroTo(iHeroDirX + iHeroX, iHeroDirY + iHeroY);
			break;
		case 'x':														// клавиша х завершает игру
			system("cls");
			cout << "\n\n\n\t GAME OVER \n\n\n";
			cout << "\tYour Time: " << timer << endl << endl << endl;
			system("pause > NULL");
			bIsGameOver = true;
			break;
		case 'p':														// клавиша р останавливает игру
			system("pause > NULL");
			break;
		}
	}
}