#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include "entity.h"
#include <time.h>
#include <chrono>
#include <thread>
#include <pthread.h>
#include <iostream>

class Crosshair: public Entity
{
private:
	std::thread reloadingThread;

	int magazineSize;
	int bulletsLeft;
	int reloadTime;		//in millis
	time_t shootedTime;
	int shootDelay;		//in secs
public:
	int getBulletsLeft() { return bulletsLeft; }
	void decBulletsLeft() { bulletsLeft--; }
	void setShootedTime(time_t nShootedTime) { shootedTime = nShootedTime; }
	time_t getShootedTime() { return shootedTime; }
	int getShootDelay() { return shootDelay; }

	void reload();
	void *reloading();
	bool shootable();
	void update();

	Crosshair(std::string spritePath, double nSize, int oSize);
	~Crosshair();
	
};

#endif