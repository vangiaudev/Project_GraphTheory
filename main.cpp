// ---------------------------------------------------------------------------
//                   	Project Graph Theory
// ---------------------------------------------------------------------------
#include <fstream>	
#include <iostream>
#include "include/queue.hpp"	
#include "include/stack.hpp"	
#include "include/colors.hpp"			// Xac dinh tat ca ca mau can dung
#include "include/button.hpp"			// Xu ly cac nut lenh
#include "include/vertex.hpp"			// Dinh
#include "include/list_vertices.hpp"	// Quan ly danh sach cac dinh
#include "include/helpers.hpp" 			// Cac chuc nang co ban de ve do thi
#include "include/constants.hpp" 		// Dinh nghia tat ca cac hang so
#include "include/global_variables.hpp"	// Tat ca cac bien toan cuc

// ---------------------------------------------------------------------------
// 							Cac ham ve giao dien
// ---------------------------------------------------------------------------
void drawWindow();
void drawWorkingZone();
void drawLimitZone();
void drawMenuZone();
void drawTextZone();
void drawMatrixZone();
void showSpeed();
void showAllButtons();
void refreshScreen();
void refreshGraph(int);
void initScreen();
void initializer();

// ---------------------------------------------------------------------------
//                          Menu Thuat Toan
// ---------------------------------------------------------------------------
void pathXY();
void hamilton();
void euler();
void SCC();
// ---------------------------------------------------------------------------
//                          		File
// ---------------------------------------------------------------------------
void open();
void save();
void quit();
void help();

// ---------------------------------------------------------------------------
//                          Cac Chuc Nang Chinh Sua Do Thi
// ---------------------------------------------------------------------------
void addVertex();
void addEdges();
void renameVertex();
void deleteVertex();
void moveVertex();
void cleanGraph();

// ---------------------------------------------------------------------------
//                           Cac Chuc Nang Khac
// ---------------------------------------------------------------------------
void removeVertex(int);
void removeRow(int);
void removeCol(int);
void removeLast();


void tarjanVisit(int, int *, int *, stack &, int &, int &, bool);
void tarjanResult(stack &, int, int);
int tarjanAlgo(bool, int remove = -1);

void recursiveHamilton(int, int *, bool &);
void resultHamilton(int *);
void continueHamilton(bool &);

bool isExistUndirectedEdge(int, int); //kiem tra canh vo huong co ton tai
bool isExistDirectedEdge(int , int); //kiem tra canh co huong co ton tai
bool dfsToCheckConnected(bool (*)(int, int), int, int stop = -1);

void calcDegree(int *, int *);
bool isStronglyConnected(); //kiem tra lien thong manh
bool isWeaklyConnected(); //kiem tra lien thong yeu
int eulerChecker(); // kiem tra Euler

void copyToMutilGraph(bool [][MAX_VERTEX]); //sao chep thanh da do thi
bool isNegativeWeight(); //kiem tra do thi co trong so am Dijkstra
bool isNegativeCycle(double *); // Kiem tra do thi co chu trinh am Ford-Bellman
void dijkstra(int, int);
bool fordbellman(int, int); 

// ---------------------------------------------------------------------------
//                          Chuc Nang Tro Giup Ve Do Thi
// ---------------------------------------------------------------------------
void drawEdge(int, int, int); //ve canh
void drawAllEdges(); //ve tat ca canh
int chooseVertex(int, int skipReset = -1); //chon dinh
bool chooseStartVertex(int &, const char*, const char*); //chon dinh bat dau
bool chooseTwoVertices(int &, int &);
char getKey();
void adjustSpeed(char); //chinh toc do
bool isEmptyGraph(); //do thi rong
void showResultStack(stack &); //xuat ket qua
void showResultPathXY(double [], int, int); //xuat ket qua duong di XY

// ---------------------------------------------------------------------------
//                          Chuc nang nhap tu ban phim
// ---------------------------------------------------------------------------
bool getInputChar(char *, int, bool (*)(char));
bool getInputWeight(float &);

// ---------------------------------------------------------------------------
//                          Texts: In, Xoa, Thiet Ke Kieu Mau
// ---------------------------------------------------------------------------
void setTextPrintStyle(int);
void printText(float);
void printText(const char*);
void deleteText(const char*);
template <typename Type>
void printTextWl(Type); // print text -> endl
template <typename Type>
void printTextWlb(Type); // endl -> print text

// ---------------------------------------------------------------------------
//                          		Menu
// ---------------------------------------------------------------------------
int findButton(int, int); //nut tim
void switchMenuItem(int); //chuyen doi cac menu
void menu();
void backToMenu(); //quay lai
// ---------------------------------------------------------------------------

