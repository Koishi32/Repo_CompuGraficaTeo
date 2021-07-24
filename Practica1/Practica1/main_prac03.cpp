/*---------------------------------------------------------*/
/* ----------------   Práctica 3 --------------------------*/
/*-----------------    2021-2   ---------------------------*/
/*-------Alumno: Leyva Diaz Allejandro Ivan ---------------*/
#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_m.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;

void myData(void);
void getResolution(void);

//For Keyboard

float movX = 0.0f,
movY = -4.0f,
movZ = -10.0f,
rot = 0.0f;


void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{	

	GLfloat verticesCubo[] = {
		//Position				//Color
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V0 - Frontal
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V1
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V5
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V0
		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V4
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V5

		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	//V3
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V7
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V2
		0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V6
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V7

		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V4 - Izq
		-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	//V7
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	//V3
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	//V3
		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V4
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V0

		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V5 - Der
		0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V1
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V2
		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V5
		0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V6
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V2

		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V4 - Sup
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V5
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V6
		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V4
		-0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V7
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V6

		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V0 - Inf
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	//V3
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	//V2
		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V0
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	//V2
		0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V1
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCubo), verticesCubo, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 3 Leyva Diaz Alejandro Ivan", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowPos(window, 0, 30);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	myData();
	glEnable(GL_DEPTH_TEST);

	//Prepare to draw the scene with Projections
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	Shader myShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");

	myShader.use();
	// create transformations and Projection
	glm::mat4 modelOp = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 modelOp2 = glm::mat4(1.0f);
	glm::mat4 viewOp = glm::mat4(1.0f);			//Use this matrix for ALL models
	glm::mat4 projectionOp = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" in order to change how we see the information
	projectionOp = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	//projectionOp = glm::ortho(-5.0f, 5.0f, -3.0f, 3.0f, 0.1f, 10.0f);

    // render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        my_input(window);

        // render
        // Backgound color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi función de dibujo
		/*******************************************/
		//Use "view" in order to affect all models
		viewOp = glm::translate(glm::mat4(1.0f), glm::vec3(movX, movY,movZ));
		viewOp = glm::rotate(viewOp,glm::radians(rot),glm::vec3(0.0f,1.0f,0.0f));
		// pass them to the shaders
		myShader.setMat4("model", modelOp);
		myShader.setMat4("model", modelOp2);
		myShader.setMat4("view", viewOp);
		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		myShader.setMat4("projection", projectionOp);
		

		glBindVertexArray(VAO);

		myShader.setVec3("aColor", glm::vec3(0.8f, 0.4f, 0.0f));
		for (int i = 0; i < 11; i++) {
			modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f + i, 0.0f, 0.0f));
			myShader.setMat4("model", modelOp);
			
			glDrawArrays(GL_TRIANGLES, 0, 36); //A 
		}
		for (int i = 0; i < 5; i++) {
			modelOp2 = glm::translate(glm::mat4(1.0f), glm::vec3(-6.0f + i, 1.0f, 0.0f));
			myShader.setMat4("model", modelOp2);

			glDrawArrays(GL_TRIANGLES, 0, 36); //A 
		}
		myShader.setVec3("aColor", glm::vec3(1.0f,1.0f,1.0f));
		for (int i = 1; i < 4; i++) {
			modelOp = glm::translate(modelOp2, glm::vec3(0.0f + i, 0.0f, 0.0f));
			myShader.setMat4("model", modelOp);
			glDrawArrays(GL_TRIANGLES, 0, 36); //A 
		}

		myShader.setVec3("aColor", glm::vec3(0.8f, 0.4f, 0.0f));

		for (int i = 1; i < 6; i++) {
			modelOp2 = glm::translate(modelOp, glm::vec3(0.0f + i, 0.0f, 0.0f));
			myShader.setMat4("model", modelOp2);
			glDrawArrays(GL_TRIANGLES, 0, 36); //A 
		}

		for (int i = 0; i < 4; i++) {
			modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-6.0f + i,2.0f, 0.0f));
			myShader.setMat4("model", modelOp);
			glDrawArrays(GL_TRIANGLES, 0, 36); //A 
		}

		myShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));

		for (int i = 1; i < 6; i++) {
			modelOp2 = glm::translate(modelOp, glm::vec3(0.0f + i, 0.0f, 0.0f));
			myShader.setMat4("model", modelOp2);
			glDrawArrays(GL_TRIANGLES, 0, 36); //A 
		}
		myShader.setVec3("aColor", glm::vec3(0.8f, 0.4f, 0.0f));
		for (int i = 1; i < 5; i++) {
			modelOp = glm::translate(modelOp2, glm::vec3(0.0f + i, 0.0f, 0.0f));
			myShader.setMat4("model", modelOp);
			glDrawArrays(GL_TRIANGLES, 0, 36); //A 
		}

		for (int i = 0; i < 11; i++) {
			modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f + i, 3.0f, 0.0f));
			myShader.setMat4("model", modelOp);
			glDrawArrays(GL_TRIANGLES, 0, 36); //A 
		}
		for (int i = 0; i < 2; i++) {
			modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f + i, 4.0f, 0.0f));
			myShader.setMat4("model", modelOp);
			glDrawArrays(GL_TRIANGLES, 0, 36); //A 
		}

		myShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));

		for (int i = 1; i < 8; i++) {
			if (i==4) {
				myShader.setVec3("aColor", glm::vec3(0.8f, 0.4f, 0.0f));
				modelOp2 = glm::translate(modelOp, glm::vec3(0.0f + i, 0.0f, 0.0f));
				myShader.setMat4("model", modelOp2);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			else {
				myShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
				modelOp2 = glm::translate(modelOp, glm::vec3(0.0f + i, 0.0f, 0.0f));
				myShader.setMat4("model", modelOp2);
				glDrawArrays(GL_TRIANGLES, 0, 36); //A 
			}
		}
		myShader.setVec3("aColor", glm::vec3(0.8f, 0.4f, 0.0f));
		for (int i = 0; i < 3; i++) {
			modelOp = glm::translate(modelOp2, glm::vec3(0.0f + i, 0.0f, 0.0f));
			myShader.setMat4("model", modelOp);
			glDrawArrays(GL_TRIANGLES, 0, 36); //A 
		}



		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-4.0f, 5.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		glDrawArrays(GL_TRIANGLES, 0, 36); //A 
		

		myShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));

		for (int i = 1; i < 9; i++) {
			if (i == 4 || i==8) {
				myShader.setVec3("aColor", glm::vec3(0.8f, 0.4f, 0.0f));
				modelOp2 = glm::translate(modelOp, glm::vec3(0.0f + i, 0.0f, 0.0f));
				myShader.setMat4("model", modelOp2);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			else if ((i==2) || (i==6) ){
				myShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
				modelOp2 = glm::translate(modelOp, glm::vec3(0.0f + i, 0.0f, 0.0f));
				myShader.setMat4("model", modelOp2);
				glDrawArrays(GL_TRIANGLES, 0, 36); //A 
			}
			else {
				myShader.setVec3("aColor", glm::vec3(1.0f,1.0f,1.0f));
				modelOp2 = glm::translate(modelOp, glm::vec3(0.0f + i, 0.0f, 0.0f));
				myShader.setMat4("model", modelOp2);
				glDrawArrays(GL_TRIANGLES, 0, 36); //A 
			}
		}

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-4.0f, 6.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		glDrawArrays(GL_TRIANGLES, 0, 36); //A 


		myShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));

		for (int i = 1; i < 9; i++) {
			if (i == 4 || i == 8) {
				myShader.setVec3("aColor", glm::vec3(0.8f, 0.4f, 0.0f));
				modelOp2 = glm::translate(modelOp, glm::vec3(0.0f + i, 0.0f, 0.0f));
				myShader.setMat4("model", modelOp2);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			else if ((i == 2) || (i == 6)) {
				myShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
				modelOp2 = glm::translate(modelOp, glm::vec3(0.0f + i, 0.0f, 0.0f));
				myShader.setMat4("model", modelOp2);
				glDrawArrays(GL_TRIANGLES, 0, 36); //A 
			}
			else {
				myShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
				modelOp2 = glm::translate(modelOp, glm::vec3(0.0f + i, 0.0f, 0.0f));
				myShader.setMat4("model", modelOp2);
				glDrawArrays(GL_TRIANGLES, 0, 36); //A 
			}
		}

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-4.0f, 7.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		glDrawArrays(GL_TRIANGLES, 0, 36); //A 


		myShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));

		for (int i = 1; i < 9; i++) {
			if (i == 4 || i == 8) {
				myShader.setVec3("aColor", glm::vec3(0.8f, 0.4f, 0.0f));
				modelOp2 = glm::translate(modelOp, glm::vec3(0.0f + i, 0.0f, 0.0f));
				myShader.setMat4("model", modelOp2);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			else {
				myShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
				modelOp2 = glm::translate(modelOp, glm::vec3(0.0f + i, 0.0f, 0.0f));
				myShader.setMat4("model", modelOp2);
				glDrawArrays(GL_TRIANGLES, 0, 36); //A 
			}
		}

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 8.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		glDrawArrays(GL_TRIANGLES, 0, 36); //A 
		for (int i = 1; i < 7; i++) {
			myShader.setVec3("aColor", glm::vec3(0.8f, 0.4f, 0.0f));
			modelOp2 = glm::translate(modelOp, glm::vec3(0.0f + i, 0.0f, 0.0f));
			myShader.setMat4("model", modelOp2);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 9.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		glDrawArrays(GL_TRIANGLES, 0, 36); //A 
		for (int i = 1; i < 5; i++) {
				myShader.setVec3("aColor", glm::vec3(0.8f, 0.4f, 0.0f));
				modelOp2 = glm::translate(modelOp, glm::vec3(0.0f + i, 0.0f, 0.0f));
				myShader.setMat4("model", modelOp2);
				glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 10.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		glDrawArrays(GL_TRIANGLES, 0, 36); //A 
		for (int i = 1; i < 5; i++) {
			myShader.setVec3("aColor", glm::vec3(0.8f, 0.4f, 0.0f));
			modelOp2 = glm::translate(modelOp, glm::vec3(0.0f + i, 0.0f, 0.0f));
			myShader.setMat4("model", modelOp2);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 11.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		glDrawArrays(GL_TRIANGLES, 0, 36); //A 
		for (int i = 1; i < 3; i++) {
			myShader.setVec3("aColor", glm::vec3(0.8f, 0.4f, 0.0f));
			modelOp2 = glm::translate(modelOp, glm::vec3(0.0f + i, 0.0f, 0.0f));
			myShader.setMat4("model", modelOp2);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 12.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		glDrawArrays(GL_TRIANGLES, 0, 36); //A 
		for (int i = 1; i < 3; i++) {
			myShader.setVec3("aColor", glm::vec3(0.8f, 0.4f, 0.0f));
			modelOp2 = glm::translate(modelOp, glm::vec3(0.0f + i, 0.0f, 0.0f));
			myShader.setMat4("model", modelOp2);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		/*
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //B

		modelOp = glm::translate(modelOp, glm::vec3(0.0f,3.9f, 0.0f));
		//modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 3.9f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 1.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //C
		*/
		glBindVertexArray(0);
		/*****************************************************************/
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		movY += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		movY -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rot -= 0.5f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rot += 0.5f;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}