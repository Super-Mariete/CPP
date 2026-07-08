// ************************************************************************** //
//                                                                            //
//                Account.cpp for GlobalBanksters United                      //
//                                                                            //
// ************************************************************************** //

#include "Account.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>

// Inicialización de variables estáticas (compartidas por todas las cuentas)
int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

// Constructor: se llama al crear una cuenta
Account::Account(int initial_deposit)
	: _accountIndex(_nbAccounts), _amount(initial_deposit),
	  _nbDeposits(0), _nbWithdrawals(0)
{
	// Actualizar variables estáticas
	_nbAccounts++;
	_totalAmount += initial_deposit;

	// Mostrar mensaje de creación
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";"
			  << "amount:" << this->_amount << ";"
			  << "created" << std::endl;
}

// Destructor: se llama al destruir una cuenta
Account::~Account()
{
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";"
			  << "amount:" << this->_amount << ";"
			  << "closed" << std::endl;
}

// Métodos estáticos (getters de variables estáticas)
int Account::getNbAccounts()
{
	return _nbAccounts;
}

int Account::getTotalAmount()
{
	return _totalAmount;
}

int Account::getNbDeposits()
{
	return _totalNbDeposits;
}

int Account::getNbWithdrawals()
{
	return _totalNbWithdrawals;
}

// Muestra información de todas las cuentas
void Account::displayAccountsInfos()
{
	_displayTimestamp();
	std::cout << "accounts:" << _nbAccounts << ";"
			  << "total:" << _totalAmount << ";"
			  << "deposits:" << _totalNbDeposits << ";"
			  << "withdrawals:" << _totalNbWithdrawals << std::endl;
}

// Hacer un depósito
void Account::makeDeposit(int deposit)
{
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";"
			  << "p_amount:" << this->_amount << ";"
			  << "deposit:" << deposit << ";";
	
	this->_amount += deposit;
	this->_nbDeposits++;
	_totalAmount += deposit;
	_totalNbDeposits++;
	
	std::cout << "amount:" << this->_amount << ";"
			  << "nb_deposits:" << this->_nbDeposits << std::endl;
}

// Hacer un retiro (con validación)
bool Account::makeWithdrawal(int withdrawal)
{
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";"
			  << "p_amount:" << this->_amount << ";";
	
	// Verificar si hay fondos suficientes
	if (this->_amount < withdrawal)
	{
		std::cout << "withdrawal:refused" << std::endl;
		return false;
	}
	
	std::cout << "withdrawal:" << withdrawal << ";";
	
	this->_amount -= withdrawal;
	this->_nbWithdrawals++;
	_totalAmount -= withdrawal;
	_totalNbWithdrawals++;
	
	std::cout << "amount:" << this->_amount << ";"
			  << "nb_withdrawals:" << this->_nbWithdrawals << std::endl;
	
	return true;
}

// Obtener el saldo actual
int Account::checkAmount() const
{
	return this->_amount;
}

// Mostrar el estado de esta cuenta
void Account::displayStatus() const
{
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";"
			  << "amount:" << this->_amount << ";"
			  << "deposits:" << this->_nbDeposits << ";"
			  << "withdrawals:" << this->_nbWithdrawals << std::endl;
}

// Mostrar timestamp en el formato del log
void Account::_displayTimestamp()
{
	std::time_t		t = std::time(NULL);
	std::tm*		timePtr = std::localtime(&t);
	
	std::cout << "["
			  << (timePtr->tm_year + 1900)
			  << std::setfill('0') << std::setw(2) << (timePtr->tm_mon + 1)
			  << std::setfill('0') << std::setw(2) << timePtr->tm_mday
			  << "_"
			  << std::setfill('0') << std::setw(2) << timePtr->tm_hour
			  << std::setfill('0') << std::setw(2) << timePtr->tm_min
			  << std::setfill('0') << std::setw(2) << timePtr->tm_sec
			  << "] ";
}

// ************************************************************************** //
// vim: set ts=4 sw=4 tw=80 noexpandtab:                                      //
// ************************************************************************** //
