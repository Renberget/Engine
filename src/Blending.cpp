#include "Blending.hpp"
#include "Glfw.hpp"

const Blending Blending::Alpha(Factor::SrcAlpha, Factor::OneMinusSrcAlpha, Func::Add, Factor::One, Factor::OneMinusSrcAlpha, Func::Add);
const Blending Blending::Additive(Factor::SrcAlpha, Factor::One, Func::Add, Factor::One, Factor::One, Func::Add);
const Blending Blending::Multiplicative(Factor::DstColor, Factor::Zero, Func::Add);
const Blending Blending::None(Factor::One, Factor::Zero, Func::Add);

constexpr Blending::Blending(Factor srcFactor, Factor dstFactor, Func func) :
	colorSrcFactor(srcFactor), alphaSrcFactor(srcFactor),
	colorDstFactor(dstFactor), alphaDstFactor(dstFactor),
	colorFunc(func), alphaFunc(func)
{}

constexpr Blending::Blending(Factor colorSrcFactor, Factor colorDstFactor, Func colorFunc, Factor alphaSrcFactor, Factor alphaDstFactor, Func alphaFunc) :
	colorSrcFactor(colorSrcFactor),
	colorDstFactor(colorDstFactor),
	colorFunc(colorFunc),
	alphaSrcFactor(alphaSrcFactor),
	alphaDstFactor(alphaDstFactor),
	alphaFunc(alphaFunc)
{}

void Blending::bind() const
{
	glBlendFuncSeparate(static_cast<GLenum>(colorSrcFactor), static_cast<GLenum>(colorDstFactor), static_cast<GLenum>(alphaSrcFactor), static_cast<GLenum>(alphaDstFactor));
	glBlendEquationSeparate(static_cast<GLenum>(colorFunc), static_cast<GLenum>(alphaFunc));
}
