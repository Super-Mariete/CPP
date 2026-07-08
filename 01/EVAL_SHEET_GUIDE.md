# CPP Module 01 - Official Evaluation Guide
## Based on Official 42 Evaluation Sheet

---

## 🎯 **PRELIMINARY TESTS**

### **Prerequisites**

**Check these BEFORE starting evaluation:**

#### ✅ **Compilation Requirements**
```bash
# Must compile with these exact flags
c++ -Wall -Wextra -Werror -std=c++98
```

#### ❌ **INSTANT FAIL if:**
- Function implemented in header (except templates)
- Makefile doesn't use required flags
- Makefile uses compiler other than `c++`

#### ❌ **"Forbidden Function" FLAG if:**
- Uses C functions: `*alloc`, `*printf`, `free`
- Uses function not allowed in guidelines
- Uses `using namespace <ns_name>`
- Uses `friend` keyword
- Uses external library or features other than C++98

---

## 📝 **EXERCISE 00: BraiiiiiiinnnzzzZ**

### **Check 1: Makefile and tests**

**Verification:**
```bash
cd ex00
make
```

**Requirements:**
- ✅ Makefile compiles with appropriate flags
- ✅ At least one main to test

**Pass:** ☐ Yes ☐ No

---

### **Check 2: Zombie Class**

**Verification:**
```bash
# Check files exist
ls Zombie.hpp Zombie.cpp

# Read class definition
cat Zombie.hpp
```

**Requirements:**
- ✅ Zombie class exists
- ✅ Private `name` attribute
- ✅ At least one constructor
- ✅ Member function `announce()` that prints: `<name>: BraiiiiiiinnnzzzZ...`
- ✅ Destructor prints debug message with zombie name

**Test:**
```bash
./zombie
```

**Expected output includes:**
```
<name>: BraiiiiiiinnnzzzZ...
<name> is destroyed  (or similar destructor message)
```

**Pass:** ☐ Yes ☐ No

---

### **Check 3: newZombie**

**Verification:**
```bash
# Check function exists
grep "newZombie" *.cpp
```

**Requirements:**
- ✅ Function prototype: `Zombie* newZombie(std::string name);`
- ✅ Allocates Zombie on the HEAP
- ✅ Returns pointer to Zombie
- ✅ Ideally: calls constructor with name parameter
- ✅ Zombie can announce itself with correct name
- ✅ Tests prove functionality
- ✅ Zombie is deleted before program ends

**Test questions for student:**
- "Where is this zombie allocated?" (Answer: Heap)
- "Why return a pointer?" (Answer: So it can be used outside function scope)
- "Show me where you delete it" (Should show `delete zombie;`)

**Pass:** ☐ Yes ☐ No

---

### **Check 4: randomChump**

**Verification:**
```bash
# Check function exists
grep "randomChump" *.cpp
```

**Requirements:**
- ✅ Function prototype: `void randomChump(std::string name);`
- ✅ Creates Zombie on stack (or heap and deletes it)
- ✅ Makes zombie announce itself
- ✅ Ideally: allocated on stack (implicitly deleted)
- ✅ **Student must justify their choice**
- ✅ Tests prove functionality

**Questions for student:**
- "Where did you allocate this zombie?" (Stack or Heap)
- "Why did you choose that?"
  - Stack: Automatic destruction, only needed in function
  - Heap: Must manually delete but explicit control

**Pass:** ☐ Yes ☐ No

---

## 📝 **EXERCISE 01: Moar brainz!**

### **Check 1: Makefile and tests**

**Verification:**
```bash
cd ex01
make
```

**Requirements:**
- ✅ Makefile compiles with appropriate flags
- ✅ At least one main to test

**Pass:** ☐ Yes ☐ No

---

### **Check 2: zombieHorde**

**Verification:**
```bash
# Check class has default constructor
grep -A 3 "Zombie()" Zombie.hpp

# Check zombieHorde function
cat zombieHorde.cpp
```

