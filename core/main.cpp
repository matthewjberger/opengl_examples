#include <Application.h>

int main(int argc, char * argv[])
{
	Application app;
	if (app.initialize_all(800, 600))
	{
		app.run();
	}
	return EXIT_SUCCESS;
}
