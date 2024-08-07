﻿export module Vite.Renderer.DesignerCamera;

import Vite.Bridge.GLM;
import Vite.Core;
import Vite.Device.Input;
import Vite.Renderer.Camera;

#pragma warning(push)
#pragma warning(disable: 4201)

export namespace Hedron {

class DesignerCamera: public Camera {
public:
    DesignerCamera() = default;
    DesignerCamera(float fov, float aspectRatio, float nearClip, float farClip):
        mFOV(fov),
        mAspectRatio(aspectRatio),
        mNearClip(nearClip),
        mFarClip(farClip),
        Camera(glm::Perspective(glm::radians(fov), aspectRatio, nearClip, farClip)) {
        UpdateView();
    }
    ~DesignerCamera() = default;
    
    void Update(DeltaTime delta) { // ToDo: Works everywhere, but eats the performance...
        const float cameraSpeed = 0.003f;

        if (Input::GetKeyState(KeyCode::A)) { Pan(glm::vec2(2.0, 0.0f) * cameraSpeed); }
        if (Input::GetKeyState(KeyCode::W)) { Pan(glm::vec2(0.0, 2.0f) * cameraSpeed); }
        if (Input::GetKeyState(KeyCode::D)) { Pan(glm::vec2(-2.0, 0.0f) * cameraSpeed); }
        if (Input::GetKeyState(KeyCode::S)) { Pan(glm::vec2(0.0, -2.0f) * cameraSpeed); }

        auto wheel = Input::GetMouseWheelDelta();
        // ToDo: Implement the zooming over the mouse wheel

        bool mouseButtonPressed =
            Input::GetMouseButtonState(MouseButton::Left) ||
            Input::GetMouseButtonState(MouseButton::Middle) ||
            Input::GetMouseButtonState(MouseButton::Right);

        if (!mouseButtonPressed) {
            mInitialMousePosition = glm::vec2(0.0f, 0.0f);
            UpdateView();
            return;
        }

        auto [x, y] = Input::GetMousePositionDelta();
        const glm::vec2 &mouse { x, y };

        if (mInitialMousePosition.x == 0 && mInitialMousePosition.y == 0) {
            mInitialMousePosition = mouse;
        }

        glm::vec2 mouseDelta = (mouse - mInitialMousePosition) * cameraSpeed;
        mInitialMousePosition = mouse;
        
        if (Input::GetMouseButtonState(MouseButton::Left)) Rotate(mouseDelta);
        if (Input::GetMouseButtonState(MouseButton::Middle)) Pan(mouseDelta);
        if (Input::GetMouseButtonState(MouseButton::Right)) Zoom(mouseDelta.y);
        
        UpdateView();
    }
    
    inline float GetDistance() const { return mDistance; }
    inline void SetDistance(float distance) { mDistance = distance; }
    
    inline void SetPosition(const glm::vec3 &position) {
        mPosition = position;
        mFocalPoint = mPosition + GetForwardDirection() * mDistance;
        UpdateProjection();
        UpdateView();
    }
    inline void SetViewportSize(float width, float height) {
        mAspectRatio = width / height;
        mViewportWidth = width;
        mViewportHeight = height;
        UpdateProjection();
    }
    const glm::mat4 &GetViewMatrix() const { return mViewMatrix; }
    const glm::mat4 &GetProjectionMatrix() const { return mProjection; }
    glm::mat4 GetViewProjection() const { return mProjection * mViewMatrix; }
    glm::mat4 GetInverseViewProjection() const { return glm::inverse(GetViewProjection()); }
    glm::mat4 GetInverseView() const { return glm::inverse(mViewMatrix); }
    glm::mat4 GetInverseProjection() const { return glm::inverse(mProjection); }
    
    glm::vec3 GetUpDirection() const {
        return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    glm::vec3 GetRightDirection() const {
        return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
    }
    glm::vec3 GetForwardDirection() const {
        return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, 1.0f));
    }
    glm::vec3 GetPosition() const { return mPosition; }
    glm::quat GetOrientation() const {
        return glm::quat(glm::vec3(mPitch, mYaw, 0.0f));
    }
    float GetNearPoint() const { return mNearClip; }
    float GetFarPoint() const { return mFarClip; }

    float GetPitch() const { return mPitch; }
    float GetYaw() const { return mYaw; }

private:
    void UpdateProjection() {
        mAspectRatio = mViewportWidth / mViewportHeight;
        mProjection = glm::Perspective(glm::radians(mFOV), mAspectRatio, mNearClip, mFarClip);
    }
    void UpdateView() {
        // Lock the camera's rotation
        //// mYaw = mPitch = 0.0f;
        mPosition = CalculatePosition();
        ////mViewMatrix = Math::LookAt(mPosition, mFocalPoint, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::quat orientation = GetOrientation();
        mViewMatrix = glm::translate(glm::mat4(1.0f), mPosition) * glm::toMat4(orientation);
        mViewMatrix = glm::inverse(mViewMatrix);
    }

    void Pan(const glm::vec2 &delta) {
        auto [xSpeed, ySpeed] = PanSpeed();
        mFocalPoint += -GetRightDirection() * delta.x * xSpeed * mDistance;
        mFocalPoint += GetUpDirection() * delta.y * ySpeed * mDistance;
    }
    void Rotate(const glm::vec2 &delta) {
        float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
        mYaw += yawSign * delta.x * RotationSpeed();
        mPitch += delta.y * RotationSpeed();
    }
    void Zoom(float delta) {
        mDistance -= delta * ZoomSpeed();
    
        if (mDistance < 1.0f) {
            mFocalPoint += GetForwardDirection();
            mDistance = 1.0f;
        }
    }

    glm::vec3 CalculatePosition() const {
        return mFocalPoint - GetForwardDirection() * mDistance;
    }

    std::pair<float, float> PanSpeed() const {
        float xFactor = std::min(mViewportWidth / 1000.0f, 0.64f);
        float yFactor = std::min(mViewportHeight / 1000.0f, 0.64f);
        return { xFactor, yFactor };
    }
    float RotationSpeed() const {
        return 0.92f;
    }
    float ZoomSpeed() const {
        float speed = std::clamp(0.64f * mDistance, 2.0f, 100.0f);
        return speed;
    }

private:
    float mAspectRatio = 1.334f;
    float mViewportWidth = 800;
    float mViewportHeight = 600;

    float mFOV = 45.0f;
    float mNearClip = 0.1f;
    float mFarClip = 1000.0f;

    glm::mat4 mViewMatrix = {};
    glm::vec3 mPosition = { 0.0f, 0.0f, 0.0f };
    glm::vec3 mFocalPoint = { 0.0f, 0.0f, 0.0f };
    glm::vec2 mInitialMousePosition = { 0.0f, 0.0f };

    float mDistance = 5.0f;
    float mPitch = 0.0f;
    float mYaw = 0.0f;
};

#define EXAMPLES1
#ifdef EXAMPLES
// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class FlyCamera {
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // constructor with vectors
    FlyCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH): Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // constructor with scalar values
    FlyCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch): Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix() {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime) {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch) {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset) {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors() {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }
};
#endif

}

#pragma warning(pop)
