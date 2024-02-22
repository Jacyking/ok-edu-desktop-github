#include "qobject.h"
#include "qobjectdefs.h"
#include <iostream>

class ApplicationTest : public QObject {
  Q_OBJECT
public:
  void init();
};

void ApplicationTest::init() { std::cout << "init..." << std::endl; }

// QTEST_GUILESS_MAIN(ApplicationTest);
#include "application_test.moc";