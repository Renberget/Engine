#pragma once
#include "Mat.hpp"

template<std::floating_point T>
class Transform2
{
public:
	[[nodiscard]] consteval static Transform2<T> identity();

	constexpr Transform2() = default;
	constexpr Transform2(const Vec2<T>& position, const T rotation = static_cast<T>(0), const Vec2<T>& scale = Vec2<T>::one());

	void setPosition(const Vec2<T>& position);
	[[nodiscard]] const Vec2<T>& getPosition() const;
	void setRotation(T rotation);
	[[nodiscard]] T getRotation() const;
	void setScale(T scale);
	void setScale(const Vec2<T>& scale);
	[[nodiscard]] const Vec2<T>& getScale() const;

	void translate(const Vec2<T>& translation);
	void rotate(T radians);
	void scale(T scale);
	void scale(const Vec2<T>& scale);

	//Faster than inverting the matrix
	Transform2& invert();
	//Faster than inverting the matrix
	[[nodiscard]] Transform2 inverse() const;

	[[nodiscard]] const Mat<3, 3, T>& matrix() const;
	[[nodiscard]] std::span<const T, Mat<3, 3, T>::N> data() const;

private:
	constexpr void updateMatrix() const;

	mutable Mat<3, 3, T> mMatrix;
	Vec2<T> mPosition;
	Vec2<T> mScale;
	T mRotation;
	mutable bool mChanged;
};

#include "Transform2.inl"

using Transform2f = Transform2<float_t>;
using Transform2d = Transform2<double_t>;
