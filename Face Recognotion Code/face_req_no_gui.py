from picamera import PiCamera
from time import sleep
import face_recognition
import os
import serial

ser = serial.Serial ("/dev/ttyAMA0", 9600) 
camera = PiCamera()
camera.resolution = (250, 250)
KNOWN_FACES_DIR = '/home/pi/Desktop/faceRec/known_faces'
UNKNOWN_FACES_DIR = '/home/pi/Desktop/faceRec/unknown_faces'
TOLERANCE = 0.55
MODEL = 'cnn'  # default: 'hog', other one can be 'cnn' - CUDA accelerated (if available) deep-learning pretrained model

known_faces = []
known_names = []

def loadKnownFaces():
     for name in os.listdir(KNOWN_FACES_DIR):

        # Next we load every file of faces of known person
        for filename in os.listdir(f'{KNOWN_FACES_DIR}/{name}'):

            # Load an image
            image = face_recognition.load_image_file(f'{KNOWN_FACES_DIR}/{name}/{filename}')

            # If the number of faces is not ONLY ONE in an image retake the images!
            encodings = face_recognition.face_encodings(image)
            if len(encodings) > 0:            
                encoding = encodings[0]
                # Append encodings and name
                known_faces.append(encoding)
                known_names.append(name)
                return True
            else:
                return False
        
loadKnownFaces()
while True:
    ser.flush
    firstTime = ' '
    ser.write(str.encode('S'))
    firstTime = ser.read() 

    # this is the first time, add the user
    if firstTime == str.encode('y'):
        camera.rotation = 180
        for i in range(3):
            sleep(3)
            camera.capture('/home/pi/Desktop/faceRec/known_faces/Zizo/image%s.jpg' % i)

        if loadKnownFaces() == False:
            ser.write(str.encode('R'))
        else:
            ser.write(str.encode('W'))
        

    # not the first time, we are validating user 
    elif firstTime == str.encode('n'):
        camera.rotation = 180
        sleep(3)
        camera.capture('/home/pi/Desktop/faceRec/unknown_faces/image.jpg')
        
        # Now let's loop over a folder of faces we want to label
        for filename in os.listdir(UNKNOWN_FACES_DIR):

            # Load image
            image = face_recognition.load_image_file(f'{UNKNOWN_FACES_DIR}/{filename}')

            # This time we first grab face locations - we'll need them to draw boxes
            locations = face_recognition.face_locations(image, model=MODEL)

            # Now since we know loctions, we can pass them to face_encodings as second argument
            # Without that it will search for faces once again slowing down whole process
            encodings = face_recognition.face_encodings(image, locations)

            # But this time we assume that there might be more faces in an image - we can find faces of dirrerent people
            if len(encodings) == 0:
                ser.write(str.encode('f'))
                continue

            for face_encoding, face_location in zip(encodings, locations):

                # We use compare_faces (but might use face_distance as well)
                # Returns array of True/False values in order of passed known_faces
                results = face_recognition.compare_faces(known_faces, face_encoding, TOLERANCE)

                # Since order is being preserved, we check if any face was found then grab index
                # then label (name) of first matching known face withing a tolerance
                match = None
                if True in results:  # If at least one is true, get a name of first of found labels
                    ser.write(str.encode('t'))
                    match = known_names[results.index(True)]

                else:
                    ser.write(str.encode('f'))
