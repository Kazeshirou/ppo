#ifndef SIGNS_GLOBAL_H
#define SIGNS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SIGNS_LIBRARY)
#  define SIGNSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SIGNSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SIGNS_GLOBAL_H
