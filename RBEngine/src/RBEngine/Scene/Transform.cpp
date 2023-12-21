#include "rbpch.h"
#include "Transform.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>


namespace RB
{
	namespace Utils
	{
		static glm::quat GetOrientation(const Vector3& rotation)
		{
			return glm::quat(glm::radians(glm::vec3(-rotation.x, rotation.y, 0.0f)));
		}
	}

	Vector3 TransformComponent::Forward() const
	{
		return (glm::vec3)glm::rotate(Utils::GetOrientation(Rotation), (gVec3)Vector3::Forward);
	}
	Vector3 TransformComponent::Back() const
	{
		return (glm::vec3)glm::rotate(Utils::GetOrientation(Rotation), (gVec3)Vector3::Back);
	}
	Vector3 TransformComponent::Right() const
	{
		return (glm::vec3)glm::rotate(Utils::GetOrientation(Rotation), (gVec3)Vector3::Right);
	}
	Vector3 TransformComponent::Left() const
	{
		return (glm::vec3)glm::rotate(Utils::GetOrientation(Rotation), (gVec3)Vector3::Left);
	}
	Vector3 TransformComponent::Up() const
	{
		return (glm::vec3)glm::rotate(Utils::GetOrientation(Rotation), (gVec3)Vector3::Up);
	}
	Vector3 TransformComponent::Down() const
	{
		return (glm::vec3)glm::rotate(Utils::GetOrientation(Rotation), (gVec3)Vector3::Down);
	}
	Matrix4 TransformComponent::GetMatrix() const
	{
		return glm::translate(glm::mat4(1.0f), (gVec3)Position)
			* glm::scale(glm::mat4(1.0f), (gVec3)Scale);
	}
	Matrix4 TransformComponent::GetInverseMatrix() const
	{
		return glm::inverse(GetMatrix());
	}
}