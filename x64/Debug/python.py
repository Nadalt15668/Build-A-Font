import os
TEMPLATES_CHR_DIR = r"C:\Users\nadav\Desktop\SFML\Build-A-Font\Build-A-Font\Templates\CharacterTemplates\Characters"
TEMPLATES_NUM_DIR = r"C:\Users\nadav\Desktop\SFML\Build-A-Font\Build-A-Font\Templates\CharacterTemplates\Numbers"
TEMPLATES_SMBL_DIR = r"C:\Users\nadav\Desktop\SFML\Build-A-Font\Build-A-Font\Templates\CharacterTemplates\Symbols"
CHARACTERS_DIR = r"C:\Users\nadav\Desktop\SFML\Build-A-Font\Build-A-Font\CharacterDrawings\Drawings"

def retrieve_templates():
    filenames = os.listdir(TEMPLATES_CHR_DIR)
    filenames = filenames + os.listdir(TEMPLATES_NUM_DIR)
    filenames = filenames + os.listdir(TEMPLATES_SMBL_DIR)
    return filenames

def retrieve_characters():
    filenames = os.listdir(CHARACTERS_DIR)
    return filenames