#include "TXLib.h"
#include "math.h"
#include "stdio.h"

struct coord
{
    int x;
    int y;
};

//double alphaRad = 153 * M_PI / 180;

double alphaDeg = 160;

double alphaRad = alphaDeg * M_PI / 180;

void DrawLandscape ();

void DrawRope   (coord catapult, coord lever1);

void DrawCatapult (coord catapult);

void DrawBucket (coord bucket);

void DrawLever  (coord lever1, coord lever0, int);

void DrawStone     (coord stone);

void DrawWall     (coord wall);

void DrawWarrior   (coord warrior, COLORREF color);

void DrawSun    ();

void DrawRays     (coord rays);

void DrawClouds    (coord clouds);

void WorkCatapult   ();

int main ()
{
    txCreateWindow (1500, 800);

    coord lever0     = {-198, 650};

    coord lever1     = {-368, 586};

    coord bucket     =  {-353, 598};

    coord catapult   = {-400, 635};

    coord wall   = {710, 400};

    coord rays   = {210, 5};

    coord stone  = {-353, 598};

    coord warrior[] = {{870, 627}, {985, 627}, {1100, 627}, {1215, 627}, {1330, 627}};

    coord clouds[] = {{750, 45},  {1050, 95}, {450, 125},  {1350, 125}};

    coord monteki   = {-200, 627};

    COLORREF red  = RGB (204, 29, 64);

    COLORREF blue = RGB (0, 99, 198);

    DrawLandscape ();

    DrawSun    ();

    DrawRays    (rays);

    DrawClouds (clouds[0]);
    DrawClouds (clouds[1]);
    DrawClouds (clouds[2]);
    DrawClouds (clouds[3]);


    int t = 0;

    while (t < 150)
    {


        txClear();

        DrawLandscape ();
        DrawSun    ();

        DrawRays    (rays);

        DrawClouds (clouds[0]);
        DrawClouds (clouds[1]);
        DrawClouds (clouds[2]);
        DrawClouds (clouds[3]);

        catapult.x += 3 ;
        lever0.x += 3;
        lever1.x += 3;
        bucket.x += 3;
        monteki.x += 3;
        stone.x += 3;

        DrawRope(catapult, lever1);

        DrawStone(stone);

        DrawLever(lever1, lever0, alphaDeg);

        DrawBucket(bucket);

        DrawCatapult(catapult);

        DrawWall(wall);

        DrawWarrior (warrior[0], red);
        DrawWarrior (warrior[1], red);
        DrawWarrior (warrior[2], red);
        DrawWarrior (warrior[3], red);
        DrawWarrior (warrior[4], red);

        DrawWarrior (monteki,    blue);

        txSleep(10);
        t += 1;
    }


    double ti = 0;
    double e = 0.003;

    while (alphaDeg >= 135)
    //while (ti <= 40)
    {

        txClear();

        DrawLandscape ();
        DrawSun    ();

        DrawRays    (rays);

        DrawClouds (clouds[0]);
        DrawClouds (clouds[1]);
        DrawClouds (clouds[2]);
        DrawClouds (clouds[3]);

        lever1.x = lever0.x + 182 * cos(alphaRad);
        lever1.y = lever0.y - 182 * sin(alphaRad);

        bucket.x = lever0.x + 162 * cos(alphaRad);
        bucket.y = lever0.y - 162 * sin(alphaRad);

        stone.x = lever0.x + 162 * cos(alphaRad);
        stone.y = lever0.y - 162 * sin(alphaRad);

        alphaDeg = 160 - e * ti * ti / 2;
        alphaRad = alphaDeg * M_PI / 180;

        DrawRope(catapult, lever1);

        DrawStone(stone);

        DrawLever(lever1, lever0, alphaRad);

        DrawBucket(bucket);

        DrawCatapult(catapult);

        DrawWall(wall);

        DrawWarrior (warrior[0], red);
        DrawWarrior (warrior[1], red);
        DrawWarrior (warrior[2], red);
        DrawWarrior (warrior[3], red);
        DrawWarrior (warrior[4], red);

        DrawWarrior (monteki,    blue);

        txSleep(1);
        ti += 10;


    }

    //int v = 0.3 * 3.7 * 182;
    //int v = 0.03 * 40 * 182;
    int v = e * ti * 182;


    double time = 0;

    int stone0x = stone.x;
    int stone0y = stone.y;

    while (time < 50)
    {
        txClear();

        DrawLandscape ();
        DrawSun    ();

        DrawRays    (rays);

        DrawClouds (clouds[0]);
        DrawClouds (clouds[1]);
        DrawClouds (clouds[2]);
        DrawClouds (clouds[3]);

        DrawRope(catapult, lever1);

        DrawLever(lever1, lever0, alphaDeg);

        DrawBucket(bucket);

        DrawCatapult(catapult);

        DrawWall(wall);

        DrawWarrior (warrior[0], red);
        DrawWarrior (warrior[1], red);
        DrawWarrior (warrior[2], red);
        DrawWarrior (warrior[3], red);
        DrawWarrior (warrior[4], red);

        DrawWarrior (monteki,    blue);


        stone.x = stone0x + v * time * cos(alphaRad - M_PI/2);
        stone.y = stone0y - v * time * sin(alphaRad - M_PI/2) + (9.81 * time * time) / 2;


        DrawStone(stone);

        if (stone.y >= 675) {
            break;
        }

        txSleep(10);
        time += 1;

    }

    return 0;
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


void DrawRays (coord rays)
{
    txSetColor      (TX_YELLOW, 8);

    txLine          (rays.x, rays.y, rays.x + 100, rays.y);

    txLine          (rays.x - 10, rays.y + 75, rays.x + 90, rays.y + 120);

    txLine          (rays.x - 60, rays.y + 145, rays.x + 30, rays.y + 235);

    txLine          (rays.x - 130, rays.y + 195, rays.x - 85, rays.y + 295);

    txLine          (rays.x - 205, rays.y + 205, rays.x - 205, rays.y + 305);
}


void DrawClouds (coord clouds)
{
    txSetColor        (TX_WHITE);
    txSetFillColor    (TX_WHITE);

    txCircle          (clouds.x, clouds.y, 40);
    txCircle          (clouds.x - 40, clouds.y + 10, 30);
    txCircle          (clouds.x - 70, clouds.y + 20, 20);
    txCircle          (clouds.x - 45, clouds.y + 30, 20);
    txCircle          (clouds.x - 10, clouds.y + 25, 30);
    txCircle          (clouds.x + 25, clouds.y + 35, 15);
    txCircle          (clouds.x + 50, clouds.y + 20, 30);
    txCircle          (clouds.x + 30, clouds.y + 5, 30);

}


void DrawRope   (coord catapult, coord lever1)
{
    txSetColor      (TX_BLACK, 3);

    txLine            (catapult.x, catapult.y, lever1.x, lever1.y);
}


void DrawLever (coord lever1, coord lever0, int)
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


void DrawCatapult (coord catapult)
{
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


void DrawStone (coord stone)
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
