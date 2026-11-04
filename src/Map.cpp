#include "Map.h"
#include <utility>

Map::Map(unsigned int stepsCounter, bool day)
    : stepsCounter(stepsCounter), day(day),
      grid(18, std::vector<Tiles>(28, Tiles(true))) {
    for (int y = 0; y < static_cast<int>(getHeight()); ++y) {
        for (int x = 0; x < static_cast<int>(getWidth()); ++x) {
            const bool border = x == 0 || y == 0 ||
                x == static_cast<int>(getWidth()) - 1 ||
                y == static_cast<int>(getHeight()) - 1;
            const bool forest = ((x * 7 + y * 11 + x * y) % 17 == 0) ||
                (x > 8 && x < 13 && y > 3 && y < 7);
            setWalkable(x, y, !border && !forest);
        }
    }

    for (int x = 1; x < static_cast<int>(getWidth()) - 1; ++x) {
        setWalkable(x, 2, true);
        setWalkable(x, 9, true);
    }
    for (int y = 1; y < static_cast<int>(getHeight()) - 1; ++y) {
        setWalkable(2, y, true);
        setWalkable(14, y, true);
    }

    setEvent(6, 3, treasureChest);
    setEvent(10, 9, campfire);
    setEvent(20, 13, travellingMerchant);
    setEvent(4, 14, waypoint);
    setEvent(22, 4, golem);
    setEvent(8, 13, fairy);
}

unsigned int Map::countStep() {
    if (stepsCounter == 0) {
        cycleDay();
    }

    --stepsCounter;
    if (stepsCounter == 0) {
        cycleDay();
    }
    return stepsCounter;
}

void Map::cycleDay() {
    if (this->day) {
        this->day = false;
        this->stepsCounter = 30;
    } else {
        this->day = true;
        this->stepsCounter = 50;
    }
}

int Map::getSteps() {
    return static_cast<int>(stepsCounter);
}

bool Map::isDay() const {
    return day;
}

unsigned int Map::getWidth() const {
    return static_cast<unsigned int>(grid.empty() ? 0 : grid.front().size());
}

unsigned int Map::getHeight() const {
    return static_cast<unsigned int>(grid.size());
}

bool Map::isWalkable(int x, int y) const {
    return x >= 0 && y >= 0 && y < static_cast<int>(grid.size()) &&
        x < static_cast<int>(grid[static_cast<std::size_t>(y)].size()) &&
        grid[static_cast<std::size_t>(y)][static_cast<std::size_t>(x)].isWalkable();
}

bool Map::isEvent(int x, int y) const {
    return x >= 0 && y >= 0 && y < static_cast<int>(grid.size()) &&
        x < static_cast<int>(grid[static_cast<std::size_t>(y)].size()) &&
        grid[static_cast<std::size_t>(y)][static_cast<std::size_t>(x)].isEvent();
}

eventType Map::getEventType(int x, int y) const {
    return grid.at(static_cast<std::size_t>(y)).at(static_cast<std::size_t>(x)).getEventType();
}

void Map::setWalkable(int x, int y, bool walkable) {
    if (x >= 0 && y >= 0 && y < static_cast<int>(grid.size()) &&
        x < static_cast<int>(grid[static_cast<std::size_t>(y)].size())) {
        grid[static_cast<std::size_t>(y)][static_cast<std::size_t>(x)].setWalkable(walkable);
    }
}

void Map::setEvent(int x, int y, eventType type) {
    if (x < 0 || y < 0 || y >= static_cast<int>(grid.size()) ||
        x >= static_cast<int>(grid[static_cast<std::size_t>(y)].size())) {
        return;
    }
    setWalkable(x, y, true);
    events.push_back(std::make_unique<Event>(type));
    grid[static_cast<std::size_t>(y)][static_cast<std::size_t>(x)].setEvent(events.back().get());
}