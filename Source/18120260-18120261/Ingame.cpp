#include "Ingame.h"

cIngame::cIngame()
{
}

cIngame::cIngame(int w, int h)
{
	up1 = 'w';	down1 = 's';
	up2 = 'i'; down2 = 'k';
	score1 = 0; score2 = 0;
	width = w;
	height = h;
	cBall ballTemp(width / 2, (height +4)/ 2); // khoi tao bong o vi tri giua san choi
	ball = ballTemp;
	cBar p1Temp(1, (height - 2) / 2, (height + 10) / 2);  // khoi tao thanh p1
	p1 = p1Temp;
	cBar p2Temp(width - 2, (height - 2) / 2, (height + 10) / 2);//khoi tao thanh p2
	p2 = p2Temp;
	quit = 0;
	this->n = 10;
	//foody = new cFood[n];
	for (int i = 0; i < n; i++) {
		foody[i].color = i + 1;
	}
}
bool cIngame::getQuit()
{
	return quit;
}
void cIngame::draw()
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (ball.getX() == j && ball.getY() == i)//ve ball
			{
				gotoXY(j, i);
				cout << "o";  
			}
			else if (j == 1 && i >= p1.gety1() && i <= p1.gety2())//ve thanh p1
			{
				gotoXY(j, i);
				cout << "\xDB";
			}
			else if (j == width -2  && i >= p2.gety1() && i <= p2.gety2())// ve thanh p2
			{
				gotoXY(j, i);
				cout << "\xDB";
			}
		}
	drawFood();

	gotoXY((consolewidth - 24)/2, 0);//den vi tri tren cung giua console
	cout << "score p1:" << score1 << " - " << "score p2:" << score2;
}
void cIngame::Input()
{
	Sleep(ball.getSleep());
	gotoXY(ball.getX(), ball.getY());//den vi tri de xoa ball cu
	cout << " ";//xoa ball
	ball.move();//ball chuyen toi vi tri moi
	//Sleep(257);

	if (_kbhit())//nhap input
	{
		char inputKey = _getch();
		if (inputKey == up1)
			if (p1.gety1() > 6)//bien tren
			{
				p1.moveup();//di len
				gotoXY(1, p1.gety2() + 1);//xoa vi tri cu
				cout << " ";
			}
		if (inputKey == up2)
			if (p2.gety1() > 6)//bien tren
			{
				p2.moveup();//di len
				gotoXY(width -2, p2.gety2() + 1);//xoa vi tri cu
				cout << " ";
			}
		if (inputKey == down1)
			if (p1.gety2() < height - 2)//bien duoi
			{
				p1.movedown();//di xuong
				gotoXY(1, p1.gety1() - 1);//xoa vi  tri cu
				cout << " ";
			}
		if (inputKey == down2)
			if (p2.gety2() < height - 2)//bien duoi
			{
				p2.movedown();//di xuong
				gotoXY(width-2, p2.gety1() - 1);//xoa vi tri cu
				cout << " ";
			}
	}
	//Sleep(ball.getSleep());
}

void cIngame::logic()
{
	if (p1.getx() == ball.getX() - 1 && p1.gety1() <= ball.getY() && p1.gety2() >= ball.getY())//dieu kien ball cham p1
	{
		ball.hit = true;
		ball.hitBar();//ham phan xa
		ball.setnewsleep();//tang toc 10%
	}
	if (p2.getx() == ball.getX() + 1 && p2.gety1() <= ball.getY() && p2.gety2() >= ball.getY())//dieu kien ball cham p2
	{
		ball.hit = false;
		ball.hitBar();//ham phan xa
		ball.setnewsleep();//tang toc 10%
	}
	if (ball.getY() == 6 || ball.getY() == height - 2)//dieu kien ball cham tuong
	{
		ball.hitWall();//ham phan xa tuong
	}
	if (ball.getX() <= 0)//p2 thang
	{
		score2++;// tang diem p2
		cBall ballTemp(width / 2, (height + 4) / 2);//dat lai ball
		ball = ballTemp;
	}
	if (ball.getX() >= width -2)//p1 thang
	{
		score1++;//tang diem p1
		cBall ballTemp(width / 2, (height + 4) / 2);//dat lai ball
		ball = ballTemp;
	}
	if (score1 >= 15 || score2 >= 15)//dieu kien ket thuc game
	{
		quit = 1;
	}
	if (checkFood() != 0) { 
		int z = checkFood();//ham tang diem neu an duoc hoa qua
		if (ball.hit == true) score1 = score1 + foody[z].bonus;
		else score2 = score2 + foody[z].bonus;
		deleteFood(z);
		foody[z].x = random(20, 60);
		foody[z].y = random(10, 50);
		foody[z].bonus = random(1, 8);
		foody[z].color = random(2, 10);
		drawFood();
	}
}

