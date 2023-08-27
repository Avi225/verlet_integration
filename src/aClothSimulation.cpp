#include "aClothSimulation.hpp"

bool aClothPoint::getIsLocked()
{
	return (isLocked);
}

void aClothPoint::setIsLocked(bool pIsLocked)
{
	isLocked = pIsLocked;
}

vector2f aClothPoint::getPosition()
{
	return (position);
}

void aClothPoint::setPosition(vector2f pPosition)
{
	position = pPosition;
}

vector2f aClothPoint::getPreviousPosition()
{
	return (previousPosition);
}

void aClothPoint::setPreviousPosition(vector2f pPreviousPosition)
{
	previousPosition = pPreviousPosition;
}

float aClothStick::getLength()
{
	return (length);
}

void aClothStick::setLength(float pLength)
{
	length = pLength;
}

aClothPoint* aClothStick::pointA()
{
	return a;
}

void aClothStick::setA(aClothPoint* pA)
{
	a = pA;
}

aClothPoint* aClothStick::pointB()
{
	return b;
}

void aClothStick::setB(aClothPoint* pB)
{
	b = pB;
}

aClothPoint aClothStick::getA()
{
	return *a;
}

aClothPoint aClothStick::getB()
{
	return *b;
}

float aClothStick::getStress()
{
	return (stress);
}
void aClothStick::setStress(float pStress)
{
	stress = pStress;
}

void aClothSimulation::switchIsSimulating()
{
	isSimulating = !isSimulating;
}

std::vector<aClothPoint>* aClothSimulation::getPoints()
{
	return (&clothPoints);
}

std::vector<aClothStick>* aClothSimulation::getSticks()
{
	return (&clothSticks);
}

aClothPoint* aClothSimulation::getStickMaker()
{
	return (stickMaker);
}

void aClothSimulation::setStickMaker(aClothPoint* point)
{
	stickMaker = point;
}
void aClothSimulation::switchLockPoint(aClothPoint* point)
{
	if (point != NULL)
		point->setIsLocked(!point->getIsLocked());
}

void aClothSimulation::deletePoint(aClothPoint* point)
{
	bool isUsed = false;
	for (int i = 0; i < int(clothSticks.size()); i++)
	{
		if (clothSticks[i].pointA() == point || clothSticks[i].pointB() == point)
		{
			isUsed = true;
			break;
		}
	}
	if (!isUsed)
	{
		for (int i = 0; i < int(clothPoints.size()); i++)
		{
			if (&clothPoints[i] == point)
				clothPoints.erase(clothPoints.begin() + i);
		}
	}
}

void aClothSimulation::deleteStick(aClothStick* stick)
{
	for (int i = 0; i < int(clothSticks.size()); i++)
	{
		std::cout << stick << " " << &clothSticks[i] << "  " << i << std::endl;
		if (&clothSticks[i] == stick)
		{
			clothSticks.erase(clothSticks.begin() + i);
		}
	}
}

void aClothSimulation::mouseDeleteStick()
{
	for (int i = 0; i < int(clothSticks.size()); i++)
	{
		if (&clothSticks[i] == selectedStick)
		{
			clothSticks.erase(clothSticks.begin() + i);
		}
	}
}

vector2f* aClothSimulation::getGravityPointer()
{
	return (&gravity);
}

int* aClothSimulation::getsimulationIterations()
{
	return (&simulationIterations);
}

bool* aClothSimulation::getShowStretchPointer()
{
	return (&showStretch);
}

bool* aClothSimulation::getShowCompressionPointer()
{
	return (&showCompression);
}

bool* aClothSimulation::getEditorShowSticks()
{
	return (&editorShowSticks);
}

bool* aClothSimulation::getEditorShowPoints()
{
	return (&editorShowPoints);
}

bool* aClothSimulation::getSimulationShowSticks()
{
	return (&simulationShowSticks);
}

bool* aClothSimulation::getSimulationShowPoints()
{
	return (&simulationShowPoints);
}

int* aClothSimulation::getGridW()
{
	return (&gridW);
}

int* aClothSimulation::getGridH()
{
	return (&gridH);
}

int* aClothSimulation::getGridCellW()
{
	return (&gridCellW);
}

int* aClothSimulation::getGridCellH()
{
	return (&gridCellH);
}

int*  aClothSimulation::getPointsSize()
{
	return (&points);
}

int*  aClothSimulation::getSticksSize()
{
	return (&sticks);
}

