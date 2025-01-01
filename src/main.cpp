#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include <array>

#include "Shader.h"
#include "ErrorHandling.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


uint32_t width = 800;
uint32_t height = 600;


int main()
{
	//1.Init opengl
	//2.Compile Shader
	//3.VBO VAO 
	//4.while loop



	if (!glfwInit())
	{
		std::cout << "Blad inicjalizacji glfw\n";
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(width, height, "Moje okno", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Blad okna\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Blad inicjalizacji glad\n";
		return -1;
	}
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, nullptr);

	std::cout << "OpenGL Info: \n";
	std::cout << "	Vendor: "   << glGetString(GL_VENDOR)   << std::endl;
	std::cout << "	Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "	Version: "  << glGetString(GL_VERSION)  << std::endl;
	
	std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;

	Shader shader("res/Shaders/Basic.shader");
	shader.Bind();
	shader.UnBind();
	
	std::array<GLfloat, 18> vertices{
		-0.5, -0.5, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5, -0.5, 0.0,  0.0f, 1.0f, 0.0f,
		 0.0,  0.5, 0.0,  0.0f, 0.0f, 1.0f
	};

	std::array<GLint, 3> indices{
		0, 1, 2
	};

	GLuint VBO, VAO, IndexBuffer;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);




	while (!glfwWindowShouldClose(window))
	{
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		shader.Bind();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	shader.UnBind();

	glfwTerminate();
}
