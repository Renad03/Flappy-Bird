#include <iostream>
#include <SFML/Audio.hpp>
#include "SFML/Graphics.hpp"
#include <vector>
#define size 9
using namespace std;
using namespace sf;
int i = 0;
float delay = 0.2f;
double timecnt = 0.01, time_for_bird_jump = 0.1;
double backgroundcnt = 1;
int upper_offset = 0;
int lower_offset = 0;
Texture upperpipe; Texture lowerpipe;
bool playhoover = 0, settingshoover = 0, exithooverInMain = 0, returnhoover = 0;
bool play = 0, menu = 1, settings = 0, loosing = 0, pause = 0;
float menu_cnt = 0, one_time_jump = 0;
void draw_pipes(RenderWindow& window, Sprite upipe[], Sprite lowpipe[], int& pipe_offset) {
	for (int e = 0; e < size; e++) {
		if (upipe[e].getPosition().x <= -500) {
			upipe[e].setPosition(Vector2f(1000 + upper_offset, -rand() % 200 + 5));
			//upper_offset += pipe_offset;
			backgroundcnt += 0.05;
		}
		if (lowpipe[e].getPosition().x <= -500) {
			lowpipe[e].setPosition(Vector2f(1000 + lower_offset, 560 + upipe[e].getPosition().y - 30));
			//lower_offset += pipe_offset;
		}
	}
	for (int k = 0; k < size; k++) {
		window.draw(upipe[k]);
		window.draw(lowpipe[k]);

		upipe[k].move(-0.15 * backgroundcnt, 0);
		lowpipe[k].move(-0.15 * backgroundcnt, 0);
	}

}
void timer(float& timer, float time) {
	if (timer > 0)
		timer -= time;
	else timer = 0;
}
void game(RenderWindow& window, bool& loosing) {
	////////////////////////////////////////sound///////////////////////////////////
	bool soundon = 1;
	SoundBuffer Wing;
	Wing.loadFromFile("./photos/sfx_wing.wav");
	Sound wing;
	wing.setBuffer(Wing);
	SoundBuffer Click;
	Click.loadFromFile("./photos/mixkit-game-click-1114.wav");
	Sound click;
	click.setBuffer(Click);
	///////////////////////////////////////menu////////////////////////////////
	VideoMode desktop = VideoMode::getDesktopMode();
	//------------------------------------------ background 
	Texture pausebck;
	pausebck.loadFromFile("./photos/background.png");
	Sprite spausebk;
	spausebk.setTexture(pausebck);
	//-------------------------------------------- start buttom
	Texture playt;
	playt.loadFromFile("./photos/play.png");
	Sprite splay;
	splay.setTexture(playt);
	splay.setPosition((pausebck.getSize().x) / 2 - 150, (pausebck.getSize().y) / 2 + 100);
	//-------------------------------------------------return
	Texture returnt;
	returnt.loadFromFile("./photos/return.png");
	Sprite returns;
	returns.setTexture(returnt);
	returns.setPosition((pausebck.getSize().x) / 2, (pausebck.getSize().y) / 2 + 100);
	//-------------------------------------------------for board
	Texture board;
	board.loadFromFile("./photos/board.png");
	Sprite sboard;
	sboard.setTexture(board);
	sboard.setScale(0.5, 0.5);
	sboard.setPosition((pausebck.getSize().x) / 2 - 200, (pausebck.getSize().y) / 2 - 80);
	RectangleShape rectms(Vector2f(20, 20));
	Mouse ms;

	///////////////////////////////////////animation//////////////////////////////////
	int anim = 0;
	int f = 500, q = 500, s = 0, y = 0;
	int pipe_offset = 165;
	Texture bird, wall1, wall2, upperpipe, lowerpipe, Ground, box;
	bird.loadFromFile("./photos/bird.png");
	wall1.loadFromFile("./photos/background (2).png");
	wall2.loadFromFile("./photos/background (2).png");
	upperpipe.loadFromFile("./photos/pipeDown2.png");
	lowerpipe.loadFromFile("./photos/pipeUp2.png");
	Ground.loadFromFile("./photos/ground.png");
	RectangleShape lowpipebox[size];
	RectangleShape upipebox[size];
	Sprite Fbird, background[2], ground, upipe[size], lowpipe[size], menu_background;
	Fbird.setTexture(bird);
	Fbird.setTextureRect(IntRect(anim * 144, 1 * 97, 144, 97));
	Fbird.setPosition(200, 400);
	Fbird.setScale(0.5, 0.5);
	RectangleShape birdsquare(Vector2f(40, 40));
	ground.setTexture(Ground);
	ground.setPosition(0, 630);
	ground.setScale(1.2, 1);
	background[0].setTexture(wall1);
	background[1].setTexture(wall2);
	menu_background.setTexture(wall1);
	bool is_jumping = false;
	int is_pressed = 0;
	for (int k = 0; k < 2; k++) {
		background[k].setPosition(Vector2f(k * 1360, 0));
	}
	for (int j = 0; j < size; j++) {
		upipe[j].setTexture(upperpipe);
		upipe[j].setScale(1, 1.3);
		upipe[j].setPosition(f, -rand() % 200 + 5); //----------------------------------random from (0 -> -250)
		f += pipe_offset;

		lowpipe[j].setTexture(lowerpipe);
		lowpipe[j].setScale(1, 1.3);
		lowpipe[j].setPosition(q, 560 + upipe[j].getPosition().y - 30);
		q += pipe_offset;
	}
	while (window.isOpen())
	{
		timer(menu_cnt, timecnt);
		timer(one_time_jump, time_for_bird_jump);
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (play && !pause) {
			loosing = 0;
			birdsquare.setPosition(Fbird.getPosition().x + 10, Fbird.getPosition().y);
			float vely = 0.0f;
			bool is_jumping = false;
			const float gravity = 0.5f;
			float jumpvelocity = -0.8;
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				if (soundon)
					//wing.play();
					is_jumping = true;
			}
			if (is_jumping) {
				is_jumping = false;
				vely = jumpvelocity;
				Fbird.move(0, vely);
			}
			else {
				vely += gravity;
				Fbird.move(0, vely);
				is_jumping = false;
			}

			if (Fbird.getPosition().y < 0) {
				Fbird.setPosition(Fbird.getPosition().x, 0);
				//loosing = 1;play = 0;
			}
			if (Fbird.getPosition().y + Fbird.getGlobalBounds().height > 620)
			{
				vely = 0;
				is_jumping = false;
				Fbird.setPosition(Fbird.getPosition().x, 620 - Fbird.getGlobalBounds().height);
				//loosing = 1;play = 0;

			}
			for (int z = 0; z < size; z++) {
				if (birdsquare.getGlobalBounds().intersects(upipe[z].getGlobalBounds()) ||
					birdsquare.getGlobalBounds().intersects(lowpipe[z].getGlobalBounds())) {
					//loosing = true;	play = false;	break;


				}
			}
			if (Fbird.getGlobalBounds().intersects(ground.getGlobalBounds())) {
				//loosing = 1;play = 0;

			}

			if (loosing) {
				play = 0;
				menu = 0;
				break;
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::P)) {
				pause = 1; play = 0;
			}
			window.clear();
			//------------------------------------------------------------------- draw background
			window.draw(background[0]);
			window.draw(background[1]);


			for (int j = 0; j < 2; j++)
			{
				background[j].move(Vector2f(-0.15 * backgroundcnt, 0));
			}

			// ----------------------------------------------------------reset background position
			if (background[0].getPosition().x <= -1365)
				background[0].setPosition(Vector2f(1300, 0));

			else if (background[1].getPosition().x <= -1365)
			{
				background[1].setPosition(Vector2f(1300, 0));
				backgroundcnt += 0.05;
			}

			//-----------------------------------------------------------------bird animation
			anim++;
			anim %= 4;
			Fbird.setTextureRect(IntRect(anim * 144, 1 * 97, 144, 97));

			//------------------------------------------------------------- draw bird
			window.draw(Fbird);// window.draw(birdsquare);
			// ----------------------------------------------------------draw pipes
			draw_pipes(window, upipe, lowpipe, pipe_offset);
			window.draw(ground);
			window.display();
		}
		else if (!play && pause)
		{
			loosing = 0;
			rectms.setPosition(ms.getPosition().x - 200, ms.getPosition().y - 30);
			if (rectms.getGlobalBounds().intersects(splay.getGlobalBounds())) {
				playhoover = 1;
				splay.setScale(1.1, 1.1);
				if (playhoover && Mouse::isButtonPressed(Mouse::Left)) {
					if (menu_cnt == 0) {
						if (soundon)
							click.play();
						pause = 0;
						play = 1;
						menu_cnt = 1;
					}
				}
			}
			else {
				playhoover = 0;
				splay.setScale(1, 1);
			}
			//-------
			if (rectms.getGlobalBounds().intersects(returns.getGlobalBounds())) {
				returnhoover = 1;
				returns.setScale(1.1, 1.1);
				if (returnhoover && Mouse::isButtonPressed(Mouse::Left)) {
					if (menu_cnt == 0) {
						if (soundon)
							click.play();
						pause = 0;
						menu = 1;
						menu_cnt = 1;
					}
					break;
				}
			}
			else {
				returnhoover = 0;
				returns.setScale(1, 1);
			}
			window.clear();
			window.draw(menu_background); window.draw(sboard); window.draw(splay); window.draw(returns); window.draw(rectms);
			window.display();
		}


	}
}
int main()
{//-----------------------------------------------main menu
	RenderWindow window(VideoMode(1000, 768), "Flappy Bird");
	Event e;
	Texture logo;
	Texture settingst;
	Texture birdyellow;
	Sprite slogo;
	Sprite ssettings;
	Sprite sbirdyellow;
	logo.loadFromFile("./photos/logo.png");
	slogo.setTexture(logo);
	slogo.setPosition(250, 100);
	settingst.loadFromFile("./photos/settings.png");
	ssettings.setTexture(settingst);
	ssettings.setPosition(440, 390);
	birdyellow.loadFromFile("./photos/bird 2.png");
	sbirdyellow.setTexture(birdyellow);
	sbirdyellow.setPosition(700, 100);
	sbirdyellow.setScale(0.3, 0.3);
	VideoMode desktop = VideoMode::getDesktopMode();
	//------------------------------------------ background 
	Texture pausebck;
	pausebck.loadFromFile("./photos/background.png");
	Sprite spausebk;
	spausebk.setTexture(pausebck);
	//-------------------------------------------- start buttom
	Texture playt;
	playt.loadFromFile("./photos/play.png");
	Sprite splay;
	splay.setTexture(playt);
	splay.setPosition((pausebck.getSize().x) / 2 - 150, (pausebck.getSize().y) / 2 + 100);
	//--------------------------------------------for exit buttom
	Texture exit;
	exit.loadFromFile("./photos/exit.png");
	Sprite sexitInMain;
	sexitInMain.setTexture(exit);
	sexitInMain.setPosition((pausebck.getSize().x) / 2, (pausebck.getSize().y) / 2 + 100);
	//-------------------------------------------------return
	Texture returnt;
	returnt.loadFromFile("./photos/return.png");
	Sprite returns;
	returns.setTexture(returnt);
	returns.setPosition((pausebck.getSize().x) / 2, (pausebck.getSize().y) / 2 + 100);
	//-------------------------------------------------for board
	Texture board;
	board.loadFromFile("./photos/board.png");
	Sprite sboard;
	sboard.setTexture(board);
	sboard.setScale(0.5, 0.5);
	sboard.setPosition((pausebck.getSize().x) / 2 - 200, (pausebck.getSize().y) / 2 - 80);
	RectangleShape rectms(Vector2f(20, 20));
	Mouse ms;

	//---------------------------------------------------------------gameover
	Texture replaybutton;
	Texture mainmenubutton;
	Texture gameoverlogo;
	Texture yellowbird;
	yellowbird.loadFromFile("./photos/yellow bird.png");
	replaybutton.loadFromFile("./photos/replay.png");
	mainmenubutton.loadFromFile("./photos/menu.png");
	gameoverlogo.loadFromFile("./photos/gameover .png");
	Sprite s_gameoverlogo;
	Sprite s_replaybutton;
	Sprite s_mainmenubutton;
	Sprite s_yellowbird;
	s_yellowbird.setTexture(yellowbird);
	int anim2 = 0;
	s_yellowbird.setTextureRect(IntRect(anim2 * 64, 1 * 48, 64, 48));
	s_yellowbird.setScale(1, 1);
	s_yellowbird.setPosition(0, 0);
	s_gameoverlogo.setTexture(gameoverlogo);
	s_replaybutton.setTexture(replaybutton);
	s_mainmenubutton.setTexture(mainmenubutton);
	s_gameoverlogo.setPosition(250, 100);
	s_replaybutton.setPosition((pausebck.getSize().x) / 2 - 150, (pausebck.getSize().y) / 2 + 100);
	s_mainmenubutton.setPosition((pausebck.getSize().x) / 2, (pausebck.getSize().y) / 2 + 100);
	int gameovercnt = 1;
	//------------------------------------------------------- sound and music
	SoundBuffer Lost;
	Lost.loadFromFile("./photos/sfx_die.wav");
	Sound lost;
	lost.setBuffer(Lost);
	SoundBuffer Fall;
	Fall.loadFromFile("./photos/sfx_hit.wav");
	Sound fall;
	fall.setBuffer(Fall);
	SoundBuffer Click;
	Click.loadFromFile("./photos/mixkit-game-click-1114.wav");
	Sound click;
	click.setBuffer(Click);
	Font foont;
	foont.loadFromFile("./photos/FlappyBirdy.ttf");
	Text sound;
	sound.setFont(foont);
	sound.setString("sound");
	sound.setScale(2, 2);
	sound.setPosition(350, 330);
	Texture On, Off;
	On.loadFromFile("./photos/on.png");
	Off.loadFromFile("./photos/off.png");
	Sprite on, off;
	on.setTexture(On);
	off.setTexture(Off);
	on.setScale(0.3, 0.3);
	off.setScale(0.3, 0.3);
	on.setPosition(500, 355);
	off.setPosition(500, 355);
	bool soundon = 1;
	
	int anim = 0;
	int f = 500, q = 500, s = 0, y = 0;
	int pipe_offset = 165;
	Texture bird, wall1, wall2, upperpipe, lowerpipe, Ground, box;
	bird.loadFromFile("./photos/bird.png");
	wall1.loadFromFile("./photos/background (2).png");
	wall2.loadFromFile("./photos/background (2).png");
	upperpipe.loadFromFile("./photos/pipeDown2.png");
	lowerpipe.loadFromFile("./photos/pipeUp2.png");
	Ground.loadFromFile("./photos/ground.png");
	RectangleShape lowpipebox[size];
	RectangleShape upipebox[size];
	Sprite Fbird, background[2], ground, upipe[size], lowpipe[size];
	Fbird.setTexture(bird);
	Fbird.setTextureRect(IntRect(anim * 144, 1 * 97, 144, 97));
	Fbird.setPosition(200, 400);
	Fbird.setScale(0.5, 0.5);
	RectangleShape birdsquare(Vector2f(40, 40));
	ground.setTexture(Ground);
	ground.setPosition(0, 630);
	ground.setScale(1.2, 1);
	background[0].setTexture(wall1);
	background[1].setTexture(wall2);

	while (window.isOpen())
	{
		timer(menu_cnt, timecnt);
		timer(one_time_jump, time_for_bird_jump);
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}
		//-------------------------------main menu-----------------------------------------------------------
		if (menu && !play) {
			gameovercnt = 1;
			anim2++;
			anim2 %= 3;
			s_yellowbird.setTextureRect(IntRect(anim2 * 64, 1 * 48, 64, 48));
			loosing = 0;
			rectms.setPosition(ms.getPosition().x - 200, ms.getPosition().y - 30);
			if (rectms.getGlobalBounds().intersects(splay.getGlobalBounds())) {
				playhoover = 1;
				splay.setScale(1.1, 1.1);
				if (playhoover && Mouse::isButtonPressed(Mouse::Left)) {
					if (menu_cnt == 0) {
						if (soundon)
							click.play();
						play = 1;
						menu = 0;
						menu_cnt = 1;
					}
				}
			}
			else {
				playhoover = 0;
				splay.setScale(1, 1);
			}
			if (rectms.getGlobalBounds().intersects(sexitInMain.getGlobalBounds())) {
				exithooverInMain = 1;
				sexitInMain.setScale(1.1, 1.1);
				if (exithooverInMain && Mouse::isButtonPressed(Mouse::Left)) {
					if (menu_cnt == 0) {
						if (soundon)
							click.play();
						window.close();
						menu_cnt = 1;
					}
				}
			}
			else {
				exithooverInMain = 0;
				sexitInMain.setScale(1, 1);
			}
			if (rectms.getGlobalBounds().intersects(ssettings.getGlobalBounds())) {
				settingshoover = 1;
				ssettings.setScale(1.1, 1.1);
				if (settingshoover && Mouse::isButtonPressed(Mouse::Left)) {
					if (menu_cnt == 0) {
						if (soundon)
							click.play();
						settings = 1;
						menu = 0;
						menu_cnt = 1;
					}
				}
			}
			else {
				settingshoover = 0;
				ssettings.setScale(1, 1);
			}


			// ----------------------------------------------------------reset background position
			if (background[0].getPosition().x <= -1365)
				background[0].setPosition(Vector2f(1365, 0));

			else if (background[1].getPosition().x <= -1365)
				background[1].setPosition(Vector2f(1365, 0));

			for (int j = 0; j < 2; j++)
			{
				background[j].move(Vector2f(-0.05, 0));
				window.draw(background[j]);
			}

			window.clear();
			window.draw(background[0]);
			window.draw(background[1]);  window.draw(sboard); window.draw(splay);
			window.draw(sexitInMain); window.draw(ssettings); window.draw(slogo); window.draw(sbirdyellow); window.draw(rectms);
			window.display();
		}
		//--------------------------------settings-----------------------------------------------------------
		else if (settings && !menu) {
			rectms.setPosition(ms.getPosition().x - 200, ms.getPosition().y - 30);
			if (rectms.getGlobalBounds().intersects(returns.getGlobalBounds())) {
				returnhoover = 1;
				returns.setScale(1.1, 1.1);
				if (returnhoover && Mouse::isButtonPressed(Mouse::Left)) {
					if (menu_cnt == 0) {
						if (soundon)
							click.play();
						settings = 0;
						menu = 1;
						menu_cnt = 1;
					}
				}
			}
			else {
				returnhoover = 0;
				returns.setScale(1, 1);
			}
			if (rectms.getGlobalBounds().intersects(on.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && soundon) {
				if (menu_cnt == 0) {
					if (soundon)
						click.play();
					soundon = 0;	menu_cnt = 1;
				}
			}

			if (rectms.getGlobalBounds().intersects(off.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && soundon == 0)
			{
				if (menu_cnt == 0) {
					if (soundon)
						click.play();
					soundon = 1; menu_cnt = 1;
				}
			}
			// ----------------------------------------------------------reset background position
			if (background[0].getPosition().x <= -1365)
				background[0].setPosition(Vector2f(1365, 0));

			else if (background[1].getPosition().x <= -1365)
				background[1].setPosition(Vector2f(1365, 0));

			for (int j = 0; j < 2; j++)
			{
				background[j].move(Vector2f(-0.05, 0));
				window.draw(background[j]);
			}

			window.clear();
			window.draw(background[0]);
			window.draw(background[1]); window.draw(sboard); window.draw(returns);
			if (soundon)
				window.draw(on);
			else window.draw(off);
			window.draw(sound); window.draw(slogo); window.draw(sbirdyellow); window.draw(rectms);
			window.display();
		}
		//-------------------------------game over-----------------------------------------------------------
		else if (loosing && !play && !menu) {
			anim2++;
			anim2 %= 3;
			s_yellowbird.setTextureRect(IntRect(anim2 * 790, 1 * 319, 790, 319));
			if (gameovercnt == 1) {
				if (soundon)
				{
					lost.play();
					fall.play();
				}
				gameovercnt = 0;
			}



			rectms.setPosition(ms.getPosition().x - 200, ms.getPosition().y - 30);
			if (rectms.getGlobalBounds().intersects(s_replaybutton.getGlobalBounds())) {
				playhoover = 1;
				s_replaybutton.setScale(1.1, 1.1);
				if (playhoover && Mouse::isButtonPressed(Mouse::Left)) {
					if (menu_cnt == 0) {
						if (soundon)
							click.play();
						loosing = 0;
						play = 1;
						menu = 0;
						menu_cnt = 1;
					}
				}
			}
			else {
				playhoover = 0;
				s_replaybutton.setScale(1, 1);
			}
			if (rectms.getGlobalBounds().intersects(s_mainmenubutton.getGlobalBounds())) {
				returnhoover = 1;
				s_mainmenubutton.setScale(1.1, 1.1);
				if (returnhoover && Mouse::isButtonPressed(Mouse::Left)) {
					if (menu_cnt == 0) {
						if (soundon)
							click.play();
						loosing = 0;
						menu = 1;
						menu_cnt = 1;
					}
				}
			}
			else {
				returnhoover = 0;
				s_mainmenubutton.setScale(1, 1);
			}
			// ----------------------------------------------------------reset background position
			if (background[0].getPosition().x <= -1365)
				background[0].setPosition(Vector2f(1365, 0));

			else if (background[1].getPosition().x <= -1365)
				background[1].setPosition(Vector2f(1365, 0));

			for (int j = 0; j < 2; j++)
			{
				background[j].move(Vector2f(-0.05, 0));
				window.draw(background[j]);
			}

			window.clear();
			window.draw(background[0]);
			window.draw(background[1]);  window.draw(sboard); window.draw(s_replaybutton);
			window.draw(s_mainmenubutton); window.draw(s_gameoverlogo); window.draw(sbirdyellow); window.draw(rectms);
			window.display();
		}
		//-----------------------------------game------------------------------------------------------------
		else if (play && !menu)
		{
			gameovercnt = 1;
			game(window, loosing);
		}
	}
}