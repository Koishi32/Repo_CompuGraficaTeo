/*---------------------------------------------------------*/
/* ----------------  ProyectoFinal -----------*/
/*-----------------    2021-2   ---------------------------*/
/*------------- Alumno:                     ---------------*/
#include <Windows.h>

#include <glad/glad.h>
#include <glfw3.h>	//main
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include <time.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	//Texture

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>

//#pragma comment(lib, "winmm.lib")

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void my_input(GLFWwindow *window);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void tipoCorriendo(void);
void palmera(void);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
GLFWmonitor *monitors;

void getResolution(void);

// camera
Camera camera(glm::vec3(0.0f, 10.0f, 20.0f));
float MovementSpeed = 0.1f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, -10.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

// posiciones
//float x = 0.0f;
//float y = 0.0f;
float	movAuto_x = 0.0f,
		movAuto_z = 0.0f,
		orienta = 0.0f;
bool	animacion = false,
		recorrido1 = true,
		recorrido2 = false,
		recorrido3 = false,
		recorrido4 = false;


//Keyframes (Manipulación y dibujo)
float	posX = 0.0f,
		posY = 0.0f,
		posZ = 0.0f,
		rotPiernaIzq = 0.0f,
		rotPiernaDer = 0.0f,
		rotBrazoIzq = 0.0f,
		rotManoIzq = 0.0f,
		rotBrazoDer = 0.0f,
	    rotManoDer = 0.0f,
		rotCabeza = 0.0f,
		giroCuerpo = -90.0f,
		giroTorso = 0.0f;
float	incX = 0.0f,
		incY = 0.0f,
		incZ = 0.0f,
		rotPIInc = 0.0f,
		rotPDInc = 0.0f,
		rotBIInc = 0.0f,
		rotMIInc = 0.0f,
		rotBDInc = 0.0f,
		rotMDInc = 0.0f,
		rotCInc = 0.0f,
		giroCuerpoInc = 0.0f,
		giroTorsoInc = 0.0f;

#define CUADROS_MAXIMOS 11
int interpoladasMaximas = 60;
int pasoActual = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float rotPiernaIzq;
	float rotPiernaDer;
	float rotBrazoIzq;
	float rotManoIzq;
	float rotBrazoDer;
	float rotManoDer;
	float rotCabeza;
	float giroCuerpo;
	float giroTorso;

}FRAMEX;

FRAMEX cuadroClave[CUADROS_MAXIMOS];
int indiceCuadro = 11;			//introducir datos
bool correr = false;
int playIndice = 0;


void resetearElementos(void)
{
	posX = cuadroClave[0].posX;
	posY = cuadroClave[0].posY;
	posZ = cuadroClave[0].posZ;

	rotPiernaIzq = cuadroClave[0].rotPiernaIzq;
	rotPiernaDer = cuadroClave[0].rotPiernaDer;
	rotBrazoIzq = cuadroClave[0].rotBrazoIzq;
	rotManoIzq = cuadroClave[0].rotManoIzq;
	rotBrazoDer = cuadroClave[0].rotBrazoDer;
	rotManoDer = cuadroClave[0].rotManoDer;
	rotCabeza = cuadroClave[0].rotCabeza;
	giroCuerpo = cuadroClave[0].giroCuerpo;
	giroTorso = cuadroClave[0].giroTorso;
}


void interpolacionCorrer(void)
{
	incX = (cuadroClave[playIndice + 1].posX - cuadroClave[playIndice].posX) / interpoladasMaximas;
	incY = (cuadroClave[playIndice + 1].posY - cuadroClave[playIndice].posY) / interpoladasMaximas;
	incZ = (cuadroClave[playIndice + 1].posZ - cuadroClave[playIndice].posZ) / interpoladasMaximas;

	rotPIInc = (cuadroClave[playIndice + 1].rotPiernaIzq - cuadroClave[playIndice].rotPiernaIzq) / interpoladasMaximas;
	rotPDInc = (cuadroClave[playIndice + 1].rotPiernaDer - cuadroClave[playIndice].rotPiernaDer) / interpoladasMaximas;
	rotBIInc = (cuadroClave[playIndice + 1].rotBrazoIzq - cuadroClave[playIndice].rotBrazoIzq) / interpoladasMaximas;
	rotMIInc = (cuadroClave[playIndice + 1].rotManoIzq - cuadroClave[playIndice].rotManoIzq) / interpoladasMaximas;
	rotBDInc = (cuadroClave[playIndice + 1].rotBrazoDer - cuadroClave[playIndice].rotBrazoDer) / interpoladasMaximas;
	rotMDInc = (cuadroClave[playIndice + 1].rotManoDer - cuadroClave[playIndice].rotManoDer) / interpoladasMaximas;
	rotCInc = (cuadroClave[playIndice + 1].rotCabeza - cuadroClave[playIndice].rotCabeza) / interpoladasMaximas;
	giroCuerpoInc = (cuadroClave[playIndice + 1].giroCuerpo - cuadroClave[playIndice].giroCuerpo) / interpoladasMaximas;
	giroTorsoInc = (cuadroClave[playIndice + 1].giroTorso - cuadroClave[playIndice].giroTorso) / interpoladasMaximas;
}

