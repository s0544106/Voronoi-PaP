#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <GL/glut.h>
#include "abstand.h"
#include "parallel.h"
#include "sequentiell.h"
#define MAX_POINTS 5000
#define HEIGHT 900
#define WIDTH 900

// globale Variablen für die draw Funktion
int saveColor[HEIGHT][WIDTH];
int x[MAX_POINTS];
int y[MAX_POINTS];
int pointsFromFileCounter = 0;


/**
 * Es werden zufällige Farben erzeugt
 * Jeder Pixel bekommt eine Farbe
 * Jeder Punkt aus der txt Datei wird gesetzt
 */
void draw()
{
	int i,j,colorIndex;
	unsigned char rgb[pointsFromFileCounter*3];

	/*
	 * Erstellen von zufälligen, aufeinanderfolgenden RGB Farben
	 * z.B. rgb[0]+rgb[1]+rgb[2] = gelb
	 * 		  rgb[3]+rgb[4]+rgb[5] = blau
	 *      ......
	 */
	for(i = 0; i < (pointsFromFileCounter)*3; i++) {
		rgb[i] = rand() / (1. + RAND_MAX) * 256;
	}

	// Jeder einzelne Pixel wird eingefärbt
	glClear ( GL_COLOR_BUFFER_BIT );
	for(i = 0; i < HEIGHT; i++){
		for(j = 0; j < WIDTH; j++){
			colorIndex = saveColor[i][j];
			glBegin(GL_POINTS);
			glColor3ub(rgb[colorIndex*3],rgb[colorIndex*3+1],rgb[colorIndex*3+2]);
			glVertex2i(j,i);
			glEnd();
		}
	}


	glPointSize(2.0f);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f,0.0f);
	for(i = 0; i < pointsFromFileCounter; i++){
		glVertex2i(x[i],y[i]);
	}
	glEnd();
	glFlush();
}

/**
 *	Daten werden aus der Textdatei gelesen und verarbeitet.
 *	Beginn der sequentiellen und parallelen Berechnung
 *	kuerzeste Dintanz auswerten und zuweisen
 *	Starte grafische Darstellung mit OpenGL
 */
int main (int argc, char **argv) {

	if ( argc != 2 ) {
			printf( "Anwendung: %s coordinates900.txt \n", argv[0] );

	}
	else {

		FILE *infile;
		infile = fopen(argv[1], "r");
		int i = 0;
		double number;
		system("clear");
		printf("Voronoi Generator auf einer Ebene.\n" );
		printf("Bitte die Azahl der Sites festlegen,\n" );
		printf("dazu eine Zahl zwischen 2 und 5000 eingeben: ");
		scanf("%lf", &number);

		/*
		 * Lesen der Dateil Zeile für Zeile. Die X und Y Werte werden gespeichert
		 * "pointsFromFileCounter" läuft bis die gewollten Sites erreicht sind
		 */
		while(i < number) {
			fscanf(infile,"%d %d",&x[pointsFromFileCounter],&y[pointsFromFileCounter]);
			i++;
			pointsFromFileCounter++;
			if (feof(infile))
			{
				i = number;
			}
		}

		fclose(infile);

		float result_size = HEIGHT*WIDTH*pointsFromFileCounter;
		float * results = (float *)malloc(result_size*sizeof(float));
		double prgstart, prgende;

		// sequentielle Berechnung
		// Start der Zeitmessung
		prgstart = omp_get_wtime();

		sequentiell(x, y, results, result_size, pointsFromFileCounter, HEIGHT, WIDTH);

		prgende = omp_get_wtime();
		printf("sequentielle Laufzeit: %.2f Sekunden\n",prgende-prgstart);

		// parallele Berechnung
		prgstart = omp_get_wtime();

		parallel(x, y, results, result_size, pointsFromFileCounter, HEIGHT, WIDTH);

		prgende = omp_get_wtime();
		printf("parallele Laufzeit: %.2f Sekunden\n",prgende-prgstart);

		// Kuerzestern Abstand als colorIndex speichern
		int point, j;
		int nCounter = 0;
		double tempDistance;

		for(i=0;i<HEIGHT;i++){
			for(j=0;j<WIDTH;j++){


				tempDistance = HEIGHT*WIDTH; point = 0;

				/*
				 * Alle Abstaende der Punkte zu X,Y Werten betrachten
				 * Sund den kuerzesten als Index speichern
				 */
				while(point < pointsFromFileCounter){
					if (results[nCounter] < tempDistance){
						tempDistance = results[nCounter];
						saveColor[i][j] = point;
					}
					point++;
					nCounter++;
				}
			}
		}

		free(results);

		//Initialisieren der grafischen Ausgabe mit OpenGL
		//Hier wird die oben stehende "draw" Funktion aufgerufen
		glutInit ( &argc, argv );
		glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB );
		glutInitWindowSize ( (GLsizei)WIDTH, (GLsizei)HEIGHT );
		glutInitWindowPosition ( 70, 50 );
		glutCreateWindow("Voronoi");
		glClearColor ( 1.0, 1.0, 1.0, 0.0 ); //white background
		glMatrixMode ( GL_PROJECTION );
		glLoadIdentity ( );
		gluOrtho2D(0.0,(GLdouble)WIDTH,0.0,(GLdouble)HEIGHT);
		glutDisplayFunc ( draw );
		glutMainLoop ();

	}
    return EXIT_SUCCESS;
}
