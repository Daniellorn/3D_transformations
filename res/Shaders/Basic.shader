#shader vertex
#version 460 core


layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 color;


//out vec3 v_Position;
out vec3 v_vertexColor;

void main()
{
    //v_Position = aPos;
    //gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    gl_Position = vec4(aPos, 1.0);

    v_vertexColor = color;
};



#shader fragment
#version 460 core

layout (location = 0) out vec4 FragColor; 

//in vec3 v_Position;
in vec3 v_vertexColor;

void main()
{
   //FragColor = vec4(v_Position * 0.5 + 0.5, 1.0f);
   FragColor = vec4(v_vertexColor, 1.0f);
};