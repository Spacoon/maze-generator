#include "App.h"

const bool App::IsRunning() const
{
	return window->isOpen();
}

void App::Update()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);

        if (event.type == sf::Event::Closed)
            window->close();
    }

    ImGui::SFML::Update(*window, deltaClock.restart());
    handleGUI();
}

void App::Render()
{
    window->clear(sf::Color(
		255.0f * fbackgroundColor[0],
        255.0f * fbackgroundColor[1],
        255.0f * fbackgroundColor[2]));

    // no need to draw boundaries as they're the same color as the background
    //for (int cell : boundaries)
    //    drawCell(cell, sf::Color::Blue);

    window->draw(path);

    ImGui::SFML::Render(*window);
    window->display();
}

App::App()
{
    setWindow();
    setBoundaries();
	path.setCellSize(CELL_SIZE);

    handleMazeSetting();
    /* That's how 5x5 map would look like
     * 0, 1, 2, 3, 4,
     * 5, 6, 7, 8, 9,
     *10,11,12,13,14,
     *15,16,17,18,19,
     *20,21,22,23,24
     */
}

App::~App()
{
    ImGui::SFML::Shutdown();
    delete window;
}

void App::setWindow()
{
    window = new sf::RenderWindow
    (
        sf::VideoMode(CELL_SIZE * SCREEN_SIZE, CELL_SIZE * SCREEN_SIZE),
        "Maze generator"
    );

    window->setFramerateLimit(60);
    ImGui::SFML::Init(*window);
}

void App::setBoundaries()
{
    boundaries.reserve(2 * SCREEN_SIZE + 2 * (SCREEN_SIZE - 2));
    for (int i = 0; i < SCREEN_SIZE; i++)
    {
        boundaries.emplace_back(i);
        boundaries.emplace_back(SCREEN_SIZE * SCREEN_SIZE - SCREEN_SIZE + i);
    }
    for (int i = 0; i < SCREEN_SIZE - 2; i++)
    {
        boundaries.emplace_back((i + 1) * SCREEN_SIZE);
        boundaries.emplace_back((i + 2) * SCREEN_SIZE - 1);
    }
}

void App::handleMazeSetting()
{
    int currentCell = getRandomNumber(1, SCREEN_SIZE - 2) * SCREEN_SIZE;
    Direction dir = Direction::Right;

    std::vector<Direction> possibleDirections = {
        Direction::Up,
        Direction::Right,
        Direction::Down,
        Direction::Left
    };

    path.addCell(currentCell, dir);
    path.addCell(++currentCell, dir);

    int lastElementIndex = path.getCells().size() - 1;

	while (path.getCells().size() - 1 != SCREEN_SIZE * SCREEN_SIZE - boundaries.size())
    {
        dir = possibleDirections[getRandomNumber(0, possibleDirections.size() - 1)];

        switch (dir)
        {
        case Direction::Up:
            currentCell -= SCREEN_SIZE;
            break;
        case Direction::Right:
            currentCell++;
            break;
        case Direction::Down:
            currentCell += SCREEN_SIZE;
            break;
        case Direction::Left:
            currentCell--;
            break;
        }

         if (contains(currentCell, boundaries))
        {
	        if (possibleDirections.size() == 1)
	        {
                currentCell = path.getCells()[--lastElementIndex].pos;
                possibleDirections = {
                        Direction::Up,
                        Direction::Right,
                        Direction::Down,
                        Direction::Left
                };
                possibleDirections.erase(std::remove(possibleDirections.begin(), possibleDirections.end(), dir), possibleDirections.end());
	        }
	        else
	        {
                currentCell = path.getCells()[lastElementIndex].pos;
                possibleDirections.erase(std::remove(possibleDirections.begin(), possibleDirections.end(), dir), possibleDirections.end());
	        }
            
        }
        else if(contains(currentCell, path))
        {
	        if (possibleDirections.size() == 1)
	        {
                currentCell = path.getCells()[--lastElementIndex].pos;
                possibleDirections = {
                        Direction::Up,
                        Direction::Right,
                        Direction::Down,
                        Direction::Left
                };
	        }
            else
            {
                currentCell = path.getCells()[lastElementIndex].pos;
                possibleDirections.erase(std::remove(possibleDirections.begin(), possibleDirections.end(), dir), possibleDirections.end());
            }
        }
        else
        {
            path.addCell(currentCell, dir);
            lastElementIndex = path.getCells().size() - 1; 
            possibleDirections = {
                Direction::Up,
                Direction::Right,
                Direction::Down,
                Direction::Left
            };
        }
    }

    currentCell = getRandomNumber(1, SCREEN_SIZE - 2);
    path.addExit(currentCell);
}

void App::handleGUI()
{
	using namespace ImGui;

	Begin("Menu");

	ColorEdit3("Background color", fbackgroundColor);
    if (ColorEdit3("Path color", fpathColor))
    {
        path.setColor(sf::Color(
            255.0f * fpathColor[0],
            255.0f * fpathColor[1],
            255.0f * fpathColor[2]));
    }

    End();
}

void App::drawCell(const int& position, const sf::Color& color) const
{
    sf::ConvexShape cell(4);
    cell.setFillColor(color);
    int x_pos = position % SCREEN_SIZE;
    int y_pos = position / SCREEN_SIZE;

    cell.setPoint(0, sf::Vector2f(
        x_pos * CELL_SIZE, y_pos * CELL_SIZE
    ));
    cell.setPoint(1, sf::Vector2f(
        x_pos * CELL_SIZE + CELL_SIZE, y_pos * CELL_SIZE
    ));
    cell.setPoint(2, sf::Vector2f(
        x_pos * CELL_SIZE + CELL_SIZE, y_pos * CELL_SIZE + CELL_SIZE
    ));
    cell.setPoint(3, sf::Vector2f(
        x_pos * CELL_SIZE, y_pos * CELL_SIZE + CELL_SIZE
    ));

    window->draw(cell);
}


const bool App::contains(const int& number, const std::vector<int>& array) const
{
    for (const int& a : array)
    {
	    if (number == a)
		    return true;
    }
    return false;
}

const bool App::contains(const int& number, Path& path) const
{
    for (const auto& c : path.getCells())
    {
	    if (number == c.pos)
            return true;
    }
    return false;
}