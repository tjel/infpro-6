#include "avatar.h"

avatar::avatar()
{
    QImage image(100, 100, QImage::Format_RGB32);
    QRgb value;
    int x=0;
    int y=0;
    int pom;
    value = qRgb(qrand()%255, qrand()%255, qrand()%255);
    for (int a=0;a<25;a++)
    {
        pom=x;
        if (y%20==0)
         for (int b=0;b<200;b++)
        {
            if (b%20==0) {y+=1;x=pom;}
                    else {image.setPixel(x, y, value);x+=1;}

        }
    }
    //image.setPixel(2, 1, value);
    //image.setPixel(0, 1, value);
    //image.setPixel(1, 0, value);
    //image.setPixel(1, 1, value);
   /* QFile file( "plik.txt" );
        file.open( QIODevice::WriteOnly | QIODevice::Text );
        QTextStream out( & file );
        out << image.setPixel(2, 1, value);
        file.close();*/
}

