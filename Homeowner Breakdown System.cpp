// Homeowner Breakdown System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <istream>
#include <string>
class Person {
private:
    std::string m_sName;
    double m_dMonthlyIncome;
    
public:
    Person() :m_sName{ "" }, m_dMonthlyIncome{ 0 }{}
    Person(std::string sName, double dMonthlyIncome) :
        m_sName{ sName }, m_dMonthlyIncome{ dMonthlyIncome }
    {}
    void set_name(std::string sName) {
        m_sName = sName;
    }
    void set_monthly_income(double dMonthlyIncome) {
        m_dMonthlyIncome = dMonthlyIncome;
    }
    std::string get_name() const { return m_sName; }
    double get_monthly_salary() const { return m_dMonthlyIncome; }
};

class Outgoing {
private:
    std::string m_sName;
    double m_dCostPerMonth;
public:
    Outgoing() :m_sName{ "" }, m_dCostPerMonth{ 0 }{}
    Outgoing(std::string sName, double dCostPerMonth) :m_sName{ sName }, m_dCostPerMonth{dCostPerMonth} {}
    std::string get_outgoing_name() const { return m_sName; }
    double get_cost_per_month() const { return m_dCostPerMonth; }
};

class Household {
private:
    std::vector<Person>m_objPeople;
    std::string m_sAddress;
    int m_iNumberOfAdultsInHousehold;
    std::vector<Outgoing>objPleasureCosts;
    std::vector<Outgoing>objBills;
    
public:
    Household(std::string address) 
        :m_sAddress{ address }, m_iNumberOfAdultsInHousehold{0}    
    {}
    void set_address(std::string address) { m_sAddress = address; }

    std::string get_address()const { return m_sAddress; }
    int get_number_of_adults_in_household()const { return m_iNumberOfAdultsInHousehold; }
    
    double calculate_monthly_total_expenditure() const {
        return calculate_monthly_bill_costs() + calculate_monthly_pleasure_costs();
    }
    void add_new_monthly_bill(Outgoing &&objOutgoingBill) {
        objBills.emplace_back(objOutgoingBill);
    }
    void add_new_monthly_pleasure_cost(Outgoing &&objOutgoingPleasure) {
        objPleasureCosts.emplace_back(objOutgoingPleasure);
    }
    double calculate_yearly_expenditure() const {
        
        return (calculate_monthly_pleasure_costs() + calculate_monthly_bill_costs() * 12);
    }
    double calculate_monthly_savings() const {

        return calculate_total_income() - (calculate_monthly_bill_costs() + calculate_monthly_pleasure_costs());
    }
    double calculate_total_income() const {

        double dTotalIncome = 0;
        for (const Person& objPerson : m_objPeople) {
            dTotalIncome += objPerson.get_monthly_salary();
        }
        return dTotalIncome;
    }
    double calculate_total_monthly_outgoing_costs() const {
        return (calculate_monthly_pleasure_costs() + calculate_monthly_bill_costs()) * 12;
    }
    double calculate_yearly_bill_costs() const {
        return calculate_monthly_bill_costs() * 12;
    }
    double calculate_yearly_pleasure_costs() const {
        return calculate_monthly_pleasure_costs() * 12;
    }
    double calculate_monthly_bill_costs() const {
        double dSum = 0;
        for (const Outgoing& objOutcoming : objBills) {
            dSum += objOutcoming.get_cost_per_month();
        }
        return dSum;
    }
    double calculate_monthly_pleasure_costs() const {
        double dSum = 0;
        for (const Outgoing& objOutcoming : objPleasureCosts) {
            dSum = objOutcoming.get_cost_per_month();
        }
        return dSum;
    }
    void add_person_to_household(Person objPerson) {
        m_objPeople.emplace_back(objPerson);
        m_iNumberOfAdultsInHousehold++;      
    }
    void display_household_adults() const {
        std::cout << "Household...\n";
        std::cout << "Address: " << m_sAddress << "\n";
        std::cout << "Occupants...\n";
        for (const Person& objPerson : m_objPeople) {
            std::cout << objPerson.get_name() << "\n";           
        }
    } 
    void display_household_bills() const {
        std::cout << "Bills...\n";
        for (const Outgoing& objBill : objBills) {
            std::cout << "Name: " << objBill.get_outgoing_name() << "\n";
            std::cout << "Cost a month: " << char(156) << objBill.get_cost_per_month() << "\n";
            std::cout << objBill.get_cost_per_month() << "\n";
        }
    }
};

