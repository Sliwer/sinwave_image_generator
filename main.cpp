#include <iostream>

void printImageMatrix(int **img);

int main()
{   
    // Define the basic image properties
    const int image_width = 4, image_height = 4, image_layers_count = 10;

    // The values to be multiplied with the x coordonate
    float *x_mod = new float[image_layers_count];

    // The values to be multiplied with the y coordonate
    float *y_mod = new float[image_layers_count];

    // The values to be multiplied with the layers itself (thus scaling the layer)
    float *s_mod = new float[image_layers_count];

    // The matrix that will hold the image data
    int **image_data = new int*[image_height];
    for (int i = 0; i < image_height; i++)
        image_data[i] = new int[image_width];

    // Fill the matrix with 0's
    for (int i = 0; i < image_height; i++)
        for (int j = 0; j < image_width; j++)
            image_data[i][j] = 0;

    
    
    // Code that renders the image using a python script
    int res = system("python gen_image.py");
    if (res != 0)
        printf("Exit code was: %d", res);

    return 0;
}

void printImageMatrix(int **img, int h, int w)
{
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++)
            printf("%d ", img[i][j]);
        printf("\n");
    }
}