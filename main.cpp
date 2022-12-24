#include "mbed.h"
#include "ICM_20948.h"

using namespace ECE4180;

ICM_20948 icm(p28, p27);
BufferedSerial pc(USBTX, USBRX);
// main() runs in its own thread in the OS
int main()
{
    ICM_20948_selfTest(icm, &pc);
    return 0;
}

