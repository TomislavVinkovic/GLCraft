#pragma once

#include "Character.h"
#include "TextureAtlas.h"
#include "Parser.h"
#include <unordered_map>
#include <string>

class CharacterSet {
    private:
        std::string fntFilePath;
        TextureAtlas charactersTexture;
        std::unordered_map<int, Character> characters;
    public:
        CharacterSet() = default;
        CharacterSet(
            const std::string& fntFile,
            const std::string textureFile
        );

        //setters
        void setFntFile(const std::string& filePath);
        void setTexture(const std::string& filePath);

        //getters
        const std::unordered_map<int, Character>& getCharacters() const;

        //parse the necessary files
        void parse();

};
