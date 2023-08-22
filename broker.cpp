#include "broker.h"
#include "cmath"
#include "iostream"


/**
 * @brief Broker object is initilized to a nullptr
 * @author Hamid Zargar
 */

Broker* Broker::broker= nullptr;

/**
 * @brief Gets the currenlty initialized Broker object as a pointer. If no Broker object exists, it creates one.
 * @author Hamid Zargar
 * @return void
 */

Broker* Broker::GetInstance()
{
    if(broker==nullptr){
        broker = new Broker();
    }
    return broker;
}

/**
 * @brief Gets The connection status of the Broker object.
 * @author Hamid Zargar
 * @return The connection status
 */

bool Broker::getConnectionStatus() const {
    return this->connection_status;
}


/**
 * @brief Buys to close a open position.
 * @author Hamid Zargar
 * @param it Represents an iterator to the Trade object in our open positions.
 * @param trade Represents our new trade object.
 * @return A status integer representing the outcome of the operation. 0 for success, -1 for failure.
 */

int Broker::buyToClose(std::vector<Trade>::iterator it, const Trade& trade){

    // Current number of shares in open position is greater than or equal to the new trade's

    if (it->getNumShares() >= trade.getNumShares()){
        // Calculate PnL
        float pnl = ((float) trade.getNumShares() * it->getPrice()) -
                    ((float) trade.getNumShares() * trade.getPrice());

        // Add to closed positions
        float ret = (pnl/this->total_equity);
        this->addToClosedPositions(*it, pnl, ret);

        // Update our total total_balance
        this->total_equity += pnl;

        if (this->total_equity < this->lowest_reached_equity){
            this->lowest_reached_equity = this->total_equity;
        }

        // Update stats
        this->calculateSortinoRatio();
        this->calculateSharpeRatio();
        this->calculateMaxDrawdown();
        this->calculateCurrentReturn();

        this->stock_position += (float) trade.getNumShares() * it->getPrice();
        this->cash_balance -= (float) trade.getNumShares() * trade.getPrice();
        this->addToTradeHistory(trade);

        // Update share count
        it->setNumShares(it->getNumShares() - trade.getNumShares());

        // If new share count is 0, then position should be fully closed and shouldn't exist anymore
        if (it->getNumShares() == 0){
            it = this->open_positions.erase(it);
        }
        return 0;
    }

    // Current number of shares in open position is strictly less than the new trade's

    else {

        int diff_shares = trade.getNumShares() - it->getNumShares();

        if (((float) diff_shares * trade.getPrice()) > this->cash_balance){
            return -1;
        }

        float pnl = ((float) it->getNumShares() * it->getPrice()) -
                    ((float) it->getNumShares() * trade.getPrice());

        float ret = (pnl/this->total_equity);
        this->addToClosedPositions(*it, pnl, ret);

        // Update our total total_balance
        this->total_equity += pnl;

        if (this->total_equity < this->lowest_reached_equity){
            this->lowest_reached_equity = this->total_equity;
        }

        // Update stats
        this->calculateSortinoRatio();
        this->calculateSharpeRatio();
        this->calculateMaxDrawdown();
        this->calculateCurrentReturn();

        this->stock_position += (float) it->getNumShares() * it->getPrice() + (float) diff_shares * trade.getPrice();
        this->cash_balance -= (float) trade.getNumShares() * trade.getPrice();
        this->addToTradeHistory(trade);

        // Update share count
        it->setNumShares(diff_shares);
        it->setAction(trade.getAction());
        it->setPrice(trade.getPrice());

        return 0;
    }
}

/**
 * @brief Sells to close a open position.
 * @author Hamid Zargar
 * @param it Represents an iterator to the Trade object in our open positions.
 * @param trade Represents our new trade object.
 * @return A status integer representing the outcome of the operation. 0 for success, -1 for failure.
 */

