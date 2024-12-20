#include "Transform3.hpp"
#pragma once

template<std::floating_point T>
consteval Transform3<T> Transform3<T>::identity()
{
	Transform3<T> transform;
	transform.mMatrix = Mat<4, 4, T>::identity();
	transform.mPosition = Vec3<T>::zero();
	transform.mRotation = Quat<T>::identity();
	transform.mScale = Vec3<T>::one();
	transform.mChanged = false;
	return transform;
}

template<std::floating_point T>
constexpr Transform3<T>::Transform3(const Vec3<T>& position, const Quat<T>& rotation, const Vec3<T>& scale) :
	mPosition(position),
	mRotation(rotation),
	mScale(scale),
	mChanged(false)
{
	updateMatrix();
}

template<std::floating_point T>
void Transform3<T>::setPosition(const Vec3<T>& position)
{
	mPosition = position;
	mChanged = true;
}

template<std::floating_point T>
const Vec3<T>& Transform3<T>::getPosition() const
{
	return mPosition;
}

template<std::floating_point T>
void Transform3<T>::setRotation(const Quat<T>& rotation)
{
	mRotation = rotation;
	mChanged = true;
}

template<std::floating_point T>
const Quat<T>& Transform3<T>::getRotation() const
{
	return mRotation;
}

template<std::floating_point T>
void Transform3<T>::setScale(T scale)
{
	mScale = Vec3<T>(scale);
	mChanged = true;
}

template<std::floating_point T>
void Transform3<T>::setScale(const Vec3<T>& scale)
{
	mScale = scale;
	mChanged = true;
}

template<std::floating_point T>
const Vec3<T>& Transform3<T>::getScale() const
{
	return mScale;
}

template<std::floating_point T>
void Transform3<T>::translate(const Vec3<T>& translation)
{
	mPosition += translation;
	mChanged = true;
}

template<std::floating_point T>
void Transform3<T>::rotate(const Quat<T>& rotation)
{
	mRotation *= rotation;
	mChanged = true;
}

template<std::floating_point T>
void Transform3<T>::scale(T scale)
{
	mScale *= scale;
	mChanged = true;
}

template<std::floating_point T>
void Transform3<T>::scale(const Vec3<T>& scale)
{
	mScale *= scale;
	mChanged = true;
}

template<std::floating_point T>
Transform3<T>& Transform3<T>::invert()
{
	mPosition = -mPosition;
	mRotation.safeInvert();
	mScale /= static_cast<T>(1);
	mChanged = true;
	return *this;
}

template<std::floating_point T>
Transform3<T> Transform3<T>::inverse() const
{
	return Transform3(*this).invert();
}

template<std::floating_point T>
const Mat<4, 4, T>& Transform3<T>::matrix() const
{
	if (mChanged)
	{
		mChanged = false;
		updateMatrix();
	}
	return mMatrix;
}

template<std::floating_point T>
std::span<const T, Mat<4, 4, T>::N> Transform3<T>::data() const
{
	return matrix().matrix();
}

template<std::floating_point T>
constexpr void Transform3<T>::updateMatrix() const
{
	Mat<3, 3, T> rotationMatrix = mRotation.rotationMatrix();
	
	mMatrix[0] = mScale.x * rotationMatrix[0];
	mMatrix[1] = mScale.x * rotationMatrix[1];
	mMatrix[2] = mScale.x * rotationMatrix[2];
	mMatrix[3] = static_cast<T>(0);

	mMatrix[4] = mScale.y * rotationMatrix[3];
	mMatrix[5] = mScale.y * rotationMatrix[4];
	mMatrix[6] = mScale.y * rotationMatrix[5];
	mMatrix[7] = static_cast<T>(0);

	mMatrix[8] = mScale.z * rotationMatrix[6];
	mMatrix[9] = mScale.z * rotationMatrix[7];
	mMatrix[10] = mScale.z * rotationMatrix[8];
	mMatrix[11] = static_cast<T>(0);

	mMatrix[12] = mPosition.x;
	mMatrix[13] = mPosition.y;
	mMatrix[14] = mPosition.z;
	mMatrix[15] = static_cast<T>(1);
}