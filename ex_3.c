// (89110, Spring 2023, Assignment #3, Roie Amsalem, 322535436, roieams)
#include <stdio.h>

#define BADRESULT 2147483648
#define RIGHTSHIFT 10
#define MODULU 10
#define ARRAY_SIZE 48

//1
long long int evaluator(char expression);

void optionOne(void);

char cleanWhiteSpace(char nextChar);

//2
void buildBinary(int length, int binaryNum, int indexNum);

void printBinary(int binarySeq, int length);

void optionTwo(void);

//3
int countDigits(int num);

unsigned int returnPower(unsigned int num, int count, unsigned int mod, unsigned int value, int statcount);

unsigned int calculatePower(unsigned int mod, int count, unsigned int num);

void optionThree(void);

//4
void arr_Sort(double arr[ARRAY_SIZE], int count, unsigned int number, int temp);

void optionFour(void);

//5
int gridPaths(int width, int height);

int gridSteps(int width, int height, int right, int down);

void optionFive(void);

/**
 * @brief main function, holds the entire main menu and regulates answers from the user.
 *
 *@param trueWhile keeps the loop running until the user enters 0.
 * @param answer is the answer the user inputs to decide which option we commit to.
 * @param cleanBuffer is used throughout main() to clean the buffer.
 */
int main() {
    int trueWhile = 1;
    char answer, cleanBuffer;
    //A while loop that contains the main menu.
    while (trueWhile == 1) {
        printf("Choose an option:\n"
               "0. Exit\n"
               "1. Evaluator\n"
               "2. Binary strings\n"
               "3. Exciting number\n"
               "4. Cool number\n"
               "5. Count paths\n");
        // edge case where the user enters \n then a number. cleans the buffer.
        // cleaning the buffer and receiving answer from the user.
        scanf("%c", &answer);
        if (answer == '\n') {
            printf("Invalid option\n");
            continue;
        }
        scanf("%c", &cleanBuffer);
        if (answer > '6' || answer < '0') {
            printf("Invalid option\n");
            while (cleanBuffer != '\n') {
                scanf("%c", &cleanBuffer);
            }
        }
        // option 0 is exit.
        if (answer == '0') {
            // 'break;' to exit, 'continue;' for all other options.
            break;
            // option 1 is the first exercise.
        } else if (answer == '1') {
            optionOne();
            continue;
            // option 2 is the second exercise.
        } else if (answer == '2') {
            optionTwo();
            continue;
            // option 3 is the third exercise.
        } else if (answer == '3') {
            optionThree();
            continue;
            // option 4 is the fourth exercise.
        } else if (answer == '4') {
            optionFour();
            continue;
            // option 5 is the fifth exercise.
        } else if (answer == '5') {
            optionFive();
            continue;
        }
    }
}

/**
 * @brief optionOne() runs the process of exercise 1. checks if the expression is valid.
 *
 * @param value set to 0, more about it in the brief for evaluator() function.
 * @param count set to 0, more about it in the brief for evaluator() function.
 * @param counter set to 0, more about it in the brief for evaluator() function.
 * @param result calls the function evaluator() and receives the value of the expression from it and printed.
 * @param expression the expression input by the user.
 * @param cleanBuffer cleans the buffer.
 *
 * @return return if the character was invalid.
 */
void optionOne(void) {
    long long int result;
    char expression, cleanBuffer = '0';
    // scan expression's first character.
    printf("Enter an expression:\n");
    scanf("%c", &expression);
    // check expression's validity.
    if (expression != '(' && expression != ' ') {
        printf("Invalid expression\n");
        if (expression == '\n') {
            return;
        }
        scanf(" %c", &cleanBuffer);
        // If expression is invalid for its first char, clean the buffer and return to the main menu.
        while (cleanBuffer != '\n') {
            scanf("%c", &cleanBuffer);
        }
        return;
    }
    //result calls evaluator to calculate the value of the given expression.
    result = evaluator(expression);
    //if the value returned is BADRESULT, which is the maximum size of int + 1, we had an invalid expression.
    if (result == BADRESULT) {
        printf("Invalid expression\n");
        //iteratively clean the buffer until we hit \n.
        while (cleanBuffer != '\n') {
            scanf("%c", &cleanBuffer);
        }
        return;
    } else {
        // else we have a good result, print it and exit the function.
        printf("The value is %lld\n", result);
    }
}

