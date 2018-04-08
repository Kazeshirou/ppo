#include <QApplication>
#include <QTest>

#include "testgpxparser.h"
#include "testcoder.h"

using namespace std;

int main()
{
    //freopen("testing.log", "w", stdout);
    QTest::qExec(new TestGPXParser);
    QTest::qExec(new TestCoder);
    return 0;
}
