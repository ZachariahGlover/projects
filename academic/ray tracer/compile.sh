#!/bin/sh
g++ -O4 svdDynamic.c RayTracer.c utils.c -lm -pthread -o RayTracer -w