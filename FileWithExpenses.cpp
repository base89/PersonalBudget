#include "FileWithExpenses.h"

Expense FileWithExpenses::getExpenseData(CMarkup xml)
{
    Expense expense;

    xml.IntoElem();

    xml.FindElem("ExpenseId");
    MCD_STR strExpenseId = xml.GetData();
    expense.setExpenseId(AuxiliaryMethods::convertStringToInt(strExpenseId));

    xml.FindElem("UserId");
    MCD_STR strUserId = xml.GetData();
    expense.setUserId(AuxiliaryMethods::convertStringToInt(strUserId));

    xml.FindElem("Date");
    MCD_STR strDate = xml.GetData();
    expense.setDate(AuxiliaryMethods::convertStringToInt(strDate));

    xml.FindElem("Item");
    MCD_STR strItem = xml.GetData();
    expense.setItem(strItem);

    xml.FindElem("Amount");
    MCD_STR strAmount = xml.GetData();
    expense.setAmount(AuxiliaryMethods::convertStringToDouble(strAmount));

    xml.OutOfElem();

    return expense;
}

int FileWithExpenses::getLastExpenseIdFromFile(CMarkup xml)
{
    xml.FindElem();
    xml.IntoElem();

    while (xml.FindElem("Expense")) {}

    xml.IntoElem();

    xml.FindElem("ExpenseId");
    MCD_STR strExpenseId = xml.GetData();

    return AuxiliaryMethods::convertStringToInt(strExpenseId);
}

void FileWithExpenses::addExpenseToFile(Expense expense)
{
    CMarkup xml;

    xml = loadFile(getFileName());

    xml.FindElem();
    xml.IntoElem();
    xml.AddElem("Expense");
    xml.IntoElem();
    xml.AddElem("ExpenseId", expense.getExpenseId());
    xml.AddElem("UserId", expense.getUserId());
    xml.AddElem("Date", expense.getDate());
    xml.AddElem("Item", expense.getItem());
    xml.AddElem("Amount", expense.getAmount());

    xml.OutOfElem();
    xml.Save(getFileName() + ".xml");
}

vector <Expense> FileWithExpenses::loadExpensesOfLoggedInUserFromFile(int loggedInUserId)
{
    CMarkup xml;
    vector <Expense> expenses;
    string userId = AuxiliaryMethods::convertIntToString(loggedInUserId);

    xml = loadFile(getFileName());
    xml.FindElem();
    xml.IntoElem();

    while (xml.FindElem("Expense"))
    {
        xml.FindChildElem("UserId");
        MCD_STR strUserId = xml.GetChildData();

        if (strUserId == userId)
        {
            expenses.push_back(getExpenseData(xml));
        }
    }
    cout << "Loaded expenses from file. " << endl;

    return expenses;
}

int FileWithExpenses::getLastExpenseId()
{
    return lastExpenseId;
}
