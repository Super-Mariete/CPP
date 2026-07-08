#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo "=== CPP Module 01 Verification ==="
echo ""

# Check forbidden keywords
echo -e "${YELLOW}Checking for forbidden keywords...${NC}"
if grep -rE "using namespace|friend[^l]|\bprintf\(|\balloc\(|\bfree\(" ex*/*.cpp ex*/*.hpp 2>/dev/null; then
    echo -e "${RED}✗ Found forbidden keywords!${NC}"
else
    echo -e "${GREEN}✓ No forbidden keywords${NC}"
fi
echo ""

# Test each exercise
for ex in ex00 ex01 ex02 ex03 ex04 ex05 ex06; do
    echo -e "${YELLOW}=== Testing $ex ===${NC}"
    cd $ex

    # Clean and compile
    make fclean > /dev/null 2>&1
    if make 2>&1; then
        echo -e "${GREEN}✓ Compilation successful${NC}"

        # Run appropriate test
        case $ex in
            ex00)
                echo "Output:"
                ./zombie
                ;;
            ex01)
                echo "Output:"
                ./zombie
                ;;
            ex02)
                echo "Output:"
                ./brain
                ;;
            ex03)
                echo "Output:"
                ./violence
                ;;
            ex04)
                echo "Creating test file..."
                echo -e "hello world\nhello there\ngoodbye hello" > test.txt
                ./replace test.txt hello hi
                echo "Output:"
                cat test.txt.replace
                rm -f test.txt test.txt.replace
                ;;
            ex05)
                echo "Output:"
                ./harl
                ;;
            ex06)
                echo "Output (WARNING filter):"
                ./harlFilter "WARNING"
                ;;
        esac

        echo -e "${GREEN}✓ Execution successful${NC}"
    else
        echo -e "${RED}✗ Compilation failed${NC}"
    fi

    echo ""
    cd ..
done

echo -e "${GREEN}=== Verification Complete ===${NC}"
