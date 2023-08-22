/**
 * @brief This class creates a regression to the mean trading strategy that executes trades in the direction of their previous days movement.
 * @author Hamid Zargar
 */

#ifndef TRADINGSYSTEMGUI_REGRESSION_TRADING_STRATEGY_H
#define TRADINGSYSTEMGUI_REGRESSION_TRADING_STRATEGY_H

#include "tradingstrategy.h"
#include "broker.h"

class RegressionTradingStrategy: public TradingStrategy{

private:

    std::string ticker;
    int strategy_id;

public:

    RegressionTradingStrategy(const std::string& ticker, int strategy_id);
    void analyze();
    ~RegressionTradingStrategy();
    std::string getName();
};

#endif //TRADINGSYSTEMGUI_REGRESSION_TRADING_STRATEGY_H
