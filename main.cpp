#include <ctime>
#include <cmath>
#include <cstring>
#include <iostream>
#include <graphics.h>

#define WIDTH  800
#define HEIGHT 600
#define LENGTH 500
#define PI 3.14159265358979323846

using namespace std;

int op, x, y;
float alfa;

struct point{
    int x, y;
} center;

//Square Grid Fractal
void squareGrid(point p, int L)
{
    point u;
    if (L > 10)
    {
        delay(10);
        srand (time(0));
        setcolor(rand()%15 + 1);

        p.x = p.x - L / 2;
        p.y = p.y - L / 2;
        u.x = p.x + L;
        u.y = p.y + L;
        rectangle(p.x, p.y, u.x, u.y);

        u.x = p.x;      u.y = p.y;      squareGrid(u, L / 2);
        u.x = p.x + L;  u.y = p.y;      squareGrid(u, L / 2);
        u.x = p.x + L;  u.y = p.y + L;  squareGrid(u, L / 2);
        u.x = p.x;      u.y = p.y + L;  squareGrid(u, L / 2);
    }
}

//Sierpinski Fractals
void triangle(point p1, point p2, point p3)
{
    line(p1.x, p1.y, p2.x, p2.y);
    line(p1.x, p1.y, p3.x, p3.y);
    line(p3.x, p3.y, p2.x, p2.y);
}

void sierpinskiTriangle(point p1, point p2, point p3, int L)
{
    point u1, u2, u3;
    if (L > 10)
    {
        delay(10);
        srand (time(0));
        setcolor(rand()%15 + 1);

        u1.x = (p1.x + p3.x) / 2;
        u1.y = (p1.y + p3.y) / 2;
        u2.x = (p1.x + p2.x) / 2;
        u2.y = (p1.y + p2.y) / 2;
        u3.x = (p3.x + p2.x) / 2;
        u3.y = (p3.y + p2.y) / 2;

        triangle(u1, u2, u3);

        sierpinskiTriangle(p1, u2, u1, L / 2);
        sierpinskiTriangle(u2, p2, u3, L / 2);
        sierpinskiTriangle(u1, u3, p3, L / 2);
    }
}

void sierpinskiT(point p, int L)
{
    int l = sqrt(3) * L / 2;
    point p1, p2, p3;

    p1.x = p.x - L / 2;
    p1.y = p.y + l / 2;
    p2.x = p.x;
    p2.y = p.y - l / 2;
    p3.x = p.x + L / 2;
    p3.y = p1.y;

    triangle(p1, p2, p3);
    sierpinskiTriangle(p1, p2, p3, L);
}

void sierpinskiCarpet(point r, int L)
{
    point p, u;
    if (L > 10)
    {
        delay(5);

        p.x = r.x - L / 2;
        p.y = r.y - L / 2;
        u.x = p.x + L;
        u.y = p.y + L;

        setfillstyle(SOLID_FILL, 15);
        bar(p.x, p.y, u.x, u.y);

        u.x = r.x - L; u.y = r.y - L; sierpinskiCarpet(u, L / 3);
        u.x = r.x    ; u.y = r.y - L; sierpinskiCarpet(u, L / 3);
        u.x = r.x + L; u.y = r.y - L; sierpinskiCarpet(u, L / 3);

        u.x = r.x + L; u.y = r.y;     sierpinskiCarpet(u, L / 3);
        u.x = r.x - L; u.y = r.y ;    sierpinskiCarpet(u, L / 3);

        u.x = r.x - L; u.y = r.y + L; sierpinskiCarpet(u, L / 3);
        u.x = r.x    ; u.y = r.y + L; sierpinskiCarpet(u, L / 3);
        u.x = r.x + L; u.y = r.y + L; sierpinskiCarpet(u, L / 3);
    }
}

//Koch Fractals
void left(float angle)
{
    alfa += angle * PI / 180.;
}

void right(float angle)
{
    alfa -= angle * PI / 180.;
}

void koch(float L)
{
    int x1 = x;
    int y1 = y;
    x += (int) (L * cos(alfa));
    y += (int) (L * sin(alfa));
    line (x1, y1, x, y);
}

void kochLine(int n, float L)
{
    if (n == 0)
        koch (L);
    else
    {
        kochLine(n - 1, L / 3); right(60);   delay(3);
        kochLine(n - 1, L / 3); left(120);   delay(3);
        kochLine(n - 1, L / 3); right(60);   delay(3);
        kochLine(n - 1, L / 3);              delay(3);
    }
}

void kochLineAll(float L)
{
    for (int i = 0; i < 5; i++)
    {
        cleardevice();
        x = 150; y = 150; alfa = 0;
        kochLine(i, L);
        outtextxy(150, HEIGHT - 50, "Press any key...");
        getch();
    }
}

