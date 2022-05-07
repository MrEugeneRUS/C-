#include "TXLib.h"
#include "math.h"

struct coord
{
    int x;
    int y;
};

double alphaDeg = 160;
double alphaRad = alphaDeg * M_PI / 180;

void DrawLandscape ();
void DrawRope   (coord catapult);
void DrawCatapult ();
void DrawBucket (coord bucket);
void DrawLever  ();
void DrawStone     ();
void DrawWall     (coord wall);
void DrawWarrior   (coord warrior, COLORREF color);
void DrawSun    ();
void DrawRays     ();
void DrawClouds    ();
void DrawWarriors();
void DrawFinalAngleValue();

void CalculateCatapult();
void CalculateLever();
void CalculateStone();

LRESULT CALLBACK MyWndProc (HWND window, UINT message, WPARAM wParam, LPARAM lParam);

coord lever0     = {-198, 650};
coord lever1     = {-368, 586};
coord bucket     =  {-353, 598};
coord catapult   = {-400, 635};
coord wall   = {710, 400};
coord rays   = {210, 5};
coord stone  = {-353, 598};
double stoneSpeedX = 0;
double stoneSpeedY = 0;
int xDirection = 1;
int finalAngle = 135;

coord warrior[] = {{870, 627}, {985, 627}, {1100, 627}, {1215, 627}, {1330, 627}};
coord monteki   = {-200, 627};
COLORREF red  = RGB (204, 29, 64);
COLORREF blue = RGB (0, 99, 198);

void Init();
void Calculate();
void Draw();
bool NeedContinue();
bool needContinue;
bool isLeverMoving = false;
bool isStoneMoving = false;

void DrawBackground();


int main()
{
    Init();
    while( NeedContinue() ) {
        Calculate();
        Draw();
        txSleep( 10 );
    }
    return 0;
}

void Init()
{
    txCreateWindow (1500, 800);
    needContinue = true;
    txDisableAutoPause();
    txTextCursor(false);
    txSetWindowsHook (MyWndProc);
}

void Calculate()
{
    CalculateCatapult();
    CalculateLever();
    CalculateStone();
}

void Draw()
{
    txBegin();
    txClear();
    DrawBackground();
    DrawCatapult();
    DrawWarriors();
    DrawFinalAngleValue();

    txEnd();
}

bool NeedContinue()
{
    return needContinue;
}

void DrawBackground()
{
        DrawLandscape ();
        DrawSun    ();
        DrawRays    ();
        DrawClouds ();
        DrawWall(wall);
}

void DrawLandscape ()
{
    txSetColor      (RGB(153, 217, 234));
    txSetFillColor  (RGB(153, 217, 234));

    txRectangle     (0, 0, 1700, 700);

    txSetFillColor  (RGB(34, 177, 76));
    txRectangle     (0, 700, 1900, 800);

}

void DrawSun ()
{
    txSetColor      (TX_YELLOW);
    txSetFillColor  (TX_YELLOW);

    txCircle        (0, 0, 200);

    txSetFillColor  (TX_BLACK);

    txCircle        (25, 65, 10);
    txCircle        (65, 25, 10);

    txSetColor      (TX_BLACK, 5);

    txArc           (0, 0, 90, 90, 270, 90);
}


void DrawRays ()
{
    txSetColor      (TX_YELLOW, 8);
    txLine          (rays.x, rays.y, rays.x + 100, rays.y);

    txLine          (rays.x - 10, rays.y + 75, rays.x + 90, rays.y + 120);

    txLine          (rays.x - 60, rays.y + 145, rays.x + 30, rays.y + 235);

    txLine          (rays.x - 130, rays.y + 195, rays.x - 85, rays.y + 295);

    txLine          (rays.x - 205, rays.y + 205, rays.x - 205, rays.y + 305);
}


void DrawClouds ()
{
    coord clouds[] = {{750, 45},  {1050, 95}, {450, 125},  {1350, 125}};
    txSetColor        (TX_WHITE);
    txSetFillColor    (TX_WHITE);
    for( int i = 0; i < 4; i++ ) {
        txCircle          (clouds[i].x, clouds[i].y, 40);
        txCircle          (clouds[i].x - 40, clouds[i].y + 10, 30);
        txCircle          (clouds[i].x - 70, clouds[i].y + 20, 20);
        txCircle          (clouds[i].x - 45, clouds[i].y + 30, 20);
        txCircle          (clouds[i].x - 10, clouds[i].y + 25, 30);
        txCircle          (clouds[i].x + 25, clouds[i].y + 35, 15);
        txCircle          (clouds[i].x + 50, clouds[i].y + 20, 30);
        txCircle          (clouds[i].x + 30, clouds[i].y + 5, 30);
    }

}


void DrawRope   (coord catapult)
{
    txSetColor      (TX_BLACK, 3);

    txLine            (catapult.x, catapult.y, lever1.x, lever1.y);
}


void DrawLever ()
{
    txSetColor      (RGB(191, 112, 46), 13);

    txSetFillColor    (TX_GREY);

    txLine          (lever1.x, lever1.y, lever0.x, lever0.y);

    txSetColor      (TX_BLACK, 1);

}


