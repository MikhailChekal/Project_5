#include <iostream>
#include "json.hpp"
#include <filesystem>
#include <string>
#include <fstream>
#include <utility>


using namespace std;
using nlohmann::json;
namespace fs = std::filesystem;

class Person{
private:
    string full_name;
    string gender;
    unsigned age;
    double body_temp;

public:
    explicit Person(string name = "name", string gr = "m", unsigned age = 0u, double temp = 0.0):
    full_name(std::move(name)), gender(std::move(gr)), age(age), body_temp(temp){}

    string fnm(){return full_name;} string gdr(){return gender;} unsigned& ag(){return age;} double& tmp(){return body_temp;}
    friend std::ostream& operator<< (std::ostream &out, const Person &person);
    friend std::istream& operator>> (std::istream &in, Person &person);
    };

std::istream& operator>> (std::istream &in, Person &person){
    in >> person.full_name;
    in >> person.age;
    in >> person.gender;
    in >> person.body_temp;

    return in;
}
std::ostream& operator<< (std::ostream &out, const Person &person){
    out << "Name: " << person.full_name << endl << "Gender: " << person.gender << endl << "Age: " << person.age << endl;
    return out;
}

int main() {
    std::vector<json> population;
    std::cout << "Enter number of people to add: "; int m; std::cin >> m;
    for (int i = 0; i < m; i++) {
        Person person;
        cin >> person;

        json persona;
        persona["full name"] = person.fnm();
        persona["age"] = person.ag();
        persona["gender"] = person.gdr();
        persona["body temp"] = person.tmp();

        population.push_back(persona);
        }
    for (auto & i : population){
        std::string address = ".txt";
        address.insert ( 0, i["full name"]);
        //fs::current_path();
        fs::create_directory("C:/Users/misha/CLionProjects/Project_4/Visitors_database");
        std::ofstream file(address.c_str());
        file << i << endl;
    }

};