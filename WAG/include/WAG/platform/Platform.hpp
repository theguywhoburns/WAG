#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>

class PlatformSpecificData;

// Static
class Platform final {
public:
	PlatformSpecificData* data;
	
	static void Initialize();
	static void Shutdown();
	static bool IsInitiallized();
private:
	static bool initialized;
};

class PlatformWindow {
public:
	void Show(bool show = true);
	bool ShouldClose();
	void ShouldClose(bool close);
	void Update();

	void SetTitle(std::wstring title);
	std::wstring GetTitle();

	void SetSize(int width, int height);
	void SetPosition(int x, int y);

	glm::vec2 GetSize();
	glm::vec2 GetPosition();

	void* RendererSpecificData = nullptr;
};