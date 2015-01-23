#version 410

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D aSampler;

void main() {
    vec4 textureColor = texture(aSampler, fragmentUV);
    
    color = fragmentColor * textureColor;
}