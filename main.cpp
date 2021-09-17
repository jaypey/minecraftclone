#include <iostream>
#include  "blockinfo.h"
#include "blockarray3d.h"

int main()
{
    //Tests de BlockInfo
    std::cout << "--------------------" << std::endl;
    std::cout << "|TESTS DE BLOCKINFO|" << std::endl;
    std::cout << "--------------------" << std::endl;
    BlockInfo blockInfo1(BTYPE_DIRT_, "Terre");
    blockInfo1.SetDurability(52);
    std::cout << "\033[4m Get/Set Durability \033[0m" << std::endl;
    std::cout << blockInfo1.GetDurability() << std::endl;
    std::cout << "\033[4m Block Info Show \033[0m" << std::endl;
    blockInfo1.Show();
    std::cout << "--------------------" << std::endl;

    //Tests BlockArray
    std::cout << "--------------------" << std::endl;
    std::cout << "|TESTS DE BLOCKARRAY|" << std::endl;
    std::cout << "--------------------" << std::endl;
    BlockArray3d blockArray1(2, 2, 2);
    blockArray1.Reset(BTYPE_GRASS);
    std::cout << "\033[4m Get Block from Reset \033[0m" << std::endl;
    std::cout << blockArray1.Get(0,1,0) << std::endl;
    std::cout << "\033[4m Set Block \033[0m" << std::endl;
    blockArray1.Set(0,1,0, BTYPE_AIR);
    std::cout << blockArray1.Get(0,1,0) << std::endl;
    std::cout << "--------------------" << std::endl;
}