int Broker::sellToClose(std::vector<Trade>::iterator it, const Trade& trade){

    if (it->getNumShares() >= trade.getNumShares()){

        float pnl = ((float) trade.getNumShares() * trade.getPrice()) -
                    ((float) trade.getNumShares() * it->getPrice());

        float ret = (pnl/this->total_equity);
        this->addToClosedPositions(*it, pnl, ret);

        // Update our total balance
        this->total_equity += pnl;

        if (this->total_equity < this->lowest_reached_equity){
            this->lowest_reached_equity = this->total_equity;
        }

        // Update stats
        this->calculateSortinoRatio();
        this->calculateSharpeRatio();
        this->calculateMaxDrawdown();
        this->calculateCurrentReturn();

        this->stock_position -= (float) trade.getNumShares() * it->getPrice();
        this->cash_balance += (float) trade.getNumShares() * trade.getPrice();
        this->addToTradeHistory(trade);

        // Update share count
        it->setNumShares(it->getNumShares() - trade.getNumShares());

        // If new share count is 0, then position should be fully closed and shouldn't exist anymore
        if (it->getNumShares() == 0){
            it = this->open_positions.erase(it);
        }
        return 0;
    }

    // Otherwise, number of shares in current position is strictly less than the new trade amount
    else{

        int diff_shares = trade.getNumShares() - it->getNumShares();

        // change cash balance to something related to equity since we are going short
        if (((float) diff_shares * trade.getPrice()) > this->cash_balance){
            return -1;
        }

        float pnl = ((float) it->getNumShares() * trade.getPrice()) -
                    ((float) it->getNumShares() * it->getPrice());


        float ret = (pnl/this->total_equity);
        this->addToClosedPositions(*it, pnl, ret);

        // Update our total total_balance
        this->total_equity += pnl;

        if (this->total_equity < this->lowest_reached_equity){
            this->lowest_reached_equity = this->total_equity;
        }

        // Update stats
        this->calculateSortinoRatio();
        this->calculateSharpeRatio();
        this->calculateMaxDrawdown();
        this->calculateCurrentReturn();

        this->stock_position -= (float) it->getNumShares() * it->getPrice() + (float) diff_shares * trade.getPrice();
        this->cash_balance += (float) trade.getNumShares() * trade.getPrice();
        this->addToTradeHistory(trade);

        // Update share count
        it->setNumShares(diff_shares);
        it->setAction(trade.getAction());
        it->setPrice(trade.getPrice());

        return 0;
    }
}

/**
 * @brief Buys to open a open position.
 * @author Hamid Zargar
 * @param add_to_open_positions Boolean to whether add to our open positions after execution.
 * @param trade Represents our new trade object.
 * @return A status integer representing the outcome of the operation. 0 for success, -1 for failure.
 */
int Broker::buyToOpen(const Trade& trade, bool add_to_open_positions = false){

    // Check if we have enough cash to execute trade
    if (((float) trade.getNumShares() * trade.getPrice()) > this->cash_balance){
        return -1;
    }

    else{
        this->stock_position += (float) trade.getNumShares() * trade.getPrice();
        this->cash_balance -= (float) trade.getNumShares() * trade.getPrice();
        this->total_equity = this->stock_position + this->cash_balance;
        this->addToTradeHistory(trade);

        if (add_to_open_positions){
            this->addToOpenPositions(trade);
        }

        return 0;
    }

}

/**
 * @brief Sells to open a open position.
 * @author Hamid Zargar
 * @param add_to_open_positions Boolean to whether add to our open positions after execution.
 * @param trade Represents our new trade object.
 * @return A status integer representing the outcome of the operation. 0 for success, -1 for failure.
 */

int Broker::sellToOpen(const Trade& trade, bool add_to_open_positions = false){

    // Check if we have enough cash to execute trade
    if (((float) trade.getNumShares() * trade.getPrice()) > this->cash_balance){
        return -1;
    }
    else{
        this->stock_position -= (float) trade.getNumShares() * trade.getPrice();
        this->cash_balance += (float) trade.getNumShares() * trade.getPrice();
        this->total_equity = this->stock_position + this->cash_balance;
        this->addToTradeHistory(trade);

        if (add_to_open_positions){
            this->addToOpenPositions(trade);
        }

        return 0;
    }
}

