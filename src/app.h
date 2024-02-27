#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

#include "Path.h"

class App
{
public:
	const bool IsRunning() const;
	void Update();
	void Render();

	App();
	~App();

private:
	sf::RenderWindow* window = nullptr;
	sf::Clock deltaClock;

	// boundaries cells are sides of our map
	std::vector<int> boundaries;

	int CELL_SIZE = 44,
		SCREEN_SIZE = 22;
	float fbackgroundColor[3] = { 0.0f, 0.0f, 0.0f },
		  fpathColor[3] = { 1.0f, 1.0f, 1.0f };

	Path path;

	void setWindow();
	void setBoundaries();
	void handleMazeSetting();
	void handleGUI();
	void drawCell(const int& position, const sf::Color& color = sf::Color::White) const;

	const bool contains(const int& number, const std::vector<int>& array) const;
	const bool contains(const int& number, Path& path) const;
};