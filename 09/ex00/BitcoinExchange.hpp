#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>

class BitcoinExchange
{
public:
	BitcoinExchange(const std::string& dbFile);
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	void evaluate(const std::string& inputFile) const;

private:
	std::map<std::string, float> _rates;

	bool isValidDate(const std::string& date) const;
	bool isValidValue(const std::string& str, float& out) const;
};

#endif
