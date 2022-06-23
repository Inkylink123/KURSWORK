#include <string>
#include <iostream>
#include <stdexcept>
#include <exception>
#include <vector>

using namespace std;

class Person
{
protected:
    string fullName;
    int d, m, y;
    string Country;
    string City;
    string TelephoneNumber;
public:
    Person() :fullName("None"), d(1), m(1), y(1970), Country("None"), City("None"), TelephoneNumber("None") {}
    Person(string fullName, int d, int m, int y, string Country, string City, string TelephoneNumber)
    {
        if (!fullName.empty()) this->fullName = fullName; else throw invalid_argument("Empty string!");
        if (!((d < 1 || d > 31) || (m < 1 || m > 12)))
        {
            this->d = d;
            this->m = m;
            this->y = y;
        }
        else throw invalid_argument("Invalid data!");
        if (!Country.empty()) this->Country = Country; else throw invalid_argument("Empty indication!");
        if (!City.empty()) this->City = City; else throw invalid_argument("Empty indication!");
        if (!TelephoneNumber.empty()) this->TelephoneNumber = TelephoneNumber; else throw invalid_argument("Empty number!");
    }
    bool IsNameRight() const
    {
        size_t p = fullName.find_first_of(" ", 0), p2 = fullName.find_first_of(" ", p + 1), p3 = fullName.find_first_of(" ", p2 + 1);
        if(p == 0) return false;
        if(p == string::npos) return false;
        if(p2 == p + 1) return false;
        if(p2 == string::npos) return false;
        if(p3 != string::npos) return false;
        return true;
    }
    bool Residence() const
    {
        if (Country == "Ukraine" && City == "Lviv") return true;
        else return false;
    }
    virtual string printInfo() const
    {
        return  "Full Name:" + fullName + "\nDay of birth:" + to_string(d) + "." + to_string(m) + "." + to_string(y) +
                "\nCountry:" + Country + "\nCity:" + City + "\nTelephone number:" + TelephoneNumber;
    }
};


class Doctor : public Person
{
private:
    string specialization;
    int numberOfPatients;
    int salary;
    string category;
    string degree;
public:
    Doctor() :Person(), specialization("None"), numberOfPatients(0), salary(0), category("None"), degree("None") {}
    Doctor(string fullName, int d, int m, int y, string Country, string City, string TelephoneNumber,
           string specialization, int numberOfPatients, int salary, string category, string degree)
        :Person(fullName, d, m, y, Country, City, TelephoneNumber), specialization(specialization),
        numberOfPatients(numberOfPatients), category(category), degree(degree), salary(salary)
        {
            if (specialization.empty()) throw invalid_argument("Empty string!");
            if (numberOfPatients < 0) throw invalid_argument("Invalid number!");
            if (salary < 0) throw invalid_argument("Invalid number!");
            if (category.empty()) throw invalid_argument("Empty string!");
            if (degree.empty()) throw invalid_argument("Empty string!");
        }
    double CostOfConsultation()
    {
        if (degree == "Junior")
        {
            if (category == "General") return salary * 0.5;
            else if (category == "Specialist") return salary * 0.6;
            else if (category == "Expert") return salary * 0.7;
            else throw invalid_argument("Invalid category!");
        }
        else if (degree == "Middle")
        {
            if (category == "General") return salary * 0.6;
            else if (category == "Specialist") return salary * 0.7;
            else if (category == "Expert") return salary * 0.8;
            else throw invalid_argument("Invalid category!");
        }
        else if (degree == "Senior")
        {
            if (category == "General") return salary * 0.7;
            else if (category == "Specialist") return salary * 0.8;
            else if (category == "Expert") return salary * 0.9;
            else throw invalid_argument("Invalid category!");
        }
        else throw invalid_argument("Invalid degree!");
    }
    int CountSalary()
    {
        if (degree == "Junior")
        {
            if (category == "General") return 1000 * 0.5 * numberOfPatients;
            else if (category == "Specialist") return 1000 * 0.6 * numberOfPatients;
            else if (category == "Expert") return 1000 * 0.7 * numberOfPatients;
        }
        else if (degree == "Middle")
        {
            if (category == "General") return 2000 * 0.6 * numberOfPatients;
            else if (category == "Specialist") return 2000 * 0.7 * numberOfPatients;
            else if (category == "Expert") return 2000 * 0.8 * numberOfPatients;
        }
        else if (degree == "Senior")
        {
            if (category == "General") return 3000 * 0.7 * numberOfPatients;
            else if (category == "Specialist") return 3000 * 0.8 * numberOfPatients;
            else if (category == "Expert") return 3000 * 0.9 * numberOfPatients;
        }
    }
    string printInfo() const override
    {
        return Person::printInfo() + "\nSpecialization:" + specialization + "\nNumber of patients:" + to_string(numberOfPatients) +
                "\nSalary:" + to_string(salary) + "\nCategory:" + category + "\nDegree:" + degree;
    }
    string getSpecialization() const
    {
        return specialization;
    }

    void implementConsultation()
    {
        numberOfPatients++;
    }

};


