#pragma once

#include "GBC/Rendering/Shader.h"

namespace gbc
{
	enum class ShaderType
	{
		None = 0,
		Vertex,
		TessolationControl,
		TessolationEvaluation,
		Geometry,
		Fragment,
		Compute
	};

	struct ShaderFile
	{
		ShaderType type;
		std::string source;
	};

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetFloat  (const std::string& name, float              value) override;
		virtual void SetFloat2 (const std::string& name, const glm::vec2&   value) override;
		virtual void SetFloat3 (const std::string& name, const glm::vec3&   value) override;
		virtual void SetFloat4 (const std::string& name, const glm::vec4&   value) override;
		virtual void SetInt    (const std::string& name, int                value) override;
		virtual void SetInt2   (const std::string& name, const glm::ivec2&  value) override;
		virtual void SetInt3   (const std::string& name, const glm::ivec3&  value) override;
		virtual void SetInt4   (const std::string& name, const glm::ivec4&  value) override;
		virtual void SetUInt   (const std::string& name, uint32_t           value) override;
		virtual void SetUInt2  (const std::string& name, const glm::uvec2&  value) override;
		virtual void SetUInt3  (const std::string& name, const glm::uvec3&  value) override;
		virtual void SetUInt4  (const std::string& name, const glm::uvec4&  value) override;
		virtual void SetBool   (const std::string& name, bool               value) override;
		virtual void SetBool2  (const std::string& name, const glm::bvec2&  value) override;
		virtual void SetBool3  (const std::string& name, const glm::bvec3&  value) override;
		virtual void SetBool4  (const std::string& name, const glm::bvec4&  value) override;
		virtual void SetMat2   (const std::string& name, const glm::mat2&   value) override;
		virtual void SetMat2x3 (const std::string& name, const glm::mat2x3& value) override;
		virtual void SetMat2x4 (const std::string& name, const glm::mat2x4& value) override;
		virtual void SetMat3x2 (const std::string& name, const glm::mat3x2& value) override;
		virtual void SetMat3   (const std::string& name, const glm::mat3&   value) override;
		virtual void SetMat3x4 (const std::string& name, const glm::mat3x4& value) override;
		virtual void SetMat4x2 (const std::string& name, const glm::mat4x2& value) override;
		virtual void SetMat4x3 (const std::string& name, const glm::mat4x3& value) override;
		virtual void SetMat4   (const std::string& name, const glm::mat4&   value) override;
		virtual void SetInts   (const std::string& name, const int*          values, int count) override;
		virtual void SetUInts  (const std::string& name, const uint32_t*     values, int count) override;
	private:
		std::vector<ShaderFile> ParseFile(const std::string& filepath);
		void CreateProgram(const std::vector<ShaderFile>& shaders);
		RendererID CompileShader(const ShaderFile& shader);
		bool LinkAndValidate();
		int GetUniformLocation(const std::string& name);

		RendererID rendererID = 0;
		std::unordered_map<std::string, int> uniformLocations;
	};
}
