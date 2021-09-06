#version 330 core
        out vec4 fragcolor;

        in vec3 ourcolor;
        in vec4 tofrag;
        in vec2 atex;
        uniform sampler2D mytexture;
        uniform sampler2D mytexture1;
        uniform float tp;

        void main()
        {
        fragcolor=mix(texture(mytexture,atex),texture(mytexture1,atex),tp+0.2);
        //fragcolor = (ourcolor, 1.0);
        }