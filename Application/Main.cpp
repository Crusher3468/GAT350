#include "Engine.h"
#include <iostream>

#define POST_PROCESS

int main(int ardc, char** argv)
{
	neu::InitializeMemory();
	neu::SetFilePath("../Assets");


	neu::Engine::Instance().Initialize();
	neu::Engine::Instance().Register();

	neu::g_renderer.CreateWindow("Neumont", 800, 600);

	neu::g_gui.Initialize(neu::g_renderer);

	auto texture = std::make_shared<neu::Texture>();
	texture->CreateTexture(1024, 1024);
	neu::g_resources.Add<neu::Texture>("fb_texture", texture);

	auto framebuffer = neu::g_resources.Get<neu::Framebuffer>("framebuffer", "fb_texture");
	framebuffer->Unbind();

	auto scene = neu::g_resources.Get<neu::Scene>("scenes/final.scn");

	glm::vec3 rot{ 0, 0, 0 };
	float ri = 1;
	bool quit = false;

	while (!quit)
	{
		neu::Engine::Instance().Update();
		neu::g_gui.BeginFrame(neu::g_renderer);

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		/*
		auto actor = scene->GetActorFromName("Ogre");
		if (actor)
		{
			actor->m_transform.rotation - math::EulerToQuaternion(rot);
		}

		auto program = neu::g_resources.Get<neu::Program>("shaders/fx/refraction.prog");

		if (program)
		{
			program->Use();
			program->SetUniform("ri", ri);
		}
		*/

		/*
		//Wave
		auto program = neu::g_resources.Get<neu::Program>("shaders/postprocess/postprocess.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("offset", neu::g_time.time);
		}
		*/

		//ImGui::Begin("Transform");
		//ImGui::DragFloat3("Rotation", &rot[0]);
		//ImGui::DragFloat("Refraction Index", &ri, 0.01f, 1, 3);
		//ImGui::End();

		scene->Update();

#ifdef POST_PROCESS 
		// don't draw post process actor when rendering to the framebuffer 
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(false);
			}
		}
		// render pass 1 (render scene to framebuffer) 
		neu::g_renderer.SetViewport(0, 0, framebuffer->GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
		framebuffer->Unbind();

		// render pass 2 (render to screen) 
		neu::g_renderer.RestoreViewport();
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);

		// draw only the post process actor to the screen 
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(true);
				actor->Draw(neu::g_renderer);
			}
		}
#else 
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
#endif // POST_PROCESS 


		// draw gui
		neu::g_gui.Draw();
		neu::g_renderer.EndFrame();
		neu::g_gui.EndFrame();
	}


	scene->RemoveAll();
	neu::Engine::Instance().Shutdown();
	return 0;
}