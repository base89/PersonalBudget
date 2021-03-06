#ifndef AUXILIARYMETHODS_H
#define AUXILIARYMETHODS_H

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

class AuxiliaryMethods
{
public:
    static string convertIntToString(int number);
    static string convertDoubleToString(double number);
    static int convertStringToInt(string number);
    static double convertStringToDouble(string number);
    static string changeCommaForDot(string numberWithComma);
    static string saveTwoDecimalPlaces(double amount);
    static string changeFirstLetterForUpperCaseAndOthersForLowerCase(string text);
    static char loadChar();
    static int loadInteger();
    static string loadInputData();
};

#endif
