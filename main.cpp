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

Camera* myCamera = new Camera(glm::vec3(0, 0, 3), 0, 90, glm::vec3(0, 1, 0));
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

int main() {
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

	//背面剔除
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//Camera* myCamera = new Camera(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	Shader* myshader = new Shader("vertexSource.txt", "fragmentSource.txt");


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


	//设置v轴反转
	stbi_set_flip_vertically_on_load(true);

	//定义纹理，将其绑定到相应的纹理单元并且载入数据
	unsigned int texBuffer1;
	glGenTextures(1, &texBuffer1);

	//绑定
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texBuffer1);

	//设置纹理环绕和过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else std::cout << "failed to load texture" << std::endl;
	stbi_image_free(data);	

	unsigned int texBuffer2;
	glGenTextures(1, &texBuffer2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texBuffer2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else std::cout << "failed to load texture" << std::endl;
	stbi_image_free(data2);

	myshader->use();//将着色器中的变量对应到相应的纹理单元
	glUniform1i(glGetUniformLocation(myshader->ID, "ourTexture1"),0);
	glUniform1i(glGetUniformLocation(myshader->ID, "ourTexture2"),3);
	
	//MVP变换
	glm::mat4 modelMat, viewMat, projMat;
	modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	unsigned int modelMatLoc = glGetUniformLocation(myshader->ID, "modelMat");
	unsigned int viewMatLoc = glGetUniformLocation(myshader->ID, "viewMat");
	unsigned int projMatLoc = glGetUniformLocation(myshader->ID, "projMat");

	/*//预设GLSL shader代码
	const char* vertexShaderSource =
		"	#version 330 core								\n	"
		"   layout(location = 1) in vec3 aColor;		        \n  "
		"	layout(location = 0) in vec3 aPos;				\n	"
		"out vec4 vertexColor;								\n  "
		"void main()										\n	"
		"{gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	\n	"
		"vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);}	\n	";

	const char* fragmentShaderSource =
		"	#version 330 core						\n "
		"uniform vec4 ourColor;						\n"
		"	out vec4 FragColor;						\n "
		"in vec4 vertexColor;						\n"
		"void main()								\n "
		"{FragColor=vertexColor;}						\n";

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);


	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);


	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	
	glEnable(GL_DEPTH_TEST);
	//glm::mat4 trans;
	
	while (!glfwWindowShouldClose(window)) {
		//处理input
		inputProcess(window);
		

		//trans = glm::translate(trans, glm::vec3(0.0001, 0.0002f, 0.f));
		//trans = glm::rotate(trans, glm::radians(0.1f), glm::vec3(0.f, 0.f, 1.0f));
		//trans = glm::scale(trans, glm::vec3(1.0001f,1.0001f, 1.0001f));

		//渲染部分
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texBuffer1);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, texBuffer2);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

		
		/*myCamera->Pos.x =10 *cos(glfwGetTime());
		myCamera->Pos.z = 10*sin(glfwGetTime());
		glm::mat4 viewMat2 = myCamera->getViewMatrix();*/
		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model2;
			model2 = glm::translate(model2, cubePositions[i]);
			model2 = glm::rotate(model2, glm::radians(20.0f *(i+1))*(float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
			myshader->use();

			viewMat = myCamera->getViewMatrix();
			glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(model2));
			glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));

				glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		/*float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, 0.2f, greenValue, 0.4f, 1.0f);*/
		

		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		//响应事件并且swapbuffer
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glfwTerminate();
	return 0;
}