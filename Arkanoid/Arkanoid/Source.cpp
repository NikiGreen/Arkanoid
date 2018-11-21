//#include "JM.h"
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace sf;

void menu(RenderWindow & window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images/111.png");
	menuTexture2.loadFromFile("images/222.png");
	menuTexture3.loadFromFile("images/333.png");
	aboutTexture.loadFromFile("images/about.png");
	menuBackground.loadFromFile("images/Penguins.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);
	menuBg.setPosition(345, 0);

	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
	////////////////////////////////////////////////////
}

int main()
{
	srand(time(0));
	int Lives = 5, Scoure = 0;
	RenderWindow app(VideoMode(520, 450), "Arkanoid ver 1.1");
	menu(app);
	
	app.setFramerateLimit(60);

	
	
	Font font;//шрифт 
	font.loadFromFile("images/12583.otf");
	Text text;//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый

	text.setPosition(5,5 );//задаем позицию текста, центр камеры
	text.setCharacterSize(15);
	text.setFont(font);
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

	while (app.isOpen() && !Keyboard::isKeyPressed(Keyboard::Escape))//При открытии окна
	{
		text.setString("Lives:" + std::to_string(Lives));//задает строку тексту
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
				block[i].setPosition(-100, 0); dx = -dx;
			}

		y += dy;
		for (int i = 0; i<n; i++)
			if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
			{
				block[i].setPosition(-100, 0); dy = -dy;
			}
		//}
		if (x<0 || x>520)  dx = -dx;//Контроль стенок
		if (y < 0 /*|| y>450*/) {
			
			dy = -dy;
		}
		else if (y>450) {
			Lives--;
			dy = -dy;
			}

		if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(6, 0);//Реагирование на кнопки клавиатуры
		if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(-6, 0);

		if (FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds())) dy = -(rand() % 5 + 2);//реагирование шарика на платформу

		sBall.setPosition(x, y);//Сохранение позиции шарика

		app.clear();//отображение всех элементов
		
		app.draw(sBackground);
		app.draw(text);
		app.draw(sBall);
		app.draw(sPaddle);
		

		for (int i = 0; i<n; i++)
			app.draw(block[i]);

		app.display();
	}

	return 0;
}