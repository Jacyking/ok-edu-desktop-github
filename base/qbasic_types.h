#ifndef QBASIC_TYPES_H
#define QBASIC_TYPES_H

#include <QObject>
#include <QString>
#include <QLatin1String>

#include "basic_types.h"

//using uchar = unsigned char; // Qt has uchar
using int8 = qint8;
using uint8 = quint8;

using int16 = qint16;
using uint16 = quint16;
using int32 = qint32;
using uint32 = quint32;
using int64 = qint64;
using uint64 = quint64;
using TimeMs = uint32;

#endif // QBASIC_TYPES_H
