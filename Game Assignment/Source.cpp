//#include <SFML/Graphics.hpp>
//using namespace sf;
//
//class Game
//{
//public:Game();
//	  void run();
//
//private:
//	void processEvents();
//	void update(Time);
//	void render();
//	void handlePlayerInput(Keyboard::Key, bool);
//
//	bool mIsMovingUp, mIsMovingRight, mIsMovingLeft, mIsMovingDown;
//	float playerSpeed;
//	Time TimePerFrame;
//
//
//private:
//	RenderWindow mWindow;
//	CircleShape mPlayer;
//};
//
//Game::Game() :mWindow(VideoMode(640, 480), "SFML Application"), mPlayer(), playerSpeed(20.f), TimePerFrame(seconds(1.f / 60.f))
//{
//	mPlayer.setRadius(20.f);
//	mPlayer.setPosition(220.f, 220.f);
//	mPlayer.setFillColor(Color::White);
//}
//
//void Game::handlePlayerInput(Keyboard::Key key, bool isPressed)
//{
//	if (key == Keyboard::W || key == Keyboard::Up)
//		mIsMovingUp = isPressed;
//	else if (key == Keyboard::S || key == Keyboard::Down)
//		mIsMovingDown = isPressed;
//	else if (key == Keyboard::A || key == Keyboard::Left)
//		mIsMovingLeft = isPressed;
//	else if (key == Keyboard::D || key == Keyboard::Right)
//		mIsMovingRight = isPressed;
//}
//
//void Game::run()
//{
//	Clock clock;
//	Time timeSinceLastUpdate = Time::Zero;
//	while (mWindow.isOpen())
//	{
//		processEvents();
//		timeSinceLastUpdate += clock.restart();
//		while (timeSinceLastUpdate > TimePerFrame)
//		{
//			timeSinceLastUpdate -= TimePerFrame;
//			processEvents();
//			update(TimePerFrame);
//		}
//		render();
//	}
//}
//
//void Game::processEvents()
//{
//	Event event;
//	while (mWindow.pollEvent(event))
//	{
//		switch (event.type)
//		{
//		case Event::KeyPressed:
//			handlePlayerInput(event.key.code, true);
//			break;
//		case sf::Event::KeyReleased:
//			handlePlayerInput(event.key.code, false);
//			break;
//		case sf::Event::Closed:
//			mWindow.close();
//			break;
//		}
//	}
//}
//
//void Game::update(Time deltaTime)
//{
//	Vector2f movement(0.f, 0.f);
//	if (mIsMovingUp)
//		movement.y -= playerSpeed;
//	if (mIsMovingDown)
//		movement.y += playerSpeed;
//	if (mIsMovingLeft)
//		movement.x -= playerSpeed;
//	if (mIsMovingRight)
//		movement.x += playerSpeed;
//
//	mPlayer.move(movement * deltaTime.asSeconds());
//}
//
//void Game::render()
//{
//	mWindow.clear();
//	mWindow.draw(mPlayer);
//	mWindow.display();
//}
//
//int main()
//{
//	Game game;
//	game.run();
//}