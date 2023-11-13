#ifndef PACMANLIB_GLOBAL_H
#define PACMANLIB_GLOBAL_H

#include <QtCore/QtGlobal>

#if defined(COMPILE_LIBRARY)
#  define PACMANLIB_EXPORT Q_DECL_EXPORT
#else
#  define PACMANLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // PACMANLIB_GLOBAL_H
