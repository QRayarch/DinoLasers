#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.01f;

#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false, bLastF = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

#pragma region Modifiers
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		bModifier = true;
#pragma endregion

#pragma region Camera Positioning
	/*
	if(bModifier)
		fSpeed *= 10.0f;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_pCameraMngr->MoveForward(fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_pCameraMngr->MoveForward(-fSpeed);
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_pCameraMngr->MoveSideways(-fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_pCameraMngr->MoveSideways(fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		m_pCameraMngr->MoveVertical(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		m_pCameraMngr->MoveVertical(fSpeed);
		*/
#pragma endregion
	
#pragma region Camera Control
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
	//	//m_pCameraMngr->MoveForward(-fSpeed);
	//
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	//	m_pCameraMngr->MoveForward(-fSpeed);
	//
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
	//{
	//	steveMatrix *= glm::rotate(matrix4(IDENTITY_M4), -1.0f, vector3(0.0f, 1.0f, 0.0f));
	//	//CameraFollow();
	//}
	//
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	//{
	//	//steveMatrix *= glm::rotate(matrix4(IDENTITY_M4), 1.0f, vector3(0.0f, 1.0f, 0.0f));
	//	//CameraFollow();
	//}
#pragma endregion

#pragma region Creeper Control
	//if (bModifier)
	//	fSpeed *= 10.0f;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	//	m_v3O1.x -= 0.1f;
	//
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	//	m_v3O1.x += 0.1f;
	//
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	//	m_v3O1.y -= 0.1f;
	//
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	//	m_v3O1.y += 0.1f;
#pragma region Creeper Control
	if (bModifier)
		fSpeed *= 10.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		m_v3O1.x -= 0.1f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		m_v3O1.x += 0.1f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_v3O1.z -= 0.1f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_v3O1.z += 0.1f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		playerRotation = quaternion(vector3(0.0f, glm::radians(1.0f), 0.0f)) * playerRotation;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		playerRotation = quaternion(vector3(0.0f, glm::radians(-1.0f), 0.0f)) * playerRotation;
#pragma endregion

#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL));
	ON_KEY_PRESS_RELEASE(F1, NULL, m_pCameraMngr->SetCameraMode(CAMPERSP));
	ON_KEY_PRESS_RELEASE(F2, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOZ));
	ON_KEY_PRESS_RELEASE(F3, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOY));
	ON_KEY_PRESS_RELEASE(F4, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOX));
#pragma endregion
}
void AppClass::ProcessMouse(void)
{
	m_bArcBall = false;
	m_bFPC = false;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
		m_bArcBall = true;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		m_bFPC = true;
}
