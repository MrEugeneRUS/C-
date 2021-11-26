#include "TXLib.h"

struct coord
{
    int x;
    int y;
};

void Landscape();

void Katapulta(coord k);

void Kamen();

void Stena(coord s);

void Kapuletti(coord p);

void Monteki(coord m);

void Solnce();

void Luchi(coord l);

void Oblaka(coord o);


int main()
{
    txCreateWindow(1900, 800);

    coord k = {200, 635};

    coord s = {910, 400};

    coord l = {210, 5};

    coord p[] ={{1270, 627}, {1385, 627}, {1500, 627}, {1615, 627}, {1730, 627}};

    coord o[] = {{950, 45}, {1350, 95}, {650, 125}, {1650, 125}};

    coord m = {400, 627};

    Landscape();

    Solnce();

    Luchi(l);

    Oblaka(o[0]);
    Oblaka(o[1]);
    Oblaka(o[2]);
    Oblaka(o[3]);

    Kamen();

    Katapulta(k);

    Stena(s);

    Kapuletti(p[0]);
    Kapuletti(p[1]);
    Kapuletti(p[2]);
    Kapuletti(p[3]);
    Kapuletti(p[4]);

    Monteki(m);

    return 0;
}

void Landscape()
{
    txSetColor      (RGB(153, 217, 234));
    txSetFillColor  (RGB(153, 217, 234));

    txRectangle     (0, 0, 1900, 700);

    txSetFillColor  (RGB(34, 177, 76));
    txRectangle     (0, 700, 1900, 800);

}

void Solnce()
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

void Luchi(coord l)
{
    txSetColor      (TX_YELLOW, 8);

    txLine          (l.x, l.y, l.x + 100, l.y);

    txLine          (l.x - 10, l.y + 75, l.x + 90, l.y + 120);

    txLine          (l.x - 60, l.y + 145, l.x + 30, l.y + 235);

    txLine          (l.x - 130, l.y + 195, l.x - 85, l.y + 295);

    txLine          (l.x - 205, l.y + 205, l.x - 205, l.y + 305);
}

void Oblaka(coord o)
{
    txSetColor        (TX_WHITE);
    txSetFillColor    (TX_WHITE);

    txCircle          (o.x, o.y, 40);
    txCircle          (o.x - 40, o.y + 10, 30);
    txCircle          (o.x - 70, o.y + 20, 20);
    txCircle          (o.x - 45, o.y + 30, 20);
    txCircle          (o.x - 10, o.y + 25, 30);
    txCircle          (o.x + 25, o.y + 35, 15);
    txCircle          (o.x + 50, o.y + 20, 30);
    txCircle          (o.x + 30, o.y + 5, 30);

}

void Katapulta(coord k)
{
    txSetColor      (TX_BLACK, 1);

    txSetFillColor  (RGB(191, 112, 46));

    POINT richag[4] = {{k.x + 33, k.y - 62}, {k.x + 202, k.y + 15}, {k.x + 207, k.y + 5}, {k.x + 38, k.y - 72}};
    txPolygon       (richag, 4);

    txRectangle     (k.x, k.y, k.x + 400, k.y + 30);

    txCircle        (k.x + 100, k.y + 30, 35);

    txRectangle     (k.x + 225, k.y - 125, k.x + 245, k.y);

    POINT opora1[4] = {{k.x + 135, k.y}, {k.x + 150, k.y}, {k.x + 225, k.y - 80}, {k.x + 225, k.y - 95}};
    txPolygon       (opora1, 4);

    POINT opora2[4] = {{k.x + 350, k.y}, {k.x + 335, k.y}, {k.x + 245, k.y - 80}, {k.x + 245, k.y - 95}};
    txPolygon       (opora2, 4);

    txCircle        (k.x + 350, k.y + 30, 35);

    txSetFillColor  (TX_GREY);

    txPie           (k.x + 30, k.y - 77, k.x + 80, k.y - 27, 155, 180);

    txSetColor      (TX_BLACK, 3);

    txLine          (k.x + 90, k.y - 50, k.x + 225, k.y - 105);

    txSetColor      (TX_BLACK, 1);

    txSetFillColor  (TX_GREY);

    txCircle        (k.x + 100, k.y + 30, 10);
    txCircle        (k.x + 350, k.y + 30, 10);
}

void Kamen()
{
    txSetColor      (TX_LIGHTGREY);
    txSetFillColor  (TX_LIGHTGREY);
    txCircle        (255, 583, 25);
}

void StenaOdd(coord s)
{
    txSetColor      (TX_BLACK);
    txSetFillColor  (TX_GREY);

    txRectangle     (s.x, s.y, s.x + 40, s.y + 20);
    txRectangle     (s.x + 40, s.y, s.x + 80, s.y + 20);
}

void StenaEven(coord s)
{
    txSetColor      (TX_BLACK);
    txSetFillColor  (TX_GREY);

    txRectangle     (s.x, s.y, s.x + 20, s.y + 20);
    txRectangle     (s.x + 20, s.y, s.x + 60, s.y + 20);
    txRectangle     (s.x + 60, s.y, s.x + 80, s.y + 20);

}

