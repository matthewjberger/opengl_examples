#pragma once

#include "ApplicationBase.h"

class Application : public ApplicationBase
{
public:
	Application();
	~Application();

	void initialize() override;
	void cleanup() override;
	void update() override;
	void render() override;
};
