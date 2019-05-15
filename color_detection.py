#Codigo de interaccion entre Arduino y OpenCV
import urllib 
import cv2
import numpy as np
import serial #cargamos la libreria serial
 
#Iniciamos la camara
captura = cv2.VideoCapture(0)
 
#Iniciamos la comunicacion serial
ser = serial.Serial('/dev/ttyACM0', 9600)
 
while(1):
  
   #Capturamos una imagen y la convertimos de RGB -> HSV
   _, imagen = captura.read()
   hsv = cv2.cvtColor(imagen, cv2.COLOR_BGR2HSV)
 
  #mascara color verde 
   verde_bajos = np.array([49,50,50], dtype=np.uint8)
   verde_altos = np.array([80, 255, 255], dtype=np.uint8)

   #Creamos mascaras para los colores Rojo y Azul
   #Rojos:
   rojo_bajos1 = np.array([0,65,75], dtype=np.uint8)
   rojo_altos1 = np.array([12, 255, 255], dtype=np.uint8)
   rojo_bajos2 = np.array([240,65,75], dtype=np.uint8)
   rojo_altos2 = np.array([256, 255, 255], dtype=np.uint8)
    #Verdes:
   #verde_bajos = np.array([49,50,50])
   #verde_altos = np.array([107, 255, 255])
   #Azules:
   azul_bajos = np.array([100,65,75], dtype=np.uint8)
   azul_altos = np.array([130, 255, 255], dtype=np.uint8)
 
    #Crear una mascara con solo los pixeles dentro del rango de verdes
   mask_v = cv2.inRange(hsv, verde_bajos, verde_altos)
   mask_a = cv2.inRange(hsv, azul_bajos, azul_altos)
   mask_r1 = cv2.inRange(hsv, rojo_bajos1, rojo_altos1)
   mask_r2 = cv2.inRange(hsv, rojo_bajos2, rojo_altos2)
   mask_r = cv2.add(mask_r1, mask_r2)
   
   #Encontrar el area de los objetos que detecta la camara
   moments_v = cv2.moments(mask_v)
   area_v = moments_v['m00']

   moments_a = cv2.moments(mask_a)
   area_a = moments_a['m00']

   moments_r = cv2.moments(mask_r)
   area_r = moments_r['m00']
 
   #Descomentar para ver el area por pantalla
   #print area
 
   #Si el objeto tiene un area determinada, escribimos 'h'
   #Si no, escribimos un caracter erroneo
   if(area_v > 2000000):
      ser.write('h')
   if(area_a > 2000000):
      ser.write('a')
   #if(area_r > 2000000):
   #   ser.write('r')
   else:
      ser.write('n')
 
   #Mostramos la imagen original y
   #la mascara
   #cv2.imshow('mask', mask_r)
   cv2.imshow('mask', mask_a)
   #cv2.imshow('mask', mask_v)
   cv2.imshow('Camara', imagen)
   tecla = cv2.waitKey(5) & 0xFF
   if tecla == 27:
      break
 
cv2.destroyAllWindows()