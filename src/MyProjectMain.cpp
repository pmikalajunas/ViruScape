#include "header.h"
#include "BaseEngine.h"
#include "MyProjectMain.h"

#include "JPGImage.h"
#include "TileManager.h"

#include "DisplayableObject.h"
#include "Tile.h"
#include "TileAnti.h"
#include "EnemyTile.h"
#include "Virus.h"
#include "MyPlayer.h"
#include <iostream>
#include "Constants.h"
#include <vector>
#include "ParallaxBg.h"

using namespace std; 


// Initialize tile x locations
vector<int> Tile::xTileLocations = {100, 200, 300, 400, 500, 520};
vector<int> Tile::xTileLocationsInitial(xTileLocations.begin(), xTileLocations.end()); 

// Initialize tile y locations
vector<int> Tile::yTileLocations = {20, 40, 60, 80};
vector<int> Tile::yTileLocationsInitial(yTileLocations.begin(), yTileLocations.end()); 


MyProjectMain::MyProjectMain(void) : BaseEngine( 50 ), 
m_state(stateInit), score(0), rectanglePosition(FROG_SELECTED)
{

	// Put frame on frog initially.
	rectangle = new SelectionRectangle(this, FROG_FRAME_X, FROG_FRAME_Y);
	reader = new FileReader();
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

	// Draw the static background for initial and end states.
	if(m_state == stateInit || m_state == endGame) {
		ImageData im;
		im.LoadImage( "bg.png" );
		im.RenderImageWithMask(this->GetBackground(), 0, 0, 0, 0, im.GetWidth(), im.GetHeight());
	}


	// Draw virus on the main screen as a logo.
	if(m_state == stateInit) {
		init_virus = new ImageSurface();
		virtual_guy_big = new ImageSurface();
		frog_big = new ImageSurface();
		pink_man_big = new ImageSurface();
	
		virtual_guy_big->LoadImage("virtual_guy_big.png");
		virtual_guy_big->RenderImage(
			GetBackground(),
			0, 0, 190, 220,
			virtual_guy_big->GetWidth(), virtual_guy_big->GetHeight()
		);

		frog_big->LoadImage("frog_big.png");
		frog_big->RenderImage(
			GetBackground(),
			0, 0, 340, 220,
			frog_big->GetWidth(), frog_big->GetHeight()
		);

		pink_man_big->LoadImage("pink_man_big.png");
		pink_man_big->RenderImage(
			GetBackground(),
			0, 0, 490, 220,
			pink_man_big->GetWidth(), pink_man_big->GetHeight()
		);

		init_virus->LoadImage("virus_main.png");
		init_virus->RenderImage(
			GetBackground(),
			0, 0, 540, 30,
			init_virus->GetWidth(), init_virus->GetHeight()
		);

		rectangle->Draw();
		// Redraw(false);
		// rectangle->RedrawBackground();
		
	}
 
	// Draw trophy next to leaderboard title.
	if(m_state == endGame) {
		trophy_image = new ImageSurface();

		trophy_image->LoadImage("trophy.png");
		trophy_image->RenderImage(
			GetBackground(),
			0, 0, 674, 50,
			trophy_image->GetWidth(), trophy_image->GetHeight()
		);
	}


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
	m_ppDisplayableObjects = new DisplayableObject*[11];

	// List of available x locations for tiles.
	vector<int> xLocations = Tile::xTileLocationsInitial;

	TileAnti* sanitizerTile = new TileAnti(this, xLocations[5], 250);
	MyPlayer* player = new MyPlayer(this, sanitizerTile, rectanglePosition);
	Virus* virus =  new Virus(this, player);
	EnemyTile* enemyTile = new EnemyTile(this, xLocations[0], 300, virus);	

	// You MUST set the array entry after the last one that you create to NULL, so that ,the system knows when to stop.
	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in order to work out where the end of the array is.
	m_ppDisplayableObjects[0] = player;
	m_ppDisplayableObjects[1] = enemyTile;
	m_ppDisplayableObjects[2] = new Tile(this, xLocations[1], 500);
	m_ppDisplayableObjects[3] = new Tile(this, xLocations[2], 350);
	m_ppDisplayableObjects[4] = new Tile(this, xLocations[3], 200);
	m_ppDisplayableObjects[5] = new Tile(this, xLocations[4], 400);
	m_ppDisplayableObjects[6] = virus;
	m_ppDisplayableObjects[7] = new ParallaxBg(this, 0);
	// Another background will take over the first, creating infinite sky illusion.
	m_ppDisplayableObjects[8] = new ParallaxBg(this, - BASE_SCREEN_HEIGHT);
	m_ppDisplayableObjects[9] = sanitizerTile;
	m_ppDisplayableObjects[10] = NULL;

	return 0;
}


void MyProjectMain::intialiseFonts(){
	smallFont = GetFont("neuropol x rg.ttf", 16);
	mediumFont = GetFont("neuropol x rg.ttf", 20);
	largeFont = GetFont("neuropol x rg.ttf", 52);
}


