import os
CHARACTERS_DIR = r"C:\Users\nadav\Desktop\SFML\Build-A-Font\Build-A-Font\Build-A-Font\Templates\CharacterTemplates\Characters"
NUMBERS_DIR = r"C:\Users\nadav\Desktop\SFML\Build-A-Font\Build-A-Font\Build-A-Font\Templates\CharacterTemplates\Numbers"
SYMBOLS_DIR = r"C:\Users\nadav\Desktop\SFML\Build-A-Font\Build-A-Font\Build-A-Font\Templates\CharacterTemplates\Symbols"

def retrieve_filenames():
    filenames = os.listdir(CHARACTERS_DIR)
    filenames = filenames + os.listdir(NUMBERS_DIR)
    filenames = filenames + os.listdir(SYMBOLS_DIR)
    return filenames