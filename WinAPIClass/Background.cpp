#include "Background.h"
#include "resource.h"
#include "Renderer.h"

Background::Background()
{
	renderer = new Renderer(IDB_BG, *this);
}