**Requirements:**
- ✅ Zombie class has default constructor
- ✅ Function prototype: `Zombie* zombieHorde(int N, std::string name);`
- ✅ Allocates N zombies using `new[]`
- ✅ After allocation, initializes objects with name
- ✅ Returns pointer to first zombie
- ✅ Main calls `announce()` on all zombies
- ✅ All zombies deleted at same time with `delete[]`

**Critical check:**
```bash
# Run and verify
./zombie

# Check for delete[]
grep "delete\[\]" main.cpp
```

**Questions for student:**
- "Show me where you use `new[]`"
- "Show me where you use `delete[]`"
- "Why `delete[]` and not `delete`?" (Answer: Array allocation needs array delete)

**Memory leak check:**
```bash
# On macOS
leaks -atExit -- ./zombie

# On Linux
valgrind --leak-check=full ./zombie
```

**Pass:** ☐ Yes ☐ No

---

## 📝 **EXERCISE 02: HI THIS IS BRAIN**

### **Check 1: Makefile and tests**

**Verification:**
```bash
cd ex02
make
```

**Requirements:**
- ✅ Makefile compiles with appropriate flags
- ✅ At least one main to test

**Pass:** ☐ Yes ☐ No

---

### **Check 2: HI THIS IS BRAIN**

**Verification:**
```bash
# Read main
cat main.cpp

# Run program
./brain
```

**Requirements:**
- ✅ String containing "HI THIS IS BRAIN"
- ✅ `stringPTR` is pointer to string
- ✅ `stringREF` is reference to string
- ✅ Displays address of string using:
  - Original variable
  - stringPTR
  - stringREF
- ✅ Displays value using:
  - stringPTR (with `*`)
  - stringREF (direct)

**Expected output:**
```
Address of brain:       0x...
Address in stringPTR:   0x...  (same!)
Address of stringREF:   0x...  (same!)

Value of brain:         HI THIS IS BRAIN
Value pointed by PTR:   HI THIS IS BRAIN
Value pointed by REF:   HI THIS IS BRAIN
```

**Questions for student:**
- "Are the three addresses the same?" (Yes)
- "What's the difference between pointer and reference?"
  - Reference: alias, cannot be NULL, cannot reassign
  - Pointer: address, can be NULL, can reassign

**Pass:** ☐ Yes ☐ No

---

## 📝 **EXERCISE 03: Unnecessary violence**

### **Check 1: Makefile and tests**

**Verification:**
```bash
cd ex03
make
```

**Requirements:**
- ✅ Makefile compiles with appropriate flags
- ✅ At least one main to test

**Pass:** ☐ Yes ☐ No

---

### **Check 2: Weapon**

**Verification:**
```bash
# Check Weapon class
cat Weapon.hpp
```

**Requirements:**
- ✅ Weapon class exists
- ✅ Has private `type` string
- ✅ Has `getType()` - returns `const` reference to type
- ✅ Has `setType()` - sets type

**Critical check:**
```cpp
// In Weapon.hpp, should see:
const std::string& getType() const;
```

**Pass:** ☐ Yes ☐ No

---

### **Check 3: HumanA and HumanB**

**Verification:**
```bash
# Check HumanA
cat HumanA.hpp

# Check HumanB
cat HumanB.hpp

# Run test
./violence
```

**Requirements:**

#### **HumanA:**
- ✅ Can have reference OR pointer to Weapon
- ✅ **Ideally:** Should be reference (weapon exists from creation to destruction)
- ✅ Weapon set in constructor

#### **HumanB:**
- ✅ **MUST** have pointer to Weapon
- ✅ Weapon NOT set at creation
- ✅ Weapon can be NULL
- ✅ Has `setWeapon()` function

**Expected output:**
```
Bob attacks with their crude spiked club
Bob attacks with their some other type of club
Jim attacks with their crude spiked club
Jim attacks with their some other type of club
```

**Questions for student:**
- "Why did HumanA use reference/pointer?"
  - Reference: Always has weapon, set in constructor
- "Why did HumanB use pointer?"
  - Pointer: May not have weapon, can be NULL

**Pass:** ☐ Yes ☐ No

---

## 📝 **EXERCISE 04: Sed is for losers**

### **Check 1: Makefile and tests**

**Verification:**
```bash
cd ex04
make
```

