/*------------------------------------------------------*/
/* ---------- Proyecto Computacion Grafica -------------*/
/*-----------------    2021-2   ------------------------*/
/*------------- -----  Alumnos -------------------------*/
/*----------Tabura Sanchez Mario Tomihuatzin------------*/
/*------------Alejandro Iván Leyva Diaz-----------------*/
/*--------------Silva Barrera Brandon-------------------*/
/*-------------Espinosa Gonzalez Isaac------------------*/

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

#pragma comment(lib, "winmm.lib")

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void my_input(GLFWwindow *window);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);
void tipoCorriendo(void);
void AVE_VOLANDO(void);
void palmera(void);
// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
GLFWmonitor *monitors;

void getResolution(void);

// camera
Camera camera(glm::vec3(0.0f, 10.0f, 90.0f));
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
glm::vec3 lightDirection(0.0f, -1.0f, 1.0f);

// posiciones
//float x = 0.0f;
//float y = 0.0f;
float	movAuto_x = 0.0f,
movAuto_z = 0.0f,
movAuto_y = 0.0f,
orienta = 180.0f,
luzSolY = 0.0f,
luzSolX = -1.0f,
faroDescomuesto = 0.0f,
giroLlantas = 0.0f;
bool	animacion = false,
recorrido1 = true,
recorrido2 = false,
recorrido3 = false,
recorrido4 = false,
avanza = false,
tramo = false,
cicloFaro = false,
noche = false,
prenderFaros = false,
sube = false;

float rotacionCoche = 90.0f;
//Keyframes (Manipulación y dibujo)
float	posX = 0.0f,
posY = 0.0f,
posZ = 0.0f,
rotRodIzq = 0.0f,
giroMonito = 0.0f,
movBrazoIzq = 0.0f;

float GIROROT_AVE=0.0f;

float	incX = 0.0f,
incY = 0.0f,
incZ = 0.0f,
rotInc = 0.0f,
giroMonitoInc = 0.0f,
movBrazoIzqInc = 0.0f;


//variables Gun
float gun_x,gun_y;
//VARIABLES TIPO
float	posXt = 0.0f,
posYt = 0.0f,
posZt = 0.0f,
rotPiernaIzq = 0.0f,
rotPiernaDer = 0.0f,
rotBrazoIzq = 0.0f,
rotManoIzq = 0.0f,
rotBrazoDer = 0.0f,
rotManoDer = 0.0f,
rotCabeza = 0.0f,
giroCuerpo = -90.0f,
giroTorso = 0.0f;
float	incXt = 0.0f,
incYt = 0.0f,
incZt = 0.0f,
rotPIInc = 0.0f,
rotPDInc = 0.0f,
rotBIInc = 0.0f,
rotMIInc = 0.0f,
rotBDInc = 0.0f,
rotMDInc = 0.0f,
rotCInc = 0.0f,
giroCuerpoInc = 0.0f,
giroTorsoInc = 0.0f;

// VARIABLES AVE
float	AVE_X = 0.0f,
AVE_Y = 0.0f,
AVE_Z = 0.0f,
ROTOALA_DER = 0.0f,
ROT_CUERPO_AVE = 0.0f,
ROT_CUERPO_AVE_X = 0.0f,
ROTALA_IZQ = 0.0f;

float EAGLE_DER_ALA_UP = 0, EAGLE_IZQ_ALA_UP=0;
//AVE INCREMENTO
float	AVE_X_INC = 0.0f,
AVE_Y_INC = 0.0f,
AVE_Z_INC = 0.0f,
ROTOALA_DER_INC = 0.0f,
ROT_CUERPO_AVE_INC = 0.0f,
ROT_CUERPO_AVE_X_INC = 0.0f,
ROTALA_IZQ_INC = 0.0f;
#define CUADROS_MAXIMOS_AVE 9
int interpoladasMaximas_AVE = 60;
int pasoActualAVE = 0;

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

//More palmera animation


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

//More AVE animanation

typedef struct _frame_AVE
{
	//Variables para GUARDAR Key Frames
	float
		AVE_X = 0.0f,
		AVE_Y = 0.0f,
		AVE_Z = 0.0f,
		ROTOALA_DER = 0.0f,
		ROT_CUERPO_AVE = 0.0f,
		ROTALA_IZQ = 0.0f,
		ROT_CUERPO_AVE_X = 0.0f;

}FRAMEX_AVE;

