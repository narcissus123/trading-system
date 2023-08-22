//
// Created by Hamid Zargar on 2021-11-26.
//

#include "riskmanager.h"


/**
 * @brief Constructor for our Risk Manager
 * @author Hamid Zargar
 * @param portfolio Pointer to our portoflio containing our strategy
 */
RiskManager::RiskManager(Portfolio* portfolio) {

    this->portfolio = portfolio;

}

/**
 * @brief If our max drawdown threshold is reached, we stop all strategies and close all open positions.
 * @author Hamid Zargar
 */

void RiskManager::manageRisk() {

    // If we've surpassed our max draw down threshold (tolerance) then we stop all strategies and exit all positions
    // Note: draw down numbers are negative numbers that represent returns, so we look for a draw down that is LESS THAN
    // our threshold

    if (this->broker->getMaxDrawdown() < this->broker->getMaxDrawdownThreshold()){

        this->portfolio->stopAllStrategies();
        this->closeAllOpenPositions();
    }
}

/**
 * @brief Closes all open positions in our Broker object by executing the opposite trade at the current price.
 * @author Hamid Zargar
 */

void RiskManager::closeAllOpenPositions() {

    // Close all open positions by executing the opposite trade
    for (Trade trade: this->broker->getOpenPositions()){

        float last_price = priceFetcher.fetch_last_price(trade.getTicker(), 0);

        // Update values to opposite action and the current available price
        trade.setAction((-1) * trade.getAction());
        trade.setPrice(last_price);

        this->broker->execute(trade);
    }
}
