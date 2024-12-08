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
	mVertices.bind();
	if (!mId)
		glGenVertexArrays(1, &mId);
	glBindVertexArray(mId);
	vertexLayout.registerAttribs(MeshLayout::Usage::Vertex);
	mIndices.bind();
	glBindVertexArray(0);
}

void Mesh::create(const MeshLayout& vertexLayout, const MeshLayout& instanceLayout)
{
	mVertices.bind();
	if (!mId)
		glGenVertexArrays(1, &mId);
	glBindVertexArray(mId);
	vertexLayout.registerAttribs(MeshLayout::Usage::Vertex);
	mIndices.bind();
	mInstances.bind();
	instanceLayout.registerAttribs(MeshLayout::Usage::Instance, &vertexLayout);
	glBindVertexArray(0);
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

uint32_t Mesh::id() const
{
	return mId;
}

void Mesh::draw() const
{
	glBindVertexArray(mId);
	GLsizei instanceCount = mInstances.size() ? static_cast<GLsizei>(mInstances.size()) : 1;
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