/**
 * @brief evaluator() function recursively checks arithmetic operations on the numbers withing expression and calculates
 *I tried to narrow it and split it into 5 functions (4 arithmatic operators and 1 major 1) but it didn't work.
 * Tried some other function splits as well but nothing wokred, it is longer than 40 lines I didn't manage to make it shorter...
 * If it makes the checking of it harder I apologize.
 * @param expression takes in the expression from the user as type char 1 at a time.
 * @return return value for when we finished.
 * return evaluator() for the recursive call going inside-out of the expression, left to right.
 */
long long evaluator(char expression) {
    //ascii difference constant.
    const int asciiNum = 48;
    //Initialize the value to 0.
    long long value = 0;
    //Declare the variable for the next character to be read.
    char nextChar;
    //If the input expression is a digit, add its value to the total.
    if (expression >= '0' && expression <= '9') {
        value += expression - asciiNum;
    }
    //Continue reading the input expression until the end of the line or a closing parenthesis is reached.
    while (expression != '\n' && expression != ')') {
        //Read in the next character.
        scanf("%c", &nextChar);
        //Clean up any whitespace characters using cleanWhiteSpace(nextChar), returning nextChar.
        nextChar = cleanWhiteSpace(nextChar);
        //If the current character is an opening parenthesis, recursively
        //evaluate the expression inside the parentheses and add it to the total value.
        if (expression == '(') {
            value += evaluator(nextChar);
        //If the current character is a digit, check the next character to
        //determine the appropriate operation to perform.
        } else if (expression >= '0' && expression <= '9') {
            //If the next character is another digit or an opening parenthesis, return an error.
            if (((nextChar >= '0') && (nextChar <= '9')) || (nextChar == '(')) {
                return BADRESULT;
            }
            //If the next character is a closing parenthesis, return the total value.
            if (nextChar == ')') {
                return value;
            }
            //Otherwise, perform the appropriate arithmetic operation based on the next character.
            else if (nextChar == '+') {
                scanf("%c", &nextChar);
                nextChar = cleanWhiteSpace(nextChar);
                //If the next character is an opening parenthesis, recursively
                //evaluate the expression inside the parentheses and add it to the total value.
                if (nextChar == '(') {
                    scanf("%c", &nextChar);
                    nextChar = cleanWhiteSpace(nextChar);
                    value += evaluator(nextChar);
                //If the next character is a digit, add its value to the total.
                } else if ((nextChar >= '0') && (nextChar <= '9')) {
                    value += (nextChar - asciiNum);
                } else {
                    //If the next character is anything else, return an error.
                    return BADRESULT;
                }
            } else if (nextChar == '-') {
                scanf("%c", &nextChar);
                nextChar = cleanWhiteSpace(nextChar);
                //If the next character is an opening parenthesis, recursively
                //evaluate the expression inside the parentheses and subtract it from the total value.
                if (nextChar == '(') {
                    scanf("%c", &nextChar);
                    nextChar = cleanWhiteSpace(nextChar);
                    value -= evaluator(nextChar);
                //If the next character is a digit, subtract its value from the total.
                } else if ((nextChar >= '0') && (nextChar <= '9')) {
                    value -= (nextChar - asciiNum);
                } else {
                    //If the next character is anything else, return an error.
                    return BADRESULT;
                }
            } else if (nextChar == '*') {
                scanf("%c", &nextChar);
                nextChar = cleanWhiteSpace(nextChar);
                //If the next character is an opening parenthesis, recursively
                //evaluate the expression inside the parentheses and multiply it by the total value.
                if (nextChar == '(') {
                    scanf("%c", &nextChar);
                    nextChar = cleanWhiteSpace(nextChar);
                    value *= evaluator(nextChar);
                //If the next character is a digit, multiply its value by the total.
                } else if ((nextChar >= '0') && (nextChar <= '9')) {
                    value *= (nextChar - asciiNum);
                } else {
                    //If the next character is anything else, return an error.
                    return BADRESULT;
                }
            } else if (nextChar == '/') {
                scanf("%c", &nextChar);
                nextChar = cleanWhiteSpace(nextChar);
                //If the next character is an opening parenthesis, recursively
                //evaluate the expression inside the parentheses and divide it by the total value.
                if (nextChar == '(') {
                    scanf("%c", &nextChar);
                    nextChar = cleanWhiteSpace(nextChar);
                    value /= evaluator(nextChar);
                //If the next character is a digit, divide its value by the total.
                } else if ((nextChar >= '0') && (nextChar <= '9') && (nextChar - asciiNum != 0)) {
                    value /= (nextChar - asciiNum);
                } else {
                    //If the next character is anythingg else, return an error.
                    return BADRESULT;
                }
            }
        } else {
            //If the expression isn't a digit, return an error.
            return BADRESULT;
        }
        // Pass nextChar to expression.
        expression = nextChar;
    }
    return value;
}
/**
 * @brief cleans whitespaces from nextChar in evaluator().
 * @param nextChar the nextChar variable from evaluator()
 * @return nextChar, the next relevant char to the calculation.
 */
