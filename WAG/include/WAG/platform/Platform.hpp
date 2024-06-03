#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>

class PlatformSpecificData;

// Static, also a Main window
class Platform final {
public:
	static PlatformSpecificData* data;
	
	static void Initialize(std::wstring title, int width, int height);
	static void Update();
	static void Shutdown();
	static bool IsInitiallized();
	
	static void Show(bool show = true);

	static void SetTitle(std::wstring title);
	static std::wstring GetTitle();

	static void SetSize(int width, int height);
	static void SetPosition(int x, int y);

	static glm::vec2 GetSize();
	static glm::vec2 GetPosition();
	static void* RendererSpecificData;
private:
	static bool initialized;
};

class PlatformChildWindow {
public:
	PlatformChildWindow(std::wstring title, int width, int height);
	~PlatformChildWindow();

	void Show(bool show = true);

	void SetTitle(std::wstring title);
	std::wstring GetTitle();

	void SetSize(int width, int height);
	void SetPosition(int x, int y);

	glm::vec2 GetSize();
	glm::vec2 GetPosition();

	void* RendererSpecificData = nullptr;
	PlatformSpecificData* data;
};