int main()
{
    initializer();
	menu();
	closegraph(); //ket thuc che do do hoa
	return EXIT_SUCCESS;
}
void drawWorkingZone() //ve vung lam viec
{
	setfillstyle(SOLID_FILL, wZONE_COLOR); //xu ly mau
	bar(wbLEFT, wTOP, wRIGHT, wBOTTOM); //ve hinh chu nhat
	setcolor(LINE_COLOR); 
	setlinestyle(SOLID_LINE, 1, 2); //kieu duong ve, do dam
	rectangle(wLEFT, wTOP, wRIGHT, wBOTTOM); //ve hinh chu nhat rong
}
void drawLimitZone() //ve vung gioi han
{
	setcolor(LIMIT_COLOR);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH); //kieu duong ve, do dam
	rectangle(wbLEFT + 2, wTOP + 2, wRIGHT - 2, wBOTTOM - 2); //ve hinh chu nhat rong
}
void drawMenuZone() //ve vung menu
{
	setbkcolor(BACKGROUND_COLOR); //dat mau nen
	setusercharsize(1, 2, 1, 2);  //xac dinh ky tu cho phong chu duoc ve
	settextstyle(BOLD_FONT, HORIZ_DIR, 1); //gom font chu, huong, kich thuoc
	settextjustify(LEFT_TEXT, TOP_TEXT); //dieu chinh cach viet (tu trai sang phai, tu tren xuong duoi)
	setcolor(LINE_COLOR);
	outtextxy(148, mTOP - 20, "FILE"); //in ra label "Menu" tai vi tri x = 5 va y = mTOP - 20
	outtextxy(148, fTOP - 120, "MENU"); //tuong tu label "File"
	outtextxy(138, aTOP - 20, "MATRIX"); //...
	setlinestyle(SOLID_LINE, 1, 2);  //kieu duong ve
	setcolor(LINE_COLOR);
	rectangle(mLEFT, mTOP, mRIGHT, mBOTTOM-105); //ve hinh chu nhat rong
	rectangle(fLEFT, fTOP-100, fRIGHT, fBOTTOM-15);
}
void drawTextZone() //ve vung hien thi van ban
{
	setfillstyle(SOLID_FILL, BACKGROUND_COLOR); //xu ly mau
	bar(tLEFT, tTOP, tRIGHT, tBOTTOM); //ve hinh chu nhat
	setcolor(LINE_COLOR);
	setlinestyle(SOLID_LINE, 1, 2); //kieu duong ve
	rectangle(tLEFT, tTOP, tRIGHT, tBOTTOM); //ve hinh chu nhat rong
	xCursor = xCURSOR; // Di chuyen con tro x den diem bat dau
	yCursor = yCURSOR;
}
void drawMatrixZone() //ve vung ma tran
{
	setfillstyle(SOLID_FILL, BACKGROUND_COLOR); 
	bar(aLEFT, aTOP, aRIGHT, aBOTTOM);
	setcolor(LINE_COLOR);
	setlinestyle(SOLID_LINE, 1, 2);
	rectangle(aLEFT, aTOP, aRIGHT, aBOTTOM);
	const int &n = listv.num + 1;
	if (n == 1) return;
	const float width = float(aRIGHT - aLEFT) / n;
	const float hight = float(aBOTTOM - aTOP) / n;
	setlinestyle(SOLID_LINE, 1, NORM_WIDTH);
	setcolor(BLACK);
	setbkcolor(BACKGROUND_COLOR);
	settextjustify(LEFT_TEXT, CENTER_TEXT);
	if (n > aVERTEX_MAX_2)
	{
		settextjustify(CENTER_TEXT, CENTER_TEXT);//dieu chinh cach viet (tu vi tri con tro sang hai ben, tu con tro len tren va xuong duoi)
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
		outtextxy((aRIGHT + aLEFT) / 2, (aBOTTOM + aTOP) / 2, "KHONG THE HIEN THI.");
		return;
	}
	if (n > aVERTEX_MAX_1) settextstyle(SMALL_FONT, HORIZ_DIR, 4);
	else
	{
		setusercharsize(1, 2, 1, 2);
		settextstyle(BOLD_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	}
	setlinestyle(SOLID_LINE, 1, NORM_WIDTH);
	char str[10];
	for (int i = 1; i < n; ++i)
	{
		line(aLEFT, aTOP + i * hight, aRIGHT, aTOP + i * hight);
		line(aLEFT + i * width, aTOP, aLEFT + i * width, aBOTTOM);
		outtextxy(ADJUST_TEXT_X, i * hight + ADJUST_TEXT_Y, listv.v[i - 1]->name);
		outtextxy(ADJUST_TEXT_X + i * width, ADJUST_TEXT_Y, listv.v[i - 1]->name);
		for (int j = 1; j < n; ++j)
			if (adjaGraph[i - 1][j - 1] != NO_EDGE_VALUE)
			{
				convertToChar(adjaGraph[i - 1][j - 1], str);
				outtextxy(ADJUST_TEXT_X + j * width, i * hight + ADJUST_TEXT_Y, str);
			}
	}
}
void showSpeed() //toc do duyet do thi
{
	char status[15];
	char speed[3];
	convertToChar((MAX_SPEED - delayRunTime) / 100, speed);
	strcpy(status, "Speed: ");
	strcat(status, speed);
	setcolor(LINE_COLOR);
	setfillstyle(SOLID_FILL, BACKGROUND_COLOR);
	bar(sLEFT, sTOP, sRIGHT, sBOTTOM);
	setbkcolor(BACKGROUND_COLOR);
	setusercharsize(1, 2, 1, 2);
	settextstyle(BOLD_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	outtextxy(sLEFT, sTOP, status);
}
void drawWindow()
{
	setcolor(DOT_COLOR);
	setbkcolor(BACKGROUND_COLOR);
	setfillstyle(CLOSE_DOT_FILL, wZONE_COLOR);
	bar(0, 0, WINDOW_WIDTH, WINDOW_HIGHT);
}
void showAllButtons() //Hien tat ca cac button
{
	for (int i = 0; i < NUM_OF_MENU; ++i)
	{
		menuButton[i].showNormalButton();
		showButtonIcon(menuButton, i);
	}
}
void initScreen() //Man hinh chinh
{
	drawWindow();
	drawWorkingZone();
	drawTextZone();
	drawMenuZone();
	drawMatrixZone();
	showAllButtons();
	showSpeed();
}
void initializer()
{
	initwindow(WINDOW_WIDTH + 5, WINDOW_HIGHT + 10); 
	setwindowtitle("Graph Theory 4.0");
	hwnd = GetActiveWindow();
	::SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE)&~WS_MAXIMIZEBOX);//&~WS_SIZEBOX
    initScreen();
    setMatrixTo(adjaGraph, NO_EDGE_VALUE);
}

void pathXY() //Tim duong di ngan nhat
{
	if (isEmptyGraph()) return;
	int start, stop;
	if (chooseTwoVertices(start, stop))
	{
		setTextPrintStyle(TEXT_COLOR);
		if (!isNegativeWeight()) //Kiem tra neu do thi khong co trong so am thi khoi chay Dijkstra
		{
			printTextWl("Khoi chay thuat toan Dijkstra:");
			dijkstra(start, stop);
		}
		else //Nguoc lai thi chay Ford-Bellman
		{
			printTextWl("Khoi chay thuat toan FordBellman: ");
			if (!fordbellman(start, stop))
				printTextWlb("Do thi ton tai chu trinh am.");
		} 
	}
	return backToMenu();
}