void aClothSimulation::generateGrid()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	int indexes[clothSticks.size() * 2];

	int previousSize = clothPoints.size();

	for (int i = 0; i < int(clothSticks.size()); i++)
	{
		for (int ii = 0; ii < int(clothPoints.size()); ii++)
		{
			if (clothSticks[i].pointA() == &clothPoints[ii])
			{
				indexes[i + i] = ii;
			}
			else if (clothSticks[i].pointB() == &clothPoints[ii])
			{
				indexes[i + i + 1] = ii;
			}
		}
	}

	for (int i = 0; i < gridH; i++)
	{
		for (int ii = 0; ii < gridW; ii++)
		{
			clothPoints.push_back(aClothPoint(vector2f(mouseX + ii * gridCellW, mouseY + i * gridCellH), false));
		}
	}

	for (int ii = 0; ii < int(clothSticks.size()); ii++)
	{
		clothSticks[ii].setA(&clothPoints[indexes[ii + ii]]);
		clothSticks[ii].setB(&clothPoints[indexes[ii + ii + 1]]);
	}

	std::cout << previousSize << std::endl;

	for (int i = 0; i < gridH; i++)
	{
		for (int ii = 0; ii < gridW - 1; ii++)
		{
			clothSticks.push_back(aClothStick(&clothPoints[previousSize + ii + i * gridW], &clothPoints[previousSize + ii + 1 + i * gridW], gridCellW));
		}
		std::cout << std::endl;
	}
	for (int i = 0; i < gridW - 1; i++)
	{
		for (int ii = 0; ii < gridH; ii++)
		{
			clothSticks.push_back(aClothStick(&clothPoints[previousSize + ii + i * gridW], &clothPoints[previousSize + ii + i * gridW + gridW], gridCellH));
		}
		std::cout << std::endl;
	}

}

aClothPoint* aClothSimulation::checkClosestPoint()
{
	if (clothPoints.size() > 0)
	{
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		aClothPoint* bestPoint = &clothPoints[0];
		for (int i = 0; i < int(clothPoints.size()); i++)
		{
			if (vector2f(mouseX, mouseY).distance(clothPoints[i].getPosition()) < vector2f(mouseX, mouseY).distance(bestPoint->getPosition()))
				bestPoint = &clothPoints[i];
		}
		if (vector2f(mouseX, mouseY).distance(bestPoint->getPosition()) < 5)
			return (bestPoint);
		else
			return (NULL);

		delete bestPoint;
	} else
	{
		return (NULL);
	}
}

aClothStick* aClothSimulation::checkClosestStick()
{
	if (clothSticks.size() > 0)
	{
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		aClothStick* bestStick = NULL;
		aClothPoint* bestPoint = &clothPoints[0];
		float s, a, b, x, y, bestHeight;

		for (int i = 0; i < int(clothPoints.size()); i++)
		{
			if (vector2f(mouseX, mouseY).distance(clothPoints[i].getPosition()) < vector2f(mouseX, mouseY).distance(bestPoint->getPosition()))
				bestPoint = &clothPoints[i];
		}

		for (int i = 0; i < int(clothSticks.size()); i++)
		{
			b = clothSticks[i].pointA()->getPosition().distance(clothSticks[i].pointB()->getPosition());
			x = vector2f(mouseX, mouseY).distance(clothSticks[i].pointA()->getPosition());
			y = vector2f(mouseX, mouseY).distance(clothSticks[i].pointB()->getPosition());
			s = (b + x + y) / 2;
			a = aSquareRoot(s * (s - b) * (s - x) * (s - y));

			if ((clothSticks[i].pointA() == bestPoint && (x * x + b * b - y * y) / 2 * x * b > 0) || (clothSticks[i].pointB() == bestPoint && (y * y + b * b - x * x) / 2 * y * b > 0))
			{
				if (a / (b / 2) < bestHeight)
				{
					bestHeight = a / (b / 2);
					bestStick = &clothSticks[i];
				}
			}
		}
		if (bestStick != NULL)
		{
			if (bestHeight < 3)
				return (bestStick);
			else
				return (NULL);
		} else
			return (NULL);

		delete bestStick;
		delete bestPoint;

	} else
	{
		return (NULL);
	}
}

void aClothSimulation::mouseSpawnPoint()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	int indexes[clothSticks.size() * 2];

	for (int i = 0; i < int(clothSticks.size()); i++)
	{
		for (int ii = 0; ii < int(clothPoints.size()); ii++)
		{
			if (clothSticks[i].pointA() == &clothPoints[ii])
			{
				indexes[i + i] = ii;
			}
			else if (clothSticks[i].pointB() == &clothPoints[ii])
			{
				indexes[i + i + 1] = ii;
			}
		}
	}

	clothPoints.push_back(aClothPoint(vector2f(mouseX, mouseY), false));

	for (int i = 0; i < int(clothSticks.size()); i++)
	{
		clothSticks[i].setA(&clothPoints[indexes[i + i]]);
		clothSticks[i].setB(&clothPoints[indexes[i + i + 1]]);
	}
}


void aClothSimulation::spawnStick(aClothPoint * point)
{
	if (point != NULL && stickMaker != NULL && point != stickMaker)
		clothSticks.push_back(aClothStick(point, stickMaker, point->getPosition().distance(stickMaker->getPosition())));
	stickMaker = NULL;
}

void aClothSimulation::renderPoints()
{
	for (int i = 0; i < int(clothPoints.size()); i++)
	{
		SDL_Color color = {255, 255, 255, 255};

		if (clothPoints[i].getIsLocked())
			color = {255, 64, 128, 255};

		if (&clothPoints[i] == selectedPoint)
		{
			if (color.r >= 128)
				color.r = - 128;
			if (color.g >= 128)
				color.g = - 128;
			if (color.b >= 128)
				color.b = - 128;
		}

		window->aRenderFillCircle(clothPoints[i].getPosition(), 2, color);
	}
}

