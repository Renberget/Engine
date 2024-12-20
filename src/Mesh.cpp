#include "Mesh.hpp"
#include "Glfw.hpp"

Mesh::Mesh(Mesh&& mesh) noexcept :
	mVertices(std::move(mesh.mVertices)),
	mIndices(std::move(mesh.mIndices)),
	mInstances(std::move(mesh.mInstances)),
	mPrimitive(mesh.mPrimitive),
	mId(mesh.mId)
{
	mesh.mId = 0;
}

Mesh& Mesh::operator=(Mesh&& mesh) noexcept
{
	mVertices = std::move(mesh.mVertices);
	mIndices = std::move(mesh.mIndices);
	mInstances = std::move(mesh.mInstances);
	mPrimitive = mesh.mPrimitive;
	mId = mesh.mId;
	mesh.mId = 0;
	return *this;
}

void Mesh::create(const MeshLayout& vertexLayout)
{
	assert(!mId);
	glCreateVertexArrays(1, &mId);
	vertexLayout.registerAttribs(mId, mVertices.id(), MeshLayout::Usage::Vertex);
	if (mIndices.id())
		glVertexArrayElementBuffer(mId, mIndices.id());
}

void Mesh::create(const MeshLayout& vertexLayout, const MeshLayout& instanceLayout)
{
	create(vertexLayout);
	instanceLayout.registerAttribs(mId, mInstances.id(), MeshLayout::Usage::Instance, &vertexLayout);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &mId);
}

void Mesh::setPrimitive(Primitive primitive)
{
	mPrimitive = primitive;
}

ArrayBuffer& Mesh::vertices()
{
	return mVertices;
}

IndicesBuffer& Mesh::indices()
{
	return mIndices;
}

ArrayBuffer& Mesh::instances()
{
	return mInstances;
}

void Mesh::draw() const
{
	draw(mInstances.size() ? static_cast<GLsizei>(mInstances.size()) : 1);
}

void Mesh::draw(int instanceCount) const
{
	glBindVertexArray(mId);
	if (mIndices.id())
	{
		assert(mIndices.storedType() == typeid(uint8_t) || mIndices.storedType() == typeid(uint16_t) || mIndices.storedType() == typeid(uint32_t));
		GLenum indexType =
			mIndices.storedType() == typeid(uint8_t) ? GL_UNSIGNED_BYTE :
			mIndices.storedType() == typeid(uint16_t) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;

		glDrawElementsInstanced(static_cast<GLenum>(mPrimitive), static_cast<GLsizei>(mIndices.size()), indexType, nullptr, instanceCount);
		return;
	}
	glDrawArraysInstanced(static_cast<GLenum>(mPrimitive), 0, static_cast<GLsizei>(mVertices.size()), instanceCount);
}