void tipoCorriendo(void)
{
	if (correr)
	{
		if (pasoActual >= interpoladasMaximas) //end of animation between frames?
		{
			playIndice++;
			if (playIndice > indiceCuadro - 2)	//end of total animation?
			{
				std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndice = 0;
				correr = false;
			}
			else //Next frame interpolations
			{
				pasoActual = 0; //Reset counter
								  //Interpolation
				interpolacionCorrer();
			}
		}
		else
		{
			//Draw animation
			posX += incX;
			posY += incY;
			posZ += incZ;

			rotPiernaIzq += rotPIInc;
			rotPiernaDer += rotPDInc;
			rotBrazoIzq += rotBIInc;
			rotManoIzq += rotMIInc;
			rotBrazoDer += rotBDInc;
			rotManoDer += rotMDInc;
			rotCabeza += rotCInc;
			giroCuerpo += giroCuerpoInc;
			giroTorso += giroTorsoInc;

			pasoActual++;
		}
	}

	//Vehículo
	if (animacion)
	{
		movAuto_z += 3.0f;
	}
}

//Variables palmera
float	rotBasePalma = 0.0f,
		rotMitadPalma = 0.0f,
		rotCopaPalma = 0.0f,
		caidaCopa = 0.0f,
		posXCopa = 0.0f,
		posXCopaInc = 0.0f,
		caidaCopaInc = 0.0f,
		rotBPInc = 0.0f,
		rotMPInc = 0.0f,
		rotCPInc = 0.0f;

#define CUADROS_PALMA_MAXIMOS 18
int interpoladasMaximasP = 60;
int pasoActualP = 0;
typedef struct _framep
{
	//Variables para GUARDAR Key Frames

	float rotBasePalma;
	float rotMitadPalma;
	float rotCopaPalma;
	float caidaCopa;
	float posXCopa;
	
}FRAMEP;

FRAMEP cuadroClaveP[CUADROS_PALMA_MAXIMOS];
int indiceCuadroP = 15;			//introducir datos
bool agitarse = false;
int playIndiceP = 0;

void resetearElementosP(void)
{
	rotBasePalma = cuadroClaveP[0].rotBasePalma;
	rotMitadPalma = cuadroClaveP[0].rotMitadPalma;
	rotCopaPalma = cuadroClaveP[0].rotCopaPalma;
	caidaCopa = cuadroClaveP[0].caidaCopa;
	posXCopa = cuadroClaveP[0].posXCopa;
}

void interpolacionAgitarse(void)
{
	rotBPInc = (cuadroClaveP[playIndiceP + 1].rotBasePalma - cuadroClaveP[playIndiceP].rotBasePalma) / interpoladasMaximasP;
	rotMPInc = (cuadroClaveP[playIndiceP + 1].rotMitadPalma - cuadroClaveP[playIndiceP].rotMitadPalma) / interpoladasMaximasP;
	rotCPInc = (cuadroClaveP[playIndiceP + 1].rotCopaPalma - cuadroClaveP[playIndiceP].rotCopaPalma) / interpoladasMaximasP;
	caidaCopaInc = (cuadroClaveP[playIndiceP + 1].caidaCopa - cuadroClaveP[playIndiceP].caidaCopa) / interpoladasMaximasP;
	posXCopaInc = (cuadroClaveP[playIndiceP + 1].posXCopa - cuadroClaveP[playIndiceP].posXCopa) / interpoladasMaximasP;
}

