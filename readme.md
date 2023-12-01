# GLSL Builder

This is a project that uses a solution to compile a set of GLSL files to its text specific target, to be compiled by opengl. Is a fork of the project [HLSLBuilder](https://github.com/bmarques1995/hlslbuilder.git).

The builder is based in 2 pipelines:

## Graphics Pipeline (.gp) (will be the first pipeline implemented)

This is the most common shader pipeline, either GLSL and HLSL, involving the following stages: vertex, domain, hull, geometry and pixel, following the rules above:

* Vertex and Pixel stages are mandatory
* Geometry stage is optional
* If Domain stage is present, Hull is mandatory

## Compute Pipeline (.cp)

This is the pipeline used to compute data on GPU using the graphics API, it only has the compute stage
