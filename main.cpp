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
    string printInfoAboutPerson() const
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
        numberOfPatients(numberOfPatients), salary(salary), category(category), degree(degree)
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
    string printInfoAboutDoctor() const
    {
        return Person::printInfoAboutPerson() + "\nSpecialization:" + specialization + "\nNumber of patients:" + to_string(numberOfPatients) +
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
    string printInfoAboutSoldier() const
    {
        return Person::printInfoAboutPerson() + "\nRank:" + rank + "\nService life:" + to_string(serviceLife) +
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
        Doctor doc1("Ivanov Ivan Ivanovich", 1, 1, 1990, "Ukraine", "Lviv", "098-765-43-21", "Nurse", 5, 1000, "General", "Junior");
        Doctor doc2("Petrov Petr Petrovich", 1, 1, 1990, "Ukraine", "Lviv", "098-765-43-21", "Dentist", 10, 1000, "Specialist", "Junior");
        Doctor doc3("Sidorov Sidor Sidorovich", 1, 1, 1990, "Ukraine", "Lviv", "098-765-43-21", "Surgery", 32, 1000, "Expert", "Junior");
        Doctor doc4("Kuznetsov Kuznet Kuznetovich", 1, 1, 1990, "Ukraine", "Lviv", "098-765-43-21", "General", 15, 1000, "Specialist", "Middle");
        Doctor doc5("Ivanov Ivan Ivanovich", 1, 1, 1990, "Ukraine", "Lviv", "098-765-43-21", "General", 2, 1000, "Expert", "Senior");

        Doctor *doc[5] = {&doc1, &doc2, &doc3, &doc4, &doc5};
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (doc[i]->CostOfConsultation() > doc[j]->CostOfConsultation())
                {
                    Doctor *temp = doc[i];
                    doc[i] = doc[j];
                    doc[j] = temp;
                }
            }
        }

        cout << "Doctors with specialization General: " << endl;
        for (int i = 0; i < 5; i++)
        {
            if (doc[i]->getSpecialization() == "General")
            {
                cout << doc[i]->printInfoAboutDoctor() << "\n\n\n";
            }
        }
        int s;
        cin >> s;
        cout << string(100, '\n');
        Soldier sol1("Ivanov Ivan Ivanovich", 1, 1, 1990, "Ukraine", "Lviv", "098-765-43-21", "None", 0, "Glock", Soldier::army);
        Soldier sol2("Petrov Petr Petrovich", 1, 1, 1990, "Ukraine", "Lviv", "098-765-43-21", "None", 0, "Shooting knife", Soldier::reserve);
        Soldier sol3("Sidorov Sidor Sidorovich", 1, 1, 1990, "Ukraine", "Lviv", "098-765-43-21", "None", 0, "AK-47", Soldier::contract);
        Soldier *sol[3] = {&sol1, &sol2, &sol3};
        for (int i = 0; i < 3; i++)
        {
            cout << sol[i]->printInfoAboutSoldier() << "\n\n\n";
        }
        sol1.fight();
        sol2.fight();
        for (int i = 0; i < 3; i++)
        {
            cout << sol[i]->printInfoAboutSoldier() << "\n\n\n";
        }


    }
    catch (exception& ex)
    {
        cerr << ex.what();
    }

    return 0;
}
