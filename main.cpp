#define GLEW_STATIC	
#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"Camera.h"
#pragma region definition
unsigned int load_Texture(const char* path,GLenum format,int Channel) {
	//定义纹理，将其绑定到相应的纹理单元并且载入数据
	unsigned int texBuffer;
	glGenTextures(1, &texBuffer);

	//绑定
	glActiveTexture(GL_TEXTURE0+Channel);
	glBindTexture(GL_TEXTURE_2D, texBuffer);


	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		//设置纹理环绕和过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else std::cout << "failed to load texture" << std::endl;
	stbi_image_free(data);
	return texBuffer;
}
#pragma endregion

#pragma region Init_Camera
Camera* myCamera = new Camera(glm::vec3(0, 0, 3), 0, 90, glm::vec3(0, 1, 0));
#pragma endregion

#pragma region VertexData
float vertices[] = {
	////     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
	// 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
	// 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
	//-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
	//-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
glm::vec3 cubePositions[] = {
glm::vec3(0.0f,  0.0f,  -1.0f),
glm::vec3(2.0f,  5.0f, -15.0f),
glm::vec3(-1.5f, -2.2f, -2.5f),
glm::vec3(-3.8f, -2.0f, -12.3f),
glm::vec3(2.4f, -0.4f, -3.5f),
glm::vec3(-1.7f,  3.0f, -7.5f),
glm::vec3(1.3f, -2.0f, -2.5f),
glm::vec3(1.5f,  2.0f, -2.5f),
glm::vec3(1.5f,  0.2f, -1.5f),
glm::vec3(-1.3f,  1.0f, -1.5f)
};
unsigned int indices[] = { 0,1,2,0,2,3 };
#pragma endregion

#pragma region Input_Process
float lastx, lasty;
bool firstmouse = true;
bool altpress;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (altpress)
		return;
	if (firstmouse) {
		lastx = xpos;
		lasty = ypos;
		firstmouse = false;
	}
	float xoffset = xpos - lastx;
	float yoffset = ypos - lasty;
	//std::cout << ypos << std::endl;
	myCamera->cameraVectorUpdate(xoffset, yoffset);
	lastx = xpos;
	lasty = ypos;
};
void inputProcess(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstmouse = true;
		altpress = true;
	}
	else {
		altpress = false;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	glfwSetCursorPosCallback(window, mouse_callback);
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		myCamera->displacement = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		myCamera->displacement = -1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		myCamera->displacementR = -1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		myCamera->displacementR = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		myCamera->displacementU = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		myCamera->displacementU = -1.0f;
	}
	myCamera->cameraPosUpdata();
}
#pragma endregion

int main() {

#pragma region Init_Window
	glfwInit();
	//版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);


	//create a window
	GLFWwindow* window = glfwCreateWindow(1600, 900, "my window", nullptr, nullptr);
	if (!window) {
		std::cout << "fail to create" << std::endl;
		glfwTerminate();
		return -1;
	}


	glfwMakeContextCurrent(window);

	//init a window
	glewExperimental = true;
	if (glewInit()!= GLEW_OK) {
		glfwTerminate();
		std::cout << "fail to init" << std::endl;
		return -1;
	}
	
	glViewport(0, 0, 1600, 900);//规定渲染区域

	
#pragma endregion

#pragma region Global_Settings
	//设置v轴反转
	stbi_set_flip_vertically_on_load(true);

	//背面剔除
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);



	//深度测试
	glEnable(GL_DEPTH_TEST);
#pragma endregion

#pragma region Init_Shader
	Shader* myshader = new Shader("vertexSource.vert", "fragmentSource.frag");
#pragma endregion

#pragma region Init_Bind_Stuff_VAO_VBO_EBO
	unsigned int VAO;
	glGenVertexArrays(1,&VAO);//将VAO和VERTEX_ARRAY绑定
	glBindVertexArray(VAO);//将此VAO设置为context_VAO

	unsigned int VBO;
	glGenBuffers(1, &VBO);//将VBO和ARRAY_BUFFER绑定
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//将此VBO设置为context_VAO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//存放数据

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
#pragma endregion

#pragma region Init_Texture
	unsigned int texBuffer1, texBuffer2;
	texBuffer1 = load_Texture("container.jpg",GL_RGB, 0);
	texBuffer2 = load_Texture("awesomeface.png", GL_RGBA, 3);
	myshader->use();//将着色器中的变量对应到相应的纹理单元
	glUniform1i(glGetUniformLocation(myshader->ID, "ourTexture1"),0);
	glUniform1i(glGetUniformLocation(myshader->ID, "ourTexture2"),3);

#pragma endregion

#pragma region Init_Transform
	//MVP变换
	glm::mat4 modelMat, viewMat, projMat;
	modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	unsigned int modelMatLoc = glGetUniformLocation(myshader->ID, "modelMat");
	unsigned int viewMatLoc = glGetUniformLocation(myshader->ID, "viewMat");
	unsigned int projMatLoc = glGetUniformLocation(myshader->ID, "projMat");
#pragma endregion
	
#pragma region Atrribute_Pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
#pragma endregion
	

	//glm::mat4 trans;
#pragma region render_Loop
	while (!glfwWindowShouldClose(window)) {
		//处理input
		inputProcess(window);
		

		//trans = glm::translate(trans, glm::vec3(0.0001, 0.0002f, 0.f));
		//trans = glm::rotate(trans, glm::radians(0.1f), glm::vec3(0.f, 0.f, 1.0f));
		//trans = glm::scale(trans, glm::vec3(1.0001f,1.0001f, 1.0001f));

		//渲染部分

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		myshader->use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texBuffer1);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, texBuffer2);

		glBindVertexArray(VAO);

		viewMat = myCamera->getViewMatrix();
		/*myCamera->Pos.x =10 *cos(glfwGetTime());
		myCamera->Pos.z = 10*sin(glfwGetTime());
		glm::mat4 viewMat2 = myCamera->getViewMatrix();*/
		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model2;
			model2 = glm::translate(model2, cubePositions[i]);
			model2 = glm::rotate(model2, glm::radians(20.0f *(i+1))*(float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
			
			glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(model2));
			glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));

				glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//swapbuffer并且检测鼠标
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glfwTerminate();
	return 0;
#pragma endregion
}