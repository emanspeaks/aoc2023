#pragma once

#define CAT(a, b) a##b

#include "utf8.h"
#include "strings.h"
#include "debug.h"
#include "aocgrid.h"
#include "timing.h"
#include "a_star.h"

template <typename T>
const T inf = std::numeric_limits<T>::max();