char cleanWhiteSpace(char nextChar){
    // While nextChar is a ' ', loop through the buffer and clean it.
    while (nextChar == ' '){
        scanf("%c", &nextChar);
    }
    // when nextChar != ' ' return whatever we got to nextChar.
    return nextChar;
}

/**
 * @brief optionTwo() runs the process of exercise 2.
 *
 * Checks if length is valid and calls the buildBinary function.
 * @param length The length of the binary sequences we will print. Entered by the user.
 * @param starter Just a value for the bit in index 0 to start from.
 * @param MAXINT,MININT The maximum and minimum values for length.
 * @param cleanBuffer Cleans the buffer.
 */
void optionTwo(void) {
    int length, starter = 0, MAXINT = 32, MININT = 1;
    char cleanBuffer;
    // Receiving input length from the user.
    printf("Enter length:\n");
    scanf("%d", &length);
    // Checking if length is valid, if not return to menu.
    if (length > MAXINT || length < MININT) {
        // Cleaning the buffer.
        scanf("%c", &cleanBuffer);
        printf("Invalid length\n");
        return;
    }
    // Calling function buildBinary.
    buildBinary(length, starter, starter);
    // Cleaning the buffer.
    scanf("%c", &cleanBuffer);
}

/**
 * @brief Function buildBinary recursively creates 1 valid binary sequence at a time.
 *
 * @param length The length of the binary sequences we will print.
 * @param binaryNum The binary sequence number.
 * @param index The current index of the binary sequence.
 */
void buildBinary(int length, int binaryNum, int index) {
    // Checking if we reached the (index) number in each binary sequence we build.
    if (length == index) {
        // If we did, call printBinary to print the binary sequence recursively.
        printBinary(binaryNum, length);
        printf("\n");
        return;
    }
    // If length != index, left shift binaryNum to make space, index + 1 closing in on length.
    buildBinary(length, binaryNum << 1, index + 1);
    // Recursively checking if we should append a 1 or a 0. Skipping recurse when binaryNum & 1 == 1.
    if ((binaryNum & 1) == 0) {
        buildBinary(length, binaryNum << 1 | 1, index + 1);
    }
}

/**
 * @brief Function printBinary prints the binary sequence recursively.
 *
 * @param binarySeq The binary sequence number.
 * @param length The length of the binary sequences we will print.
 */
void printBinary(int binarySeq, int length) {
    // If length == 0 we finished printing the current sequence.
    if (length == 0) {
        // Return to buildBinary.
        return;
    }
    // Recursively calling printBinary to print the sequence, right-shifting binarySeq >> 1 and length - 1 until it reaches 0.
    printBinary(binarySeq >> 1, length - 1);
    // Checking if the least significant bit in binarySeq is 1 or 0 and printing accordingly.
    if (binarySeq & 1) {
        printf("%d", (binarySeq & 1));
    } else {
        printf("%d", (binarySeq & 0));
    }
}

/**
 * @brief Checks if a number is "exciting" or not.
 *
 * A positive integer is said to be "exciting" if it is the sum of the powers of its digits.
 * This function prompts the user to enter a natural number, checks if it is exciting, and
 * prints an appropriate message to the console.
 */
