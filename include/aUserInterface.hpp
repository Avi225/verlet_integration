#pragma once
#include <string>
#include "aMath.hpp"
#include "aWindow.hpp"

class aSliderF
{
public:

	aSliderF(float* pValue, vector2f pPosition, int pLength, std::string pName, float pMinimumValue, float pMaximumValue)
		: value(pValue), position(pPosition), length(pLength), name(pName), minimumValue(pMinimumValue), maximumValue(pMaximumValue)
	{}

	void updateSlider();

	vector2f getPosition();
	void setPosition(vector2f pPosition);

	int getLength();
	void setLength(int pLength);

	void setSelected(bool pSelected);
	bool getSelected();
	void switchSelected();

	float getValue();
	void setValue(float pValue);

	float getMinimumValue();
	void setMinimumValue(float pMinimumValue);

	float getMaximumValue();
	void setMaximumValue(float pMaximumValue);

	std::string getName();
	void setName(std::string pName);

private:

	float* value;

	vector2f position;

	int length;

	std::string name;

	float minimumValue, maximumValue;

	bool selected = false;
};

class aSwitchB
{
public:
	aSwitchB(bool* pValue, vector2f pPosition, std::string pName)
		: value(pValue), position(pPosition), name(pName)
	{}

	void switchValue();

	vector2f getPosition();
	void setPosition(vector2f pPosition);

	std::string getName();
	void setName(std::string pName);

	bool getValue();
	void setValue(bool pValue);

private:

	bool* value;

	vector2f position;

	std::string name;
};

class aText
{
public:

	aText(vector2f pPosition, std::string pName)
		: position(pPosition), name(pName)
	{}

	std::string getName();
	void setName(std::string pName);

	vector2f getPosition();
	void setPosition(vector2f pPosition);

private:

	vector2f position;

	std::string name;
};


class aHeader
{
public:
 
	aHeader(vector2f pPosition, std::string pName)
		: position(pPosition), name(pName)
	{}

	std::string getName();
	void setName(std::string pName);

	vector2f getPosition();
	void setPosition(vector2f pPosition);

private:

	vector2f position;

	std::string name;
};

class aUserInterface
{
public:
	aUserInterface(aWindow* pWindow)
		: window(pWindow)
	{}

	aSliderF* checkSelectedSlider();
	aSwitchB* checkPressedSwitch();

	void unselectAllSliders();

	void updateUserInterface();

	void renderSliderFs();
	void renderSwitchBs();
	void renderHeaders();
	void renderTexts();

	void createSliderF(aSliderF pSlider);
	void createSwitchB(aSwitchB pSwitch);
	void createHeader(aHeader pHeader);
	void createText(aText pText);

private:

	aWindow* window;
	std::vector<aSliderF> sliders;
	std::vector<aSwitchB> switches;
	std::vector<aHeader> headers;
	std::vector<aText> texts;
};