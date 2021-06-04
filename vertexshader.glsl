#version 330 core
        layout (location = 0) in vec3 aPos;
        layout( location= 1) in vec3 acolor;
        layout(location=2) in vec2 myatex;
        //uniform vec3 pi;
        out vec3 ourcolor;
        out vec4 tofrag;
        out vec2 atex;
        void main()
        {
        gl_Position = vec4(aPos, 1.0);
        ourcolor = acolor;
        tofrag=vec4(aPos,1.0);
        atex=myatex;
        }