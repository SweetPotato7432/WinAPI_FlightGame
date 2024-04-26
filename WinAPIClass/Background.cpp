#include "Background.h"
#include "resource.h"
#include "Renderer.h"
#include "Application.h"


Background::Background()
{
	renderer = new Renderer(IDB_BG, *this);
	const SIZE& resolution = Application::GetDefaultResolution();
	SetPosition({ resolution.cx * 0.5f,resolution.cy * 0.5f });
	renderer->SetSize(resolution.cx, resolution.cy);

}
