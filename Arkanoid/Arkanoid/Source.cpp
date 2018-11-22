//#include "MainMenu.cpp"
//#include "JM.h"

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace sf;

void menu(RenderWindow & window) {
	Font first_font;//шрифт 
	Texture menuTitleTexture,menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTitleTexture.loadFromFile("images/Title3.png");
	menuTexture1.loadFromFile("images/Button_PlayGame.png");
	menuTexture2.loadFromFile("images/Button_About.png");
	menuTexture3.loadFromFile("images/Button_Exit.png");
	aboutTexture.loadFromFile("images/ABOUT2.png");
	menuBackground.loadFromFile("images/background.jpg");
	Sprite menuTitle(menuTitleTexture),menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;

	menuTitle.setPosition(-40, -150);
	menu1.setPosition(/*100*/150, /*30*/190);
	menu2.setPosition(150, /*90*/250);
	menu3.setPosition(150, /*150*/310);
	menuBg.setPosition(0, 0);


	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(/*100*/150, /*30*/190, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(/*100*/150, /*90*/250, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(/*100*/150, /*150*/310, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) {
				isMenu = false;
				
			}//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menuTitle);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
	////////////////////////////////////////////////////
}


//void LosePanel(RenderWindow & window1) {
//	Font first_font1;//шрифт 
//	Texture menuTitleTexture1, menuTexture11, menuBackground1;
//	menuTitleTexture1.loadFromFile("images/YouWon.png");
//	menuTexture11.loadFromFile("images/InMenu.png");
//	menuBackground1.loadFromFile("images/background4.jpg");
//	Sprite menuTitle1(menuTitleTexture1), menu11(menuTexture11), menuBg1(menuBackground1);
//	
//	bool isMenu1;
//
//		isMenu1 = 1;
//	int menuNum1 = 0;
//
//	menuTitle1.setPosition(-10, -130);
//
//	menu11.setPosition(/*100*/150, /*30*/190);
//
//	menuBg1.setPosition(0, 0);
//
//
//	//////////////////////////////МЕНЮ///////////////////
//	while (isMenu1)
//	{
//
//		menu11.setColor(Color::White);
//		menuNum1 = 0;
//		window1.clear(Color(129, 181, 221));
//
//		if (IntRect(/*100*/150, /*30*/190, 300, 50).contains(Mouse::getPosition(window1))) { menu11.setColor(Color::Blue); menuNum1 = 1; }
//
//		if (Mouse::isButtonPressed(Mouse::Left))
//		{
//			if (menuNum1 == 1) {
//				isMenu1 = false;
//				id = true;
//				/*isMenu = false;*/
//			}
//			
//			//если нажали первую кнопку, то выходим из меню 
//		}
//			window1.draw(menuBg1);
//			window1.draw(menuTitle1);
//			window1.draw(menu11);
//
//			window1.display();
//		
//		////////////////////////////////////////////////////
//	}
//}


int main()
{
	bool id = false;
	srand(time(0));
	int Lives = 5, Score = 0; int ifi = 0;
	RenderWindow app(VideoMode(520, 450), "Arkanoid ver 1.1");
	menu(app);
	
	app.setFramerateLimit(60);



	Texture LoseTexture, WinTexture;
	LoseTexture.loadFromFile("images/YouLost.png");
	WinTexture.loadFromFile("images/YouWon.png");
	Sprite Lose(LoseTexture), Win(WinTexture);
	

	Font font;//шрифт 
	font.loadFromFile("images/12583.otf");
	Text text_lives,text_score;//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)

	text_lives.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	text_score.setStyle(sf::Text::Bold | sf::Text::Underlined);

	text_lives.setPosition(5,5 );//задаем позицию текста, центр камеры
	text_lives.setCharacterSize(15);
	text_lives.setFont(font);

	text_score.setPosition(470, 5);//задаем позицию текста, центр камеры
	text_score.setCharacterSize(15);
	text_score.setFont(font);
	//рисую этот текст

	Texture sp1, sp2, sp3, sp4;
	sp1.loadFromFile("images/block01.png");
	sp2.loadFromFile("images/background2.jpg");
	sp3.loadFromFile("images/ball.png");
	sp4.loadFromFile("images/paddle2.png");

	Sprite sBackground(sp2), sBall(sp3), sPaddle(sp4);
	sPaddle.setPosition(260, 440);

	Sprite block[1000];//создание массива спрайтов

	int n = 0;//Придание элементам массива спрайтов загруженной текстуры блока и выстраиваем
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			block[n].setTexture(sp1);
			block[n].setPosition(i * 43, j * 20);
			n++;
		}

	float dx = 6, dy = 5;//старт шарика
	float x = 260, y = 440;

	while (app.isOpen())//При открытии окна
	{
		Sprite panel(WinTexture);

		/*if (id == true) {*/
			/* panel.setTexture(WinTexture);*/
		/*}
		else
			 panel.setTexture(LoseTexture);*/


		if (Lives < 5 ) {//исправить 4 на 1   поражение!!!
			id = false;
			if(id==false)
			{
				app.clear();
				app.draw(sBackground);
				app.draw(Lose);
				app.display(); 
				while (!Keyboard::isKeyPressed(Keyboard::Escape));
			}
			
			menu(app);
			Lives = 5;
			
		}
		else if (Score>=100) {//Победа!!!
			id = true;
			if (id == true)
			{
				app.clear();
				app.draw(sBackground);
				app.draw(Win);
				app.display();
				while (!Keyboard::isKeyPressed(Keyboard::Escape));
			}
			menu(app);
			
		}
		else if (Keyboard::isKeyPressed(Keyboard::Escape)) //Выход!!!
		{
			/*id = false;
			if (id == false)
			{
				app.clear();
				app.draw(sBackground);
				app.draw(Lose);
				app.display();
				while (!Keyboard::isKeyPressed(Keyboard::Escape));
			}*/
			menu(app);
			
		}
								
		
		

		text_lives.setString("Lives:" + std::to_string(Lives));//задает строку тексту
		text_score.setString("Score:" + std::to_string(Score));
		Event e;
		while (app.pollEvent(e))//Для ловли ивента
		{
			if (e.type == Event::Closed)//Для закрытия программы при закрытии окна
				app.close();
		}
		//контроль столкновения блоков и шара{
		x += dx;
		for (int i = 0; i<n; i++)
			if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
			{
				block[i].setPosition(-100, 0); dx = -dx; Score++;
			}

		y += dy;
		for (int i = 0; i<n; i++)
			if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
			{
				block[i].setPosition(-100, 0); dy = -dy; Score++;
			}
		//}
		if (x<0 || x>520)  dx = -dx;//Контроль стенок
		if (y < 0 /*|| y>450*/) {
			
			dy = -dy;
		}
		else if (y>450) {//Сделать поражение
			Lives--;
			dy = -dy;
			}
		
		if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(/*6*/8, 0);//Реагирование на кнопки клавиатуры
		if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(/*-6*/-8, 0);

		if (FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds())) dy = -(rand() % 5 + 2);//реагирование шарика на платформу

		sBall.setPosition(x, y);//Сохранение позиции шарика

		app.clear();//отображение всех элементов
		
		app.draw(sBackground);
		app.draw(text_lives);
		app.draw(text_score);
		app.draw(sBall);
		app.draw(sPaddle);
		

		for (int i = 0; i<n; i++)
			app.draw(block[i]);

		app.display();
	}

	return 0;
}