class Soldier : public Person
{
public:
    enum militaryService {
        army, reserve, contract
    };
    Soldier(string fullName, int d, int m, int y, string Country, string City, string TelephoneNumber,
    string rank, int serviceLife, string armament, militaryService militaryServiceType) :
        Person(fullName, d, m, y, Country, City, TelephoneNumber), rank(rank), serviceLife(serviceLife), armament(armament), militaryServiceType(militaryServiceType)
        {
            if(rank.empty()) throw invalid_argument("Invalid rank!");
            if(armament.empty()) throw invalid_argument("Invalid armament!");
            if(serviceLife < 0) throw invalid_argument("Invalid service life!");
        }
    Soldier() : Person(), rank("None"), serviceLife(0), armament("None"), militaryServiceType(army){};
    string printInfo() const override
    {
        return Person::printInfo() + "\nRank:" + rank + "\nService life:" + to_string(serviceLife) +
                "\nArmament:" + armament + "\nMilitary service:" + to_string(militaryServiceType);
    }
    void fight()
    {
        if (militaryServiceType == army)
        {
            if (serviceLife < 2)
            {
                serviceLife++;
            }
            else
            {
                if (rand() % 5 == 0)
                {
                    serviceLife++;
                }
            }
        }
        else if (militaryServiceType == contract)
        {
            if (serviceLife < 10)
            {
                serviceLife++;
            }
            else
            {
                if (rand() % 2 == 0)
                {
                    serviceLife++;
                }
            }
        }
    }
    void toReserve()
    {
        if (militaryServiceType == army)
        {
            militaryServiceType = reserve;
        }
    }
private:
    string rank;
    int serviceLife;
    string armament;
    militaryService militaryServiceType;
};

int main()
{
    try
    {
        bool flag = true;
        vector <Person*> people;
        vector <Doctor*> doctors;
        vector <Soldier*> soldiers;
        while (flag)
        {

            cout << "1. Create person" << endl;
            cout << "2. Create doctor" << endl;
            cout << "3. Create soldier" << endl;
            cout << "4. Print info about all people" << endl;
            cout << "5. Exit" << endl;
            cout << "------------------------------------------" << endl;
            int choice;
            cin >> choice;
            if (choice == 1)
            {
                string fullName, Country, City, TelephoneNumber;
                int d, m, y;
                cout << "Enter full name:" << endl;
                cin >> fullName;
                cout << "Enter date of birth:" << endl;
                cin >> d >> m >> y;
                cout << "Enter country:" << endl;
                cin >> Country;
                cout << "Enter city:" << endl;
                cin >> City;
                cout << "Enter telephone number:" << endl;
                cin >> TelephoneNumber;
                people.push_back(new Person(fullName, d, m, y, Country, City, TelephoneNumber));
                cout << "Person created!" << endl;
                cout << "------------------------------------------" << endl;
            }
            else if (choice == 2) {
                string fullName, Country, City, TelephoneNumber, specialization, category, degree;
                int d, m, y, numberOfPatients, salary;
                cout << "Enter full name:" << endl;
                cin >> fullName;
                cout << "Enter date of birth:" << endl;
                cin >> d >> m >> y;
                cout << "Enter country:" << endl;
                cin >> Country;
                cout << "Enter city:" << endl;
                cin >> City;
                cout << "Enter telephone number:" << endl;
                cin >> TelephoneNumber;
                cout << "Enter specialization:" << endl;
                cin >> specialization;
                cout << "Enter number of patients:" << endl;
                cin >> numberOfPatients;
                cout << "Enter salary:" << endl;
                cin >> salary;
                cout << "Enter category:" << endl;
                cout << "General, Specialist, Expert" << endl;
                cin >> category;
                cout << "Enter degree:" << endl;
                cout << "Junior, Middle, Senior" << endl;
                cin >> degree;
                doctors.push_back(new Doctor(fullName, d, m, y, Country, City, TelephoneNumber, specialization, numberOfPatients, salary, category, degree));
                cout << "Doctor created!" << endl;
                cout << "------------------------------------------" << endl;
            }
            else if(choice == 3)
            {
                string fullName, Country, City, TelephoneNumber, rank, armament;
                int d, m, y, serviceLife;
                cout << "Enter full name:" << endl;
                cin >> fullName;
                cout << "Enter date of birth:" << endl;
                cin >> d >> m >> y;
                cout << "Enter country:" << endl;
                cin >> Country;
                cout << "Enter city:" << endl;
                cin >> City;
                cout << "Enter telephone number:" << endl;
                cin >> TelephoneNumber;
                cout << "Enter rank:" << endl;
                cin >> rank;
                cout << "Enter service life:" << endl;
                cin >> serviceLife;
                cout << "Enter armament:" << endl;
                cin >> armament;
                cout << "Enter military service type:" << endl;
                cout << "Army - 0, Reserve - 1, Contract - 2" << endl;
                int militaryServiceType;
                cin >> militaryServiceType;
                soldiers.push_back(new Soldier(fullName, d, m, y, Country, City, TelephoneNumber, rank,
                                               serviceLife, armament, (Soldier::militaryService)militaryServiceType));
                cout << "Soldier created!" << endl;
                cout << "------------------------------------------" << endl;
            }
            else if (choice == 4)
            {
                if(people.size() == 0)
                {
                    cout << "No people!" << endl;
                }
                else {
                    for (int i = 0; i < people.size(); i++) {
                        cout << "Person " << i+1 << ": " << endl << people[i]->printInfo() << endl;
                        cout << "---------------------------------------------------------" << endl;
                    }
                }
                if(doctors.size() == 0)
                {
                    cout << "No doctors!" << endl;
                }
                else {
                    for (int i = 0; i < doctors.size(); i++) {
                        cout << "Doctor " << i+1 << ": " << endl << doctors[i]->printInfo() << endl;
                        cout << "---------------------------------------------------------" << endl;
                    }
                }
                if(soldiers.size() == 0)
                {
                    cout << "No soldiers!" << endl;
                }
                else {
                    for (int i = 0; i < soldiers.size(); i++) {
                        cout << "Soldier " << i+1 << ": " << endl << soldiers[i]->printInfo() << endl;
                        cout << "---------------------------------------------------------" << endl;
                    }
                }
            }
            else
            {
                flag = false;
            }
        }
    }
    catch (exception& ex)
    {
        cerr << ex.what();
    }

    return 0;
}
