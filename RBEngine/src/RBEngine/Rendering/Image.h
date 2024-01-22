#pragma once

#include "RBEngine/Core/Defines.h"
#include "RBEngine/Utils/File.h"
#include "RBEngine/Math/Vector3.h"

namespace RB
{
	enum class ImageType
	{
		e1D,
		e2D,
		e3D
	};

	enum class ImageFormat
	{
		R8,
		RGBA8,
		RGBA32F
	};

	enum class ImageWrap
	{
		Repeat,
		ClampToEdge,
		MirroredRepeat
	};

	enum class ImageTiling
	{
		Linear,
		Nearest
	};

	class Image
	{
	public:
		struct Builder
		{
			uint32_t Binding{ 0 };
			ImageType Type{ ImageType::e2D };
			ImageFormat Format{ ImageFormat::RGBA8 };
			ImageWrap Wrap{ ImageWrap::Repeat };
			ImageTiling Tiling{ ImageTiling::Nearest };
			UVector3 Size{ 1, 1, 1 };

			Builder& setBinding(uint32_t binding) { Binding = binding; return *this; }
			Builder& setType(ImageType type) { Type = type; return *this; }
			Builder& setFormat(ImageFormat format) { Format = format; return *this; }
			Builder& setWrap(ImageWrap wrap) { Wrap = wrap; return *this; }
			Builder& setTiling(ImageTiling tiling) { Tiling = tiling; return *this; }
			Builder& setSize(UVector3 size) { Size = size; return *this; }
			Ref<Image> Build() const;
		};

		virtual void Bind(uint32_t slot) const = 0;
		virtual void SetData(void* data, size_t size) = 0;
		virtual void LoadData(const File& path) = 0;

		virtual UVector3 GetSize() const = 0;
		virtual void* GetRenderID() const = 0;

		bool Flipped{ false };
	};
}