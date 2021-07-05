#version 330 core
        layout (location = 0) in vec3 aPos;
        layout( location= 1) in vec3 acolor;
        layout(location=2) in vec2 myatex;
        //uniform vec3 pi;
        out vec3 ourcolor;
        out vec4 tofrag;
        out vec2 atex;
        uniform mat4 transform;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main()
        {
        gl_Position = projection * view * model * vec4(aPos, 1.0);
        ourcolor = acolor;
        tofrag=vec4(aPos,1.0);
        atex=myatex;
        }