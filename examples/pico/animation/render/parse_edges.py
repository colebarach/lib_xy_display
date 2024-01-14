import time
import os
import json

import cv2
import numpy as np

FRAMES = 512

IN_WIDTH  = 480
IN_HEIGHT = 360

OUT_WIDTH  = 256
OUT_HEIGHT = 192
OUT_Y_OFF  = 32

BASE_PNG_DIR = 'frames'
BASE_PNG_PATH = BASE_PNG_DIR + '/frame%d.png'

def get_edges(i):
    img = cv2.imread(BASE_PNG_PATH % (i + 1), 0)
    edges = cv2.Canny(img, 100, 255)
    
    indices = np.where(edges != [0])

    x = np.round((indices[1] / IN_WIDTH) * OUT_WIDTH).astype(int)
    y = np.round((1 - indices[0] / IN_HEIGHT) * OUT_HEIGHT + OUT_Y_OFF).astype(int)

    coords = zip(x, y)
    return list(coords)

print(FRAMES)

for i in range(FRAMES):
    coords = get_edges(i*2)
    print(len(coords))
    print(coords)
