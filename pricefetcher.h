//
// Created by Hamid Zargar on 2021-10-31.
//

/**
 * @brief This class is the API to Yahoo Finance that will retrieve the stock price data for which our strategies will execute their trades on.
 * @author Hamid Zargar
*/

#ifndef pricefetcher_h
#define pricefetcher_h

#include "string"
#include "map"

class PriceFetcher{

public:

    //constructor
    PriceFetcher();

    //destructor
    ~PriceFetcher();
    int downloadHistoricalCSV(std::string ticker, std::string start_date, std::string end_date, std::string interval, std::string file_name);
    std::map<std::string, std::map<std::string, double>> fetch(std::string ticker, std::string start_date, std::string end_date, std::string interval);
    float fetch_last_price(std::string ticker, int minus_days);


    tm DatePlusDays(tm date, int days);
};

#endif //pricefetcher_h
