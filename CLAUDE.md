# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This repository contains C++ exercises following the C++98 standard, structured in numbered directories (00, 42, etc.) with subdirectories for individual exercises (ex00, ex01, ex02).

## Build System

All exercises use Makefiles with consistent targets:

- `make` or `make all` - Compile the program
- `make clean` - Remove object files
- `make fclean` - Remove object files and executable
- `make re` - Clean and rebuild from scratch

Each exercise directory has its own Makefile. Navigate to the specific exercise directory before building:
```bash
cd 00/ex00 && make     # Build megaphone
cd 00/ex01 && make     # Build phonebook
cd 00/ex02 && make     # Build account
```

## Compilation Standards

- Compiler: `c++`
- Flags: `-Wall -Wextra -Werror -std=c++98`
- Standard: C++98 (no C++11 or later features)

## Architecture

### Exercise Structure

**00/ex00 - Megaphone**: Single-file program (megaphone.cpp) demonstrating basic I/O.

**00/ex01 - PhoneBook**: Multi-class contact management system
- `Contact` class: Stores individual contact data with private fields (firstName, lastName, nickname, phoneNumber, darkestSecret)
  - Uses unified setter `setContact()` for efficiency instead of 5 individual setters
  - Self-displaying methods: `displaySummary()` and `displayDetails()`
  - Static `formatField()` helper for table formatting
- `PhoneBook` class: Manages array of 8 contacts with circular buffer behavior
  - Fixed-size array (not dynamic), replaces oldest when full
  - Tracks `contactCount` and `oldestIndex`
  - Private validation methods
- `main.cpp`: Command-line interface with ADD, SEARCH, EXIT commands

**00/ex02 - Account**: Bank account management system
- `Account` class: Implements static member tracking across instances
  - Static variables: `_nbAccounts`, `_totalAmount`, `_totalNbDeposits`, `_totalNbWithdrawals`
  - Instance variables: `_accountIndex`, `_amount`, `_nbDeposits`, `_nbWithdrawals`
  - Methods for deposits, withdrawals, and status display
  - Private `_displayTimestamp()` method
- `tests.cpp`: Provided test file

### Key Design Patterns

**Encapsulation**: Classes display themselves (Contact::displaySummary, Contact::displayDetails) rather than external display functions accessing private data.

**Const correctness**: Getters return `const std::string&` for efficiency. Display methods are const-qualified.

**Initialization lists**: Constructors use initialization lists (e.g., `PhoneBook::PhoneBook() : contactCount(0), oldestIndex(0)`) per C++98 best practices.

**Static members**: Account class demonstrates static variable tracking across all instances.

## Directory Structure

- Two main versions: `00/` and `42/` (appears to be different iterations or versions)
- Each contains ex00, ex01, ex02 subdirectories
- `00/docs/` contains reference implementations and tests

## Code Style

- Header guards using `#ifndef`/`#define` pattern
- 42 School header comments (copyright blocks)
- Private methods prefixed with underscore in Account class
- Use of `this->` pointer for member access
