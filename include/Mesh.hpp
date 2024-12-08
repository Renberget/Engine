#pragma once
#include "MeshLayout.hpp"
#include "ArrayBuffer.hpp"
#include "IndicesBuffer.hpp"

enum class Primitive : uint32_t
{
	Points,
	Lines,
	LineLoop,
	LineStrip,
	Triangles,
	TriangleStrip,
	TriangleFan
};

class Mesh : public Uncopyable
{
public:
	Mesh() = default;
	Mesh(Mesh&& mesh) noexcept;
	Mesh& operator=(Mesh&& mesh) noexcept;
	~Mesh();
	void create(const MeshLayout& vertexLayout);
	void create(const MeshLayout& vertexLayout, const MeshLayout& instanceLayout);
	//Set the mesh primitive
	void setPrimitive(Primitive primitive);
	
	//Returns the vertices buffer
	[[nodiscard]] ArrayBuffer& vertices();
	//Returns the indices buffer
	[[nodiscard]] IndicesBuffer& indices();
	//Returns the instances buffer
	[[nodiscard]] ArrayBuffer& instances();
	//Returns the OpenGL handle
	[[nodiscard]] uint32_t id() const;

private:
	void draw() const;

	IndicesBuffer mIndices;
	ArrayBuffer mVertices;
	ArrayBuffer mInstances;
	Primitive mPrimitive = Primitive::Triangles;
	uint32_t mId = 0;

	friend class RenderTarget;
};