void optionThree(void) {
    //unsigned number and result according to exercise guidelines.
    unsigned int number, result, notMinus = 0;
    //count the amount of digits for the power calculation.
    int count;
    //used to clean the buffer.
    char cleanBuffer;
    printf("Enter a natural number:\n");
    //user inputs number.
    scanf("%u", &number);
    //count receives the amount of digits back.
    count = countDigits(number);
    // calling returnPower through result to calculate the combined digits to the power of count.
    result = returnPower(number, count, number % RIGHTSHIFT, 0, count);
    //checking if the number is exciting according to the definition of an exciting number.
    if (number == result && number >= notMinus) {
        printf("The number is exciting\n");
    } else {
        printf("The number is not exciting\n");
    }
    //clean buffer.
    scanf("%c", &cleanBuffer);
}

/**
 * @brief Counts the number of digits in a given integer.
 *
 * This function recursively counts the number of digits in a given integer using right shifting.
 *
 * @param num The integer whose digits are to be counted.
 * @return The number of digits in the integer.
 */
int countDigits(int num) {
    // when num == 0 we counted enough and return 0.
    if (num == 0) {
        return 0;
    } else {
        // else return 1 + another recursive call to count, now with num / 10.
        return 1 + countDigits(num / RIGHTSHIFT);
    }
}

/**
 * @brief Calculates the sum of the powers of the digits of a given integer.
 *
 * This function recursively calculates the sum of the powers of the digits of a given integer.
 *
 * @param num The integer whose digits' powers are to be summed.
 * @param count The number of digits in the integer.
 * @param mod The last digit of the integer.
 * @param value The current value of the sum of powers.
 * @param statcount The initial number of digits in the integer.
 * @return The sum of the powers of the digits of the integer.
 */
unsigned int returnPower(unsigned int num, int count, unsigned int mod, unsigned int value, int statcount) {
    // stop condition. count is 0 so we recursively summated enough elements and can return value.
    if (count == 0) {
        return value;
    } else {
        // else calculate value = value + calculatePower. each time after num /= 10.
        value += calculatePower(mod, statcount, num);
        // rightshifting num's digits by 1.
        num /= RIGHTSHIFT;
        // return for the summation. count - 1 until we reach 0.
        return returnPower(num, count - 1, num % MODULU, value, statcount);
    }
}

/**
 * @brief Calculates the power of a given number to a given exponent.
 *
 * This function recursively calculates the power of a given number to a given exponent.
 *
 * @param mod The base number.
 * @param count The exponent.
 * @param num The original number before right shifting.
 * @return The power of the base number to the given exponent.
 */
unsigned int calculatePower(unsigned int mod, int count, unsigned int num) {
    // if we reached count == 1, return modulu and start the recursive calculation. stop condition.
    if (count == 1) {
        return mod;
    } else {
        //if num is single digit, return it.
        if (num / RIGHTSHIFT == 0 && count < 2) {
            return num;
        }
    }
    // the recursive call to calculate the power of each digit according to count.
    return mod * calculatePower(mod, count - 1, num);
}

/**
 * @brief Calculates the coolness of a natural number
 *
 * This function prompts the user to input a natural number and calculates
 * its coolness using an algorithm based on its digits. The coolness of a number
 * is determined by finding if there exists a sequence of digits such that the
 * sum of any two adjacent digits equals the next digit in the sequence.
 *
 * @return void
 */
void optionFour(void) {
    //number for the number input. arr[] for the array. ARRAY_SIZE = 48, because looking at finobacchi I realised
    //it is the series with the largest amount of elements smaller than the max size of unsigned int. meaning it takes the longest to reach it.
    // the 48th element of fibonacchi is the first one to be larger than MAX UNSIGNED INT, and that's what I went with.
    double number, arr[ARRAY_SIZE];
    //count uses countDigits from exercise 3 to check the amount of digits. temp for holding temporary array elements.
    int count, temp = 0;
    //cleans the buffer.
    char cleanBuffer;
    printf("Enter a natural number:\n");
    // receiving number as user input.
    scanf("%lf", &number);
    // counting the digits in number.
    count = countDigits(number);
    // calling arr_Sort.
    arr_Sort(arr, count, number, temp);
    //clean buffer.
    scanf("%c", &cleanBuffer);
}

