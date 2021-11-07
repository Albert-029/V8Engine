#include "PanelInspector.h"
#include "ModuleGUI.h"
#include "ModuleWindow.h"

#include "Libraries/SDL/include/SDL_opengl.h"
#include "Libraries/imgui-1.78/imgui_impl_sdl.h"

PanelInspector::PanelInspector() : PanelManager()
{
}

PanelInspector::~PanelInspector()
{
}

bool PanelInspector::Start()
{
	this->active = true;

	return true;
}

bool PanelInspector::Draw()
{
	if (!App->gui->Pinspector->active)
		return false;

	if (App->gui->Pinspector->active)
	{
		if (ImGui::Begin("Inspector", &active))
		{
			if (ImGui::CollapsingHeader("Transform"))
			{

			}

			if (ImGui::CollapsingHeader("Mesh"))
			{

			}

			if (ImGui::CollapsingHeader("Texture"))
			{

			}

		}

		ImGui::End();
	}

	return true;
}