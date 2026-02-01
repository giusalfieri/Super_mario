#include <QKeyEvent>
#include <QWheelEvent>

#include "Game.h"
#include "Object.h"
#include "Entity.h"
#include "Mario.h"
#include "Sounds.h"
#include "Sprites.h"
#include "Hud.h"
#include "Enemy.h"
#include "SwitchBlock.h"
#include "EndLevelText.h"
#include "Card.h"
#include <iostream>

// Singleton design pattern
Game* Game::uniqueInstance = nullptr;
Game* Game::instance(QWidget* parent)
{
	if (uniqueInstance == 0)
		uniqueInstance = new Game(parent);
	return uniqueInstance;
}


Game::Game(QWidget* parent) : QGraphicsView(parent)
{
	// setup scene/view
	levels.push_back(new QGraphicsScene()); 
	levels.push_back(nullptr);              
	levels.push_back(nullptr);              


	currentLevelIdx = 0;
	cur_scene = levels[0];
	black_scene = nullptr;
	
	lives = 4;
	score = 0;
	
	scale(3.0, 3.0);
	centerOn(0, 0);
	

	
	setViewportUpdateMode(QGraphicsView::FullViewportUpdate); 
	setCacheMode(QGraphicsView::CacheBackground);     


	setFrameShape(QFrame::NoFrame);
	setInteractive(false);		// disables events
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	
	// setup game music
	playlist.push_back(new QSound(":/sounds/overworld.wav"));
	playlist.push_back(new QSound(":/sounds/underwater.wav"));
	playlist.push_back(new QSound(":/sounds/super-mario-rap.wav"));

	fast_playlist.push_back(new QSound(":/sounds/overworld-hurry-up.wav"));
	fast_playlist.push_back(new QSound(":/sounds/underwater-hurry-up.wav"));
	fast_playlist.push_back(new QSound(":/sounds/underground-hurry-up.wav"));

	for (auto s : playlist) s->setLoops(QSound::Infinite);
	for (auto s : fast_playlist) s->setLoops(QSound::Infinite);

	// initialize mario
	mario = nullptr;
	spinning_item = nullptr;
	
	// flags
	hurry_up = false;
	key_up_pressed = false;

	// counter
	clear_level_counter = -1;
	
	// setup game time
	game_time = new QTimer(this);
	game_time->setInterval(600);

	// reset game
	reset();

	// setup game engine 
	QObject::connect(&engine, SIGNAL(timeout()), this, SLOT(advance()));
	engine.setInterval(15);
	

	// setup window size
	this->setFixedHeight(602);
	this->setFixedWidth(3*16*16);
}

// reset game
void Game::reset()
{
	// 1. Reset degli stati e dell'indice di livello
	cur_state = READY;
	currentLevelIdx = 0; // Torna alla prima parte del livello

	// 2. Ripristina la scena iniziale dal vettore
	cur_scene = levels[0];
	setScene(cur_scene);

	// 3. Ferma i motori di gioco
	mario = nullptr;
	engine.stop();
	game_time->stop();

	// Ripristina l'intervallo del timer se era stato accelerato a fine livello
	if (game_time->interval() == 2)
		game_time->setInterval(600);

	stopMusic();
	hurry_up = false; // Reset del flag della musica veloce

	// 4. Pulisci TUTTE le scene caricate nel vettore
	for (auto& scene : levels)
	{
		if (scene != nullptr) 
		{
			scene->clear();
		}
	}

	// N.B: keep levels[0] allocated, while other scenes
	// will be reloaded via Lazy Loading in switchSubLevel.
	

	// 5. Reset debug e contatori
	grid.clear();
	if (clear_level_counter >= 0)
		clear_level_counter = -1;

	// 6. Mostra la schermata principale (Splash Screen)
	cur_scene->setBackgroundBrush(QBrush(Qt::black));
	cur_scene->addPixmap(Sprites::instance()->get("main-screen"));
	centerOn(0, 0);
}

void Game::gameover()
{
	if(!mario->isDead())
	{
		if (!mario->isDying())
			mario->die();

		// set black background
		cur_scene->setBackgroundBrush(QBrush(Qt::black));

		//  stop music and play game over sound
		stopMusic();

		Sounds::instance()->play("gameover");
	}
	else
	{
		// stop game
		cur_state = GAME_OVER;
		engine.stop();
		game_time->stop();
		
		//update attributes
		lives = mario->getLives() - 1;
		score = mario->getScore();

		//reset lives when is finished
		if (lives == -1)
		{
			lives = 4;
			score = 0;
		}
	}
	
}

