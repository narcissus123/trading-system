/**
 * @brief This file deals with running our entire application and creates the UI and window elements.
 * @author Narges Haeri
 */

#include "trade.h"
#include "tradingstrategy.h"
#include "momentum_trading_strategy.h"
#include "broker.h"
#include "mainwindow.h"
#include <QApplication>
#include <sys/types.h>
#include <QDebug>
#include "authentication.h"

int main(int argc, char **argv)
{

 QApplication app (argc, argv);


  MainWindow window;
  window.show();
  window.show();


 return app.exec();
}
