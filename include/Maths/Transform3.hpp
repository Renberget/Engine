#pragma once
#include "Quat.hpp"

template<std::floating_point T>
class Transform3
{
public:
	[[nodiscard]] consteval static Transform3<T> identity();

	constexpr Transform3() = default;
	constexpr Transform3(const Vec3<T>& position, const Quat<T>& rotation = Quat<T>::identity(), const Vec3<T>& scale = Vec3<T>::one());

	void setPosition(const Vec3<T>& position);
	[[nodiscard]] const Vec3<T>& getPosition() const;
	void setRotation(const Quat<T>& rotation);
	[[nodiscard]] const Quat<T>& getRotation() const;
	void setScale(T scale);
	void setScale(const Vec3<T>& scale);
	[[nodiscard]] const Vec3<T>& getScale() const;

	void translate(const Vec3<T>& translation);
	void rotate(const Quat<T>& rotation);
	void scale(T scale);
	void scale(const Vec3<T>& scale);

	//Faster than inverting the matrix
	Transform3& invert();
	//Faster than inverting the matrix
	[[nodiscard]] Transform3 inverse() const;

	[[nodiscard]] const Mat<4, 4, T>& matrix() const;
	[[nodiscard]] std::span<const T, Mat<4, 4, T>::N> data() const;

private:
	constexpr void updateMatrix() const;

	mutable Mat<4, 4, T> mMatrix;
	Quat<T> mRotation;
	Vec3<T> mPosition;
	Vec3<T> mScale;
	mutable bool mChanged;
};

#include "Transform3.inl"

using Transform3f = Transform3<float_t>;
using Transform3d = Transform3<double_t>;
