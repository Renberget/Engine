#pragma once
#include "Utils/Meta.hpp"
#include "Maths/Math.hpp"
#include "Type.hpp"
#include "Color.hpp"
#include <vector>
#include <assert.h>

template<typename T>
concept standard_layout = std::is_standard_layout_v<T>;

//Data layout that stores all the members of a struct
class MeshLayout
{
public:
	enum Usage : uint8_t
	{
		Vertex,
		Instance
	};

	/*!
	 * @brief Creates the layout
	 * @tparam T The object corresponding to this layout
	 * @tparam Members of the object, all the members must be provided and ordered like in the object declaration, a member type can be arithmetical, VecN or Color/Color32
	 * @param normalize If true and applied to an integer type, data will be normalized between 0.0 and 1.0 for unsigned types and -1.0 and 1.0 for signed types
	 */
	template<typename T, auto T::*... Members>
	void create(std::initializer_list<bool> normalize = {})
	{
		assert(mAttribs.empty());

#ifndef NDEBUG
		//Check if all members of T are present and packed in the right order
		bool isAlignmentCorrect = true;
		size_t alignment = 0;
		([&]
			{
				if (alignment != member_offset<T, Members>)
					isAlignmentCorrect = false;
				alignment += sizeof(member_ptr_to_type_t<decltype(Members)>);
			}(), ...);
		assert(isAlignmentCorrect);
		assert(alignment == sizeof(T));
#endif

		if (normalize.size())
		{
			size_t i = 0;
			(addType<member_ptr_to_type_t<decltype(Members)>>(normalize.begin()[i++]), ...);
		}
		else
		{
			(addType<member_ptr_to_type_t<decltype(Members)>>(true), ...);
		}
	}

private:
	struct Attrib
	{
		Type type;
		int elementSize;
		int size;
		bool isFloat;
		bool normalize;
	};

	template<math::vec T>
	void addType(bool normalize)
	{
		addAttrib<first_template_parameter_t<T>>(T::N, normalize);
	}
	
	template<standard_layout T> requires(!math::vec<T>)
	void addType(bool normalize)
	{
		addAttrib<T>(1, normalize);
	}

	template<>
	void addType<Color32>(bool normalize)
	{
		addAttrib<uint8_t>(4, normalize);
	}

	template<>
	void addType<Color>(bool normalize)
	{
		addAttrib<float_t>(4, false);
	}
	
	template<standard_layout T>
	void addAttrib(int size, bool normalize)
	{
		constexpr Type type = getType<T>();
		static_assert(type != Type::Unknown);
		constexpr int elementSize = static_cast<int>(sizeof(T));
		mStride += size * elementSize;
		mAttribs.emplace_back(Attrib
			{
				.type = type,
				.elementSize = elementSize,
				.size = size,
				.isFloat = std::is_floating_point_v<T>,
				.normalize = normalize && std::is_integral_v<T>
			});
	}

	void registerAttribs(uint32_t vaoId, uint32_t vboId, Usage usage, const MeshLayout* previousLayout = nullptr) const;

	std::vector<Attrib> mAttribs;
	int mStride = 0;

	friend class Mesh;
};