void palmera(void)
{
	if (agitarse)
	{
		if (pasoActualP >= interpoladasMaximasP) //end of animation between frames?
		{
			playIndiceP++;
			if (playIndiceP > indiceCuadroP - 2)	//end of total animation?
			{
				std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndiceP = 0;
				agitarse = false;
			}
			else //Next frame interpolations
			{
				pasoActualP = 0; //Reset counter
								//Interpolation
				interpolacionAgitarse();
			}
		}
		else
		{
			//Draw animation
			rotBasePalma += rotBPInc;
			rotMitadPalma += rotMPInc;
			rotCopaPalma += rotCPInc;
			caidaCopa += caidaCopaInc;
			posXCopa += posXCopaInc;

			pasoActualP++;
		}
	}

}


void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CGeIHC", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");

	vector<std::string> faces
	{
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front.jpg",
		"resources/skybox/back.jpg"
	};

	Skybox skybox = Skybox(faces);

	// Shader configuration
	// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	// load models
	// -----------
	Model piso("resources/objects/Escenario/EscenarioLigero.obj");
	//
	//Model botaDer("resources/objects/Personaje/bota.obj");
	Model piernaDer("resources/objects/tipo/piernaDer.obj");
	Model piernaIzq("resources/objects/tipo/piernaIzq.obj");
	Model torso("resources/objects/tipo/torso.obj");
	Model brazoDer("resources/objects/tipo/brazoDer.obj");
	Model brazoIzq("resources/objects/tipo/brazoIzq.obj");
	Model manoDer("resources/objects/tipo/manoDer.obj");
	Model manoIzq("resources/objects/tipo/manoIzq.obj");
	Model cabeza("resources/objects/tipo/cabeza.obj");

	//Palmeras
	Model basePalma("resources/objects/palmas/basePalma.obj");
	Model mitadPalma("resources/objects/palmas/mitadPalma.obj");
	Model copaPalma("resources/objects/palmas/copaPalma.obj");

	ModelAnim animacionPersonaje("resources/objects/Personaje1/PersonajeBrazo.dae");
	animacionPersonaje.initShaders(animShader.ID);

	//ModelAnim ninja("resources/objects/ZombieWalk/ZombieWalk.dae");
	//ninja.initShaders(animShader.ID);

	//Cuadros clave tipo Corriendo
	cuadroClave[0].posX = 0;
	cuadroClave[0].posY = 0;
	cuadroClave[0].posZ = 0;
	cuadroClave[0].rotPiernaIzq = 0;
	cuadroClave[0].rotPiernaDer = 0;
	cuadroClave[0].rotBrazoIzq = 0;
	cuadroClave[0].rotManoIzq = 0;
	cuadroClave[0].rotBrazoDer = 0;
	cuadroClave[0].rotManoDer = 0;
	cuadroClave[0].rotCabeza = 0;
	cuadroClave[0].giroCuerpo = -90.0f;
	cuadroClave[0].giroTorso = 0.0f;

	cuadroClave[1].posX = -50.0f;
	cuadroClave[1].posY = 0.0f;
	cuadroClave[1].posZ = 0.0f;
	cuadroClave[1].rotPiernaIzq = -20.0f;
	cuadroClave[1].rotPiernaDer = 20.0f;
	cuadroClave[1].rotBrazoIzq = 20.0f;
	cuadroClave[1].rotManoIzq = 65.0f;
	cuadroClave[1].rotBrazoDer = -20.0f;
	cuadroClave[1].rotManoDer = 25.0f;
	cuadroClave[1].rotCabeza = 0.0f;
	cuadroClave[1].giroCuerpo = -90.0f;
	cuadroClave[1].giroTorso = 0.0f;

	cuadroClave[2].posX = -125.0f;
	cuadroClave[2].posY = 0.0f;
	cuadroClave[2].posZ = 0.0f;
	cuadroClave[2].rotPiernaIzq = 30.0f;
	cuadroClave[2].rotPiernaDer = -30.0f;
	cuadroClave[2].rotBrazoIzq = -30.0f;
	cuadroClave[2].rotManoIzq = 15.0f;
	cuadroClave[2].rotBrazoDer = 30.0f;
	cuadroClave[2].rotManoDer = 75.0f;
	cuadroClave[2].rotCabeza = -30.0f;
	cuadroClave[2].giroCuerpo = -90.0f;
	cuadroClave[2].giroTorso = 0.0f;

	cuadroClave[3].posX = -225.0f;
	cuadroClave[3].posY = 0.0f;
	cuadroClave[3].posZ = 0.0f;
	cuadroClave[3].rotPiernaIzq = -40.0f;
	cuadroClave[3].rotPiernaDer = 40.0f;
	cuadroClave[3].rotBrazoIzq = 40.0f;
	cuadroClave[3].rotManoIzq = 85.0f;
	cuadroClave[3].rotBrazoDer = -40.0f;
	cuadroClave[3].rotManoDer = 5.0f;
	cuadroClave[3].rotCabeza = -60.0f;
	cuadroClave[3].giroCuerpo = -90.0f;
	cuadroClave[3].giroTorso = 0.0f;

	cuadroClave[4].posX = -350.0f;
	cuadroClave[4].posY = 0.0f;
	cuadroClave[4].posZ = 0.0f;
	cuadroClave[4].rotPiernaIzq = 40.0f;
	cuadroClave[4].rotPiernaDer = -40.0f;
	cuadroClave[4].rotBrazoIzq = -40.0f;
	cuadroClave[4].rotManoIzq = 5.0f;
	cuadroClave[4].rotBrazoDer = 40.0f;
	cuadroClave[4].rotManoDer = 85.0f;
	cuadroClave[4].rotCabeza = -90.0f;
	cuadroClave[4].giroCuerpo = -90.0f;
	cuadroClave[4].giroTorso = 0.0f;

	cuadroClave[5].posX = -500.0f;
	cuadroClave[5].posY = 0.0f;
	cuadroClave[5].posZ = 0.0f;
	cuadroClave[5].rotPiernaIzq = -40.0f;
	cuadroClave[5].rotPiernaDer = 40.0f;
	cuadroClave[5].rotBrazoIzq = 40.0f;
	cuadroClave[5].rotManoIzq = 85.0f;
	cuadroClave[5].rotBrazoDer = -40.0f;
	cuadroClave[5].rotManoDer = 5.0f;
	cuadroClave[5].rotCabeza = -45.0f;
	cuadroClave[5].giroCuerpo = -90.0f;
	cuadroClave[5].giroTorso = 0.0f;

	cuadroClave[6].posX = -600.0f;
	cuadroClave[6].posY = 0.0f;
	cuadroClave[6].posZ = 0.0f;
	cuadroClave[6].rotPiernaIzq = 30.0f;
	cuadroClave[6].rotPiernaDer = -30.0f;
	cuadroClave[6].rotBrazoIzq = -30.0f;
	cuadroClave[6].rotManoIzq = 15.0f;
	cuadroClave[6].rotBrazoDer = 30.0f;
	cuadroClave[6].rotManoDer = 75;
	cuadroClave[6].rotCabeza = 0.0f;
	cuadroClave[6].giroCuerpo = -90.0f;
	cuadroClave[6].giroTorso = 0.0f;

	cuadroClave[7].posX = -675.0f;
	cuadroClave[7].posY = 0.0f;
	cuadroClave[7].posZ = 0.0f;
	cuadroClave[7].rotPiernaIzq = 0.0f;
	cuadroClave[7].rotPiernaDer = 0.0f;
	cuadroClave[7].rotBrazoIzq = 0.0f;
	cuadroClave[7].rotManoIzq = 0.0f;
	cuadroClave[7].rotBrazoDer = 0.0f;
	cuadroClave[7].rotManoDer = 0;
	cuadroClave[7].rotCabeza = 0.0f;
	cuadroClave[7].giroCuerpo = -90.0f;
	cuadroClave[7].giroTorso = 20.0f;

	cuadroClave[8].posX = -675.0f;
	cuadroClave[8].posY = 0.0f;
	cuadroClave[8].posZ = 0.0f;
	cuadroClave[8].rotPiernaIzq = 0.0f;
	cuadroClave[8].rotPiernaDer = 0.0f;
	cuadroClave[8].rotBrazoIzq = 0.0f;
	cuadroClave[8].rotManoIzq = 20.0f;
	cuadroClave[8].rotBrazoDer = 0.0f;
	cuadroClave[8].rotManoDer = 20.0f;
	cuadroClave[8].rotCabeza = 0.0f;
	cuadroClave[8].giroCuerpo = -90.0f;
	cuadroClave[8].giroTorso = 0.0f;

	cuadroClave[9].posX = -675.0f;
	cuadroClave[9].posY = 0.0f;
	cuadroClave[9].posZ = 0.0f;
	cuadroClave[9].rotPiernaIzq = 0.0f;
	cuadroClave[9].rotPiernaDer = 0.0f;
	cuadroClave[9].rotBrazoIzq = 10.0f;
	cuadroClave[9].rotManoIzq = 0;
	cuadroClave[9].rotBrazoDer = 0.0f;
	cuadroClave[9].rotManoDer = 10.0f;
	cuadroClave[9].rotCabeza = 0.0f;
	cuadroClave[9].giroCuerpo = -90.0f;
	cuadroClave[9].giroTorso = 20.0f;

	cuadroClave[10].posX = -675.0f;
	cuadroClave[10].posY = 0.0f;
	cuadroClave[10].posZ = 0.0f;
	cuadroClave[10].rotPiernaIzq = 0.0f;
	cuadroClave[10].rotPiernaDer = 0.0f;
	cuadroClave[10].rotBrazoIzq = 0.0f;
	cuadroClave[10].rotManoIzq = 0;
	cuadroClave[10].rotBrazoDer = 0.0f;
	cuadroClave[10].rotManoDer = 0;
	cuadroClave[10].rotCabeza = 0.0f;
	cuadroClave[10].giroCuerpo = -90.0f;
	cuadroClave[10].giroTorso = 0.0f;

	//Cuadros clave palmera
	cuadroClaveP[0].rotBasePalma = 0.0f;
	cuadroClaveP[0].rotMitadPalma = 0.0f;
	cuadroClaveP[0].rotCopaPalma = 0.0f;
	cuadroClaveP[0].caidaCopa = 0.0f;
	cuadroClaveP[0].posXCopa = 0.0f;


	cuadroClaveP[1].rotBasePalma = 0.5f;
	cuadroClaveP[1].rotMitadPalma = 1.0f;
	cuadroClaveP[1].rotCopaPalma = 1.5f;
	cuadroClaveP[1].caidaCopa = 0.0f;
	cuadroClaveP[1].posXCopa = 0.0f;

	cuadroClaveP[2].rotBasePalma = -0.5f;
	cuadroClaveP[2].rotMitadPalma = -1.5f;
	cuadroClaveP[2].rotCopaPalma = -2.5f;
	cuadroClaveP[2].caidaCopa = 0.0f;
	cuadroClaveP[2].posXCopa = 0.0f;

	cuadroClaveP[3].rotBasePalma = 1.0f;
	cuadroClaveP[3].rotMitadPalma = 2.5f;
	cuadroClaveP[3].rotCopaPalma = 4.0f;
	cuadroClaveP[3].caidaCopa = 0.0f;
	cuadroClaveP[3].posXCopa = 0.0f;

	cuadroClaveP[4].rotBasePalma = -1.0f;
	cuadroClaveP[4].rotMitadPalma = -3.0f;
	cuadroClaveP[4].rotCopaPalma = -5.0f;
	cuadroClaveP[4].caidaCopa = 0.0f;
	cuadroClaveP[4].posXCopa = 0.0f;

	cuadroClaveP[5].rotBasePalma = 1.5f;
	cuadroClaveP[5].rotMitadPalma = 4.0f;
	cuadroClaveP[5].rotCopaPalma = 6.5f;
	cuadroClaveP[5].caidaCopa = 0.0f;
	cuadroClaveP[5].posXCopa = 0.0f;

	cuadroClaveP[6].rotBasePalma = -1.5f;
	cuadroClaveP[6].rotMitadPalma = -4.5f;
	cuadroClaveP[6].rotCopaPalma = -7.5f;
	cuadroClaveP[6].caidaCopa = 0.0f;
	cuadroClaveP[6].posXCopa = 0.0f;

	cuadroClaveP[7].rotBasePalma = 2.0f;
	cuadroClaveP[7].rotMitadPalma = 5.5f;
	cuadroClaveP[7].rotCopaPalma = 9.0f;
	cuadroClaveP[7].caidaCopa = 0.0f;
	cuadroClaveP[7].posXCopa = 0.0f;

	cuadroClaveP[8].rotBasePalma = -2.0f;
	cuadroClaveP[8].rotMitadPalma = -6.0f;
	cuadroClaveP[8].rotCopaPalma = -10.0f;
	cuadroClaveP[8].caidaCopa = 0.0f;
	cuadroClaveP[8].posXCopa = 0.0f;

	cuadroClaveP[9].rotBasePalma = 2.5f;
	cuadroClaveP[9].rotMitadPalma = 7.0f;
	cuadroClaveP[9].rotCopaPalma = 11.5f;
	cuadroClaveP[9].caidaCopa = 0.0f;
	cuadroClaveP[9].posXCopa = 0.0f;

	cuadroClaveP[10].rotBasePalma = -2.5f;
	cuadroClaveP[10].rotMitadPalma = -7.5f;
	cuadroClaveP[10].rotCopaPalma = -12.5f;
	cuadroClaveP[10].caidaCopa = 0.0f;
	cuadroClaveP[10].posXCopa = 0.0f;

	cuadroClaveP[11].rotBasePalma = 3.0f;
	cuadroClaveP[11].rotMitadPalma = 8.5f;
	cuadroClaveP[11].rotCopaPalma = 14.0f;
	cuadroClaveP[11].caidaCopa = 0.0f;
	cuadroClaveP[11].posXCopa = 0.0f;

	cuadroClaveP[12].rotBasePalma = -3.0f;
	cuadroClaveP[12].rotMitadPalma = -9.0f;
	cuadroClaveP[12].rotCopaPalma = 12.0f;
	cuadroClaveP[12].caidaCopa = -27.0f;
	cuadroClaveP[12].posXCopa = -6.8f;

	cuadroClaveP[13].rotBasePalma = 0.0f;
	cuadroClaveP[13].rotMitadPalma = 0.0f;
	cuadroClaveP[13].rotCopaPalma = 0.0f;
	cuadroClaveP[13].caidaCopa = -27.0f;
	cuadroClaveP[13].posXCopa = -9.0f;

	cuadroClaveP[14].rotBasePalma = 0.0f;
	cuadroClaveP[14].rotMitadPalma = 0.0f;
	cuadroClaveP[14].rotCopaPalma = 90.0f;
	cuadroClaveP[14].caidaCopa = -27.0f;
	cuadroClaveP[14].posXCopa = -9.0f;

	
	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		skyboxShader.setInt("skybox", 0);
		
		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		// input
		// -----
		//my_input(window);
		tipoCorriendo();
		palmera();
		// render
		// ------
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		staticShader.use();
		//Setup Advanced Lights
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		staticShader.setVec3("dirLight.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		staticShader.setVec3("dirLight.diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("dirLight.specular", glm::vec3(0.0f, 0.0f, 0.0f));

		staticShader.setVec3("pointLight[0].position", lightPosition);
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 0.08f);
		staticShader.setFloat("pointLight[0].linear", 0.009f);
		staticShader.setFloat("pointLight[0].quadratic", 0.032f);

		staticShader.setVec3("pointLight[1].position", glm::vec3(-80.0, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[1].constant", 1.0f);
		staticShader.setFloat("pointLight[1].linear", 0.009f);
		staticShader.setFloat("pointLight[1].quadratic", 0.032f);

		staticShader.setFloat("material_shininess", 32.0f);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp1 = glm::mat4(1.0f);
		glm::mat4 tmp2 = glm::mat4(1.0f);
		glm::mat4 tmp3 = glm::mat4(1.0f);
		glm::mat4 tmp4 = glm::mat4(1.0f);
		glm::mat4 tmp5 = glm::mat4(1.0f);
		glm::mat4 tmp6 = glm::mat4(1.0f);
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		//// Light
		glm::vec3 lightColor = glm::vec3(0.6f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.75f);
		

		// -------------------------------------------------------------------------------------------------------------------------
		// Personaje Animacion
		// -------------------------------------------------------------------------------------------------------------------------
		//Remember to activate the shader with the animation
		animShader.use();
		animShader.setMat4("projection", projection);
		animShader.setMat4("view", view);
	
		animShader.setVec3("material.specular", glm::vec3(0.5f));
		animShader.setFloat("material.shininess", 32.0f);
		animShader.setVec3("light.ambient", ambientColor);
		animShader.setVec3("light.diffuse", diffuseColor);
		animShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		animShader.setVec3("light.direction", lightDirection);
		animShader.setVec3("viewPos", camera.Position);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-40.3f, 1.75f, 0.3f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.2f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		animShader.setMat4("model", model);
		//animacionPersonaje.Draw(animShader);


		// -------------------------------------------------------------------------------------------------------------------------
		// Escenario
		// -------------------------------------------------------------------------------------------------------------------------
		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);


		//piso
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		piso.Draw(staticShader);
		
		// -------------------------------------------------------------------------------------------------------------------------
		// Personaje
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(8.0, -0.45f, -11.0f));
		model = glm::scale(model, glm::vec3(0.016f));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		tmp1 = model = glm::rotate(model, glm::radians(giroCuerpo), glm::vec3(0.0f, 1.0f, 0.0));
		tmp4 =  model = glm::rotate(model, glm::radians(giroTorso), glm::vec3(1.0f, 0.0f, 0.0));
		staticShader.setMat4("model", model);
		torso.Draw(staticShader);

		//Pierna Der
		model = glm::translate(tmp1, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-rotPiernaDer), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		piernaDer.Draw(staticShader);
		
		//Pierna Izq
		model = glm::translate(tmp1, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotPiernaIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		piernaIzq.Draw(staticShader);

		//Brazo derecho
		model = glm::translate(tmp4, glm::vec3(-22.0f, 50.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		tmp2 = model = glm::rotate(model, glm::radians(-rotBrazoDer), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		brazoDer.Draw(staticShader);

		//Mano derecha
		model = glm::translate(tmp2, glm::vec3(-9.0f, -15.0f, 2.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotManoDer), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		manoDer.Draw(staticShader);

		//Brazo izquierdo
		model = glm::translate(tmp4, glm::vec3(23.0f, 50.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		tmp3 = model = glm::rotate(model, glm::radians(-rotBrazoIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		brazoIzq.Draw(staticShader);

		//Mano izquierda
		model = glm::translate(tmp3, glm::vec3(5.0f, -18.0f, 2.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotManoIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		manoIzq.Draw(staticShader);

		//Cabeza
		model = glm::translate(tmp4, glm::vec3(0.0f, 62.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-rotCabeza), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 2.5f, 0));
		staticShader.setMat4("model", model);
		cabeza.Draw(staticShader);

		// palmera
		//Base
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, -1.75f, -22.0f));
		model = glm::rotate(model, glm::radians(rotBasePalma), glm::vec3(0.0f, 0.0f, 1.0));
		tmp5 = model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		basePalma.Draw(staticShader);
		//Mitad
		model = glm::translate(tmp5, glm::vec3(0.2f, 16.5f, 0.0f));
		tmp6 = model = glm::rotate(model, glm::radians(rotMitadPalma), glm::vec3(0.0f, 0.0f, 1.0));		
		staticShader.setMat4("model", model);
		mitadPalma.Draw(staticShader);
		//Copa
		model = glm::translate(tmp6, glm::vec3(3.5f, 11.5, 0.0f));
		model = glm::translate(model, glm::vec3(posXCopa, caidaCopa, 0.0f));
		model = glm::rotate(model, glm::radians(rotCopaPalma), glm::vec3(0.0f, 0.0f, 1.0));
		staticShader.setMat4("model", model);
		copaPalma.Draw(staticShader);
		
		// -------------------------------------------------------------------------------------------------------------------------
		// Termina Escenario
		// -------------------------------------------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------
		// draw skybox as last
		// -------------------
		skyboxShader.use();
		skybox.Draw(skyboxShader, view, projection, camera);

		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		//std::cout <<"frame time = " << frameTime << " milli sec"<< std::endl;
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	skybox.Terminate();

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	//To Configure Model
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		posZ++;
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		posZ--;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		posX--;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		posX++;
	/*
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		rotRodIzq--;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		rotRodIzq++;
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		giroMonito--;
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		giroMonito++;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		lightPosition.x++;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		lightPosition.x--;
	*/
	//Car animation
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		animacion ^= true;

	//To play KeyFrame animation 
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		if (correr == false && (indiceCuadro > 1))
		{
			std::cout << "Play animation" << std::endl;
			resetearElementos();
			//First Interpolation				
			interpolacionCorrer();

			correr = true;
			playIndice = 0;
			pasoActual = 0;
		}
		else
		{
			correr = false;
			std::cout << "Not enough Key Frames" << std::endl;
		}
	}

	if (key == GLFW_KEY_O && action == GLFW_PRESS)
	{
		if (agitarse == false && (indiceCuadroP > 1))
		{
			std::cout << "Play animation" << std::endl;
			resetearElementosP();
			//First Interpolation				
			interpolacionAgitarse();

			agitarse = true;
			playIndiceP = 0;
			pasoActualP = 0;
		}
		else
		{
			agitarse = false;
			std::cout << "Not enough Key Frames" << std::endl;
		}
	}

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}