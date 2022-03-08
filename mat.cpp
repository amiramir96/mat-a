#include "mat.hpp"
#include <stdexcept>
#include <iostream>
namespace ariel{

    std::string one_row(int len, char sym){
        /* special case when there is only one row, no need the whole algorithm process */
        
        std::string ret = ""; // init empty string
        for (int i=0; i<len; i++) ret += sym; 
        return ret;
    
    }

    std::string one_col(int len, char sym){
        /* special case when there is only one col, no need the whole algorithm process */
       
        std::string ret = ""; // init empty string
        for(int i=0; i<len-1; i++){
            ret += sym;
            ret += '\n';
        } 

        ret += sym; // last symbol without down line
        return ret; 
    }

    std::string row_produce(int col, char sym1, char sym2, int key){
        /* this func producing a string, represent a row of the carpet from 'mat' function
            the base of this function is the parameter -key- which decides which row of the carpet shall be produced */
        
        // init vars
        std::string ret = "";
        bool flag = true; // true := add sym1, false := add sym2
        int chars_to_print = 0; // how many chars we added till present to ret string

        /* 1st loop */
        for (; chars_to_print < key; chars_to_print++){
            // this for-loop add step by step sym1-sym2-sym1-sym2 via using the flag. till the key!
            if (flag) ret += sym1;
            if (!flag) ret += sym2;
            flag = !flag;
        }

        /* 2nd loop */ 
        for (; chars_to_print < col - key; chars_to_print++){
            // this for-loop add from ret[key] to ret[col-key] the currect symbol (1 or 2)
            // reminder - key is our magic parameter, since its influence is about the flag state at this stage   
            if(flag) ret += sym1;
            if(!flag) ret += sym2;
        }
        flag = !flag; // switch flag so we can continue to third adding

        /* 3rd loop */
        for (; chars_to_print < col; chars_to_print++){
            // works exactly as first loop
            if (flag) ret += sym1;
            if (!flag) ret += sym2;
            flag = !flag;
        }

        ret += '\n'; // down line at the end of the row
        return ret;
    }

    std::string mat (int col, int row, char sym1, char sym2)
    {

        /* check for valid input.. else throw */
        if (col % 2 == 0 || row % 2 == 0){
            throw std::invalid_argument("Mat size is always odd");        
        }
        if (col < 0 || row < 0){
            throw std::invalid_argument("Mat size shall be positive");
        }
        if (sym1 <= 32 || sym2 <= 32){
            throw std::invalid_argument("invalid symbols arg, please input char symbols with ascii > 32");
        }
        
        /* for degenerated cases which is row || col is one, no needs the "complicated" algorithm */
        if (row == 1) return one_row(col, sym1);
        if (col == 1) return one_col(row, sym1); 

        /* algorithm to make string represents carpet via 3 steps:
                1- add to string the first half (withtout middle row) of carpet
                2- add middle row of carpet
                3- add second half of carpet which is a mirror of the first half (without middle row)
                
                (*) control the key - key "farwarding" have three options:
                    a. move by 1 (first half of carpet)
                    b. back by 1 (second half of carpet)
                    c. dont move (|col-row| > 3 of carpet) in the middle rows of the carpet 
                        cuz case (c.) shall not move on or back the key too much, so wont give the key to cross the col/2 param
                        same with second half, waiting till col/2 iterates from end to move back the key

                    ~~ special credit to our teacher to probabilities, got this idea from his story about 'the drunken move'
                 */
        std::string my_lovely_carpet; // output string
        int key = 0;  // count how many "switchs" shall be made before and after the same symbol line
       
        // step 1
        for (int i=0; i < row/2; i++){

            my_lovely_carpet += row_produce(col, sym1, sym2, key);
            if (key < col/2) key++; // control the key 

        }

        // step 2
        my_lovely_carpet += row_produce(col, sym1, sym2, key);
        
        if (col >= row){ 
            // control the key 
            // since we took 1 move farword for the middle line, we shall take 1 move back to start the symetric printing
            key--;
        }

        // step 3
        for (int i = row/2; i > 0; i--){
            
            my_lovely_carpet += row_produce(col, sym1, sym2, key);
            if (i - key <= 1) key--;

        }

        my_lovely_carpet.pop_back();  // delete the '\n' last char of string
        return my_lovely_carpet;
    }
}