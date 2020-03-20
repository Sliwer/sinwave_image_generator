import numpy
import cv2

with open('image_data.txt', 'r') as f:
    d = f.readline().split(' ')
    image_height = int(d[0])
    image_width = int(d[1])

    image_data = numpy.empty([image_height, image_width])

    # The image data as an array
    d = f.readline().split(' ')

    # Counts each element of the image data
    # so that we can convert it into a matrix with for loops
    counter = 0 

    for i in range(0, image_height):
        for j in range(0, image_width):
            image_data[i][j] = d[counter]
            counter += 1

cv2.imshow('image', image_data)
cv2.waitKey(0)
quit()
