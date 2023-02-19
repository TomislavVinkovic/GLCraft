#include "Biome.h"

Biome::Biome(const NoiseParameters &parameters, int treeFreq, int plantFreq,
             int seed)
        : m_heightGenerator(seed)
        , m_treeFreq(treeFreq)
        , m_plantFreq(plantFreq)
{
    m_heightGenerator.setParameters(parameters);
}

const ChunkBlockData& Biome::getBeachBlock(Rand &rand) const
{
    return block_type::SandBlock;
}

int Biome::getHeight(int x, int z, int chunkX, int chunkZ) const
{
    return m_heightGenerator.getHeight(x, z, chunkX, chunkZ);
}

int Biome::getTreeFrequency() const noexcept
{
    return m_treeFreq;
}

int Biome::getPlantFrequency() const noexcept
{
    return m_plantFreq;
}

const ChunkBlockData &Biome::getUndergroundBlock(Rand &rand) const {
    return block_type::DirtBlock;
}

const ChunkBlockData &Biome::getFlowerBlock(Rand &rand) const {
    return block_type::FlowerBlock;
}

int Biome::getMineralFrequency() const noexcept {
    return mineralFreq;
}

const ChunkBlockData &Biome::getMineralBlock(Rand &rand) const {
    auto r = rand.intInRange(0,10);
    if(r < 5) return block_type::MathosBlock;
    if(r >= 5 && r <= 8) return block_type::CoalBlock;
    else return block_type::MathosSinisterBlock;
}
