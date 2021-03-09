#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace cbc
{
	RendererAPI::API RendererAPI::api = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::CreateScope()
	{
		switch (api)
		{
			case API::None:   return nullptr;
			case API::OpenGL: return cbc::CreateScope<OpenGLRendererAPI>();
		}

		CBC_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}
