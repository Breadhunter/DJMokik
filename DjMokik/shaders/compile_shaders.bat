@echo off

glslangValidator -V triangle.vert -o triangle.vert.spv
glslangValidator -V triangle.frag -o triangle.frag.spv
glslangValidator -V wave.vert -o wave.vert.spv
glslangValidator -V wave.frag -o wave.frag.spv

echo Shaders compiled
pause
