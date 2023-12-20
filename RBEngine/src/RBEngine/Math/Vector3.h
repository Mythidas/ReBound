#pragma once

#include <glm/glm.hpp>

namespace RB
{
	template <typename T>
	struct TVector3;

	using gVec3 = glm::vec3;
	using Vector3 = TVector3<float>;
	using IVector3 = TVector3<int>;
	using UVector3 = TVector3<unsigned int>;

	template <typename T>
	struct TVector3
	{
		union { T x; T r; };
		union { T y; T g; };
		union { T z; T b; };

		static const Vector3 One;
		static const Vector3 Zero;
		static const Vector3 Up;
		static const Vector3 Right;
		static const Vector3 Left;
		static const Vector3 Down;
		static const Vector3 Back;
		static const Vector3 Forward;

		TVector3() : x(0), y(0), z(0) {}
		TVector3(T all) : x(all), y(all), z(all) {}
		TVector3(T x, T y, T z) : x(x), y(y), z(z) {}
		TVector3(const gVec3& vec3) : x(vec3.x), y(vec3.y), z(vec3.z) {}

		// Scalar Ops
		TVector3<T> operator+(const T& rhs) const;
		TVector3<T> operator-(const T& rhs) const;
		TVector3<T> operator*(const T& rhs) const;
		TVector3<T> operator/(const T& rhs) const;

		TVector3<T>& operator+=(const T& rhs);
		TVector3<T>& operator-=(const T& rhs);
		TVector3<T>& operator*=(const T& rhs);
		TVector3<T>& operator/=(const T& rhs);

		// TVector3<T> Ops
		TVector3<T> operator+(const TVector3<T>& rhs) const;
		TVector3<T> operator-(const TVector3<T>& rhs) const;
		TVector3<T> operator*(const TVector3<T>& rhs) const;
		TVector3<T> operator/(const TVector3<T>& rhs) const;
		
		TVector3<T>& operator+=(const TVector3<T>& rhs);
		TVector3<T>& operator-=(const TVector3<T>& rhs);
		TVector3<T>& operator*=(const TVector3<T>& rhs);
		TVector3<T>& operator/=(const TVector3<T>& rhs);

		T operator[](int index) const
		{
			if (index == 0)
				return x;
			if (index == 1)
				return y;
			if (index == 2)
				return z;
		}

		operator glm::vec3() const
		{
			return glm::vec3(x, y, z);
		}
	};

	// Scalar Ops

	template <typename T>
	inline TVector3<T> TVector3<T>::operator+(const T& rhs) const
	{
		return TVector3<T>(x + rhs, y + rhs, z + rhs);
	}
	template <typename T>
	inline TVector3<T> TVector3<T>::operator-(const T& rhs) const
	{
		return TVector3<T>(x - rhs, y - rhs, z - rhs);
	}
	template <typename T>
	inline TVector3<T> TVector3<T>::operator*(const T& rhs) const
	{
		return TVector3<T>(x * rhs, y * rhs, z * rhs);
	}
	template <typename T>
	inline TVector3<T> TVector3<T>::operator/(const T& rhs) const
	{
		return TVector3<T>(x / rhs, y / rhs, z / rhs);
	}
	template <typename T>
	inline TVector3<T>& TVector3<T>::operator+=(const T& rhs)
	{
		x += rhs; y += rhs; z += rhs;
		return *this;
	}
	template <typename T>
	inline TVector3<T>& TVector3<T>::operator-=(const T& rhs)
	{
		x -= rhs; y -= rhs; z -= rhs;
		return *this;
	}
	template <typename T>
	inline TVector3<T>& TVector3<T>::operator*=(const T& rhs)
	{
		x *= rhs; y *= rhs; z *= rhs;
		return *this;
	}
	template <typename T>
	inline TVector3<T>& TVector3<T>::operator/=(const T& rhs)
	{
		x /= rhs; y /= rhs; z /= rhs;
		return *this;
	}

	// TVector3<T> Ops

	template <typename T>
	inline TVector3<T> TVector3<T>::operator+(const TVector3<T>& rhs) const
	{
		return TVector3<T>(x + rhs.x, y + rhs.y, z + rhs.z);
	}
	template <typename T>
	inline TVector3<T> TVector3<T>::operator-(const TVector3<T>& rhs) const
	{
		return TVector3<T>(x - rhs.x, y - rhs.y, z - rhs.z);
	}
	template <typename T>
	inline TVector3<T> TVector3<T>::operator*(const TVector3<T>& rhs) const
	{
		return TVector3<T>(x * rhs.x, y * rhs.y, z * rhs.z);
	}
	template <typename T>
	inline TVector3<T> TVector3<T>::operator/(const TVector3<T>& rhs) const
	{
		return TVector3<T>(x / rhs.x, y / rhs.y, z / rhs.z);
	}
	template <typename T>
	inline TVector3<T>& TVector3<T>::operator+=(const TVector3<T>& rhs)
	{
		x += rhs.x; y += rhs.y; z += rhs.z;
		return *this;
	}
	template <typename T>
	inline TVector3<T>& TVector3<T>::operator-=(const TVector3<T>& rhs)
	{
		x -= rhs.x; y -= rhs.y; z -= rhs.z;
		return *this;
	}
	template <typename T>
	inline TVector3<T>& TVector3<T>::operator*=(const TVector3<T>& rhs)
	{
		x *= rhs.x; y *= rhs.y; z *= rhs.z;
		return *this;
	}
	template <typename T>
	inline TVector3<T>& TVector3<T>::operator/=(const TVector3<T>& rhs)
	{
		x /= rhs.x; y /= rhs.y; z /= rhs.z;
		return *this;
	}
}