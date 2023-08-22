#include "mainwindow.h"
#include "tradingstrategy.h"
#include "momentum_trading_strategy.h"
#include <vector>
#include "portfolio.h"
#include "broker.h"
#include "fstream"
#include "filesystem"
#include "iostream"

/**
 * @brief Creates login window.
 * @author Narges Haeri
 */

void MainWindow::loginPrompt(){

    //Setting Login button for authentication
    logInButt = new QPushButton("Log in", this);
    logInButt->setGeometry(1350, 13, 100, 38);
    logInButt->setStyleSheet("QPushButton{font-size: 20px;font-family: Arial;border:1px solid rgb(181, 141, 38); background-color:none; border-radius: 5%; color:rgb(38,56,76);}");

    //Defining signal and slot for opening login window
    //connect(logInButt, SIGNAL(clicked()), &w , SLOT(show()));
    connect(logInButt, SIGNAL(clicked()), &auth , SLOT(show()));

    while (!this->loggedIn){
        auth.exec();
        if(auth.loggedin()){
            this->loggedIn = true;
        }
    }

}

/**
 * @brief Creates strategy labels.
 * @author Narges Haeri
 */

void MainWindow::createStrategyLabels(){

    //Defining title for portfolio section
    Portfolio1Label = new QLabel("Portfolio 1", this);
    Portfolio1Label->setGeometry(60, 80, 125, 33);
    Portfolio1Label->setStyleSheet("QLabel{font-size: 29px;font-family: Arial;color: rgb(38,56,76);}");

    //trading strategy 1 label
    QString strategy_type1 = QString::fromStdString(this->strategy1->getName());
    QString ticker1 = QString::fromStdString(this->strategy1->getTicker());
    QString text1 = strategy_type1 + " (" + ticker1 + ")";

    Strategy1Label = new QLabel(text1, this);
    Strategy1Label->setGeometry(60, 130, 305, 33);
    Strategy1Label->setStyleSheet("QLabel{font-size: 19px;font-family: Arial;color: rgb(38,56,76);}");

    //button for turning on trading strategy 1
    strategy1Butt = new QPushButton("TURN OFF", this);
    strategy1Butt->setGeometry(340, 130, 90, 33);
    strategy1Butt->setStyleSheet("QPushButton{font-size: 14px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);border-radius: 5%;}");

    //changing button (text indicating that this stratedy is on or off)
    connect(strategy1Butt, SIGNAL(clicked()), this, SLOT(turnOnstrategy1()));

    //trading strategy 2 label
    QString strategy_type2 = QString::fromStdString(this->strategy2->getName());
    QString ticker2 = QString::fromStdString(this->strategy2->getTicker());
    QString text2 = strategy_type2 + " (" + ticker2 + ")";

    Strategy2Label = new QLabel(text2, this);
    Strategy2Label->setGeometry(60, 180, 305, 33);
    Strategy2Label->setStyleSheet("QLabel{font-size: 19px;font-family: Arial;color: rgb(38,56,76);}");

    //button for turning on trading strategy 2
    strategy2Butt = new QPushButton("TURN OFF", this);
    strategy2Butt->setGeometry(340, 180, 90, 33);
    strategy2Butt->setStyleSheet("QPushButton{font-size: 14px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);border-radius: 5%;}");

    //changing button (text indicating that this strategy is on or off)
    connect(strategy2Butt, SIGNAL(clicked()), this, SLOT(turnOnStrategy2()));

    //trading strategy 3 label
    QString strategy_type3 = QString::fromStdString(this->strategy3->getName());
    QString ticker3 = QString::fromStdString(this->strategy3->getTicker());
    QString text3 = strategy_type3 + " (" + ticker3 + ")";

    Strategy3Label = new QLabel(text3, this);
    Strategy3Label->setGeometry(60, 230, 305, 33);
    Strategy3Label->setStyleSheet("QLabel{font-size: 19px;font-family: Arial;color: rgb(38,56,76);}");

    //button for turning on trading strategy 3
    strategy3Butt = new QPushButton("TURN OFF", this);
    strategy3Butt->setGeometry(340, 230, 90, 33);
    strategy3Butt->setStyleSheet("QPushButton{font-size: 14px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);border-radius: 5%;}");

    //changing button (text indicating that this strategy is on or off)
    connect(strategy3Butt, SIGNAL(clicked()), this, SLOT(turnOnStrategy3()));

}

