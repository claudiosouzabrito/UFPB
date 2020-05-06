#ifndef INCLUDES_HPP
#define INCLUDES_HPP

// MAIN INCLUDER

#define GLEW_STATIC
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#if defined(__BORLANDC__)
typedef unsigned char uint8_t;
typedef __int64 int64_t;
typedef unsigned long uintptr_t;
#elif defined(_MSC_VER)
typedef unsigned char uint8_t;
typedef __int64 int64_t;
#else
#include <stdint.h>
#endif

#endif // INCLUDES_HPP3
