﻿#type vertex
#version 450 core
#include <Buffers.glslh>

layout (location = 0) in vec3 aPosition;

void main() {
    gl_Position = uCamera.ViewProjection * uEntity.Transform * vec4(aPosition, 1.0);
}

#type fragment
#version 450 core

layout (location = 0) out vec4 FragColor;

float near = 0.1; 
float far  = 100.0; 

float LinearizeDepth(float depth) {
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main() {
    float depth = LinearizeDepth(gl_FragCoord.z) / far;
    FragColor = vec4(vec3(depth), 1.0);
}