class HomeownerBreakdownSystem {
private:
    std::vector<Household> m_objHouseholds;
public:
    auto find_household(std::string address) {
        return std::find_if(m_objHouseholds.begin(), m_objHouseholds.end(), [&](auto& household) {return household.get_address() == address; });
    }

    void add_household_to_system(std::string address) {
        m_objHouseholds.emplace_back(address);
    }
    auto& newly_added_household() {
        return m_objHouseholds.back();
    }
};
bool confirm_continue() {
    unsigned char cOption = 0;
    do {
        std::cin >> cOption;
        cOption = tolower(cOption);
        if (cOption == 'y') {
            return true;
        }
        else if (cOption == 'n') {
            return false;
        }
        else
        {
            std::cout << "Your answer wasn't decisive, enter either y or n: ";
            continue;
        }
       
    } while (true);
}
void display_outgoings_report(const Household &objHousehold) {

    objHousehold.display_household_adults();
    std::cout << "Household's Outgoing Total Cost: " << char(156) << objHousehold.calculate_monthly_total_expenditure() << "\n";
    std::cout << "  . Bills total cost: " << char(156) << objHousehold.calculate_monthly_bill_costs() << "\n";
    std::cout << "  . Pleasure total cost: " << char(156) << objHousehold.calculate_monthly_pleasure_costs() << "\n";
    objHousehold.display_household_bills();
    std::cout << "Monthly savings: " << char(156) << objHousehold.calculate_monthly_savings() << "\n";
    std::cout << "Total yearly expenditure: " << char(156) << objHousehold.calculate_yearly_expenditure() << "\n";
    std::cout << "  . Yearly Bill expenditure: " << char(156) << objHousehold.calculate_yearly_bill_costs() << "\n";
    std::cout << "  . Yearly Pleasure expenditure: " << char(156) << objHousehold.calculate_yearly_pleasure_costs() << "\n";
}
void establish_new_household(HomeownerBreakdownSystem &objSystem) {
    std::string sHousehold;
    std::cout << "Enter the address of household: ";
    std::getline(std::cin >> std::ws, sHousehold);
    objSystem.add_household_to_system(sHousehold);
}
void enter_occupants_for_new_household(Household& objHousehold) {
    std::string sName;
    double dMonthlySalary = 0;
    unsigned char cOption = 0;
    do 
    {
        std::cout << "\nEnter occupant's name: ";
        std::getline(std::cin >> std::ws, sName);

        std::cout << "Enter occupant's monthly income " << char(156);
        std::cin >> dMonthlySalary;
        objHousehold.add_person_to_household(Person{ sName, dMonthlySalary });
          
        std::cout << "Do you wish to add another to " << objHousehold.get_address() << "? (y/n): ";
        if (confirm_continue()) {
            continue;
        }
        else 
        {
            return;
        }
    } while (true);
}
void enter_monthly_bills_to_pay_for_new_household(Household& objHousehold) {
    std::string sBillName;
    double dCostPerMonth = 0;
    unsigned char cOption = 0;
    do
    {
        std::cout << "\nEnter bill's name: ";
        std::getline(std::cin >> std::ws, sBillName);
        std::cout << "Enter bill's monthly cost: " << char(156);
        std::cin >> dCostPerMonth;
        objHousehold.add_new_monthly_bill(Outgoing{ sBillName, dCostPerMonth });

        std::cout << "Do you wish to add another to bill? (y/n): ";
        if (confirm_continue()) {
            continue;
        }
        else
        {
            return;
        }
    } while (true);
}
void enter_monthly_pleasure_costs_for_new_household(Household& objHousehold) {
    std::string sPleasureName;
    double dCostPerMonth = 0;
    unsigned char cOption = 0;
    do
    {
        std::cout << "\nEnter pleasure's name: ";
        std::cin >> sPleasureName;

        std::cout << "Enter pleasure's monthly cost: " << char(156);
        std::cin >> dCostPerMonth;
        objHousehold.add_new_monthly_pleasure_cost(Outgoing{sPleasureName, dCostPerMonth});
        std::cout << "Do you wish to add another pleasure cost? (y/n): ";
        if (confirm_continue()) {
            continue;
        }
        else
        {
            return;
        }
    } while (true);
}

int main()
{
    HomeownerBreakdownSystem objSystem;
    establish_new_household(objSystem);
    enter_occupants_for_new_household(objSystem.newly_added_household());
    enter_monthly_bills_to_pay_for_new_household(objSystem.newly_added_household());
    enter_monthly_pleasure_costs_for_new_household(objSystem.newly_added_household());
    display_outgoings_report(objSystem.newly_added_household());
}

