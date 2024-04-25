#include "Component.h"
#include "GameObject.h"

void Component::SetActive(bool value)
{
	if (active != value) {
		active = value;
	}
}

bool Component::IsActive()
{
	return active;
}

Component::Component(GameObject& gameObject)
	:gameObject(gameObject), active(true)
{
	gameObject.AddComponent(this);
}
