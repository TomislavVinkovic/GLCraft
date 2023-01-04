cmake_minimum_required(VERSION 3.24)
project(GLCraft)

set(CMAKE_CXX_STANDARD 17)
include_directories(src include/glad include/stb_image include/glm Shader Application Camera State Renderer Model Texture Model/Chunk)

set(SOURCE_FILES
        include/glad/glad.c
        main.cpp Camera/Camera.cpp
        Application/Context.cpp

        Application/Application.cpp
        Renderer/Renderer.cpp
        Renderer/Cube/CubeRenderer.cpp
        Renderer/Chunk/ChunkRenderer.cpp
        Model/Block/Block.cpp
        Texture/BasicTexture.cpp
        Camera/Movement.h Model/Chunk/ChunkBlock.cpp Model/Chunk/ChunkBlock.h Model/Chunk/Chunk.cpp Model/Chunk/Chunk.h Model/Chunk/ChunkGenerator.cpp Model/Chunk/ChunkGenerator.h Model/Chunk/ChunkBlockType.h Model/Chunk/Face.h Model/Chunk/Face.h Model/Chunk/FaceIndices.h Model/Chunk/AdjacentBlockPositions.h Exceptions/NotImplementedException.h Renderer/AbstractObjectRenderer.h)


add_executable(GLCraft ${SOURCE_FILES} Application/Context.cpp Application/Context.h Model/Chunk/Face.h)

target_link_libraries(GLCraft glfw3 wayland-client m GL GLU)
