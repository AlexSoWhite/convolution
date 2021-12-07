#include "Resolver.h"

const std::vector<std::string> menu = {
        "1. Linear Convolution",
        "2. Circular Convolution",
        "3. Two dimensional linear convolution",
        "4. Two dimensional circular convolution",
        "5. Interpolation",
        "6. Thinning",
        "7. exit"
};

int main() {
    bool run = true;
    srand(time(nullptr));
    while (run) {
        for (const auto &_s: menu) {
            std::cout<<_s<<std::endl;
        }
        std::cout<<"> ";
        char c;
        std::cin>>c;
        switch (c) {
            case '1':
                resolve(LINEAR);
                break;
            case '2':
                resolve(CIRCULAR);
                break;
            case '3':
                resolve(DLINEAR);
                break;
            case '4':
                resolve(DCIRCULAR);
                break;
            case '5':
                resolve(INTERPOLATION);
                break;
            case '6':
                resolve(THINNING);
                break;
            case '7':
                run = false;
                break;
            default:
                std::cout<<"incorrect input"<<std::endl;
        }
    }
    return 0;
}
