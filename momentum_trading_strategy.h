/**
 * @brief This class creates a momentum trading strategy that executes trades in the direction of their previous days movement.
 * @author Hamid Zargar
 */

#ifndef MOMENTUM_TRADING_STRATEGY
#define MOMENTUM_TRADING_STRATEGY

#include "tradingstrategy.h"
#include "broker.h"

class MomentumTradingStrategy: public TradingStrategy{

private:

    std::string ticker;
    int strategy_id;

public:

    MomentumTradingStrategy(const std::string& ticker, int strategy_id);
    void analyze();
    ~MomentumTradingStrategy();
    std::string getName();
};

#endif //MOMENTUM_TRADING_STRATEGY