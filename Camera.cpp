#include "Camera.h"
Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraTarget, glm::vec3 worldUp) {
	Pos = cameraPos;
	Forward = glm::normalize(cameraTarget-cameraPos);
	WorldUp =glm::normalize( worldUp);
	Right = glm::normalize(glm::cross(Forward,WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}
glm::mat4 Camera::getViewMatrix() {

	return glm::lookAt(Pos, Forward+Pos, WorldUp);
}
Camera::Camera(glm::vec3 cameraPos, float pitch, float yaw, glm::vec3 worldUp) {
	Pos = cameraPos;
	WorldUp = worldUp;
	pitch = glm::radians(pitch);
	yaw = glm::radians(yaw);
	Pitch = pitch;
	Yaw = yaw;
	Forward.x = cos(Pitch) * cos(Yaw);
	Forward.y = sin(Pitch);
	Forward.z = -cos(Pitch) * sin(Yaw);
	Right = glm::cross(Forward, WorldUp);
	Up = glm::cross(Right, Forward);
}
void Camera::cameraVectorUpdate(float xoffset, float yoffset) {
	Pitch -= yoffset* sensitivity;
	Yaw -= xoffset* sensitivity;
	Forward.x = cos(Pitch) * cos(Yaw);
	Forward.y = sin(Pitch);
	Forward.z = -cos(Pitch) * sin(Yaw);
	Right = glm::cross(Forward, WorldUp);
	Up = glm::cross(Right, Forward);
}
void Camera::cameraPosUpdata() {
	Pos = Pos + displacement * Forward*sensitivity*10.f;
	Pos = Pos + displacementR * Right*sensitivity*10.f;
	Pos = Pos + displacementU * WorldUp *sensitivity * 10.f;
	displacement = 0;
	displacementR = 0;
	displacementU = 0;
}
