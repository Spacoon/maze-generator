#pragma once

#include <vector>

#include "random.h"
#include "Direction.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/ConvexShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

struct Cell
{
	int pos;
	Direction direction;
};

class Path : public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<Cell> cells;
	int endCell_y = 0;
	int CELL_SIZE;
	sf::Color m_color = sf::Color::White;

public:
	void setCellSize(int cell_size);
	std::vector<Cell> getCells();
	void addCell(const int& pos, const Direction& dir);
	void setColor(const sf::Color& color);
	void addExit(const int& y_pos);
};