/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 2/25/18
 */

#ifndef EXPERIMENTS_INTRAVARIATES_H
#define EXPERIMENTS_INTRAVARIATES_H

#include "../Constants/Errors.h"
#include "../Constants.h"
#include "../utils/StringUtils.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

/**
 * Typedef for vector<int> that represents a list of bit numbers
 */
typedef vector<int> BitList;

/**
 * An IntraVariateGroup contains a subset of the bits in the vector
 * and the corresponding variate type.
 * Each group MUST have at least one IID bit, this bit is going to be
 * used as reference to generate the other bits using either antithetic or CRN.
 *
 * If more than one bit is IID then the group MUST contain only IID elements.
 *
 * This is an alias for map<int, VariateMethod>.
 * The key is the type of variate used for that bit.
 * The value is a list of bit numbers, each of which is [0..VECTOR_SIZE)
 */
typedef map<VariateMethod, BitList> IntraVariateGroup;

/**
 * IntraVariates hold all the different groups that are needed to
 * generate the full vector representation.
 *
 * @TODO: add checks to confirm all bits are included. For now assume it
 * is constructed properly.
 */
typedef vector<IntraVariateGroup> IntraVariates;

typedef bitset<7> GroupSelector;

class IntraVariatesUtils {
public:
    /**
     * Reads a file and creates the IntraVariates groups accordingly.
     * Each line of the file corresponds to a group.
     * The format of each line is:
     * bit0,bit1,bit2,...;bit00,bit01,bit02,...;bit000,bit001,...
     * where the ; delimits the different types (IID, AV, CRN), in that order.
     * @param filepath Path to the file that will be read
     * @param selector list of booleans indicating whether the i-th group should be included or not
     * @return the intra variates
     */
    static IntraVariates fromFile(string filepath, GroupSelector selector) {
        IntraVariateGroup allIID;
        for (int i = 0; i < VECTOR_SIZE; i++) {
            allIID[VariateMethod::IID].push_back(i);
        }
        IntraVariates result;

        ifstream file(filepath);

        string line;
        getline(file, line);

        bool pooled = strcmp("pooled", line.c_str()) == 0;
        int idx = 0;
        while (!file.eof()) {
            getline(file, line);
            if (line.empty())
                continue;

            if (!selector[idx]) {
                idx += 1;
                continue;
            }
            idx += 1;

            auto parts = StringUtils::split(line, ";");
            IntraVariateGroup group;
            if (parts[0].empty())
                throw Dependency::FILE_FORMAT_ERROR;

            for (auto iid: StringUtils::split(parts[0], ",")) {
                if (iid.empty()) break;
                int bit = stoi(iid);
                group[VariateMethod::IID].push_back(bit);
                remove(begin(allIID[VariateMethod::IID]), end(allIID[VariateMethod::IID]), bit);
            }

            if (parts.size() > 1) {
                for (auto av: StringUtils::split(parts[1], ",")) {
                    if (av.empty()) break;
                    int bit = stoi(av);
                    group[VariateMethod::ANTITHETIC].push_back(bit);
                    remove(begin(allIID[VariateMethod::IID]), end(allIID[VariateMethod::IID]), bit);
                }
            }

            if (parts.size() > 2) {
                for (auto crn: StringUtils::split(parts[2], ",")) {
                    if (crn.empty()) break;
                    int bit = stoi(crn);
                    group[VariateMethod::COMMON].push_back(bit);
                    remove(begin(allIID[VariateMethod::IID]), end(allIID[VariateMethod::IID]), bit);
                }
            }

            result.push_back(group);

            if (pooled) {
                for (int i = 1; i < 4; i++) {
                    auto clone = group;
                    for (int j = 0; j < group[VariateMethod::IID].size(); j++) {
                        int bit = clone[VariateMethod::IID][j] + i * REGION_VECTOR_SIZE;
                        clone[VariateMethod::IID][j] = bit;
                        remove(begin(allIID[VariateMethod::IID]), end(allIID[VariateMethod::IID]), bit);
                    }

                    for (int j = 0; j < group[VariateMethod::COMMON].size(); j++) {
                        int bit = clone[VariateMethod::COMMON][j] + i * REGION_VECTOR_SIZE;
                        clone[VariateMethod::COMMON][j] = bit;
                        remove(begin(allIID[VariateMethod::IID]), end(allIID[VariateMethod::IID]), bit);
                    }
                    for (int j = 0; j < group[VariateMethod::ANTITHETIC].size(); j++) {
                        int bit = clone[VariateMethod::ANTITHETIC][j] + i * REGION_VECTOR_SIZE;
                        clone[VariateMethod::ANTITHETIC][j] = bit;
                        remove(begin(allIID[VariateMethod::IID]), end(allIID[VariateMethod::IID]), bit);
                    }
                    result.push_back(clone);
                }
            }
        }

        file.close();
        if (allIID[VariateMethod::IID].size())
            result.push_back(allIID);

        return result;
    }

    static void toFile(IntraVariates variates, string filePath) {
        ofstream file(filePath);
        for (auto group: variates) {
            if (group[VariateMethod::ANTITHETIC].size() + group[VariateMethod::COMMON].size() == 0)
                continue;

            for (int bit: group[VariateMethod::IID])
                file << bit << ',';
            file.seekp(-1, ios_base::end);
            file << ';';

            for (int bit: group[VariateMethod::ANTITHETIC])
                file << bit << ',';
            file.seekp(-1, ios_base::end);
            file << ';';

            for (int bit: group[VariateMethod::COMMON])
                file << bit << ',';
            file.seekp(-1, ios_base::end);
            file << ' ' << endl;
        }
        file.close();
    }
};


#endif //EXPERIMENTS_INTRAVARIATES_H
