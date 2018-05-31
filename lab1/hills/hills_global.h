#ifndef HILLS_GLOBAL_H
#define HILLS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HILLS_LIBRARY)
#  define HILLSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define HILLSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // HILLS_GLOBAL_H
