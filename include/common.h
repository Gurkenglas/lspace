#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Error handling */
#define FATAL(reason) \
    fprintf(stderr, "[!] Fatal error in file %s at line %d: %s\n", __FILE__, __LINE__, reason "\n"); \
    exit(EXIT_FAILURE);

/* Beautiful sugar */
#define COUNT(x) (sizeof (x)/sizeof (x)[0])
#define UNUSED(x) ((void)(x))

#endif /* COMMON_H */