void hamilton()
{
	if (isEmptyGraph()) return;
	int path[listv.num];
	setArrayTo(trace, listv.num, 0);
	bool continueRun = 1;
	for (int i = 0; i < listv.num; ++i)
		if (continueRun && dfsToCheckConnected(isExistDirectedEdge, i))
		{
			setArrayTo(trace, listv.num, 0);
			path[0] = i;
			trace[i] = 1;
			recursiveHamilton(1, path, continueRun);
		}
	setTextPrintStyle(TEXT_COLOR);
	printText("Tim kiem ket thuc.");
	return backToMenu();
}
void euler()
{
	if (isEmptyGraph()) return;
	int start = eulerChecker();
	setTextPrintStyle(TEXT_COLOR);
	if (start == NOT_EXIST_EULER)
	{
		printTextWl("Do thi khong phai la Euler/Nua Euler.");
		return backToMenu();
	}
	if (start == EXIST_EULER)
	{
		if (!chooseStartVertex(start, "Chon dinh bat dau: ", "Chu trinh euler: ")) return;
	}
	else printText("Duong di euler: "); 
	stack s, result;
	bool gr[MAX_VERTEX][MAX_VERTEX];
	copyToMutilGraph(gr);
	s.push(start);
	int u, v;
	while (!s.isEmpty())
	{
		u = s.get();
		for (v = 0; v < listv.num; ++v)
			if (gr[u][v])
			{
				s.push(v);
				gr[u][v] = 0;
				break;
			}
		if (v == listv.num)
			result.push(s.pop());
	}
	showResultStack(result);
	return backToMenu();
}

void SCC()
{
	if (isEmptyGraph()) return;
	//listv.showAll(VERTEX_COLOR_0);
	setTextPrintStyle(TEXT_COLOR);
	printTextWl("Cac thanh phan lien thong manh:");
	int count = tarjanAlgo(1);
	setTextPrintStyle(TEXT_COLOR);
	printTextWlb("Tong cong: ");
	printText(count);
	return backToMenu();
}
inline void removeRow(int row)
{
	for (int i = row; i < listv.num - 1; ++i)
		for (int j = 0; j < listv.num; ++j)
			adjaGraph[i][j] = adjaGraph[i + 1][j];
}
inline void removeCol(int col)
{
	for (int i = 0; i < listv.num; ++i)
		for (int j = col; j < listv.num - 1; ++j)
			adjaGraph[i][j] = adjaGraph[i][j + 1];
}
inline void removeLast()
{
	const int &LAST = listv.num - 1;
	for (int i = 0; i < listv.num; ++i) //xoa dong cuoi va cot cuoi
	{
		adjaGraph[LAST][i] = NO_EDGE_VALUE;
		adjaGraph[i][LAST] = NO_EDGE_VALUE;
	}
}
void removeVertex(int v)
{
	removeCol(v);
	removeRow(v);
	removeLast();
}

void calcDegree(int *degIn, int *degOut)
{
	for (int i = 0; i < listv.num; ++i)
	{
		degOut[i] = degIn[i] = 0;
		for (int j = 0; j < listv.num; ++j)
		{
			if (adjaGraph[i][j] != NO_EDGE_VALUE) ++degOut[i];
			if (adjaGraph[j][i] != NO_EDGE_VALUE) ++degIn[i];
		}
	}
}

int tarjanAlgo(bool showResult, int remove)
{
	const int &NUM = listv.num;
	int disc[NUM];
	int low[NUM];
	setArrayTo(disc, NUM, 0);
	setArrayTo(trace, NUM, 1);
	int count(0), components(0);
	stack s;
	if (remove != -1)
	{
		disc[remove] = 1; // ignore remove
		trace[remove] = 0; // ignore remove
	}
	for (int i = 0; i < NUM; ++i)
		if (disc[i] == 0) tarjanVisit(i, disc, low, s, count, components, showResult);
	return components;
}
void tarjanVisit(int u, int *disc, int *low, stack &s, int &count, int &components, bool callTarjanResult)
{
	low[u] = disc[u] = ++count;
	s.push(u);
	int v;
	for (v = 0; v < listv.num; ++v)
		if (trace[v] != 0 && adjaGraph[u][v] != NO_EDGE_VALUE)
			if (disc[v] != 0)
				low[u] = min(low[u], disc[v]);
			else
			{
				tarjanVisit(v, disc, low, s, count, components, callTarjanResult);
				low[u] = min(low[u], low[v]);
			}
	if (disc[u] == low[u])
	{
		++components;
		if (callTarjanResult)
			tarjanResult(s, u, components);
		else
			do
			{
				v = s.pop();
				trace[v] = 0;
			} while (v != u);
	}
}
void tarjanResult(stack &s, int stop, int components)
{
	setTextPrintStyle(TEXT_COLOR);
	printText(components);
	printText(":(");
	int v;
	do
	{
		v = s.pop();
		trace[v] = 0;
		listv.v[v]->show(VERTEX_MORE_COLOR[components]);
		setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
		printText(listv.v[v]->name);
		printText(",");
		
	} while (v != stop);
	deleteText(",");
	printText(") ");
}
void continueHamilton(bool &continueRun)
{
	setTextPrintStyle(TEXT_COLOR);
	printTextWlb("Tiep tuc tim kiem Y/N ? : ");
	fflush(stdin);
	while (1)
	{
		if (kbhit())
		{
			if (toupper(getch()) == 'N')
			{
				continueRun = 0;
				printTextWl("");
				return;
			}
			break;
		}
		delay(DELAY_VALUE);
	}
	drawTextZone();
	drawAllEdges();
	listv.showAll(VERTEX_COLOR);
}
void recursiveHamilton(int u, int *path, bool &continueRun)
{
	for (int v = 0; v < listv.num; ++v)
		if (trace[v] != 1 && adjaGraph[path[u - 1]][v] != NO_EDGE_VALUE)
		{
			path[u] = v;
			if (u < listv.num - 1)
			{
				trace[v] = 1;
				if (continueRun) recursiveHamilton(u + 1, path, continueRun);
				trace[v] = 0;
			}
			else 
			{
				resultHamilton(path);
				continueHamilton(continueRun);
			}
		}
}
void resultHamilton(int *path)
{
	int begin = path[0];
	int end = path[listv.num - 1];
	bool isExistCycle = (adjaGraph[end][begin] != NO_EDGE_VALUE);
	setTextPrintStyle(TEXT_COLOR);
	(isExistCycle) ? printText("Chu trinh hamilton: ") : printText("Duong di hamilton: ");
	printText(listv.v[begin]->name);
	listv.v[begin]->show(VERTEX_CHOSE_COLOR);
	for (int i = 1; i < listv.num; ++i)
	{
		end = path[i];
		drawEdge(begin, end, EDGE_VISTED_COLOR);
		listv.v[end]->show(VERTEX_VISTED_COLOR);
		setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
		printText("->");
		printText(listv.v[end]->name);
		begin = end;
		if (getKey() == KEY_ESC) return;
		delay(delayRunTime);
	}
	if (isExistCycle)
	{
		begin = path[0];
		printText("->");
		printText(listv.v[begin]->name);
		drawEdge(end, begin, EDGE_VISTED_COLOR);
	}
}
inline bool isExistUndirectedEdge(int v1, int v2)
{
	return (adjaGraph[v1][v2] != NO_EDGE_VALUE || adjaGraph[v2][v1] != NO_EDGE_VALUE);
}
inline bool isExistDirectedEdge(int v1, int v2)
{
	return (adjaGraph[v1][v2] != NO_EDGE_VALUE);
}
bool dfsToCheckConnected(bool (*checkEdge)(int , int ), int start, int stop)
{
	setArrayTo(trace, listv.num, 0);
	stack s;
	s.push(start);
	trace[start] = 1;
	int numOfCheckedVertex(0);
	while (!s.isEmpty())
	{
		start = s.pop();
		if (start == stop) return 1;
		++numOfCheckedVertex;
		for (int i = 0; i < listv.num; ++i)
			if (trace[i] == 0 && checkEdge(start, i))
			{
				trace[i] = 1;
				s.push(i);
			}
	}
	return (numOfCheckedVertex == listv.num);
}

