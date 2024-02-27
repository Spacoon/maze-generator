#include "Path.h"

void Path::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// vertices
    sf::Vector2f first, second, third, fourth;

	sf::ConvexShape cell(4);
    cell.setFillColor(m_color);

    int x_pos, y_pos;

	for (const auto& c : cells)
	{
        x_pos = c.pos % (target.getSize().x / CELL_SIZE);
		y_pos = c.pos / (target.getSize().y / CELL_SIZE);

		switch (c.direction)
		{
		case Direction::Up:
            first = sf::Vector2f(
				x_pos * CELL_SIZE + 4,
                y_pos * CELL_SIZE + 4);
            second = sf::Vector2f(
				x_pos * CELL_SIZE + CELL_SIZE - 4,
                y_pos * CELL_SIZE + 4);
            third = sf::Vector2f(
				x_pos * CELL_SIZE + CELL_SIZE - 4,
                y_pos * CELL_SIZE + CELL_SIZE + 4);
            fourth = sf::Vector2f(
				x_pos * CELL_SIZE + 4,
                y_pos * CELL_SIZE + CELL_SIZE + 4);
            break;
		case Direction::Right:
            first = sf::Vector2f(
                x_pos * CELL_SIZE - 4, 
                y_pos * CELL_SIZE + 4);
            second = sf::Vector2f(
                x_pos * CELL_SIZE + CELL_SIZE - 4,
                y_pos * CELL_SIZE + 4);
            third = sf::Vector2f(
                x_pos * CELL_SIZE + CELL_SIZE - 4,
                y_pos * CELL_SIZE + CELL_SIZE - 4);
            fourth = sf::Vector2f(
                x_pos * CELL_SIZE - 4,
                y_pos * CELL_SIZE + CELL_SIZE - 4);
            break;
        case Direction::Down:
            first = sf::Vector2f(
                x_pos * CELL_SIZE + 4,
                y_pos * CELL_SIZE - 4);
            second = sf::Vector2f(
                x_pos * CELL_SIZE + CELL_SIZE - 4,
                y_pos * CELL_SIZE - 4);
            third = sf::Vector2f(
                x_pos * CELL_SIZE + CELL_SIZE - 4,
                y_pos * CELL_SIZE + CELL_SIZE - 4);
            fourth = sf::Vector2f(
                x_pos * CELL_SIZE + 4,
                y_pos * CELL_SIZE + CELL_SIZE - 4);
            break;
        case Direction::Left:
            first = sf::Vector2f(
                x_pos * CELL_SIZE + 4,
                y_pos * CELL_SIZE + 4);
            second = sf::Vector2f(
	            x_pos * CELL_SIZE + CELL_SIZE + 4,
                y_pos * CELL_SIZE + 4);
            third = sf::Vector2f(
                x_pos * CELL_SIZE + CELL_SIZE + 4,
                y_pos * CELL_SIZE + CELL_SIZE - 4);
            fourth = sf::Vector2f(
                x_pos * CELL_SIZE + 4,
                y_pos * CELL_SIZE + CELL_SIZE - 4);
            break;
		}

        cell.setPoint(0, first);
        cell.setPoint(1, second);
        cell.setPoint(2, third);
        cell.setPoint(3, fourth);
        
		target.draw(cell, states);
	}

    // draw the exit
    x_pos = target.getSize().y / CELL_SIZE - 1;
	y_pos = endCell_y;

    first = sf::Vector2f(
        x_pos * CELL_SIZE - 4,
        y_pos * CELL_SIZE + 4);
    second = sf::Vector2f(
        x_pos * CELL_SIZE + CELL_SIZE + 4,
        y_pos * CELL_SIZE + 4);
    third = sf::Vector2f(
        x_pos * CELL_SIZE + CELL_SIZE + 4,
        y_pos * CELL_SIZE + CELL_SIZE - 4);
    fourth = sf::Vector2f(
        x_pos * CELL_SIZE - 4,
        y_pos * CELL_SIZE + CELL_SIZE - 4);

    cell.setPoint(0, first);
    cell.setPoint(1, second);
    cell.setPoint(2, third);
    cell.setPoint(3, fourth);

	target.draw(cell, states);
}

void Path::setCellSize(int cell_size)
{
    CELL_SIZE = cell_size;
}

std::vector<Cell> Path::getCells()
{
	return cells;
}

void Path::addCell(const int& pos, const Direction& dir)
{
	cells.push_back(
		Cell{ pos, dir }
	);
}

void Path::setColor(const sf::Color& color)
{
    m_color = color;
}

void Path::addExit(const int& y_pos)
{
    endCell_y = y_pos;
}