/**
 * @brief Creates statistics labels.
 * @author Narges Haeri
 */
void MainWindow::createStatisticsLabels(){

    //This section reports statistics related to specific trading strategy
    statisticsLabel = new QLabel("Statistics", this);
    statisticsLabel->setGeometry(60, 290, 105, 33);
    statisticsLabel->setStyleSheet("QLabel{font-size: 25px;font-family: Arial;color: rgb(38,56,76);border-bottom: 1px solid orange;}");

    //reporting Sotino ration
    sortinoLabel = new QLabel("Sortino Ratio:", this);
    sortinoLabel->setGeometry(60, 340, 155, 33);
    sortinoLabel->setStyleSheet("QLabel{font-size: 19px;font-family: Arial;color: rgb(38,56,76);border: none; border: none;}");

    sortinoRatio = new QLineEdit(this);
    sortinoRatio->setReadOnly(true);
    sortinoRatio->setText("0");
    sortinoRatio->setGeometry(200, 340, 90, 33);
    sortinoRatio->setStyleSheet("QLineEdit{font-size: 20px;font-family: Arial;color: rgb(38,56,76);border-radius: 2%;border: 1px solid rgba(181, 141, 38, 0.733);}");

    //reporting sharp ratio
    sharpeRatioLabel = new QLabel("Sharp Ratio:", this);
    sharpeRatioLabel->setGeometry(60, 390, 155, 33);
    sharpeRatioLabel->setStyleSheet("QLabel{font-size: 19px;font-family: Arial;color: rgb(38,56,76);border: none; border: none;}");

    sharpeRatio = new QLineEdit(this);
    sharpeRatio->setReadOnly(true);
    sharpeRatio->setText("0");
    sharpeRatio->setGeometry(200, 390, 90, 33);
    sharpeRatio->setStyleSheet("QLineEdit{font-size: 20px;font-family: Arial;color: rgb(38,56,76);border-radius: 2%;border: 1px solid rgba(181, 141, 38, 0.733);}");

    //reporting max drawdown

    DrawdownLabel = new QLabel("Max Drawdown:", this);
    DrawdownLabel->setGeometry(320, 390, 170, 33);
    DrawdownLabel->setStyleSheet("QLabel{font-size: 19px;font-family: Arial;color: rgb(38,56,76);}");

    maxDrawdown = new QLineEdit(this);
    maxDrawdown->setReadOnly(true);
    maxDrawdown->setText("0");
    maxDrawdown->setGeometry(510, 390, 90, 33);
    maxDrawdown->setStyleSheet("QLineEdit{font-size: 20px;font-family: Arial;color: rgb(38,56,76);border-radius: 2%;border: 1px solid rgba(181, 141, 38, 0.733);}");

}

/**
 * @brief Creates historical trades table.
 * @author Narges Haeri
 */

void MainWindow::createHistoricalTradesTable(){

    tradeLabel = new QLabel("Trading History", this);
    tradeLabel->setGeometry(60, 443, 155, 33);
    tradeLabel->setStyleSheet("QLabel{font-size: 22px;font-family: Arial;color: rgb(38,56,76);border: none; border: none;}");

    //Reporting trades that has been done as a table (trade history)
    tradeHistoryTable = new QTableWidget(this);
    tradeHistoryTable->setGeometry(60, 490, 680, 210);
    tradeHistoryTable->setRowCount((int)(tradeHistory.size()));
    tradeHistoryTable->setColumnCount(6);
    tradeHistoryTable->setStyleSheet("QTableWidget{font-size: 17px;font-family: Arial;color: rgb(38,56,76);background-color: rgb(240, 240, 240); none; border: 1px solid rgba(181, 141, 38, 0.733);}");

    //setting trade history column title
    tradeHistoryTable->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("%1").arg("Ticker")));
    tradeHistoryTable->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("%1").arg("Share Num")));
    tradeHistoryTable->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("%1").arg("Action")));
    tradeHistoryTable->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("%1").arg("Price")));
    tradeHistoryTable->setHorizontalHeaderItem(4, new QTableWidgetItem(tr("%1").arg("Order Type")));
    tradeHistoryTable->setHorizontalHeaderItem(5, new QTableWidgetItem(tr("%1").arg("Datetime")));
    tradeHistoryTable->setColumnWidth(4, 90);
    tradeHistoryTable->setColumnWidth(5, 190);
}

