#include <iostream>
#include <shiva/version.h>

int main()
{
  std::cout << "Shiva version = " << 
    SHIVA_MAJOR_VERSION << "." <<
    SHIVA_MINOR_VERSION << "." <<
    SHIVA_SUBMINOR_VERSION << "." <<
    SHIVA_UPDATE_VERSION <<
    "\n";
}