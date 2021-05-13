#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "types.h"

// Struct for a SMB3 level; includes all "level headers" and level data
struct level
{
    u16 subLevel;
    u8 subLevelTileset;
    u16 altObject;
    u8 levelSize;
    u8 playerStartX;
    u8 playerStartY;
    u8 levelPalette;
    u8 objectPalette;
    u8 levelUnusedFlag;
    u8 verticalScrollLock;
    u8 pipesExitToMap;
    u8 backgroundBank;
    u8 levelEntranceType;
    u8 levelBGM;
    u8 levelTimer;
    std::vector <u8> levelData;
    std::vector <u8> objectData;
};

// Create a variable to store the level data
static level levelData;

// Function that parses level data from a passed level directory
level levelParser(std::string level = "smb3-master/PRG/levels/plains/1-1.asm");
