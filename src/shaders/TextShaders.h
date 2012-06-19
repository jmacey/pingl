#ifndef TEXTSHADERS_H__
#define TEXTSHADERS_H__

static const char * textVertexShader[]={
  "precision highp float; \n"
    "attribute vec2 inVert; \n"
    "attribute vec2 inUV; \n"
    "varying vec2 vertUV; \n"
    "uniform vec3 textColour; \n"
    "uniform float scaleX; \n"
    "uniform float scaleY; \n"
    "uniform float xpos;  \n"
    "uniform float ypos; \n"
    "void main() \n"
    "{ \n"
    "vertUV=inUV; \n"
    "gl_Position=vec4( ((xpos+inVert.x)*scaleX)-1.0,((ypos+inVert.y)*scaleY)+1.0,0.0,1.0); \n"
    "}\n\0"
  };

const char * textFragmentShader[]={
  "precision highp float; \n"
    "uniform sampler2D tex; \n"
    "varying mediump vec2 vertUV; \n"
    "uniform vec3 textColour; \n"
    "void main() \n"
    "{ \n"
    "vec4 text=texture2D(tex,vertUV.st); \n"
    "gl_FragColor.rgb=textColour.rgb; \n"
    "gl_FragColor.a=text.a; \n"
    "}\n\0"
 };


#endif