void kochSnowflake(int n, float L)
{
    kochLine(n, L); left(120);
    kochLine(n, L); left(120);
    kochLine(n, L);
}

void kochSnowflakeAll(float L)
{
    for (int i = 0; i < 5; i++)
    {
        cleardevice();
        x = 150; y = 150; alfa = 0;
        kochSnowflake(i, L);
        outtextxy(150, HEIGHT - 50, "Press any key...");
        getch();
    }
}

//Hilbert Curve
void hilbert(float dx, float dy)
{
    int x1 = x + dx;
    int y1 = y + dy;

    line (x, y, x1, y1);
    x = x1;
    y = y1;
}

void hilbertLine(int n, float dx, float dy)
{
    if (n > 1)
        hilbertLine(n - 1, dy, dx);

    hilbert(dx, dy);

    if (n > 1)
        hilbertLine(n - 1, dx, dy);

    hilbert(dy, dx);

    if (n > 1)
        hilbertLine(n - 1, dx, dy);

    hilbert(-dx, -dy);

    if (n > 1)
        hilbertLine(n - 1, -dy, -dx);
}

void hilbertCurve(int n)
{
    float totalLength, startX, startY, startLength;

    if (HEIGHT < WIDTH)
        totalLength = (float)(0.9 * HEIGHT);
    else
        totalLength = (float)(0.9 * WIDTH);

    startX = (WIDTH - totalLength) / 2;
    startY = (HEIGHT - totalLength) / 2;
    startLength = (float)(totalLength / ((1<<n) - 1));

    x = (int)startX;
    y = (int)startY;
    hilbertLine(n, 0, (int)startLength);
}

void hilbertCurveAll()
{
    for (int i = 1; i < 8; i++)
    {
        cleardevice();
        hilbertCurve(i);
        outtextxy(150, HEIGHT - 20, "Press any key...");
        getch();
    }
}

void init(int fractalType = 0)
{
    const char *titleWindow;

    switch (fractalType)
    {
        case 1: titleWindow = "S Q U A R E     G R I D";                    break;
        case 2: titleWindow = "S I E R P I N S K I     T R I A N G L E";    break;
        case 3: titleWindow = "S I E R P I N S K I     C A R P E T";        break;
        case 4: titleWindow = "K O C H     L I N E";                        break;
        case 5: titleWindow = "K O C H     S N O W F L A K E";              break;
        case 6: titleWindow = "H I L B E R T      C U R V E";               break;
        case 7: titleWindow = "K O C H     L I N E";                        break;
        case 8: titleWindow = "K O C H     S N O W F L A K E";              break;
        case 9: titleWindow = "H I L B E R T      C U R V E";               break;
        default: titleWindow = "F R A C T A L S";
    }

    initwindow(WIDTH, HEIGHT, titleWindow, 400, 100);
    center.x = getmaxx() / 2;
    center.y = getmaxy() / 2;
}

void close()
{
    getch();
    cleardevice();
    closegraph();
}

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(h, c);
}

void menu()
{
    gotoxy(0, 0);
    cout<<"1.  Square Grid\n";
    cout<<"2.  Sierpinski Triangle\n";
    cout<<"3.  Sierpinski Carpet\n";
    cout<<"4.  Koch Line\n";
    cout<<"5.  Koch Snowflake\n";
    cout<<"6.  Hilbert\n";
    cout<<"7.  Koch Line Levels\n";
    cout<<"8.  Koch Snowflake Levels\n";
    cout<<"9.  Hilbert Levels\n";
    cout<<"10. Exit\n";
    cout<<"Your option:";
    cin>>op;
}

int main()
{
    SetConsoleTitle("F R A C T A L S");

    do{
        menu();
        switch (op)
        {
            case 1: init(1); squareGrid(center, 300);                   close(); break;
            case 2: init(2); sierpinskiT(center, LENGTH);               close(); break;
            case 3: init(3); sierpinskiCarpet(center, 200);             close(); break;
            case 4: init(4); x = 150; y = 150; kochLine(3, LENGTH);     close(); break;
            case 5: init(5); x = 150; y = 150; kochSnowflake(3, LENGTH);close(); break;
            case 6: init(6); hilbertCurve(4);                           close(); break;
            case 7: init(4); x = 150; y = 150; kochLineAll(LENGTH);     close(); break;
            case 8: init(5); x = 150; y = 150; kochSnowflakeAll(LENGTH);close(); break;
            case 9: init(6); hilbertCurveAll();                         close(); break;
        }
    } while (op != 10);

    return 0;
}
