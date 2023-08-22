/**
 * @brief This class creates our window and UI elements and connects them to our backend code
 * @author Narges Haeri, Hamid Zargar, Andrew Raycroft, Alaa AL
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tradingstrategy.h"
#include "momentum_trading_strategy.h"
#include "regression_trading_strategy.h"
#include "trade.h"
#include "broker.h"
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTimer>
#include <QMessageBox>
#include <QComboBox>
#include "authentication.h"
#include "portfolio.h"

#include "QtCharts/QChart"
#include <QtCharts/QLineSeries>
#include <QtCharts/QLegend>
#include <QList>
#include <QChartView>
#include <QtCharts/QValueAxis>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    Broker* broker = Broker::GetInstance();
    Portfolio portfolio;
    PriceFetcher priceFetcher;

    MainWindow *ui;
    std::vector<QString> openingOrdersList;
    std::vector<std::pair<Trade, std::string>> tradeHistory;
    std::vector<Trade> openPositions;
    std::vector<std::tuple<Trade,float, float>> closedPositions;
    int numberOfTrades;
    QTableWidget *tradeHistoryTable;
    QTableWidget *openPositionsTable;
    QTableWidget *closedPositionsTable;
    std::string ticker;
    int num_shares;
    int action;
    double price;
    float pnl;
    float ret;
    std::string datetime;
    std::string order_type;
    QTableWidgetItem *newItem;
    bool strategy1On = false;         //check if trading strategy 1 is on/off
    bool strategy2On = false;         //check if trading strategy 2 is on/off
    bool strategy3On = false;         //check if trading strategy 3 is on/off
    QPushButton *strategy1Butt;
    QPushButton *strategy2Butt;
    QPushButton *strategy3Butt;
    QLineEdit *startdateField;
    QLineEdit *enddateField;
    QLineEdit *tickerField;
    QPushButton *logInButt;
    bool loggedIn = false;
    Authentication auth;
    QString user;

    QLabel *Portfolio1Label;
    QLabel *Strategy1Label;
    QLabel *Strategy2Label;
    QLabel *Strategy3Label;
    QLabel *statisticsLabel;
    QLabel *sortinoLabel;
    QLineEdit *sortinoRatio;
    QLabel *sharpeRatioLabel;
    QLineEdit *sharpeRatio;
    QLabel *DrawdownLabel;
    QLineEdit *maxDrawdown;
    QLabel *tradeLabel;
    QLabel *closedLabel;
    QLabel *openPositionLabel;
    QLabel *exportLabel;
    QLabel *startdateLabel;
    QLabel *enddateLabel;
    QLabel *tickerLabel;
    QPushButton* exportSubmitButton;
    QPushButton* exportAsCSV1;
    QPushButton* exportAsCSV2;
    QFrame *line;
    QFrame *line1;
    QLineEdit *Brand;

    MomentumTradingStrategy* strategy1;
    RegressionTradingStrategy* strategy2;
    MomentumTradingStrategy* strategy3;

    QHeaderView* header;

    QChart* chart;
    QLineSeries *totalEquity;
    QLineSeries *cashBalance;
    QLineSeries *stockPosition;
    QChartView *chartView;
    QVBoxLayout* layout;
    QValueAxis *axisX;
    QValueAxis *axisY;

    int old_x = 0;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void newTradeAdded();
    void newPositionOpened();

private slots:

    void loginPrompt();
    void exportData();
    void updateHistoryTable();
    void updateOpenPositionTable();
    void updateClosedPositionsTable();
    void analyzeAllStrategies();
    void updateStatistics();

    void turnOnstrategy1();
    void turnOnStrategy2();
    void turnOnStrategy3();

    void createStrategyLabels();
    void createStatisticsLabels();
    void createHistoricalTradesTable();
    void createOpenPositionsTable();
    void createExportDataFeature();
    void createMainWindowLabels();
    void createClosedPositionsTable();

    void addStrategiesToPortfolioAndStart();
    void exportTradeHistory();
    void createExportTradeHistoryFeature();
    void createExportClosedPositionsFeature();
    void exportClosedPositions();

    void createChart();
    void updateChart();
};
#endif // MAINWINDOW_H
