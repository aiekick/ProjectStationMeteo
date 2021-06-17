#version 330 core

uniform float time;
uniform vec2 size;

out vec4 fragColor;

void main(void)
{
    vec2 g = gl_FragCoord.xy / size;
    vec3 c = 0.5 + 0.5 * cos(time + g.xyx + vec3(0.0,2.0,4.0));
    fragColor = vec4(c, 1.0);
}
