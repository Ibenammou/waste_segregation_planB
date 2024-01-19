import cv2
import os
import numpy as np
import serial
import urllib.request

ser = serial.Serial('COM3', 9600)  # Replace 'COM3' with the correct COM port

# URL of the IP Webcam
url_ipwebcam = 'http://192.168.1.9:8080/shot.jpg'
video = cv2.VideoCapture(url_ipwebcam)

# Load class names
class_names = []
class_folder = r'C:\\Users\\Windownet\\Desktop\\waste segregation\\santa'

# List all subfolders (class names) in the 'santa' folder
for class_folder_name in os.listdir(class_folder):
    class_path = os.path.join(class_folder, class_folder_name)
    if os.path.isdir(class_path):
        class_names.append(class_folder_name)

# Load the trained model
# Update the paths to your configuration and weights files
config_path = r'C:\\Users\\Windownet\\Desktop\\planb\\yolov3.cfg'
weight_path = r'C:\\Users\\Windownet\\Desktop\\planb\\yolov3.weights'

net = cv2.dnn_DetectionModel(weight_path, config_path)
net.setInputSize(416, 416)
net.setInputScale(1.0 / 255)
net.setInputSwapRB(True)

# Create a window named "Output" with automatic size adjustment
cv2.namedWindow("Output", cv2.WINDOW_AUTOSIZE)

while True:
    try:
        # Read the image from the IP Webcam
        ipwebcam_img_array = urllib.request.urlopen(url_ipwebcam).read()
        img = cv2.imdecode(np.array(bytearray(ipwebcam_img_array), dtype=np.uint8), -1)

        # Object detection
        class_ids, confs, bbox = net.detect(img, confThreshold=0.5)

        if len(class_ids) != 0:
            # Draw bounding boxes and labels on the image
            for class_id, confidence, box in zip(class_ids.flatten(), confs.flatten(), bbox):
                cv2.rectangle(img, box, color=(0, 255, 0), thickness=2)
                cv2.putText(img, class_names[class_id - 1], (box[0] + 10, box[1] + 20),
                            cv2.FONT_HERSHEY_COMPLEX, 1, (0, 255, 0), thickness=2)

                # Send a signal to Arduino based on the detected waste type
                waste_type = class_names[class_id - 1]
                if waste_type == 'metal_waste':
                    ser.write(b'1')  # Send '1' to the serial port for metal waste
                elif waste_type == 'paper_waste':
                    ser.write(b'2')  # Send '2' to the serial port for paper waste
                elif waste_type == 'plastic_waste':
                    ser.write(b'3')  # Send '3' to the serial port for plastic waste

        # Display the image from the IP Webcam in the "Output" window
        cv2.imshow('Output', img)

    except Exception as e:
        print(f"Error: {e}")

    # Wait for a short period (1 millisecond) and check if the 'q' key is pressed to exit
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release resources and destroy the window when exiting
cv2.destroyAllWindows()
