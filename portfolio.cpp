#include "portfolio.h"


/**
 * @brief The constructor for our class.
 * @author Hamid Zargar
 */
Portfolio::Portfolio() = default;

/**
 * @brief The strategies within our portoflio will be started and their status will changed to 1 to indicate they are on.
 * @author Hamid Zargar
 */
void Portfolio::startAllStrategies() {

    // Change all status bits to 1 to signify ON
    for (auto & strategy : this->strategies){
        strategy.second = 1;
    }
}

/**
 * @brief The strategy within our portoflio will be started and their status will changed to 1 to indicate they are on.
 * @author Hamid Zargar
 * @param strategy_id Represent the id of the strategy we want to start
 */
void Portfolio::startStrategy(int strategy_id) {

    // Change all status bits to 1 to signify ON
    for (auto & strategy : this->strategies){
        if (strategy.first->getStrategyID() == strategy_id){
            strategy.second = 1;
        }
    }
}

/**
 * @brief The strategies within our portoflio will be stopped and their status will changed to 0 to indicate they are off.
 * @author Hamid Zargar
 */
void Portfolio::stopAllStrategies() {

    // Change all status bits to 0 to signify OFF
    for (auto & strategy : this->strategies){
        strategy.second = 0;
    }
}

/**
 * @brief The strategy within our portoflio will be stopped and their status will changed to 0 to indicate they are off.
 * @author Hamid Zargar
 * @param strategy_id Represent the id of the strategy we want to stop
 */
void Portfolio::stopStrategy(int strategy_id) {

    // Change all status bits to 0 to signify OFF
    for (auto & strategy_pair : this->strategies){
        if (strategy_pair.first->getStrategyID() == strategy_id){
            strategy_pair.second = 0;
        }
    }
}

/**
 * @brief Adds the strategy to the portfolio.
 * @author Hamid Zargar
 * @param strategy Represent a pointer a TradingStrategy subclass object.
 */
void Portfolio::addStrategy(TradingStrategy *strategy) {

    this->strategies.push_back({strategy, 0});

}

/**
 * @brief Removes the strategy to the portfolio.
 * @author Hamid Zargar
 * @param strategy_id Represent the id of the strategy.
 */
void Portfolio::removeStrategy(int strategy_id) {

    for (auto it = this->strategies.begin(); it != this->strategies.end(); it++){
        if (it->first->getStrategyID() == strategy_id){
            this->strategies.erase(it);
        }
    }
}

/**
 * @brief Gets the strategy to the portfolio.
 * @author Hamid Zargar
 * @param strategy_id Represent the id of the strategy.
 */
TradingStrategy* Portfolio::getStrategy(int strategy_id) {

    for (auto & strategy : this->strategies){
        if (strategy.first->getStrategyID() == strategy_id){
            return strategy.first;
        }
    }

    throw std::invalid_argument("Strategy with id: " + std::to_string(strategy_id) +" does not exist in 'strategies' vector");
}

/**
 * @brief Gets all the strategies in the portfolio.
 * @author Hamid Zargar
 * @return A vector holding the strategy objects and their status codes
 */

std::vector<std::pair<TradingStrategy *, int>> Portfolio::getStrategies() {
    return this->strategies;
}


/**
 * @brief Determines whether a strategy is active.
 * @author Hamid Zargar
 * @param strategy_id Represent the id of the strategy.
 * @return Boolean for whether the strategy is active. True if active, False if not active.
 */
bool Portfolio::isStrategyActive(int strategy_id) {

    for (auto & strategy : this->strategies){
        if (strategy.second == 1 && strategy.first->getStrategyID() == strategy_id){
            return true;
        }
        else if (strategy.second == 0 && strategy.first->getStrategyID() == strategy_id){
            return false;
        }
    }

    throw std::invalid_argument("Strategy with id: " + std::to_string(strategy_id) +" does not exist in 'strategies' vector");
}


/**
 * @brief Runs the analyze method on all the strategies i nteh portfolio that are active.
 * @author Hamid Zargar
 */

void Portfolio::analyzeAll() {

    for (auto& strategy: this->strategies){
        if (this->isStrategyActive(strategy.first->getStrategyID())){
            strategy.first->analyze();
        }
    }
}







