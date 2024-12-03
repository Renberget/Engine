#pragma once
#include <cstdint>

struct Blending
{
	enum Factor : uint32_t
	{
		Zero = 0,
		One = 1,
		SrcColor = 0x0300,
		OneMinusSrcColor = 0x0301,
		SrcAlpha = 0x0302,
		OneMinusSrcAlpha = 0x0303,
		DstAlpha = 0x0304,
		OneMinusDstAlpha = 0x0305,
		DstColor = 0x0306,
		OneMinusDstColor = 0x0307
	};

	enum Func : uint32_t
	{
		Add = 0x8006,
		Subtract = 0x800A,
		ReverseSubtract = 0x800B,
		Min = 0x8007,
		Max = 0x8008
	};

	static const Blending Alpha;
	static const Blending Additive;
	static const Blending Multiplicative;
	static const Blending None;

	Blending() = default;
	//Creates blending with same srcFactor and dstFactor for color and alpha
	constexpr explicit Blending(Factor srcFactor, Factor dstFactor, Func func = Func::Add);
	//Creates blending with different srcFactor and dstFactor for color and alpha
	constexpr explicit Blending(Factor colorSrcFactor, Factor colorDstFactor, Func colorFunc, Factor alphaSrcFactor, Factor alphaDstFactor, Func alphaFunc);
	void bind() const;

	Factor colorSrcFactor;
	Factor colorDstFactor;
	Func colorFunc;
	Factor alphaSrcFactor;
	Factor alphaDstFactor;
	Func alphaFunc;
};
