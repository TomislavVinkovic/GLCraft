cmake_minimum_required(VERSION 3.24)
project(GLCraft)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")
#add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
include_directories(src Util World Maths  include/glad include/stb_image include/glm include/imgui Shader Application Camera State Renderer Model Texture Model/Chunk Player World NoiseGenerator Text)

set(SOURCE_FILES
        include/glad/glad.c
        include/imgui/imgui.cpp
        include/imgui/imgui_draw.cpp
        include/imgui/imgui_demo.cpp
        include/imgui/imgui_impl_glfw_gl3.cpp
        main.cpp Camera/Camera.cpp
        Application/Context.cpp

        Application/Application.cpp
        Renderer/Renderer.cpp
        Renderer/Cube/CubeRenderer.cpp
        Renderer/Chunk/ChunkRenderer.cpp
        Model/Block/Block.cpp
        Texture/BasicTexture.cpp
        Camera/Movement.h Model/Chunk/ChunkBlock.cpp Model/Chunk/ChunkBlock.h Model/Chunk/Chunk.cpp Model/Chunk/Chunk.h Model/Chunk/ChunkGenerator.cpp Model/Chunk/ChunkGenerator.h Model/Chunk/ChunkBlockType.h Model/Chunk/Face.h Model/Chunk/Face.h Model/Chunk/AdjacentBlockPositions.h Exceptions/NotImplementedException.h Renderer/AbstractObjectRenderer.h Model/Chunk/AdjacentChunkPositions.h Texture/TextureAbstract.h Texture/TextureAtlas.cpp Texture/TextureAtlas.h Model/Chunk/ChunkBlockData.h Player/Player.cpp Player/Player.h Player/Inventory.cpp Player/Inventory.h Camera/Ray.cpp Camera/Ray.h State/State.cpp State/State.h World/World.cpp World/World.h Renderer/UIRenderer/UIRenderer.cpp Renderer/UIRenderer/UIRenderer.h Renderer/Skybox/SkyboxRenderer.cpp Renderer/Skybox/SkyboxRenderer.h Texture/CubeMap.cpp Texture/CubeMap.h NoiseGenerator/NoiseGenerator.cpp NoiseGenerator/NoiseGenerator.h Model/Chunk/ChunkBlockData.cpp Text/Character.h Text/CharacterSet.cpp Text/CharacterSet.h Text/Parser.cpp Text/Parser.h Renderer/ImGuiRenderer/ImGuiRenderer.cpp Renderer/ImGuiRenderer/ImGuiRenderer.h World/Generation/Biome/Biome.cpp World/Generation/Biome/Biome.h Util/NonCopyable.h Util/NonMovable.h Util/Random.cpp Util/Random.h Util/Singleton.h World/Generation/Biome/DesertBiome.cpp World/Generation/Biome/DesertBiome.h World/Generation/Biome/ForestBiome.cpp World/Generation/Biome/ForestBiome.h World/Generation/Biome/GrassLandBiome.cpp World/Generation/Biome/GrassLandBiome.h World/Generation/Terrain/TerrainGenerator.cpp World/Generation/Terrain/TerrainGenerator.h World/Generation/Biome/OceanBiome.cpp World/Generation/Biome/OceanBiome.h Maths/InterpolationMaths.cpp Maths/InterpolationMaths.h World/Generation/Tree/TreeGenerator.cpp World/Generation/Tree/TreeGenerator.h Maths/ViewFrustum.cpp Maths/ViewFrustum.h Maths/ABAB.h Maths/ABAB.h)


add_executable(GLCraft ${SOURCE_FILES} Application/Context.cpp Application/Context.h Model/Chunk/Face.h)

target_link_libraries(GLCraft glfw3 wayland-client m GL GLU)
