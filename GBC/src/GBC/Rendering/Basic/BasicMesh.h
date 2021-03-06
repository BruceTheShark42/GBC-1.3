#pragma once

#include "BasicVertex.h"
#include "GBC/IO/OBJLoader.h"

namespace gbc
{
	// TODO: refactor this
	struct BasicMesh
	{
		BasicMesh() = default;
		BasicMesh(uint32_t vertexCount, uint32_t indexCount);
		BasicMesh(const BasicMesh& mesh);
		BasicMesh(BasicMesh&& mesh) noexcept;
		BasicMesh& operator=(BasicMesh&& mesh) noexcept;
		BasicMesh(const OBJModel& model);
		BasicMesh(OBJModel&& model) noexcept;

		void Create(uint32_t vertexCount, uint32_t indexCount);

		std::vector<BasicVertex> vertices;
		std::vector<uint32_t> indices;
	};
}
