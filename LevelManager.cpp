﻿#include "LevelManager.h"
#include "FixedBlock.h"
#include "Iceberg.h"
#include "Background.h"
#include "Mario.h"
#include "Muncher.h"
#include "Sprites.h"
#include "Terrain.h" 
#include "Coin.h"
#include "Pipe.h"
#include "Cheep.h"
#include "SecretBox.h"
#include "BrickBlock.h"
#include "HiddenBlock.h"
#include "GoalRoulette.h"
#include "Firework.h"
#include <iostream>
#include "EndLevelText.h"
#include "LifeUp.h"
#include "Leaf.h"
#include "JumpBlock.h"
#include "Mushroom.h"
#include "BlooberNanny.h"
#include "Plant.h"
#include "PlantFire.h"
//#include "Collectable.h"

// load all items from the given level in the given scene
Mario* LevelManager::load(std::string level_name,QGraphicsScene* scene)
{

	Mario* mario = nullptr;

	if (level_name == "World 6-9-1")
	{

		scene->setSceneRect(0, 0, 97*16, 27*16);
		
		// set background color
		scene->setBackgroundBrush(QBrush(Sprites::instance()->get("sky")));
		
		new Background(QPoint(1151, 27*16), ":/graphics/background/sky1.png");

		// terrain level
		int terrain_level = 26*16;

		// terrain
		new Terrain(QRect(0, terrain_level, 97*16, 1*16));

		for (int i = 0; i < 3; i++)
			new FixedBlock(QPoint(8*16 + (32*i), terrain_level - 32),"ice");
		
		//new Leaf(QPoint(6 * 16, terrain_level - 80));//todo foglia di debug
		
		
		// ice_block
		new FixedBlock(QPoint(10*16, terrain_level-64),  "ice");
		new FixedBlock(QPoint(12*16, terrain_level-64),  "ice");
		new FixedBlock(QPoint(12*16, terrain_level-32*3),"ice");
		new FixedBlock(QPoint(16*16, terrain_level-32),  "ice");
		new FixedBlock(QPoint(16*16, terrain_level-32*2),"ice");
		new FixedBlock(QPoint(18*16, terrain_level-32),  "ice");
		for (int raw = 0; raw < 13; raw++)
			for (int col = 0; col < 6; col++)
				new FixedBlock(QPoint(24 * 16 + 32 * raw, terrain_level - 32 - 32 * col), "ice");
		new FixedBlock(QPoint(50 * 16, terrain_level - 32), "ice");
		new FixedBlock(QPoint(54 * 16, terrain_level - 32), "ice");
		new FixedBlock(QPoint(62 * 16, terrain_level - 32), "ice");
		//todo solo per il debug
		(new Iceberg(QRect(18 * 16, terrain_level - 64 + 1, 159, 1), level_name, "downhill"))->setRotation(45);

		// pipe
		new Pipe(QPoint(14*16, terrain_level+16), level_name, 4);
		new Pipe(QPoint(52*16, terrain_level+16), level_name, 3);

		//new Firework(QPoint(0,1*16), "FLOWER");
		//new GoalRoulette(QPoint(4*16,23*16));
		new GoalRoulette(QPoint(88*16, 337));

		
	   // new JumpBlock(QPoint(6 * 16, terrain_level - 48));
	    new SecretBox(QPoint(8 * 16, terrain_level - 150),LIFE);
		new Cheep(QPoint(5 * 16, terrain_level - 32));
		new Cheep(QPoint(80* 16, terrain_level - 32));
		new Plant(QPoint(5* 16, terrain_level - 32),DOWN,true,true);
		
		//new BrickBlock(QPoint(4 * 16, terrain_level-48),"ice");
		new KoopaTroopa(QPoint(38 * 16, terrain_level-200));
		//new BrickBlock(QPoint(27 * 16, terrain_level-200),"ice");
		//new JumpBlock(QPoint(4 * 16, terrain_level-48));

		//new Mushroom(QPoint(6 * 16, terrain_level - 80),UP);
		
		//new JumpBlock(QPoint(2 * 16, terrain_level - 80), MUSHROOM);
		new Coin(QPoint(80 * 16, terrain_level-32));
		
		// Mario
		//mario = new Mario(QPoint(1.5 * 16, terrain_level), level_name); //mario di default
		mario = new Mario(QPoint(15 * 16, terrain_level-64), level_name); //mario sopra la pipe
	//	mario = new Mario(QPoint(80 * 16, terrain_level), level_name); //mario fine livello
		//mario = new Mario(QPoint(26 * 16, terrain_level-192), level_name); // mario sopra l'iceberg

	}
	else if (level_name == "World 6-9-2" )
	{
		scene->setSceneRect(0, 0, 128*16, 27*16);
		
		// set background color
		scene->setBackgroundBrush(QBrush(Sprites::instance()->get("night-sky")));

		// set level's background
		new Background(QPoint(0, 27*16), ":/graphics/background/water.png");
		new Background(QPoint(0, 27*16), ":/graphics/background/icebergs.png");
		
		// NOTE: By design choice only collidable iceberg items are load in the level (i.e. the edge ones)
		//       while the others are part of level's background
		//       
		// edge's types:
		//
		//       edge  :    -------->          ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
		//                                     ____________________________
		//
		//       edge1 :    -------->          |‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
		//                                     |___________________________
		//
		//       edge2 :    -------->          ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|
		//                                     ____________________________|
		




		(new Iceberg(QRect(28  , 19 * 16, 163, 1),     level_name, "downhill"))->setRotation(45);
		(new Iceberg(QRect(8*16, 14 * 16, 112, 1),     level_name, "downhill2"))->setRotation(45);    //todo settare lunghezza giusta, forse un poco più corta
		(new Iceberg(QRect(60*16,19 * 16 + 1, 159, 1), level_name, "downhill"))->setRotation(45);
		(new Iceberg(QRect(120*16, 12 * 16 + 1, 159, 1),level_name, "uphill"))->setRotation(135);//todo settare la lunghezza giusta
		new Iceberg(QRect( 1*16,   0  ,  1*16, 19*16), level_name, "vert-right-edge");
		new Iceberg(QRect(19*16,  2*16,  1*16, 16*16), level_name, "vert-right-edge");
		new Iceberg(QRect( 8*16,   0  ,  1*16, 14*16), level_name, "vert-left-edge" );
		new Iceberg(QRect(13*16, 18*16,  7*16,  1*16), level_name, "horiz-bottom-edge2","underwater");
		new Iceberg(QRect( 9*16, 26*16, 14*16,  1*16), level_name, "horiz-top-edge2"   ,"underwater");
		new Iceberg(QRect(20*16,  1*16, 15*16,  1*16), level_name, "horiz-bottom-edge");
		new Iceberg(QRect(37*16,  1*16, 14*16,  1*16), level_name, "horiz-bottom-edge");
		new Iceberg(QRect(24*16, 16*16,  4*16,  1*16), level_name, "horiz-bottom-edge1","underwater");
		new Iceberg(QRect(24*16, 11*16,  1*16,  5*16), level_name, "vert-left-edge1");
		new Iceberg(QRect(16*25, 11*16,  9*16,  1*16), level_name, "horiz-top-edge2");
		new Iceberg(QRect(33*16, 12*16,  1*16,  8*16), level_name, "vert-right-edge");
		new Iceberg(QRect(30*16, 20*16,  1*16,  1*16), level_name, "horiz-bottom-edge1","underwater");
		new Iceberg(QRect(33*16, 20*16,  1*16,  1*16), level_name, "horiz-bottom-edge2","underwater");
		new Iceberg(QRect(31*16, 20*16,  2*16,  1*16), level_name, "horiz-bottom-edge" ,"underwater");
		new Iceberg(QRect(53*16,  1*16,  7*16,  1*16), level_name, "horiz-bottom-edge");
		new Iceberg(QRect(60*16,  2*16,  1*16, 11*16), level_name, "vert-left-edge");
		new Iceberg(QRect(42*16, 19*16, 18*16,  1*16), level_name, "horiz-top-edge1",   "underwater");
		new Iceberg(QRect(42*16, 20*16,  7*16,  1*16), level_name, "horiz-bottom-edge1","underwater");
		new Iceberg(QRect(51*16, 20*16,  6*16,  1*16), level_name, "horiz-bottom-edge" ,"underwater");
		new Iceberg(QRect(57*16, 21*16,  1*16,  5*16), level_name, "vert-left-edge"    ,"underwater");
		new Iceberg(QRect(40*16, 16*16, 16*16,  1*16), level_name, "horiz-bottom-edge2","underwater");
		new Iceberg(QRect(38*16, 13*16,  7*16,  1*16), level_name, "horiz-top-edge1");
		new Iceberg(QRect(38*16, 14*16,  1*16,  6*16), level_name, "vert-left-edge" );
		new Iceberg(QRect(39*16, 17*16,  1*16,  3*16), level_name, "vert-right-edge");
		new Iceberg(QRect(38*16, 20*16,  1*16,  1*16), level_name, "horiz-bottom-edge1","underwater");
		new Iceberg(QRect(39*16, 20*16,  1*16,  1*16), level_name, "horiz-bottom-edge2","underwater");
		new Iceberg(QRect(45*16, 11*16,  1*16,  2*16), level_name, "vert-left-edge1");
		new Iceberg(QRect(49*16, 11*16,  1*16,  2*16), level_name, "vert-right-edge1");
		new Iceberg(QRect(46*16, 11*16,  3*16,  1*16), level_name, "horiz-top-edge");
		new Iceberg(QRect(51*16, 11*16,  1*16,  2*16), level_name, "vert-left-edge1");
		new Iceberg(QRect(52*16, 11*16,  1*16,  2*16), level_name, "vert-right-edge1");
		new Iceberg(QRect(54*16, 11*16,  1*16,  2*16), level_name, "vert-left-edge1");
		new Iceberg(QRect(55*16, 11*16,  1*16,  5*16), level_name, "vert-right-edge1");
		new Iceberg(QRect(50*16, 13*16,  1*16,  1*16), level_name, "horiz-top-edge");
		new Iceberg(QRect(53*16, 13*16,  1*16,  1*16), level_name, "horiz-top-edge");
		new Iceberg(QRect(54*16, 26*16,  1*16,  1*16), level_name, "vert-left-edge");
		new Iceberg(QRect(56*16, 26*16,  1*16,  1*16), level_name, "horiz-top-edge",    "underwater");
		new Iceberg(QRect(41*16, 26*16,  1*16,  1*16), level_name, "vert-right-edge");
		new Iceberg(QRect(60*16, 13*16,  9*16,  1*16), level_name, "horiz-bottom-edge1");
		new Iceberg(QRect(69*16,  8*16,  1*16,  6*16), level_name, "vert-right-edge2");
		new Iceberg(QRect(70*16,  7*16, 10*16,  1*16), level_name, "horiz-bottom-edge2");
		new Iceberg(QRect(79*16,  2*16,  1*16,  5*16), level_name, "vert-right-edge");
		new Iceberg(QRect(80*16,  1*16 , 3*16,  1*16), level_name, "horiz-bottom-edge");
		new Iceberg(QRect(85*16,  1*16,  6*16,  1*16), level_name, "horiz-bottom-edge");
		new Iceberg(QRect(93*16,  1*16, 15*16,  1*16), level_name, "horiz-bottom-edge");
		new Iceberg(QRect(67*16, 26*16,  3*16,  1*16), level_name, "horiz-top-edge",    "underwater");
		new Iceberg(QRect(72*16, 26*16,  4*16,  1*16), level_name, "horiz-top-edge",    "underwater");
		new Iceberg(QRect(78*16, 26*16,  2*16,  1*16), level_name, "horiz-top-edge",    "underwater");
		new Iceberg(QRect(82*16, 26*16,  5*16,  1*16), level_name, "horiz-top-edge",    "underwater");
		new Iceberg(QRect(89*16, 26*16,  1*16,  1*16), level_name, "horiz-top-edge2",   "underwater");
		new Iceberg(QRect(93*16, 25*16,  5*16,  1*16), level_name, "horiz-top-edge",    "underwater");
		new Iceberg(QRect(92*16, 25*16,  1*16,  2*16), level_name, "vert-left-edge1",   "underwater");
		new Iceberg(QRect(96*16, 16*16,  5*16,  1*16), level_name, "horiz-bottom-edge1","underwater");
		new Iceberg(QRect(98*16, 25*16,  1*16,  2*16), level_name, "vert-right-edge1",  "underwater");
		new Iceberg(QRect(104*16,26*16,  2*16,  1*16), level_name, "horiz-top-edge1",   "underwater");
		new Iceberg(QRect(110*16, 1*16,  2*16,  1*16), level_name, "horiz-bottom-edge");
		new Iceberg(QRect(112*16, 2*16,  1*16,  5*16), level_name, "vert-left-edge2");
		new Iceberg(QRect(113*16, 6*16,  7*16,  1*16), level_name, "horiz-bottom-edge");
		new Iceberg(QRect(120*16, 7*16,  1*16,  5*16), level_name, "vert-left-edge");
		new Iceberg(QRect(110*16,11*16,  2*16,  1*16), level_name, "horiz-top-edge2");
		new Iceberg(QRect(111*16,12*16,  1*16,  4*16), level_name, "vert-right-edge");
		new Iceberg(QRect(111*16,16*16,  1*16,  1*16), level_name, "horiz-bottom-edge2","underwater");
		new Iceberg(QRect(108*16,16*16,  3*16,  1*16), level_name, "horiz-bottom-edge1","underwater");
		new Iceberg(QRect(108*16,11*16,  1*16,  5*16), level_name, "vert-left-edge");
		new Iceberg(QRect(103*16,16*16,  4*16,  1*16), level_name, "horiz-bottom-edge2","underwater");
		new Iceberg(QRect(96*16, 11*16,  1*16,  5*16), level_name, "vert-left-edge1");
		new Iceberg(QRect(97*16, 11*16,  1*16,  2*16), level_name, "vert-right-edge1");
		new Iceberg(QRect(98*16, 13*16,  2*16,  1*16), level_name, "horiz-top-edge");
		new Iceberg(QRect(100*16,11*16,  1*16,  2*16), level_name, "vert-left-edge1");
		new Iceberg(QRect(103*16,11*16,  4*16,  1*16), level_name, "horiz-top-edge2");
		new Iceberg(QRect(106*16,12*16,  1*16,  4*16), level_name, "vert-right-edge");
		new Iceberg(QRect(84*16, 13*16,  8*16,  1*16), level_name, "horiz-top-edge");
		new Iceberg(QRect(83*16, 11*16,  1*16,  2*16), level_name, "vert-right-edge1");
		new Iceberg(QRect(82*16, 16*16, 12*16,  1*16), level_name, "horiz-bottom-edge2", "underwater");
		new Iceberg(QRect(78*16, 16*16,  2*16,  1*16), level_name, "horiz-bottom-edge",  "underwater");
		new Iceberg(QRect(93*16, 11*16, 1*16,   5*16), level_name, "vert-right-edge1");
		new Iceberg(QRect(92*16, 11*16, 1*16,   2*16), level_name, "vert-left-edge1");
		new Iceberg(QRect(74*16, 16*16, 2*16,   1*16), level_name, "horiz-bottom-edge1", "underwater");
		new Iceberg(QRect(77*16, 15*16, 5*16,   1*16), level_name, "horiz-top-edge");
		new Iceberg(QRect(74*16, 14*16, 1*16,   2*16), level_name, "vert-left-edge1");
		new Iceberg(QRect(75*16, 14*16, 2*16,   1*16), level_name, "horiz-top-edge2");
		new Iceberg(QRect(82*16, 11*16, 1*16,   4*16), level_name, "vert-left-edge1");

		new Pipe(QPoint(40*16, 26*16), level_name, 2);
		new Pipe(QPoint(54*16, 26*16), level_name, 2);
		new Pipe(QPoint(70*16, 26*16), level_name, 2);
		new Pipe(QPoint(76*16, 26*16), level_name, 1);
		new Pipe(QPoint(80*16, 26*16), level_name, 3);
		new Pipe(QPoint(87*16, 26*16), level_name, 1);
		new Pipe(QPoint(101*16,11*16), level_name, 1);
		new Pipe(QPoint(108*16,11*16), level_name, 2);
	   (new Pipe(QPoint( 4*16,   0  ), level_name, 1, "rotated"))->setRotation(180);
	   (new Pipe(QPoint(28*16, 17*16), level_name, 3, "rotated"))->setRotation(180);
	   (new Pipe(QPoint(51*16,  2*16), level_name, 6, "rotated"))->setRotation(180);
	   (new Pipe(QPoint(35*16,  2*16), level_name, 2, "rotated"))->setRotation(180);
	   (new Pipe(QPoint(49*16, 21*16), level_name, 1, "rotated"))->setRotation(180);
	   (new Pipe(QPoint(76*16, 17*16), level_name, 1, "rotated"))->setRotation(180);
	   (new Pipe(QPoint(80*16, 17*16), level_name, 2, "rotated"))->setRotation(180);
       (new Pipe(QPoint(83*16,  2*16), level_name, 2, "rotated"))->setRotation(180);
       (new Pipe(QPoint(91*16,  2*16), level_name, 2, "rotated"))->setRotation(180);
	   (new Pipe(QPoint(108*16, 2*16), level_name, 1, "rotated"))->setRotation(180);
	   (new Pipe(QPoint(101*16,17*16), level_name, 5, "rotated"))->setRotation(180);

		//plant
	   new Plant(QPoint(35.5 * 16, 5 * 16), DOWN, false, true);
	   new PlantFire(QPoint(108.5 * 16, 6.5 * 16),UP);

	   for (int i = 0; i <= 3; i++)
		   new Muncher(QPoint((28+i)*16, 10*16));
	   for (int i = 0; i <= 5; i++)
		   new Muncher(QPoint((39+i)*16, 12*16));
	   for (int i = 0; i <= 3; i++)
		   new Muncher(QPoint((77+i)*16, 14*16));
	   for (int i = 0; i <= 7; i++)
		   new Muncher(QPoint((84+i)*16, 12*16));
	   for (int i = 0; i <= 1; i++)
		   new Muncher(QPoint((98+i)*16, 12*16));
	   new Muncher(QPoint(50 * 16, 12 * 16));
	   new Muncher(QPoint(53 * 16, 12 * 16));
	 
	   new FixedBlock(QPoint(23*16, 15*16), "wood");
	   new FixedBlock(QPoint(27*16,  9*16), "wood");
	   new FixedBlock(QPoint(27*16, 10*16), "wood");
	   new FixedBlock(QPoint(32*16,  9*16), "wood");
	   new FixedBlock(QPoint(32*16, 10*16), "wood");
	   new FixedBlock(QPoint(38*16, 11*16), "wood");
	   new FixedBlock(QPoint(38*16, 12*16), "wood");
	   new FixedBlock(QPoint(73*16, 16*16), "wood");
	   new FixedBlock(QPoint(76*16, 13*16), "wood");
	   new FixedBlock(QPoint(81*16, 13*16), "wood");
	   new FixedBlock(QPoint(81*16, 14*16), "wood");
	   new FixedBlock(QPoint(94*16, 15*16), "wood");
	   new FixedBlock(QPoint(89*16,  9*16), "wood");
	   for(int i = 0; i <= 2 ; i++)
		   new FixedBlock(QPoint((97+i)*16, 6*16), "wood");
	
	   
	   //new BrickBlock(QPoint(82*16, 5*16));
	   
	   new HiddenBlock(QPoint(80 * 16, 7 * 16));
		//todo controllare se le posizioni sono giuste
	   new JumpBlock(QPoint(47 * 16, 7 * 16));
	   new JumpBlock(QPoint(95 * 16, 9 * 16));

	   // enemies
	   // first cheep
	   new Cheep(QPoint(14*16, 22*16), RIGHT);
	  // new BlooberNanny(QPoint(20 * 16, 23 * 16));
	}
	else if(level_name == "World 6-9-3")
    {

		scene->setSceneRect(0, 0, 16*16, 27*16);

		scene->setBackgroundBrush(QBrush(Sprites::instance()->get("night-sky2")));

		new Background(QPoint(0, 27*16), ":/graphics/background/scene3.png");

		new Iceberg(QRect(  0  ,  1*16,  1*16, 22*16), level_name, "vert-right-edge");
		new Iceberg(QRect( 1*16,   0  ,  7*16,  1*16), level_name, "horiz-bottom-edge");
		new Iceberg(QRect(10*16,   0  ,  3*16,  1*16), level_name, "horiz-bottom-edge");
		new Iceberg(QRect(13*16,  1*16,  1*16, 16*16), level_name, "vert-left-edge");
		new Iceberg(QRect(15*16, 22*16,  1*16,  3*16), level_name, "vert-left-edge");
		new Iceberg(QRect( 9*16, 23*16,  1*16,  1*16), level_name, "horiz-top-edge");
		new Iceberg(QRect( 1*16, 23*16,  2*16,  1*16), level_name, "horiz-top-edge");
		new Iceberg(QRect( 5*16, 25*16,  2*16,  1*16), level_name, "horiz-top-edge", "underwater");
		new Iceberg(QRect(12*16, 25*16,  3*16,  1*16), level_name, "horiz-top-edge", "underwater");
	   (new Iceberg(QRect(16 * 3, 23 * 16 + 1, 47, 1), level_name, "downhill"))->setRotation(45);
	   (new Iceberg(QRect(16 * 10, 23 * 16 + 1, 47, 1), level_name, "downhill"))->setRotation(45);
	   (new Iceberg(QRect(16 * 9, 23 * 16 + 2, 47, 1), level_name, "uphill"))->setRotation(135);
	   (new Pipe(QPoint( 8*16,   0  ), level_name, 1, "rotated"))->setRotation(180);
	   (new Pipe(QPoint(13*16, 17*16), level_name, 4, "rotated"))->setRotation(180);


	   for (int i=0; i<=3; i++)
		   new Coin(QPoint(3*16, (9+2*i)*16));
	   for (int raw=0; raw<7; raw++)
		   for (int col=0; col<=3; col++)
			   new Coin(QPoint((5+2*col)*16, (3+2*raw)*16));


	   //todo, deve essere un altro tipo di contenuto,tipo extra life
	   new SecretBox(QPoint(5*16, 20*16),LIFE); 
																					
    }
	else
		std::cerr << "Level not implemented";

	return mario;
}