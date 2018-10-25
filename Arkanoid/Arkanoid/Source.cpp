#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int main()
{
	srand(time(0));

	RenderWindow app(VideoMode(520, 450), "Arkanoid ver 1.1");
	app.setFramerateLimit(60);

	Texture sp1, sp2, sp3, sp4;
	sp1.loadFromFile("images/block01.png");
	sp2.loadFromFile("images/background2.jpg");
	sp3.loadFromFile("images/ball.png");
	sp4.loadFromFile("images/paddle2.png");

	Sprite sBackground(sp2), sBall(sp3), sPaddle(sp4);
	sPaddle.setPosition(260, 440);

	Sprite block[1000];//создание массива спрайтов

	int n = 0;//Придание элементам массива спрайтов загруженной текстуры блока
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			block[n].setTexture(sp1);
			block[n].setPosition(i * 43, j * 20);
			n++;
		}

	float dx = 6, dy = 5;
	float x = 300, y = 300;

	while (app.isOpen())//При открытии окна
	{
		Event e;
		while (app.pollEvent(e))//Для закрытия программы при закрытии окна
		{
			if (e.type == Event::Closed)
				app.close();
		}
		//Построение блока с блоками{
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
		if (x<0 || x>520)  dx = -dx;
		if (y<0 || y>450)  dy = -dy;

		if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(6, 0);//Реагирование на кнопки клавиатуры
		if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(-6, 0);

		if (FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds())) dy = -(rand() % 5 + 2);

		sBall.setPosition(x, y);//Сохранение позиции шарика

		app.clear();
		app.draw(sBackground);
		app.draw(sBall);
		app.draw(sPaddle);

		for (int i = 0; i<n; i++)
			app.draw(block[i]);

		app.display();
	}

	return 0;
}