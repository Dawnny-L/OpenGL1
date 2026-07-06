#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Camera.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include <stb/stb_image.h>
#include"Texture.h"

const unsigned int width = 800;
const unsigned int height = 800;

int main()
{
	//Initialize GLFW
	glfwInit();
	//Tell GLFW what version of OpenGL we are using
	//Version 3.4 thus there being a 4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Tell GLFW we are using the core profile(only have modern functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//triangle point coordinates
	GLfloat vertices[] =
	{
		// Vertices coordinates

			//  COORDINATES            //COLORS                // TexCoord     //NORMALS           //
			-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,  0.0f, 0.0f,   0.0f, -1.0f, 0.0f,  // Bottom side
			 -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,  0.0f, 5.0f,   0.0f, -1.0f, 0.0f,  // Bottom side
			 0.5f, 0.0f,  -0.5f,     0.83f, 0.70f, 0.44f,  5.0f, 5.0f,   0.0f, -1.0f, 0.0f,  // Bottom side
			 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,  5.0f, 0.0f,   0.0f, -1.0f, 0.0f,  // Bottom side
			
			-0.5f, 0.0f, 0.5f,     0.83f, 0.70f, 0.44f,  0.0f, 0.0f,  -0.8f,  0.5f, 0.0f,  // Left side
			-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,  5.0f, 0.0f,  -0.8f,  0.5f, 0.0f,  // Left side
			0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,  2.5f, 5.0f,  -0.8f,  0.5f, 0.0f,  // Left side
		
			 -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,  5.0f, 0.0f,   0.0f,  0.5f, -0.8f, // Non-facing side
			 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,  0.0f, 0.0f,   0.0f,  0.5f, -0.8f, // Non-facing side
			 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,  2.5f, 5.0f,   0.0f,  0.5f, -0.8f, // Non-facing side
			

			 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,  0.0f, 0.0f,   0.8f,  0.5f, 0.0f,  // Right side
			 0.5f, 0.0f, 0.5f,     0.83f, 0.70f, 0.44f,  5.0f, 0.0f,   0.8f,  0.5f, 0.0f,  // Right side
			 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,  2.5f, 5.0f,   0.8f,  0.5f, 0.0f,  // Right side

			 0.5f, 0.0f, 0.5f,     0.83f, 0.70f, 0.44f,  5.0f, 0.0f,   0.0f,  0.5f, 0.8f,  // Facing side
			-0.5f, 0.0f, 0.5f,     0.83f, 0.70f, 0.44f,  0.0f, 0.0f,   0.0f,  0.5f, 0.8f,  // Facing side
			 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,  2.5f, 5.0f,   0.0f,  0.5f, 0.8f   // Facing side
		


	};

	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		4, 6, 5,
		7, 9, 8,
		10, 12, 11,
		13, 15, 14
	};

	GLfloat lightVertices[] =
	{
	
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	-0.1f,  0.1f, -0.1f,
	-0.1f, -0.1f,  0.1f,
	 0.1f, -0.1f,  0.1f,
	 0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,


	}; 

	GLuint lightIndices[] =
	{
	
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3, 
	3, 7, 6,
	3, 6, 2,
	2, 6, 5, 
	2, 5, 1,
	1, 5, 4, 
	1, 4, 0, 
	4, 5, 6, 
	4, 6, 7

	};

	//Creating a GLFWwindow object of 800 by 800 pixels, with the name "OPENGL 1"
	GLFWwindow* window = glfwCreateWindow(width, height, "OPENGL 1", NULL, NULL);
	//Error check if the window fails to create
	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
			glfwTerminate();
			return -1;
	}
	//Introduce the window into the current context
	glfwMakeContextCurrent(window);
	
	//Load glad so that it configures OpenGL
	gladLoadGL();

	//The viewport of the GLFWwindow
	//From x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();
	
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));


	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	Shader lightShader("light.vert", "light.frag");

	VAO lightVAO;
	lightVAO.Bind();

	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);



	//Texture
	Texture pic("wall_texture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	pic.texUnit(shaderProgram, "tex0", 0);
	
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	//Main while loop
	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Tell OpenGL which Shader Program we want to use
		

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);
		camera.Matrix(shaderProgram, "camMatrix");

		shaderProgram.Activate();
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");


		pic.Bind();
		//Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		lightShader.Activate();
		camera.Matrix(lightShader, "CamMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		//Take care of all GLFW events
		glfwPollEvents();
	}

	//Deleting the objects
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	pic.Delete();
	shaderProgram.Delete();
	//Delete window before ending the program
	glfwDestroyWindow(window);
	//Terminate GLFW 
	glfwTerminate();
	return 0;
}