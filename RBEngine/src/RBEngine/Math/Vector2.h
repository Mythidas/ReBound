#pragma once

#include <glm/glm.hpp>

namespace RB
{
	template <typename T>
	struct TVector2;

	using gVec2 = glm::vec2;
	using Vector2 = TVector2<float>;
	using IVector2 = TVector2<int>;
	using UVector2 = TVector2<unsigned int>;

	template <typename T>
	struct TVector2
	{
		union { T x; T r; };
		union { T y; T g; };

		TVector2() : x(0), y(0) {}
		TVector2(T all) : x(all), y(all) {}
		TVector2(T x, T y) : x(x), y(y) {}

		// Scalar Ops
		TVector2 operator+(const T& rhs) const;
		TVector2 operator-(const T& rhs) const;
		TVector2 operator*(const T& rhs) const;
		TVector2 operator/(const T& rhs) const;

		TVector2& operator+=(const T& rhs);
		TVector2& operator-=(const T& rhs);
		TVector2& operator*=(const T& rhs);
		TVector2& operator/=(const T& rhs);

		// TVector2<T> Ops
		TVector2 operator+(const TVector2& rhs) const;
		TVector2 operator-(const TVector2& rhs) const;
		TVector2 operator*(const TVector2& rhs) const;
		TVector2 operator/(const TVector2& rhs) const;

		TVector2& operator+=(const TVector2& rhs);
		TVector2& operator-=(const TVector2& rhs);
		TVector2& operator*=(const TVector2& rhs);
		TVector2& operator/=(const TVector2& rhs);

		float operator[](int index) const
		{
			if (index == 0)
				return x;
			if (index == 1)
				return y;
		}

		operator glm::vec2() const
		{
			return glm::vec2(x, y);
		}
	};

	// Scalar Ops

	template <typename T>
	inline TVector2<T> TVector2<T>::operator+(const T& rhs) const
	{
		return TVector2<T>(x + rhs, y + rhs);
	}
	template <typename T>
	inline TVector2<T> TVector2<T>::operator-(const T& rhs) const
	{
		return TVector2<T>(x - rhs, y - rhs);
	}
	template <typename T>
	inline TVector2<T> TVector2<T>::operator*(const T& rhs) const
	{
		return TVector2<T>(x * rhs, y * rhs);
	}
	template <typename T>
	inline TVector2<T> TVector2<T>::operator/(const T& rhs) const
	{
		return TVector2<T>(x / rhs, y / rhs);
	}
	template <typename T>
	inline TVector2<T>& TVector2<T>::operator+=(const T& rhs)
	{
		x += rhs; y += rhs;
		return *this;
	}
	template <typename T>
	inline TVector2<T>& TVector2<T>::operator-=(const T& rhs)
	{
		x -= rhs; y -= rhs;
		return *this;
	}
	template <typename T>
	inline TVector2<T>& TVector2<T>::operator*=(const T& rhs)
	{
		x *= rhs; y *= rhs;
		return *this;
	}
	template <typename T>
	inline TVector2<T>& TVector2<T>::operator/=(const T& rhs)
	{
		x /= rhs; y /= rhs;
		return *this;
	}

	// TVector2<T> Ops

	template <typename T>
	inline TVector2<T> TVector2<T>::operator+(const TVector2<T>& rhs) const
	{
		return TVector2<T>(x + rhs.x, y + rhs.y);
	}
	template <typename T>
	inline TVector2<T> TVector2<T>::operator-(const TVector2<T>& rhs) const
	{
		return TVector2<T>(x - rhs.x, y - rhs.y);
	}
	template <typename T>
	inline TVector2<T> TVector2<T>::operator*(const TVector2<T>& rhs) const
	{
		return TVector2<T>(x * rhs.x, y * rhs.y);
	}
	template <typename T>
	inline TVector2<T> TVector2<T>::operator/(const TVector2<T>& rhs) const
	{
		return TVector2<T>(x / rhs.x, y / rhs.y);
	}
	template <typename T>
	inline TVector2<T>& TVector2<T>::operator+=(const TVector2<T>& rhs)
	{
		x += rhs.x; y += rhs.y;
		return *this;
	}
	template <typename T>
	inline TVector2<T>& TVector2<T>::operator-=(const TVector2<T>& rhs)
	{
		x -= rhs.x; y -= rhs.y;
		return *this;
	}
	template <typename T>
	inline TVector2<T>& TVector2<T>::operator*=(const TVector2<T>& rhs)
	{
		x *= rhs.x; y *= rhs.y;
		return *this;
	}
	template <typename T>
	inline TVector2<T>& TVector2<T>::operator/=(const TVector2<T>& rhs)
	{
		x /= rhs.x; y /= rhs.y;
		return *this;
	}
}