void Stena(coord s)
{
    for( int i = 0; i < 7; i++ )
    {
        StenaOdd(s);
        s.y += 20;
        StenaEven(s);
        s.y += 20;

    }
    StenaOdd(s);
}

void Kapuletti(coord p)
{
    txSetColor      (TX_BLACK, 1);

    txSetFillColor  (RGB(170, 170, 170));
    txRectangle     (p.x - 33, p.y + 20, p.x + 33, p.y + 74);

    txSetFillColor  (RGB(204, 29, 64));
    txRectangle     (p.x - 43, p.y + 10, p.x + 43, p.y + 64);

    txSetFillColor  (RGB(170, 170, 170));
    txRectangle     (p.x - 55, p.y + 10, p.x - 43, p.y + 49);
    txRectangle     (p.x + 43, p.y + 10, p.x + 55, p.y + 49);

    txSetFillColor  (RGB(204, 29, 64));
    txCircle        (p.x - 49, p.y + 49, 7);
    txCircle        (p.x + 49, p.y + 49, 7);

    txSetFillColor  (RGB(255, 255, 0));
    for(int i = 0; i < 5; i++)
        {
            for(int i = 0; i < 10; i++)
            {
                txCircle(p.x - 41, p.y + 14, 2);
                p.x += 9;
            }
            p.x -= 90;
            p.y += 11;
        }
    p.y -= 55;

    txSetFillColor  (RGB(241, 207, 170));
    txCircle        (p.x, p.y, 38);

    txSetFillColor  (RGB(255, 255, 255));
    txCircle        (p.x - 12, p.y - 10, 10);
    txCircle        (p.x + 12, p.y - 10, 10);

    txSetFillColor  (TX_BLACK);
    txCircle        (p.x - 7, p.y - 10, 2);
    txCircle        (p.x + 7, p.y - 10, 2);

    txSetColor      (TX_BLACK, 1);
    txLine          (p.x, p.y + 38, p.x, p.y + 64);

    txSetColor      (TX_BLACK, 2);
    txLine          (p.x - 7, p.y + 15, p.x + 7, p.y + 15);

    txSetColor      (TX_BLACK, 1);
    txSetFillColor  (RGB(170, 170, 170));
    txPie           (p.x - 33, p.y - 48, p.x + 33, p.y + 5, 0, 180);

    txRectangle     (p.x - 3, p.y - 22, p.x + 3, p.y);

    txSetFillColor  (RGB(128, 64, 0));
    txRectangle     (p.x - 43, p.y + 49, p.x + 43, p.y + 57);
}

void Monteki(coord m)
{

    txSetColor      (TX_BLACK, 1);

    txSetFillColor  (RGB(170, 170, 170));
    txRectangle     (m.x - 33, m.y + 20, m.x + 33, m.y + 74);

    txSetFillColor  (RGB(0, 99, 198));
    txRectangle     (m.x - 43, m.y + 10, m.x + 43, m.y + 64);

    txSetFillColor  (RGB(170, 170, 170));
    txRectangle     (m.x - 55, m.y + 10, m.x - 43, m.y + 49);
    txRectangle     (m.x + 43, m.y + 10, m.x + 55, m.y + 49);

    txSetFillColor  (RGB(0, 99, 198));
    txCircle        (m.x - 49, m.y + 49, 7);
    txCircle        (m.x + 49, m.y + 49, 7);

    txSetFillColor  (RGB(255, 255, 0));
    for(int i = 0; i < 5; i++)
        {
            for(int i = 0; i < 10; i++)
            {
                txCircle(m.x - 41, m.y + 14, 2);
                m.x += 9;
            }
            m.x -= 90;
            m.y += 11;
        }
    m.y -= 55;

    txSetFillColor  (RGB(241, 207, 170));
    txCircle        (m.x, m.y, 38);

    txSetFillColor  (RGB(255, 255, 255));
    txCircle        (m.x - 12, m.y - 10, 10);
    txCircle        (m.x + 12, m.y - 10, 10);

    txSetFillColor  (TX_BLACK);
    txCircle        (m.x - 7, m.y - 10, 2);
    txCircle        (m.x + 7, m.y - 10, 2);

    txSetColor      (TX_BLACK, 1);
    txLine          (m.x, m.y + 38, m.x, m.y + 64);

    txSetColor      (TX_BLACK, 2);
    txLine          (m.x - 7, m.y + 15, m.x + 7, m.y + 15);

    txSetColor      (TX_BLACK, 1);
    txSetFillColor  (RGB(170, 170, 170));
    txPie           (m.x - 33, m.y - 48, m.x + 33, m.y + 5, 0, 180);

    txRectangle     (m.x - 3, m.y - 22, m.x + 3, m.y);

    txSetFillColor  (RGB(128, 64, 0));
    txRectangle     (m.x - 43, m.y + 49, m.x + 43, m.y + 57);
}
