/**
 * @brief The class holds and manages the existing strategies by turning them on and off.
 * @author Hamid Zargar
 */

#ifndef TRADINGSYSTEM_PORTFOLIO_H
#define TRADINGSYSTEM_PORTFOLIO_H

#include "tradingstrategy.h"

class Portfolio{

private:

    std::vector<std::pair<TradingStrategy*,int>> strategies; // int is the status in the pair

public:

    Portfolio();
    void startAllStrategies();
    void startStrategy(int strategy_id);
    void stopAllStrategies();
    void stopStrategy(int strategy_id);
    void addStrategy(TradingStrategy* strategy);
    void removeStrategy(int strategy_id);
    TradingStrategy* getStrategy(int strategy_id);
    std::vector<std::pair<TradingStrategy*,int>> getStrategies();
    bool isStrategyActive(int strategy_id);
    void analyzeAll();



};

#endif //TRADINGSYSTEM_PORTFOLIO_H
