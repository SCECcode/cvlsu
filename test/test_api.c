/**
 * @file test.c
 * @brief Bootstraps the test framework for the COACHELLEA/CVLSU library.
 * @author - SCEC
 * @version 1.0
 *
 * Tests the COACHELLEA/CVLSU library by loading it and executing the code as
 * UCVM would do it.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "cvlsu.h"

/**
 * Initializes and runs the test program. Tests link against the
 * static version of the library to prevent any dynamic loading
 * issues.
 *
 * @param argc The number of arguments.
 * @param argv The argument strings.
 * @return A zero value indicating success.
 */
int main(int argc, const char* argv[]) {

	// Declare the structures.
	cvlsu_point_t pt;
	cvlsu_properties_t ret;

	// Initialize the model.
        char *envstr=getenv("UCVM_INSTALL_PATH");
        if(envstr != NULL) {
           assert(cvlsu_init(envstr, "cvlsu") == 0);
           } else {
             assert(cvlsu_init("..", "cvlsu") == 0);
        }

	printf("Loaded the model successfully.\n");

	// Query a point.
	pt.longitude = -116.4;
	pt.latitude = 33.5;
	pt.depth = 1000;

	cvlsu_query(&pt, &ret, 1);

	assert(ret.vs > 0);
	assert(ret.vp > 0);
	assert(ret.rho > 0);

	printf("Query was successful.\n");

	// Close the model.
	assert(cvlsu_finalize() == 0);

	printf("Model closed successfully.\n");

	printf("\nALL CVLSU TESTS PASSED");

	return 0;
}
