#ifndef ADI_H
#define ADI_H

#include <stddef.h>   // for size_t (future-safe)

/* ADI file header structure
   This structure is written at the beginning of every .adi file */
struct ADIHeader {
    char magic[3];            // 'A', 'D', 'I'
    int width;                // image width in pixels
    int height;               // image height in pixels
    unsigned char channels;   // number of color channels (1 or 3)
};

/* Write an ADI file to disk
   Returns 0 on success, non-zero on failure */
int write_adi(const char *filename,
              struct ADIHeader *header,
              unsigned char *pixels);

/* Read an ADI file from disk
   Returns pointer to pixel data on success, NULL on failure
   Caller is responsible for freeing the returned buffer */
unsigned char *read_adi(const char *filename,
                        struct ADIHeader *out_header);

#endif /* ADI_H */

