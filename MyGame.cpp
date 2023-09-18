#include<iostream>
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"

using namespace sf;

void Update(RectangleShape& square, RenderWindow& window, float& moveSpeed, float& jumpspeed, Vector2f& velocity, const float& gravity, int &jumpcount, Event &event);
void Draw(RenderWindow &target, RectangleShape &square);

int main() {

	const float gravity = 1;
	Vector2f velocity(Vector2f(0, 0));
	float moveSpeed = 10.0f, jumpspeed = 10.0f;
	int jumpcount = 0;

	RenderWindow window(VideoMode(1920, 1080), "Test");
	window.setFramerateLimit(60);
	RectangleShape square(Vector2f(50.f, 50.0f));
	square.setFillColor(Color::Red);
	square.setPosition(window.getSize().x / 2, window.getSize().y / 2);


	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}

		Update( square, window, moveSpeed, jumpspeed, velocity, gravity, jumpcount, event);
		Draw(window, square);
	}
}

void Update(RectangleShape &square, RenderWindow &window, float &moveSpeed, float &jumpspeed, Vector2f &velocity, const float &gravity, int &jumpcount, Event &event) {
	
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

void Draw(RenderWindow &window, RectangleShape &square) {
	window.clear(Color::White);
	window.draw(square);
	window.display();
}