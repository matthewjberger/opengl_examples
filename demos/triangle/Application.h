#pragma once

#include "ApplicationBase.h"

class Application : public ApplicationBase
{
public:
	Application();
	~Application();

	void render() override;
};
