#include "Plane.h"
#include "AtlasRenderer.h"
#include "resource.h"

Plane::Plane()
{
	AtlasRenderer* renderer = new AtlasRenderer(IDB_PLANE, *this, 8, RGB(255, 0, 255));

	renderer->SetSize(200, 150);
	renderer->SetIndex(1);
}
