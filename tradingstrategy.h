/**
 * @brief This class is an abstract class that will be the super class for all our trading strategy subclasses.
 * This is the base class for our strategies and holds common methods and attributes that are common among all of its subclasses.
 * @author Narges Haeri
 */

#ifndef tradingstrategy_h
#define tradingstrategy_h

#include <string>
#include <iostream>
#include <vector>
#include "trade.h"
#include "pricefetcher.h"
#include "broker.h"

class TradingStrategy
{

protected:
    Broker *broker = Broker::GetInstance();
    PriceFetcher price_fetcher = PriceFetcher();
    std::string ticker;
    std::vector<Trade> local_history;
    int strategy_id;

public:
    TradingStrategy(std::string ticker, int strategy_id); // constructor of class TradingStrategy
    virtual void analyze() = 0;                           // method for analysing trade
    virtual std::string getName() = 0;
    Trade createTrade(int num_shares, int action); // opening new position
    void addToLocalHistory(const Trade &trade);    // adding the trade to history
    std::vector<Trade> getLocalHistory();          // getting the list of all open and close positions
    virtual ~TradingStrategy();                    // destructor of class TradingStrategy
    int getStrategyID();
    std::string getTicker();
};

#endif /* tradingstrategy_h */