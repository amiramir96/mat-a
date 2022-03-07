#include "mat.hpp"
#include <stdexcept>
namespace ariel{
    std::string mat (int col, int row, char sym1, char sym2)
    {
        std::string ret;
        if (col % 2 == 0 || row % 2 == 0){
            throw std::invalid_argument("Mat size is always odd");        
        }
        if (col < 0 || row < 0){
            throw std::invalid_argument("Mat size shall be positive");
        }
        if (sym1 <= 32 || sym2 <= 32){
            throw std::invalid_argument("invalid symbols arg, please input char symbols with ascii > 32");
        }
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++){
                ret += std::to_string(j%10);
                ret += " ";
            }
            ret += "\n";
        }
        
        return ret;
    }
}