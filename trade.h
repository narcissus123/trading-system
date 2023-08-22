/**
 * @brief This calss deals with creation of our trades that will be created by our strategies and executed by our Broker.
 * @author Hamid Zargar
 */

#ifndef trade_h
#define trade_h

#include <string>

class Trade{

private:

    std::string ticker;
    int num_shares;
    int action;
    float price{};
    std::string order_type;
    int strategy_id;

public:

    //constructor
    Trade(std::string ticker, int num_shares, int action, float price, int strategy_id);

    //destructor
    ~Trade();
    std::string getTicker() const;
    int getNumShares() const;
    int getAction() const;
    float getPrice() const;
    std::string getOrderType() const;
    int getStrategyID() const;

    void setNumShares(int num_shares);
    void setPrice(float new_price);
    void setAction(int new_action);
};

#endif //trade_h
