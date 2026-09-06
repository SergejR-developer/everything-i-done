#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image\stb_image_write.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image\stb_image.h>

int main()
{
    int width, height, channels;

    printf("Please type in width (in pixels): ");
    scanf(" %d", &width);

    printf("Please type in height (in pixels): ");
    scanf(" %d", &height);

    printf("Please type in number of channels: ");
    scanf(" %d", &channels);

    int size = width * height * channels;

    unsigned char *data = malloc(size);

    for (unsigned char *p = data, x = 0; p != data + size; p += channels, x++)
    {
        if (x < width * height / 2)
        {
            *p       = 0; //red channel
            *(p + 1) = 0; //green channel
            *(p + 2) = 255; //blue channel
        }
        else
        {
            *p       = 255; //red channel
            *(p + 1) = 255; //green channel
            *(p + 2) = 0; //blue channel
        }
    }
    stbi_write_png("try.png", width, height, channels, data, width * channels);

    free(data);

    return 0;
}