#include <iostream>
#include <string>
#include <vector>
#include "ErrorHandler.h"
using namespace EzChat;
using namespace std;

void ErrorHandler::logError(string error) noexcept {
    log_.push_back(error);
}

void ErrorHandler::dump(ostream output) const noexcept {
    for (auto s : log_) {
        output << s << endl;
    }
}

void ErrorHandler::clearContents() noexcept {
    log_.clear();
}
