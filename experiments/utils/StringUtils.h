/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 2/25/18
 */

#ifndef EXPERIMENTS_STRINGUTILS_H
#define EXPERIMENTS_STRINGUTILS_H

#include <string>
#include <vector>
using namespace std;

class StringUtils {
public:
    static vector<string> split(string s, string delimiter) {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        string token;
        vector<string> res;
        while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
            token = s.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back(token);
        }
        res.push_back(s.substr(pos_start));
        return res;
    }
};


#endif //EXPERIMENTS_STRINGUTILS_H
