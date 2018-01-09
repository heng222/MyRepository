#ifndef ISCSMOCK_GLOBAL_H
#define ISCSMOCK_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef ISCSMOCK_LIB
# define ISCSMOCK_EXPORT Q_DECL_EXPORT
#else
# define ISCSMOCK_EXPORT Q_DECL_IMPORT
#endif

#endif // ISCSMOCK_GLOBAL_H
