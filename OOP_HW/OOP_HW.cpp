#include <iostream>
#include "Message.h"

int main()
{
    Message m1(1, "Teodor beshe tuk");
    Message m2(1, "Teodor ne beshe tuk");

    std::cout << m1.getContent() << " " << m1.getTimeStamp() << std::endl;
    std::cout << m2.getContent() << " " << m2.getTimeStamp() << std::endl;

}