/* Draw text labels */
void MyProjectMain::DrawStrings()
{
	// NEW SWITCH
	switch( m_state )
	{
		case stateInit:
			CopyBackgroundPixels( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
			DrawScreenString( 169, 30, "ViruScape", 0x0, largeFont );
			char buf[128];
			sprintf( buf, "Playing as %s", reader->getPlayer().c_str());
			DrawScreenString( 174, 93, buf, 0x0, mediumFont );
			DrawScreenString( 150, 410, "Arrow Keys to select character", 0x0, mediumFont );
			DrawScreenString( 150, 430, "Press 'Space' to play the game", 0x0, mediumFont );
			DrawScreenString( 150, 450, "Press 'Esc' to exit the game", 0x0, mediumFont );
			SetNextUpdateRect( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
			break;
		case stateMain:
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
			DrawScreenString( 110, 50, "LEADERBOARD", 0x0, largeFont );
			unordered_map<string, int> scores = reader->getScores();
			int y = 120;
			for (auto& x : scores){
				char buf[64];
				sprintf( buf, "%s: %d", x.first.c_str(), x.second);
				DrawScreenString( 160, y, buf, 0x0, mediumFont );
				y += 20;
			}
			DrawScreenString( 150, 430, "Press 'Space' to play again", 0x0, mediumFont );
			DrawScreenString( 150, 450, "Press 'Esc' to exit the game", 0x0, mediumFont );
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
	SetTimeToAct( 5 );

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
			MyPlayer* myPlayer = dynamic_cast<MyPlayer*>(m_ppDisplayableObjects[0]);
			// End the game if ball touched the ground.
			if (myPlayer->getTouchedGround()) {
				m_state = endGame;
				// Add and Save player's score.
				reader->addScore(score);
				reader->writeScores();
				// Force redraw of background.
				SetupBackgroundBuffer();
				// Redraw the whole screen now.
				Redraw(true);
				return;
			}
			
			// If player touched a tile, get the tiles moving.
			if (dynamic_cast<Tile*>(m_ppDisplayableObjects[i]) != NULL && myPlayer->getTileCollision()) {
				Tile* tile = dynamic_cast<Tile*>(m_ppDisplayableObjects[i]);
				tile->setTileYSpeed(TILE_SPEED_AFTER_BOUNCE);
				score += 1;
			}

			if ( m_iDrawableObjectsChanged )
				return; // Abort! Something changed in the array
		}
		MyPlayer* myPlayer = dynamic_cast<MyPlayer*>(m_ppDisplayableObjects[0]);
		myPlayer->setTileCollision(false);

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
			case endGame:
				m_state = stateMain;
				// Force redraw of background
				SetupBackgroundBuffer();
				resetGame();
				// Redraw the whole screen now
				Redraw(true);
				break;
			} // End switch on current state
			break;
		case SDLK_LEFT:
			if(m_state == stateInit) {
				if(rectanglePosition == FROG_SELECTED) {
					rectanglePosition = V_GUY_SELECTED;
					rectangle->setPosition(V_GUY_FRAME_X, V_GUY_FRAME_Y);
					SetupBackgroundBuffer();
					// rectangle->RedrawBackground();
					// rectangle->Draw();
					Redraw(true);
				} 
				else if(rectanglePosition == PINK_M_SELECTED) {
					rectanglePosition = FROG_SELECTED;
					rectangle->setPosition(FROG_FRAME_X, FROG_FRAME_Y);
					SetupBackgroundBuffer();
					// rectangle->RedrawBackground();
					// rectangle->Draw();
					Redraw(true);
				}
			}
			break;
		case SDLK_RIGHT:
			if(m_state == stateInit) {
				if(rectanglePosition == V_GUY_SELECTED) {
					rectanglePosition = FROG_SELECTED;
					rectangle->setPosition(FROG_FRAME_X, FROG_FRAME_Y);
					SetupBackgroundBuffer();
					// rectangle->RedrawBackground();
					// rectangle->Draw();
					Redraw(true);
				} 
				else if(rectanglePosition == FROG_SELECTED) {
					rectanglePosition = PINK_M_SELECTED;
					rectangle->setPosition(P_M_FRAME_X, P_M_FRAME_Y);
					SetupBackgroundBuffer();
					// rectangle->RedrawBackground();
					// rectangle->Draw();
					Redraw(true);
				}
			}
			break;
	}
}

/*
	Resets the game after player have lost.
*/
void::MyProjectMain::resetGame() {
	reader = new FileReader();
	InitialiseObjects();
	score = 0;
}


/* 
	Draw the changes to the screen.
	Remove the changing objects, redraw the strings and draw the changing objects again.
*/
void MyProjectMain::DrawChanges()
{
	// Don't update objects if we are in either starting or finishing state.
	if ( m_state == stateInit || m_state == endGame )
		return; // Do not draw objects if initialising

	// Remove objects from their old positions
	UndrawChangingObjects();
	// Draw the text for the user
	DrawStrings();
	// Draw objects at their new positions
	DrawChangingObjects();
}

/* 	
	Draw the screen - copy the background buffer, then draw the text and objects. 
*/
void MyProjectMain::DrawScreen()
{

	// Prevent from drawing background in main state, we have moving bg.
	if (m_state != stateMain) {
		CopyAllBackgroundBuffer();
	}
	
	// And finally, draw the text
	DrawStrings();

	// Don't draw objects if we are in either starting or finishing state.
	if ( m_state == stateInit || m_state == endGame )
		return; 

	// Then draw the changing objects
	DrawChangingObjects();
}