inline bool isStronglyConnected()
{
	return (tarjanAlgo(0) == 1); // Cac thanh phan lien thong manh = 1
}
inline bool isWeaklyConnected()
{
	return dfsToCheckConnected(isExistUndirectedEdge, 0);
}
int eulerChecker()
{
	int returnValue = NOT_EXIST_EULER;
	int degIn[listv.num];
	int degOut[listv.num];
	calcDegree(degIn, degOut);
	int u(0), v(0), count(0);
	for (int i = 0; i < listv.num; ++i)
		if (degIn[i] != degOut[i])
			(++count == 1) ? u = i : v = i;
	if (isStronglyConnected() && count == 0)
		returnValue = EXIST_EULER;
	else
		if (isWeaklyConnected() && count == 2)
		{
			const int s1 = abs(degOut[u] - degIn[u]);
			const int s2 = abs(degIn[v] - degOut[v]);
			if (s1 == 1 && s2 == 1)
				(degOut[u] < degOut[v]) ? returnValue = v : returnValue = u; // return start's vertex haft euler 
		}
	return returnValue;
}
void copyToMutilGraph(bool gr[][MAX_VERTEX]) // use for euler
{
	for (int i = 0; i < listv.num; ++i)
		for (int j = 0; j < listv.num; ++j)
			gr[i][j] = (adjaGraph[i][j] != NO_EDGE_VALUE);
}
bool isNegativeWeight()
{
	for (int i = 0; i < listv.num; ++i)
		for (int j = 0; j < listv.num; ++j)
			if (adjaGraph[i][j] != NO_EDGE_VALUE && adjaGraph[i][j] < 0)
				return 1;
	return 0;
}
void dijkstra(int start, int stop)
{
	const int &NUM = listv.num;
	bool free[NUM];
	double dist[NUM];
	setArrayTo(free, NUM, true);
	setArrayTo(trace, NUM, start);
	setArrayTo(dist, NUM, MAX_EDGE_VALUE);
	dist[start] = 0;
	float d; int u;
	while (1)
	{
		d = MAX_EDGE_VALUE;
		u = -1;
		for (int i = 0; i < NUM; ++i)
			if (free[i] && dist[i] < d)
			{
				d = dist[i];
				u = i;
			}
		if (u == -1 || u == stop) break;
		free[u] = 0;
		for (int i = 0; i < NUM; ++i)
		{
			float weight = adjaGraph[u][i];
			if (free[i] && weight != NO_EDGE_VALUE && dist[i] > d + weight)
			{
				dist[i] = d + weight;
				trace[i] = u;
			}
		}
	}
	showResultPathXY(dist, start, stop);
}
bool isNegativeCycle(double *dist)
{
	const int &NUM = listv.num;
	for (int i = 0; i < NUM; ++i)
		for (int j = 0; j < NUM; ++j)
			if (adjaGraph[j][i] != NO_EDGE_VALUE && dist[j] != MAX_EDGE_VALUE 
				&& dist[i] > dist[j] + adjaGraph[j][i])
				return true;
	return false;
}
bool fordbellman(int start, int stop)
{
	const int &NUM = listv.num;
	double dist[NUM];
	setArrayTo(trace, NUM, start);
	for (int i = 0; i < NUM; ++i)
		dist[i] = (adjaGraph[start][i] == NO_EDGE_VALUE) ? MAX_EDGE_VALUE : adjaGraph[start][i];
	dist[start] = 0;
	for (int k = 1; k < NUM - 1; ++k)
	{
		bool stop = 1;
		for (int i = 0; i < NUM; ++i)
		{
			if (i == start) continue;
			for (int j = 0; j < NUM; ++j)
			{
				if (i == j) continue;
				double weight = adjaGraph[j][i];
				if (weight != NO_EDGE_VALUE && dist[i] > dist[j] + weight && dist[j] != NO_EDGE_VALUE)
				{
					dist[i] = dist[j] + weight;
					trace[i] = j;
					stop = 0;
				}
			}
		}
		if (stop) break; // if not update any dist ==> stop
	}
	if (isNegativeCycle(dist)) return false;
	showResultPathXY(dist, start, stop);
	return true;
}

