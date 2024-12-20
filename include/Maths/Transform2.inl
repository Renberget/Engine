#pragma once

template<std::floating_point T>
consteval Transform2<T> Transform2<T>::identity()
{
	Transform2<T> transform;
	transform.mMatrix = Mat<3, 3, T>::identity();
	transform.mPosition = Vec2<T>::zero();
	transform.mRotation = static_cast<T>(0);
	transform.mScale = Vec2<T>::one();
	transform.mChanged = false;
	return transform;
}

template<std::floating_point T>
constexpr Transform2<T>::Transform2(const Vec2<T>& position, const T rotation, const Vec2<T>& scale) :
	mPosition(position),
	mRotation(rotation),
	mScale(scale),
	mChanged(false)
{
	updateMatrix();
}

template<std::floating_point T>
void Transform2<T>::setPosition(const Vec2<T>& position)
{
	mPosition = position;
	mChanged = true;
}

template<std::floating_point T>
const Vec2<T>& Transform2<T>::getPosition() const
{
	return mPosition;
}

template<std::floating_point T>
void Transform2<T>::setRotation(T rotation)
{
	mRotation = rotation;
	mChanged = true;
}

template<std::floating_point T>
T Transform2<T>::getRotation() const
{
	return mRotation;
}

template<std::floating_point T>
void Transform2<T>::setScale(T scale)
{
	mScale = Vec2<T>(scale);
	mChanged = true;
}

template<std::floating_point T>
void Transform2<T>::setScale(const Vec2<T>& scale)
{
	mScale = scale;
	mChanged = true;
}

template<std::floating_point T>
const Vec2<T>& Transform2<T>::getScale() const
{
	return mScale;
}

template<std::floating_point T>
void Transform2<T>::translate(const Vec2<T>& translation)
{
	mPosition += translation;
	mChanged = true;
}

template<std::floating_point T>
void Transform2<T>::rotate(T radians)
{
	mRotation += radians;
	mChanged = true;
}

template<std::floating_point T>
void Transform2<T>::scale(T scale)
{
	mScale *= scale;
	mChanged = true;
}

template<std::floating_point T>
void Transform2<T>::scale(const Vec2<T>& scale)
{
	mScale *= scale;
	mChanged = true;
}

template<std::floating_point T>
Transform2<T>& Transform2<T>::invert()
{
	mPosition = -mPosition;
	mRotation.safeInvert();
	mScale /= static_cast<T>(1);
	mChanged = true;
	return *this;
}

template<std::floating_point T>
Transform2<T> Transform2<T>::inverse() const
{
	return Transform2(*this).invert();
}

template<std::floating_point T>
const Mat<3, 3, T>& Transform2<T>::matrix() const
{
	if (mChanged)
	{
		mChanged = false;
		updateMatrix();
	}
	return mMatrix;
}

template<std::floating_point T>
std::span<const T, Mat<3, 3, T>::N> Transform2<T>::data() const
{
	return matrix().matrix();
}

template<std::floating_point T>
constexpr void Transform2<T>::updateMatrix() const
{
	T c = cos(mRotation);
	T s = sin(mRotation);

	mMatrix[0] = mScale.x * c;
	mMatrix[1] = mScale.y * s;
	mMatrix[2] = static_cast<T>(0);

	mMatrix[3] = mScale.x * -s;
	mMatrix[4] = mScale.y * c;
	mMatrix[5] = static_cast<T>(0);

	mMatrix[6] = mPosition.x;
	mMatrix[7] = mPosition.y;
	mMatrix[8] = static_cast<T>(1);
}