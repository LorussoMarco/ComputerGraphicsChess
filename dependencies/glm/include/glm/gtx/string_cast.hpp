/// @ref gtx_string_cast
/// @file glm/gtx/string_cast.hpp
///
/// @see core (dependence)
/// @see gtx_integer (dependence)
/// @see gtx_quaternion (dependence)
///
/// @defgroup gtx_string_cast GLM_GTX_string_cast
/// @ingroup gtx
///
/// Include <glm/gtx/string_cast.hpp> to use the features of this extension.
///
/// Setup strings for GLM type values

#pragma once

// Dependency:
#include "../glm.hpp"
#include "../gtc/type_precision.hpp"
#include "../gtc/quaternion.hpp"
#include "../gtx/dual_quaternion.hpp"
#include <string>
#include <cmath>
#include <cstring>

#ifndef GLM_ENABLE_EXPERIMENTAL
#elif GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_GTX_string_cast extension included")
#endif

namespace glm
{
	/// @addtogroup gtx_string_cast
	/// @{

	/// Create a string from a GLM vector or matrix typed variable.
	/// @see gtx_string_cast extension.
	template<typename genType>
	GLM_FUNC_DECL std::string to_string(genType const& x);

	/// @}
}//namespace glm

#include "string_cast.inl"
