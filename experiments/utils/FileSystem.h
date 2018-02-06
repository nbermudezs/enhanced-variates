/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 1/31/18
 */

#ifndef EXPERIMENTS_FILESYSTEM_H
#define EXPERIMENTS_FILESYSTEM_H

#include <array>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "../Constants.h"
using namespace std;

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}


template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

class FileSystem {
public:
    static void mkdir(string path, bool recursive) {
        string cmd = "mkdir ";
        cmd += recursive ? "-p " : "";
        cmd += path;
        system(cmd.c_str());
    }

    static string createRunFolder() {
        string lsCmd = "cd " + RESULTS_PATH + "/runs; ls -1 -d run*";
        string ls = exec(lsCmd.c_str());
        vector<string> dirs = split(ls, '\n');
        if (dirs.size()) {
            sort(begin(dirs), end(dirs), [](string a, string b) {
                return stoi(a.replace(0, 3, "")) > stoi(b.replace(0, 3, ""));
            });
        }
        int last = dirs.size() ? stoi(dirs[0].replace(0, 3, "")) : -1;
        string newDir = RESULTS_PATH + "/runs/run" + to_string(last + 1);
        mkdir(newDir, false);

        return newDir;
    }
};

#endif //EXPERIMENTS_FILESYSTEM_H
