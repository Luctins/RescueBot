# -*- coding: cp1252 -*-
from collections import deque
import numpy as np
import cv2
import argparse

#TODO: Achar Objetos da cor rosa (vítimas)

#Lista de argumentos
ap = argparse.ArgumentParser()
ap.add_argument("-b", "--buffer", type = int, default = 32, help =  "max buffer size")
ap.add_argument("-co", type = bool, default = True, help = "debug color picker" )
args = vars(ap.parse_args())

#cores para achar na imagem, HSV
colorUpper = np.uint8([[[50,50,50]]])
colorUpper = cv2.cvtColor(colorUpper, cv2.COLOR_BGR2HSV)

colorLower = np.uint8([[[2,2,2]]])
colorLower = cv2.cvtColor(colorLower, cv2.COLOR_BGR2HSV)

#fila de eventos
pts = deque(maxlen = args["buffer"])

#Abre a câmera '0'
cap = cv2.VideoCapture(0)

while (1):
    #captura imagem da câmera
    grabbed, frame = cap.read() 

    grey = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)#converte para escala de cinza
    blur = cv2.GaussianBlur(grey, (11,11), 0)   #borra a imagem
    

    #converte para imagema apenas P&B
    mask = cv2.adaptiveThreshold(blur,255,cv2.ADAPTIVE_THRESH_MEAN_C,\
                                                           cv2.THRESH_BINARY, 11, 5)
   
    #hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)  #converte cores da imagem de RGB para HS
    #mask2 = cv2.inRange(hsv, colorLower, colorUpper)     #filtra imagem pela cor

    mask = cv2.erode(mask, None, iterations = 3)        #remove ruído da imagem
    mask = cv2.dilate(mask, None, iterations = 1)       #realça a imagem

    
    
    cv2.imshow('original', frame)
    cv2.imshow('grey', grey)
    cv2.imshow('blurred', blur)
    cv2.imshow('result', mask)
                    
    #contours = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]

    #Sequência de Escape, aperte 'q' para sair
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    
cap.release()
cv2.destroyAllWindows()
