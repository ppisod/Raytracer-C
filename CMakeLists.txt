cmake_minimum_required(VERSION 4.0)
project(RayTracer C)

set(CMAKE_C_STANDARD 11)

add_executable(RayTracer main.c
        lib/vec3.c
        lib/vec3.h
        lib/vec2.c
        lib/vec2.h
        lib/ray.c
        lib/ray.h
        shape/sphere.c
)
