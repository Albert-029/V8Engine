#include "Application.h"
#include "ModuleUserInterface.h"
#include "ModuleGUI.h"
#include "ModuleRenderer3D.h"
#include "FontUI.h"

ModuleUserInterface::ModuleUserInterface(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleUserInterface::~ModuleUserInterface()
{
}

bool ModuleUserInterface::Init()
{
	FT_Error error = FT_Init_FreeType(&ft_library);

	if (error)
	{
		LOG_C("ERROR: Could not init FreeType Library ");
	}

	return true;
}

bool ModuleUserInterface::Start()
{
	LoadFont("arial", 20);

	return true;
}

update_status ModuleUserInterface::Update(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleUserInterface::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleUserInterface::CleanUp()
{
	return true;
}

FontUI* ModuleUserInterface::LoadFont(std::string name, int size)
{
	FontUI* new_font = new FontUI();

	new_font->name = name;
	string path = ASSETS_FONTS_FOLDER + name + ".ttf";
	FT_Error error = FT_New_Face(ft_library, path.c_str(), 0, &new_font->text_font);

	if (error)
	{
		LOG_C("ERROR: Couldn't load the font '%s'", name.c_str());
		return nullptr;
	}
	else
	{
		LOG_C("The font '%s' has been loaded correctly", name.c_str());
		FT_Set_Pixel_Sizes(new_font->text_font, 0, size);
		new_font->CreateCharacterText();
		fontsList.push_back(new_font);
		return new_font;
	}

	FT_Done_Face(new_font->text_font);
	FT_Done_FreeType(ft_library);
}

FontUI* ModuleUserInterface::GetFont(std::string name)
{
	for (auto it = fontsList.begin(); it != fontsList.end(); it++)
	{
		if ((*it)->name == name)
		{
			return (*it);
		}
	}

	return nullptr;
}

void ModuleUserInterface::SetOrthogonalCamera()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// args: left, right, bottom, top, near, far
	float left = 0.0f;
	float right = 640.0f;
	float bottom = 480.0f;
	float top = 0.0f;
	float near_plane = 1.0f;
	float far_plane = -1.0f;

	glOrtho(left, right, bottom, top, near_plane, far_plane);
}

void ModuleUserInterface::UseUIRenderSettings()
{
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void ModuleUserInterface::DrawUI()
{
	// GetComponentCamera to set what camera we will be using while rendering elements of the list

	for (std::vector<GameObject*>::iterator it = GOcanvas.begin(); it != GOcanvas.end(); it++)
	{
		// we must set the orthogonal cam here (?) and then...

		UseUIRenderSettings();
		(*it)->Draw();
	}
}

void ModuleUserInterface::AddCanvasGO(GameObject* GO)
{
	GOcanvas.push_back(GO);
}


