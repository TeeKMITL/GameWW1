#include<iostream>
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"

using namespace sf;

void Update(RectangleShape& square, RenderWindow& window, float& moveSpeed, float& jumpspeed, Vector2f& velocity, const float& gravity, int& jumpcount, Event& event, CircleShape& egg1, CircleShape& egg2);

int main() {
	sf::Clock clock1;
	sf::Clock clock2;

	const float gravity = 1;
	Vector2f velocity(Vector2f(0, 0));
	float moveSpeed = 10.0f, jumpspeed = 10.0f;
	int jumpcount = 0;

	RenderWindow window(VideoMode(1920, 1080), "Test");
	window.setFramerateLimit(60);

	RectangleShape square(Vector2f(50.f, 50.0f));
	square.setFillColor(Color::Red);
	square.setPosition(window.getSize().x / 2, window.getSize().y / 2);

	CircleShape egg1;
	egg1.setRadius(20);
	egg1.setFillColor(Color::Yellow);
	egg1.setOutlineThickness(5);
	egg1.setPosition(40, 630);

	CircleShape egg2;
	egg2.setRadius(20);
	egg2.setFillColor(Color::Yellow);
	egg2.setOutlineThickness(5);
	egg2.setPosition(1830, 630);

	Font font;
	if (!font.loadFromFile("ARIAL.ttf")) {
		return 1;
	}


	Texture texture;
	if (!texture.loadFromFile("res/sword.png")) {
		return 1;
	}
	std::vector<sf::Sprite> sprites;
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	for (int i = 0; i < 20; ++i) {
		sf::Sprite sprite(texture);
		sprite.setScale(0.1f, 0.1f);
		sprite.setPosition(std::rand() % 1920, -50);
		sprites.push_back(sprite);
	}

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}

		FloatRect rectBounds = square.getGlobalBounds();
		FloatRect egg1Bounds = egg1.getGlobalBounds();
		FloatRect egg2Bounds = egg2.getGlobalBounds();


		for (auto& sprite : sprites) {
			sprite.move(0, 2);
			if (sprite.getPosition().y > 600) {
				sprite.setPosition(std::rand() % 800, -50);
			}
		}

		Update(square, window, moveSpeed, jumpspeed, velocity, gravity, jumpcount, event, egg1, egg2);
		window.clear(Color::White);
		for (const auto& sprite : sprites) {
			window.draw(sprite);
		}
		window.draw(square);
		window.draw(egg1);
		window.draw(egg2);
		window.display();

	}
}

void Update(RectangleShape& square, RenderWindow& window, float& moveSpeed, float& jumpspeed, Vector2f& velocity, const float& gravity, int& jumpcount, Event& event, CircleShape& egg1, CircleShape& egg2) {

	bool paused;


	if (Keyboard::isKeyPressed(Keyboard::P)) {
		paused = true;

		velocity.x = square.getPosition().x;
		velocity.y = square.getPosition().y;

		while (window.isOpen()) {
			if (paused == false)
				break;
			sf::sleep(sf::milliseconds(100));
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)
					window.close();
				square.setPosition(velocity.x, velocity.y);
				if (Keyboard::isKeyPressed(Keyboard::P)) {
					paused = false;
					sf::sleep(sf::milliseconds(100));
					break;
				}
			}
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::A) && square.getPosition().x > 0) {
		velocity.x = -moveSpeed;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D) && square.getPosition().x + square.getSize().x < window.getSize().x) {
		velocity.x = +moveSpeed;
	}
	else
		velocity.x = 0;
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		if (jumpcount < 2)
			velocity.y = -jumpspeed;
		square.move(velocity.x, velocity.y);
		jumpcount++;
	}
	if (square.getPosition().y + square.getSize().y < 700) {
		velocity.y += gravity;
	}
	else {
		square.setPosition(square.getPosition().x, 700 - square.getSize().y);
		velocity.y = 0;
		jumpcount = 0;
	}
	square.move(velocity.x, velocity.y);
}