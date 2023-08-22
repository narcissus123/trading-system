#include "trade.h"
#include <string>

/**
 * @brief Constructor for our Trade object.
 * @author Hamid Zargar
 * @param ticker Represents the stock ticker we want to employ the strategy on.
 * @param num_shares Represents the number of shares we want to execute in our trade.
 * @param action 1 to buy, -1 to sell
 * @param price Represents the the price we want to execute at.
 * @param strategy_id Represents the id of the strategy that is executing this trade.
 */

Trade::Trade(std::string ticker, int num_shares, int action, float price, int strategy_id) {

    this->ticker = ticker;
    this->num_shares = num_shares;
    this->action = action;
    this->price = price;
    // If price is given then we want an execution at a specific price so it's a limit order
    this->order_type = "MKT";
    this->strategy_id = strategy_id;


}

/**
 * @brief Gets the ticker of the trade.
 * @author Hamid Zargar
 * @return The ticker of the trade
 */

std::string Trade::getTicker() const {
    return this->ticker;
}

/**
 * @brief Gets the number of shares of the trade.
 * @author Hamid Zargar
 * @return The number of shares of the trade
 */

int Trade::getNumShares() const {
    return this->num_shares;
}

/**
 * @brief Gets the action of the trade.
 * @author Hamid Zargar
 * @return The action of the trade
 */

int Trade::getAction() const {
    return this->action;
}

/**
 * @brief Gets the price of the trade.
 * @author Hamid Zargar
 * @return The price of the trade
 */

float Trade::getPrice() const {
    return this->price;
}

/**
 * @brief Gets the order type of the trade.
 * @author Hamid Zargar
 * @return The order type of the trade
 */

std::string Trade::getOrderType() const {
    return this->order_type;
}

/**
 * @brief Gets the strategy id of the trade.
 * @author Hamid Zargar
 * @return The strategy id of the trade
 */

int Trade::getStrategyID() const {
    return this->strategy_id;
}

/**
 * @brief Sets the number of shares of the trade.
 * @author Hamid Zargar
 */

void Trade::setNumShares(int shares) {
    this->num_shares = shares;
}

/**
 * @brief Sets the price of the trade.
 * @author Hamid Zargar
 */

void Trade::setPrice(float new_price) {
    this->price = new_price;
}

/**
 * @brief Sets the action of the trade.
 * @author Hamid Zargar
 */

void Trade::setAction(int new_action) {
    this->action = new_action;
}

/**
 * @brief Destructor to deallocate memory.
 * @author Hamid Zargar
 */

Trade::~Trade() = default;





