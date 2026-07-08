#!/bin/bash

echo "=== CPP Module 02 Verification ==="
echo ""

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Check forbidden keywords
echo -e "${YELLOW}Checking for forbidden keywords...${NC}"
if grep -r "using namespace\|friend" ex*/*.cpp ex*/*.hpp 2>/dev/null; then
    echo -e "${RED}✗ Found forbidden keywords!${NC}"
else
    echo -e "${GREEN}✓ No forbidden keywords${NC}"
fi

# Test each exercise
for ex in ex00 ex01 ex02 ex03; do
    echo ""
    echo -e "${YELLOW}=== Testing $ex ===${NC}"
    cd $ex

    # Clean and compile
    make fclean > /dev/null 2>&1
    if make 2>&1; then
        echo -e "${GREEN}✓ Compilation successful${NC}"

        # Run test
        echo "Output:"
        if [ "$ex" = "ex00" ]; then
            ./fixed
        elif [ "$ex" = "ex01" ]; then
            ./fixed
        elif [ "$ex" = "ex02" ]; then
            ./fixed
        elif [ "$ex" = "ex03" ]; then
            ./bsp
        fi

        echo -e "${GREEN}✓ Execution successful${NC}"
    else
        echo -e "${RED}✗ Compilation failed${NC}"
    fi

    cd ..
done

echo ""
echo -e "${GREEN}=== Verification Complete ===${NC}"
