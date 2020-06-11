#include "header.h"

// This is a basic implementation, without fancy stuff

#include "BaseEngine.h"

#include "MyProjectMain.h"

#include "JPGImage.h"

#include "TileManager.h"

#include "DisplayableObject.h"
#include "Tile.h"
#include "MyBall.h"
#include <iostream>

using namespace std; 


MyProjectMain::MyProjectMain(void) : BaseEngine( 50 ), 
m_state(stateInit), score(0)
{

	reader = new FileReader();
	reader->readScores("scores.txt");

	intialiseFonts();

}

MyProjectMain::~MyProjectMain(void)
{
}


/*
Do any setup of back buffer prior to locking the screen buffer
Basically do the drawing of the background in here and it'll be copied to the screen for you as needed
*/
void MyProjectMain::SetupBackgroundBuffer()
{
	FillBackground( 0xffffff );

}


/*
In here you need to create any movable objects that you wish to use.
Sub-classes need to implement this function.
*/
int MyProjectMain::InitialiseObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();

	// Create an array one element larger than the number of objects that you want.
	m_ppDisplayableObjects = new DisplayableObject*[6];

	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.
	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in order to work out where the end of the array is.
	m_ppDisplayableObjects[0] = new MyBall(this, 60);
	m_ppDisplayableObjects[1] = new Tile(this, 100, 300, 150);
	m_ppDisplayableObjects[2] = new Tile(this, 500, 500, 150);
	m_ppDisplayableObjects[3] = new Tile(this, 100, 600, 150);
	m_ppDisplayableObjects[4] = new Tile(this, 500, 200, 150);
	m_ppDisplayableObjects[5] = NULL;

	return 0;
}


void MyProjectMain::intialiseFonts(){
	smallFont = GetFont("neuropol x rg.ttf", 16);
	mediumFont = GetFont("neuropol x rg.ttf", 20);
	largeFont = GetFont("neuropol x rg.ttf", 48);
}


/* Draw text labels */
void MyProjectMain::DrawStrings()
{
	// NEW SWITCH
	switch( m_state )
	{
		case stateInit:
			CopyBackgroundPixels( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
			DrawScreenString( 169, 280, "Initialised and waiting for SPACE", 0x0, mediumFont );
			SetNextUpdateRect( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
			break;
		case stateMain:
			char buf[64];
			sprintf( buf, "Score:%d", score);
			CopyBackgroundPixels( 0/*X*/, 0/*Y*/, GetScreenWidth(), 30/*Height*/ );
			DrawScreenString(600, 10, buf, 0x0, mediumFont );
			SetNextUpdateRect( 0/*X*/, 0/*Y*/, GetScreenWidth(), 30/*Height*/ );
			break;
		case statePaused:
			CopyBackgroundPixels( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
			DrawScreenString( 169, 280, "Paused. Press SPACE to continue", 0x0, mediumFont );
			SetNextUpdateRect( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
			break;
		case endGame:
			CopyBackgroundPixels( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
			DrawScreenString( 169, 280, "Scores", 0x0, smallFont );

			unordered_map<string, int> scores = reader->getScores();
			int y = 300;
			for (auto& x : scores){
				char buf[64];
				sprintf( buf, "%s: %d", x.first.c_str(), x.second);
				DrawScreenString( 169, y, buf, 0x0, smallFont );
				y += 20;
			}


			SetNextUpdateRect( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );


			break;
	}
}

/* Overridden GameAction which can be modified */
void MyProjectMain::GameAction()
{
	// If too early to act then do nothing
	if ( !TimeToAct() )
		return;

	// Don't act for another 10 ticks
	SetTimeToAct( 1 );

	// NEW SWITCH
	switch( m_state )
	{
	case stateInit:
	case statePaused:
	case endGame:
		break;
	case stateMain:
		// Only tell objects to move when not paused etc
		UpdateAllObjects( GetTime() );
		break;
	}
}


void MyProjectMain::UpdateAllObjects(int iCurrentTime) {

	m_iDrawableObjectsChanged = 0;
	if ( m_ppDisplayableObjects != NULL )
	{
		for ( int i = 0 ; m_ppDisplayableObjects[i] != NULL ; i++ )
		{
			m_ppDisplayableObjects[i]->DoUpdate(iCurrentTime);
			MyBall* myBall = dynamic_cast<MyBall*>(m_ppDisplayableObjects[0]);
			// End the game if ball touched the ground.
			if (myBall->getTouchedGround()) {
				m_state = endGame;
				// Force redraw of background
				SetupBackgroundBuffer();
				// Redraw the whole screen now
				Redraw(true);
				return;
			}

			
			// If it's a tile object
			if (i != 0 && myBall->getTileCollision()) {
				Tile* tile = dynamic_cast<Tile*>(m_ppDisplayableObjects[i]);
				tile->setTileYSpeed(0.2);
				score += 1;
			}
			if ( m_iDrawableObjectsChanged )
				return; // Abort! Something changed in the array
		}
		MyBall* myBall = dynamic_cast<MyBall*>(m_ppDisplayableObjects[0]);
		myBall->setTileCollision(false);

	}

}


/*
Handle any key presses here.
Note that the objects themselves (e.g. player) may also check whether a key is currently pressed
*/
void MyProjectMain::KeyDown(int iKeyCode)
{
	switch ( iKeyCode )
	{
        case SDLK_ESCAPE: // End program when escape is pressed
            SetExitWithCode( 0 );
            break;

		case SDLK_SPACE: // SPACE Pauses
			switch( m_state )
			{
			case stateInit:
				// Go to state main
				m_state = stateMain;
				// Force redraw of background
				SetupBackgroundBuffer();
				// Redraw the whole screen now
				Redraw(true);
				break;
			case stateMain:
				// Go to state paused
				m_state = statePaused;
				// Force redraw of background
				SetupBackgroundBuffer();
				// Redraw the whole screen now
				Redraw(true);
				break;
			case statePaused:
				// Go to state main
				m_state = stateMain;
				// Force redraw of background
				SetupBackgroundBuffer();
				// Redraw the whole screen now
				Redraw(true);
				break;
			} // End switch on current state
			break; // End of case SPACE
	}

}


/* Draw the changes to the screen.
Remove the changing objects, redraw the strings and draw the changing objects again.
 */
void MyProjectMain::DrawChanges()
{
	// NEW IF
	if ( m_state == stateInit || m_state == endGame )
		return; // Do not draw objects if initialising

	// Remove objects from their old positions
	UndrawChangingObjects();
	// Draw the text for the user
	DrawStrings();
	// Draw objects at their new positions
	DrawChangingObjects();
}

/* Draw the screen - copy the background buffer, then draw the text and objects. */
void MyProjectMain::DrawScreen()
{
	// First draw the background
	//this->CopyBackgroundPixels( 100, 100, 100, 100 );
	CopyAllBackgroundBuffer();
	// And finally, draw the text
	DrawStrings();

	// NEW IF
	if ( m_state == stateInit || m_state == endGame )
		return; // Do not draw objects if initialising

	// Then draw the changing objects
	DrawChangingObjects();
}