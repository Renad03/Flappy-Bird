#include <iostream>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;
#include "SFML/Graphics.hpp"
	int main() {
		sf::RenderWindow window(sf::VideoMode(509,768),"Flappy Bird");
		sf::Event e;
		int x = 0;
		Texture bird, wall, pipe, menu;
		bird.loadFromFile("C:/Users/renad/source/repos/Flappy Bird/Flappy Bird/photos/kindpng_1685720.png");
		wall.loadFromFile("C:/Users/renad/source/repos/Flappy Bird/Flappy Bird/photos/wp6957163-flappy-bird-wallpapers.png");
		menu.loadFromFile("C:/Users/renad/source/repos/Flappy Bird/Flappy Bird/photos/pngkit_flappy-bird-png_1515677.png");
			Sprite Fbird, background, Menu;
			Fbird.setTexture(bird);
			Fbird.setTextureRect(IntRect(x*144, 1*97, 144, 97));
			Fbird.setPosition(200, 400);
			Fbird.setScale(0.5, 0.5);
			background.setTexture(wall);
			Menu.setTexture(menu);
		

		while (window.isOpen()) 
		{
			Event event;
			while (window.pollEvent(e)) 
			{
				if (e.type == sf::Event::Closed)
					window.close();

				

			}
			if (Mouse::isButtonPressed(Mouse::Left)) 
			{
				Vector2i mousepos = Mouse::getPosition(window);
				if (mousepos.x > 50 && mousepos.x < 220 && mousepos.y > 620 && mousepos.y < 750) {
					window.close();
				}
			}



			if (Keyboard::isKeyPressed(Keyboard::Space)) 
			{
				Fbird.move(0, -0.3);
				x++;
				x %= 4;
				Fbird.setTextureRect(IntRect(x * 144, 1*97, 144, 97));
				
			}
			
			window.clear();
			window.draw(background);
			window.draw(Fbird);
			window.draw(Menu);
			window.display();
		}
		 

			
			
		
	return 0;
}