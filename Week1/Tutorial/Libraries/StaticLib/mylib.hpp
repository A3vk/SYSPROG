#ifndef MYLIB_H_
#define MYLIB_H_

#include <string>

namespace mylib {
    class myclass {
        public:
            myclass(const std::string& message);
            const std::string& message() const { return _message; }

        private:
            std::string _message;
    };
}

#endif // MYLIB_H_
