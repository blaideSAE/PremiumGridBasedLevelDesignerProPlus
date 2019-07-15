#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include "arial.h"
using namespace std;

void HideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

// I declare the window size here so i can refer to it in classes as the window is created in main, and other funcions can't assume there is a window, also cant create the window here,.. i tried that.
int windowWidth = 500;
int windowHeight = 800;
bool debounceEscape = false;

bool debounceClick = false;
const int x = 5;
const int y = 5;
// an enum for menu nav i just switch through this every frame, each state has a way of getting to other states.
enum ProgramState{mainWindow};
ProgramState programState = mainWindow;

class Tile : public sf::Drawable, public sf::Transformable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{

		target.draw(shape, states);
	}
public:
	float width = 100;
	float height = 100;
	float xPos = 0;
	float yPos = 0;
	enum Type {Air,Ground,Enemy,Coin,Spawn};
	bool clicked = true;

	Type type = Tile::Air;
	sf::RectangleShape shape;
	sf::FloatRect rBounds;
	void init(float x, float y, bool cl) 
	{
		clicked = cl;
		shape.setOutlineColor(sf::Color::Black);
		shape.setOutlineThickness(1.0f);
		shape.setSize(sf::Vector2f(width, height));
		shape.setPosition(x,y);

		//if (type == Tile::Air)
		//
		//}
		if (clicked)
		{
			shape.setFillColor(sf::Color::Black);
		}
		else 
		{
			shape.setFillColor(sf::Color::White);
		}

		
		
	}
	Tile() 
	{
	}
	Tile(Type t, float x, float y)
	{
		type = t;
		shape.setOutlineColor(sf::Color::Black);
		shape.setOutlineThickness(1.0f);
		shape.setSize(sf::Vector2f(width, height));
		shape.setPosition(x, y);

		//if (type == Tile::Air)
		//{

		//}

		shape.setFillColor(sf::Color::Black);
	}

	bool mouseOver(sf::Vector2i windPos)
	{
		rBounds = shape.getGlobalBounds();
		sf::Vector2i mousePos;
		mousePos.x = sf::Mouse::getPosition().x - windPos.x - 8;
		mousePos.y = sf::Mouse::getPosition().y - windPos.y - 30;
		if (rBounds.contains(mousePos.x, mousePos.y))
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	void refresh() 
	{
		if (clicked)
		{
			shape.setFillColor(sf::Color::Black);
		}
		else
		{
			shape.setFillColor(sf::Color::White);
		}
	}

};



class Button : public sf::Drawable , public sf::Transformable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{

		target.draw(rect, states);
		target.draw(text, states);
	}

public:

	float textSize = 25;
	float textOutline = 2;
	float rectOutline = 2;
	sf::RectangleShape rect;
	sf::Font font;
	sf::Text text;
	sf::FloatRect rBounds;
	//Title init
	Button()
	{
		if (!font.loadFromFile("arial.ttf"))
		{
			font.loadFromMemory(&arial_ttf, arial_ttf_size);
		}
		
		text.setFont(font);
		text.setCharacterSize(textSize);
		text.setFillColor(sf::Color::White);
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(textOutline);
		text.setStyle(sf::Text::Regular);

		rect.setFillColor(sf::Color::White);
		rect.setOutlineColor(sf::Color::Black);
		rect.setOutlineThickness(rectOutline);
		
	}
	bool mouseOver(sf::Vector2i windPos)
	{
		rBounds = rect.getGlobalBounds();
		sf::Vector2i mousePos;
		mousePos.x = sf::Mouse::getPosition().x  - windPos.x -8;
		mousePos.y = sf::Mouse::getPosition().y  - windPos.y -30;
		if (rBounds.contains(mousePos.x,mousePos.y)) 
		{
			return true;
		}
		else
		{
			return false;
		}
			
	}



};

class UI
{
public:
	//Text Variable delcarations
	float titleSize = 60;
	float titleOutline = 6;
	float uiTextSize = 30;
	float uiTextOutline = 3;
	
