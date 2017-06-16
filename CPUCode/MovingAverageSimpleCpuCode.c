/**
 * MaxFile name: MovingAverageSimple
 * 
 * k-means algorithm is a method of cluster analysis in data mining. 
 * k-means clustering aims to partition n observations into k clusters. 
 * each observation belongs to the cluster with the nearest center point of the class. 
 * 
 * Implementation:
 * Calculates a given point belongs to each of the given classes.
 *
 * A point belongs to a class if it lies within its radius.
 * In order to check that, a point lies within the radius of the class
 * Calculate the Euclidean distance between the point and the centre of the class
 * The point would lie within the class if that distance is less than the radius of the class.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Maxfiles.h"
#include "MaxSLiCInterface.h"

// initial values
static const int DIM = 4;		    // # of dimensions.
static const int CLASSES = 8;	    // # of classes.
static const int POINTS	= 128;	    // # of data points.
static const int SIZE_FLOAT = 4;	// size of float.

static void calc_kmeans(
	const float const *center_classes,     // centre points of all the classes.
	const float const *square_radiuses,    // square radiuses of all the classes.
	const float const *data_points,        // data points to be classified.
	float *output                          // relationship between data point and all the classes.
	) {
    // calculate the square euclidean distance between its centre and the given point.
    // if Euclidean distance is smaller than the class radius, the data point belongs to that class.
    for(int j = 0; j < CLASSES; j++) {
    	float dist = 0.0;
    	for(int i = 0 ; i < DIM; i++) {
    		dist = pow(center_classes[i + DIM*j] - data_points[i], 2) + dist;
    	}
    	output[j] = (dist < square_radiuses[j])? j : -1;
    }
}

int main(void) {
    // initialize actual k-means calculation variables
	float *kmean_center_classes = malloc(DIM*CLASSES*SIZE_FLOAT);
	float *kmean_square_radiuses = malloc(CLASSES*SIZE_FLOAT);
	float *kmean_data_points = malloc(POINTS*DIM*SIZE_FLOAT);
	float *actual_output = malloc(POINTS*CLASSES*SIZE_FLOAT);

	// generate random input data points, class center points and square radiuses
	for(int i = 0; i < CLASSES*DIM; i++){
		kmean_center_classes[i] = random() % 100;
	}	
	for(int i = 0; i < CLASSES; i++) {
		kmean_square_radiuses[i] = random() % 100;
		kmean_square_radiuses[i] = kmean_square_radiuses[i] * kmean_square_radiuses[i];
	}
	for(int i = 0; i < DIM*POINTS; i++){
		kmean_data_points[i] = random() % 100;
	}
	
	// initialize actual CPU output and Euclidean distances
	for(int i = 0 ; i < CLASSES*POINTS; i++) {
		actual_output[i] = 0;
	}
	
	
	// initialize kernal k-means calculation variables
	float *kernal_center_classes = malloc(DIM*CLASSES*SIZE_FLOAT);
	float *kernal_square_radiuses = malloc(CLASSES*SIZE_FLOAT);
	float *kernal_data_points = malloc(POINTS*DIM*SIZE_FLOAT);
	float *kernal_output = malloc(POINTS*CLASSES*SIZE_FLOAT);

	// generate random input data points, class center points and square radiuses
	for(int i = 0; i < CLASSES*DIM; i++){
		kernal_center_classes[i] = random() % 100;
	}	
	for(int i = 0; i < CLASSES; i++) {
		kernal_square_radiuses[i] = random() % 100;
		kernal_square_radiuses[i] = kernal_square_radiuses[i] * kernal_square_radiuses[i];
	}
	for(int i = 0; i < DIM*POINTS; i++){
		kernal_data_points[i] = random() % 100;
	}
	
	// initialize kernal output and Euclidean distances
	for(int i = 0 ; i < CLASSES*POINTS; i++) {
		kernal_output[i] = 0;
	}
	
    // running k-means actual and kernal method
	printf("Running K-Means on CPU.\n");
	for(int i = 0; i < POINTS; i++) {
		calc_kmeans(kmean_center_classes, kmean_square_radiuses, 
		            &kmean_data_points[DIM*i], &actual_output[CLASSES*i]);
	}
	for(int i = 0; i < POINTS; i++) {
		MovingAverageSimple(1, kernal_center_classes, kernal_square_radiuses, 
		                    &kernal_data_points[DIM*i], &kernal_output[CLASSES*i]);
	}
		
	// check kernal and actual result and print the output
    for(int i = 0; i < POINTS*CLASSES; i++) {
        if (actual_output[i] != kernal_output[i]) {
			printf("actual and kernal giving different result for data point %d: %.3lf, %.3lf\n", 
			        i, actual_output[i], kernal_output[i]);
		}else{
		    printf("actual and kernal giving same result for data point %d: %.3lf, %.3lf\n", 
		            i, actual_output[i], kernal_output[i]);
		}
    }
    printf("Done.\n");
	return 0;
}