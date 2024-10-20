#include "GameController.h"
#include "SpriteSheet.h"
#include "Level.h"
#include "Timing.h"
#include "TTFont.h"
#include "SpriteAnim.h"
#include "Renderer.h"

GameController::GameController()
{
	srand(time(NULL));
	m_sdlEvent = { };
}

GameController::~GameController()
{
}

void GameController::RunGame()
{

	//initializing 
	AssetController::Instance().Initialize(10000000);
	Renderer* r = &Renderer::Instance();
	Timing* t = &Timing::Instance();
	//Level* level1 = new Level(Color(128, 128, 128, 255));

	//loads warriors + rocks and initializes their values
	//level1->CreateWarriors();
	Level* level = new Level(Color(128, 128, 128, 255));
	Level* level2 = new Level(Color(0, 128, 0, 255));      // Green background

	level->CreateWarriors();
	//level->CreateRocks();
	level2->CreateWarriors();
	level2->CreateRocks();

	//sets window size to 1920x1080
	r->Initialize(1920, 1080);

	TTFont* font = new TTFont();
	font->Initialize(20);

	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	SpriteSheet* sheet = SpriteSheet::Pool->GetResource();
	SpriteSheet* rockSheet = SpriteSheet::Pool->GetResource();
	
	//goes through each unit in level's m_units
	//loads the texture according to m_guid member in each unit
	for (auto const& x : level->GetUnits())
	{
		sheet->Load(x->getGuid());	
	}

	////same thing for rocks
	//for (auto const& x : level->GetRocks())
	//{
	//	rockSheet->Load(x->getGuid());
	//}
	//same thing for rocks
	for (auto const& x : level2->GetRocks())
	{
		rockSheet->Load(x->getGuid());
	}
	sheet->SetSize(17, 6, 69, 44);
	sheet->AddAnimation(EN_AN_RUN, 6, 8, 6.0f);
	sheet->AddAnimation(EN_AN_DEATH, 26, 11, 4.0f);

	rockSheet->SetSize(1, 4, 19, 20);
	rockSheet->AddAnimation(EN_AN_ROCK, 0, 4, 6.0f);
	//auto - save the level state after 5 seconds as Level1.bin, immediately load the auto - saved
	//	level(Level1.bin) and continue level execution
	bool hasAutoSaved = false;
	bool isLevel1 = false;
	//main game loop, runs every frame
	//if 60 frames per second, runs 60 times a second
	while (m_sdlEvent.type != SDL_QUIT)
	{

		t->Tick();
	
		SDL_PollEvent(&m_sdlEvent);
		//r->SetDrawColor(level1->getLvlColour());
		r->SetDrawColor(level->getLvlColour());//origina level logic
		r->ClearScreen();

		if (isLevel1) {
			r->SetDrawColor(level->getLvlColour());//
			r->ClearScreen();
			level->RunLevel1Logic(r, sheet, t);

		}
		else {
			//cout << "level 2" << endl;
			r->SetDrawColor(level2->getLvlColour());
			r->ClearScreen();
			level2->RunLevel2Logic(r, sheet, rockSheet, t);
		}
		//if (isLevel1 && level->GetUnits().front()->getPos().X2 > 1920) { //doesn't work 100 % of the time
		//	isLevel1 = false;
		//}
		if (isLevel1) { //checking if first warrior has left screen
			for (int i = 0; i < level->GetUnits().size(); i++) {
				if (level->GetUnits()[i]->getPos().X1 > 1920) {
					isLevel1 = false;

				}
			}
	
		}

		//currently there is only 1 level
		//level spawns warriors and rocks
		//somehow find a way to start with level 1 (only warriors) then switch to level 2 (warriors + rocks) according to a condition
		//level->RunLevelLogic(r, sheet,rockSheet, t);//origina level logic
		
		
		

		string fps = "Frames per Second: " + to_string(t->GetFPS());
		font->Write(r->GetRenderer(), fps.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 0 });

		string gameTime = "Game Time: " + to_string(t->GetGameTime());
		font->Write(r->GetRenderer(), gameTime.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 250, 0 });

		
		SDL_RenderPresent(r->GetRenderer());
	}

	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;

	font->Shutdown();
	r->Shutdown();
}