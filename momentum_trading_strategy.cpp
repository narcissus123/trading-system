#include "momentum_trading_strategy.h"

/**
 * @brief Constructor for momentum trading strategy class.
 * @author Hamid Zargar
 * @param ticker Represents the stock ticker we want to employ the strategy on.
 * @param strategy_id Represents the id we will assign to the strategy.
 */

MomentumTradingStrategy::MomentumTradingStrategy(const std::string& ticker, int strategy_id) : TradingStrategy(ticker, strategy_id) {

    this->ticker = ticker;
    this->strategy_id = strategy_id;

}


/**
 * @brief Executes the trade using our Broker object pointer if the price conditions are met.
 * @author Hamid Zargar
 */

void MomentumTradingStrategy::analyze(){

    float currentPrice = TradingStrategy::price_fetcher.fetch_last_price(this->ticker, 0);
    float lastClosePrice = TradingStrategy::price_fetcher.fetch_last_price(this->ticker, 1);

    if ((currentPrice < lastClosePrice)){
        Trade trade(this->ticker, 100, -1, currentPrice, this->strategy_id);
        TradingStrategy::broker->execute(trade);
    }

    else if ((currentPrice > lastClosePrice)){
        Trade trade(this->ticker, 100, 1, currentPrice, this->strategy_id);
        TradingStrategy::broker->execute(trade);
    }

    // Otherwise, don't execute any trades
}

/**
 * @brief The strategy name for this type of strategy.
 * @author Hamid Zargar
 * @return The strategy name "Momentum Strategy"
 */

std::string MomentumTradingStrategy::getName(){
    return "Momentum Strategy";
}

/**
 * @brief Destructor to deallocate memory.
 * @author Hamid Zargar
 */
MomentumTradingStrategy::~MomentumTradingStrategy() = default;;