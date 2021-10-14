
# OPENGLNGINE

OpenGL sandbox.

## CI

![Build Status](https://github.com/PamplemousseMR/OPENGLNGINE/actions/workflows/build.yml/badge.svg)

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

- [Conan](https://conan.io/): The C / C++ Package Manager for Developers.
- [OpenGL](https://www.opengl.org/): An environment for developing portable, interactive 2D and 3D graphics applications.
- [glew](http://glew.sourceforge.net/index.html): The OpenGL Extension Wrangler Library.
- [glfw](http://www.glfw.org/): It provides a simple API for creating windows, contexts and surfaces, receiving input and events.
- [glm](https://github.com/g-truc/glm) : A mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications.
- [SOIL2](https://github.com/SpartanJ/SOIL2): A tiny C library used primarily for uploading textures into OpenGL. into OpenGL.
- [assimp](https://assimp.org/): The official Open-Asset-Importer-Library Repository. Loads 40+ 3D-file-formats into one unified and clean data structure.

## Documentation

### Coordinate systems

OpenGL expects all the vertices, that we want to become visible, to be in normalized device coordinates after each vertex shader run. That is, the  `x`,  `y`  and  `z`  coordinates of each vertex should be between  `-1.0`  and  `1.0`; coordinates outside this range will not be visible. What we usually do, is specify the coordinates in a range (or space) we determine ourselves and in the vertex shader transform these coordinates to normalized device coordinates (NDC). These NDC are then given to the rasterizer to transform them to 2D coordinates/pixels on your screen.

Transforming coordinates to NDC is usually accomplished in a step-by-step fashion where we transform an object's vertices to several coordinate systems before finally transforming them to NDC. The advantage of transforming them to several  _intermediate_  coordinate systems is that some operations/calculations are easier in certain coordinate systems as will soon become apparent. There are a total of 5 different coordinate systems that are of importance to us:

-   Local space (or Object space)
-   World space
-   View space (or Eye space)
-   Clip space
-   Screen space

Those are all a different state at which vertices will be transformed in before finally ending up as fragments.

To transform the coordinates from one space to the next coordinate space we'll use several transformation matrices of which the most important are the model, view and projection matrix. Our vertex coordinates first start in local space as local coordinates and are then further processed to world coordinates, view coordinates, clip coordinates and eventually end up as screen coordinates. The following image displays the process and shows what each transformation does:

![coordinate_systems](https://github.com/PamplemousseMR/OPENGLNGINE/blob/master/media/coordinate_systems.png)

1.  Local coordinates are the coordinates of your object relative to its local origin; they're the coordinates your object begins in.
2.  The next step is to transform the local coordinates to world-space coordinates which are coordinates in respect of a larger world. These coordinates are relative to some global origin of the world, together with many other objects also placed relative to this world's origin.
3.  Next we transform the world coordinates to view-space coordinates in such a way that each coordinate is as seen from the camera or viewer's point of view.
4.  After the coordinates are in view space we want to project them to clip coordinates. Clip coordinates are processed to the  `-1.0`  and  `1.0`  range and determine which vertices will end up on the screen. Projection to clip-space coordinates can add perspective if using perspective projection.
5.  And lastly we transform the clip coordinates to screen coordinates in a process we call  viewport transform  that transforms the coordinates from  `-1.0`  and  `1.0`  to the coordinate range defined by  glViewport. The resulting coordinates are then sent to the rasterizer to turn them into fragments.

#### Local space

Local space is the coordinate space that is local to your object, i.e. where your object begins in. Imagine that you've created your cube in a modeling software package (like Blender). The origin of your cube is probably at  `(0,0,0)`  even though your cube may end up at a different location in your final application. Probably all the models you've created all have  `(0,0,0)`  as their initial position. All the vertices of your model are therefore in  _local_  space: they are all local to your object.

The vertices of the container we've been using were specified as coordinates between  `-0.5`  and  `0.5`  with  `0.0`  as its origin. These are local coordinates.

#### World space

If we would import all our objects directly in the application they would probably all be somewhere positioned inside each other at the world's origin of  `(0,0,0)`  which is not what we want. We want to define a position for each object to position them inside a larger world. The coordinates in world space are exactly what they sound like: the coordinates of all your vertices relative to a (game) world. This is the coordinate space where you want your objects transformed to in such a way that they're all scattered around the place (preferably in a realistic fashion). The coordinates of your object are transformed from local to world space; this is accomplished with the  model  matrix.

The model matrix is a transformation matrix that translates, scales and/or rotates your object to place it in the world at a location/orientation they belong to. Think of it as transforming a house by scaling it down (it was a bit too large in local space), translating it to a suburbia town and rotating it a bit to the left on the y-axis so that it neatly fits with the neighboring houses. You could think of the matrix in the previous chapter to position the container all over the scene as a sort of model matrix as well; we transformed the local coordinates of the container to some different place in the scene/world.

#### View space

The view space is what people usually refer to as the  camera  of OpenGL (it is sometimes also known as  camera space  or  eye space). The view space is the result of transforming your world-space coordinates to coordinates that are in front of the user's view. The view space is thus the space as seen from the camera's point of view. This is usually accomplished with a combination of translations and rotations to translate/rotate the scene so that certain items are transformed to the front of the camera. These combined transformations are generally stored inside a  view matrix  that transforms world coordinates to view space. In the next chapter we'll extensively discuss how to create such a view matrix to simulate a camera.

#### Clip space

At the end of each vertex shader run, OpenGL expects the coordinates to be within a specific range and any coordinate that falls outside this range is  clipped. Coordinates that are clipped are discarded, so the remaining coordinates will end up as fragments visible on your screen. This is also where  clip space  gets its name from.

Because specifying all the visible coordinates to be within the range  `-1.0`  and  `1.0`  isn't really intuitive, we specify our own coordinate set to work in and convert those back to NDC as OpenGL expects them.

To transform vertex coordinates from view to clip-space we define a so called  projection matrix  that specifies a range of coordinates e.g.  `-1000`  and  `1000`  in each dimension. The projection matrix then transforms coordinates within this specified range to normalized device coordinates (`-1.0`,  `1.0`). All coordinates outside this range will not be mapped between  `-1.0`  and  `1.0`  and therefore be clipped. With this range we specified in the projection matrix, a coordinate of (`1250`,  `500`,  `750`) would not be visible, since the  `x`  coordinate is out of range and thus gets converted to a coordinate higher than  `1.0`  in NDC and is therefore clipped.

Note that if only a part of a primitive e.g. a triangle is outside the  clipping volume  OpenGL will reconstruct the triangle as one or more triangles to fit inside the clipping range.

This  _viewing box_  a projection matrix creates is called a  frustum  and each coordinate that ends up inside this frustum will end up on the user's screen. The total process to convert coordinates within a specified range to NDC that can easily be mapped to 2D view-space coordinates is called  projection  since the projection matrix  projects  3D coordinates to the easy-to-map-to-2D normalized device coordinates.

Once all the vertices are transformed to clip space a final operation called  perspective division  is performed where we divide the  `x`,  `y`  and  `z`  components of the position vectors by the vector's homogeneous  `w`  component; perspective division is what transforms the 4D clip space coordinates to 3D normalized device coordinates. This step is performed automatically at the end of the vertex shader step.

It is after this stage where the resulting coordinates are mapped to screen coordinates (using the settings of  glViewport) and turned into fragments.

The projection matrix to transform view coordinates to clip coordinates usually takes two different forms, where each form defines its own unique frustum. We can either create an  orthographic  projection matrix or a  perspective  projection matrix.

#### Space conversion in GLSL

```glsl
#version 150

uniform vec4 u_viewportSize;

uniform float u_clippingNearDis;
uniform float u_clippingFarDis;

/// Converts OpenGL fragment coordinates to normalized device coordinates (NDC).
vec3 fragCoordsToNDC(in vec3 _f3FragPos_Ss)
{
    vec3 f3FragPos_Ns = vec3(_f3FragPos_Ss.xy * u_viewportSize.zw, _f3FragPos_Ss.z);
    f3FragPos_Ns = (f3FragPos_Ns - 0.5) * 2.0;
    return f3FragPos_Ns;
}

//-----------------------------------------------------------------------------

/// Converts OpenGL normalized device coordinates (NDC) to fragment coordinates.
vec3 ndcToFragCoord(in vec3 _f3FragPos_Ns)
{
    vec3 f3FragPos_Ss = (_f3FragPos_Ns + 1.0) * 0.5;
    return vec3(f3FragPos_Ss.xy * u_viewportSize.xy, f3FragPos_Ss.z);
}

//-----------------------------------------------------------------------------

/// Converts a position in OpenGL's normalized device coordinates (NDC) to the specified space.
vec4 ndcToSpecificSpacePosition(in vec3 _f3FragPos_Ns, in mat4 _m4Inverse)
{
    vec4 clipPos;
    clipPos.w = (2.0 * u_clippingNearDis * u_clippingFarDis) / (u_clippingNearDis + u_clippingFarDis + _f3FragPos_Ns.z * (u_clippingNearDis - u_clippingFarDis));
    clipPos.xyz = _f3FragPos_Ns * clipPos.w;

    return _m4Inverse * clipPos;
}
```

### Camera calibration

```cpp
#include <iostream>
#include <assert.h>
#include <glm/glm.hpp>

struct Calibration
{
    float fx;
    float fy;
    float cx;
    float cy;
    float width;
    float height;
};

::glm::mat4 computeProjectionMatrix(const Calibration& _calibration, float _width, float _height, float _near, float _far)
{
    assert(_width > 0.0f && "calibration width should be > 0.");
    assert(_height > 0.0f && "height width should be > 0.");
    assert(_near > 0.0f && "near width should be > 0.");
    assert(_far > 0.0f && "far width should be > 0.");
    assert(_far > _near && "far width should be > near.");

    // Compute ratio between calibration image height and the displayed image height.
    const float ratioH = _height / _calibration.height;

    // Compute new fx, fy.
    const float nfx = _calibration.fx * ratioH;
    const float nfy = _calibration.fy * ratioH;

    // Compute principle point offset according to size of displayed image.
    float px = ratioH * _calibration.cx;
    const float py = ratioH * _calibration.cy;

    const long expectedWindowSize = std::lround(ratioH * _calibration.width);

    if (expectedWindowSize != static_cast<long>(_width))
    {
        const long diffX = (static_cast<long>(_width) - expectedWindowSize) / 2;
        px += static_cast<float>(diffX);
    }

    const float cx1 = _width - px;
    const float cy1 = _height - py;

    // Avoid divide by zero below.
    const float invWinW = std::max(1e-5f, _width - 1.f);
    const float invWinH = std::max(1e-5f, _height - 1.f);

    // Compute the offset according to current size.
    const float wcx = cx1 / (invWinW / 2.f) - 1.f;
    const float wcy = cy1 / (invWinH / 2.f) - 1.f;

    // Setup projection matrix.
    ::glm::mat4 m;

    m[0][0] = 2.f * nfx / _width;
    m[0][1] = 0.f;
    m[0][2] = wcx;
    m[0][3] = 0.f;

    m[1][0] = 0.f;
    m[1][1] = 2.f * nfy / _height;
    m[1][2] = -wcy;
    m[1][3] = 0.f;

    m[2][0] = 0.f;
    m[2][1] = 0.f;
    m[2][2] = -(_far + _near) / (_far - _near);
    m[2][3] = -2.f * _far * _near / (_far - _near);

    m[3][0] = 0.f;
    m[3][1] = 0.f;
    m[3][2] = -1.f;
    m[3][3] = 0.f;

    return m;
}
```

## Authors

* **MANCIAUX Romain** - *Initial work* - [PamplemousseMR](https://github.com/PamplemousseMR).

## License

This project is licensed under the GNU Lesser General Public License v3.0 - see the [LICENSE.md](LICENSE.md) file for details.