#ifndef LOADER_HPP
#define LOADER_HPP

#include "include.hpp"
#include "./model.hpp"
#include "player.hpp"

class Loader
{
public:
    Model loadVAO(const std::vector<float> &, const std::vector<unsigned int> &, const std::vector<float> &, const std::vector<float> &);
    Player loadVAOPlayer(const std::vector<float> &, const std::vector<unsigned int> &, const std::vector<float> &, const std::vector<float> &);
    unsigned int loadTexture(const std::string);
    Model loadObj(const char *);
    Player loadObjPlayer(const char *);

private:
    std::vector<unsigned int> vaos;
    std::vector<unsigned int> vbos;
    std::vector<unsigned int> textures;
    unsigned int createVAO();
    void storeDataInAttributeList(const unsigned int attributeNumber, const unsigned int size, const std::vector<float> &data);
    void unbindVAO();
    void bindIndicesBuffer(const std::vector<unsigned int> indices);
};

#endif
