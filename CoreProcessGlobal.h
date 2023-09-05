#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(COREPROCESS_LIB)
#  define COREPROCESS_EXPORT Q_DECL_EXPORT
# else
#  define COREPROCESS_EXPORT Q_DECL_IMPORT
# endif
#else
# define COREPROCESS_EXPORT
#endif
