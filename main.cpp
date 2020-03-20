#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

void output(float **image_data, int w, int h);
void init(int image_width, int image_height, int image_layers_count, float **image_data, float *x_mod, float *y_mod, float *s_mod);
void printImageMatrix(float **img, int h, int w);
float map_number(float in_value, float min_in_range, float max_in_range, float min_out_range, float max_out_range);


int main()
{   
    // Define the basic image properties
    const int image_width = 800, image_height = 600, image_layers_count = 3;

    // The values to be multiplied with the x coordonate
    float *x_mod = new float[image_layers_count];

    // The values to be multiplied with the y coordonate
    float *y_mod = new float[image_layers_count];

    // The values to be multiplied with the layers itself (thus scaling the layer)
    float *s_mod = new float[image_layers_count];

    // The matrix that will hold the image data
    float **image_data = new float*[image_height];
    for (int i = 0; i < image_height; i++)
        image_data[i] = new float[image_width];

    // Initializing all the field above from a file
    init(image_width, image_height, image_layers_count, image_data, x_mod, y_mod, s_mod);

    // This is where the fun happens
    // Generate the image_dat using cos waves
    for (int layer = 0; layer < image_layers_count; layer++)
    {
        for (int i = 0; i < image_height; i++) 
        {
            for (int j = 0; j < image_width; j++) 
            {
                float cos_value = cos(x_mod[layer] * i * s_mod[layer] + y_mod[layer] * j * s_mod[layer]);
                image_data[i][j] -= map_number(cos_value, -1.0, 1.0, 0.0, 1.0);
                if (image_data[i][j] > 1) 
                    image_data[i][j] = 1;
            }
        }
    }
    // printImageMatrix(image_data, image_height, image_width);
    // Write the generated image matrix in a file
    output(image_data, image_width, image_height);

    // Code that renders the image using a python script
    int img_script_res = system("python gen_image.py");
    if (img_script_res != 0)
        printf("Exit code was: %d", img_script_res);

    //return 0;
}

void output(float **image_data, int w, int h)
{
    std::ofstream data_output("image_data.txt");
    data_output << h << " " << w << "\n";
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            data_output << image_data[i][j] << " ";
    data_output.close();
}

void init(int image_width, int image_height, int image_layers_count, float **image_data, float *x_mod, float *y_mod, float *s_mod)
{
    // Fill the image_data matrix with 0's
    for (int i = 0; i < image_height; i++)
        for (int j = 0; j < image_width; j++)
            image_data[i][j] = 1;

    // Generate the data for x_mod, y_mod, s_mod with a .py script
    char layer_count_string[4], layer_gen_command[30] = "python gen_layers.py ";
    std::sprintf(layer_count_string, "%d", image_layers_count);
    std::strcat(layer_gen_command, layer_count_string);
    
    int layer_gen_script_res = system(layer_gen_command);
    if (layer_gen_script_res != 0)
        printf("Exit code was: %d", layer_gen_script_res);

    // Reading the data into x_mod, y_mod, s_mod
    std::ifstream layer_input("layer_data.txt");
    for (int i = 0; i < image_layers_count; i++)
        layer_input >> x_mod[i] >> y_mod[i] >> s_mod[i];
    layer_input.close();
}

void printImageMatrix(float **img, int h, int w)
{
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++)
            printf("%d ", img[i][j]);
        printf("\n");
    }
}

float map_number(float in_value, float min_in_range, float max_in_range, float min_out_range, float max_out_range)
{
    float x = (in_value - min_in_range) / (max_in_range - min_in_range);
    return min_out_range + (max_out_range - min_out_range) * x;
}