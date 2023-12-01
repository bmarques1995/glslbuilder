# OpenGL Shading Language Solution (.gls2)

GLS2 is the pattern of solution that incorporates a set of GLSL shaders, is inspired on visual studio strategy of C/C++ solutions. It is a json text, storing a set of properties:

* `GraphicsPipelineSources` : stores all graphics pipeline shaders, the default shaders, to be built, all pipeline stages used by the shader must be present, all will be compiled at once, following some rules:
  * Vertex and Pixel shader are required
  * Geometry shader is optional
  * If Domain shader is present, hull shader is required
* `GraphicsPipeline->VertexEntry` : stores the vertex shader entryponint
* `GraphicsPipeline->PixelEntry` : stores the pixel shader entryponint

Obs: The arrow `->` indicates a subproperty.

## Parameters Rules

* `Name`: starts with a letter or `_` and follows a letter, a digit or a `_`
* `Sources`: must be valid paths

## FutureChanges(it will be removed from this section by implementation)

* Support Geometry, Hull and Domain shaders
* Add include options
* Process GraphicsPipeline tokens:
  * InputLayout
  * ConstantBuffers(for all others pipelines)
* Add Compute Pipeline
* Add RayTracing Pipeline
* Add Mesh Pipeline
