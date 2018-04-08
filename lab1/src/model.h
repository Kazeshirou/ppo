#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "georoute.h"

class Model
{
    Q_OBJECT

public:
    explicit Model(const QString &filename);

protected:
    QList<GeoRoute> m_routes;
    GeoRoute *curroute;
    QString *polyline;
};

#endif // MODEL_H
