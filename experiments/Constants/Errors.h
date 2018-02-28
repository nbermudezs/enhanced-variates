/**
 * @author Nestor Bermudez Sarmiento
 * @email nab6@illinois.edu
 * @email nestor.bermudezs@gmail.com
 * @version 1.0, 2/26/18
 */

#ifndef EXPERIMENTS_ERRORS_H
#define EXPERIMENTS_ERRORS_H

#include <stdexcept>
using namespace std;

namespace Dependency {
    const runtime_error FILE_FORMAT_ERROR = std::runtime_error("Dependecy file format error");
}

#endif //EXPERIMENTS_ERRORS_H
