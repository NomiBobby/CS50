#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// typedef struct
// {
//     BYTE  rgbtBlue;
//     BYTE  rgbtGreen;
//     BYTE  rgbtRed;
// } __attribute__((__packed__))
// RGBTRIPLE;

// typedef uint8_t  BYTE;
// typedef uint32_t DWORD;
// typedef int32_t  LONG;
// typedef uint16_t WORD;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average =
                round(
                        (
                            (float)image[i][j].rgbtBlue +
                            (float)image[i][j].rgbtGreen +
                            (float)image[i][j].rgbtRed
                        )
                        / 3.0
                    );

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int mid_index;
    if (width % 2 == 0)
    {
        // Even number
        mid_index = width/2 - 1;
    }
    else
    {
        mid_index = (width - 1) / 2;
    }

    BYTE temp_blue;
    BYTE temp_green;
    BYTE temp_red;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <= mid_index; j++)
        {
            temp_blue = image[i][j].rgbtBlue;
            temp_green = image[i][j].rgbtGreen;
            temp_red = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtBlue = temp_blue;
            image[i][width - j - 1].rgbtGreen = temp_green;
            image[i][width - j - 1].rgbtRed = temp_red;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // make a copy of image
    RGBTRIPLE (*image_copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image_copy == NULL)
    {
        printf("Failed to allocate memory for image_copy.\n");
        return;
    }

    // Copy image to image_copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            {
                float sum_r = 0.0;
                float sum_g = 0.0;
                float sum_b = 0.0;
                int count = 0;

                for (int m = i - 1; m <= i + 1; m++)
                {
                    for (int n = j - 1; n <= j + 1; n++)
                    {
                        if (!(m < 0 || m > height -1 || n < 0 || n > width - 1))
                        {
                            sum_b = sum_b + image_copy[m][n].rgbtBlue;
                            sum_g = sum_g + image_copy[m][n].rgbtGreen;
                            sum_r = sum_r + image_copy[m][n].rgbtRed;
                            count ++;
                        }
                    }
                }

                image[i][j].rgbtBlue = round(sum_b / count);
                image[i][j].rgbtGreen = round(sum_g / count);
                image[i][j].rgbtRed = round(sum_r / count);
            }
        }
    }

    free(image_copy);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // make a copy of image
    RGBTRIPLE (*image_copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image_copy == NULL)
    {
        printf("Failed to allocate memory for image_copy.\n");
        return;
    }

    // Copy image to image_copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] = {
        {-1, -2, -1},
        {0,  0,  0},
        {1,  2,  1}
    };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float gx_r = 0;
            float gx_g = 0;
            float gx_b = 0;
            float gy_r = 0;
            float gy_g = 0;
            float gy_b = 0;

            for (int m = 0; m < 3; m++)
            {
                for (int n = 0; n < 3; n++)
                {
                    // if [m][n] is within the 2D array
                    if (!(i - 1 + m < 0 || i - 1 + m > height - 1 || j - 1 + n < 0 || j - 1 + n > width -1))
                    {
                        gx_b = gx_b + Gx[m][n] * image_copy[i - 1 + m][j - 1 + n].rgbtBlue;
                        gx_g = gx_g + Gx[m][n] * image_copy[i - 1 + m][j - 1 + n].rgbtGreen;
                        gx_r = gx_r + Gx[m][n] * image_copy[i - 1 + m][j - 1 + n].rgbtRed;
                        gy_b = gy_b + Gy[m][n] * image_copy[i - 1 + m][j - 1 + n].rgbtBlue;
                        gy_g = gy_g + Gy[m][n] * image_copy[i - 1 + m][j - 1 + n].rgbtGreen;
                        gy_r = gy_r + Gy[m][n] * image_copy[i - 1 + m][j - 1 + n].rgbtRed;
                    }
                    // [m][n] is outside of the 2D array, set all channels to 0
                    else
                    {
                        gx_b = gx_b + Gx[m][n] * 0;
                        gx_g = gx_g + Gx[m][n] * 0;
                        gx_r = gx_r + Gx[m][n] * 0;
                        gy_b = gy_b + Gy[m][n] * 0;
                        gy_g = gy_g + Gy[m][n] * 0;
                        gy_r = gy_r + Gy[m][n] * 0;
                    }
                }
            }

            // Assign value to Blue
            int GxGy_b = round(sqrt(gx_b*gx_b + gy_b*gy_b));
            int GxGy_g = round(sqrt(gx_g*gx_g + gy_g*gy_g));
            int GxGy_r = round(sqrt(gx_r*gx_r + gy_r*gy_r));

            if (GxGy_b > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = GxGy_b;
            }

            // Assign value to Green
            if (GxGy_g > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = GxGy_g;
            }

            // Assign value to Red
            if (GxGy_r > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = GxGy_r;
            }
        }
    }

    free(image_copy);

    return;
}
