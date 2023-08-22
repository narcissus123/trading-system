/**
 * @brief This class recevies a pointer to our Broker object and Portoflio object and if our total balance
 * drops below our max drawdown threshold we turn off all the strategies, stop trade execution, and close all open positions.
 * @author Hamid Zargar
 */

#ifndef TRADINGSYSTEM_RISKMANAGER_H
#define TRADINGSYSTEM_RISKMANAGER_H

#include "broker.h"
#include "portfolio.h"

class RiskManager {

private:

    Broker *broker = Broker::GetInstance();
    Portfolio* portfolio;
    PriceFetcher priceFetcher;
    void closeAllOpenPositions();

public:

    RiskManager(Portfolio* portfolio);
    void manageRisk();

};


#endif //TRADINGSYSTEM_RISKMANAGER_H
