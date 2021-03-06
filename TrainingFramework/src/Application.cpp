#include "Application.h"
#include "GameStates/GameStateMachine.h"
#include "GameStates/GameStatebase.h"
extern GLint screenWidth;
extern GLint screenHeight;


Application::Application()
{
}


Application::~Application()
{
	soloud.deinit();
}

void Application::Play(std::string songName)
{
	songName = "src/music/" + songName;
	sample.load(songName.c_str()); // Load a wave file
	sample.setLooping(true);
	soloud.play(sample);        // Play it
}


void Application::Init()
{
	// Initialize SoLoud (automatic back-end selection)
	soloud.init();
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	GameStateMachine::GetInstance()->PushState(StateTypes::STATE_Intro);
}

void Application::Update(GLfloat deltaTime)
{
	GameStateMachine::GetInstance()->PerformStateChange();

	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->Update(deltaTime);
}

void Application::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->Draw();
}

void Application::HandleKeyEvent(unsigned char key, bool bIsPresseded)
{
	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->HandleKeyEvents(key, bIsPresseded);

}

void Application::HandleTouchEvent(GLint x, GLint y, bool bIsPresseded)
{

	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->HandleTouchEvents(x, y, bIsPresseded);
}

void Application::Exit()
{
	exit(0);
}
