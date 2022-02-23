import os
TEMPLATE_DIR = r"C:\Users\nadav\Desktop\SFML\Build-A-Font\Build-A-Font\Build-A-Font\Templates"

def retrieve_filenames():
    filenames = os.listdir(TEMPLATE_DIR)
    for filename in filenames:
        filename = "Templates/" + filename
    return filenames

def concatenateDirectory(filename, dir):
    filename = dir + filename