#include "FileWithIncomes.h"

Income FileWithIncomes::getIncomeData(CMarkup xml)
{
    Income income;

    xml.IntoElem();

    xml.FindElem("IncomeId");
    MCD_STR strIncomeId = xml.GetData();
    income.setIncomeId(AuxiliaryMethods::convertStringToInt(strIncomeId));

    xml.FindElem("UserId");
    MCD_STR strUserId = xml.GetData();
    income.setUserId(AuxiliaryMethods::convertStringToInt(strUserId));

    xml.FindElem("Date");
    MCD_STR strDate = xml.GetData();
    income.setDate(DateManager::convertDateSeparatedDashesToInt(strDate));

    xml.FindElem("Item");
    MCD_STR strItem = xml.GetData();
    income.setItem(strItem);

    xml.FindElem("Amount");
    MCD_STR strAmount = xml.GetData();
    income.setAmount(AuxiliaryMethods::convertStringToDouble(strAmount));

    xml.OutOfElem();

    return income;
}

int FileWithIncomes::getLastIncomeIdFromFile(CMarkup xml)
{
    xml.ResetPos();
    xml.FindElem();
    xml.IntoElem();

    while (xml.FindElem("Income")) {}

    xml.IntoElem();
    xml.FindElem("IncomeId");
    MCD_STR strIncomeId = xml.GetData();

    return AuxiliaryMethods::convertStringToInt(strIncomeId);
}

void FileWithIncomes::addIncomeToFile(Income income)
{
    CMarkup xml;

    xml = loadFile();

    xml.FindElem();
    xml.IntoElem();
    xml.AddElem("Income");
    xml.IntoElem();
    xml.AddElem("IncomeId", income.getIncomeId());
    xml.AddElem("UserId", income.getUserId());
    xml.AddElem("Date", DateManager::convertIntDateToDateWithDashes(income.getDate()));
    xml.AddElem("Item", income.getItem());
    xml.AddElem("Amount", AuxiliaryMethods::saveTwoDecimalPlaces(income.getAmount()));

    xml.OutOfElem();
    xml.Save(getFileName());

    lastIncomeId++;
}

vector <Income> FileWithIncomes::loadIncomesOfLoggedInUserFromFile(int loggedInUserId)
{
    CMarkup xml;
    vector <Income> incomes;
    string userId = AuxiliaryMethods::convertIntToString(loggedInUserId);

    xml = loadFile();
    xml.FindElem();
    xml.IntoElem();

    while (xml.FindElem("Income"))
    {
        xml.FindChildElem("UserId");
        MCD_STR strUserId = xml.GetChildData();

        if (strUserId == userId)
        {
            incomes.push_back(getIncomeData(xml));
        }
    }
    lastIncomeId = getLastIncomeIdFromFile(xml);

    return incomes;
}

int FileWithIncomes::getLastIncomeId()
{
    return lastIncomeId;
}
