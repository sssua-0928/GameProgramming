#include "G2W.h"

float G2W_Scale = big_window;
float W2G_Scale = 1.f / big_window;

float big_window = 300.f;
float small_window = 150.f;

void big2smallWindow() {
	G2W_Scale = small_window;
	W2G_Scale = 1.f / small_window;
}

void small2bigWindow() {
	G2W_Scale = big_window;
	W2G_Scale = 1.f / big_window;
}


int G2W_X(float g_x)
{
	return (int)(g_x * G2W_Scale + 500);
}

int G2W_Y(float g_y)
{
	return (int)(-1 * g_y * G2W_Scale + 650);
}

float W2G_X(int w_x)
{
	return (w_x - 500.f) * W2G_Scale;
}

float W2G_Y(int w_y)
{
	return (w_y - 650.f) * -1 * W2G_Scale;
}

