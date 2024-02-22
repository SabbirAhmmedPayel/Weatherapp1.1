#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iGraphics.h"
#include <iostream>
#include <windows.h>
#include <time.h>
#include <mmsystem.h>
#include <random>
#pragma comment(lib, "Winmm.lib")

int len = 0;
int page;
int mode = 0;
int musicon = 1;
int ismps = 0;   // 0 means meter per second
int isfaren = 0; // 0 means celcius

char name[100], tempstr[100];
using namespace std;
#define screenWidth 700
#define screenHeight 315
#define MAX_CITIES 1000

char sky[5][30] = {"sky\\sunny.bmp", "sky\\cloudy.bmp", "sky\\rainy.bmp", "sky\\partlycloudy.bmp", "sky\\thunder.bmp"};

struct Weather
{
    float temperature;
    float humidity;
    float wind;
    float precipitation;
    int sky_index;
};

struct City
{
    char name[20];
    struct Weather weather_data;
};

struct City cities[MAX_CITIES];
int num_cities = 0;

void readWeatherDataFromFile()
{
    const char *filename = "makad.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read data from the file
    while (fscanf(file, "%s %f %f %f %f %d", cities[num_cities].name,
                  &cities[num_cities].weather_data.temperature,
                  &cities[num_cities].weather_data.humidity,
                  &cities[num_cities].weather_data.wind,
                  &cities[num_cities].weather_data.precipitation,
                  &cities[num_cities].weather_data.sky_index) == 6)
    {
        num_cities++;
        if (num_cities >= MAX_CITIES)
        {
            printf("Maximum number of cities reached. Increase MAX_CITIES if needed.\n");
            break;
        }
    }

    fclose(file);
}

struct Weather getWeather(const char *city_name)
{
    for (int i = 0; i < num_cities; ++i)
    {
        if (strcasecmp(city_name, cities[i].name) == 0)
        {
            return cities[i].weather_data;
        }
    }
    struct Weather default_weather = {0.0, 0.0, 0.0, 0.0, 0.0};
    return default_weather;
}

struct Weather city_weather;
// int skyo= city_weather.sky_index;

float convertTemperature(int isFahren, float temperature)
{
    if (isFahren == 1)
    {
        // Convert Celsius to Fahrenheit
        return temperature * 9 / 5 + 32;
    }
    else
    {
        // Return the temperature as is
        return temperature;
    }
}
float convertSpeed(int isMetersPerSecond, float speed)
{
    if (isMetersPerSecond == 1)
    {
        // Convert km/h to m/s
        return speed * 5 / 18;
    }
    else
    {
        // Return the speed as is (in km/h)
        return speed;
    }
}

void drawWeatherInfo(char *city_name)
{
    city_weather = getWeather(city_name);

    if (city_weather.temperature == 0.0)
    {
        page = 1;
        iText(100, 400, "City not found", GLUT_BITMAP_TIMES_ROMAN_24);
    }
    else
    {
        int x = 382;
        char info[100];
        // sprintf(info, "%s", city_name);
        // iText(x, 400, info, GLUT_BITMAP_TIMES_ROMAN_24);

        float tempa = convertTemperature(isfaren, city_weather.temperature);

        // sprintf(info, "%.1f °C", city_weather.temperature);
        sprintf(info, "%.1f °C", tempa);

        if (isfaren)
        {
            info[strlen(info) - 1] = 'F';
        }
        if (!isfaren)
        {
            info[strlen(info) - 1] = 'C';
        }

        iText(x, 417, info, GLUT_BITMAP_TIMES_ROMAN_24);

        sprintf(info, " %.1f%%", city_weather.humidity);
        iText(x, 362, info, GLUT_BITMAP_TIMES_ROMAN_24);

        sprintf(info, " %.1f mm", city_weather.precipitation);
        iText(x, 320, info, GLUT_BITMAP_TIMES_ROMAN_24);

        float teampa2 = convertSpeed(ismps, city_weather.wind);

        if (!ismps )
        {
            sprintf(info, "%.1f km/h", teampa2);
        }
        if (ismps )
        {
            sprintf(info, "%.1f m/s", teampa2);
        }

        iText(x, 286, info, GLUT_BITMAP_TIMES_ROMAN_24);

        // sprintf(info, "Atmospheric Pressure: %.1f mmHg", city_weather.sky_index);
        // iText(x, 150, info, GLUT_BITMAP_TIMES_ROMAN_24);
    }
}

int xa = 135;
int ya = 275;

