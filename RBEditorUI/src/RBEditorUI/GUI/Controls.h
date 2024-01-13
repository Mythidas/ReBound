#pragma once

#include "RBEngine/Math/Vector.h"
#include <vector>

namespace RB::Editor
{
	class Controls
	{
	public:
		static void Text(const std::string& label, std::string& value);
		static void Checkbox(const std::string& label, bool& checked);
		static void ButtonCombo(const std::string& label, int& index, std::vector<const char*> values);
		static void ButtonComboFiltered(const std::string& label, int& index, std::vector<const char*> values, const char* filter);

		static void Vector3(const std::string& label, Vector3& vex3);

	private:
		static void _DrawLabel(const std::string& label);
		static void _SetPadding(float padding = 0);
	};
}