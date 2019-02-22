//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Utility.h"

#include <iostream>
#include <fstream>

std::string UnitTestUtil::GetSysSeparator()
{
#ifdef _WINDOWS
    return "\\";
#else
    return "/";
#endif
}


std::string UnitTestUtil::GetTestResoucreFolder()
{
    std::string sep = GetSysSeparator();

    return std::string(GITPATH) + sep + "files";
}

bool UnitTestUtil::FileExists(std::string fullPath)
{
    std::ifstream f(fullPath.c_str());
    return f.good();
}

void UnitTestUtil::print_Ascii_BUG()
{
std::cout <<"  ,--.       ,---. "<< std::endl;
std::cout <<"  /    '.    /     \\ "<< std::endl;
std::cout <<"         \\  ; "<< std::endl;
std::cout <<"          \\-| "<< std::endl;
std::cout <<"         (o o)      (/    An ERROR occured."<< std::endl;
std::cout <<"         /'v'     ,-' "<< std::endl;
std::cout <<" ,------/ >< \\---' "<< std::endl;
std::cout <<"/)     ;  --  : "<< std::endl;
std::cout <<"   ,---| ---- |--. "<< std::endl;
std::cout <<"  ;    | ---- |   : "<< std::endl;
std::cout <<" (|  ,-| ---- |-. |) "<< std::endl;
std::cout <<"    | /| ---- |\\ | "<< std::endl;
std::cout <<"    |/ | ---- | \\| "<< std::endl;
std::cout <<"    \\  : ---- ;  | "<< std::endl;
std::cout <<"     \\  \\ -- /  / "<< std::endl;
std::cout <<"     ;   \\  /  : "<< std::endl;
std::cout <<"    /   / \\/ \\  \\ "<< std::endl;
std::cout <<"   /)           (\\"<< std::endl;
}

