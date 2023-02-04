#include "CharacterSet.h"

CharacterSet::CharacterSet(const std::string &fntFile, const std::string textureFile) {
    fntFilePath = fntFile;
    charactersTexture = TextureAtlas(textureFile);
}

void CharacterSet::parse() {
    Parser::parse(fntFilePath, characters);
}

void CharacterSet::setFntFile(const std::string &filePath) {
    fntFilePath = filePath;
}

void CharacterSet::setTexture(const std::string &filePath) {
    charactersTexture = TextureAtlas(filePath, GL_RGBA);
}

const std::unordered_map<int, Character> &CharacterSet::getCharacters() const {
    return characters;
}
