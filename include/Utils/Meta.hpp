#pragma once
#include <type_traits>

/*!
 * @return true if T is a specialization of template U
 */
template<typename T, template<typename...> typename U>
constexpr bool is_instance_of_v = std::false_type{};
/*!
 * @return true if T is a specialization of template U
 */
template<template<typename...> typename T, typename... Us>
constexpr bool is_instance_of_v<T<Us...>, T> = std::true_type{};


template<typename T>
struct first_template_parameter;
/*!
 * @brief Get the type of the first template parameter of T
 */
template<template<typename...> typename T, typename U, typename... Vs>
struct first_template_parameter<T<U, Vs...>>
{
	using type = U;
};
/*!
 * @brief Get the type of the first template parameter of T
 */
template<typename T>
using first_template_parameter_t = typename first_template_parameter<T>::type;


template<typename T>
struct member_ptr_to_type;
/*!
 * @brief Get the raw type of T, removing the member pointer
 */
template<typename T, typename S>
struct member_ptr_to_type<T S::*>
{
	using type = T;
};
/*!
 * @brief Get the raw type of T, removing the member pointer
 */
template<typename T>
using member_ptr_to_type_t = typename member_ptr_to_type<T>::type;

/*!
* @brief Returns the offset in bytes of an object member
*/
template<typename T, auto T::* Member>
static const size_t member_offset = reinterpret_cast<size_t>(&(reinterpret_cast<T*>(0)->*Member));
