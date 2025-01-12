/**
 * An example of how to write unit tests.
 * Use this as a basis to build a more complete Test.cpp file.
 * 
 * IMPORTANT: Please write more tests - the tests here are only for example and are not complete.
 *
 * AUTHORS: <Amir Sabag>
 * 
 * Date: 2021-02
 */
#include "doctest.h"
#include "mat.hpp"
using namespace ariel;

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/**
 * Returns the input string without the whitespace characters: space, newline and tab.
 * Requires std=c++2a.
 */
string nospaces(string input) {
	std::erase(input, ' ');
	std::erase(input, '\t');
	std::erase(input, '\n');
	std::erase(input, '\r');
	return input;
}


TEST_CASE("Good input") {
    /* only valid inputs */

    SUBCASE("Easy case"){
        /* "BDIKAT SHFIUT OF FUNCTION" 
            check that its only print the size of the carpet of one symbol, without currectness*/
        string str1 = mat(3, 3, '1', '1');

        // credit https://stackoverflow.com/questions/2896600/how-to-replace-all-occurrences-of-a-character-in-string
        std::replace(str1.begin(), str1.end(), '\r', '\n');  // replace one char to another in the string
        CHECK_EQ(str1, "111\n111\n111");
    }


    /* check currectness of solution */

    SUBCASE("Small input"){
        /* base cases, of the minimal carpets possibles */

        // ------- degenerated cases ------ 
        // 1x1 == one char
        CHECK_EQ(mat(1, 1, '@', '-'), "@");

        // col 3, row 1 => 1x3 carpet
        CHECK_EQ(mat(3, 1, '@', '-'), "@@@");


        // col 1, row 3 => 3x1 carpet
        CHECK_EQ(nospaces(mat(1, 3, '@', '-')), nospaces("@\n@\n@"));

        // ------- 3x3 carpet -------
        CHECK_EQ(nospaces(mat(3, 3, '1', '-')), nospaces("111\n"
                                                        "1-1\n"
                                                        "111"));
    }

    SUBCASE("Medium input"){
        /* inputs which we can test with a human paint solution */

        // col == row, 5x5 carpet
        CHECK_EQ(nospaces(mat(5, 5, '1', '_')), nospaces("11111\n"
                                                        "1___1\n"
                                                        "1_1_1\n"
                                                        "1___1\n"
                                                        "11111"));

        // col < row, 9x7 carpet
        CHECK_EQ(nospaces(mat(7,9, '1', '-')), nospaces("1111111\n"
                                                       "1-----1\n"
                                                       "1-111-1\n"
                                                       "1-1-1-1\n"
                                                       "1-1-1-1\n"
                                                       "1-1-1-1\n"
                                                       "1-111-1\n"
                                                       "1-----1\n"
                                                       "1111111"));

        // col > row, 7x9 carpet
        CHECK_EQ(nospaces(mat(9, 7, '@', '-')), nospaces("@@@@@@@@@\n"
                                                        "@-------@\n"
                                                        "@-@@@@@-@\n"
                                                        "@-@---@-@\n"
                                                        "@-@@@@@-@\n"
				    									 "@-------@\n"
					    								 "@@@@@@@@@"));
	
    }

    SUBCASE("Big input proportional carpet"){
        /* inputs which we couldnt "print" manualy and shall check this carpets 
			proportional carpet menas - |col - row| is close to zero, makes carpet looks like a 'square' - easier case 
				this case doesnt test if the mat function algorithm understands that: there is cases which alot of rows returns on themselves */

        string str2 = mat(101, 99, '1', '-');
        // string str2_copy = std::string::copy(str2, str2.length+1, 0);

        // first, length shall be like a matrix of 99*101
        CHECK_EQ(nospaces(str2).length(), 99*101); 

        string first_line = str2.substr(0, 101);
        string second_line = str2.substr(102, 101);
        string third_line = str2.substr(204, 101);
        string middle_line = str2.substr(101*48+48, 101);

        string first_line_check = "";
        string second_line_check = "";
        string third_line_check = "";
        string middle_line_check = "";

        bool flag = true;

        // initialize strings of answers
        // first_line - only 1 -> "11111111...1"
        // second line - only 1 at corners "1----.....-1"
        // third line - only '-' before corners "1-111111111....111-1"
        // middle line - switching one after another "1-1-1-...-11111-..-1-1" <- while the five chars in the middle is indexes 48 to 52 (perfect middle) of line
        for (int i=0; i<101; i++){
            first_line_check += '1'; // init first
             
            if (i == 0 || i == 100){ // init second
                second_line_check += '1';
            }
            else {
                second_line_check += '-';
            }
            
            if (i == 1 || i == 99){ // init third
                third_line_check += '-';
            }
            else {
                third_line_check += '1';
            }
            
            if (flag && (i<48 || i > 52)){ // init mid
                middle_line_check += '1';
                flag = false;
            }
            else if (!flag && (i<48 || i > 52)){
                middle_line_check += '-';
                flag = true;
            }
            else {
                middle_line_check += '1';
                flag = false;
            }
        }
        
        // check them
        CHECK_EQ(first_line, first_line_check);

        CHECK_EQ(second_line, second_line_check);

        CHECK_EQ(third_line, third_line_check);

        CHECK_EQ(middle_line, middle_line_check);

    }

	SUBCASE("Big input not proportional carpet"){
	/* inputs which we couldnt "print" manualy and shall check this carpets 
		proportional carpet menas - |col - row| >>> (bigger by lot) zero, makes carpet looks like a 'rectangle' - harder case 
			this case test if the mat function algorithm understands that: there is cases which alot of rows returns on themselves */

		string str3 = mat(11, 77, '@', '-');

        // first, length shall be like a matrix of 99*101
        CHECK_EQ(nospaces(str3).length(), 77*11); 

		// first and last line 
        string first_linee = str3.substr(0, 11);
		string last_linee = str3.substr(12*76, 11);
        string first_linee_check = "@@@@@@@@@@@";
		CHECK_EQ(first_linee, first_linee_check);
		CHECK_EQ(last_linee, first_linee_check);

		// 2nd and one beofre last line
        string second_linee = str3.substr(12, 11);
		string before_last = str3.substr(12*75, 11);
		string second_linee_check = "@---------@";
		CHECK_EQ(second_linee, second_linee_check);
		CHECK_EQ(before_last, second_linee_check);

		// 3rd and 3rd from end line 
        string third_linee = str3.substr(24, 11);
		string third_before_end = str3.substr(12*74, 11);
		string third_linee_check = "@-@@@@@@@-@";
		CHECK_EQ(third_linee, third_linee_check);
		CHECK_EQ(third_before_end, third_linee_check);

		// 4th and 4th from end
		string fourth_linee = str3.substr(36, 11);
		string fourth_before_end = str3.substr(12*73, 11);
		string fourth_linee_check = "@-@-----@-@";
		CHECK_EQ(fourth_linee, fourth_linee_check);
		CHECK_EQ(fourth_before_end, fourth_linee_check);

		// 5th and 5th from end
		string fifth_linee = str3.substr(48, 11); 
		string fifth_before_end = str3.substr(12*72, 11);
		string fifth_linee_check = "@-@-@@@-@-@";
		CHECK_EQ(fifth_linee, fifth_linee_check);
		CHECK_EQ(fifth_before_end, fifth_linee_check);

		// check random middle lines to be same 
        string first_middle_linee = str3.substr(60, 11);
		string last_middle_linee = str3.substr(12*71, 11);
		string rand_mid_line1 = str3.substr(12*36, 11);
		string rand_mid_line2 = str3.substr(12*21, 11);
		string rand_mid_line3 = str3.substr(12*47, 11);
		string middle_linee_check = "@-@-@-@-@-@";
		CHECK_EQ(first_middle_linee, middle_linee_check);
		CHECK_EQ(last_middle_linee, middle_linee_check);
		CHECK_EQ(rand_mid_line1, middle_linee_check);
		CHECK_EQ(rand_mid_line2, middle_linee_check);
		CHECK_EQ(rand_mid_line3, middle_linee_check);

	}

}

TEST_CASE("Bad input") {
    /* only invalid inputs to the function mat */

    SUBCASE("Even size input"){
        /* row or col is even, shall throw exception */

        CHECK_THROWS(mat(10, 5, '$', '%')); // col is even
    
        CHECK_THROWS(mat(3, 2, '$', '%')); // row is even
    }

    SUBCASE("Zero size input"){
        /* row or col is zero, shall throw exception */

        CHECK_THROWS(mat(0, 5, '$', '%')); // col is zero

        CHECK_THROWS(mat(3, 0, '$', '%')); // row is zero
    }

    SUBCASE("Negative size input"){
        /* row or col is negative, shall throw exception */

        CHECK_THROWS(mat(-1, 5, '$', '%')); // col is negative

        CHECK_THROWS(mat(3, -1, '$', '%')); // row is negative

    }

    SUBCASE("Invalid symbols"){
        /* sym1 or sym2 ascii is <= 32 which means the system wont be able to print a carpet */

        CHECK_THROWS(mat(5, 9, '\t', '1'));

        CHECK_THROWS(mat(9, 5, '1', ' '));

        CHECK_THROWS(mat(7, 7, '\r', '-'));

        CHECK_THROWS(mat(5, 5, '1', '\n'));
    }

}