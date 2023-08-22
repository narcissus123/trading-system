/**
 * @brief This class deals with the executions of trades (Trade objects). Depending on the trade executed. Various
 * member varaibles will be updated. It will also keep track of all our portfolio statistics. It also keeps track of
 * all historical trades, current open positions, and closed positions and their profit and loss.
 *
 * @author Hamid Zargar
 */

#ifndef broker_h
#define broker_h

#include <vector>
#include "string"
#include "map"
#include "trade.h"

class Broker {

protected:

    Broker(){};
    static Broker* broker;
    bool connection_status = true;
    std::vector<std::pair<Trade, std::string>> trade_history; // string is the datetime trade occurred
    std::vector<Trade> open_positions;
    std::vector<std::tuple<Trade,float, float>> closed_positions; //first float is pnl, second return in percentage

    // Update these as trades executed
    float sortino_ratio = 0;
    float sharpe_ratio = 0;
    float max_drawdown = 0;
    float current_return = 0;

    // Don't change
    float risk_free_rate = 0.06; // This is th risk-free rate of return used in our calculations
    float max_drawdown_threshold = -0.1;

    void addToTradeHistory(const Trade& trade);
    void addToOpenPositions(const Trade& trade);
    void addToClosedPositions(const Trade& trade, float pnl, float ret);
    int buyToClose(std::vector<Trade>::iterator it, const Trade& trade);
    int sellToClose(std::vector<Trade>::iterator it, const Trade& trade);
    int buyToOpen(const Trade& trade, bool add_to_open_positions);
    int sellToOpen(const Trade& trade, bool add_to_open_positions);
    static float calculateStandardDeviation(const std::vector<float>& data);

    // Updates stats
    void calculateSortinoRatio();
    void calculateSharpeRatio();
    void calculateMaxDrawdown();
    void calculateCurrentReturn();

    //   Our initial balance, this is not updated actively but rather used for calculation of overall returns
    float initial_balance = 100000;

    // These values are the ones that are updated
    float total_equity = 100000;
    float lowest_reached_equity = 100000;
    float stock_position = 0;
    float cash_balance = 100000;

public:

    /**
     * Broker should not be cloneable.
     */

    Broker(Broker &other) = delete;

    /**
     * Broker should not be assignable.
     */

    void operator=(const Broker &) = delete;

    /**
     * This is the static method that controls the access to the Broker
     * instance. On the first run, it creates a Broker object and places it
     * into the static field. On subsequent runs, it returns the existing
     * object stored in the static field.
     */

    static Broker *GetInstance();

    /**
     * Finally, any Broker should define some business logic, which can be
     * executed on its instance.
     */

    bool getConnectionStatus() const;

    ~Broker(); //deConstructor when we point to the object
    int execute(const Trade& trade);
    std::vector<Trade> getOpenPositions();
    std::vector<std::pair<Trade, std::string>> getTradeHistory();
    std::vector<std::tuple<Trade, float, float>> getClosedPositions();
    float getTotalEquity();
    float getStockPosition();
    float getCashBalance();
    float getInitialBalance();
    float getSortinoRatio();
    float getSharpeRatio();
    float getMaxDrawdown();
    float getCurrentReturn();
    float getMaxDrawdownThreshold();

};


#endif //broker_h
