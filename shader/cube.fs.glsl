#version 400

// get color from vertex shader
in vec3 vcolor;

// send color to screen
layout(location = 0) out vec4 fcolor;

void main(void)
{
    // set fragment color
    fcolor = vec4(normalize(vcolor), 1);
}
