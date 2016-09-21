#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"
#define pi 3.14159265358979
const int width = 1024;
const int height = 600;

float* pixels = new float[width*height * 3];// 픽셀의 배열을 선언해줍니다. 해상도 x 3(rgb)입니다.

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)//픽셀배열에 값(rgb)을 넣는 과정입니다.
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{

	if (i1 - i0 == 0)//직선 함수는 분모가 0이면 즉 x2-x1 차이가 0이면 오류가 나므로 0일때 y축만그리는것으로함.
	{
		for (int i = j0;i < j1;i++)
		{
			drawPixel(i1, i, red, green, blue);
		}
	}
	else if ((j1 - j0) != 0)//기울기가 0이아닌 나머지일경우 
	{
		for (int i = i0; i < i1; i++)
		{
			const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

			drawPixel(i, j, red, green, blue);// i부터 j까지 rgb값으로 그린다
			drawPixel(i, j - 1, red, green, blue);drawPixel(i, j + 1, red, green, blue);//기울어지면 픽셀수가 적어지기때문에 추가해주었습니다.

		}
	}
	else//가로일경우 
	{
		for (int i = i0; i < i1; i++)
		{
			const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

			drawPixel(i, j, red, green, blue);// i부터 j까지 rgb값으로 그린다

		}
	}
}
void thickLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{

	if (i1 - i0 == 0)//세로그리기
	{
		for (int i = j0;i < j1;i++)
		{
			for (int j = 0;j < 10;j++)//기존픽셀에서 x값을 10만큼 증가시켜 찍습니다.(두꺼워지는과정)
			{
				drawPixel(i1 + j, i, red, green, blue);
			}
		}
	}
	else if ((j1 - j0) != 0)
	{
		for (int i = i0; i < i1; i++)
		{
			const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;
			for (int k = 0;k < 10;k++)
			{
				drawPixel(i, j, red, green, blue);// i부터 j까지 rgb값으로 그린다
				drawPixel(i, j - k, red, green, blue);drawPixel(i, j + k, red, green, blue);
			}
		}
	}
	else
	{
		for (int i = i0; i < i1; i++)
		{
			const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

			drawPixel(i, j, red, green, blue);// i부터 j까지 rgb값으로 그린다

		}
	}
}

void drawcircle(const int& x1, const int& y1, const int& r, const float& red, const float& green, const float& blue)
{
	float i = 0.0;
	float rad_to_deg = 0.0;
	float degree = 360.0;
	int x2 = 0, y2 = 0;

	
	for (degree = 0;degree < 360;degree++)
	{
		rad_to_deg = degree*(pi / 180);
		x2 = x1 + r*sin(rad_to_deg);
		y2 = y1 + r*cos(rad_to_deg);
		drawPixel(x2, y2, red, green, blue);
		drawPixel(x2 + 1, y2, red, green, blue);
		drawPixel(x2, y2 - 1, red, green, blue);
	}


}

void drawsqaure()
{
	drawLine(400, 550, 600, 550, 1.0f, 0.0f, 0.0f);
	drawLine(400, 350, 400, 550, 1.0f, 0.0f, 0.0f);
	drawLine(400, 350, 600, 350, 1.0f, 0.0f, 0.0f);
	drawLine(600, 350, 600, 550, 1.0f, 0.0f, 0.0f);
	//안이 빈 사각형 그리기
}
void drawfilledsqaure()
{

}
void drawtriangle()
{
	drawLine(100, 100, 200, 250, 1.0f, 0.0f, 0.0f);
	drawLine(100, 100, 300, 100, 1.0f, 0.0f, 0.0f);
	drawLine(200, 250, 300, 100, 1.0f, 0.0f, 0.0f);
	//삼각형 그리기
}
void pentagon()
{
	drawLine(425, 175, 500, 250, 0.0f, 0.0f, 0.0f);
	drawLine(425, 175, 450, 100, 0.0f, 0.0f, 0.0f);
	drawLine(450, 100, 550, 100, 0.0f, 0.0f, 0.0f);
	drawLine(550, 100, 575, 175, 0.0f, 0.0f, 0.0f);
	drawLine(500, 250, 575, 175, 0.0f, 0.0f, 0.0f);
}
void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}

	//const int i = rand() % width, j = rand() % height;
	//(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing
	//TODO: try moving object
	//drawsqaure();
}
void draw()
{
	const int i_center = 800, j_center = 450;
	const int thickness = 100;
	for (int j = j_center - thickness; j < j_center + thickness; j++)
		for (int i = i_center - thickness;i < i_center + thickness;i++)
		{
			drawPixel(i, j, 1.0f, 0.0f, 0.0f);

		}


		drawsqaure();
		drawfilledsqaure();
		drawtriangle();
		pentagon();

	thickLine(100, 350, 250, 550, 0.0f, 0.0f, 0.0f);

	drawcircle(800, 200, 100, 1.0f, 0.0f, 0.0f);
}
int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		drawOnPixelBuffer();

		//TODO: RGB struct

		//Make a pixel drawing function
		//Make a line drawing function
		draw();
		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}
