#pragma once

#ifdef VITAR_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
	#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Vitar/Core/Base.h"

#include "Vitar/Core/Log.h"

#include "Vitar/Debug/Instrumentor.h"


#ifdef VITAR_PLANTFORM_WINDOWS
	#include<Windows.h>
#endif // VITAR_PLANTFORM_WINDOWS
