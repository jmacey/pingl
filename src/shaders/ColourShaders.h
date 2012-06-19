#ifndef COLOURSHADERS_H__
#define COLOURSHADERS_H__


static const char * colourVertexShader[]={
"uniform mat4 MVP; \n"
"attribute vec3 inVert; \n"
"uniform vec4 Colour; \n"
"void main(void) \n"
"{ \n"
"  gl_Position = MVP*vec4(inVert, 1.0); \n"
"} \n "
};




static const char *  colourFragmentShader[]={
"uniform vec4 Colour; \n"
"void main() \n"
"{ \n"
"  gl_FragColor = Colour; \n"
"} \n"
};

#endif

