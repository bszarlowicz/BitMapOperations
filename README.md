
# Bitmap description

A binary image (or briefly a bitmap) is an image in which each pixel
is either black or white in color. It is very often used in the recognition and analysis of binary images
the so-called morphological operations (filters). By default, these filters are defined very generally.
We, for the purposes of this task, narrow down their definitions a bit.
For example, consider a 7 by 7 pixel bitmap. Every bitmap pixel can be
represented in computer memory as a logical variable. For the purposes of this task, we assume
that black pixels correspond to a true value in the bitmap, and white pixels correspond to a true value
false. The figure below will be used to illustrate the operation of basic filters
morphological.

Bitmap template

![image](https://github.com/bszarlowicz/BitMapOperations/assets/127704473/37c5acd1-a570-4168-b990-2bf39218aec6)

For a fixed pixel by its neighbors we mean:
1. The pixel directly above it.
2. The pixel directly below it.
3. The pixel directly to the left of it.
4. The pixel directly to the right of it.

## Description of the implemented morphological filters
1. Inversion - or simply negation - consists in replacing black pixels with white and white pixels with
black.

![image](https://github.com/bszarlowicz/BitMapOperations/assets/127704473/66fbc736-f1f6-447a-b277-636aa71d7613)

2. Erosion. By the edge pixel of the image we mean a black pixel, one of whose neighbors it is white pixel.
   The erosion operation consists in locating all pixels first in the image, and then set their color to white.

![image](https://github.com/bszarlowicz/BitMapOperations/assets/127704473/0d2b66bc-2496-4e6e-907e-536485550423)

3. Dilation - is in a sense the opposite operation to erosion.
   As a result of dilation all white pixels that are adjacent to a black pixel are changed to black.

![image](https://github.com/bszarlowicz/BitMapOperations/assets/127704473/6d2ae980-ce6e-4017-8cf1-1a6972adf3fc)

4. Reset - total reset, tabula rasa - sets all pixels to white.

![image](https://github.com/bszarlowicz/BitMapOperations/assets/127704473/7a3309fc-6213-4227-9312-20a456d8f3d1)

5. Averaging - for each pixel p of the image we check the number of adjacent pixels
whites and blacks. If it has more than 2 neighbors in color k, then the new color of the pixel p is the color k.

![image](https://github.com/bszarlowicz/BitMapOperations/assets/127704473/2b8dfaa2-1a6f-4371-b961-6c3f3a3b731d)