/**
 * @brief Sorts the digits of a number and checks its coolness
 *
 * This function takes a natural number and sorts its digits in an array. It then
 * calculates the coolness of the number by finding if there exists a sequence of
 * digits such that the sum of any two adjacent digits equals the next digit in the
 * sequence. The coolness of the number is determined by comparing its sum to the
 * calculated sum.
 *
 * @param arr Array to store the digits of the number
 * @param count Number of digits in the number
 * @param number Natural number to check for coolness
 * @param temp Temporary variable for sorting
 * @return void
 */
void arr_Sort(double arr[ARRAY_SIZE], int count, unsigned int number, int temp) {
    //holding number in keepNum.
    double keepNum = number;
    // for loop to rearrange the array so for the number 14 the array is: (1,4,...) and not: (4,1,...)
    for (int j = count; j > 0; j--) {
        temp = number % MODULU;
        number /= RIGHTSHIFT;
        arr[j] = temp;
    }
    //inserting 0s to all array indexes larger than count.
    for (int j = ARRAY_SIZE; j > count; j--) {
        arr[j] = 0;
    }
    //for loop to add elements n-1 + ... + n-count and insert the result to the element in position n.
    for (int i = count + 1; i < ARRAY_SIZE; i++) {
        // j = i - 1 in each iteration. i is count + 1 so j == count.
        int j = i - 1;
        // a while loop. i - count is the amount of elements we need to sum and their indexes.
        while (j >= i - count) {
            //summation of the elements iteratively together until we have the new element n.
            arr[i] += arr[j];
            j--;
        }
        //after finding each new element in index n, check if it is equal to keepNum, aka, the original input the user gave.
        if (arr[i] == keepNum) {
            // if condition is true the number is cool. end the program.
            printf("The number is cool\n");
            break;
        } else if (arr[i] > keepNum) {
            //if we have an element bigger than keepNum end the program. number is not cool.
            printf("The number is not cool\n");
            break;
        }
    }
}

/**
 * @brief Calculates the number of paths in a grid
 *
 * This function prompts the user to enter the width and height of a grid and
 * calculates the number of unique paths that can be taken from the top-left
 * corner to the bottom-right corner. The paths can only move right or down.
 *
 * @return void
 */
void optionFive(void) {
    //width and height serve as the grid's width and height inputs.
    unsigned int width, height;
    //cleans the buffer.
    char cleanBuffer;
    printf("Enter width and height:\n");
    //receive input of width and height.
    scanf("%d%d", &width, &height);
    //call to gridpaths through printf, the resulting number of paths will be printed.
    printf("The number of paths is %u\n", gridPaths(width, height));
    //clean buffer
    scanf("%c", &cleanBuffer);
}

/**
 * @brief Computes the number of paths in a grid from top-left corner to bottom-right corner.
 *
 * @param width The width of the grid.
 * @param height The height of the grid.
 * @param right The number of steps taken right in the current path.
 * @param down The number of steps taken down in the current path.
 *
 * @return The number of paths in the grid.
 */
int gridSteps(int width, int height, int right, int down) {
    //Amount of steps allowed to be taken by the puppy, down or right.
    const int steps = 3;
    //If puppy went 3 steps right or down, return 0 for that path.
    if (right == steps || down == steps) {
        return 0;
    }
    //If we reached all the way to a (1,1) grid return 1 through the recursive call.
    if (width == 1 && height == 1) {
        return 1;
    }
    //Stop condition for width/height == 0, meaning we crossed the grid;
    if (width <= 0 || height <= 0) {
        return 0;
    }
    // The recursive call to calculate once with width - 1 and right + 1, once with height - 1 down + 1.
    return gridSteps(width - 1, height, right + 1, 0) +
           gridSteps(width, height - 1, 0, down + 1);
}

/**
 * @brief Computes the number of paths in a grid from top-left corner to bottom-right corner.
 *
 * @param width The width of the grid.
 * @param height The height of the grid.
 *
 * @return The number of paths in the grid.
 */
int gridPaths(int width, int height) {
    //Stop condition.
    if (width <= 0 || height <= 0) {
        //return value of paths 0.
        return 0;
    }
    //valid option sent to gridSteps().
    return gridSteps(width, height, 0, 0);
}
