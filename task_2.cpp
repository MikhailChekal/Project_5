#include <iostream>
#include <iterator>
#include <string>
#include <regex>


std::vector<std::string> search(const std::regex& pattern,
                                const std::string& text) {
    auto begin = std::sregex_iterator(std::begin(text),
                                      std::end(text), pattern);
    auto end = std::sregex_iterator();
    std::vector<std::string> results(std::distance(begin, end));
    std::transform(begin, end, std::back_inserter(results), [](auto x){
        return x.str();
    });
    return results;
}


int main() {
    std::regex date_pattern(R"(([0][1-9]|[12][0-9]|[3][01])\.([0][1-9]|[1][012])\.([0-9][0-9][0-9][0-9]))");
    std::regex time_pattern(R"(([0][0-9]|[1][0-9]|[2][0-4])\:([0-5][0-9])\:([0-5][0-9]))");


    std::string s = "I was born on 31.12.2001 at approximately 05:31:22. \n"
                    "Kneel, ignorant slave, for I am thy lord and my anger is unstoppable. Today is 10.08.2022 btw. \n"
                    "Whoever eats after 19:00:00 is doomed to suffer and cry in pain.";


    if (std::regex_search(s, date_pattern)) {
        std::cout << "Text contains date\n";
    } else {std::cout << "No date?(\n";}
    if (std::regex_search(s, time_pattern)) {
        std::cout << "Text contains time\n";
    }else {
        std::cout << "No time?(\n";
    }

    auto date_result = search(date_pattern, s);
    auto time_result = search(time_pattern, s);

    std::copy(std::begin(date_result), std::end(date_result),
              std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;
    std::copy(std::begin(time_result), std::end(time_result),
              std::ostream_iterator<std::string>(std::cout, " "));

}