//Variables para interpolacionAVE
FRAMEX_AVE cuadroClaveAVE[CUADROS_MAXIMOS_AVE];
bool AVE_FLY = false;
int playIndiceAVE = 0;
int indiceCuadroAVE = CUADROS_MAXIMOS_AVE;
//Para resetear los cuadros clave de tipo corriendo
void resetearElementosAVE(void)
{
	posX = cuadroClaveAVE[0].AVE_X;
	posY = cuadroClaveAVE[0].AVE_Y;
	posZ = cuadroClaveAVE[0].AVE_Z;

	ROTOALA_DER = cuadroClaveAVE[0].ROTOALA_DER;
	ROT_CUERPO_AVE = cuadroClaveAVE[0].ROTALA_IZQ;
	ROTALA_IZQ = cuadroClaveAVE[0].ROT_CUERPO_AVE;

	ROT_CUERPO_AVE_X= cuadroClaveAVE[0].ROT_CUERPO_AVE_X;
}

void interpolacionAVECorrer(void)
{
	AVE_X_INC = (cuadroClaveAVE[playIndiceAVE + 1].AVE_X - cuadroClaveAVE[playIndiceAVE].AVE_X) / interpoladasMaximas_AVE;
	AVE_Y_INC = (cuadroClaveAVE[playIndiceAVE + 1].AVE_Y - cuadroClaveAVE[playIndiceAVE].AVE_Y) / interpoladasMaximas_AVE;
	AVE_Z_INC = (cuadroClaveAVE[playIndiceAVE + 1].AVE_Z - cuadroClaveAVE[playIndiceAVE].AVE_Z) / interpoladasMaximas_AVE;


	ROTOALA_DER_INC = (cuadroClaveAVE[playIndiceAVE + 1].ROTOALA_DER - cuadroClaveAVE[playIndiceAVE].ROTOALA_DER) / interpoladasMaximas_AVE;
	ROT_CUERPO_AVE_INC = (cuadroClaveAVE[playIndiceAVE + 1].ROT_CUERPO_AVE - cuadroClaveAVE[playIndiceAVE].ROT_CUERPO_AVE) / interpoladasMaximas_AVE;
	ROTALA_IZQ_INC = (cuadroClaveAVE[playIndiceAVE + 1].ROTALA_IZQ - cuadroClaveAVE[playIndiceAVE].ROTALA_IZQ) / interpoladasMaximas_AVE;
	ROT_CUERPO_AVE_X_INC = (cuadroClaveAVE[playIndiceAVE + 1].ROT_CUERPO_AVE_X - cuadroClaveAVE[playIndiceAVE].ROT_CUERPO_AVE_X) / interpoladasMaximas_AVE;
}

void AVE_VOLANDO(void)
{
	
		if (pasoActualAVE >= interpoladasMaximas_AVE) //end of animation between frames?
		{
			playIndiceAVE++;
			if (playIndiceAVE > indiceCuadroAVE)	//end of total animation?
			{
				std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndiceAVE = 0;
				resetearElementosAVE();
				//AVE_FLY = false;
			}
			else //Next frame interpolations
			{
				pasoActualAVE = 0; //Reset counter
								  //Interpolation
				interpolacionAVECorrer();
			}
		}
		else
		{
			//Draw animation
			AVE_X += AVE_X_INC;
			AVE_Y += AVE_Y_INC;
			AVE_Z += AVE_Z_INC;

			ROTOALA_DER += ROTOALA_DER_INC;
			ROT_CUERPO_AVE += ROT_CUERPO_AVE_INC;
			ROTALA_IZQ += ROTALA_IZQ_INC;

			ROT_CUERPO_AVE_X += ROT_CUERPO_AVE_X_INC;
			pasoActualAVE++;
		}
	
}

//ANIMACION TIPO CAMINANDO

//Estructura con variables del cuadro clave de tipo corriendo
#define CUADROS_MAXIMOS 11
int interpoladasMaximas = 60;
int pasoActual = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posXt;		//Variable para PosicionX
	float posYt;		//Variable para PosicionY
	float posZt;		//Variable para PosicionZ
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