/**
 * @brief Creates closed positons table.
 * @author Hamid Zargar
 */

void MainWindow::createClosedPositionsTable(){

    closedLabel = new QLabel("Closed Positions", this);
    closedLabel->setGeometry(770, 653, 175, 33);
    closedLabel->setStyleSheet("QLabel{font-size: 22px;font-family: Arial;color: rgb(38,56,76);border: none; border: none;}");

    //Reporting trades that has been done as a table (trade history)
    closedPositionsTable = new QTableWidget(this);
    closedPositionsTable->setGeometry(770, 710, 680, 210);
    closedPositionsTable->setRowCount((int)(closedPositions.size()));
    closedPositionsTable->setColumnCount(7);
    closedPositionsTable->setStyleSheet("QTableWidget{font-size: 17px;font-family: Arial;color: rgb(38,56,76);background-color: rgb(240, 240, 240); none; border: 1px solid rgba(181, 141, 38, 0.733);}");

    //setting closed positions column title
    closedPositionsTable->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("%1").arg("Ticker")));
    closedPositionsTable->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("%1").arg("Share Num")));
    closedPositionsTable->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("%1").arg("Action")));
    closedPositionsTable->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("%1").arg("Price")));
    closedPositionsTable->setHorizontalHeaderItem(4, new QTableWidgetItem(tr("%1").arg("Order Type")));
    closedPositionsTable->setHorizontalHeaderItem(5, new QTableWidgetItem(tr("%1").arg("Pnl")));
    closedPositionsTable->setHorizontalHeaderItem(6, new QTableWidgetItem(tr("%1").arg("Return (%)")));
    closedPositionsTable->setColumnWidth(5, 80);
    closedPositionsTable->setColumnWidth(6, 100);
}

/**
 * @brief Creates open positions table.
 * @author Narges Haeri
 */

void MainWindow::createOpenPositionsTable(){

    openPositionLabel = new QLabel("Open Positions", this);
    openPositionLabel->setGeometry(770, 383, 155, 33);
    openPositionLabel->setStyleSheet("QLabel{font-size: 22px;font-family: Arial;color: rgb(38,56,76);border: none; border: none;}");

    //Reporting open positions as table
    openPositionsTable = new QTableWidget(this);
    openPositionsTable->setGeometry(770, 430, 680, 210);
    openPositionsTable->setRowCount((int)(tradeHistory.size()));
    openPositionsTable->setColumnCount(5);

    //setting open position table column title
    openPositionsTable->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("%1").arg("Ticker")));
    openPositionsTable->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("%1").arg("Share Num")));
    openPositionsTable->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("%1").arg("Action")));
    openPositionsTable->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("%1").arg("Price")));
    openPositionsTable->setHorizontalHeaderItem(4, new QTableWidgetItem(tr("%1").arg("Order Type")));
    openPositionsTable->setStyleSheet("QTableWidget{font-size: 17px;font-family: Arial;color: rgb(38,56,76);background-color: rgb(240, 240, 240); none; border: 1px solid rgba(181, 141, 38, 0.733);}");

}

/**
 * @brief Creates export data feature.
 * @author Narges Haeri
 */

