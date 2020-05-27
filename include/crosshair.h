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
	bool reloading;
	time_t shootedTime;
	int shootDelay;		//in secs
public:
	int getMagazineSize() { return magazineSize; }
	int getBulletsLeft() { return bulletsLeft; }
	void decBulletsLeft() { bulletsLeft--; }
	bool getReloading() { return reloading; }
	void setShootedTime(time_t nShootedTime) { shootedTime = nShootedTime; }
	time_t getShootedTime() { return shootedTime; }
	int getShootDelay() { return shootDelay; }

	void reload();
	bool shootable();
	void update();

	Crosshair(std::string spritePath, double nSize, int oSize);
	~Crosshair();
	
};

#endif