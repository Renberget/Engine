#pragma once
#include "Utils/MoreTypeTraits.hpp"
#include "Maths/Vec4.hpp"
#include "Type.hpp"
#include "Color.hpp"
#include <vector>

//Data layout for a mesh, used for vertex or instance layout
class MeshLayout
{
public:
	enum Usage : uint8_t
	{
		Vertex,
		Instance
	};

	//Variadic version of add
	template<typename T, typename U, typename... Vs>
	void add()
	{
		add<T>();
		add<U>();
		(add<Vs>(), ...);
	}

	/*!
	 * @brief Add a type to the layout
	 * @tparam T Can be an arithmetical type or a Vec2/Vec3/Vec4 or Color/Color32
	 * @param normalize If true and T is an integer type, data will be normalized between 0 and 1 for unsigned types and -1 and 1 for signed types
	 */
	template<typename T>
	void add(bool normalize = false)
	{
		constexpr int size = is_instance_of_v<T, Vec2> ? 2 : is_instance_of_v<T, Vec3> ? 3 : is_instance_of_v<T, Vec4> ? 4 : 1;
		if constexpr (size == 1)
		{
			addAttrib<T>(1, normalize);
			return;
		}
		addAttrib<first_template_parameter_t<T>>(size, normalize);
	}

	template<>
	void add<Color32>(bool normalize)
	{
		addAttrib<uint8_t>(4, true);
	}

	template<>
	void add<Color>(bool normalize)
	{
		addAttrib<float_t>(4, false);
	}

	void registerAttribs(Usage usage, const MeshLayout* previousLayout = nullptr) const;

private:
	struct Attrib
	{
		Type type;
		int elementSize;
		int size;
		bool isInt;
		bool normalize;
	};

	template<typename T>
	void addAttrib(int size, bool normalize)
	{
		constexpr Type type = getType<T>();
		static_assert(type != Type::Unknown);
		constexpr int elementSize = static_cast<int>(sizeof(T));
		mStride += size * elementSize;
		mAttribs.emplace_back(Attrib{ type, elementSize, size, std::is_integral_v<T>, normalize });
	}

	std::vector<Attrib> mAttribs;
	int mStride = 0;
};
