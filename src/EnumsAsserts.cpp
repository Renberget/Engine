#include "Glfw.hpp"
#include "Type.hpp"
#include "Texture.hpp"
#include "Buffer.hpp"
#include "Blending.hpp"

//Type
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
static_assert(static_cast<std::underlying_type_t<Texture::DepthStencilFormat>>(Texture::DepthStencilFormat::Depth32F) == GL_DEPTH_COMPONENT32);
static_assert(static_cast<std::underlying_type_t<Texture::DepthStencilFormat>>(Texture::DepthStencilFormat::Depth24Stencil8) == GL_DEPTH24_STENCIL8);
static_assert(static_cast<std::underlying_type_t<Texture::DepthStencilFormat>>(Texture::DepthStencilFormat::Depth32FStencil8) == GL_DEPTH32F_STENCIL8);

//Buffer
static_assert(static_cast<std::underlying_type_t<Usage>>(Usage::Stream) == GL_STREAM_DRAW);
static_assert(static_cast<std::underlying_type_t<Usage>>(Usage::Static) == GL_STATIC_DRAW);
static_assert(static_cast<std::underlying_type_t<Usage>>(Usage::Dynamic) == GL_DYNAMIC_DRAW);

static_assert(static_cast<std::underlying_type_t<BufferType>>(BufferType::Array) == GL_ARRAY_BUFFER);
static_assert(static_cast<std::underlying_type_t<BufferType>>(BufferType::IndicesArray) == GL_ELEMENT_ARRAY_BUFFER);
static_assert(static_cast<std::underlying_type_t<BufferType>>(BufferType::Uniform) == GL_UNIFORM_BUFFER);

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