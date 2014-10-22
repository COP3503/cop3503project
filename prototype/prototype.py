import cv2
import cv2.cv as cv
import numpy as np
import os

class Coin_Counter(object):
    def __init__(self):
        '''Design:
            - Segment
            - Label
            - Resegment
            - Relabel
            - 10-20 Iterations
            --> Dynamically arrive at a solution
        '''
        pass

    @classmethod
    def count_coins(self, image):
        coin_names = []
        coins = self.segment_coins(image)
        for coin in coins:
            coin_name = identify_coin(coin)
            coin_names.append(coin_name)

    @classmethod
    def segment_coins(self, image):
        cv2.imshow("image", image)
        im_greyscale = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        circles = cv2.HoughCircles(im_greyscale, cv.CV_HOUGH_GRADIENT,
            dp=0.1, minDist=100,
            param1=1, param2=1,  # WTF do these do?
            minRadius=10, maxRadius=250)

        for circle in circles[0]:
            # Image, (x, y), radius, (R, G, B), thickness
            cv2.circle(image, (circle[0], circle[1]), circle[2], 
                (255, 0, 255), thickness=5)
        cv2.imshow("Image 2", image)
        cv2.waitKey(0)
        return

    @classmethod
    def identify_coin(self, image):
        '''Returns None if no coin is identified'''
        pass

if __name__=='__main__':
    image = cv2.imread(os.path.join('.', 'coins.jpg'))
    CC = Coin_Counter()
    CC.segment_coins(image)