void open()
{

	if (listv.num > 0 && MessageBox(hwnd,"Dang ton tai do thi\
	\nBan co muon xoa va mo do thi moi khong?","Thong bao",
	MB_APPLMODAL | MB_ICONWARNING | MB_YESNO) == IDNO) return;
	OPENFILENAME file;
	char fileName[MAX_PATH] = "\0";
//	_getcwd(fileName, MAX_PATH);
	ZeroMemory(&file, sizeof(file));
	file.lStructSize = sizeof(file);
	file.lpstrFile = fileName;
	file.nMaxFile = sizeof(fileName);
	file.lpstrFilter = (FILE_FILTER);
	file.nFilterIndex = 1;
	file.hwndOwner = hwnd;
	file.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_READONLY;
	bool error = 0;
	if (GetOpenFileName(&file) == 1)
	{
		while (ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);
		std::ifstream openFile(fileName);
		int num;
		if ((openFile >> num) && openFile.good())
		{
			listv.clear();
			setMatrixTo(adjaGraph, NO_EDGE_VALUE); //Xoa ma tran
			char tmpName[MAX_NAME_LENGTH];
			int x, y; float weight; 
			for (int i = 0; i < num && !error; ++i)
				if (!(openFile >> tmpName >> x >> y)) error = 1;
				else listv.addVertex(tmpName, x, y);
			if (!error)
				while (!openFile.eof())
				{
					if (!(openFile >> x >> y >> weight)) break;
					else adjaGraph[x][y] = weight;
				}
			isSaved = 1;
		}
		else error = 1;
		openFile.close();
	}
	if (error) 
	{
		listv.clear();
		setMatrixTo(adjaGraph, NO_EDGE_VALUE); //Xoa ma tran
		MessageBox(hwnd, "LOI DOC FILE!!!", "Loi",  MB_APPLMODAL | MB_ICONERROR);
	}
}
void save()
{
	OPENFILENAME file;
	char fileName[MAX_PATH] = "\0";
	ZeroMemory(&file, sizeof(file));
	file.lStructSize = sizeof(file);
	file.lpstrFile = fileName;
	file.nMaxFile = sizeof(fileName);
	file.lpstrFilter = (FILE_FILTER);
	file.nFilterIndex = 1;
	file.hwndOwner = hwnd;
	file.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_CREATEPROMPT;
	if (GetSaveFileName(&file) == 1)
	{
		if (!strstr(fileName, ".graph")) 
			strcat(fileName, ".graph");
		std::ofstream saveFile(fileName);
		const int num = listv.num;
		saveFile << num << '\n';
		for (int i = 0; i < num; ++i)
			saveFile << listv.v[i]->name << ' ' << listv.v[i]->x << ' ' << listv.v[i]->y << '\n';
		saveFile << '\n'; // Endl giua dinh va cac canh
		for (int i = 0; i < num; ++i)
			for (int j = 0; j < num; ++j)
				if (adjaGraph[i][j] != NO_EDGE_VALUE)
					saveFile << i << ' ' << j << ' ' << adjaGraph[i][j] << '\n';
		saveFile.close();
		isSaved = 1;
	}
}
void quit()
{
	if (!isSaved && listv.num > 0)
	{
		int id = MessageBox(hwnd, "Ban co muon luu do thi lai khong?", "Save file",
								  MB_APPLMODAL | MB_ICONEXCLAMATION | MB_YESNOCANCEL);
		if (id == IDCANCEL) return;
		if (id == IDYES) return save();
	}
	closegraph();
	exit(EXIT_SUCCESS);
}

