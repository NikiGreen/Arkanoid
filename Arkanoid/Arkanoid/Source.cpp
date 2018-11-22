#include "Menu.h"
//#include "1.h"
//#include "MainMenu.cpp"


//#include <SFML/Graphics.hpp>
//#include <time.h>
//#include <iostream>
//using namespace sf;

//Старое место функции menu()

void Game() {
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
	Text text_lives, text_score;//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)

	text_lives.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	text_score.setStyle(sf::Text::Bold | sf::Text::Underlined);

	text_lives.setPosition(5, 5);//задаем позицию текста, центр камеры
	text_lives.setCharacterSize(15);
	text_lives.setFillColor(Color(255, 0, 0));
	text_lives.setFont(font);

	text_score.setPosition(470, 5);//задаем позицию текста, центр камеры
	text_score.setCharacterSize(15);
	text_score.setFillColor(Color(255, 215, 000));
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


		if (Lives < 4) {//исправить 4 на 1   поражение!!!
			id = false;
			if (id == false)
			{
				Text text_lives_final, text_score_final;
				text_lives_final.setStyle(sf::Text::Bold | sf::Text::Underlined);
				text_lives_final.setPosition(150, 300);//задаем позицию текста, центр камеры
				text_lives_final.setCharacterSize(30);
				text_lives_final.setFillColor(Color(255, 0, 0));

				text_lives_final.setFont(font);
				text_lives_final.setString("Lives:" + std::to_string(Lives));

				text_score_final.setStyle(sf::Text::Bold | sf::Text::Underlined);
				text_score_final.setPosition(315, 300);//задаем позицию текста, центр камеры
				text_score_final.setCharacterSize(30);
				text_score_final.setFillColor(Color(255, 215, 000));
				text_score_final.setFont(font);
				text_score_final.setString("Score:" + std::to_string(Score));
				
				
				app.clear();
				app.draw(sBackground);
				app.draw(Lose);
				app.draw(text_lives_final);
				app.draw(text_score_final);
				app.display();
				while (!Keyboard::isKeyPressed(Keyboard::Escape));
			}

			menu(app);
			Lives = 5;

		}
		else if (Score >= 100) {//Победа!!!
			id = true;
			if (id == true)
			{
				Text text_lives_final, text_score_final;
				text_lives_final.setStyle(sf::Text::Bold | sf::Text::Underlined);
				text_lives_final.setPosition(150, 300);//задаем позицию текста, центр камеры
				text_lives_final.setCharacterSize(30);
				text_lives_final.setFillColor(Color(255, 0, 0));
				text_lives_final.setFont(font);
				text_lives_final.setString("Lives:" + std::to_string(Lives));

				text_score_final.setStyle(sf::Text::Bold | sf::Text::Underlined);
				text_score_final.setPosition(315, 300);//задаем позицию текста, центр камеры
				text_score_final.setCharacterSize(30);
				text_score_final.setFillColor(Color(255, 215, 000));
				text_score_final.setFont(font);
				text_score_final.setString("Score:" + std::to_string(Score));


				app.clear();
				app.draw(sBackground);
				app.draw(Win);
				app.draw(text_lives_final);
				app.draw(text_score_final);
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
}

void AfterRunning() {
	Game();
}

int main()
{
	Game();

	return 0;
}