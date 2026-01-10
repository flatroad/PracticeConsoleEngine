#include "DemoLevel.h"
#include "Actors/TestActor.h"

DemoLevel::DemoLevel()
{
	AddActor(new TestActor());
}
