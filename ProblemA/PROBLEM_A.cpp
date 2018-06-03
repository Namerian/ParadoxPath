#include <bitset>
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    std::string input_string;
    std::string binary;
    int output_int;

    getline(std::cin, input_string);

    /**/
    //std::cout << "input=" << input_string << std::endl;
    /**/

    binary = std::bitset<32>(std::stoi(input_string)).to_string();

    /**/
    //std::cout << "dirty_binary=" << binary << std::endl;
    /**/

    int first_one_index = binary.find_first_of('1');
    binary.erase(0, first_one_index);

    /**/
    //std::cout << "clean_binary=" << binary << std::endl;
    /**/

    int binary_length = binary.length();
    int binary_half_length = binary_length / 2;

    for (int index = 0; index < binary_half_length; index++)
    {
        int other_index = binary_length - 1 - index;

        char temp = binary[other_index];
        binary[other_index] = binary[index];
        binary[index] = temp;
    }

    output_int = std::stoi(binary, nullptr, 2);

    /**/
    //std::cout << "result=" << output_int << std::endl;
    /**/

    std::cout << output_int << std::endl;

    return 0;
}