void DrawBucket (coord bucket)
{
    txPie           (bucket.x - 25, bucket.y - 25, bucket.x + 25, bucket.y + 25, alphaRad * 180 / M_PI, 180);
}


void DrawCatapult ()
{
    DrawRope(catapult);
    DrawStone();
    DrawLever();
    DrawBucket(bucket);

    txSetColor      (RGB(191, 112, 46), 13);

    txSetFillColor  (RGB(191, 112, 46));

    txSetColor      (TX_BLACK, 1);

    txRectangle       (catapult.x, catapult.y, catapult.x + 400, catapult.y + 30);

    txCircle          (catapult.x + 100, catapult.y + 30, 35);

    txRectangle       (catapult.x + 225, catapult.y - 125, catapult.x + 245, catapult.y);

    POINT opora1[4] = {{catapult.x + 135, catapult.y}, {catapult.x + 150, catapult.y}, {catapult.x + 225, catapult.y - 80}, {catapult.x + 225, catapult.y - 95}};
    txPolygon (opora1, 4);

    POINT opora2[4] = {{catapult.x + 350, catapult.y}, {catapult.x + 335, catapult.y}, {catapult.x + 245, catapult.y - 80}, {catapult.x + 245, catapult.y - 95}};
    txPolygon (opora2, 4);

    txCircle          (catapult.x + 350, catapult.y + 30, 35);

    txSetFillColor    (TX_GREY);

    txSetColor        (TX_BLACK, 3);

    txSetColor        (TX_BLACK, 1);

    txSetFillColor    (TX_GREY);

    txCircle          (catapult.x + 100, catapult.y + 30, 10);
    txCircle          (catapult.x + 350, catapult.y + 30, 10);
}


void DrawStone ()
{
    txSetColor      (TX_LIGHTGREY);
    txSetFillColor  (TX_LIGHTGREY);
    txCircle        (stone.x, stone.y, 25);
}


void DrawWallOdd(coord wall)
{
    txSetColor      (TX_BLACK);
    txSetFillColor  (TX_GREY);

    txRectangle     (wall.x, wall.y, wall.x + 40, wall.y + 20);
    txRectangle     (wall.x + 40, wall.y, wall.x + 80, wall.y + 20);
}


void DrawWallEven(coord wall)
{
    txSetColor      (TX_BLACK);
    txSetFillColor  (TX_GREY);

    txRectangle     (wall.x, wall.y, wall.x + 20, wall.y + 20);
    txRectangle     (wall.x + 20, wall.y, wall.x + 60, wall.y + 20);
    txRectangle     (wall.x + 60, wall.y, wall.x + 80, wall.y + 20);

}


void DrawWall (coord wall)
{
    for( int i = 0; i < 7; i++ )
    {
        DrawWallOdd (wall);
        wall.y += 20;
        DrawWallEven (wall);
        wall.y += 20;

    }
    DrawWallOdd (wall);
}

void DrawWarriors()
{
    for (int i = 0; i < 5; i++) {
        DrawWarrior (warrior[i], red);
    }

    DrawWarrior (monteki,    blue);
}

void Legs(coord warrior)
{
    txSetColor      (TX_BLACK, 1);
    txSetFillColor  (RGB (170, 170, 170));
    txRectangle     (warrior.x - 33, warrior.y + 20, warrior.x + 33, warrior.y + 74);
}


void Body(coord warrior, COLORREF color)
{
    txSetFillColor  (color);
    txRectangle     (warrior.x - 43, warrior.y + 10, warrior.x + 43, warrior.y + 64);
}


void Arms(coord warrior)
{
    txSetFillColor  (RGB (170, 170, 170));
    txRectangle     (warrior.x - 55, warrior.y + 10, warrior.x - 43, warrior.y + 49);
    txRectangle     (warrior.x + 43, warrior.y + 10, warrior.x + 55, warrior.y + 49);
}


void Hands (coord warrior, COLORREF color)
{
    txSetFillColor  (color);
    txCircle        (warrior.x - 49, warrior.y + 49, 7);
    txCircle        (warrior.x + 49, warrior.y + 49, 7);
}


void Rivets(coord warrior)
{
    txSetFillColor  (RGB(255, 255, 0));
    for(int i = 0; i < 5; i++)
        {
            for(int i = 0; i < 10; i++)
            {
                txCircle (warrior.x - 41, warrior.y + 14, 2);
                warrior.x += 9;
            }
            warrior.x -= 90;
            warrior.y += 11;
        }
    warrior.y -= 55;
}


void Head (coord warrior)
{
    txSetFillColor  (RGB(241, 207, 170));
    txCircle        (warrior.x, warrior.y, 38);
}


void Eyes (coord warrior)
{
    txSetFillColor  (RGB(255, 255, 255));
    txCircle        (warrior.x - 12, warrior.y - 10, 10);
    txCircle        (warrior.x + 12, warrior.y - 10, 10);

    txSetFillColor  (TX_BLACK);
    txCircle        (warrior.x - 7, warrior.y - 10, 2);
    txCircle        (warrior.x + 7, warrior.y - 10, 2);
}


