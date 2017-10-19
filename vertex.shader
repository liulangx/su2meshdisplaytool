#version 430 core
//in layout(location=0) vec3 Position;
in vec3 Position;
//in layout(location=1) vec4 Color;
in vec4 Color;
//in vec2 textureCoords;
uniform vec2 xrange;
uniform vec2 yrange;
uniform vec2 zrange;

uniform vec3 baseCoord;
uniform int choose;

uniform float scale;
uniform mat4 move;
uniform mat4 rot;


out vec4 outcolor;
//out vec2 pass_texture;
void main(void)
{
    mat4 reverse = mat4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, -1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
//    mat4 zoomMove = mat4(
//            1.0f, 0.0f, 0.0f, 0.0f,
//            0.0f, 1.0f, 0.0f, 0.0f,
//            0.0f, 0.0f, 1.0f, - scale + 1,
//            0.0f, 0.0f, 0.0f, 1.0f
//        );
//    mat4 _rot = mat4(
//        0.866f, 0.0f, -0.5f, 0.0f,
//        0.0f, 1.0f, 0.0f, 0.0f,
//        0.5f, 0.0f, 0.866f, 0.0f,
//                0.0f,0.0f,0.0f,1.0f
//    );
    //outcolor = Color;
    float X = xrange.x - xrange.y;
    float Y = yrange.x - yrange.y;
    float Z = zrange.x - zrange.y;
    vec4 _tmpPosition;
    if(1 == choose)
    {
        _tmpPosition = /*_rot */ vec4(((Position.x - xrange.y) / X * 2 - 1) * scale, ((Position.y - yrange.y) / Y * 2 - 1) * scale, ((Position.z - zrange.y) / Z * 2 - 1) * scale, 1);
        outcolor = vec4(0.0, 0.0, 1.0, 1);
    }
    else if(0 == choose)
    {
        _tmpPosition = vec4(Position, 1);
        outcolor = Color;
    }


    gl_Position = /*zoomMove * */move * rot * reverse *  _tmpPosition;

};
//out_color = mix(texture(texture, pass_texture),texture(texture1,pass_texture),0.3);
