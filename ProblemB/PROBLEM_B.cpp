#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

template <typename Out>
void Split(const std::string &string, char delimiter, Out result)
{
    std::stringstream stream(string);
    std::string item;

    while (std::getline(stream, item, delimiter))
    {
        *(result++) = item;
    }
}

std::vector<std::string> Split(const std::string &string, char delimiter)
{
    std::vector<std::string> elements;
    Split(string, delimiter, std::back_inserter(elements));
    return elements;
}

int main(int argc, char const *argv[])
{
    int num_rows = 0;
    int num_columns = 0;

    std::vector<int> row_sums_vector;
    std::vector<int> column_sums_vector;

    int row_total = 0;
    int column_total = 0;

    //************************************************

    // reading input

    std::string first_line;
    std::string second_line;
    std::string third_line;

    getline(std::cin, first_line);
    getline(std::cin, second_line);
    getline(std::cin, third_line);

    std::vector<std::string> first_line_vector = Split(first_line, ' ');
    std::vector<std::string> second_line_vector = Split(second_line, ' ');
    std::vector<std::string> third_line_vector = Split(third_line, ' ');

    //************************************************

    // transforming input

    num_rows = std::stoi(first_line_vector[0]);
    num_columns = std::stoi(first_line_vector[1]);

    for (int row_index = 0; row_index < num_rows; row_index++)
    {
        int row_sum = std::stoi(second_line_vector[row_index]);
        row_sums_vector.push_back(row_sum);
        row_total += row_sum;
    }

    for (int column_index = 0; column_index < num_columns; column_index++)
    {
        int column_sum = std::stoi(third_line_vector[column_index]);
        column_sums_vector.push_back(column_sum);
        column_total += column_sum;
    }

    //************************************************

    // first check

    if (row_total != column_total)
    {
        //std::cout << "First Check - row_total=" << row_total << " - column_total=" << column_total << std::endl;
        std::cout << "No" << std::endl;

        return 0;
    }

    //************************************************

    while (!row_sums_vector.empty())
    {
        std::sort(column_sums_vector.begin(), column_sums_vector.end(), std::greater<int>());

        int k = row_sums_vector.back();
        row_sums_vector.pop_back();

        if (k > column_sums_vector.size())
        {
            //std::cout << "AAAA" << std::endl;
            std::cout << "No" << std::endl;

            return 0;
        }

        if (k == 0)
        {
            continue;
        }

        for (int index = 0; index < k; index++)
        {
            if (column_sums_vector[index] < 1)
            {
                //std::cout << "BBBB" << std::endl;
                std::cout << "No" << std::endl;

                return 0;
            }
        }

        for (int index = 0; index < k; index++)
        {
            column_sums_vector[index]--;
        }
    }

    // for (std::vector<int>::iterator iterator = column_sums_vector.begin(); iterator != column_sums_vector.end(); iterator++)
    // {
    //     if (*iterator != 0)
    //     {
    //         //std::cout << "CCCC" << std::endl;
    //         std::cout << "No" << std::endl;

    //         return 0;
    //     }
    // }

    //************************************************

    std::cout << "Yes" << std::endl;

    return 0;
}