void Zip (coord warrior)
{
    txSetColor      (TX_BLACK, 1);
    txLine          (warrior.x, warrior.y + 38, warrior.x, warrior.y + 64);
}


void Mouth (coord warrior)
{
    txSetColor      (TX_BLACK, 2);
    txLine          (warrior.x - 7, warrior.y + 15, warrior.x + 7, warrior.y + 15);
}


void Helmet (coord warrior)
{
    txSetColor      (TX_BLACK, 1);
    txSetFillColor  (RGB(170, 170, 170));
    txPie           (warrior.x - 33, warrior.y - 48, warrior.x + 33, warrior.y + 5, 0, 180);

    txRectangle     (warrior.x - 3, warrior.y - 22, warrior.x + 3, warrior.y);
}


void Belt(coord warrior)
{
    txSetFillColor  (RGB(128, 64, 0));
    txRectangle     (warrior.x - 43, warrior.y + 49, warrior.x + 43, warrior.y + 57);
}


void DrawWarrior (coord warrior, COLORREF color)
{
    Legs    (warrior);
    Body    (warrior, color);
    Arms    (warrior);
    Hands   (warrior, color);
    Rivets  (warrior);
    Head    (warrior);
    Eyes    (warrior);
    Zip     (warrior);
    Mouth   (warrior);
    Helmet  (warrior);
    Belt    (warrior);
}

void CalculateCatapult()
{
    const int speed = 3;
    if (catapult.x <= 40) {
        catapult.x += speed;
        lever0.x += speed;
        lever1.x += speed;
        bucket.x += speed;
        monteki.x += speed;
        stone.x += speed;
    }
}

void CalculateLever()
{
    static double t = 0;
    const double e = 0.0045;
    alphaRad = alphaDeg * M_PI / 180;
    lever1.x = lever0.x + 182 * cos(alphaRad);
    lever1.y = lever0.y - 182 * sin(alphaRad);

    bucket.x = lever0.x + 162 * cos(alphaRad);
    bucket.y = lever0.y - 162 * sin(alphaRad);
    if( !isStoneMoving ) {
        stone.x = bucket.x;
        stone.y = bucket.y;
    }

    if (isLeverMoving && alphaDeg >= finalAngle) {
        alphaDeg = 160 - e * t * t / 2;
        t += 3;
    }
    if ( isLeverMoving && alphaDeg < finalAngle && !isStoneMoving ) {
        isStoneMoving = true;
        double stoneSpeed =  e * t * 182;
        stoneSpeedX = stoneSpeed * cos( alphaRad - M_PI/2 );
        stoneSpeedY = stoneSpeed * sin( alphaRad - M_PI/2 );
        isLeverMoving = false;
        t = 0;
    }
}

void CalculateStone()
{
    if (isStoneMoving && stone.y <= 675) {
        const double deltaT = 0.1;
        stone.x += xDirection * stoneSpeedX * deltaT;
        stone.y += -stoneSpeedY * deltaT + (9.81 * deltaT * deltaT) / 2;
        stoneSpeedY -= 9.81 * deltaT;

        for (int i = 0; i < 5; i++) {

            if ((stone.x >= warrior[i].x - 55 - 25) && (stone.x <= warrior[i].x + 55 + 25) && (stone.y >= warrior[i].y - 38 - 25) && (stone.y <= warrior[i].y + 74 + 25)) {

                warrior[i].y = 900;
            }
        }

        if (((stone.x >= wall.x - 25) && (stone.x <= wall.x) && (stone.y >= wall.y) && (stone.y <= 650)) || (stone.x >= 1500)) {

            xDirection = -1;
        }

        if ((stone.x >= wall.x) && (stone.x <= wall.x + 80) && (stone.y >= wall.y - 25)) {
           stoneSpeedY = -stoneSpeedY;
        }
    }
}

void DrawFinalAngleValue()
{
    char buffer[20];
    int angleToDisplay = finalAngle - 90;
    sprintf( buffer, "���� ��������: %d", angleToDisplay );
    txSetColor(TX_BLACK, 3);
    txSelectFont ("Verdana", 40);
    txTextOut (50, 750, buffer);

}

LRESULT CALLBACK MyWndProc (HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    const int minAngle = 120;
    const int maxAngle = 160;
    if( message == WM_KEYUP ) {
        if( wParam == VK_UP && finalAngle < maxAngle ) {
            finalAngle++;
        }
        if( wParam == VK_DOWN && finalAngle > minAngle ) {
            finalAngle--;
        }
        if( wParam == VK_SPACE ) {
            isLeverMoving = true;
        }
        if( wParam == VK_RETURN ) {
            isLeverMoving = false;
            isStoneMoving = false;
            alphaDeg = 160;
            stoneSpeedX = 0;
            stoneSpeedY = 0;
            stone.x = bucket.x;
            stone.y = bucket.y;
            xDirection = 1;
        }
        return true;
    }
    if( message == WM_CLOSE ) {
        needContinue = false;
        return true;
    }
    return false;
}