/**
 * @brief Executes a trade.
 * @author Hamid Zargar
 * @param trade Represents our new trade object.
 * @return A status integer representing the outcome of the operation. 0 for success, -1 for failure.
 */

int Broker::execute(const Trade& trade) {

    // Close the open position if the opposite position already exists
    for (auto it=this->open_positions.begin(); it!=open_positions.end(); it++)  {

        if ((it->getAction() == (trade.getAction() * -1)) &&
            (it->getStrategyID() == trade.getStrategyID()) &&
             (it->getTicker() == trade.getTicker())) {

            // If we receive a buy order for an existing position we buy to close
            if (trade.getAction() == 1 && it->getAction() == -1) {
                return this->buyToClose(it, trade);
            }

            // If we receive a sell order for an existing position we sell to close
            else if (trade.getAction() == -1 && it->getAction() == 1) {
                return this->sellToClose(it,trade);
            }
        }

        // If we have an identical position, with trade opening in same direction for the same stock
        else if ((it->getAction() == (trade.getAction())) &&
            (it->getStrategyID() == trade.getStrategyID()) &&
             (it->getTicker() == trade.getTicker())) {

            // Get the new price for our position which is the average of these prices weighted by the number of shares
            float avg_price = ((it->getPrice() * (float) it->getNumShares()) + (trade.getPrice() * (float) trade.getNumShares()))/((float)(it->getNumShares() + trade.getNumShares()));
            it->setNumShares(it->getNumShares() + trade.getNumShares());
            it->setPrice(avg_price);

            // buy to open if trade is buy order
            if (trade.getAction() == 1){
                return this->buyToOpen(trade);
            }
            // sell to open if trade is sell order
            else{
                return this->sellToOpen(trade);
            }
        }
    }

    // If no existing position for trade to interact with then we create a
    // new open position instead of modifying an old one

    if (trade.getAction() == 1){
        return this->buyToOpen(trade, true);
    }
    else{
        return this->sellToOpen(trade, true);
    }
}

/**
 * @brief Gets the open positions.
 * @author Hamid Zargar
 * @return The open positions.
 */

std::vector<Trade> Broker::getOpenPositions() {
    return this->open_positions;
}

/**
 * @brief Gets the historical trades.
 * @author Hamid Zargar
 * @return The historical trades.
 */

std::vector<std::pair<Trade, std::string>> Broker::getTradeHistory() {
    return this->trade_history;
}

/**
 * @brief Destructor.
 * @author Hamid Zargar
 */


Broker::~Broker() = default;


/**
 * @brief Adds trade to historical trades.
 * @author Hamid Zargar
 * @param trade Represents the Trade object we want to add to the trade history.
 */

void Broker::addToTradeHistory(const Trade& trade) {

    // Adds time it was executed to table
    time_t now = time(nullptr);
    tm * ptm = localtime(&now);
    char buffer[32];
    strftime(buffer, 32, "%Y-%m-%m %H:%M:%S", ptm);

    this->trade_history.push_back({trade, buffer});
}

/**
 * @brief Add to open positions.
 * @author Hamid Zargar
 * @param trade Represents the Trade object we want to add to our open positions.
 */

void Broker::addToOpenPositions(const Trade &trade) {

    this->open_positions.push_back(trade);

}

/**
 * @brief Gets the total equity.
 * @author Hamid Zargar
 * @return The total equity.
 */

float Broker::getTotalEquity() {
    return this->total_equity;
}

/**
 * @brief Gets the cash balance.
 * @author Hamid Zargar
 * @return The cash balance.
 */

float Broker::getCashBalance() {
    return this->cash_balance;
}

/**
 * @brief Add to closed positions.
 * @author Hamid Zargar
 * @param trade Represents the Trade object we want to add to our closed positions.
 * @param pnl Represents our profit/loss.
 * @param ret Represents return in percentage.
 */

void Broker::addToClosedPositions(const Trade &trade, float pnl, float ret) {

    this->closed_positions.emplace_back(trade, pnl, ret);
}