void aClothSimulation::renderSticks()
{
	for (int i = 0; i < int(clothSticks.size()); i++)
	{

		/* set stick's color according to stress */

		SDL_Color color = {255, 255, 255, 255};

		if (clothSticks[i].getStress() < 0 && showStretch)
		{
			if (clothSticks[i].getStress() * 100 < -255)
			{
				color.g = 0;
				color.b = 0;
			} else
			{
				color.g = 255 + clothSticks[i].getStress() * 100;
				color.b = 255 + clothSticks[i].getStress() * 100;
			}
		} else if (clothSticks[i].getStress() > 0 && showCompression)
		{
			if (clothSticks[i].getStress() * 100 > 255)
			{
				color.g = 0;
				color.r = 0;
			} else
			{
				color.g = 255 - clothSticks[i].getStress() * 100;
				color.r = 255 - clothSticks[i].getStress() * 100;
			}
		}
		if (&clothSticks[i] == selectedStick)
		{
			if (color.r >= 128)
				color.r = - 128;
			if (color.g >= 128)
				color.g = - 128;
			if (color.b >= 128)
				color.b = - 128;
		}

		window->aRenderLine(clothSticks[i].pointA()->getPosition(), clothSticks[i].pointB()->getPosition(), color);
	}
}

void aClothSimulation::updateSimulation()
{
	points = int(clothPoints.size());
	sticks = int(clothSticks.size());

	if (isSimulating)
	{
		selectedPoint = checkClosestPoint();
		if(!simulationShowPoints)
			selectedPoint = NULL;
		if (selectedPoint == NULL && simulationShowSticks)
			selectedStick = checkClosestStick();
		else
			selectedStick = NULL;

		/* update points */

		for (int i = 0; i < int(clothPoints.size()); i++)
		{

			if (!clothPoints[i].getIsLocked())
			{
				vector2f previousPosition = clothPoints[i].getPosition();

				/* keep momentum from previous frame, apply gravity */

				clothPoints[i].setPosition(clothPoints[i].getPosition().returnAddVector(clothPoints[i].getPosition().returnSubtractVector(clothPoints[i].getPreviousPosition())));
				clothPoints[i].setPosition(clothPoints[i].getPosition().returnAddVector(gravity));

				clothPoints[i].setPreviousPosition(previousPosition);
			}
		}

		/* update sticks */

		for (int i = 0; i < simulationIterations; i++)
		{
			for (int ii = 0; ii < int(clothSticks.size()); ii++)
			{
				vector2f stickCenter = clothSticks[ii].pointA()->getPosition().returnAddVector(clothSticks[ii].pointB()->getPosition()).returnDivideFloat(2);
				vector2f stickDirection = clothSticks[ii].pointA()->getPosition().returnSubtractVector(clothSticks[ii].pointB()->getPosition());
				stickDirection.normalize();

				/* set stick stress according to the average of differences between stick's center, desired locations of points and their actual positions */

				if (i == 0)
				{
					clothSticks[ii].setStress(vector2f(stickCenter.x + stickDirection.x * clothSticks[ii].getLength() / 2, stickCenter.y + stickDirection.y * clothSticks[ii].getLength() / 2).distance(vector2f(stickCenter.x - stickDirection.x * clothSticks[ii].getLength() / 2, stickCenter.y - stickDirection.y * clothSticks[ii].getLength() / 2))/50);
				}

				if (!clothSticks[ii].pointA()->getIsLocked())
				{
					clothSticks[ii].pointA()->setPosition(vector2f(stickCenter.x + stickDirection.x * clothSticks[ii].getLength() / 2, stickCenter.y + stickDirection.y * clothSticks[ii].getLength() / 2));
				}

				if (!clothSticks[ii].pointB()->getIsLocked())
				{
					clothSticks[ii].pointB()->setPosition(vector2f(stickCenter.x - stickDirection.x * clothSticks[ii].getLength() / 2, stickCenter.y - stickDirection.y * clothSticks[ii].getLength() / 2));
				}
			}
		}

		if (simulationShowSticks)
			renderSticks();
		if (simulationShowPoints)
			renderPoints();

	} else
	{
		selectedPoint = checkClosestPoint();
		if(!editorShowPoints)
			selectedPoint = NULL;
		if (selectedPoint == NULL && editorShowSticks)
			selectedStick = checkClosestStick();
		else
			selectedStick = NULL;
		

		if (editorShowSticks)
			renderSticks();
		if (editorShowPoints)
			renderPoints();
	}
	if (stickMaker != NULL)
	{

		/* render a real time stick to mouse when creating a new one */

		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		SDL_Color color = {255, 255, 255, 255};
		window->aRenderLine(stickMaker->getPosition(), vector2f(mouseX, mouseY), color);
	}
}