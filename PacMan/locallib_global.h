#ifndef LOCALLIB_GLOBAL_H
#define LOCALLIB_GLOBAL_H

#include <QtCore/QtGlobal>

#if defined(COMPILE_LIBRARY)
#  define LOCALLIB_EXPORT Q_DECL_EXPORT
#else
#  define LOCALLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // LOCALLIB_GLOBAL_H
