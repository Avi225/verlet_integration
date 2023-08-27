#include "aUserInterface.hpp"

vector2f aSliderF::getPosition()
{
	return (position);
}

void aSliderF::setPosition(vector2f pPosition)
{
	position = pPosition;
}

int aSliderF::getLength()
{
	return (length);
}

void aSliderF::setLength(int pLength)
{
	length = pLength;
}

void aSliderF::setSelected(bool pSelected)
{
	selected = pSelected;
}

bool aSliderF::getSelected()
{
	return (selected);
}

void aSliderF::switchSelected()
{
	selected = !selected;
}

float aSliderF::getValue()
{
	return (*value);
}

void aSliderF::setValue(float pValue)
{
	*value = pValue;
}

float aSliderF::getMinimumValue()
{
	return (minimumValue);
}

void aSliderF::setMinimumValue(float pMinimumValue)
{
	minimumValue = pMinimumValue;
}

float aSliderF::getMaximumValue()
{
	return (maximumValue);
}

void aSliderF::setMaximumValue(float pMaximumValue)
{
	maximumValue = pMaximumValue;
}

std::string aSliderF::getName()
{
	return (name);
}

void aSliderF::setName(std::string pName)
{
	name = pName;
}

void aSliderF::updateSlider()
{
	if (selected)
	{
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		*value = mapRange(mouseX, position.x, position.x + length, minimumValue, maximumValue);
		if (*value > maximumValue)
			*value = maximumValue;
		if (*value < minimumValue)
			*value = minimumValue;
	}
}

void aSwitchB::switchValue()
{
	*value = !*value;
}

vector2f aSwitchB::getPosition()
{
	return (position);
}

void aSwitchB::setPosition(vector2f pPosition)
{
	position = pPosition;
}

std::string aSwitchB::getName()
{
	return (name);
}

void aSwitchB::setName(std::string pName)
{
	name = pName;
}

bool aSwitchB::getValue()
{
	return (*value);
}

void aSwitchB::setValue(bool pValue)
{
	*value = pValue;
}

std::string aHeader::getName()
{
	return (name);
}

void aHeader::setName(std::string pName)
{
	name = pName;
}

vector2f aHeader::getPosition()
{
	return (position);
}

void aHeader::setPosition(vector2f pPosition)
{
	position = pPosition;
}

std::string aText::getName()
{
	return (name);
}

void aText::setName(std::string pName)
{
	name = pName;
}

vector2f aText::getPosition()
{
	return (position);
}

void aText::setPosition(vector2f pPosition)
{
	position = pPosition;
}

int* aIntDisplay::getValue()
{
	return (value);
}
void aIntDisplay::setValue(int* pValue)
{
	value = pValue;
}

vector2f aIntDisplay::getPosition()
{
	return (position);
}
void aIntDisplay::setPosition(vector2f pPosition)
{
	position = pPosition;
}

void aUserInterface::createSliderF(aSliderF pSlider)
{
	sliders.push_back(pSlider);
}
void aUserInterface::createSwitchB(aSwitchB pSwitch)
{
	switches.push_back(pSwitch);
}
void aUserInterface::createHeader(aHeader pHeader)
{
	headers.push_back(pHeader);
}
void aUserInterface::createText(aText pText)
{
	texts.push_back(pText);
}

void aUserInterface::createIntDisplay(aIntDisplay pDisplay)
{
	displays.push_back(pDisplay);
}


aSliderF* aUserInterface::checkSelectedSlider()
{
	if (sliders.size() > 0)
	{
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		aSliderF* best = &sliders[sliders.size() - 1];
		vector2f pointPosition;
		vector2f bestPosition;
		for (int i = 0; i < int(sliders.size()); i++)
		{
			pointPosition = vector2f(mapRange(sliders[i].getValue(), sliders[i].getMinimumValue(), sliders[i].getMaximumValue(), sliders[i].getPosition().x, sliders[i].getPosition().x + sliders[i].getLength()), sliders[i].getPosition().y);
			bestPosition = vector2f(mapRange(best->getValue(), best->getMinimumValue(), best->getMaximumValue(), best->getPosition().x, best->getPosition().x + best->getLength()), best->getPosition().y);
			if (vector2f(mouseX, mouseY).distance(pointPosition) < vector2f(mouseX, mouseY).distance(bestPosition))
				best = &sliders[i];
		}
		if (vector2f(mouseX, mouseY).distance(bestPosition) < 6)
			return (best);
		else
			return (NULL);

		delete best;
	} else
	{
		return (NULL);
	}
}

