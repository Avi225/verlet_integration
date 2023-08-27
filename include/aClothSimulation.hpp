#pragma once

#include <vector>
#include <cmath>

#include "aMath.hpp"
#include "aWindow.hpp"

class aClothPoint
{
public:
	
	ClothPoint();
	aClothPoint(vector2f position, bool isLocked)
		: position(position), previousPosition(position), isLocked(isLocked)
	{}

	bool getIsLocked();
	void setIsLocked(bool pIsLocked);

	vector2f getPosition();
	void setPosition(vector2f pPosition);

	vector2f getPreviousPosition();
	void setPreviousPosition(vector2f pPreviousPosition);


private:

	vector2f position, previousPosition;

	bool isLocked = false;
};

class aClothStick
{
public:

	aClothStick();
	aClothStick(aClothPoint *a, aClothPoint *b, float length)
		: a(a), b(b), length(length)
	{}

	float getLength();
	void setLength(float pLength);

	aClothPoint* pointA();
	aClothPoint* pointB();

	aClothPoint getA();
	aClothPoint getB();

	void setA(aClothPoint* pA);
	void setB(aClothPoint* pB);

	float getStress();
	void setStress(float pStress);

private:

	aClothPoint *a, *b;

	float length;

	float stress = 0;
};


class aClothSimulation
{
public:

	aClothSimulation(aWindow* window)
		: window(window)
	{}

	void updateSimulation();

	void renderPoints();
	void renderSticks();

	void switchIsSimulating();

	std::vector<aClothPoint>* getPoints();
	std::vector<aClothStick>* getSticks();

	aClothPoint* getStickMaker();

	void setStickMaker(aClothPoint* point);

	void switchLockPoint(aClothPoint* point);

	void deletePoint(aClothPoint* point);

	void deleteStick(aClothStick* stick);

	void mouseDeleteStick();

	aClothPoint* checkClosestPoint();
	aClothStick* checkClosestStick();

	void mouseSpawnPoint();

	void generateGrid();

	void spawnStick(aClothPoint* point);

	vector2f* getGravityPointer();

	int* getsimulationIterations();

	bool* getShowStretchPointer();
	bool* getShowCompressionPointer();

	bool* getEditorShowSticks();
	bool* getEditorShowPoints();

	bool* getSimulationShowSticks();
	bool* getSimulationShowPoints();
	
	int* getGridW();
	int* getGridH();

	int* getGridCellW();
	int* getGridCellH();

	int* getPointsSize();
	int* getSticksSize();


private:

	std::vector<aClothPoint> clothPoints;
	std::vector<aClothStick> clothSticks;

	aClothPoint* selectedPoint = NULL;
	aClothStick* selectedStick = NULL;

	aClothPoint* stickMaker = NULL;

	bool isSimulating = false;

	int simulationIterations = 50;

	vector2f gravity = {0, 0.25};

	bool showStretch = false;
	bool showCompression = false;

	bool editorShowSticks = true;
	bool editorShowPoints = true;

	bool simulationShowSticks = true;
	bool simulationShowPoints = false;

	int gridW = 50;
	int gridH = 50;
	int gridCellW = 10;
	int gridCellH = 10;

	int points;
	int sticks;

	aWindow* window;
};