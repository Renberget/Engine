#include "Glfw.hpp"
#include "Type.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "Blending.hpp"

//Type
static_assert(static_cast<std::underlying_type_t<Type>>(Type::Bool) == GL_BOOL);
static_assert(static_cast<std::underlying_type_t<Type>>(Type::Byte) == GL_BYTE);
static_assert(static_cast<std::underlying_type_t<Type>>(Type::UnsignedByte) == GL_UNSIGNED_BYTE);
static_assert(static_cast<std::underlying_type_t<Type>>(Type::Short) == GL_SHORT);
static_assert(static_cast<std::underlying_type_t<Type>>(Type::UnsignedShort) == GL_UNSIGNED_SHORT);
static_assert(static_cast<std::underlying_type_t<Type>>(Type::Int) == GL_INT);
static_assert(static_cast<std::underlying_type_t<Type>>(Type::UnsignedInt) == GL_UNSIGNED_INT);
static_assert(static_cast<std::underlying_type_t<Type>>(Type::Float) == GL_FLOAT);
static_assert(static_cast<std::underlying_type_t<Type>>(Type::Double) == GL_DOUBLE);
static_assert(static_cast<std::underlying_type_t<Type>>(Type::HalfFloat) == GL_HALF_FLOAT);

//Texture
static_assert(static_cast<std::underlying_type_t<Texture::Wrapping>>(Texture::Wrapping::Repeat) == GL_REPEAT);
static_assert(static_cast<std::underlying_type_t<Texture::Wrapping>>(Texture::Wrapping::MirroredRepeat) == GL_MIRRORED_REPEAT);
static_assert(static_cast<std::underlying_type_t<Texture::Wrapping>>(Texture::Wrapping::ClampToEdge) == GL_CLAMP_TO_EDGE);
static_assert(static_cast<std::underlying_type_t<Texture::Wrapping>>(Texture::Wrapping::ClampToBorder) == GL_CLAMP_TO_BORDER);

static_assert(static_cast<std::underlying_type_t<Texture::Filter>>(Texture::Filter::Nearest) == GL_NEAREST);
static_assert(static_cast<std::underlying_type_t<Texture::Filter>>(Texture::Filter::Linear) == GL_LINEAR);

static_assert(static_cast<std::underlying_type_t<Texture::Format>>(Texture::Format::R) == GL_RED);
static_assert(static_cast<std::underlying_type_t<Texture::Format>>(Texture::Format::RG) == GL_RG);
static_assert(static_cast<std::underlying_type_t<Texture::Format>>(Texture::Format::RGB) == GL_RGB);
static_assert(static_cast<std::underlying_type_t<Texture::Format>>(Texture::Format::RGBA) == GL_RGBA);
static_assert(static_cast<std::underlying_type_t<Texture::Format>>(Texture::Format::BGRA) == GL_BGRA);

static_assert(static_cast<std::underlying_type_t<Texture::DepthStencilFormat>>(Texture::DepthStencilFormat::Depth16) == GL_DEPTH_COMPONENT16);
static_assert(static_cast<std::underlying_type_t<Texture::DepthStencilFormat>>(Texture::DepthStencilFormat::Depth24) == GL_DEPTH_COMPONENT24);
static_assert(static_cast<std::underlying_type_t<Texture::DepthStencilFormat>>(Texture::DepthStencilFormat::Depth32) == GL_DEPTH_COMPONENT32);
static_assert(static_cast<std::underlying_type_t<Texture::DepthStencilFormat>>(Texture::DepthStencilFormat::Depth32F) == GL_DEPTH_COMPONENT32F);
static_assert(static_cast<std::underlying_type_t<Texture::DepthStencilFormat>>(Texture::DepthStencilFormat::Depth24Stencil8) == GL_DEPTH24_STENCIL8);
static_assert(static_cast<std::underlying_type_t<Texture::DepthStencilFormat>>(Texture::DepthStencilFormat::Depth32FStencil8) == GL_DEPTH32F_STENCIL8);
static_assert(static_cast<std::underlying_type_t<Texture::DepthStencilFormat>>(Texture::DepthStencilFormat::StencilIndex1) == GL_STENCIL_INDEX1);
static_assert(static_cast<std::underlying_type_t<Texture::DepthStencilFormat>>(Texture::DepthStencilFormat::StencilIndex4) == GL_STENCIL_INDEX4);
static_assert(static_cast<std::underlying_type_t<Texture::DepthStencilFormat>>(Texture::DepthStencilFormat::StencilIndex8) == GL_STENCIL_INDEX8);
static_assert(static_cast<std::underlying_type_t<Texture::DepthStencilFormat>>(Texture::DepthStencilFormat::StencilIndex16) == GL_STENCIL_INDEX16);

