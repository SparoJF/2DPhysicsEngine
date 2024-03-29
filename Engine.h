#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>
#include <memory>

extern int windowWidth;
extern int windowHeight;
extern float f_windowWidth;
extern float f_windowHeight;

class Entity
{
public:
	sf::Vector2f currentPosition;
	sf::Vector2f centrePosition;
	sf::Vector2f currentVelocity;
	sf::Vector2f currentAcceleration;
	sf::Vector2f force;

	float mass;
	float size;
	float resCoeff;

	sf::CircleShape body;
	sf::Color color;

	Entity();
	Entity(sf::Vector2f inputPos, float inputMass, float inputSize, sf::Color inputColor);
	~Entity();

	void updatePosition();

	void renderEntity(sf::RenderWindow &target);
};

class rectBarrier
{
public:
	sf::RectangleShape body;
	sf::Color color;

	sf::Vector2f size;
	sf::Vector2f position;

	rectBarrier();
	rectBarrier(sf::Color inputColor, sf::Vector2f inputSize, sf::Vector2f inputPosition);
	~rectBarrier();

	void setBarrier(sf::Color inputColor, sf::Vector2f inputSize, sf::Vector2f inputPosition);

	void renderBarrier(sf::RenderWindow &target);
};

class Spring
{
private:
	Entity* entity1;
	Entity* entity2;

public:
	sf::RectangleShape springBody;
	sf::Vector2f position;
	float springWidth;
	
	float springConstant;
	float restLength;
	sf::Vector2f centreOfMass;
	float e1RestDistance;
	float e2RestDistance;

	Spring(Entity* inputEntity1, Entity* inputEntity2, float inputSpringConstant, float inputRestLength);
	~Spring();

	void update();
	void applyForces();

	void render(sf::RenderWindow& target);
};

class Game
{
private:

	sf::RenderWindow* window;
	sf::Event e;

public:
	Game();
	~Game();

	float timeStep;
	float timeElapsed;
	int subSteps;
	int entitiesSpawned;

	std::vector<Entity*> Entities;
	std::vector<rectBarrier> rectBarriers;
	std::vector<Spring> Springs;
	rectBarrier upperBarrier;
	rectBarrier rightBarrier;
	rectBarrier lowerBarrier;
	rectBarrier leftBarrier;

	void initVariables();
	void initWindow();
	void initScene();

	void addEntities();
	void addSpring();

	void pollEvents();
	void solver(Entity& E, float dt);
	inline void applyGravity(Entity& E);
	void detectEntityBarrierCollision();
	void detectEntityEntityCollision();

	void update();
	void updateEntities();
	void updateSprings();

	void render();


	const bool isWindowOpen() const;
};