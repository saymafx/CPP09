#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <cmath>

int date_error(const std::string& dateStr) {
    std::istringstream iss(dateStr);

    int year, month, day;
    char dash1, dash2;

    if (!(iss >> year >> dash1 >> month >> dash2 >> day)) {
		std::cout << "Error: bad input => " << dateStr << std::endl;
        return 1;
    }

    if (iss.fail() || dash1 != '-' || dash2 != '-') {
		std::cout << "Error: bad input => " << dateStr << std::endl;
        return 1;
    }

    if (year < 1900 || year > 2100) {
		std::cout << "Error: bad input => " << dateStr << std::endl;
        return 1;
    }

    if (month < 1 || month > 12) {
		std::cout << "Error: bad input => " << dateStr << std::endl;
        return 1;
    }

    int maxDay = 31;
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        maxDay = 30;
    } else if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            maxDay = 29;
        } else {
            maxDay = 28;
        }
    }

    if (day < 1 || day > maxDay) {
		std::cout << "Error: bad input => " << dateStr << std::endl;
        return 1;
    }
    return 0;
}

int amount_error(float amount) {
    if (amount <= 0) {
        std::cout << "Error: not a positive number." << std::endl;
        return 1;
    }
    if (amount > 10000) {
        std::cout << "Error: too large a number." << std::endl;
        return 1;
    }
    return 0;
}

int date_difference(const std::string& date1, const std::string& date2) {
    int year1, month1, day1;
    int year2, month2, day2;
    sscanf(date1.c_str(), "%d-%d-%d", &year1, &month1, &day1);
    sscanf(date2.c_str(), "%d-%d-%d", &year2, &month2, &day2);

    int yearDiff = year1 - year2;
    int monthDiff = month1 - month2;
    int dayDiff = day1 - day2;

    int yearDays = yearDiff * 365;
    int monthDays = monthDiff * 30;

    int totalDays = yearDays + monthDays + dayDiff;
	return totalDays;
}

void	pars_data(std::map<std::string, float> &Data) {
	std::ifstream	file;
	file.open("data.csv");
	if (!file.is_open()) {
		file.open("input.csv");
		if (!file.is_open()) {
			std::cout << "Error: could not open file." << std::endl;
			exit(0);
		}
	}

	std::string	line;
	while (std::getline(file, line)) {
		if (line == "date,exchange_rate") {continue;}
		std::istringstream stream(line);
		std::string date, rate;
		if (std::getline(stream, date, ',') && std::getline(stream, rate, ',')) {
			float	exchangeRate;
			try {
                exchangeRate = std::stof(rate);
            } catch (const std::exception& e) {
                std::cout << "Error: invalid exchange rate value." << std::endl;
                continue;
            }

			Data[date] = exchangeRate;

			//std::cout << "\"" << date << "\"" << " = " << "\"" << exchangeRate << "\"" << std::endl;
		}
	}	
	file.close();
}

void    pars_file(char *av, std::map<std::string, float> &data) {
    std::string		name = av;
    std::string		ext = ".txt";
	(void)data;
	// if extention isnt .txt //
	if (name.length() <= ext.length()) {std::cout << "Error: wrong file extension." << std::endl; exit(0);}
	if (name.substr(name.length() - ext.length()) != ext) {std::cout << "Error: wrong file extension." << std::endl; exit(0);}
	// if fails opening file //
	std::ifstream	file(name);
	if (!file.is_open()) {std::cout << "Error: could not open argument file." << std::endl; exit(0);}
	// process of program follows //
	std::string			line;
	while(std::getline(file, line)) {
		if (line == "date | value") {continue;}
		std::istringstream	stream(line);
		std::string			date, amount;
		if (std::getline(stream, date, '|') && std::getline(stream, amount, '|')) {
			// remove first and last space from both elements//
			date.erase(0, date.find_first_not_of(" "));
			date.erase(date.find_last_not_of(" ") + 1);
			amount.erase(0, amount.find_first_not_of(" "));
			amount.erase(amount.find_last_not_of(" ") + 1);
			float		TheAmount;
			try {
				TheAmount = std::stof(amount);
			} catch (const std::exception& e) {
                std::cout << "Error: invalid amount value." << std::endl;
                continue;
            }
			// handle possible errors on execution //
			if (date_error(date)) {continue;}
			if (amount_error(TheAmount)) {continue;}
			// actual conversion if everything is fine //
            std::map<std::string, float>::const_iterator it = data.find(date);
            if (it == data.end()) {
                // if Date not found, find the nearest one //
                it = data.lower_bound(date);
                if (it == data.begin()) {
                    // The given date is earlier than any available dates, use first one //
                    it = data.begin();
                } else if (it == data.end()) {
                    // The given date is later than any available dates, use last one //
                    it = --data.end();
                } else {
                    // Find the nearest date by comparing the difference in days
                    std::map<std::string, float>::const_iterator lower = it;
                    std::map<std::string, float>::const_iterator upper = it;
                    --lower;

                    int daysLower = date_difference(lower->first, date);
                    int daysUpper = date_difference(upper->first, date);

                    if (daysLower > daysUpper) {
                        it = upper;
                    }
                }
            }
            // Perform the conversion using the found exchange rate
            double convertedAmount = static_cast<double>(TheAmount) * static_cast<double>(it->second);
			std::cout << date << " => " << TheAmount << " = " << convertedAmount << std::endl;

        }
		else
			std::cout << "Error: bad input => " << line << std::endl;
    }
    file.close();
}

int     main(int ac, char **av) {
    (void)ac;
    (void)av;
	std::map<std::string, float> Data;
    if (ac != 2) {std::cout << "Error: could not open file." << std::endl; exit(0);}
    pars_data(Data);
	pars_file(av[1], Data);
}