void cIngame::endGame()
{
	system("cls");
	if (score1 >= 15)
	{
		cout << "player 1 win" << endl;
	}
	if (score2 >= 15)
	{
		cout << "player 2 win" << endl;
	}
	printCup();
	_getch();
	Sleep(4000);
}

void cIngame::playWithMan()//choi voi nguoi
{
	while (this->getQuit() == 0)
	{

		this->draw();
		this->Input();
		this->logic();
		if (this->getQuit() == 1)
		{
			this->endGame();
		}
	}
}

void cIngame::playWithCom()//choi voi may
{
	while (this->getQuit() == 0)
	{
		this->draw();
		this->Input();
		this->moveComBar();
		this->logic();
		if (this->getQuit() == 1)
		{
			this->endGame();
		}
	}
}

int cIngame::findBall()//ham tim toa do Y cua bong
{
	int ballx = ball.getX();
	int bally = ball.getY();
	int ballxspeed = ball.getXspeed();
	int ballyspeed = ball.getYspeed();
	while (ballx != width - 3)
	{
		if (bally == 6 || bally == height - 2)
		{
			ballyspeed = -ballyspeed;
		}
		ballx = ballx + ballxspeed;
		bally = bally + ballyspeed;
	}
	return bally;
}

void cIngame::moveComBar()//di chuyen thanh cua may (thanh p2)
{
	if (ball.getXspeed() > 0 && ball.getX() == width / 2 + 1)
	{
		int k = findBall();
		if (k < p2.gety1())
		{
			while (p2.gety1() != k)
			{
				p2.moveup();//di len
				gotoXY(width - 2, p2.gety2() + 1);//xoa vi tri cu
				cout << " ";
			}
		}
		else
		{
			if (k > p2.gety2())
			{
				while (p2.gety2() != k)
				{
					p2.movedown();//di xuong
					gotoXY(width - 2, p2.gety1() - 1);//xoa vi tri cu
					cout << " ";
				}
			}
			else{}//truong hop da dung vi tri
		}
	}
	else
	{
		if (ball.getXspeed() < 0 && ball.getX() == width / 2 )
		{
			int k = findBallP1();
			if (k < p1.gety1())
			{
				while (p1.gety1() != k)
				{
					p1.moveup();//di len
					gotoXY(1, p1.gety2() + 1);//xoa vi tri cu
					cout << " ";
				}
			}
			else
			{
				if (k > p1.gety2())
				{
					while (p1.gety2() != k)
					{
						p1.movedown();//di xuong
						gotoXY(1, p1.gety1() - 1);//xoa vi tri cu
						cout << " ";
					}
				}
				else {}//truong hop da dung vi tri
			}
		}
	}
}

void cIngame::drawFood()
{
	for (int k = 0; k < this->n; k++) {
		TextColor(foody[k].color);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				gotoXY(foody[k].x + i, foody[k].y + j);
				cout << char(219);
			}
		}
		TextColor(14);
		gotoXY(foody[k].x + 1, foody[k].y + 1); cout << foody[k].bonus;
	}
	TextColor(7);
}

void cIngame::deleteFood(int x)
{
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				gotoXY(foody[x].x + i, foody[x].y + j);
				cout << " ";
			}
		}
}

