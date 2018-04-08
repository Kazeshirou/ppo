#ifndef TESTCODER_H
#define TESTCODER_H

#include <QObject>

class TestCoder: public QObject
{
    Q_OBJECT

private slots:
    void encode();

    void decode();
};

#endif // TESTCODER_H
