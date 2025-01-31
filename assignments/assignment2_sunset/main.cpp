#include <stdio.h>
#include <math.h>
#include <shaders/shader.h>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

struct Vertex
{
	float x, y, z;
	float u, v;
};

Vertex vertices[4] = {
	//x   //y  //z   u  v
	{ -1, -1, 0.0, 0, 0},
	{ 1, -1, 0.0, 1, 0},
	{ 1,  1, 0.0, 1, 1},
	{ -1, 1, 0.0, 0, 1}
};

unsigned int indices[6] = {
	0, 1, 2,
	2, 3, 0
};

unsigned int createVAO(Vertex* vertexData, int numVertices, unsigned int* indicesData, int numIndices);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

float triangleColor[3] = { 1.0f, 0.5f, 0.0f };
float hillColor[3] = { 0.0, 0.8, 0.0 };
float sunColor[3] = { 1.0, 1.0, 0.0 };
float colorDay[3] = { 1.0, 1.0, 0.0 };
float colorNight[3] = { 0.9, 0.0, 0.5 };
float triangleBrightness = 1.0f;
bool showImGUIDemoWindow = true;

int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Triangle", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}

	//Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	std::string vertexShaderSource = shader::loadShaderSourceFromFile("assets/vertexShader.vert");
	std::string fragmentShaderSource = shader::loadShaderSourceFromFile("assets/fragmentShader.frag");

	shader::Shader shader("assets/vertexShader.vert", "assets/fragmentShader.frag");
	unsigned int vao = createVAO(vertices, 4, indices, 6);

	shader.use();
	glBindVertexArray(vao);


	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		float time = (float)glfwGetTime();
		//Set uniforms
		shader.setFloat("_Brightness", triangleBrightness);
		shader.setVec3("_Color", triangleColor[0], triangleColor[1], triangleColor[2]);
		shader.setFloat("iTime", time);
		shader.setVec2("iResolution", (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
		shader.setVec3("hillColor", hillColor[0], hillColor[1], hillColor[2]);
		shader.setVec3("sunColor", sunColor[0], sunColor[1], sunColor[2]);
		shader.setVec3("colorDay", colorDay[0], colorDay[1], colorDay[2]);
		shader.setVec3("colorNight", colorNight[0], colorNight[1], colorNight[2]);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		//Render UI
		{
			ImGui_ImplGlfw_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Settings");
			ImGui::Checkbox("Show Demo Window", &showImGUIDemoWindow);
			ImGui::ColorEdit3("Hill Color", hillColor);
			ImGui::ColorEdit3("Sun Color", sunColor);
			ImGui::ColorEdit3("Day Color", colorDay);
			ImGui::ColorEdit3("Night Color", colorNight);
			ImGui::DragFloat("Time", &time, 0.0f, 1.0f);
			ImGui::End();
			if (showImGUIDemoWindow) {
				ImGui::ShowDemoWindow(&showImGUIDemoWindow);
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
}

unsigned int createVAO(Vertex* vertexData, int numVertices, unsigned int* indicesData, int numIndices){
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Define a new buffer id
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//Allocate space for + send vertex data to GPU.
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numVertices, vertexData, GL_STATIC_DRAW);

	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0);
	glEnableVertexAttribArray(0);

	//UV
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(offsetof(Vertex, u)));
	glEnableVertexAttribArray(1);

	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, indicesData, GL_STATIC_DRAW);

	return vao;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