int cIngame::checkFood()
{
	for (int k = 0; k < this->n; k++) {
		if (ball.getX() >= foody[k].x && ball.getX() <= foody[k].x + 3 &&
			ball.getY() >= foody[k].y && ball.getY() <= foody[k].y)
		{
			//ball.hitBar();
			return k;
		}
	}
	return 0;
}

int cIngame::findBallP1()
{
	int ballx = ball.getX();
	int bally = ball.getY();
	int ballxspeed = ball.getXspeed();
	int ballyspeed = ball.getYspeed();
	while (ballx != 2)
	{
		if (bally == 6 || bally == height - 2)
		{
			ballyspeed = -ballyspeed;
		}
		ballx = ballx + ballxspeed;
		bally = bally + ballyspeed;
	}
	return bally;
}

void cIngame::printCup() //hàm in cup chiến thắng
{
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 240);
	char c = (219);
	gotoXY(38, 4);
	SetConsoleTextAttribute(hConsole, 244);
	cout << "  " << c << c << c << c;
	SetConsoleTextAttribute(hConsole, 254);
	cout << c << c << c << c << c << c << c << c << c << c << c << c << c << c;
	SetConsoleTextAttribute(hConsole, 244);
	cout << c << c << c << c;
	gotoXY(38, 5);
	cout << "  " << c << c << "  ";
	SetConsoleTextAttribute(hConsole, 254);
	cout << c << c << c << c;
	SetConsoleTextAttribute(hConsole, 252);
	cout << c << c << c << c;
	SetConsoleTextAttribute(hConsole, 254);
	cout << c << c << c << c << c << c;
	SetConsoleTextAttribute(hConsole, 244);
	cout << "  " << c << c;
	gotoXY(38, 6);
	cout << "  " << c << c << c << c << c << c;
	SetConsoleTextAttribute(hConsole, 254);
	cout << c << c << c << c;
	SetConsoleTextAttribute(hConsole, 252);
	cout << c << c;
	SetConsoleTextAttribute(hConsole, 254);
	cout << c << c << c << c;
	SetConsoleTextAttribute(hConsole, 244);
	cout << c << c << c << c << c << c;
	gotoXY(38, 7);
	cout << "      " << c << c;
	SetConsoleTextAttribute(hConsole, 254);
	cout << c << c << c << c;
	SetConsoleTextAttribute(hConsole, 252);
	cout << c << c;
	SetConsoleTextAttribute(hConsole, 254);
	cout << c << c << c << c;
	SetConsoleTextAttribute(hConsole, 244);
	cout << c << c;
	gotoXY(38, 8);
	SetConsoleTextAttribute(hConsole, 254);
	cout << "        " << c << c << c << c << c << c << c << c << c << c;
	gotoXY(38, 9);
	SetConsoleTextAttribute(hConsole, 244);
	cout << "          " << c << c << c << c << c << c;
	gotoXY(38, 10);
	cout << "            " << c << c;
	gotoXY(38, 11);
	cout << "            " << c << c;
	gotoXY(38, 12);
	cout << "          " << c << c << c << c << c << c;
	gotoXY(38, 13);
	SetConsoleTextAttribute(hConsole, 246);
	cout << "    " << c << c << c << c << c << c << c << c << c << c << c << c << c << c << c << c << c << c;
	gotoXY(38, 14);
	cout << "    " << c << c << "              " << c << c;
	gotoXY(38, 15);
	cout << "    " << c << c << "              " << c << c << c << c << c << c << c << c << c << c << c << c << c << c << c << c << c << c;
	gotoXY(38, 16);
	cout << "    " << c << c << "              " << c << c << "              " << c << c;
	gotoXY(38, 17);
	cout << "    " << c << c << "              " << c << c << "              " << c << c;
	gotoXY(38, 18);
	cout << "    " << c << c << "              " << c << c << "              " << c << c;
	gotoXY(38, 19);
	cout << "    " << c << c << "              " << c << c << "              " << c << c;
	gotoXY(38, 21);
	SetConsoleTextAttribute(hConsole, 241);
	for (int i = 1; i <= 42; i++)
	{
		cout << c;
	}
	Sleep(400);
	
}
