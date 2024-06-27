#include <WAG/core/Application.h>
#include <WAG/core/Engine.h>

extern ApplicationCreationInfo GetAppInfo();

int main(int argc, char** argv) {
	ApplicationCreationInfo appInfo = GetAppInfo();
	Engine* engine = InitializeEngine(&appInfo, argc, &argv);

	RunEngine(engine);
	DestroyEngine(engine);
	return 0;
}