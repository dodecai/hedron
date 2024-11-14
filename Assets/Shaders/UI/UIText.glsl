#type vertex
#version 450 core
#include <Common.glslh>

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in float aTexIndex;

layout(location = 0) out vec4 vColor;
layout(location = 1) out vec2 vTexCoord;
layout(location = 2) out float vTexIndex;

layout(std140, binding = 0) uniform Transform {
    mat4 uProjection;
    mat4 uView;
};

void main() {
    vColor = aColor;
    vTexCoord = aTexCoord;
    vTexIndex = aTexIndex;

    gl_Position = uProjection * uView * vec4(aPosition, 1.0);
}

#type fragment
#version 450 core
#include <Common.glslh>

layout(location = 0) in vec4 vColor;
layout(location = 1) in vec2 vTexCoord;
layout(location = 2) in float vTexIndex;

layout(location = 0) out vec4 oColor;

//layout(binding = 0) uniform sampler2D uFontAtlas;
layout(binding = 0) uniform sampler2D uTextures[32];

float ScreenPixelRange() {
	const float pxRange = 1.0; // set to distance field's pixel range
    //vec2 unitRange = vec2(pxRange) / vec2(textureSize(uFontAtlas, 0));
    vec2 unitRange = vec2(pxRange) / vec2(textureSize(uTextures[int(vTexIndex)], 0));
    vec2 screenTexSize = vec2(1.0) / fwidth(vTexCoord);
    return max(0.5 * dot(unitRange, screenTexSize), 1.0);
}

float Median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

void main() {
    //vec4 texColor = vColor * texture(uFontAtlas, vTexCoord);
    vec4 texColor = texture(uTextures[int(vTexIndex)], vTexCoord) * vColor;

    //vec3 msd = texture(uFontAtlas, vTexCoord).rgb;
    vec3 msd = texture(uTextures[int(vTexIndex)], vTexCoord).rgb;
    float sd = Median(msd.r, msd.g, msd.b);
    float screenPixelDistance = ScreenPixelRange()*(sd - 0.5);
    float opacity = clamp(screenPixelDistance + 0.5, 0.0, 1.0);
	if (opacity == 0.0) discard;

	vec4 bgColor = vec4(0.0);
    oColor = mix(bgColor, vColor, opacity);
	if (oColor.a == 0.0) discard;
}