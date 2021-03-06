#ifndef FILEWITHEXPENSES_H
#define FILEWITHEXPENSES_H

#include <iostream>
#include <vector>

#include "Expense.h"
#include "TextFile.h"
#include "AuxiliaryMethods.h"
#include "DateManager.h"

using namespace std;

class FileWithExpenses : public TextFile
{
    int lastExpenseId;

    Expense getExpenseData(CMarkup xml);
    int getLastExpenseIdFromFile(CMarkup xml);

public:
    FileWithExpenses(string fileNameWithExpenses) : TextFile (fileNameWithExpenses)
    {
        lastExpenseId = 0;
    }

    void addExpenseToFile(Expense expense);
    vector <Expense> loadExpensesOfLoggedInUserFromFile(int loggedInUserId);
    int getLastExpenseId();
};

#endif
