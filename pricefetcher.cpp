#include <iomanip>
#include "pricefetcher.h"
#include "quote.hpp"
#include "iostream"
#include "fstream"
#include "ios"
#include "filesystem"
#include "ctime"


/**
 * @brief Constructor for our price api.
 * @author Hamid Zargar
*/

PriceFetcher::PriceFetcher() = default;

/**
 * @brief Downlaods the price data as a historical CSV saved to disk.
 * @param ticker The stock ticker we want data for
 * @param start_date The start date of our data
 * @param end_date The end date of our data
 * @param interval The granualrity of our data (1 week, 1 day, etc..)
 * @param file_name The name of the file we want to save to disk
 * @return 0 for success, 1 for failure
 * @author Hamid Zargar
*/

int PriceFetcher::downloadHistoricalCSV(std::string ticker, std::string start_date, std::string end_date, std::string interval, std::string file_name) {

    // Will store date attributes before we convert to time_t
    struct tm start_tm{};
    struct tm end_tm{};

    // Tries to make conversion from string to struct tm. If fails we return 1
    if (strptime(start_date.c_str(), "%Y-%m-%d", &start_tm) == NULL){
        return 1;
    }

    // Tries to make conversion from string to struct tm. If fails we return 1
    if (strptime(end_date.c_str(), "%Y-%m-%d", &end_tm) == NULL){
        return 1;
    }

    // Convert to time_t for function
    time_t end_t = mktime(&end_tm);
    time_t start_t = mktime(&start_tm);

    // Gets the stock historical prices in csv
    Quote *quote = new Quote(ticker);
    std::string data_string = quote->getHistoricalCsv(start_t, end_t, interval.c_str());

    std::ofstream output;
    // Current directory is cmake-build-debug so we want to save in parent directory which is trading system
    output.open("../"+file_name);
    output << data_string << std::endl;
    output.close();

    return 0;
}


/**
 * @brief Gets the price data for a specific ticker between specifci dates.
 * @param ticker The stock ticker we want data for
 * @param start_date The start date of our data
 * @param end_date The end date of our data
 * @param interval The granualrity of our data (1 week, 1 day, etc..)
 * @return 0 for success
 * @author Hamid Zargar
*/

// Fetches the prices between a pre-defined interval and returns a dictionary (map) of dictionaries (maps)
std::map<std::string, std::map<std::string, double>> PriceFetcher::fetch(std::string ticker, std::string start_date, std::string end_date, std::string interval) {

    // Gets the stock historical prices in csv
    Quote *quote = new Quote(ticker);
    quote->getHistoricalSpots(start_date.c_str(), end_date.c_str(), interval.c_str());

    // Initialize map
    std::map<std::string, std::map<std::string, double>> m {};

    int n = quote->nbSpots();
    for (int i = 0; i < n; i++){

        Spot spot = quote->getSpot((size_t)i);

        // Create a sub_map containing all our values
        std::map<std::string, double> sub_map {};

        // Add values to sub_map then add to m
        sub_map["Open"] = spot.getOpen();
        sub_map["High"] = spot.getHigh();
        sub_map["Low"] = spot.getLow();
        sub_map["Close"] = spot.getClose();

        m[spot.getDateToString()] = sub_map;

    }

    return m;
}

/**
 * @brief Gets the last price data for a specific day from the current day.
 * @param ticker The stock ticker we want data for
 * @param minus_days The number of days fro mthe current date backwards
 * @return The last price of the stock
 * @author Hamid Zargar
*/
float PriceFetcher::fetch_last_price(std::string ticker, int minus_days) {

    if (minus_days < 0){
        throw std::invalid_argument("minus days parameter must be >= 0");
    }

    Quote *security = new Quote(ticker);

    time_t now = time(0);
    tm a = *localtime(&now);
    tm b = *localtime(&now);

    tm a_minus = DatePlusDays(b, -10);

    char current_date[90];
    char current_date_minus[90];
    strftime(current_date, 20, "%Y-%m-%d", &a);
    strftime(current_date_minus, 20, "%Y-%m-%d", &a_minus);

    // Get the historical spots from Yahoo Finance
    security->getHistoricalSpots(current_date_minus, current_date, "1d");

    try {
        Spot spot = security->getLastSpot(0 + minus_days);
        return (float) spot.getClose();
    } catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 0;
    }
}

/**
 * @brief Creates a new date with the added days to the date.
 * @param date The current date
 * @param days The number of days to add to our current date
 * @return A struct tm representing the new date.
 * @author Hamid Zargar
*/

struct tm PriceFetcher::DatePlusDays( struct tm date, int days )
{
    const time_t ONE_DAY = 24 * 60 * 60 ;

    // Seconds since start of epoch
    time_t date_seconds = mktime( &date ) + (days * ONE_DAY) ;

    // Update caller's date
    // Use localtime because mktime converts to UTC so may change date
    date = *localtime( &date_seconds ) ;

    return date;
}

/**
 * @brief Destrcutor to deallocate memory.
 * @author Hamid Zargar
*/
PriceFetcher::~PriceFetcher() = default;