	//Font init
	sf::Font font;
	//Text declarations
	sf::Text title;
	sf::Text gameOver;
	//Button declarations
;
	Button mainMenuButton;
	Button exitButton;
	Button resumeButton;
	//panel
	sf::RectangleShape panel;
	sf::Vector2f panelSize = sf::Vector2f(350, 550);
	UI()
	{
		//Loading the font, I check to see if there is a font in the run dir, if not load the one i've embedded using a BIN2C converter. 
		if (!font.loadFromFile("arial.ttf"))
		{
			font.loadFromMemory(&arial_ttf, arial_ttf_size);
		}

		//Text initialisations -----------------------------------

		//Title init
		title.setString("LevelEditor");
		title.setFont(font);
		title.setPosition((windowWidth / 2) - ((title.getGlobalBounds().width / 2) + 75), 200);
		title.setCharacterSize(titleSize);
		title.setFillColor(sf::Color::White);
		title.setOutlineColor(sf::Color::Black);
		title.setOutlineThickness(titleOutline);
		title.setStyle(sf::Text::Regular);

		//panel Init
		panel.setSize(panelSize);
		panel.setFillColor(sf::Color(255,255,255,150));
		panel.setOutlineColor(sf::Color::Black);
		panel.setOutlineThickness(1.0f);
		panel.setPosition((windowWidth / 2) - (panelSize.x / 2), 180);

		//Buttons Initialisations -------------------------------

		//Main Menu Button Init
		mainMenuButton.text.setString("Main Menu");
		mainMenuButton.rect.setSize(sf::Vector2f(150, 35));
		mainMenuButton.rect.setPosition(((windowWidth / 2) - mainMenuButton.rect.getGlobalBounds().width / 2) , 600);
		mainMenuButton.text.setPosition(((windowWidth / 2) - mainMenuButton.text.getGlobalBounds().width / 2) , 600);
		//Exit Button Init
		exitButton.text.setString("Exit");
		exitButton.rect.setSize(sf::Vector2f(60, 35));
		exitButton.rect.setPosition(((windowWidth / 2) - exitButton.rect.getGlobalBounds().width / 2), 550);
		exitButton.text.setPosition(((windowWidth / 2) - exitButton.text.getGlobalBounds().width / 2), 550);
		//Resume Button Init
		resumeButton.text.setString("Resume");
		resumeButton.rect.setSize(sf::Vector2f(100, 35));
		resumeButton.rect.setPosition(((windowWidth / 2) - resumeButton.rect.getGlobalBounds().width / 2), 400);
		resumeButton.text.setPosition(((windowWidth / 2) - resumeButton.text.getGlobalBounds().width / 2), 400);
}
};

void load(Tile tile[x][y])
{
	// reading a text file

	string line;
	ifstream myfile("save.Txt");
	if (myfile.is_open())
	{
		int a = 0;
		int b = 0;
		string saveHold;
		while (getline(myfile, line))
		{
			for (int i = 0; i < line.size(); i++) {
				switch (line[i]) 
				{

				case ',':
					 b += 1;
					break;

				case '1':
					tile[b][a].clicked = true;
					tile[b][a].refresh();
					break;
				case '0':
					tile[b][a].clicked = false;
					tile[b][a].refresh();
					break;
				}

			}

			a += 1;
			b = 0;
		}
		myfile.close();
		cout << "file Loaded";
	}
	else cout << "Unable to open file";

}
void save(Tile tile[x][y])
{
	// writing on a text file
	ofstream myfile("save.Txt");
	if (myfile.is_open())
	{

		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				myfile << tile[j][i].clicked;
				myfile << ",";
			}
			myfile << "\n";
		}

		myfile.close();
		cout << "file Saved";
	}
	else 
	{ 
		cout << "Unable to open file"; 
	}

}
void printToConsole(Tile tile[x][y], bool basicMode)
{
	if (basicMode) {

		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				cout << tile[j][i].clicked;
				cout << ",";
			}
			cout << "\n";
		}
		cout << "success \n";
	}
	else 
	{
		int Count=0;
		int clicked=0;

		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				cout << tile[j][i].clicked;
				cout << ",";
			}
			cout << "\n";
		}
		cout << "success \n";

	}
}

int main()
{
	//window init -- This stuff just sets up the rendering window, and hides the console.
	//HideConsole();
	sf::RenderWindow window(sf::VideoMode(windowWidth,windowHeight), "Slay the evil bricks.", sf::Style::Titlebar | sf::Style::Close);
	
	//Menu init
	//I just use these to get a true only on the frame that it was clicked down, and not just a true for it being pressed down frame after frame.


    //Gameround Start stuff.
	// the game has a UI, level made up of bricks, a ball and a paddle.
	//UI ui;

	Tile tile[x][y];
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			float width = tile[i][j].width;
			float height = tile[i][j].height;

			tile[i][j].init(i* width + ((windowWidth / 2) - ((width*x) / 2)), j*height + 100, true);

		}
	}

	// This is the main loop,.. Or Game loop.. 
	while (window.isOpen())
	{ 
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) 
			{

			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyReleased:

				switch (event.key.code) 
				{
				case sf::Keyboard::Escape:

					break;

				case sf::Keyboard::P:

					printToConsole(tile, false);

					break;
				case sf::Keyboard::S:

					save(tile);

					break;
				case sf::Keyboard::L:

					load(tile);

					break;
				}
				break;

			}


	
		}

		window.clear(sf::Color::White);

		switch (programState) 
		{
			case mainWindow:

				for (int i = 0; i < x; i++)
				{
					for (int j = 0; j < y; j++)
					{
						float width = tile[i][j].width;
						float height = tile[i][j].height;

						if (tile[i][j].mouseOver(window.getPosition()) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !debounceClick)
						{
							tile[i][j].clicked = !tile[i][j].clicked;
							tile[i][j].refresh();

							debounceClick = true;
						}
						else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && debounceClick)
						{
							debounceClick = false;
						}

				
						window.draw(tile[i][j]);

					}
				}

				window.display();

			break;

		}
		

	}
}