//Variables para interpolacion
FRAMEX cuadroClave[CUADROS_MAXIMOS];
int indiceCuadro = 11;			//introducir datos
bool correr = false;
int playIndice = 0;

//Para resetear los cuadros clave de tipo corriendo
void resetearElementos(void)
{
	posXt = cuadroClave[0].posXt;
	posYt = cuadroClave[0].posYt;
	posZt = cuadroClave[0].posZt;

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

//Interpolacion de tipo corriendo
void interpolacionCorrer(void)
{
	incXt = (cuadroClave[playIndice + 1].posXt - cuadroClave[playIndice].posXt) / interpoladasMaximas;
	incYt = (cuadroClave[playIndice + 1].posYt - cuadroClave[playIndice].posYt) / interpoladasMaximas;
	incZt = (cuadroClave[playIndice + 1].posZt - cuadroClave[playIndice].posZt) / interpoladasMaximas;

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

//Animacion tipo corriendo
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
			posXt += incXt;
			posYt += incYt;
			posZt += incZt;

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
}
int paso = 0;
float gun_varX=-0.04f;
float gun_varY = 0.01f;
float tempa = 0.0f;
float temp_upAguila=0.01f;
void animate(void)
{

	//Luces
	if (luzSolY >= -0.1)
		prenderFaros = true;
	if (luzSolY <= -0.1)
		prenderFaros = false;
	if (luzSolX <= 0.0f && noche == false)
	{
		luzSolX += 0.002f;
		luzSolY -= 0.002f;
	}
	else
	{
		if (luzSolY <= 0.0f && noche == false)
		{
			luzSolX += 0.002f;
			luzSolY += 0.002f;
		}
		else {
			noche = true;
			if (luzSolX >= -1.0f && noche == true) {
				luzSolY = 100.0f;
				luzSolX -= 0.002f;
				if (faroDescomuesto >= 0.0f && cicloFaro == true) {
					faroDescomuesto -= 0.03f;
				}
				else {
					cicloFaro = false;
					if (faroDescomuesto <= 1.0f && cicloFaro == false) {
						faroDescomuesto += 0.05f;
					}
					else
						cicloFaro = true;
				}
			}
			else {
				noche = false;
				cicloFaro = false;
				faroDescomuesto = 0.0f;
				luzSolY = 0.0f;
			}
		}

	}
	//COCHE ANIMAICON
	if (animacion)
	{
		//avanza1
		if ((avanza == false) && (sube == false) && (tramo == false))

		{
			movAuto_x += 2.0f;
			giroLlantas += 4.0f;
			orienta = 90.0f;
			if (movAuto_x > 150.0f)
				sube = true;
		}
		//giro
		if ((avanza == false) && (sube == true) && (tramo == false))
		{

			movAuto_x = 150 + (100.0f*sin((orienta*3.1416f / 180.0f) + (90 * 3.1416f / 180.0f)));
			movAuto_z = 100 + (100.0f*cos((orienta*3.1416f / 180.0f) + (90 * 3.1416f / 180.0f)));
			giroLlantas += 3.0f;
			orienta -= 1.0f;
			if (movAuto_z > 125.0f)
			{
				avanza = true;
				sube = true;
				tramo = false;
			}
		}
		//estaciona p1
		if ((avanza == true) && (sube == true) && (tramo == false))
		{
			movAuto_x += 0.5f;
			movAuto_z -= 1.0f;
			giroLlantas += 3.0f;
			//orienta -= 1.0f;
			if (movAuto_z < 100.0f)
			{
				avanza = true;
				sube = false;
				tramo = false;
			}
		}

		//estaciona p2
		if ((sube == false) && (avanza == true) && (tramo == false))
		{
			movAuto_x -= 1.5f;
			movAuto_z += 1.0f;
			giroLlantas += 3.0f;
			//orienta -= 1.0f;
			if (movAuto_z > 125.0f) {
				avanza = true;
				sube = true;
				tramo = true;
			}
		}

		//detener
		if ((avanza == true) && (sube == true) && (tramo == true))
		{
			movAuto_x -= 1.0f;
			giroLlantas += 4.0f;
			orienta = 270.0f;
			if (movAuto_x < 420.0f) {
				animacion = false;
				paso = 5;
			}


		}
	}
	//ANIMACION AVE
	AVE_X = 0 + (100.0f*sin((GIROROT_AVE*3.1416f / 180.0f) + (90 * 3.1416f / 180.0f)));
	AVE_Y = 0 + (30.0f*sin((GIROROT_AVE*3.1416f / 180.0f) + (90 * 3.1416f / 180.0f)));
	AVE_Z = 0 + (100.0f*cos((GIROROT_AVE*3.1416f / 180.0f) + (90 * 3.1416f / 180.0f)));
	GIROROT_AVE -= 0.2f;

	EAGLE_IZQ_ALA_UP += temp_upAguila;
	EAGLE_DER_ALA_UP += temp_upAguila;
	if (EAGLE_IZQ_ALA_UP >= 0.25f || EAGLE_IZQ_ALA_UP >= 0.25f) {
		temp_upAguila = -0.01f;
	}
	if (EAGLE_IZQ_ALA_UP <= -0.15f || EAGLE_IZQ_ALA_UP <= -0.15f) {
		temp_upAguila = 0.01f;
	}
	//AnimaGun
	
	gun_x += gun_varX;
	gun_y += gun_varY/2;
	if (gun_x >0.3f) {
		gun_varX = (-0.018f);
		gun_varY = 0.018f;
	}
	else if (gun_x < -0.3f) {
		gun_varX = 0.013f;
		gun_varY = -0.013f;
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
	Model piso("resources/esc/EscenarioLigero.obj");
	Model carro("resources/objects/lambo/carroceria.obj");
	Model llanta("resources/objects/lambo/Wheel.obj");
	Model casaVieja("resources/objects/casa/OldHouse.obj");

	Model cuerpo("resources/Aguila/Cuerpo.obj");
	Model AlaIzquierda("resources/Aguila/AlaIzquierda.obj");
	Model AlaDerecha("resources/Aguila/Derecha.obj");
	//SET UP FRAMES TIPO COMINANDO
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
	Model gun("resources/shoot/ColtPythonTest.obj");
	//shooting
	ModelAnim CHAR1("resources/shoot/Shooting.dae");
	CHAR1.initShaders(animShader.ID);
	/// Cuadro clave pamera
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
	//cuandro clave tipo
	cuadroClave[0].posXt = 0;
	cuadroClave[0].posYt = 0;
	cuadroClave[0].posZt = 0;
	cuadroClave[0].rotPiernaIzq = 0;
	cuadroClave[0].rotPiernaDer = 0;
	cuadroClave[0].rotBrazoIzq = 0;
	cuadroClave[0].rotManoIzq = 0;
	cuadroClave[0].rotBrazoDer = 0;
	cuadroClave[0].rotManoDer = 0;
	cuadroClave[0].rotCabeza = 0;
	cuadroClave[0].giroCuerpo = -90.0f;
	cuadroClave[0].giroTorso = 0.0f;

	cuadroClave[1].posXt =20.0f;
	cuadroClave[1].posYt = 0.0f;
	cuadroClave[1].posZt = 0.0f;
	cuadroClave[1].rotPiernaIzq = -20.0f;
	cuadroClave[1].rotPiernaDer = 20.0f;
	cuadroClave[1].rotBrazoIzq = 20.0f;
	cuadroClave[1].rotManoIzq = 65.0f;
	cuadroClave[1].rotBrazoDer = -20.0f;
	cuadroClave[1].rotManoDer = 25.0f;
	cuadroClave[1].rotCabeza = 0.0f;
	cuadroClave[1].giroCuerpo = -90.0f;
	cuadroClave[1].giroTorso = 0.0f;

	cuadroClave[2].posXt = 40.0f;
	cuadroClave[2].posYt = 0.0f;
	cuadroClave[2].posZt = 0.0f;
	cuadroClave[2].rotPiernaIzq = 30.0f;
	cuadroClave[2].rotPiernaDer = -30.0f;
	cuadroClave[2].rotBrazoIzq = -30.0f;
	cuadroClave[2].rotManoIzq = 15.0f;
	cuadroClave[2].rotBrazoDer = 30.0f;
	cuadroClave[2].rotManoDer = 75.0f;
	cuadroClave[2].rotCabeza = -30.0f;
	cuadroClave[2].giroCuerpo = -90.0f;
	cuadroClave[2].giroTorso = 0.0f;

	cuadroClave[3].posXt = 60.0f;
	cuadroClave[3].posYt = 0.0f;
	cuadroClave[3].posZt = 0.0f;
	cuadroClave[3].rotPiernaIzq = -120.0f;
	cuadroClave[3].rotPiernaDer = 40.0f;
	cuadroClave[3].rotBrazoIzq = 40.0f;
	cuadroClave[3].rotManoIzq = 85.0f;
	cuadroClave[3].rotBrazoDer = -40.0f;
	cuadroClave[3].rotManoDer = 5.0f;
	cuadroClave[3].rotCabeza = -60.0f;
	cuadroClave[3].giroCuerpo = -90.0f;
	cuadroClave[3].giroTorso = 0.0f;

	cuadroClave[4].posXt = 80.0f;
	cuadroClave[4].posYt = 0.0f;
	cuadroClave[4].posZt = 0.0f;
	cuadroClave[4].rotPiernaIzq = 40.0f;
	cuadroClave[4].rotPiernaDer = -40.0f;
	cuadroClave[4].rotBrazoIzq = -40.0f;
	cuadroClave[4].rotManoIzq = 5.0f;
	cuadroClave[4].rotBrazoDer = 40.0f;
	cuadroClave[4].rotManoDer = 85.0f;
	cuadroClave[4].rotCabeza = -90.0f;
	cuadroClave[4].giroCuerpo = -90.0f;
	cuadroClave[4].giroTorso = 0.0f;

	cuadroClave[5].posXt = 100.0f;
	cuadroClave[5].posYt = 0.0f;
	cuadroClave[5].posZt = 0.0f;
	cuadroClave[5].rotPiernaIzq = -40.0f;
	cuadroClave[5].rotPiernaDer = 40.0f;
	cuadroClave[5].rotBrazoIzq = 40.0f;
	cuadroClave[5].rotManoIzq = 85.0f;
	cuadroClave[5].rotBrazoDer = -40.0f;
	cuadroClave[5].rotManoDer = 5.0f;
	cuadroClave[5].rotCabeza = -45.0f;
	cuadroClave[5].giroCuerpo = -90.0f;
	cuadroClave[5].giroTorso = 0.0f;

	cuadroClave[6].posXt = 110.0f;
	cuadroClave[6].posYt = 0.0f;
	cuadroClave[6].posZt = 0.0f;
	cuadroClave[6].rotPiernaIzq = 30.0f;
	cuadroClave[6].rotPiernaDer = -30.0f;
	cuadroClave[6].rotBrazoIzq = -30.0f;
	cuadroClave[6].rotManoIzq = 15.0f;
	cuadroClave[6].rotBrazoDer = 30.0f;
	cuadroClave[6].rotManoDer = 75;
	cuadroClave[6].rotCabeza = 0.0f;
	cuadroClave[6].giroCuerpo = -90.0f;
	cuadroClave[6].giroTorso = 0.0f;

	cuadroClave[7].posXt = 120.0f;
	cuadroClave[7].posYt = 0.0f;
	cuadroClave[7].posZt = 0.0f;
	cuadroClave[7].rotPiernaIzq = 0.0f;
	cuadroClave[7].rotPiernaDer = 0.0f;
	cuadroClave[7].rotBrazoIzq = 0.0f;
	cuadroClave[7].rotManoIzq = 0.0f;
	cuadroClave[7].rotBrazoDer = 0.0f;
	cuadroClave[7].rotManoDer = 0;
	cuadroClave[7].rotCabeza = 0.0f;
	cuadroClave[7].giroCuerpo = -90.0f;
	cuadroClave[7].giroTorso = 20.0f;

	cuadroClave[8].posXt = 120.0f;
	cuadroClave[8].posYt = 0.0f;
	cuadroClave[8].posZt = 0.0f;
	cuadroClave[8].rotPiernaIzq = 0.0f;
	cuadroClave[8].rotPiernaDer = 0.0f;
	cuadroClave[8].rotBrazoIzq = 0.0f;
	cuadroClave[8].rotManoIzq = 20.0f;
	cuadroClave[8].rotBrazoDer = 0.0f;
	cuadroClave[8].rotManoDer = 20.0f;
	cuadroClave[8].rotCabeza = 0.0f;
	cuadroClave[8].giroCuerpo = -90.0f;
	cuadroClave[8].giroTorso = 0.0f;

	cuadroClave[9].posXt = 120.0f;
	cuadroClave[9].posYt = 0.0f;
	cuadroClave[9].posZt = 0.0f;
	cuadroClave[9].rotPiernaIzq = 0.0f;
	cuadroClave[9].rotPiernaDer = 0.0f;
	cuadroClave[9].rotBrazoIzq = 10.0f;
	cuadroClave[9].rotManoIzq = 0.0f;
	cuadroClave[9].rotBrazoDer = 0.0f;
	cuadroClave[9].rotManoDer = 10.0f;
	cuadroClave[9].rotCabeza = 0.0f;
	cuadroClave[9].giroCuerpo = -90.0f;
	cuadroClave[9].giroTorso = 20.0f;

	cuadroClave[10].posXt = 120.0f;
	cuadroClave[10].posYt = 0.0f;
	cuadroClave[10].posZt = 0.0f;
	cuadroClave[10].rotPiernaIzq = 0.0f;
	cuadroClave[10].rotPiernaDer = 0.0f;
	cuadroClave[10].rotBrazoIzq = 0.0f;
	cuadroClave[10].rotManoIzq = 0.0f;
	cuadroClave[10].rotBrazoDer = 0.0f;
	cuadroClave[10].rotManoDer = 0;
	cuadroClave[10].rotCabeza = 0.0f; 
	cuadroClave[10].giroCuerpo = -90.0f;
	cuadroClave[10].giroTorso = 0.0f;

	glm::mat4 tmp1 = glm::mat4(1.0f);
	glm::mat4 tmp2 = glm::mat4(1.0f);
	glm::mat4 tmp3 = glm::mat4(1.0f);
	glm::mat4 tmp4 = glm::mat4(1.0f);

	/// SET UPP FRAMES AVE
	cuadroClaveAVE[0].ROTOALA_DER = 35.0f;
	cuadroClaveAVE[0].ROTALA_IZQ = 35.0f;
	cuadroClaveAVE[0].ROT_CUERPO_AVE_X = 15.0f;

	cuadroClaveAVE[1].ROTOALA_DER = 20.0f;
	cuadroClaveAVE[1].ROTALA_IZQ = 20.0f;
	cuadroClaveAVE[1].ROT_CUERPO_AVE_X = 5.0f;
	
	cuadroClaveAVE[2].ROTOALA_DER = 5.0f;
	cuadroClaveAVE[2].ROTALA_IZQ = 5.0f;
	cuadroClaveAVE[2].ROT_CUERPO_AVE_X = 0.0f;

	cuadroClaveAVE[3].ROTOALA_DER = 0.0f;
	cuadroClaveAVE[3].ROTALA_IZQ = 0.0f;
	cuadroClaveAVE[3].ROT_CUERPO_AVE_X = -10.0f;

	cuadroClaveAVE[4].ROTOALA_DER = 5.0f;
	cuadroClaveAVE[4].ROTALA_IZQ = 5.0f;
	cuadroClaveAVE[4].ROT_CUERPO_AVE_X = -5.0f;
	
	cuadroClaveAVE[5].ROTOALA_DER = 10.0f;
	cuadroClaveAVE[5].ROTALA_IZQ = 10.0f;
	cuadroClaveAVE[5].ROT_CUERPO_AVE_X = 0.0f;

	cuadroClaveAVE[6].ROTOALA_DER = 20.0f;
	cuadroClaveAVE[6].ROTALA_IZQ =20.0f;
	cuadroClaveAVE[6].ROT_CUERPO_AVE_X = 5.0f;
	
	cuadroClaveAVE[7].ROTOALA_DER = 35.0f;
	cuadroClaveAVE[7].ROTALA_IZQ = 35.0f;
	cuadroClaveAVE[7].ROT_CUERPO_AVE_X = 15.0f;
	

	//Carga del soundtrack
	bool soundtrack = PlaySound("sounds/soundtrack.wav", NULL, SND_ASYNC);



	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		tipoCorriendo();
		AVE_VOLANDO();
		palmera();
		
		skyboxShader.setInt("skybox", 0);

		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		// input
		// -----
		//my_input(window);
		animate();

		// render
		// ------
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		staticShader.use();
		//Setup Advanced Lights
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", glm::vec3(luzSolX, luzSolY, 0.0f));
		staticShader.setVec3("dirLight.ambient", glm::vec3(0.01f, 0.01f, 0.01f)); //color de la luz principal
		if (noche == false)
			staticShader.setVec3("dirLight.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		if (noche == true)
			staticShader.setVec3("dirLight.diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("dirLight.specular", glm::vec3(0.2f, 0.2f, 0.2f));

		staticShader.setVec3("pointLight[0].position", glm::vec3(-84.0f, 24.0f, 79.0f));
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(1.0f, 1.0f, 0.4));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(1.0f, 1.0f, 0.4f));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 1.0f);
		staticShader.setFloat("pointLight[1].linear", 0.014f);
		if (prenderFaros == false || cicloFaro == false)
			staticShader.setFloat("pointLight[0].quadratic", 100.0f); //intensidad
		if (prenderFaros == true && cicloFaro == true)
			staticShader.setFloat("pointLight[0].quadratic", 0.0007f); //intensidad

		staticShader.setVec3("pointLight[1].position", glm::vec3(38.0f, 24.0f, -73.0f));
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(1.0f, 1.0f, 0.4f));
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(1.0f, 1.0f, 0.4f));
		staticShader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[1].constant", 1.0f);
		staticShader.setFloat("pointLight[1].linear", 0.014f);
		if(prenderFaros == true)
			staticShader.setFloat("pointLight[1].quadratic", 0.0007f); //intensidad
		if(prenderFaros == false)
			staticShader.setFloat("pointLight[1].quadratic", 100.0f); //intensidad
		
		staticShader.setVec3("pointLight[2].position", glm::vec3(38.0f, 24.0f, -73.0f));
		staticShader.setVec3("pointLight[2].ambient", glm::vec3(1.0f, 1.0f, 0.4f));
		staticShader.setVec3("pointLight[2].diffuse", glm::vec3(1.0f, 1.0f, 0.4f));
		staticShader.setVec3("pointLight[2].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[2].constant", 1.0f);
		staticShader.setFloat("pointLight[2].linear", 0.014f);
		if(prenderFaros == true)
			staticShader.setFloat("pointLight[2].quadratic", 0.0007f); //intensidad
		if(prenderFaros == false)
			staticShader.setFloat("pointLight[2].quadratic", 100.0f); //intensidad

		staticShader.setFloat("material_shininess", 32.0f);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);
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

		//Shooting
		glm::mat4 tempGun = glm::mat4(1.0f);
		tempGun=model = glm::translate(glm::mat4(1.0f), glm::vec3(-52.0f, -22.0f,-145.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.08f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		animShader.setMat4("model", model);
		CHAR1.Draw(animShader);
		/*
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-40.3f, 1.75f, 0.3f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.2f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		animShader.setMat4("model", model);
		animacionPersonaje.Draw(animShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Segundo Personaje Animacion
		// -------------------------------------------------------------------------------------------------------------------------

		model = glm::translate(glm::mat4(1.0f), glm::vec3(40.3f, 1.75f, 0.3f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.5f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		animShader.setMat4("model", model);
		ninja.Draw(animShader);*/

		// -------------------------------------------------------------------------------------------------------------------------
		// Escenario
		// -------------------------------------------------------------------------------------------------------------------------
		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);
		/*
		model = glm::translate(glm::mat4(1.0f), glm::vec3(250.0f, 0.0f, -10.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		casaDoll.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, 0.0f, -40.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		casaOLD.Draw(staticShader);*/

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -24.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.7f, 1.2f, 2.7f));
		staticShader.setMat4("model", model);
		piso.Draw(staticShader);
		/*
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -70.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		casaVieja.Draw(staticShader);*/
		///
		//Gun tempGun
		model = glm::translate(tempGun, glm::vec3(5.8f + gun_x, 10.0f +gun_y, 1.25f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.17f));
		staticShader.setMat4("model", model);
		gun.Draw(staticShader);
		//PALMERA MODEL 

		glm::mat4 tmp5 = glm::mat4(1.0f);
		glm::mat4 tmp6 = glm::mat4(1.0f);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(16.0f, -22.0f,103.0f));
		model = glm::rotate(model, glm::radians(rotBasePalma), glm::vec3(0.0f, 0.0f, 1.0));
		tmp5 = model = glm::scale(model, glm::vec3(1.0f));
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
		// Carro
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-200.0f + movAuto_x, -24.0f + movAuto_y, -55.0f + movAuto_z));
		tmp = model = glm::rotate(model, glm::radians(orienta), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		staticShader.setMat4("model", model);
		carro.Draw(staticShader);

		model = glm::translate(tmp, glm::vec3(8.5f, 2.5f, 12.9f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, glm::radians(giroLlantas), glm::vec3(1.0f, 0.0f, 0.0f));

		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Izq delantera

		model = glm::translate(tmp, glm::vec3(-8.5f, 2.5f, 12.9f));
		model = glm::rotate(model, glm::radians(giroLlantas), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Der delantera

		model = glm::translate(tmp, glm::vec3(-8.5f, 2.5f, -14.5f));
		model = glm::rotate(model, glm::radians(giroLlantas), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.12f, 0.12f, 0.12f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Der trasera

		model = glm::translate(tmp, glm::vec3(8.5f, 2.5f, -14.5f));
		model = glm::rotate(model, glm::radians(giroLlantas), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.12f, 0.12f, 0.12f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);
		// -------------------------------------------------------------------------------------------------------------------------
		// Personaje
		// -------------------------------------------------------------------------------------------------------------------------
		// -------------------------------------------------------------------------------------------------------------------------
		// Caja Transparente --- Siguiente Práctica
		// -------------------------------------------------------------------------------------------------------------------------
		/*glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -70.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		cubo.Draw(staticShader);
		glEnable(GL_BLEND);*/
		// -------------------------------------------------------------------------------------------------------------------------
		// Termina Escenario
		// -------------------------------------------------------------------------------------------------------------------------
		// Aguila
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f +AVE_X, 70.0f+AVE_Y, 0.0f+AVE_Z));
		//model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f , 70.0f , 0.0f ));
		model = glm::rotate(model, glm::radians(ROT_CUERPO_AVE_X), glm::vec3(0.0f, 0.0f, 1.0));
		tmp = model = glm::rotate(model, glm::radians(GIROROT_AVE), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		cuerpo.Draw(staticShader);
		//Ala derecho 
		model = glm::translate(tmp, glm::vec3(0.45f,-0.1f + EAGLE_DER_ALA_UP, 0.0f));
		model = glm::rotate(model, glm::radians(ROTOALA_DER), glm::vec3(0.0f, 0.0f,1.0f));
		staticShader.setMat4("model", model);
		AlaDerecha.Draw(staticShader);

		//Ala izquierdo 
		model = glm::translate(tmp, glm::vec3(-0.45f, -0.1f + EAGLE_DER_ALA_UP, 0.0f));
		model = glm::rotate(model, glm::radians(ROTALA_IZQ), glm::vec3(0.0f, 0.0f,1.0f));
		staticShader.setMat4("model", model);
		AlaIzquierda.Draw(staticShader);


		/// ------------------
		//DRAWN TIPO 
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-30.0+ posXt, -16.0f+posYt, -145.0f+posZt));
		model = glm::scale(model, glm::vec3(-0.085f,0.085f,0.085f));
		//model = glm::translate(model, glm::vec3(posX, posY, posZ));
		tmp1 = model = glm::rotate(model, glm::radians(giroCuerpo), glm::vec3(0.0f, 1.0f, 0.0));
		tmp4 = model = glm::rotate(model, glm::radians(giroTorso), glm::vec3(1.0f, 0.0f, 0.0));
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
		///------------
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

bool IniciaReco = true;
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

	//Car animation
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		//animacion ^= true;
		//movAuto_z = 0;
		if (IniciaReco) {
			paso = 0;
			animacion = true;
			//movAuto_z = 0.0f;
			//movAuto_x = 0.0f;
			IniciaReco = true;

		}
	}

	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		if (paso == 5) {
			animacion = false;
			recorrido1 = true;
			recorrido2 = false;
			recorrido3 = false;
			recorrido4 = false;
			avanza = false;
			tramo = false;
			sube = false;
			movAuto_z = 0.0f;
			movAuto_x = 0.0f;
			movAuto_y = 0;
			paso = 0;
			orienta = 90.0f;
			animacion = false;
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
	//To play KeyFrame animation 

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
