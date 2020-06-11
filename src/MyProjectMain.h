#ifndef MYPROJECTMAIN_H
#define MYPROJECTMAIN_H

#include "BaseEngine.h"

#define BASE_SCREEN_WIDTH 800
#define BASE_SCREEN_HEIGHT 600

class MyProjectMain : public BaseEngine
{
public:

	/**
	Constructor
	*/
	MyProjectMain()
	: BaseEngine( 6 )
	{}

	// Do any setup of back buffer prior to locking the screen buffer
	// Basically do the drawing of the background in here and it'll be copied to the screen for you as needed
	virtual void SetupBackgroundBuffer();

	// Create any moving objects
	int InitialiseObjects();

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
};

#endif
