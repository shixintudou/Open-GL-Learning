

//#version 330 core
//out vec4 fragcolor;
//
//uniform vec4 ourcolor;
//
//void main()
//{
//fragcolor=ourcolor;
//}

#version 330 core
layout( location= 0) in vec3 apos;
layout( location= 1) in vec3 acolor;

out vec3 ourcolor;
void main()
{
    gl_Position = vec4(apos, 1.0);
    ourcolor = acolor; // ��ourColor����Ϊ���ǴӶ�����������õ���������ɫ
}