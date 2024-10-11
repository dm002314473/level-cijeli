#include "Enemy.h"
#include "../../Level.h"

int generateRandomNumber(int min, int max);

Enemy::Enemy(Level &level, int code, std::vector<std::vector<int>> &waypoints, int spawnDelayPixels) : Troop(level, code), waypointsEnemy(waypoints)
{
    setEnemyValues(level.getTroopStats(), code);
    //depending on level, if road starts from left x - 500, if road starts from right x + 500, if road starts from top y - 500, if road starts from bottom y + 500
    int positionX = generateRandomNumber(waypoints[0][0] - 150, waypoints[0][0] + 10) - spawnDelayPixels;
    int positionY = generateRandomNumber(waypoints[0][1] - 150, waypoints[0][1] + 10);
    getSprite().setPosition(positionX, positionY);
}

void Enemy::setEnemyValues(std::vector<std::vector<int>> allStats, int code){
    for (int i = 0; i < allStats.size(); i++)
    {
        for (int j = 0; j < allStats[i].size(); j++)
        {
            if (allStats[i][0] == code)
            {
                setLiveTaking(allStats[i][8]);
                setBounty(allStats[i][9]);
            }
        }
    }
}

void Enemy::setBounty(int newBounty) { bounty = newBounty; }
void Enemy::setLiveTaking(int newLiveTaking) { liveTaking = newLiveTaking; }

int Enemy::getBounty() { return bounty; }
int Enemy::getLiveTaking() { return liveTaking; }

void Enemy::move(float dtm)
{
    if (shouldEnemyTurn())
        currentWaypointIndex++;

    if (currentWaypointIndex >= (int)waypointsEnemy.size()) {
        outOfMap = true;
        return;
    }


    switch (waypointsEnemy[currentWaypointIndex][2])
    {
    case 1:
        moveUp(dtm);
        break;
    case 2:
        moveRight(dtm);
        break;
    case 3:
        moveDown(dtm);
        break;
    case 4:
        moveLeft(dtm);
        break;
    default:
        stopMoving();
        outOfMap = true;
        break;
    }
}
bool Enemy::isOutOfMap() { return outOfMap || getSprite().getPosition().x > 2500 || getSprite().getPosition().y > 1500; }

bool Enemy::shouldEnemyTurn()
{
    float dx = getSprite().getPosition().x - waypointsEnemy[currentWaypointIndex + 1][0];
    float dy = getSprite().getPosition().y - waypointsEnemy[currentWaypointIndex + 1][1];
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < 150)
        return true;
    return false;
}