/**
 * @brief Gets the stock position.
 * @author Hamid Zargar
 * @return The stock positon (long vs short).
 */

float Broker::getStockPosition() {
    return this->stock_position;
}

/**
 * @brief Gets the closed positions.
 * @author Hamid Zargar
 * @return The closed positions.
 */

std::vector<std::tuple<Trade, float, float>> Broker::getClosedPositions() {
    return this->closed_positions;
}

/**
 * @brief Gets the initial balance.
 * @author Hamid Zargar
 * @return The initial balance.
 */

float Broker::getInitialBalance() {
    return this->initial_balance;
}

/**
 * @brief Gets the sortino ratio.
 * @author Hamid Zargar
 * @return The sortino ratio.
 */

float Broker::getSortinoRatio() {
    return this->sortino_ratio;
}

/**
 * @brief Gets the sharpe ratio.
 * @author Hamid Zargar
 * @return The sharpe ratio.
 */

float Broker::getSharpeRatio() {
    return this->sharpe_ratio;
}

/**
 * @brief Gets the max drawdown.
 * @author Hamid Zargar
 * @return The max drawdown.
 */

float Broker::getMaxDrawdown() {
    return this->max_drawdown;
}

/**
 * @brief Gets the currentReturn.
 * @author Hamid Zargar
 * @return The current return.
 */

float Broker::getCurrentReturn() {
    return this->current_return;
}

/**
 * @brief Calcuates the standard deviation of the darta.
 * @author Hamid Zargar
 * @param data Represents a vector of floats
 * @return A float representing the standard deviation
 */


float Broker::calculateStandardDeviation(const std::vector<float>& data) {

    float sum = 0.0, mean, standardDeviation = 0.0;

    for(float val: data) {
        sum += val;
    }

    mean = sum / (float) data.size();

    for(float val: data) {
        standardDeviation += (float) pow(val - mean, 2);
    }

    return sqrt(standardDeviation / (float) data.size());
}

/**
 * @brief Calculates the sortino ratio.
 * @author Hamid Zargar
 */

void Broker::calculateSortinoRatio() {

    std::vector<float> neg_returns;

    for (auto & closed_position: this->closed_positions){

        float ret = std::get<2>(closed_position);

        // If ret is negative then add it to list
        if (ret < 0){
            neg_returns.push_back(ret);
        }
    }

    float sd = this->calculateStandardDeviation(neg_returns);
    float expected_returns = (this->total_equity/this->initial_balance) - 1;

    float sortinoRatio = (expected_returns - this->risk_free_rate) / sd;

    this->sortino_ratio = sortinoRatio;
}

/**
 * @brief Calculates the sharpe ratio.
 * @author Hamid Zargar
 */

void Broker::calculateSharpeRatio() {

    std::vector<float> returns;

    for (auto & closed_position: this->closed_positions){

        float ret = std::get<2>(closed_position);
        returns.push_back(ret);
    }

    float sd = this->calculateStandardDeviation(returns);

    float expected_returns = (this->total_equity/this->initial_balance) - 1;

    float sharpeRatio = (expected_returns - this->risk_free_rate) / sd;

    this->sharpe_ratio = sharpeRatio;

}

/**
 * @brief Calculates the max drawdown of the data.
 * @author Hamid Zargar
 */

// Max drawdown in percentage
void Broker::calculateMaxDrawdown() {

    float lowest_return = this->lowest_reached_equity/this->initial_balance - 1;

    if (lowest_return < 0 && lowest_return < this->max_drawdown){
        this->max_drawdown = lowest_return;
    }
}

/**
 * @brief Calculates the current return.
 * @author Hamid Zargar
 */

// Current total returns in percentage
void Broker::calculateCurrentReturn() {

    this->current_return = (this->total_equity/this->initial_balance) - 1;
}

/**
 * @brief Gets the max drawdown threshold.
 * @author Hamid Zargar
 * @return The max drawdown threshold
 */

float Broker::getMaxDrawdownThreshold() {
    return this->max_drawdown_threshold;
}