void MainWindow::createExportDataFeature(){

    //This section is to request exporting data
    exportLabel = new QLabel("Export Data", this);
    exportLabel->setGeometry(60, 740, 125, 33);
    exportLabel->setStyleSheet("QLabel{font-size: 24px;font-family: Arial;color: rgb(38,56,76);border-bottom: 1px solid orange;}");

    startdateLabel = new QLabel("Start Date (YYYY-MM-DD)", this);
    startdateLabel->setGeometry(60, 790, 255, 33);
    startdateLabel->setStyleSheet("QLabel{font-size: 20px;font-family: Arial;color: rgb(38,56,76);}");

    startdateField = new QLineEdit(this);                          //defining the widget where the user can enter the input
    startdateField->setAlignment(Qt::AlignLeft);
    startdateField->setGeometry(340, 790, 125, 33);
    startdateField->setStyleSheet("QLineEdit{font-size: 17px;font-family: Arial;color: rgb(38,56,76);border-radius: 2%;border: 1px solid rgba(181, 141, 38, 0.733);}");

    enddateLabel = new QLabel("End Date (YYYY-MM-DD)", this);
    enddateLabel->setGeometry(60, 840, 255, 33);
    enddateLabel->setStyleSheet("QLabel{font-size: 20px;font-family: Arial;color: rgb(38,56,76);}");

    enddateField = new QLineEdit(this);                          //defining the widget where the user can enter the input
    enddateField->setAlignment(Qt::AlignLeft);
    enddateField->setGeometry(340, 840, 125, 33);
    enddateField->setStyleSheet("QLineEdit{font-size: 17px;font-family: Arial;color: rgb(38,56,76);border-radius: 2%;border: 1px solid rgba(181, 141, 38, 0.733);}");

    tickerLabel = new QLabel("Ticker Symbol", this);
    tickerLabel->setGeometry(60, 890, 255, 33);
    tickerLabel->setStyleSheet("QLabel{font-size: 20px;font-family: Arial;color: rgb(38,56,76);}");

    tickerField = new QLineEdit(this);                          //defining the widget where the user can enter the input
    tickerField->setAlignment(Qt::AlignLeft);
    tickerField->setGeometry(340, 890, 125, 33);
    tickerField->setStyleSheet("QLineEdit{font-size: 20px;font-family: Arial;color: rgb(38,56,76);border-radius: 2%;border: 1px solid rgba(181, 141, 38, 0.733);}");

    //button for turning on trading strategy 1
    exportSubmitButton = new QPushButton("Submit", this);
    exportSubmitButton->setGeometry(500, 890, 90, 33);
    exportSubmitButton->setStyleSheet("QPushButton{font-size: 14px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);border-radius: 5%;}");

    connect(exportSubmitButton, SIGNAL(clicked()), this, SLOT(exportData()));

}

/**
 * @brief Creates export historical trades as csv feature.
 * @author Hamid Zargar
 */
void MainWindow::createExportTradeHistoryFeature(){

    //button for turning on trading strategy 1
    exportAsCSV1 = new QPushButton("Export as CSV", this);
    exportAsCSV1->setGeometry(245, 448, 110, 25);
    exportAsCSV1->setStyleSheet("QPushButton{font-size: 14px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);border-radius: 5%;}");

    connect(exportAsCSV1, SIGNAL(clicked()), this, SLOT(exportTradeHistory()));

}

/**
 * @brief Creates export closed positions as csv feature.
 * @author Hamid Zargar
 */
void MainWindow::createExportClosedPositionsFeature(){

    //button for turning on trading strategy 1
    exportAsCSV2 = new QPushButton("Export as CSV", this);
    exportAsCSV2->setGeometry(955, 658, 110, 25);
    exportAsCSV2->setStyleSheet("QPushButton{font-size: 14px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);border-radius: 5%;}");

    connect(exportAsCSV2, SIGNAL(clicked()), this, SLOT(exportClosedPositions()));

}

/**
 * @brief Creates main window UI labels.
 * @author Narges Haeri
 */