void Game::start()
{
	if (cur_state == READY)
	{
		// 1. Pulisci la prima scena dal vettore e avvia i timer
		levels[0]->clear();
		engine.start();
		game_time->start();

		cur_level_name = "World 6-9-1";
		currentLevelIdx = 0; // Assicura che l'indice sia a 0

		// 2. Carica il livello nella prima scena del vettore
		mario = LevelManager::load(cur_level_name, levels[0]);

		Hud::instance()->start();

		// 3. Sincronizza i dati di Mario
		mario->updateLives(lives);
		mario->updateScore(score);

		// 4. Configurazione della griglia di debug
		const int TILE = 16;
		for (int i = 0; i <= 27; i++)
			grid.push_back(new QGraphicsLineItem(0, i * TILE, 127 * TILE, i * TILE));
		for (int j = 0; j <= 97; j++)
			grid.push_back(new QGraphicsLineItem(j * TILE, 0, j * TILE, 27 * TILE));

		for (auto& l : grid)
		{
			l->setPen(QPen(QBrush(Qt::gray), 0.5));
			l->setZValue(100);
			levels[0]->addItem(l); // Aggiunge alla scena iniziale
			l->setVisible(false);
		}

		// 5. Gestione errori di caricamento o avvio musica
		if (!mario)
		{
			levels[0]->setBackgroundBrush(QBrush(QColor(242, 204, 204)));
			QGraphicsTextItem* text = levels[0]->addText("Error when loading level");
			text->setPos(300, 90);
			centerOn(text);
		}
		else
		{
			// Avvia la musica corrispondente al primo sotto-livello
			playlist[0]->play();
		}

		cur_state = RUNNING;
	}
}

// pause / resume game
void Game::tooglePause()
{
	
	if (cur_state == RUNNING)
	{
		stopGameTime();
		engine.stop();
		stopMusic();
		cur_state = PAUSE;
		Sounds::instance()->play("pause");
	}
	else if (cur_state == PAUSE)
	{
		game_time->start();
		engine.start();
		playMusic();
		cur_state = RUNNING;
	}
}

// show/ hide level grid
void Game::toogleGrid()
{
	for (auto& l : grid)
		l->setVisible(!l->isVisible());
}

// show/ hide object colliders
void Game::toogleColliders()
{
	for (auto& item : cur_scene->items())
		if (dynamic_cast<Object*>(item))
			dynamic_cast<Object*>(item)->toogleColliderVisible();
}

// play music
void Game::playMusic()
{
	if (currentLevelIdx >= 0 && currentLevelIdx < static_cast<int>(playlist.size()))
	{
		if (hurry_up)
			fast_playlist[currentLevelIdx]->play(); 
		else
			playlist[currentLevelIdx]->play();      
	}
}

// stop music
void Game::stopMusic()
{

	if (currentLevelIdx >= 0 && currentLevelIdx < static_cast<int>(playlist.size()))
	{
		if (hurry_up)
			fast_playlist[currentLevelIdx]->stop();
		else
			playlist[currentLevelIdx]->stop();
	}
}

void Game::keyPressEvent(QKeyEvent* e)
{
	// ignore auto repeat key pressed/released
	// (same key has been pressed before and we already processed it)
	if (e->isAutoRepeat())
		return;

	// start new game
	if (e->key() == Qt::Key_Return && cur_state == READY)
		start();

	// reset game and hud
	if ((e->key() == Qt::Key_R || cur_state == GAME_OVER) && !SwitchBlock::SwitchEffect())
	{
		Hud::instance()->reset();
		this->reset();
	}

	// pause game
	if (e->key() == Qt::Key_P)
		tooglePause();

	// show/hide grid game
	if (e->key() == Qt::Key_G)
		toogleGrid();

	// show/hide colliders
	if (e->key() == Qt::Key_C)
		toogleColliders();

	// from now on, all commands require the game to be running
	if (cur_state != RUNNING)
		return;

	// speed up / slow down
	if (e->key() == Qt::Key_Plus)
		engine.setInterval(engine.interval() / 5);
	if (e->key() == Qt::Key_Minus)
		engine.setInterval(engine.interval() * 5);

	// horizontal Mario's movements
	if (e->key() == Qt::Key_Right || e->key() == Qt::Key_Left)
	{
		mario->setDirection(e->key() == Qt::Key_Right ? Direction::RIGHT : Direction::LEFT);
		mario->setMoving(true);
	}
	
	if (e->key() == Qt::Key_Up)
		key_up_pressed = true;
	
	if (e->key() == Qt::Key_Down)
	{
		if (mario->isOnPipe(cur_level_name))
		{
			cur_state = CHANGE_LEVEL;
			mario->enterPipe(Direction::UP);
		}
		else
			mario->setCrouch(true);
	}
		
	
	// Mario's jump
	if (e->key() == Qt::Key_Space)
	{
		//mario is swimming
		if (mario->isInWater())
			mario->swim();
		//mario is rebounding on jumpblock
		else if (mario->isBouncing())
			mario->setRebound(true);
		//mario raccoon is flying
		else if (mario->isRaccoon() && mario->isSuperRunning())
			mario->fly();
		else
			mario->jump();
	}
		
	// Mario's running
	if (e->key() == Qt::Key_Z)
		mario->setRunning(true);

	// Mario's transformation
	if (e->key() == Qt::Key_T)
		mario->powerUp(DEBUG); 

		//Mario's shooting
	if (e->key() == Qt::Key_B)
		mario->setAttack(true);

	// hurt every enemy
	if (e->key() == Qt::Key_H)
		for (auto& item : cur_scene->items())
		{
			Enemy* obj = dynamic_cast<Enemy*>(item);
			if (obj)
				obj->hurt();
		}
}

