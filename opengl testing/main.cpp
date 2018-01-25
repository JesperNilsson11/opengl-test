#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>


static GLuint CompileShader(GLuint type, const std::string& source) {
	GLuint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
		std::cout << "broken shader" << std::endl;

	return id;
}

static GLuint CreateShader(const std::string& vertex, const std::string& fragment) {
	GLuint program = glCreateProgram();
	GLuint vs = CompileShader(GL_VERTEX_SHADER, vertex);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragment);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

std::string getShaderSource(std::string path) {
	std::ifstream shaderFile(path);
	std::string shaderText((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	if (!shaderFile.is_open())
	{
		std::cout << "ERROR: Could not open file: " << "\n";
		system("pause");
		exit(1);
	}

	shaderFile.close();

	return shaderText;
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glewInit();
	std::cout << glGetString(GL_VERSION) << std::endl;

	float positions[] = {
		-1, -1, 0,
		 1, -1, 0,
		 1,  1, 0,
		-1,  1, 0
	};

	GLuint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indices, GL_STATIC_DRAW);

	std::string vertexShader = getShaderSource("vertexshader.glsl");
	std::string fragmentShader = getShaderSource("fragmentshader.glsl");

	GLuint program = CreateShader(vertexShader, fragmentShader);
	glUseProgram(program);

	int u_MVP = glGetUniformLocation(program, "MVP");

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}