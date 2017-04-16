#include <omp.h>
/**
 * Berechnung des Abstands zwischen jedem gesetzten Punkt und allen Pixeln der Ebene
 * x =	Werte auf der X-Achse
 * y =	Werste auf der Y-Achse
 * results =	Array um Abstand zu speichern
 * size_results =	Anzahl der Berechnungen
 * size_points =	Anzahl der x,y Paare
 * size_height =	Hoehe der Ebene (alle x-Pixel)
 * size_width =	Breite der Ebene (alle y-Pixel)
 */
void parallel(int * x, int * y, float * results, int size_results, int size_points, int size_height, int size_width)
{
	int i,width,height,point;

	#pragma omp parallel for private(point, width, height)
	for (i = 0; i < size_results; i++) {
		point = i % size_points;
		width = (i / size_points) % size_width;
		height = ((i / size_points / size_width)) % size_height;

		results[i] = abstand(width,height,x[point],y[point]);
	}
}