aSwitchB* aUserInterface::checkPressedSwitch()
{
	if (switches.size() > 0)
	{
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		aSwitchB* pressed = NULL;
		for (int i = 0; i < int(switches.size()); i++)
		{
			if (mouseX > switches[i].getPosition().x && mouseX < switches[i].getPosition().x + 12 && mouseY > switches[i].getPosition().y && mouseY < switches[i].getPosition().y + 12)
			{
				pressed = &switches[i];
			}
		}
		return (pressed);
	} else
		return (NULL);
}

void aUserInterface::unselectAllSliders()
{
	for (int i = 0; i < int(sliders.size()); i++)
	{
		sliders[i].setSelected(false);
	}
}

void aUserInterface::updateUserInterface()
{
	for (int i = 0; i < int(sliders.size()); i++)
	{
		sliders[i].updateSlider();
	}
	renderSliderFs();
	renderSwitchBs();
	renderHeaders();
	renderTexts();
	renderDisplays();
}

void aUserInterface::renderSliderFs()
{
	TTF_Font* font = TTF_OpenFont("res/font.ttf", 12);
	SDL_Color color = {255, 255, 255, 255};
	SDL_Rect rect;
	for (int i = 0; i < int(sliders.size()); i++)
	{
		rect = {int(sliders[i].getPosition().x), int(sliders[i].getPosition().y) - 1, sliders[i].getLength(), 2};
		window->aRenderRectangle(rect, color);
		vector2f point;
		point.x = mapRange(sliders[i].getValue(), sliders[i].getMinimumValue(), sliders[i].getMaximumValue(), sliders[i].getPosition().x, sliders[i].getPosition().x + sliders[i].getLength());
		point.y = sliders[i].getPosition().y;
		window->aRenderFillCircle(point, 4, color);
		window->aRenderText(font, vector2f(sliders[i].getPosition().x, sliders[i].getPosition().y + 4), (sliders[i].getName() + ": " + std::to_string(sliders[i].getValue()).substr(0, std::to_string(sliders[i].getValue()).size() - 4)).c_str(), color);
	}
	TTF_CloseFont(font);
}

void aUserInterface::renderSwitchBs()
{
	TTF_Font* font = TTF_OpenFont("res/font.ttf", 12);
	SDL_Color color = {255, 255, 255, 255};
	SDL_Rect rect;
	for (int i = 0; i < int(switches.size()); i++)
	{
		rect = {int(switches[i].getPosition().x), int(switches[i].getPosition().y), 12, 12};
		window->aRenderRectangle(rect, color);
		if (switches[i].getValue())
			color = {255, 255, 255, 255};
		else
			color = {0, 0, 0, 255};
		rect = {rect.x + 2, rect.y + 2, rect.w - 4, rect.h - 4};
		window->aRenderRectangle(rect, color);
		color = {255, 255, 255, 255};
		window->aRenderText(font, vector2f(switches[i].getPosition().x + 18, switches[i].getPosition().y - 2), switches[i].getName().c_str(), color);
	}
	TTF_CloseFont(font);
}

void aUserInterface::renderHeaders()
{
	TTF_Font* font = TTF_OpenFont("res/fontBlack.ttf", 12);
	SDL_Color color = {255, 255, 255, 255};
	for (int i = 0; i < int(headers.size()); i++)
	{
		window->aRenderText(font, vector2f(headers[i].getPosition().x, headers[i].getPosition().y), headers[i].getName().c_str(), color);
	}
	TTF_CloseFont(font);
}

void aUserInterface::renderTexts()
{
	TTF_Font* font = TTF_OpenFont("res/font.ttf", 12);
	SDL_Color color = {255, 255, 255, 255};
	for (int i = 0; i < int(texts.size()); i++)
	{
		window->aRenderText(font, vector2f(texts[i].getPosition().x, texts[i].getPosition().y), texts[i].getName().c_str(), color);
	}
	TTF_CloseFont(font);
}

void aUserInterface::renderDisplays()
{
	TTF_Font* font = TTF_OpenFont("res/font.ttf", 12);
	SDL_Color color = {255, 255, 255, 255};
	for (int i = 0; i < int(displays.size()); i++)
	{
		window->aRenderText(font, vector2f(displays[i].getPosition().x, displays[i].getPosition().y + 4), std::to_string(*displays[i].getValue()).c_str(), color);
	}
	TTF_CloseFont(font);
}