import numpy as np
from PIL import Image
from matplotlib import pyplot as plt
from matplotlib.pyplot import imshow

ScaleAlgorith_Near = 1
ScaleAlgorith_Bilinearity = 1

Alignment_TopLeft = 1
Alignment_TopRight = 2
Alignment_BottomLeft = 3
Alignment_BottomRight = 4
Alignment_Center = 5

ColorMode_3Byte = 1
ColorMode_565 = 2
ColorMode_444 = 3

# all configs
ScaleAlgorithm = ScaleAlgorith_Near
Alignment = Alignment_TopLeft
ColorMode = ColorMode_565
OutputHeight = 40
OutputWidth = 40


def scale_image():
    im = Image.open('./screenshot.png')  # read image into an Image object with PIL
    im = im.convert('RGB')
    im = np.array(im)  # create a numpy ndarray from the Image object

    imshow(im)  # use skimage imshow to display the image

    origin_height = im.shape[0]
    origin_width = im.shape[1]
    height = OutputHeight
    width = OutputWidth

    new_image = [[[0, 0, 0] for _ in range(width)] for _ in range(height)]
    x_scale = 1.0 * width / origin_width
    y_scale = 1.0 * height / origin_height

    print("x_scale: %s, y_scale: %s", x_scale, y_scale)

    # scale image
    for i in range(height):
        for j in range(width):

            if ScaleAlgorithm == ScaleAlgorith_Near:
                if Alignment == Alignment_TopLeft:
                    hh, ww = int(i / y_scale), int(j / x_scale)
                elif Alignment == Alignment_Center:
                    raise "Unsupported Alignment"
                new_image[i][j][0] = im[hh][ww][0]
                new_image[i][j][1] = im[hh][ww][1]
                new_image[i][j][2] = im[hh][ww][2]
            elif ScaleAlgorithm == ScaleAlgorith_Bilinearity:
                if Alignment == Alignment_TopLeft:
                    hh, ww = int(i / y_scale), int(j / x_scale)
                elif Alignment == Alignment_Center:
                    raise "Unsupported Alignment"
                new_image[i][j][0] = (im[hh][ww][0] + im[hh + 1][ww][0] + im[hh][ww + 1][0] + im[hh + 1][ww + 1][0]) / 4
                new_image[i][j][1] = (im[hh][ww][1] + im[hh + 1][ww][1] + im[hh][ww + 1][1] + im[hh + 1][ww + 1][1]) / 4
                new_image[i][j][2] = (im[hh][ww][2] + im[hh + 1][ww][2] + im[hh][ww + 1][2] + im[hh + 1][ww + 1][2]) / 4

    # convert to RGB565
    image_data = [
        [((new_image[i][j][0] & 0xf8) << 8) + ((new_image[i][j][1] & 0xfc) << 3) + (new_image[i][j][2] >> 3) for j in
         range(width)] for i in range(height)]

    # print pixel encoding in c language
    print("__code unsigned int image_data[%d][%d]={" % (height, width))
    for i in range(height):
        print("{", end="")
        for j in range(width):
            print("0x%x," % image_data[i][j], end="")
        print("},\n", end="")
    print("};")
    imshow(new_image)
    plt.axis('off')
    plt.show()


if __name__ == '__main__':
    scale_image()

