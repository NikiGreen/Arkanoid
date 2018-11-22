#include "Menu.h"
//#include "1.h"
//#include "MainMenu.cpp"


//#include <SFML/Graphics.hpp>
//#include <time.h>
//#include <iostream>
//using namespace sf;

//������ ����� ������� menu()

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


	Font font;//����� 
	font.loadFromFile("images/12583.otf");
	Text text_lives, text_score;//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)

	text_lives.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	text_score.setStyle(sf::Text::Bold | sf::Text::Underlined);

	text_lives.setPosition(5, 5);//������ ������� ������, ����� ������
	text_lives.setCharacterSize(15);
	text_lives.setFillColor(Color(255, 0, 0));
	text_lives.setFont(font);

	text_score.setPosition(470, 5);//������ ������� ������, ����� ������
	text_score.setCharacterSize(15);
	text_score.setFillColor(Color(255, 215, 000));
	text_score.setFont(font);
	//����� ���� �����

	Texture sp1, sp2, sp3, sp4;
	sp1.loadFromFile("images/block01.png");
	sp2.loadFromFile("images/background2.jpg");
	sp3.loadFromFile("images/ball.png");
	sp4.loadFromFile("images/paddle2.png");

	Sprite sBackground(sp2), sBall(sp3), sPaddle(sp4);
	sPaddle.setPosition(260, 440);

	Sprite block[1000];//�������� ������� ��������

	int n = 0;//�������� ��������� ������� �������� ����������� �������� ����� � �����������
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			block[n].setTexture(sp1);
			block[n].setPosition(i * 43, j * 20);
			n++;
		}

	float dx = 6, dy = 5;//����� ������
	float x = 260, y = 440;

	while (app.isOpen())//��� �������� ����
	{
		Sprite panel(WinTexture);

		/*if (id == true) {*/
		/* panel.setTexture(WinTexture);*/
		/*}
		else
		panel.setTexture(LoseTexture);*/


		if (Lives < 4) {//��������� 4 �� 1   ���������!!!
			id = false;
			if (id == false)
			{
				Text text_lives_final, text_score_final;
				text_lives_final.setStyle(sf::Text::Bold | sf::Text::Underlined);
				text_lives_final.setPosition(150, 300);//������ ������� ������, ����� ������
				text_lives_final.setCharacterSize(30);
				text_lives_final.setFillColor(Color(255, 0, 0));

				text_lives_final.setFont(font);
				text_lives_final.setString("Lives:" + std::to_string(Lives));

				text_score_final.setStyle(sf::Text::Bold | sf::Text::Underlined);
				text_score_final.setPosition(315, 300);//������ ������� ������, ����� ������
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
		else if (Score >= 100) {//������!!!
			id = true;
			if (id == true)
			{
				Text text_lives_final, text_score_final;
				text_lives_final.setStyle(sf::Text::Bold | sf::Text::Underlined);
				text_lives_final.setPosition(150, 300);//������ ������� ������, ����� ������
				text_lives_final.setCharacterSize(30);
				text_lives_final.setFillColor(Color(255, 0, 0));
				text_lives_final.setFont(font);
				text_lives_final.setString("Lives:" + std::to_string(Lives));

				text_score_final.setStyle(sf::Text::Bold | sf::Text::Underlined);
				text_score_final.setPosition(315, 300);//������ ������� ������, ����� ������
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
		else if (Keyboard::isKeyPressed(Keyboard::Escape)) //�����!!!
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
		text_lives.setString("Lives:" + std::to_string(Lives));//������ ������ ������
		text_score.setString("Score:" + std::to_string(Score));
		Event e;
		while (app.pollEvent(e))//��� ����� ������
		{
			if (e.type == Event::Closed)//��� �������� ��������� ��� �������� ����
				app.close();
		}
		//�������� ������������ ������ � ����{
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
		if (x<0 || x>520)  dx = -dx;//�������� ������
		if (y < 0 /*|| y>450*/) {

			dy = -dy;
		}
		else if (y>450) {//������� ���������
			Lives--;
			dy = -dy;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(/*6*/8, 0);//������������ �� ������ ����������
		if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(/*-6*/-8, 0);

		if (FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds())) dy = -(rand() % 5 + 2);//������������ ������ �� ���������

		sBall.setPosition(x, y);//���������� ������� ������

		app.clear();//����������� ���� ���������

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