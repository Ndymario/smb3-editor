#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "levelParser.h"
#include "constants.h"

using namespace std;

string commentParser(string data){
    int index = 0;
    string tempData = data;

    // Loop through the data, if at any point we find a ";", we need to truncate the data
    while(tempData[index] != '\0'){
        if(tempData[index] == ';'){
            tempData[index] = '\0';
            break;
        }
        index++;
    }

    return tempData;
}

void dataInserter(string data, int index){
    string truncated;
    // Since we know the level headers are the first seven lines of any given level,
    // we can use what index we are on as a "line count" for parsing the level header.
    if (index < 7){
        // Frist, determine if there are multiple level flags in the line (found with the or operator)
        // If it does have an or operator, loop through every flag.
        // Otherwise, just save the single flag
        char orChar = '|';
        int or_pos = data.find(orChar);
        int pos = data.find(' ');
        if (or_pos != string::npos){
            if(index == 2){
                truncated = data.substr(pos + 1);
                truncated.erase(or_pos - 1);
                levelData.levelSize = levelHeaders.at(truncated);

                truncated = data.substr(or_pos + 2);
                levelData.playerStartY = levelHeaders.at(truncated);
            }

            if(index == 3){
                truncated = data.substr(pos + 1);
                truncated.erase(or_pos - 1);
                levelData.levelPalette = levelHeaders.at(truncated);

                truncated = data.substr(or_pos + 2);
                or_pos = data.find(orChar, or_pos+1);
                truncated.erase(or_pos - 1);
                levelData.objectPalette = levelHeaders.at(truncated);

                or_pos = data.find(orChar, or_pos + 1);
                truncated = data.substr(or_pos + 2);
                or_pos = data.find(orChar, or_pos+1);
                truncated.erase(or_pos - 1);
                levelData.playerStartX = levelHeaders.at(truncated);

                or_pos = data.find(orChar, or_pos + 1);
                truncated = data.substr(or_pos + 2);
                levelData.levelUnusedFlag = levelHeaders.at(truncated);
            }

            if(index == 4){
                truncated = data.substr(pos + 1);
                truncated.erase(or_pos - 1);
                levelData.subLevelTileset = levelHeaders.at(truncated);

                truncated = data.substr(or_pos + 2);
                or_pos = data.find(orChar, or_pos+1);
                truncated.erase(or_pos - 1);
                levelData.verticalScrollLock = levelHeaders.at(truncated);

                or_pos = data.find(orChar, or_pos + 1);
                truncated = data.substr(or_pos + 2);
                levelData.pipesExitToMap = levelHeaders.at(truncated);
            }

            if(index == 5){
                truncated = data.substr(pos + 1);
                truncated.erase(or_pos - 1);
                levelData.backgroundBank = levelHeaders.at(truncated);

                truncated = data.substr(or_pos + 2);
                levelData.levelEntranceType = levelHeaders.at(truncated);
            }
            if(index == 6){
                truncated = data.substr(pos + 1);
                truncated.erase(or_pos - 1);
                levelData.levelBGM = levelHeaders.at(truncated);

                truncated = data.substr(or_pos + 2);
                levelData.levelTimer = levelHeaders.at(truncated);
            }
        } else{
            // Since we know it's only one flag, store it in our truncated string
            truncated = data.substr(pos + 1);

            if (index == 0){
                levelData.subLevel = levelHeaders.at(truncated);
            } else{
                levelData.altObject = levelHeaders.at(truncated);
            }
        }
    }

    else{
        char hex = '$';
        int hexPos = data.find(hex);
        if(hexPos != string::npos){
            while((hexPos = data.find(hex)) != string::npos){
                truncated = data.substr(hexPos + 1, 2);
                levelData.levelData.push_back(stoi(truncated, 0, 16));
                hexPos = data.find(hex, hexPos + 1);
                if(hexPos == string::npos){
                    break;
                }
            }
        } else{
            return;
        }
    }
}

level levelParser(string level){
    // Open the passed level (defaults to 1-1)
    fstream levelFile;
    levelFile.open(level, ios::in);

    if(levelFile.is_open()){
        string data;
        
        // First, get the level header information
        for (int i = 0; i < 7; i++){
            getline(levelFile, data);

            // If for whatever reason there's a blank line, skip it
            if(data.length() == 0){
                i--;
                continue;
            }
            
            // Skip any stray comments
            if(data[0] == ';'){
                i--;
                continue;
            }

            // Parse any comments out
            data = commentParser(data);

            // Insert the data into our level data variable
            dataInserter(data, i);

        }
    }

    return levelData;
}