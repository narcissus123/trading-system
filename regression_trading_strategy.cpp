//
// Created by Hamid Zargar on 2021-11-30.
//


#include "regression_trading_strategy.h"

/**
 * @brief Constructor for regression trading strategy class.
 * @author Hamid Zargar
 * @param ticker Represents the stock ticker we want to employ the strategy on.
 * @param strategy_id Represents the id we will assign to the strategy.
 */

RegressionTradingStrategy::RegressionTradingStrategy(const std::string& ticker, int strategy_id) : TradingStrategy(ticker, strategy_id) {

    this->ticker = ticker;
    this->strategy_id = strategy_id;

}

/**
 * @brief Executes the trade using our Broker object pointer if the price conditions are met.
 * @author Hamid Zargar
 */

void RegressionTradingStrategy::analyze(){

    float currentPrice = TradingStrategy::price_fetcher.fetch_last_price(this->ticker, 0);
    float last1 = TradingStrategy::price_fetcher.fetch_last_price(this->ticker, 1);
    float last2 = TradingStrategy::price_fetcher.fetch_last_price(this->ticker, 2);
    float last3 = TradingStrategy::price_fetcher.fetch_last_price(this->ticker, 3);
    float last4 = TradingStrategy::price_fetcher.fetch_last_price(this->ticker, 4);
    float last5 = TradingStrategy::price_fetcher.fetch_last_price(this->ticker, 5);

    float avg = (last1 + last2 + last3 + last4 + last5)/5;

    if (currentPrice > avg){
        Trade trade(this->ticker, 50, -1, currentPrice, this->strategy_id);
        TradingStrategy::broker->execute(trade);
    }

    else if (currentPrice < avg){
        Trade trade(this->ticker, 50, 1, currentPrice, this->strategy_id);
        TradingStrategy::broker->execute(trade);
    }

    // Otherwise, don't execute any trades
}

/**
 * @brief The strategy name for this type of strategy.
 * @author Hamid Zargar
 * @return The strategy name "Regression Strategy"
 */

std::string RegressionTradingStrategy::getName(){
    return "Regression Strategy";
}

/**
 * @brief Destructor to deallocate memory.
 * @author Hamid Zargar
 */

RegressionTradingStrategy::~RegressionTradingStrategy() = default;;
