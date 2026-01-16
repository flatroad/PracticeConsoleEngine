#pragma once

#include <cstddef>

/// @class RTTI
/// @brief 런타임 타입 정보를 제공하는 베이스 클래스.
/// 
/// 파생 클래스는 RTTI_DECLARTIONS 매크로를 사용하여
/// 고유한 타입 ID와 타입 검사(Is), 캐스팅(As) 기능을 제공합니다.
class RTTI
{
public:
	/// @brief 가상 소멸자입니다.
	virtual ~RTTI() = default;

	/// @brief 이 객체 인스턴스의 타입 ID를 반환합니다.
	/// @return 정수 기반 타입 ID입니다.
	virtual std::size_t TypeIdInstance() const = 0;

	/// @brief 정수 기반 타입 ID와 현재 객체의 타입을 비교합니다.
	/// @param[In] id 비교할 타입 ID입니다.
	/// @return 현재 객체의 타입이 id와 일치하면 true를 반환합니다.
	virtual bool Is(std::size_t id) const
	{
		return (TypeIdInstance() == id);
	}

	/// @brief 템플릿 타입 T와 현재 객체의 타입을 비교합니다.
	/// @tparam T 비교할 타입입니다.
	/// @return 현재 객체가 T 타입(또는 T로 취급 가능)이라면 true를 반환합니다.
	template<typename T>
	bool Is() const
	{
		return (Is(T::TypeIdClass()));
	}

	/// @brief 템플릿 타입 T로 안전하게 캐스팅합니다.
	/// @tparam T 캐스팅할 타입입니다.
	/// @return 캐스팅에 성공하면 T* 를, 실패하면 nullptr를 반환합니다.
	template<typename T>
	T* As()
	{
		return (Is<T> ? static_cast<T*>(this) : nullptr);
	}

	/// @brief 템플릿 타입 T로 안전하게 캐스팅합니다(const 버전).
	/// @tparam T 캐스팅할 타입입니다.
	/// @return 캐스팅에 성공하면 const T* 를, 실패하면 nullptr를 반환합니다.
	template<typename T>
	const T* As() const
	{
		return (Is<T>() ? static_cast<const T*>(this) : nullptr);
	}
};

/// @brief 파생 클래스에 RTTI 관련 선언을 추가하는 매크로입니다.
///
/// Type: 이 매크로를 사용하는 클래스 이름입니다.
/// ParentType: 바로 위 부모 클래스 타입입니다.
/// 
/// 각 타입은 정적 지역 변수의 주소를 이용해
/// 고유한 정수 기반 타입 ID를 가지게 됩니다.
/// Is(id) 함수는 자신의 타입 ID와 부모 타입들의 ID를 재귀적으로 검사합니다.
#define RTTI_DECLARATIONS(Type, ParentType)							\
public:																\
	using Parent = ParentType;										\
																	\
	static std::size_t TypeIdClass()								\
	{																\
		static int sRunTimeTypeId;									\
		return (reinterpret_cast<std::size_t>(&sRunTimeTypeId));	\
	}																\
																	\
	virtual std::size_t TypeIdInstance() const override				\
	{																\
		return (TypeIdClass());										\
	}																\
																	\
	virtual bool Is(std::size_t id) const override					\
	{																\
		if (id == TypeIdClass())									\
		{															\
			return (true);											\
		}															\
		return (ParentType::Is(id));								\
	}