**Requirements:**
- ✅ Makefile compiles with appropriate flags
- ✅ At least one main to test

**Pass:** ☐ Yes ☐ No

---

### **Check 2: Exercise 04**

**Verification:**
```bash
# Create test file
echo -e "hello world\nhello there\ngoodbye hello" > test.txt

# Run program
./replace test.txt hello hi

# Check output
cat test.txt.replace
```

**Requirements:**
- ✅ Function `replace()` (or similar name) works as specified
- ✅ Error management is efficient:
  - File doesn't exist
  - No read permissions
  - Empty file
  - etc.
- ✅ Uses `ifstream` or equivalent to read
- ✅ Uses `ofstream` or equivalent to write
- ✅ Uses `std::string` functions (NOT character by character)
- ✅ **NOT C anymore!** Must use C++ file streams

**Error tests to try:**
```bash
# File doesn't exist
./replace nonexistent.txt hello hi

# Empty s1
./replace test.txt "" hi

# s1 not in file
./replace test.txt xyz abc
```

**Critical check:**
```bash
# Must NOT use std::string::replace()
grep "\.replace(" *.cpp
# Should return nothing or commented lines only
```

**If you find unhandled error that isn't esoteric → NO POINTS**

**Questions for student:**
- "Show me how you read the file"
- "Show me how you replace strings"
- "Did you use `std::string::replace()`?" (Should be NO)

**Pass:** ☐ Yes ☐ No

---

## 📝 **EXERCISE 05: Harl 2.0**

### **Check 1: Makefile and tests**

**Verification:**
```bash
cd ex05
make
```

**Requirements:**
- ✅ Makefile compiles with appropriate flags
- ✅ At least one main to test

**Pass:** ☐ Yes ☐ No

---

### **Check 2: Our beloved Harl**

**Verification:**
```bash
# Check Harl class
cat Harl.hpp Harl.cpp

# Run program
./harl
```

**Requirements:**
- ✅ Harl class with at least 5 functions:
  - `debug()`
  - `info()`
  - `warning()`
  - `error()`
  - `complain()`
- ✅ `complain()` executes other functions using **pointer to member function**
- ✅ Ideally: matches strings to function pointers
- ✅ **NOT ALLOWED:** ugly if/elseif/else forest
- ✅ Messages can be custom or from subject (both valid)

**Critical check - Must use pointers to member functions:**
```cpp
// In Harl.cpp, should see something like:
void (Harl::*functionPtr)(void) = &Harl::debug;

// Or array:
void (Harl::*functions[4])(void) = {
    &Harl::debug,
    &Harl::info,
    &Harl::warning,
    &Harl::error
};
```

**NOT allowed:**
```cpp
// ❌ This is NOT acceptable:
if (level == "DEBUG")
    debug();
else if (level == "INFO")
    info();
else if (level == "WARNING")
    warning();
else if (level == "ERROR")
    error();
```

**Expected output:**
```
[ DEBUG ]
I love having extra bacon...

[ INFO ]
I cannot believe...

[ WARNING ]
I think I deserve...

[ ERROR ]
This is unacceptable...
```

**Questions for student:**
- "Show me where you use pointers to member functions"
- "Why not use if/else?" (Answer: Subject requires function pointers, more elegant)

**Pass:** ☐ Yes ☐ No

---

## 📝 **EXERCISE 06: Harl filter (BONUS)**

### **Check 1: Makefile and tests**

**Verification:**
```bash
cd ex06
make
```

**Requirements:**
- ✅ Makefile compiles with appropriate flags
- ✅ At least one main to test
- ✅ Executable named `harlFilter`

**Pass:** ☐ Yes ☐ No

---

### **Check 2: Switching Harl Off**

**Verification:**
```bash
# Test different levels
./harlFilter "DEBUG"
echo "---"
./harlFilter "INFO"
echo "---"
./harlFilter "WARNING"
echo "---"
./harlFilter "ERROR"
echo "---"
./harlFilter "INVALID"
```

