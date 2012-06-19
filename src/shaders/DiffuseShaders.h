#ifndef DIFFUSESHADERS_H__
#define DIFFUSESHADERS_H__


const std::string diffuseVertexShader =
R"DELIM(
#version 150
/// @brief the current fragment normal for the vert being processed
out vec3 fragmentNormal;
/// @brief the vertex passed in
in vec3 inVert;
/// @brief the normal passed in
in vec3 inNormal;

// transform matrix values
uniform mat4 MVP;

void main(void)
{
// calculate the fragments surface normal
 fragmentNormal = inNormal;

 // calculate the vertex position
 gl_Position = MVP*vec4(inVert,1.0);

}

)DELIM";




const std::string  diffuseFragmentShader=
R"DELIM(
#version 150

/// @brief[in] the vertex normal
in vec3 fragmentNormal;
/// @brief our output fragment colour
out vec4 fragColour;

uniform vec4 Colour;

uniform vec3 lightPos;

void main ()
{
  // set the output colour to black
  fragColour= vec4(0.);
  // normalize the vertex normal
  vec3 N = normalize(fragmentNormal);
  // The Light source vector
  // get the Light vector
  vec3 L = normalize(lightPos);
  // calculate diffuse based on Lambert's law (L.N)
  fragColour += Colour  *light.diffuse *dot(L, N);
}
)DELIM";

#endif

