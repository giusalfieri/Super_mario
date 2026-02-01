#pragma once
#include <string>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QTimer>
#include <QSound>

#include "Hud.h"
#include "Mario.h"
#include "LevelManager.h"
#include "SpinningItem.h"

class Game : public QGraphicsView
{
	Q_OBJECT

		enum game_state { READY, RUNNING, PAUSE, GAME_OVER, CHANGE_LEVEL, END_OF_LEVEL };
	private:

		static Game* uniqueInstance;     // Singleton design pattern
		Game(QWidget* parent = nullptr);	     // Singleton design pattern

	
		QGraphicsScene* cur_scene;           // the scene used to render current game level (2D)
		std::vector<QGraphicsScene*> levels; 
		int currentLevelIdx;                 // Indice per sapere in quale parte del livello siamo


		QGraphicsScene* black_scene;     // the scene displayed when level changes (i.e black screen)
		Mario* mario;                    // mario object
		QTimer engine;                   // game engine / timer
		QTimer* game_time;               // game time remaining
		game_state cur_state;            // current game state


		std::vector<QSound*> playlist;
		std::vector<QSound*> fast_playlist;
		
		int lives;
		int score;
	
		SpinningItem* spinning_item;

		// flags
		bool hurry_up;                   // is game time under 100 seconds?
		bool key_up_pressed;             // is key up pressed?
		

		int clear_level_counter;         // counts the number of frames since level has been cleared

		std::string cur_level_name;                 // current level's name
		std::vector <QGraphicsLineItem*> grid;		// scene grid (for debugging)
	
		// utility functions
		std::string state2str();
		//void nextLevel();
		//void prevLevel();
		void switchSubLevel(int direction);           // Replacement for nextLevel/prevLevel
		QPointF getSpawnPoint(int idx, int direction); // Handles spawn coordinates
		void fastResetOfGameTime();

	protected:

		// the game is controlled using the keyboard
		// hence we have to intercept all keyboard events
		virtual void keyPressEvent(QKeyEvent* e);
		virtual void keyReleaseEvent(QKeyEvent* e);

		// zoom-in/out (for debug)
		virtual void wheelEvent(QWheelEvent* e);

	public:

		// singleton unique instance getter
		static Game* instance(QWidget* parent=0);
	
		// getters 
		QGraphicsScene* getCurScene() {return cur_scene;}
		std::string     getCurState() {return state2str();}
		Mario* getMario() { return mario; }
		QTimer* gameTime() { return game_time; }
		bool isKeyUpPressed() {return key_up_pressed;}
	
		// setters
		void setSpinningItem(SpinningItem* _spinning_item) { spinning_item = _spinning_item; }
	
	public slots:

		// advance game / next frame
		void advance();

		// pause / resume game
		void tooglePause();

		// show/ hide level grid
		void toogleGrid();

		// show/ hide object colliders
		void toogleColliders();

		// reset game
		void reset();

		// start new game
		void start();

		// game over
		void gameover();

		// freeze/unfreeze all entities
		void setFreezed(bool freezed);

		// play music
		void playMusic();

		// stop music
		void stopMusic();
	
		// change level
		void changeLevel(Direction pipe_travel_dir);

		// hurry up 
		void hurryUp();

		// end level
		void endLevel();

		void stopGameTime();
};

