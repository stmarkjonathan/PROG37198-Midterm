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
	AssetController::Instance().Initialize(10000000);
	Renderer* r = &Renderer::Instance();
	Timing* t = &Timing::Instance();
	Level* level = new Level(Color(128,128, 128, 255));
	level->CreateWarriors();
	r->Initialize(1920, 1080);

	TTFont* font = new TTFont();
	font->Initialize(20);

	Point ws = r->GetWindowSize();

	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	SpriteSheet* sheet = SpriteSheet::Pool->GetResource();
	
	for (auto const& x : level->GetUnits())
	{
		sheet->Load(x->getGuid());
	}

	sheet->SetSize(17, 6, 69, 44);
	sheet->AddAnimation(EN_AN_IDLE, 0, 6, 6.0f);
	sheet->AddAnimation(EN_AN_RUN, 6, 8, 6.0f);

	//serializing

	/*ofstream writeStream("resource.bin", ios::out | ios::binary);
	sheet->Serialize(writeStream);
	writeStream.close();*/

	//deserializing

	/*delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;
	AssetController::Instance().Clear();
	AssetController::Instance().Initialize(10000000);
	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();

	SpriteSheet* sheet2 = SpriteSheet::Pool->GetResource();
	ifstream readStream("resource.bin", ios::in | ios::binary);
	sheet2->Deserialize(readStream);
	readStream.close();*/

	while (m_sdlEvent.type != SDL_QUIT)
	{

		t->Tick();

		SDL_PollEvent(&m_sdlEvent);
		r->SetDrawColor(level->getLvlColour());
		r->ClearScreen();

		for (int i = 0; i < level->GetUnits().size(); i++) 
		{
			r->RenderTexture(sheet, sheet->Update(EN_AN_IDLE, (t->GetDeltaTime() / level->GetUnits().size())), level->GetUnits()[i]->getPos()); //divide deltaTime by m_units size to prevent fast animation
			level->GetUnits()[i]->Move(5, 0);
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