float r1[6] = {1, 0, 3.4, 2, 2, 5};
float r2[6] = {0, 1, 2.3, 3, 3, 4};
float r3[6] = {2.2, 3, 4, 0, 1, 3.1};
float r4[6] = {3, 2, 0.7, 1, 0, 4};

float r5[6] = {0, 1, 2.3, 3, 3, 4};

float r6[6] = {2.2, 3, 4, 0, 1, 3.1};

float r7[6] = {3, 2, 0.7, 1, 0, 4};

float r8[6] = {0, 1, 2.3, 3, 3, 4};

float r9[6] = {2.2, 3, 4, 0, 1, 3.1};

float r10[6] = {3, 2, 0.7, 1, 0, 4};

// float r5[6] ={3.8,4.2,0,2,3,1} ;

float ar[6];

void drawgraph()
{

    float temp = city_weather.temperature;
    if (temp < 28)
    {
        memcpy(ar, r1, sizeof(ar));
    }
    else if (temp >= 28 && temp <=28.5)
    {
        memcpy(ar, r2, sizeof(ar));
    }
    else if (temp >28.5 && temp <= 29)
    {
        memcpy(ar, r3, sizeof(ar));
    }

    else if (temp > 29 && temp <= 29.5 )
    {
        memcpy(ar, r4, sizeof(ar));
    }
    else if (temp > 29.5 && temp <= 30){
        memcpy(ar, r5, sizeof(ar));
    }

    else if (temp > 30 && temp <= 30.5)
    {
        memcpy(ar, r6, sizeof(ar));
    }
    else if (temp > 30.5 && temp <= 31)
    {
        memcpy(ar, r7, sizeof(ar));
    }

    else if (temp > 31 )

    {
        memcpy(ar, r8, sizeof(ar));
    }



    iSetColor(255, 100, 0);

    iLine(xa + 0, ya + 0, 171, ya + 4 * temp);
    iLine(171, ya + 4 * temp, 247, ya + 4 * (temp - ar[0]));
    iLine(247, ya + 4 * (temp - ar[0]), 330, ya + 4 * (temp + ar[1]));
    iLine(330, ya + 4 * (temp + ar[1]), 406, ya + 4 * (temp - ar[2]));
    iLine(406, ya + 4 * (temp - ar[2]), 487, ya + 4 * (temp + ar[3]));
    iLine(487, ya + 4 * (temp + ar[3]), 577, ya + 4 * (temp - ar[4]));
    iLine(577, ya + 4 * (temp - ar[4]), 643, ya + 4 * (temp + ar[5]));
    iLine(643, ya + 4 * (temp + ar[5]), 745, ya + 4 * (temp - ar[6]));

    int yaz = 66;
    char nexttemp[20];
    // x = 111 , 249 , 380 , 503 , 630 , 765
    iSetColor(0, 100, 150);
    sprintf(nexttemp, "%.1f°C", temp - ar[0]);
    iText(111, yaz, nexttemp, GLUT_BITMAP_TIMES_ROMAN_24);
    sprintf(nexttemp, "%.1f°C", temp + ar[1]);
    iText(249, yaz, nexttemp, GLUT_BITMAP_TIMES_ROMAN_24);
    sprintf(nexttemp, "%.1f°C", temp - ar[2]);
    iText(380, yaz, nexttemp, GLUT_BITMAP_TIMES_ROMAN_24);
    sprintf(nexttemp, "%.1f°C", temp + ar[3]);
    iText(503, yaz, nexttemp, GLUT_BITMAP_TIMES_ROMAN_24);
    sprintf(nexttemp, "%.1f°C", temp - ar[4]);
    iText(630, yaz, nexttemp, GLUT_BITMAP_TIMES_ROMAN_24);
    sprintf(nexttemp, "%.1f°C", temp + ar[5]);
    iText(765, yaz, nexttemp, GLUT_BITMAP_TIMES_ROMAN_24);

    int yu = 20;
    // x = 108 , 251 , 380 , 490 , 625 760
    iSetColor(0, 0, 0);

    iText(108, yu, "Day 1", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(248, yu, "Day 2", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(380, yu, "Day 3", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(495, yu, "Day 4", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(625, yu, "Day 5", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(760, yu, "Day 6", GLUT_BITMAP_TIMES_ROMAN_24);

    iSetColor(153, 1, 75);

    int yy = 251;

    iText(149, yy, "Today", GLUT_BITMAP_HELVETICA_12);
    iText(227, yy, "Day 1", GLUT_BITMAP_HELVETICA_12);
    iText(307, yy, "Day 2", GLUT_BITMAP_HELVETICA_12);
    iText(387, yy, "Day 3", GLUT_BITMAP_HELVETICA_12);
    iText(467, yy, "Day 4", GLUT_BITMAP_HELVETICA_12);
    iText(556, yy, "Day 5", GLUT_BITMAP_HELVETICA_12);
    iText(646, yy, "Day 5", GLUT_BITMAP_HELVETICA_12);
    iText(736, yy, "Day 6", GLUT_BITMAP_HELVETICA_12);

    int uu = city_weather.sky_index;
    int yop = 124;
    int high1 = (uu + 1) % 5;

    int high2 = (uu + 2) % 5;

    int high3 = (uu + 3) % 5;

    int high4 = (uu + 1) % 5;
    //     cout << " current index is " << uu << endl;
    // cout << high1 << " " << high2 << " " << high3 << " " << high4 << endl;

    iShowBMP2(105, yop, sky[uu % 6], 0);
    iShowBMP2(240, yop, sky[uu % 6], 0);
    iShowBMP2(375, yop, sky[high1], 0);
    iShowBMP2(500, yop, sky[high2], 0);
    iShowBMP2(635, yop, sky[high3], 0);
    iShowBMP2(760, yop, sky[high4], 0);
}

void drawskyemoji()
{
    if (city_weather.sky_index == 0)
    {
        iShowBMP2(740, 317, sky[0], 0);
        iText(750, 296, "Clear Sky", GLUT_BITMAP_TIMES_ROMAN_24);
    }
    if (city_weather.sky_index == 1)
    {
        iShowBMP2(740, 317, sky[1], 0);
        iText(750, 296, "Cloudy", GLUT_BITMAP_TIMES_ROMAN_24);
    }
    if (city_weather.sky_index == 2)
    {
        iShowBMP2(740, 317, sky[2], 0);
        iText(750, 296, "Rainy", GLUT_BITMAP_TIMES_ROMAN_24);
    }
    if (city_weather.sky_index == 3)
    {
        iShowBMP2(740, 317, sky[3], 0);
        iText(742, 294, "Partly cloudy", GLUT_BITMAP_TIMES_ROMAN_24);
    }
    if (city_weather.sky_index == 4)
    {
        iShowBMP2(740, 317, sky[4], 0);
        iText(718, 289, "ThunderStorm", GLUT_BITMAP_TIMES_ROMAN_24);
    }
}

void drawhompage()
{
    iSetColor(128, 128, 128);
    iFilledRectangle(0, 0, 1050, 545);
    iShowBMP(0, 0, "page\\1.bmp");
}

void drawtoday()
{
    iSetColor(128, 128, 128);
    iFilledRectangle(0, 0, 1050, 545);
    iShowBMP(0, 0, "page\\today.bmp");

    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    int day_of_week = timeinfo->tm_wday;
    char *days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    strftime(buffer, sizeof(buffer), "%d-%m-%Y,                                              %I:%M %p", timeinfo);
    iSetColor(0, 0, 0);

    iText(162, 490, buffer, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(288, 490, days[day_of_week], GLUT_BITMAP_TIMES_ROMAN_24);
    name[0] = toupper(name[0]);
    iText(770, 484, name, GLUT_BITMAP_TIMES_ROMAN_24);

    drawWeatherInfo(name);
    drawskyemoji();
}

drawcheckweather()
{
    // iSetColor(128,128,128);
    iFilledRectangle(0, 0, 1050, 545);
    iShowBMP(0, 0, "page\\checkweather.bmp");
}
void drawcredits()
{
    iSetColor(128, 128, 128);
    iFilledRectangle(0, 0, 1050, 545);
    iShowBMP(0, 0, "page\\credits.bmp");
}
void drawupcoming()
{
    iSetColor(128, 128, 128);
    iFilledRectangle(0, 0, 1050, 545);
    iShowBMP(0, 0, "page\\upcoming3.bmp");
}

drawsettings()
{
    iSetColor(128, 128, 128);
    iFilledRectangle(0, 0, 1050, 545);
    iShowBMP(0, 0, "page\\settings.bmp");
}
int state = 0;
;
int index;

void refreshWeather()
{
    page = 2;
    mode = 0;
    strcpy(name, tempstr);
    // printf("%s\n", name);
    for (int i = 0; i < index; i++)
        tempstr[i] = 0;
    index = 0;
    state = 0;
    // deteting all elements of an array
    
    for (int i = 0; i < 6; i++)
    {
        ar[i] = 0;
    }
}

void iKeyboard(unsigned char key)
{

    if (mode == 1)
    {
        if (key == '\r')
        {
            state = 1;
            PlaySound("sound//button.wav", NULL, SND_ASYNC);
        }

        if (state == 1)
        {
            refreshWeather();
        }
        else if (key == '\b')
        {
            if (index > 0)
            {
                index--;
                tempstr[index] = 0;
                PlaySound("sound//brkey.wav", NULL, SND_ASYNC);
            }
        }
        else
        {
            // name[index]=key;
            tempstr[index] = key;

            index++;
            PlaySound("sound//brkey.wav", NULL, SND_ASYNC);
            //  strcpy(name, str);
        }
    }
}

void iDraw()
{
    iClear();
    if (page == 0)
        drawhompage();
    if (page == 1)
    {
        if (city_weather.temperature == 0.0)
        {
            iText(100, 400, "City not found", GLUT_BITMAP_TIMES_ROMAN_24);
        }
        drawcheckweather();
        if (mode == 1)

        {
            iSetColor(0, 0, 05);
            iText(36, 315, tempstr, GLUT_BITMAP_TIMES_ROMAN_24);
        }
    }

    if (page == 2)
    {
        drawtoday();
    }
    if (page == 3)
    {
        drawupcoming();
        drawgraph();
    }

    if (page == 7)
    {
        drawcredits();
    }
    if(page == 9){
        drawsettings();
    }
}

void iSpecialKeyboard(unsigned char key)
{
}
// x = 177 625 y= 390 450
void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        PlaySound("sound//button.wav", NULL, SND_ASYNC);
        if (page == 0)
        {
            if (mx >= 0 && mx <= 350)
            {
                if (my >= 245 && my <= 340){
                        page = 1;
                }
                  //  
            }

            if (mx >= 9 && mx <= 187)
            {
                if (my >= 13 && my <= 79)
                {
                  exit(0);
                }
                else if (my >= 83 && my <= 152)
                {
                   page = 7;
                } // 7 - credits
                else if (my >= 156 && my <= 225)
                {
                    page = 9 ; //9 - settings  
                }
            }
        }

        if (page == 7) //
        {
            if (mx >= 0 && mx <= 120 && my >= 450 && my <= 540)
                page = 0;
        }
        if(page == 9){

             if (mx >= 0 && mx <= 120 && my >= 450 && my <= 540)
                page = 0;

                if(mx > 422 && mx <= 586){
                    if(my > 423 && my <= 475){
                        isfaren =  0 ; 

                    }
                    if(my > 315 && my <= 368){
                                ismps =  0 ;}
                }
                if(mx > 607 && mx <= 766){
                    if(my > 423 && my <= 475){
                        isfaren =  1 ; 

                    }
                    if(my > 315 && my <= 368){
                                ismps =  1 ;}
                }



        }

        if (page == 1) // checkweather mode (input)
        {
            if (mx >= 34 && mx <= 518 && my >= 290 && my <= 340)
            {
                mode = 1;
            }

            if (mx >= 525 && mx <= 610 && my >= 288 && my <= 350)
            {
                page = 2;
                state = 1;
                refreshWeather();
            }
        }

        if (mx >= 0 && mx <= 120 && my >= 450 && my <= 540 && page != 0 && page > -1)
            page = page - 1;

        // x = 874 x = 1033 y =65 111

        if (page == 2) // todays mode
        {
            if (mx >= 874 && mx <= 1033 && my >= 65 && my <= 111 && page == 2)
                page = 0;

            if (mx >= 875 && mx <= 1023 && my >= 123 && my <= 174)
            {
                page = 3;
            }

            // x = 887, y= 368 ,x = 966, y= 425
            // x = 970, y= 365,x = 1047, y= 424

            if (mx >= 887 && mx <= 966)
            {
                if (my >= 368 && my <= 425)
                {
                    isfaren = 0;
                }
                else if (my >= 300 && my <= 362)
                {
                    ismps = 0;
                }
            }
            if (mx >= 970 && mx <= 1047)
            {
                if (my >= 365 && my <= 424)
                {
                    isfaren = 1;
                }
                else if (my >= 300 && my <= 362)
                {
                    ismps = 1;
                }
            }
        }

        if (page == 3)
        {
            if (mx >= 874 && mx <= 1033 && my >= 65 && my <= 111 && page == 3)
                page = 0;
        }
        

        if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {
        }
    }

    printf("x = %d, y= %d ", mx, my);
    printf("\n");
    cout << ismps << endl;

    // printf("page = %d\n", page);
    // cout << city_weather.temperature << endl;
}

void iMouseMove(int mx, int my)
{
    printf("x = %d, y= %d\n", mx, my);
}

int main()
{
    int page = 0;
    readWeatherDataFromFile();

    iInitialize(1050, 545, "Weather App");

    return 0;
}
