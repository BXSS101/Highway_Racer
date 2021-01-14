#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Collision.h"
#include <Windows.h>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;
using namespace sf;
using namespace Collision;


int main(int argc, char** argv) {
	bool menuState = true, startState = false, howState = false, gameState = false, exitState = false, overState = false, afterOver = false;
	RenderWindow window(VideoMode(854, 480), "Highway Racer");
	window.setFramerateLimit(60);
	//Window Icon
	Image Icon;
	Icon.loadFromFile("resource/car-player.png");
	window.setIcon(96, 128, Icon.getPixelsPtr());
	//Main Wallpaper
	Texture mainTexture;
	mainTexture.loadFromFile("resource/Home Backdrop.png");
	Sprite mainWall(mainTexture);
	mainWall.setPosition(0, 0);
	//Start Button
	Texture startTexture;
	startTexture.loadFromFile("resource/start-sheet.png");
	IntRect rectStart(0, 0, 200, 80);
	Sprite startButton(startTexture, rectStart);
	startButton.setPosition(327, 250);
	//How button
	Texture howTexture;
	howTexture.loadFromFile("resource/how-sheet.png");
	IntRect rectHow(0, 0, 200, 80);
	Sprite howButton(howTexture, rectHow);
	howButton.setPosition(327, 340);
	//Cars Player + Enemy
	Texture enemyTexture;
	enemyTexture.loadFromFile("resource/car-enemy.png");
	Sprite enemyCar(enemyTexture);
	enemyCar.setPosition(146, 0);
	Vector2f enemyPosition = enemyCar.getPosition();
	Texture playerTexture;
	playerTexture.loadFromFile("resource/car-player.png");
	Sprite playerCar(playerTexture);
	playerCar.setPosition(289, 340);
	//In Game obstacle
	Texture coinTexture;
	coinTexture.loadFromFile("resource/coin.png");
	Sprite coin(coinTexture);
	//coin.setPosition(146, 0);
	Texture gasTexture;
	gasTexture.loadFromFile("resource/gas-can.png");
	Sprite gas(gasTexture);
	//gas.setPosition(146, 0);
	int gasCount = 0;
	int coinCount = 0;
	//Road + lines
	Texture roadTexture;
	roadTexture.loadFromFile("resource/road.png");
	Sprite roadWall(roadTexture);
	roadWall.setPosition(0, 0);

	Texture lineTexture;
	lineTexture.loadFromFile("resource/road-line.png");
	Sprite roadLineA(lineTexture);
	Sprite roadLineB(lineTexture);
	//Game Frame
	Texture frameTexture;
	frameTexture.loadFromFile("resource/game-frame.png");
	Sprite frame(frameTexture);
	frame.setPosition(0, 0);
	//How Screen
	Texture howpageTexture;
	howpageTexture.loadFromFile("resource/howtoplay.png");
	Sprite how(howpageTexture);
	how.setPosition(0, 0);
	//Game Over Screen
	Texture overTexture;
	overTexture.loadFromFile("resource/game-over.png");
	Sprite gameOver(overTexture);
	gameOver.setOrigin(369, 208);
	gameOver.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	//Font
	Font scoreFont;
	scoreFont.loadFromFile("resource/OCRAEXT.TTF");
	//Score Text
	Text scoreText;
	string scoreString;
	scoreText.setFont(scoreFont);
	scoreText.setPosition(690, 60);
	long score;
	//Over Text
	Text overText;
	overText.setFont(scoreFont);
	overText.setString("Press ENTER to continue.");
	overText.setPosition(225, 400);
	overText.setFillColor(Color(252, 165, 3, 200));
	//Name Text
	Text nameText;
	nameText.setFont(scoreFont);
	nameText.setString("Enter your name.");
	nameText.setPosition(280, 160);
	//Fuel Bar
	float FUEL = 1000;
	RectangleShape fuelBar(Vector2f(FUEL / 6.6357, 25));
	fuelBar.setFillColor(Color(252, 165, 3, 255));
	fuelBar.setPosition(683, 419);
	//Player Name Input
	RectangleShape nameBar;
	nameBar.setSize(Vector2f(300.0f, 70.0f));
	nameBar.setOrigin(Vector2f(150.0f, 35.0f));
	nameBar.setPosition(Vector2f(427.0f, 240.0f));
	char last_char = ' ';
	string input;
	Font font;
	font.loadFromFile("resource/OCRAEXT.TTF");
	Text text;
	text.setFont(font);
	text.setCharacterSize(48);
	text.setFillColor(Color::Black);
	text.setPosition(277, 205);
	RectangleShape cursor;
	cursor.setSize(sf::Vector2f(5.0f, 64.0f));
	cursor.setOrigin(sf::Vector2f(2.5f, 32.0f));
	cursor.setPosition(sf::Vector2f(282, 240.0f));
	cursor.setFillColor(sf::Color::Red);
	float totalTime = 0;
	Clock clock;
	bool state = false;
	//File Reader PTR
	FILE *fp;
	char str[30];
	int rankCheck,ranking;
	//Sound
	Music BGmusic;
	BGmusic.openFromFile("resource/Blues_Infusion.ogg");
	BGmusic.play();
	BGmusic.setVolume(70.f);
	//coin Collect Sound
	SoundBuffer coinBuffer;
	coinBuffer.loadFromFile("resource/coin.ogg");
	Sound coinCollect(coinBuffer);
	coinCollect.setVolume(100.f);
	//Game time
	Clock timer;
	
	while (window.isOpen()) {
		Event myevent;
		Time timeSinceLastUpdate = Time::Zero;
		timer.getElapsedTime().asSeconds();
		enemyPosition = enemyCar.getPosition();
		if (Collision::PixelPerfectTest(enemyCar, playerCar)) {
			cout << "game over : crashed\n";
			gameState = false;
			overState = true;
		}
		while (window.pollEvent(myevent)) {
			if (myevent.type == myevent.Closed || myevent.key.code == Keyboard::Escape) window.close();
			if (myevent.key.code == Keyboard::M) {
				menuState = true;
				startState = false;
				howState = false;
				gameState = false;
				exitState = false;
				overState = false;
				afterOver = false;
			}
			if (window.isOpen()) {
				if (menuState == true) {
					//cout << "Menu State : TRUE\n";
					afterOver = false;
					score = 0;
					coinCount = 1;
					gasCount = 1;
					FUEL = 1000;
					startButton.setColor(Color::White);
					howButton.setColor(Color::White);
					mainWall.setColor(Color::White);
					scoreText.setFillColor(Color(252, 165, 3, 0));
					roadLineA.setPosition(0, 0);
					roadLineB.setPosition(0, -480);
					if (myevent.type == Event::EventType::KeyPressed) {
						if (myevent.key.code == Keyboard::X) {
							menuState = false;
							gameState = true;
						}
					}
					if (Mouse::getPosition(window).x > 327 && Mouse::getPosition(window).x < 527 && Mouse::getPosition(window).y > 250 && Mouse::getPosition(window).y < 330) {
						if (rectStart.left == 0) {
							rectStart.left += 200;
						}
						if (Mouse::isButtonPressed(Mouse::Button::Left)) {
							menuState = false;
							//gameState = true;
							startState = true;
						}
					}
					else rectStart.left = 0;
					if (Mouse::getPosition(window).x > 327 && Mouse::getPosition(window).x < 527 && Mouse::getPosition(window).y > 340 && Mouse::getPosition(window).y < 420) {
						if (rectHow.left == 0) {
							rectHow.left += 200;
						}
						if (Mouse::isButtonPressed(Mouse::Button::Left)) {
							menuState = false;
							//gameState = true;
							howState = true;
						}
					}
					else rectHow.left = 0;

					startButton.setTextureRect(rectStart);
					howButton.setTextureRect(rectHow);
				}
				if (menuState == false) {
					//cout << "Menu State : FALSE\n";
					startButton.setColor(Color::Transparent);
					howButton.setColor(Color::Transparent);
					mainWall.setColor(Color::Transparent);
				}
				if (startState == true) {
					nameBar.setFillColor(Color::White);
					text.setFillColor(Color::Black);
					window.clear(Color::Black);
					scoreText.setFillColor(Color(252, 165, 3, 0));
					nameText.setFillColor(Color(252, 165, 3, 200));
					coinCount = 1;
					gasCount = 1;
					//mainWall.setColor(Color::White);
					if (myevent.type == Event::EventType::TextEntered) {
						if (last_char != myevent.text.unicode && myevent.text.unicode == 8 && input.length() > 0) {
							last_char = myevent.text.unicode;
							input.erase(input.length() - 1);
							text.setString(input);
							cursor.setPosition(277.0f + text.getGlobalBounds().width + 5, 240.0f);
							cout << input << endl;
						}
						else if (last_char != myevent.text.unicode && (myevent.text.unicode >= 'a' && myevent.text.unicode <= 'z' || myevent.text.unicode >= 'A' && myevent.text.unicode <= 'Z' || myevent.text.unicode >= '0' && myevent.text.unicode <= '9')) {
							last_char = myevent.text.unicode;
							input += myevent.text.unicode;
							text.setString(input);
							cursor.setPosition(277.0f + text.getGlobalBounds().width + 5, 240.0f);
							cout << input << endl;
						}
					}
					if (myevent.type == Event::EventType::KeyReleased && last_char != ' ') {
						last_char = ' ';
					}
					/*totalTime += clock.restart().asSeconds();
					if (totalTime >= 0.5)
					{
						totalTime = 0;
						state = !state;
					}
					if (state == true)
					{
						cursor.setFillColor(Color::Red);
					}
					else cursor.setFillColor(Color::Transparent);*/
					if (myevent.type == Event::EventType::KeyPressed) {
						if (myevent.key.code == Keyboard::Enter) {
							startState = false;
							gameState = true;
						}
					}
				}
				if (startState == false) {
					nameBar.setFillColor(Color::Transparent);
					text.setFillColor(Color::Transparent);
					cursor.setFillColor(Color::Transparent);
					nameText.setFillColor(Color(252, 165, 3, 0));
					//mainWall.setColor(Color::Transparent);
				}
				if (gameState == true) {
					//cout << "Game State : TRUE\n";
					scoreText.setFillColor(Color(252, 165, 3, 255));
					fuelBar.setFillColor(Color(252, 165, 3, 255));
					enemyCar.setColor(Color::White);
					playerCar.setColor(Color::White);
					roadLineA.setColor(Color::White);
					roadLineB.setColor(Color::White);
					roadWall.setColor(Color::White);
					frame.setColor(Color::White);
					coin.setColor(Color::White);
					gas.setColor(Color::White);
					scoreText.setPosition(690, 60);
					gasCount++;
					coinCount++;
					///////////////////////////////////////////////
					cout << "COIN : " << coinCount << endl;
					cout << "GAS : " << gasCount << endl;
					//enemyCar.move(Vector2f(0.f, 10.f));
					//Sleep(25);
					//cout << "Moving\n";
					//score += 5;
					
					
					//scoreText.setOrigin(scoreText.getScale().x / 2, scoreText.getScale().y / 2);
					cout << input << " ";
					cout << "Score :" << score << endl;
					
					if (myevent.key.code == sf::Keyboard::Left) {
						if (playerCar.getPosition().x > 119) {
							playerCar.move(Vector2f(-10.f, 0.f));
							cout << "Player 1 Move left\n";
						}
						else playerCar.move(Vector2f(10.f, 0.f));
					}
					if (myevent.key.code == Keyboard::Right) {
						if (playerCar.getPosition().x < 552 - 96) {
							playerCar.move(Vector2f(10.f, 0.f));
							cout << "Player 1 Move right\n";
						}
						else playerCar.move(Vector2f(-10.f, 0.f));
					}
					if (myevent.key.code == Keyboard::Down) {
						if (playerCar.getPosition().y < 480 - 128) {
							playerCar.move(Vector2f(0.f, 10.f));
							cout << "Player 1 Move down\n";
						}
						else playerCar.move(Vector2f(0.f, -10.f));
					}
					if (myevent.key.code == Keyboard::Up) {
						if (playerCar.getPosition().y > 0) {
							playerCar.move(Vector2f(0.f, -10.f));
							cout << "Player 1 Move up\n";
						}
						else playerCar.move(Vector2f(0.f, 10.f));
					}
					if (Collision::PixelPerfectTest(enemyCar, playerCar)) {
						cout << "game over : crashed\n";
						gameState = false;
						overState = true;
					}
					if (Collision::PixelPerfectTest(gas, playerCar)) {
						cout << "GAS Refilled\n";
						FUEL = 1000;
						coinCollect.play();
						gas.setColor(Color::Transparent);
					}
					if (Collision::PixelPerfectTest(coin, playerCar)) {
						cout << "COIN Collected\n";
						score += 100;
						coinCollect.play();
						coin.setColor(Color::Transparent);
					}
					if (FUEL == 0) {
						cout << "game over : out of fuel\n";
						gameState = false;
						overState = true;
					}
				}
				if (gameState == false) {
					//cout << "Game State : FAlSE\n";
					scoreText.setFillColor(Color(252, 165, 3, 0));
					fuelBar.setFillColor(Color(252, 165, 3, 0));
					enemyCar.setColor(Color::Transparent);
					playerCar.setColor(Color::Transparent);
					roadLineA.setColor(Color::Transparent);
					roadLineB.setColor(Color::Transparent);
					roadWall.setColor(Color::Transparent);
					frame.setColor(Color::Transparent);
					playerCar.setPosition(289, 340);
					enemyCar.setPosition(146, 0);
					coin.setColor(Color::Transparent);
					gas.setColor(Color::Transparent);
				}
				if (overState == true) {
					/////////////Ranking Check/////////////
					fp = fopen("resource/ranking/score5.txt", "r");
					fscanf(fp, "%s", str);
					fclose(fp);
					rankCheck = stoi(str);
					if (score > rankCheck) ranking = 5;
					
					fp = fopen("resource/ranking/score4.txt", "r");
					fscanf(fp, "%s", str);
					fclose(fp);
					rankCheck = stoi(str);
					if (score > rankCheck) ranking = 4;

					fp = fopen("resource/ranking/score3.txt", "r");
					fscanf(fp, "%s", str);
					fclose(fp);
					rankCheck = stoi(str);
					if (score > rankCheck) ranking = 3;

					fp = fopen("resource/ranking/score2.txt", "r");
					fscanf(fp, "%s", str);
					fclose(fp);
					rankCheck = stoi(str);
					if (score > rankCheck) ranking = 2;

					fp = fopen("resource/ranking/score1.txt", "r");
					fscanf(fp, "%s", str);
					fclose(fp);
					rankCheck = stoi(str);
					if (score > rankCheck) ranking = 1;

					if (ranking == 5) {
						fp = fopen("resource/ranking/name5.txt", "w+");
						fprintf(fp, "%s", input);
						fclose(fp);

						fp = fopen("resource/ranking/score5.txt", "w+");
						fprintf(fp, "%d", score);
						fclose(fp);
					}
					if (ranking == 4) {
						char nameTemp[20],scoreTemp[20];
						fp = fopen("resource/ranking/name4.txt", "w+");
						fscanf(fp, "%s", nameTemp);
						fprintf(fp, "%s", input);
						fclose(fp);

						fp = fopen("resource/ranking/score4.txt", "w+");
						fscanf(fp, "%s", scoreTemp);
						fprintf(fp, "%s", score);
						fclose(fp);

						fp = fopen("resource/ranking/name5.txt", "w+");
						fprintf(fp, "%s", nameTemp);
						fclose(fp);

						fp = fopen("resource/ranking/score5.txt", "w+");
						fprintf(fp, "%d", scoreTemp);
						fclose(fp);
					}
					if (ranking == 3) {
						char nameTemp[20], scoreTemp[20], nameTemp2[20], scoreTemp2[20];
						fp = fopen("resource/ranking/name3.txt", "w+");
						fscanf(fp, "%s", nameTemp);
						fprintf(fp, "%s", input);
						fclose(fp);

						fp = fopen("resource/ranking/score3.txt", "w+");
						fscanf(fp, "%s", scoreTemp);
						fprintf(fp, "%d", score);
						fclose(fp);

						fp = fopen("resource/ranking/name4.txt", "w+");
						fscanf(fp, "%s", nameTemp2);
						fprintf(fp, "%s", nameTemp);
						fclose(fp);

						fp = fopen("resource/ranking/score4.txt", "w+");
						fscanf(fp, "%s", scoreTemp2);
						fprintf(fp, "%s", scoreTemp);
						fclose(fp);

						fp = fopen("resource/ranking/name5.txt", "w+");
						fprintf(fp, "%s", nameTemp2);
						fclose(fp);

						fp = fopen("resource/ranking/score5.txt", "w+");
						fprintf(fp, "%s", scoreTemp2);
						fclose(fp);
					}
					if (ranking == 2) {
						char nameTemp[20], scoreTemp[20], nameTemp2[20], scoreTemp2[20];
						fp = fopen("resource/ranking/name2.txt", "w+");
						fscanf(fp, "%s", nameTemp);
						fprintf(fp, "%s", input);
						fclose(fp);

						fp = fopen("resource/ranking/score2.txt", "w+");
						fscanf(fp, "%s", scoreTemp);
						fprintf(fp, "%d", score);
						fclose(fp);

						fp = fopen("resource/ranking/name3.txt", "w+");
						fscanf(fp, "%s", nameTemp2);
						fprintf(fp, "%s", nameTemp);
						fclose(fp);

						fp = fopen("resource/ranking/score3.txt", "w+");
						fscanf(fp, "%s", scoreTemp2);
						fprintf(fp, "%s", scoreTemp);
						fclose(fp);

						fp = fopen("resource/ranking/name4.txt", "w+");
						fscanf(fp, "%s", nameTemp);
						fprintf(fp, "%s", nameTemp2);
						fclose(fp);

						fp = fopen("resource/ranking/score4.txt", "w+");
						fscanf(fp, "%s", scoreTemp);
						fprintf(fp, "%s", scoreTemp2);
						fclose(fp);

						fp = fopen("resource/ranking/name5.txt", "w+");
						fprintf(fp, "%s", nameTemp);
						fclose(fp);

						fp = fopen("resource/ranking/score5.txt", "w+");
						fprintf(fp, "%s", scoreTemp);
						fclose(fp);
					}
					if (ranking == 1) {
						char nameTemp[20], scoreTemp[20], nameTemp2[20], scoreTemp2[20];
						fp = fopen("resource/ranking/name1.txt", "w+");
						fscanf(fp, "%s", nameTemp);
						fprintf(fp, "%s", input);
						fclose(fp);

						fp = fopen("resource/ranking/score1.txt", "w+");
						fscanf(fp, "%s", scoreTemp);
						fprintf(fp, "%d", score);
						fclose(fp);

						fp = fopen("resource/ranking/name2.txt", "w+");
						fscanf(fp, "%s", nameTemp2);
						fprintf(fp, "%s", nameTemp);
						fclose(fp);

						fp = fopen("resource/ranking/score2.txt", "w+");
						fscanf(fp, "%s", scoreTemp2);
						fprintf(fp, "%s", scoreTemp);
						fclose(fp);

						fp = fopen("resource/ranking/name3.txt", "w+");
						fscanf(fp, "%s", nameTemp);
						fprintf(fp, "%s", nameTemp2);
						fclose(fp);

						fp = fopen("resource/ranking/score3.txt", "w+");
						fscanf(fp, "%s", scoreTemp);
						fprintf(fp, "%s", scoreTemp2);
						fclose(fp);

						fp = fopen("resource/ranking/name4.txt", "w+");
						fscanf(fp, "%s", nameTemp2);
						fprintf(fp, "%s", nameTemp);
						fclose(fp);

						fp = fopen("resource/ranking/score4.txt", "w+");
						fscanf(fp, "%s", scoreTemp2);
						fprintf(fp, "%s", scoreTemp);
						fclose(fp);

						fp = fopen("resource/ranking/name5.txt", "w+");
						fprintf(fp, "%s", nameTemp2);
						fclose(fp);

						fp = fopen("resource/ranking/score5.txt", "w+");
						fprintf(fp, "%s", scoreTemp2);
						fclose(fp);
					}
					cout << ranking << endl;
					////////////////////////////////////////////
					overState = false;
					afterOver = true;
				}
				if (afterOver == true) {
					gameOver.setColor(Color::White);
					overText.setFillColor(Color(252, 165, 3, 200));
					cout << score << endl;
					cout << "Press Enter To Continue.\n";
					if (myevent.key.code == Keyboard::Enter) {
						overState = false;
						menuState = true;
					}
				}
				if (afterOver == false) {
					gameOver.setColor(Color::Transparent);
					overText.setFillColor(Color(252, 165, 3, 0));
				}
				if (howState == true) {
					how.setColor(Color::White);
					if (myevent.key.code == Keyboard::BackSpace) {
						howState = false;
						menuState = true;
					}
				}
				if (howState == false) {
					how.setColor(Color::Transparent);
				}
			}
		}
		int randomValue = rand() % 3 + 1;
		if (enemyPosition.y > 480) {
			cout << "Random : " << randomValue << endl;
			if (randomValue == 1) {
				enemyCar.setPosition(146, -128);
			}
			else if (randomValue == 2) {
				enemyCar.setPosition(289, -128);
			}
			else if (randomValue == 3) {
				enemyCar.setPosition(427, -128);
			}
		}
		enemyCar.move(Vector2f(0.f, 3.f));
		if(gameState == true) score += 1;
		
		FUEL -= 0.3;
		if (FUEL < 0) {
			overState == true;
			gameState = false;
		}
		scoreString = to_string(score);
		scoreText.setString(scoreString);
		fuelBar.setSize(Vector2f(FUEL / 6.6357, 25));
		
		//if (coinCount % 137 != 0) coin.setColor(Color::Transparent);
		if (coinCount % 137 == 0) {
			coin.setColor(Color::White);
			cout << "COINCOINCOINCOIN\n";
			int randomCoin = rand() % 3 + 1;
			if (coin.getPosition().y > 480) {
				if (randomCoin == 1) {
					coin.setPosition(146, -128);
				}
				else if (randomCoin == 2) {
					coin.setPosition(289, -128);
				}
				else if (randomCoin == 3) {
					coin.setPosition(427, -128);
				}
			}
		}
		coin.move(Vector2f(0.f, 5.f));

		if (gasCount % 379 == 0) {
			gas.setColor(Color::White);
			cout << "GASGASGASGASGASGAS\n";
			int randomGas = rand() % 3 + 1;
			if (gas.getPosition().y > 480) {
				if (randomGas == 1) {
					gas.setPosition(146, -128);
				}
				else if (randomGas == 2) {
					gas.setPosition(289, -128);
				}
				else if (randomGas == 3) {
					gas.setPosition(427, -128);
				}
			}
		}
		gas.move(Vector2f(0.f, 5.f));
		totalTime += clock.restart().asSeconds();
		if (startState == true) {
			if (totalTime >= 0.5)
			{
				totalTime = 0;
				state = !state;
			}
			if (state == true)
			{
				cursor.setFillColor(Color::Red);
			}
			else cursor.setFillColor(Color::Transparent);
		}
		else cursor.setFillColor(Color::Transparent);
		
		if (roadLineA.getPosition().y > 480) {
			roadLineA.setPosition(0, -480);
		}
		roadLineA.move(0, 4);
		if (roadLineB.getPosition().y > 480) {
			roadLineB.setPosition(0, -480);
		}
		roadLineB.move(0, 4);
		window.clear();
		window.draw(mainWall);
		window.draw(roadWall);
		window.draw(gameOver);
		window.draw(overText);
		window.draw(roadLineA);
		window.draw(roadLineB);
		window.draw(startButton);
		window.draw(howButton);
		window.draw(playerCar);
		window.draw(enemyCar);
		window.draw(nameBar);
		window.draw(cursor);
		window.draw(text);
		window.draw(nameText);
		window.draw(how);
		window.draw(coin);
		window.draw(gas);
		window.draw(frame);
		window.draw(scoreText);
		window.draw(fuelBar);
		
		window.display();
	}
	return 0;
}