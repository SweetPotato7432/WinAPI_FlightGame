#include "Background.h"
#include "resource.h"
#include "Renderer.h"
#include "Application.h"
#include "Time.h"


void Background::Update()
{
	const SIZE& resolution = Application::GetDefaultResolution();

	if (position.x <= -resolution.cx * 0.5f) {
		SetPosition({ resolution.cx * 1.5f,resolution.cy * 0.5f });
	}

	// �ѹ� ���� �� ������ 1*deltatTime��ŭ �̵��ϴ� �ڵ�
	Move({ -scrollSpeed * Time::GetDeltaTime() , 0.0f });
}

Background::Background() : scrollSpeed(100.0f)
{
	renderer = new Renderer(IDB_BG, *this);
	const SIZE& resolution = Application::GetDefaultResolution();
	SetPosition({ resolution.cx * 0.5f,resolution.cy * 0.5f });
	renderer->SetSize(resolution.cx, resolution.cy);

}
