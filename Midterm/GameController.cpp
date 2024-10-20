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
	Level* level = new Level(Color(128,128, 128, 255));
	
	ofstream stream("resource.bin", ios::out | ios::binary);

	//loads warriors + rocks and initializes their values
	level->CreateWarriors();
	level->CreateRocks();

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

	//same thing for rocks
	for (auto const& x : level->GetRocks())
	{
		rockSheet->Load(x->getGuid());
	}

	sheet->SetSize(17, 6, 69, 44);
	sheet->AddAnimation(EN_AN_RUN, 6, 8, 6.0f);

	rockSheet->SetSize(1, 4, 19, 20);
	rockSheet->AddAnimation(EN_AN_ROCK, 0, 4, 6.0f);

	//main game loop, runs every frame
	//if 60 frames per second, runs 60 times a second
	while (m_sdlEvent.type != SDL_QUIT)
	{

		t->Tick();

		SDL_PollEvent(&m_sdlEvent);
		r->SetDrawColor(level->getLvlColour());
		r->ClearScreen();


		//currently there is only 1 level
		//level spawns warriors and rocks
		//somehow find a way to start with level 1 (only warriors) then switch to level 2 (warriors + rocks) according to a condition
		level->RunLevelLogic(r, sheet,rockSheet, t);

		if (t->GetGameTime() == 5000)
		{
			level->Serialize(stream);
		}

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