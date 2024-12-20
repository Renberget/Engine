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
	//Creates the mesh, the used buffers must be created before
	void create(const MeshLayout& vertexLayout);
	//Creates the mesh, the used buffers must be created before
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
	[[nodiscard]] inline uint32_t id() const { return mId; }
	//Draws the mesh on the currently bound target, prefer the draw function of RenderTexture
	void draw() const;
	void draw(int instanceCount) const;

private:
	IndicesBuffer mIndices;
	ArrayBuffer mVertices;
	ArrayBuffer mInstances;
	Primitive mPrimitive = Primitive::Triangles;
	uint32_t mId = 0;
};