void Game::keyReleaseEvent(QKeyEvent* e)
{
	// ignore auto repeat key pressed/released
	// (same key has been pressed before and we already processed it)
	if (e->isAutoRepeat())
		return;

	if (e->key() == Qt::Key_Up)
		key_up_pressed = false;

	// from now on, all commands require the game to be running
	if (cur_state != RUNNING)
		return;

	// horizontal Mario's movements
	if (e->key() == Qt::Key_Right || e->key() == Qt::Key_Left)
		mario->setMoving(false);
	
	if (e->key() == Qt::Key_Down)
		mario->setCrouch(false);

	// Mario's running
	if (e->key() == Qt::Key_Z)
		mario->setRunning(false);
}

// zoom-in/out
void Game::wheelEvent(QWheelEvent* e)
{
	if (e->delta() > 0)
		scale(1.1, 1.1);
	else
		scale(1 / 1.1 ,1 / 1.1);
}

void Game::advance()
{
	// 1.Do nothing if game is not running
	if (cur_state != RUNNING && cur_state != CHANGE_LEVEL && cur_state != END_OF_LEVEL)
		return;

	// Gestione transizione tubo
	if (mario->isEnteringPipe())
		cur_state = CHANGE_LEVEL;

	// Controllo morte di Mario
	if (mario->isDead() && cur_state != CHANGE_LEVEL)
		gameover();

	// 2. Ciclo di aggiornamento oggetti nella scena corrente
	for (auto& item : cur_scene->items())
	{
		Object* obj = dynamic_cast<Object*>(item);
		if (obj)
		{
			obj->animate();
			obj->advance();

			// Pulizia entità morte (nemici, power-up consumati)
			Entity* entity_obj = dynamic_cast<Entity*>(obj);
			Mario* mario_obj = dynamic_cast<Mario*>(obj);
			if (entity_obj && !mario_obj && entity_obj->isDead())
			{
				cur_scene->removeItem(entity_obj);
				delete entity_obj;
			}
		}
	}

	// 3. Gestione Telecamera e Fine Livello
	if (cur_state != END_OF_LEVEL)
	{
		// Segue Mario solo se non sta attaccando (Raccoon) o morendo
		if (!mario->isRaccoonAttack() && !mario->isDying())
		{
			centerOn(QPointF(mario->pos().x() + mario->shape().currentPosition().x(),
				mario->pos().y() + mario->boundingRect().height()));
		}
	}
	else
	{
		// LOGICA FINE LIVELLO (World 6-9)
		const int TILE = 16;
		centerOn(QPointF(88 * TILE, 337)); // Centra sul Goal Roulette

		if (mario->pos().x() >= 96 * TILE)
		{
			clear_level_counter++;

			// Sequenza di sblocco testi e card
			if (clear_level_counter == 0)
				new EndLevelText(QPoint(1337, 267), "CLEAR COURSE!");

			if (clear_level_counter == 23)
				new EndLevelText(QPoint(1337, 294), "YOU GOT A CARD");

			else if (clear_level_counter == 43)
			{
				// CORRETTO: Usa levels[0] invece di scene1
				new Card(QPoint(1464, 299), mario->ItemTaken(), levels[0]);
				Hud::instance()->updatePanel("CardsTaken", mario->ItemTaken());
			}
			else if (clear_level_counter == 170)
				fastResetOfGameTime();
			else if (clear_level_counter == 300)
			{
				// Fine sequenza: salva dati e resetta il gioco
				Hud::instance()->reset();
				lives = mario->getLives();
				score = mario->getScore();
				reset();
			}
		}
	}
}
// freeze/unfreeze all entities
void Game::setFreezed(bool freezed)
{
	// tell all game objects to animate and advance in the scene
	for (auto& item : cur_scene->items())
	{
		Entity* entity_obj = dynamic_cast<Entity*>(item);
		Mario*   mario_obj = dynamic_cast<Mario*>(item);
		if (cur_state == CHANGE_LEVEL && !mario_obj && entity_obj)
			entity_obj->setFreezed(freezed);
		else if(entity_obj)
			entity_obj->setFreezed(freezed);
	}

	if (freezed == false && cur_state == CHANGE_LEVEL)
		cur_state = RUNNING;
}

