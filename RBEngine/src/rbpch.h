#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include "RBEngine/Debug/Log.h"
#include "RBEngine/Debug/Timer.h"
#include "RBEngine/Debug/Assert.h"
#include "RBEngine/Debug/Result.h"
#include "RBEngine/Core/Defines.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <type_traits>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#ifdef RB_PLAT_WINDOWS
#include <Windows.h>
#endif