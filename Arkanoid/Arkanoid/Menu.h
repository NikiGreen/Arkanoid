#pragma once

#ifndef  _menu_H_
#define _menu_H_
#include"1.h"
int cout = 0;
bool new1 = false;
//#include <SFML/Graphics.hpp>
//#include <time.h>
//#include <iostream>
//using namespace sf;
 void menu(RenderWindow & window) {
	 
	Font first_font;//шрифт 
	Texture menuTitleTexture, menuTexture0, menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTitleTexture.loadFromFile("images/Title3.png");
	menuTexture0.loadFromFile("images/Button_Resume.png");
	menuTexture1.loadFromFile("images/Button_NewGame.png");
	menuTexture2.loadFromFile("images/Button_About.png");
	menuTexture3.loadFromFile("images/Button_Exit.png");
	aboutTexture.loadFromFile("images/ABOUT2.png");
	menuBackground.loadFromFile("images/background.jpg");
	Sprite menuTitle(menuTitleTexture), menu0(menuTexture0), menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;

	menuTitle.setPosition(-40, -150);
	if (cout != 0) {
		menu0.setPosition(/*100*/150, /*30*/130);
	}else
		menu0.setPosition(/*100*/1000, /*30*/1000);
	menu1.setPosition(/*100*/150, /*30*/190);
	menu2.setPosition(150, /*90*/250);
	menu3.setPosition(150, /*150*/310);
	menuBg.setPosition(0, 0);


	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menu0.setColor(Color::White);
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(/*100*/150, /*30*/130, 300, 50).contains(Mouse::getPosition(window))) { menu0.setColor(Color::Blue); menuNum = 0; }

		if (IntRect(/*100*/150, /*30*/190, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(/*100*/150, /*90*/250, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(/*100*/150, /*150*/310, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 0){
				if (cout != 0) {
					new1 = false;
					isMenu = false;
				}
				
					 
			}

			if (menuNum == 1) {
				if (cout != 0) {
					new1 = true;					
				}				
				isMenu = false;
				cout++;

			}//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menuTitle);
		window.draw(menu0);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
	////////////////////////////////////////////////////
}

#endif