void Game::changeLevel(Direction pipe_travel_dir)
{
	engine.stop();
	stopMusic();
	stopGameTime();

	if (!black_scene)
	{
		black_scene = new QGraphicsScene();
		black_scene->setBackgroundBrush(QBrush(Qt::black));
	}
	setScene(black_scene);

	
	if (pipe_travel_dir == DOWN)
		switchSubLevel(1);
	else if (pipe_travel_dir == UP)
		switchSubLevel(-1);

	QTimer::singleShot(200, this, [this]() {
		// Controllo di sicurezza prima di impostare la scena
		if (cur_scene != nullptr)
		{
			setScene(cur_scene);
			engine.start();
			playMusic();
			if (cur_state == RUNNING || cur_state == CHANGE_LEVEL)
				game_time->start();
		}
		});
}

QPointF Game::getSpawnPoint(int idx, int direction)
{
	const int TILE = 16; // Dimensione base dei blocchi

	if (direction == 1) // MOVIMENTO IN AVANTI (Entra nel tubo per scendere)
	{
		int x_tiles = (idx == 1) ? 4 : 8;
		return QPointF(x_tiles * TILE + 5, 0);
	}
	else // MOVIMENTO ALL'INDIETRO (Entra nel tubo per salire)
	{
		int x_tiles = (idx == 1) ? 70 : 52;
		int y_tiles = 25;
		qreal y_offset = mario->isRaccoon() ? 4 : 2; // Offset diverso per Mario Procione
		return QPointF(x_tiles * TILE + 5, y_tiles * TILE - y_offset);
	}
}

void Game::switchSubLevel(int direction)
{
	if (!mario || !cur_scene) return;

	// Rimuovi Mario dalla vecchia scena prima di cambiare indice
	cur_scene->removeItem(mario);

	currentLevelIdx += direction;
	if (currentLevelIdx < 0) currentLevelIdx = 0;
	if (currentLevelIdx > 2) currentLevelIdx = 2;

	cur_level_name = "World 6-9-" + std::to_string(currentLevelIdx + 1);

	if (levels[currentLevelIdx] == nullptr)
	{
		levels[currentLevelIdx] = new QGraphicsScene();
		cur_scene = levels[currentLevelIdx];          
		LevelManager::load(cur_level_name, cur_scene);
	}
	else
	{
		cur_scene = levels[currentLevelIdx];
	}


	// AGGIUNGI SEMPRE MARIO: lui è l'unica istanza che viaggia tra le scene
	cur_scene->addItem(mario);
	mario->setLevelName(cur_level_name);


	// Imposta posizione e centra la telecamera immediatamente per evitare il vuoto nero
	QPointF spawn = getSpawnPoint(currentLevelIdx, direction);
	mario->setPos(spawn);
	centerOn(mario);

}

void Game::hurryUp()
{
	stopMusic();

	// from now on, 100 seconds are left to game-time's end
	hurry_up = true;

	// play "hurry-up" sound to warn that the player is running low on time 
	Sounds::instance()->play("hurry-up");

	// when "hurry-up" jingle is finished, 
	// play level's music at a faster speed
	QTimer::singleShot(2850, this, [this]() { playMusic(); });
}

void Game::endLevel()
{
	cur_state = END_OF_LEVEL;
	stopMusic();
	Sounds::instance()->play("levelend");
}

void Game::stopGameTime()
{
	game_time->stop();
}

std::string Game::state2str()
{
	if (cur_state == READY)
		return "READY";
	else if (cur_state == RUNNING)
		return "RUNNING";
	else if (cur_state == PAUSE)
		return "PAUSE";
	else if (cur_state == GAME_OVER)
		return "GAME_OVER";
	else if (cur_state == CHANGE_LEVEL)
		return "CHANGE_LEVEL";
	else
		return "END_OF_LEVEL";
}

void Game::fastResetOfGameTime()
{
	game_time->setInterval(2);
	game_time->start();
	Sounds::instance()->play("timer-reset");
}