void MainWindow::createMainWindowLabels(){

    //setting mainwindow
    MainWindow::setWindowTitle("Main Window");
    MainWindow::resize(1505, 980);
    MainWindow::setStyleSheet("QMainWindow{background-color: #fff;}");

    //adding the separating line at the top of the window
    line = new QFrame(this);
    line->setGeometry(0, 0, 1905, 20);
    line->setFrameShape(QFrame::HLine);
    line->setStyleSheet("QFrame{border-color: rgb(181, 141, 38); font-size: 3; margin-bottom: 5px;}");

    //adding another separating line at the top of the window
    line1 = new QFrame(this);
    line1->setGeometry(6, 49, 1905, 20);
    line1->setFrameShape(QFrame::HLine);
    line1->setStyleSheet("QFrame{border-color: rgba(181, 141, 38, 0.733); font-size: 3; margin-bottom: 5px;}");

    //Setting logo of application
    Brand = new QLineEdit(this);
    Brand->setReadOnly(true);
    Brand->setText("Trading Strategy Application");
    Brand->setGeometry(20, 12, 460, 38);
    Brand->setStyleSheet("QLineEdit{font-size: 28px;font-family: Arial;color: rgba(181, 141, 38, 0.733);border: none; font-weight: bold;}");

}

/**
 * @brief Creates strategy objects and adds them to the portfolio and starts them.
 * @author Hamid Zargar
 */
void MainWindow::addStrategiesToPortfolioAndStart(){

    this->strategy1 = new MomentumTradingStrategy("AAPL", 1);
    this->strategy2 = new RegressionTradingStrategy("AMD", 2);
    this->strategy3 = new MomentumTradingStrategy("INTC", 3);

    this->portfolio.addStrategy(this->strategy1);
    this->portfolio.addStrategy(this->strategy2);
    this->portfolio.addStrategy(this->strategy3);
    this->portfolio.startAllStrategies();

}

/**
 * @brief Strategies in portoflio analyze conditions and execute trades if conditons are met.
 * @author Hamid Zargar
 */

void MainWindow::analyzeAllStrategies() {
    this->portfolio.analyzeAll();
}

/**
 * @brief Export daily historical data feature for a ticker.
 * @author Hamid Zargar
 */

