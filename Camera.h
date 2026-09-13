#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<GLFW/glfw3.h>
class Camera
{
public:
	glm::vec3 Pos;
	glm::vec3 Forward;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	float Pitch=0;
	float Yaw=0;
	float sensitivity = 0.001;
	float displacement = 0;
	float displacementR = 0;
	float displacementU = 0;



	Camera(glm::vec3 cameraPos, glm::vec3 cameraTarget, glm::vec3 worldUp);
	Camera(glm::vec3 cameraPos, float pitch, float yaw, glm::vec3 worldUp);
	glm::mat4 getViewMatrix();
	void cameraVectorUpdate(float xoffset,float yoffset);
	void cameraPosUpdata();
};

