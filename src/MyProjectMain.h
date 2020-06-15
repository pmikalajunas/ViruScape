#ifndef MYPROJECTMAIN_H
#define MYPROJECTMAIN_H

#include "BaseEngine.h"
#include "FileReader.h"
#include <unordered_map>
#include "JPGImage.h"

using namespace std;


class MyProjectMain : public BaseEngine
{
public:

	MyProjectMain(void);
	~MyProjectMain(void);

	// Do any setup of back buffer prior to locking the screen buffer
	// Basically do the drawing of the background in here and it'll be copied to the screen for you as needed
	virtual void SetupBackgroundBuffer();

	// Create any moving objects
	int InitialiseObjects();
	void intialiseFonts();

	/** Draw any strings */
	void DrawStrings();

	/**
	The game logic - move things and change the state if necessary.
	Must call Redraw(true/false) if anything changes that shows on the screen.
	*/
	virtual void GameAction();

	virtual void UpdateAllObjects( int iCurrentTime );

	// Handle pressing of a key
	virtual void KeyDown(int iKeyCode);

	void DrawScreen();
	void DrawChanges();

	void resetGame();


public:
	// State number
	enum State { stateInit, stateMain, statePaused, endGame };

private:
	FileReader* reader;
	// Virus image drawn on the main screen.
	ImageSurface* init_virus;
	ImageSurface* trophy_image;
	ImageSurface* virtual_guy_big;
	ImageSurface* frog_big;
	ImageSurface* pink_man_big;

	State m_state;
	int score;

	Font* smallFont;
	Font* mediumFont;
	Font* largeFont;


};

#endif