void MainWindow::exportData(){

    if (tickerField->text().toStdString().empty() ||
            startdateField->text().toStdString().empty() ||
            enddateField->text().toStdString().empty()){

        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setText("Error occurred. Please ensure no fields are empty and data fileds are in the correct format.");
        msgBox->exec();
    }
    else{
        try {
            priceFetcher.downloadHistoricalCSV(tickerField->text().toStdString(), startdateField->text().toStdString(), enddateField->text().toStdString(), "1d", "AAPL.csv");
        }  catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}


/**
 * @brief Starts/turns off strategy 1.
 * @author Narges Haeri
 */

//This slot turns on requred functionalities for strategy1 and changes the related buttom from off to on indicating which strategy
//we are using for analysing our trades.
void MainWindow::turnOnstrategy1(){
    if(!portfolio.isStrategyActive(1)){
        portfolio.startStrategy(1);
        strategy1Butt->setText("TURN OFF");
    }else{
        portfolio.stopStrategy(1);
        strategy1Butt->setText("TURN ON");
    }
}

/**
 * @brief Starts/turns off strategy 2.
 * @author Narges Haeri
 */
//This slot turns on requred functionalities for strategy2 and changes the related buttom from off to on indicating which strategy
//we are using for analysing our trades.
void MainWindow::turnOnStrategy2(){
    if(!portfolio.isStrategyActive(2)){
        portfolio.startStrategy(2);
        strategy2Butt->setText("TURN OFF");
    }else{
        portfolio.stopStrategy(2);
        strategy2Butt->setText("TURN ON");
    }
}

/**
 * @brief Starts/turns off strategy 3.
 * @author Narges Haeri
 */

//This slot turns on requred functionalities for strategy3 and changes the related buttom from off to on indicating which strategy
//we are using for analysing our trades.
void MainWindow::turnOnStrategy3(){
    if(!portfolio.isStrategyActive(3)){
        portfolio.startStrategy(3);
        strategy3Butt->setText("TURN OFF");
    }else{
        portfolio.stopStrategy(3);
        strategy3Butt->setText("TURN ON");
    }
}

/**
 * @brief Updates the historical trades table with new entries.
 * @author Narges Haeri
 */
//This slot will update the trade history table
void MainWindow::updateHistoryTable(){

    tradeHistory = this->broker->getTradeHistory();

    int row_count = (int)(tradeHistoryTable->rowCount());                         //counting number of rows in the table

    if (tradeHistory.size() > row_count) {

        for (int i = row_count; i < tradeHistory.size(); i++) {
            //we will add all trades information that has been added during the past 5 min to our table

            tradeHistoryTable->insertRow(i);                                  //adding new row to table by calling slot insertRow

            ticker = tradeHistory[i].first.getTicker();
            newItem = new QTableWidgetItem(tr("%1").arg(QString::fromStdString(ticker)));
            tradeHistoryTable->setItem(i, 0, newItem);

            num_shares = tradeHistory[i].first.getNumShares();
            newItem = new QTableWidgetItem(tr("%1").arg(num_shares));
            tradeHistoryTable->setItem(i, 1, newItem);

            action = tradeHistory[i].first.getAction();

            if (action == 1){
                newItem = new QTableWidgetItem(tr("%1").arg(QString::fromStdString("BUY")));
                tradeHistoryTable->setItem(i, 2, newItem);
            }
            else{
                newItem = new QTableWidgetItem(tr("%1").arg(QString::fromStdString("SELL")));
                tradeHistoryTable->setItem(i, 2, newItem);
            }


            price = tradeHistory[i].first.getPrice();
            newItem = new QTableWidgetItem(tr("%1").arg(price));
            tradeHistoryTable->setItem(i, 3, newItem);

            order_type = tradeHistory[i].first.getOrderType();
            newItem = new QTableWidgetItem(tr("%1").arg(QString::fromStdString(order_type)));
            tradeHistoryTable->setItem(i, 4, newItem);

            datetime = tradeHistory[i].second;
            newItem = new QTableWidgetItem(tr("%1").arg(QString::fromStdString(datetime)));
            tradeHistoryTable->setItem(i, 5, newItem);
        }
    }
}

/**
 * @brief Updates the open positions table with new entries.
 * @author Narges Haeri
 */
//This slot will update the opening position table
void MainWindow::updateOpenPositionTable(){

    openPositions = this->broker->getOpenPositions();

    int row_count = (int)(openPositionsTable->rowCount());//counting number of rows in the table

    for (int i = 0; i < openPositions.size(); i++){          //we will add all positions information that has been added during the past 5 min to our table

        // Inserts new row if we have a new entry, otherwise updates old positions
        if (i > row_count-1){
            openPositionsTable->insertRow(i);
        }
                                  //adding new row to table by calling slot insertRow
        ticker = openPositions[i].getTicker();
        newItem = new QTableWidgetItem(tr("%1").arg(QString::fromStdString(ticker)));
        openPositionsTable->setItem(i, 0, newItem);

        num_shares = openPositions[i].getNumShares();
        newItem = new QTableWidgetItem(tr("%1").arg(num_shares));
        openPositionsTable->setItem(i, 1, newItem);


        action = openPositions[i].getAction();

        if (action == 1){
            newItem = new QTableWidgetItem(tr("%1").arg(QString::fromStdString("BUY")));
            openPositionsTable->setItem(i, 2, newItem);
        }
        else{
            newItem = new QTableWidgetItem(tr("%1").arg(QString::fromStdString("SELL")));
            openPositionsTable->setItem(i, 2, newItem);
        }


        price = openPositions[i].getPrice();
        newItem = new QTableWidgetItem(tr("%1").arg(price));
        openPositionsTable->setItem(i, 3, newItem);

        order_type = openPositions[i].getOrderType();
        newItem = new QTableWidgetItem(tr("%1").arg(QString::fromStdString(order_type)));
        openPositionsTable->setItem(i, 4, newItem);
    }
}

/**
 * @brief Updates the statistics of the portfolio.
 * @author Hamid Zargar
 */

void MainWindow::updateStatistics() {

    this->sortinoRatio->setText(QString::fromStdString(std::to_string(this->broker->getSortinoRatio())));
    this->sharpeRatio->setText(QString::fromStdString(std::to_string(this->broker->getSharpeRatio())));
    this->maxDrawdown->setText(QString::fromStdString(std::to_string(this->broker->getMaxDrawdown())));

}

/**
 * @brief Updates the closed positions.
 * @author Hamid Zargar
 */

//This slot will update the trade history table
void MainWindow::updateClosedPositionsTable(){

    closedPositions = this->broker->getClosedPositions();

    int row_count = (int)(closedPositionsTable->rowCount());                         //counting number of rows in the table

    if (closedPositions.size() > row_count) {

        for (int i = row_count; i < closedPositions.size(); i++) {
            //we will add all trades information that has been added during the past 5 min to our table

            closedPositionsTable->insertRow(i);                                  //adding new row to table by calling slot insertRow

            Trade trade = std::get<0>(closedPositions[i]);
            pnl = std::get<1>(closedPositions[i]);
            ret = std::get<2>(closedPositions[i]);

            ticker = trade.getTicker();
            newItem = new QTableWidgetItem(tr("%1").arg(QString::fromStdString(ticker)));
            closedPositionsTable->setItem(i, 0, newItem);

            num_shares = trade.getNumShares();
            newItem = new QTableWidgetItem(tr("%1").arg(num_shares));
            closedPositionsTable->setItem(i, 1, newItem);

            action = trade.getAction();

            if (action == 1){
                newItem = new QTableWidgetItem(tr("%1").arg(QString::fromStdString("BUY")));
                closedPositionsTable->setItem(i, 2, newItem);
            }
            // action is -1
            else{
                newItem = new QTableWidgetItem(tr("%1").arg(QString::fromStdString("SELL")));
                closedPositionsTable->setItem(i, 2, newItem);
            }

            price = trade.getPrice();
            newItem = new QTableWidgetItem(tr("%1").arg(price));
            closedPositionsTable->setItem(i, 3, newItem);

            order_type = trade.getOrderType();
            newItem = new QTableWidgetItem(tr("%1").arg(QString::fromStdString(order_type)));
            closedPositionsTable->setItem(i, 4, newItem);

            newItem = new QTableWidgetItem(tr("%1").arg(pnl));
            closedPositionsTable->setItem(i, 5, newItem);

            newItem = new QTableWidgetItem(tr("%1").arg(ret));
            closedPositionsTable->setItem(i, 6, newItem);
        }
    }
}

/**
 * @brief Export trade history.
 * @author Hamid Zargar
 */

void MainWindow::exportTradeHistory(){

    std::vector<std::pair<Trade, std::string>> trades = this->broker->getTradeHistory();

    std::ofstream output;
    // Current directory is cmake-build-debug so we want to save in parent directory which is trading system
    output.open("../trade_history.csv");

    output << "Ticker,Shares,Action,Price,OrderType,DateTime" << std::endl;

    for (auto it = trades.begin(); it != trades.end(); ++it) {

        std::string action_str;

        if (it->first.getAction() == 1){
            action_str = "BUY";
        }
        else{
            action_str = "SELL";
        }

        output << it->first.getTicker()<< ","
                << it->first.getNumShares()<< ","
                << action_str<< ","
                << it->first.getPrice()<< ","
                << it->first.getOrderType()<< ","
                << it->second<< std::endl;
    }

    output.close();
}

/**
 * @brief Export closed positions.
 * @author Hamid Zargar
 */

void MainWindow::exportClosedPositions(){

    std::vector<std::tuple<Trade,float, float>> closed_positions = this->broker->getClosedPositions();

    std::ofstream output;
    // Current directory is cmake-build-debug so we want to save in parent directory which is trading system
    output.open("../closed_positions.csv");

    output << "Ticker,Shares,Action,Price,OrderType,PnL,Return(%)" << std::endl;

    for (auto it = closed_positions.begin(); it != closed_positions.end(); ++it) {

        std::string action_str;

        if (std::get<0>(*it).getAction() == 1){
            action_str = "BUY";
        }
        else{
            action_str = "SELL";
        }

        output << std::get<0>(*it).getTicker()<< ","
               << std::get<0>(*it).getNumShares()<< ","
               << action_str<< ","
               << std::get<0>(*it).getPrice()<< ","
               << std::get<0>(*it).getOrderType()<< ","
               << std::get<1>(*it)<< ","
               << std::get<2>(*it)<< std::endl;
    }

    output.close();
}


/**
 * @brief Updates the portfolio balance chart over time.
 * @author Andrew Raycroft
 */

void MainWindow::updateChart(){

    totalEquity->append(this->old_x, this->broker->getTotalEquity());
    cashBalance->append(this->old_x, this->broker->getCashBalance());
    stockPosition->append(this->old_x, this->broker->getStockPosition());

    this->chart->removeSeries(totalEquity);
    this->chart->addSeries(totalEquity);
    this->chart->removeSeries(cashBalance);
    this->chart->addSeries(cashBalance);
    this->chart->removeSeries(stockPosition);
    this->chart->addSeries(stockPosition);

    this->old_x++;

}

/**
 * @brief Creates a chart that shows the portoflio balances over time.
 * @author Andrew Raycroft
 */

void MainWindow::createChart(){

    chart = new QChart();
    chart->setGeometry(400, 100, 125, 33);

    totalEquity = new QLineSeries();
    totalEquity->setName("Total Equity");

    cashBalance = new QLineSeries();
    cashBalance->setName("Cash Balance");

    stockPosition = new QLineSeries();
    stockPosition->setName("Stock Position");

    chart->addSeries(totalEquity);
    chart->addSeries(cashBalance);
    chart->addSeries(stockPosition);

    // Set axises
    axisX = new QValueAxis;
    axisY = new QValueAxis;

    axisY->setRange(-200000, 200000);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    chart->setTitle("Balances\n""(Balance over Time)");

    // Generate chart view
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(this);
    chartView->setGeometry(770, 60, 680, 300);
    chartView->show();

}


/**
 * @brief Creates all main window and UI elements and periodically calls the functions to update our table elements.
 * @author Hamid Zargar
 */

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{

    this->loginPrompt();
    this->addStrategiesToPortfolioAndStart();
    this->createMainWindowLabels();
    this->createStrategyLabels();
    this->createStatisticsLabels();
    this->createHistoricalTradesTable();
    this->createClosedPositionsTable();
    this->createOpenPositionsTable();
    this->createExportDataFeature();
    this->createExportTradeHistoryFeature();
    this->createExportClosedPositionsFeature();

    this->createChart();



    // Dummy trades to show that closed positions table works
    Trade trade("AAPL", 50, -1, 141.54, 1);
    Trade trade2("AMD", 50, 1, 150.01, 2);
    Trade trade3("AMD", 70, -1, 165.33, 2);
    Trade trade4("AMD", 120, 1, 145.36, 2);
    Trade trade5("AAPL", 70, 1, 148.72, 1);
    Trade trade6("AAPL", 30, -1, 144.72, 1);

    this->broker->execute(trade);
    this->broker->execute(trade2);
    this->broker->execute(trade3);
    this->broker->execute(trade4);
    this->broker->execute(trade5);
    this->broker->execute(trade6);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(analyzeAllStrategies()));
    timer->start(5000);

    QTimer *timer1 = new QTimer(this);
    connect(timer1, SIGNAL(timeout()), this, SLOT(updateHistoryTable()));
    timer1->start(5000);

    QTimer *timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(updateOpenPositionTable()));
    timer2->start(5000);

    QTimer *timer3 = new QTimer(this);
    connect(timer3, SIGNAL(timeout()), this, SLOT(updateStatistics()));
    timer3->start(5000);

    QTimer *timer4 = new QTimer(this);
    connect(timer4, SIGNAL(timeout()), this, SLOT(updateClosedPositionsTable()));
    timer4->start(5000);

    QTimer *timer5 = new QTimer(this);
    connect(timer5, SIGNAL(timeout()), this, SLOT(updateChart()));
    timer5->start(5000);

}

/**
 * @brief Destructor for main window
 * @author Narges Haeri
 */

MainWindow::~MainWindow(){}
