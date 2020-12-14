#pragma once
#include "list_vertices.hpp"
#include "button.hpp"

ListVertices listv;							// List vertices
int xCursor = xCURSOR;						// For printText()
int yCursor = yCURSOR;						// For printText()
int delayRunTime = 500;						// 500ms delay default
bool isSaved = 1;							// Check if Graph is saved or not
int trace[MAX_VERTEX]; 						// visited & save path...
float adjaGraph[MAX_VERTEX][MAX_VERTEX];	// Adjacency Matrix
HWND hwnd;									// Manage win32 api functions

// List button for select menu item 
Button menuButton[] =	{ {999, 999, 999, 999, BUTTON_COLOR, " "},
						  {999, 999, 999, 999, BUTTON_COLOR, " "},
						  {45, 155, 145, 195, BUTTON_COLOR,	"DIJK - FORD"}, 
						  {999, 999, 999 ,999, BUTTON_COLOR, " "},
						  {999, 999, 999 ,999, BUTTON_COLOR, " "},
						  {999, 999, 999 ,999, BUTTON_COLOR, " "}, 
						  {45, 220, 145, 260, BUTTON_COLOR, "HAMILTON"},
						  {195, 220, 295, 260, BUTTON_COLOR,"EULER"}, 
						  {999, 999, 999 ,999, BUTTON_COLOR, " "},
						  {999, 999, 999 ,999, BUTTON_COLOR, " "},
						  {195, 155, 295, 195, BUTTON_COLOR,"LIEN THONG"},
						  {15, 45, 115, 85, BUTTON_COLOR,	"Mo File"},
						  {120, 45, 220, 85, BUTTON_COLOR,"Luu File"},
						  {225, 45, 325, 85, BUTTON_COLOR,"Thoat"},
						  {357, 22, 417, 92, BUTTON_COLOR,	"Them Dinh"},
						  {357, 92, 417, 162, BUTTON_COLOR,	"Them/Xoa Cung"},
						  {357, 162, 417, 232, BUTTON_COLOR,"Doi Ten Dinh"},
						  {357, 232, 417, 302, BUTTON_COLOR,"Xoa Dinh"},
						  {357, 302, 417, 372, BUTTON_COLOR,"Di Chuyen"},
						  {357, 372, 417, 442, BUTTON_COLOR,"Xoa Do Thi"},
						  {357, 442, 417, 498, BUTTON_COLOR,"Giup Do"}};