//Buffer
static_assert(static_cast<std::underlying_type_t<Buffer::BufferFlags>>(Buffer::BufferFlags::DynamicStorage) == GL_DYNAMIC_STORAGE_BIT);
static_assert(static_cast<std::underlying_type_t<Buffer::BufferFlags>>(Buffer::BufferFlags::MapRead) == GL_MAP_READ_BIT);
static_assert(static_cast<std::underlying_type_t<Buffer::BufferFlags>>(Buffer::BufferFlags::MapWrite) == GL_MAP_WRITE_BIT);
static_assert(static_cast<std::underlying_type_t<Buffer::BufferFlags>>(Buffer::BufferFlags::MapPersistent) == GL_MAP_PERSISTENT_BIT);
static_assert(static_cast<std::underlying_type_t<Buffer::BufferFlags>>(Buffer::BufferFlags::MapCoherent) == GL_MAP_COHERENT_BIT);
static_assert(static_cast<std::underlying_type_t<Buffer::BufferFlags>>(Buffer::BufferFlags::ClientStorage) == GL_CLIENT_STORAGE_BIT);

//Primitives
static_assert(static_cast<std::underlying_type_t<Primitive>>(Primitive::Points) == GL_POINTS);
static_assert(static_cast<std::underlying_type_t<Primitive>>(Primitive::Lines) == GL_LINES);
static_assert(static_cast<std::underlying_type_t<Primitive>>(Primitive::LineLoop) == GL_LINE_LOOP);
static_assert(static_cast<std::underlying_type_t<Primitive>>(Primitive::LineStrip) == GL_LINE_STRIP);
static_assert(static_cast<std::underlying_type_t<Primitive>>(Primitive::Triangles) == GL_TRIANGLES);
static_assert(static_cast<std::underlying_type_t<Primitive>>(Primitive::TriangleStrip) == GL_TRIANGLE_STRIP);
static_assert(static_cast<std::underlying_type_t<Primitive>>(Primitive::TriangleFan) == GL_TRIANGLE_FAN);

//Blending
static_assert(static_cast<std::underlying_type_t<Blending::Factor>>(Blending::Factor::Zero) == GL_ZERO);
static_assert(static_cast<std::underlying_type_t<Blending::Factor>>(Blending::Factor::One) == GL_ONE);
static_assert(static_cast<std::underlying_type_t<Blending::Factor>>(Blending::Factor::SrcColor) == GL_SRC_COLOR);
static_assert(static_cast<std::underlying_type_t<Blending::Factor>>(Blending::Factor::OneMinusSrcColor) == GL_ONE_MINUS_SRC_COLOR);
static_assert(static_cast<std::underlying_type_t<Blending::Factor>>(Blending::Factor::SrcAlpha) == GL_SRC_ALPHA);
static_assert(static_cast<std::underlying_type_t<Blending::Factor>>(Blending::Factor::OneMinusSrcAlpha) == GL_ONE_MINUS_SRC_ALPHA);
static_assert(static_cast<std::underlying_type_t<Blending::Factor>>(Blending::Factor::DstAlpha) == GL_DST_ALPHA);
static_assert(static_cast<std::underlying_type_t<Blending::Factor>>(Blending::Factor::OneMinusDstAlpha) == GL_ONE_MINUS_DST_ALPHA);
static_assert(static_cast<std::underlying_type_t<Blending::Factor>>(Blending::Factor::DstColor) == GL_DST_COLOR);
static_assert(static_cast<std::underlying_type_t<Blending::Factor>>(Blending::Factor::OneMinusDstColor) == GL_ONE_MINUS_DST_COLOR);

static_assert(static_cast<std::underlying_type_t<Blending::Func>>(Blending::Func::Add) == GL_FUNC_ADD);
static_assert(static_cast<std::underlying_type_t<Blending::Func>>(Blending::Func::Subtract) == GL_FUNC_SUBTRACT);
static_assert(static_cast<std::underlying_type_t<Blending::Func>>(Blending::Func::ReverseSubtract) == GL_FUNC_REVERSE_SUBTRACT);
static_assert(static_cast<std::underlying_type_t<Blending::Func>>(Blending::Func::Min) == GL_MIN);
static_assert(static_cast<std::underlying_type_t<Blending::Func>>(Blending::Func::Max) == GL_MAX);