void drawEdge(int begin, int end, int color)
{
	const int &x1 = listv.v[begin]->x;
	const int &y1 = listv.v[begin]->y;
	const int &x2 = listv.v[end]->x;
	const int &y2 = listv.v[end]->y;
	if (adjaGraph[end][begin] == NO_EDGE_VALUE || begin < end)
		drawArrow(x1, y1, x2, y2, color, adjaGraph[begin][end]);
	else
		drawCurvedLine(x1, y1, x2, y2, color, adjaGraph[begin][end]);
}
void drawAllEdges()
{
	for (int i = 0; i < listv.num; ++i)
		for (int j = 0; j < listv.num; ++j)
			if (adjaGraph[i][j] != NO_EDGE_VALUE)
				drawEdge(i, j, EDGE_COLOR);
}
int chooseVertex(int highLightColor, int skipReset)
{
	drawLimitZone();
	int x, y;
	int newPos(-1), oldPos(-1);
	while (1)
	{
		if (getKey() == KEY_ESC) break;
		newPos = listv.find(mousex(), mousey());
		if (newPos != oldPos)
		{
			if (newPos != -1 && newPos != skipReset) 
				listv.v[newPos]->show(highLightColor);
			if (oldPos != -1 && oldPos != skipReset)
				listv.v[oldPos]->show(VERTEX_COLOR);
			oldPos = newPos;
		}
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (!isInWorkingZone(x, y)) break;
			if (newPos != -1)
			{
				listv.v[newPos]->show(highLightColor);
				return newPos;
			}
		}
		delay(DELAY_VALUE);
	}
	return -1;
}
bool chooseStartVertex(int &start, const char *text1, const char *text2)
{
	setTextPrintStyle(TEXT_COLOR);
	printText(text1);
	start = chooseVertex(VERTEX_CHOOSING_COLOR);
	if (start == -1) return 0;
	setTextPrintStyle(TEXT_COLOR);
	printText(listv.v[start]->name);
	printTextWlb(text2);
	return 1;
	
}
bool chooseTwoVertices(int &start, int &stop)
{
	setTextPrintStyle(TEXT_COLOR);
	printText("Chon dinh xuat phat: ");
	start = chooseVertex(VERTEX_CHOOSING_COLOR);
	if (start == -1) return 0;
	setTextPrintStyle(TEXT_COLOR);
	printTextWl(listv.v[start]->name);
	listv.v[start]->show(VERTEX_CHOSE_COLOR);
	setTextPrintStyle(TEXT_COLOR);
	printText("Chon dinh ket thuc: ");
	stop = chooseVertex(VERTEX_CHOOSING_COLOR, start);
	if (stop == -1) return 0;
	setTextPrintStyle(TEXT_COLOR);
	printTextWl(listv.v[stop]->name);
	listv.v[stop]->show(VERTEX_CHOSE_COLOR);
	if (start == stop)
	{
		listv.v[stop]->show(VERTEX_COLOR);
		return 0;
	}
	return 1;
}
bool isEmptyGraph()
{
	if (listv.num == 0)
	{
		MessageBox(hwnd, "Do thi rong", "Loi", MB_APPLMODAL | MB_ICONERROR);
		return 1;
	}
	return 0;
}
void adjustSpeed(char key)
{
	if (key == KEY_LEFT)
		delayRunTime = (delayRunTime < MAX_SPEED) ? delayRunTime + 100 : MAX_SPEED;
	else if (key == KEY_RIGHT)
		delayRunTime = (delayRunTime > 100) ? delayRunTime - 100 : 0;
	showSpeed();
}
char getKey()
{
	if (kbhit())
	{
		char c = getch();
		switch (c)
		{
			case KEY_ESC:
				return KEY_ESC;
			case ARROW_KEY:
				c = getch();
				adjustSpeed(c);
				return c;
			case KEY_Q:
				return KEY_Q;
			case KEY_LQ:
				return KEY_Q;
			default:
				return KEY_NULL;
		}
	}
	return KEY_NULL;
}
void showResultStack(stack &s)
{
	int v, u = s.pop();
	setTextPrintStyle(TEXT_COLOR);
	printText(listv.v[u]->name);
	listv.v[u]->show(VERTEX_CHOSE_COLOR);
	while (!s.isEmpty())
	{
		v = s.pop();
		setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
		printText("->");
		printText(listv.v[v]->name);
		drawEdge(u, v, EDGE_VISTED_COLOR);
		listv.v[v]->show(VERTEX_VISTED_COLOR);
		u = v;
		if (getKey() == KEY_ESC) return;
		delay(delayRunTime);
	}
}
void showResultPathXY(double dist[], int start, int stop)
{
	setTextPrintStyle(TEXT_COLOR);
	if (dist[stop] == MAX_EDGE_VALUE)
		printText("Khong ton tai duong di.");
	else
	{
		printText("Tong trong so: ");
		printTextWl(dist[stop]);
		printText("Duong di ngan nhat: ");
		stack s;
		while (stop != start)
		{
			s.push(stop);
			stop = trace[stop];
		}
		s.push(start);
		return showResultStack(s);
	}
}
void setTextPrintStyle(int color)
{
//	setusercharsize(9, 10, 9, 10);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
	setbkcolor(BACKGROUND_COLOR);
	setcolor(color);
	settextjustify(LEFT_TEXT, TOP_TEXT);
}
bool getInputWeight(float &res)
{
	char str[10];
	getInputChar(str, 10, inputFloat);
	if (!isFloat(str)) return 0;
	res = roundf(toFloat(str) * 100) / 100;
	if (res > MAX_WEIGHT || res < MIN_WEIGHT)
	{
		char msg[70]; char w[10];
		strcpy(msg, "Trong so khong cho phep.\nTrong so >= ");
		convertToChar(MIN_WEIGHT, w);
		strcat(msg, w);
		strcat(msg, " & Trong so <= ");
		convertToChar(MAX_WEIGHT, w);
		strcat(msg, w);
		MessageBox(hwnd, msg, "Loi", MB_APPLMODAL | MB_ICONERROR);
		return 0;
	}
	return 1;
}
bool getInputChar(char *str, int max, bool (*checkKey)(char key))
{
	setTextPrintStyle(BLUE);
	int i = 0; str[0] = '\0';
	char key[2] = {'\0', '\0'};
	while (i < max)
	{
		if (kbhit())
		{
			key[0] = getch();
			if (key[0] == KEY_ESC || key[0] == KEY_ENTER) break;
			if (key[0] == KEY_BACKSPACE && i > 0) {--i; key[0] = str[i]; deleteText(key); str[i] = '\0';}
			else if (checkKey(key[0])) {strcat(str, key); ++i; printText(key);}
		}
		if (ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);
		delay(DELAY_VALUE);
	}
	return (i > 0);
}
void deleteText(const char* str)
{
	if (xCursor <= xCURSOR) return;
	const int currentColor = getcolor();
	setTextPrintStyle(BACKGROUND_COLOR);
	const int tw = textwidth(str);
	xCursor -= tw;
	printText(str);
	xCursor -= tw;
	setTextPrintStyle(currentColor);
}
void printText(const char *str)
{
	int const tw = textwidth(str);
	if (xCursor + tw >= tRIGHT)
	{
		xCursor = xCURSOR;
		yCursor += TEXTHIGHT;
	}
	if (yCursor > tBOTTOM - TEXTHIGHT)
	{
		drawTextZone();
		xCursor = xCURSOR;
		yCursor = yCURSOR;
		setTextPrintStyle(TEXT_COLOR);
	}
	outtextxy(xCursor, yCursor, str);
	xCursor += tw;
}
void printText(float value)
{
	char str[MAX_INPUT];
	convertToChar(value, str);
	printText(str);
}
template <typename Type>
void printTextWl(Type s)
{
	printText(s);
	xCursor = xCURSOR;
	yCursor += TEXTHIGHT;
}
template <typename Type>
void printTextWlb(Type s)
{
	xCursor = xCURSOR;
	yCursor += TEXTHIGHT;
	printText(s);
}
void addVertex()
{
	drawLimitZone();
	if (listv.num == MAX_VERTEX)
	{
		char msg[45], num[3];
		strcpy(msg, "Qua so luong dinh cho phep MAX_VERTEX = ");
		convertToChar(MAX_VERTEX, num);
		strcat(msg, num);
		MessageBox(hwnd, msg, "Loi", MB_APPLMODAL | MB_ICONERROR);
	}
	int x, y;
	setTextPrintStyle(TEXT_COLOR);
	printText("Click chuot de them dinh.");
	while (listv.num < MAX_VERTEX)
	{
		if (getKey() == KEY_ESC) break;
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (listv.find(x, y) != -1)
			{
				MessageBox(hwnd, "Trung dinh da co\nVui long chon lai.", "Loi",
							MB_APPLMODAL | MB_ICONERROR);
				continue;
			}
			if (isInLimitZone(x, y))
			{
				listv.addVertex(x, y);
				drawMatrixZone();
				isSaved = 0;
			}
			else break;
		}
		delay(DELAY_VALUE);
	}
}
void addEdges()
{
	if (isEmptyGraph()) return;
	int begin, end, oldEnd = -1;
	float weight;
	setTextPrintStyle(TEXT_COLOR);
	printText("Noi hai dinh de them/xoa cung.");
	while (1)
	{
		begin = chooseVertex(VERTEX_CHOOSING_COLOR);
		if (begin == -1) break;
		int x = listv.v[begin]->x;
		int y = listv.v[begin]->y;
		if (ismouseclick(WM_LBUTTONUP)) clearmouseclick(WM_LBUTTONUP);
		while (!ismouseclick(WM_LBUTTONUP))
		{
			setactivepage(1 - getactivepage());
			initScreen();
			drawLimitZone();
			drawAllEdges();
			listv.showAll();
			listv.v[begin]->show(VERTEX_CHOSE_COLOR);
			menuButton[ADD_EDGE_MENU].showChoseButton();
			showButtonIcon(menuButton, ADD_EDGE_MENU);
			end = listv.find(mousex(), mousey());
			drawArrow(x, y, mousex(), mousey(), EDGE_HIGHTLIGHT_COLOR, 0);
			setvisualpage(getactivepage());
			if (oldEnd != -1 && oldEnd != end && oldEnd != begin)
				listv.v[oldEnd]->show(VERTEX_COLOR);
			if (end != begin && end != -1 && end != oldEnd)
				listv.v[end]->show(VERTEX_CHOOSING_COLOR);
			oldEnd = end;
			if (!isInWorkingZone(mousex(), mousey())) break;
			delay(DELAY_VALUE);
		}
		if (end == -1 || end == begin)
		{
			refreshGraph(ADD_EDGE_MENU);
			listv.v[begin]->show(VERTEX_COLOR);
			continue;
		}
		listv.v[end]->show(VERTEX_CHOSE_COLOR);
		setvisualpage(getactivepage());
		adjaGraph[begin][end] = DEFAULT_WEIGHT;
		refreshGraph(ADD_EDGE_MENU);
		drawEdge(begin, end, EDGE_HIGHTLIGHT_COLOR);
		setTextPrintStyle(TEXT_COLOR);
		printText("Nhap trong so (xoa cung nhap '-') cung ");
		printText(listv.v[begin]->name);
		printText("->");
		printText(listv.v[end]->name);
		printText(": ");
		if (getInputWeight(weight)) adjaGraph[begin][end] = weight;
		else adjaGraph[begin][end] = NO_EDGE_VALUE;
		isSaved = 0;
		refreshGraph(ADD_EDGE_MENU);
		listv.v[begin]->show(VERTEX_COLOR);
		listv.v[end]->show(VERTEX_COLOR);
	}
}
void renameVertex()
{
	if (isEmptyGraph()) return;
	int choose;
	while (1)
	{
		if (chooseStartVertex(choose, "Chon dinh can doi ten: ", "Nhap ten moi cho dinh "))
		{
			printText(listv.v[choose]->name);
			printText(": ");
			listv.v[choose]->show(VERTEX_CHOSE_COLOR);
			char name[MAX_NAME_LENGTH];
			if (getInputChar(name, MAX_NAME_LENGTH - 1, inputAscii) && !listv.isExist(name))
			{
				listv.updateCurrentName(name);
				listv.v[choose]->clearName();
				strcpy(listv.v[choose]->name, name);
				drawMatrixZone();
				isSaved = 0;
			}
			else MessageBox(hwnd, "Trung ten hoac nhap sai", "Loi", MB_APPLMODAL | MB_ICONERROR);
			listv.v[choose]->show(VERTEX_COLOR);
			printTextWl("");
		} else break;
	}
}
void deleteVertex()
{
	if (isEmptyGraph()) return;
	while (listv.num > 0)
	{
		setTextPrintStyle(TEXT_COLOR);
		printText("Chon dinh can xoa: ");
		int choose = chooseVertex(VERTEX_DELETE_COLOR);
		if (choose == -1) break;
		setTextPrintStyle(VERTEX_DELETE_COLOR);
		printText(listv.v[choose]->name);
		removeVertex(choose);
		listv.deleteVertex(choose);
		refreshGraph(DELETEVE_MENU);
		isSaved = 0;
		if (listv.num == 0)
			listv.clear();
	}
}
void moveVertex()
{
	if (isEmptyGraph()) return;
	int x, y;
	setTextPrintStyle(TEXT_COLOR);
	printTextWl("Dung thao tac keo/tha dinh de di chuyen tung dinh");
	printText("hoac Ctr + keo/tha de di chuyen toan bo do thi.");
	while (1)
	{
		int choose = chooseVertex(VERTEX_CHOOSING_COLOR);
		if  (choose == -1) break;
		if (ismouseclick(WM_LBUTTONUP)) clearmouseclick(WM_LBUTTONUP);
		isSaved = 0;
		listv.v[choose]->show(VERTEX_CHOSE_COLOR);
		while (!ismouseclick(WM_LBUTTONUP))
		{
			if (ismouseclick(WM_MOUSEMOVE))
			{
				getmouseclick(WM_MOUSEMOVE, x, y);
				if (!isInLimitZone(x, y)) continue;
				if (GetKeyState(VK_CONTROL) < 0) // Crt + di chuyen tat ca cac dinh cua do thi
				{
					int dx = x - listv.v[choose]->x;
					int dy = y - listv.v[choose]->y;
					for (int i = 0; i < listv.num; ++i)
					{
						listv.v[i]->x += dx;
						listv.v[i]->y += dy;
						if (!isInLimitZone(listv.v[i]->x, listv.v[i]->y))
						{
							for (int j = i; j >= 0; --j)
							{
								listv.v[j]->x -= dx;
								listv.v[j]->y -= dy;
							}
							break;
						}
					}
				} else listv.v[choose]->setCoordinate(x, y); // di chuyen tung dinh
				setactivepage(1 - getactivepage());
				initScreen();
				drawLimitZone();
				drawAllEdges();
				listv.showAll();
				menuButton[MOVEVE_MENU].showChoseButton();
				showButtonIcon(menuButton, MOVEVE_MENU);
				setvisualpage(getactivepage());
			}
			delay(DELAY_VALUE);
		}
		listv.v[choose]->show(VERTEX_COLOR);
		setvisualpage(getactivepage());
	}
}
void cleanGraph()
{
	if (isEmptyGraph()) return;
	if (MessageBox(hwnd, "Ban co chac khong?", "Xoa do thi",
		MB_APPLMODAL| MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
		listv.clear();
		setMatrixTo(adjaGraph, NO_EDGE_VALUE);
		refreshGraph(CLEAN_GRAPH_MENU);
		isSaved = 1;
	}
}
void help()
{
	MessageBox(hwnd, "Chuong trinh Mo phong cac thuat toan cua do thi.\n"
					"Su dung:\n"
					"Phim <ESC> : Huy chuc nang.\n"
					"Phim <Q> : Thoat chuong trinh.\n"
					"Phim <LEFT>/<RIGHT> : Chinh toc do giam/tang.\n"
					"\nNhom sinh vien thuc hien:\n"
					"1. Nguyen Van Giau\n2. Huynh Anh Du\n3. Huynh Bao Loc\n4. Nguyen Minh Van\n5. Tran The Phuong\n",
				 	"Help", MB_APPLMODAL | MB_ICONINFORMATION);
}
int findButton(int x, int y)
{
	for (int i = 0; i < NUM_OF_MENU; ++i)
		if (menuButton[i].isButtonClick(x, y))
			return i;
	return -1;
}
void backToMenu()
{
	setTextPrintStyle(TEXT_COLOR);
	printTextWlb("Nhan phim bat ky hoac click chuot de tiep tuc.");
	if (ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);
	fflush(stdin);
	while (1)
	{
		if (kbhit()) break;
		if (ismouseclick(WM_LBUTTONDOWN)) break;
		delay(DELAY_VALUE);
	}
	if (ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);
	fflush(stdin);
}
void switchMenuItem(int chose)
{
	switch (chose)
	{
		case PATHXY_MENU: 			return pathXY();
		case HAMILTON_MENU: 		return hamilton();
		case EULER_MENU: 			return euler();
		case SCC_MENU:				return SCC();
		case OPEN_MENU: 			return open();
		case SAVE_MENU:				return save();
		case QUIT_MENU: 			return quit();
		case ADD_VERTEX_MENU:	 	return addVertex();
		case ADD_EDGE_MENU: 		return addEdges();
		case RENAME_VERTEX_MENU: 	return renameVertex();
		case DELETEVE_MENU: 		return deleteVertex();
		case MOVEVE_MENU: 			return moveVertex();
		case CLEAN_GRAPH_MENU: 		return cleanGraph();
		case HELP_MENU: 			return help();
		default: return;
	}
}
void refreshScreen()
{
	setactivepage(1 - getactivepage());
	initScreen();
	drawAllEdges();
	listv.showAll(VERTEX_COLOR);
	setvisualpage(getactivepage());
}
void refreshGraph(int mPos)
{
	setactivepage(1 - getactivepage());
	drawWorkingZone();
	drawMatrixZone();
	drawTextZone();
	showAllButtons();
	drawAllEdges();
	listv.showAll();
	menuButton[mPos].showChoseButton();
	showButtonIcon(menuButton, mPos);
	setvisualpage(getactivepage());
}
inline void showChoseButton(int pos)
{
	if (pos >= ADD_VERTEX_MENU) refreshScreen();
	menuButton[pos].showChoseButton();
	showButtonIcon(menuButton, pos);
}
inline void showHightLightButton(int pos)
{
	menuButton[pos].showHightLightButton();
	if (pos >= ADD_VERTEX_MENU) menuButton[pos].showButtonHint();
	showButtonIcon(menuButton, pos);
}
inline void showNormalButton(int pos)
{
	if (pos >= ADD_VERTEX_MENU) refreshScreen();
	menuButton[pos].showNormalButton();
	showButtonIcon(menuButton, pos);
}
inline void update(int &oldPos, int &newPos, int x, int y)
{
	newPos = findButton(x, y);
	if (newPos != oldPos)
	{
		if (oldPos != -1) showNormalButton(oldPos);
		if (newPos != -1) showHightLightButton(newPos);
		oldPos = newPos;
	}
}
void menu()
{
	int x, y;
	int newPos(-1), oldPos(-1);
	while (1)
	{
		if (getKey() == KEY_Q) quit();
		if (ismouseclick(WM_MOUSEMOVE))
		{
			getmouseclick(WM_MOUSEMOVE, x, y);
			update(oldPos, newPos, x, y);
		}
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			clearmouseclick(WM_LBUTTONDOWN);
			if (newPos != -1)
			{
				showChoseButton(newPos);
				switchMenuItem(newPos);
			}
			oldPos = -1;
			refreshScreen();
			update(oldPos, newPos, mousex(), mousey());
		}
		delay(DELAY_VALUE);
	}
}
