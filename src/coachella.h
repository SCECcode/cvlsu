/**
 * @file coachella.h
 * @brief Main header file for LSU Coachella Valley library.
 * @author - SCEC 
 * @version 1.0
 *
 * Delivers LSU Coachella Valley Velocity Model
 *
 */

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

// Constants
#ifndef M_PI
	/** Defines pi */
	#define M_PI 3.14159265358979323846
#endif

/** Defines a return value of success */
#define SUCCESS 0
/** Defines a return value of failure */
#define FAIL 1
/** Defines a return value of NA from model */
#define NA -1 

// Structures
/** Defines a point (latitude, longitude, and depth) in WGS84 format */
typedef struct coachella_point_t {
	/** Longitude member of the point */
	double longitude;
	/** Latitude member of the point */
	double latitude;
	/** Depth member of the point */
	double depth;
} coachella_point_t;

/** Defines the material properties this model will retrieve. */
typedef struct coachella_properties_t {
	/** P-wave velocity in meters per second */
	double vp;
	/** S-wave velocity in meters per second */
	double vs;
	/** Density in g/m^3 */
	double rho;
} coachella_properties_t;

/** The COACHELLA configuration structure. */
typedef struct coachella_configuration_t {
	/** The zone of UTM projection */
	int utm_zone;
	/** The model directory */
	char model_dir[128];
	/** Number of x points */
	int nx;
	/** Number of y points */
	int ny;
	/** Number of z points */
	int nz;
	/** Depth in meters */
	double depth;
	/** Top left corner easting */
	double top_left_corner_e;
	/** Top left corner northing */
	double top_left_corner_n;
	/** Top right corner easting */
	double top_right_corner_e;
	/** Top right corner northing */
	double top_right_corner_n;
	/** Bottom left corner easting */
	double bottom_left_corner_e;
	/** Bottom left corner northing */
	double bottom_left_corner_n;
	/** Bottom right corner easting */
	double bottom_right_corner_e;
	/** Bottom right corner northing */
	double bottom_right_corner_n;
	/** Z interval for the data */
	double depth_interval;
        /** Bilinear or Trilinear Interpolation on or off (1 or 0) */
        int interpolation;

} coachella_configuration_t;

/** The model structure which points to available portions of the model. */
typedef struct coachella_model_t {
	/** A pointer to the Vp data either in memory or disk. Null if does not exist. */
	void *vp;
	/** Vp status: 0 = not found, 1 = found and not in memory, 2 = found and in memory */
	int vp_status;
} coachella_model_t;

// Constants
/** The version of the model. */
const char *coachella_version_string = "COACHELLA";

// Variables
/** Set to 1 when the model is ready for query. */
int coachella_is_initialized = 0;

/** Location of the binary data files. */
char coachella_data_directory[128];

/** Configuration parameters. */
coachella_configuration_t *coachella_configuration;
/** Holds pointers to the velocity model data OR indicates it can be read from file. */
coachella_model_t *coachella_velocity_model;

/** The height of this model's region, in meters. */
double coachella_total_height_m = 0;
/** The width of this model's region, in meters. */
double coachella_total_width_m = 0;

// UCVM API Required Functions

#ifdef DYNAMIC_LIBRARY

/** Initializes the model */
int model_init(const char *dir, const char *label);
/** Cleans up the model (frees memory, etc.) */
int model_finalize();
/** Returns version information */
int model_version(char *ver, int len);
/** Queries the model */
int model_query(coachella_point_t *points, coachella_properties_t *data, int numpts);

#endif

// COACHELLA Related Functions

/** Initializes the model */
int coachella_init(const char *dir, const char *label);
/** Cleans up the model (frees memory, etc.) */
int coachella_finalize();
/** Returns version information */
int coachella_version(char *ver, int len);
/** Queries the model */
int coachella_query(coachella_point_t *points, coachella_properties_t *data, int numpts);

// Non-UCVM Helper Functions
/** Reads the configuration file. */
int coachella_read_configuration(char *file, coachella_configuration_t *config);
void print_error(char *err);
/** Retrieves the value at a specified grid point in the model. */
void coachella_read_properties(int x, int y, int z, coachella_properties_t *data);
/** Attempts to malloc the model size in memory and read it in. */
int coachella_try_reading_model(coachella_model_t *model);
/** Calculates density from Vs. */
double coachella_calculate_density(double vs);

// Interpolation Functions
/** Linearly interpolates two coachella_properties_t structures */
void coachella_linear_interpolation(double percent, coachella_properties_t *x0, coachella_properties_t *x1, coachella_properties_t *ret_properties);
/** Bilinearly interpolates the properties. */
void coachella_bilinear_interpolation(double x_percent, double y_percent, coachella_properties_t *four_points, coachella_properties_t *ret_properties);
/** Trilinearly interpolates the properties. */
void coachella_trilinear_interpolation(double x_percent, double y_percent, double z_percent, coachella_properties_t *eight_points,
							 coachella_properties_t *ret_properties);