**Requirements:**
- ✅ Takes log level as argument: DEBUG, INFO, WARNING, ERROR
- ✅ Displays messages at same level and above
- ✅ Order: DEBUG < INFO < WARNING < ERROR
- ✅ **MUST use switch statement**
- ✅ Has default case
- ✅ **NO if/elseif/else**

**Critical check - Must use switch:**
```cpp
// In main.cpp, should see:
switch (levelIndex) {
    case 0:  // DEBUG
        // ...
        // NO break (fall-through)
    case 1:  // INFO
        // ...
        // NO break (fall-through)
    case 2:  // WARNING
        // ...
        // NO break (fall-through)
    case 3:  // ERROR
        // ...
        break;
    default:
        // ...
}
```

**Expected outputs:**

`./harlFilter "WARNING"`:
```
[ WARNING ]
I think I deserve...

[ ERROR ]
This is unacceptable...
```

`./harlFilter "DEBUG"`:
```
[ DEBUG ]
...

[ INFO ]
...

[ WARNING ]
...

[ ERROR ]
...
```

`./harlFilter "INVALID"`:
```
[ Probably complaining about insignificant problems ]
```

**Questions for student:**
- "Show me the switch statement"
- "Why no `break` between cases?" (Answer: Fall-through to show all levels above)

**Pass:** ☐ Yes ☐ No

---

## 🏁 **FINAL CHECKLIST**

### **Compilation & Style**

- [ ] All exercises compile with `-Wall -Wextra -Werror -std=c++98`
- [ ] No compilation warnings
- [ ] Makefiles have: `all`, `clean`, `fclean`, `re`
- [ ] No relinking when running `make` twice
- [ ] Include guards in all `.hpp` files

### **Forbidden Items**

- [ ] No `using namespace`
- [ ] No `friend` keyword
- [ ] No C functions (`*printf`, `*alloc`, `free`)
- [ ] No C++11 or later features
- [ ] No external libraries
- [ ] No STL (this is module 01)

### **Memory Management**

- [ ] No memory leaks (check with valgrind/leaks)
- [ ] Proper use of `delete` vs `delete[]`
- [ ] All heap allocations are freed

### **Code Quality**

- [ ] Code is readable and well-organized
- [ ] Student can explain their code
- [ ] Proper use of references vs pointers
- [ ] File streams used correctly

---

## ⭐ **RATING FLAGS**

### **Positive Flags:**
- ☐ **Ok** - Project meets requirements
- ☐ **Outstanding project** - Exceptional work, extra tests, perfect understanding

### **Negative Flags:**
- ☐ **Empty work** - Nothing turned in
- ☐ **Incomplete work** - Missing exercises
- ☐ **Invalid compilation** - Doesn't compile
- ☐ **Cheat** - Plagiarism detected
- ☐ **Crash** - Program crashes
- ☐ **Concerning situation** - Other serious issues
- ☐ **Leaks** - Memory leaks detected
- ☐ **Forbidden function** - Uses prohibited functions
- ☐ **Can't support/explain code** - Can't explain implementation

---

## 📊 **GRADING SUMMARY**

| Exercise | Max Points | Points Earned |
|----------|------------|---------------|
| ex00 | Mandatory | |
| ex01 | Mandatory | |
| ex02 | Mandatory | |
| ex03 | Mandatory | |
| ex04 | Mandatory | |
| ex05 | Mandatory | |
| ex06 | Bonus | |

**Final Grade:** ___ / 100

**Flag:** _____________

**Comments:**
```
[Write detailed comments about the evaluation]
```

---

## 💡 **TIPS FOR EVALUATORS**

1. **Be thorough but fair** - Check all requirements but understand different approaches
2. **Ask questions** - Verify student understands their code
3. **Test edge cases** - Empty files, NULL pointers, memory leaks
4. **Check critical requirements:**
   - ex01: Must use `new[]` and `delete[]`
   - ex03: HumanB must use pointer
   - ex04: No `std::string::replace()`
   - ex05: Must use pointers to member functions
   - ex06: Must use switch statement
5. **Memory leaks = Leaks flag** - Use valgrind/leaks
6. **Forbidden functions = -42** - Check carefully

---

**Good luck with your evaluation!** ⭐

