#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <iostream>
#include <string>
#include <vector>

namespace EzChat {
    /**
     * @class ErrorHandler logs errors for debugging
     * @author Arvin Sharma
     */
    class ErrorHandler {

        public:
            /**
             * logs the given error to this handler
             * @param error is the error to record
             */
            void logError(std::string error) noexcept;
            /**
             * prints out all of the errors contained to
             * the given output stream
             * @param output is the output stream
             */
            void dump(std::ostream output) const noexcept;
            /**
             * clears all errors currently held in this buffer
             */
            void clearContents() noexcept;
        private:
            std::vector<std::string> log_;
    };
}
#endif
